/*******************************************************************************
* Copyright (C) 2022 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

/*******************************************************************************
  Application AES Storage Source File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_dm_aes.c

  Summary:
    This file contains the AES functions for BLE Device Manager module internal use.

  Description:
    This file contains the AES functions for BLE Device Manager module internal use.
 *******************************************************************************/


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include <string.h>
#include "ble_dm/ble_dm_aes.h"

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************


#define BLE_DM_AES_BLOCK_LEN        16      //Block length in bytes AES is 128b block only

#define BLE_DM_AES_KEY_EXP_SIZE     176


#define BLE_DM_AES_NB               4       // The number of columns comprising a state in AES. This is a constant in AES. Value=4
#define BLE_DM_AES_NK               4       // The number of 32 bit words in a key.
#define BLE_DM_AES_NR               10      // The number of rounds in AES Cipher.

#define BLE_DM_AES_GET_SBOX_VALUE(num) (s_aesSbox[(num)])
#define BLE_DM_AES_GET_SBOX_INVERT(num) (s_aesRsbox[(num)])

// BLE_DM_AES_MULTIPLY is used to multiply numbers in the field GF(2^8)
// Note: The last call to BLE_DM_AesXTime() is unneeded, but often ends up generating a smaller binary
//       The compiler seems to be able to vectorize the operation better this way.
//       See https://github.com/kokke/tiny-AES-c/pull/34

#define BLE_DM_AES_MULTIPLY(x, y)                                \
      (  ((y & 1) * x) ^                              \
      ((y>>1 & 1) * BLE_DM_AesXTime(x)) ^                       \
      ((y>>2 & 1) * BLE_DM_AesXTime(BLE_DM_AesXTime(x))) ^                \
      ((y>>3 & 1) * BLE_DM_AesXTime(BLE_DM_AesXTime(BLE_DM_AesXTime(x)))) ^         \
      ((y>>4 & 1) * BLE_DM_AesXTime(BLE_DM_AesXTime(BLE_DM_AesXTime(BLE_DM_AesXTime(x))))))   \


// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

struct BLE_DM_AesCtx_T
{
  uint8_t roundKey[BLE_DM_AES_KEY_EXP_SIZE];
  uint8_t iv[BLE_DM_AES_BLOCK_LEN];
};

// state - array holding the intermediate results during decryption.
typedef uint8_t BLE_DM_AesState_T[4][4];


// *****************************************************************************
// *****************************************************************************
// Section: Local Variables
// *****************************************************************************
// *****************************************************************************

// The lookup-tables are marked const so they can be placed in read-only storage instead of RAM
// The numbers below can be computed dynamically trading ROM for RAM - 
// This can be useful in (embedded) bootloader applications, where ROM is often limited.
static uint8_t const s_aesSbox[256] = {
  //0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
  0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
  0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
  0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
  0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
  0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
  0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
  0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
  0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
  0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
  0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
  0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
  0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
  0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
  0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
  0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };

static uint8_t const s_aesRsbox[256] = {
  0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
  0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
  0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
  0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
  0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
  0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
  0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
  0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
  0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
  0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
  0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
  0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
  0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
  0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
  0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
  0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };

// The round constant word array, s_aesRcon[i], contains the values given by 
// x to the power (i-1) being powers of x (x is denoted as {02}) in the field GF(2^8)
static uint8_t const s_aesRcon[11] = {
  0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };

// *****************************************************************************
// *****************************************************************************
// Section: Functions
// *****************************************************************************
// *****************************************************************************

// This function produces BLE_DM_AES_NB(BLE_DM_AES_NR+1) round keys. The round keys are used in each round to decrypt the states. 
static void BLE_DM_AesKeyExpansion(uint8_t *p_roundKey, const uint8_t *p_key)
{
    unsigned    i, j, k;
    uint8_t     tempa[4]; // Used for the column/row operations
  
  // The first round key is the key itself.
    for (i = 0; i < BLE_DM_AES_NK; ++i)
    {
        p_roundKey[(i * 4) + 0] = p_key[(i * 4) + 0];
        p_roundKey[(i * 4) + 1] = p_key[(i * 4) + 1];
        p_roundKey[(i * 4) + 2] = p_key[(i * 4) + 2];
        p_roundKey[(i * 4) + 3] = p_key[(i * 4) + 3];
    }

  // All other round keys are found from the previous round keys.
    for (i = BLE_DM_AES_NK; i < BLE_DM_AES_NB * (BLE_DM_AES_NR + 1); ++i)
    {
      {
          k = (i - 1) * 4;
          tempa[0]=p_roundKey[k + 0];
          tempa[1]=p_roundKey[k + 1];
          tempa[2]=p_roundKey[k + 2];
          tempa[3]=p_roundKey[k + 3];
      }

      if (i % BLE_DM_AES_NK == 0)
      {
      // This function shifts the 4 bytes in a word to the left once.
      // [a0,a1,a2,a3] becomes [a1,a2,a3,a0]

      // Function RotWord()
        {
            k = tempa[0];
            tempa[0] = tempa[1];
            tempa[1] = tempa[2];
            tempa[2] = tempa[3];
            tempa[3] = k;
        }

      // SubWord() is a function that takes a four-byte input word and 
      // applies the S-box to each of the four bytes to produce an output word.

      // Function Subword()
        {
            tempa[0] = BLE_DM_AES_GET_SBOX_VALUE(tempa[0]);
            tempa[1] = BLE_DM_AES_GET_SBOX_VALUE(tempa[1]);
            tempa[2] = BLE_DM_AES_GET_SBOX_VALUE(tempa[2]);
            tempa[3] = BLE_DM_AES_GET_SBOX_VALUE(tempa[3]);
        }

        tempa[0] = tempa[0] ^ s_aesRcon[i/BLE_DM_AES_NK];
      }

      j = i * 4; k=(i - BLE_DM_AES_NK) * 4;
      p_roundKey[j + 0] = p_roundKey[k + 0] ^ tempa[0];
      p_roundKey[j + 1] = p_roundKey[k + 1] ^ tempa[1];
      p_roundKey[j + 2] = p_roundKey[k + 2] ^ tempa[2];
      p_roundKey[j + 3] = p_roundKey[k + 3] ^ tempa[3];
    }
}

static void BLE_DM_AesInitCtx(struct BLE_DM_AesCtx_T *p_ctx, const uint8_t *p_key)
{
    BLE_DM_AesKeyExpansion(p_ctx->roundKey, p_key);
}

// This function adds the round key to state.
// The round key is added to the state by an XOR function.
static void BLE_DM_AesAddRoundKey(uint8_t round, BLE_DM_AesState_T *p_state, uint8_t *p_roundKey)
{
    uint8_t i,j;
    for (i = 0; i < 4; ++i)
    {
      for (j = 0; j < 4; ++j)
      {
          (*p_state)[i][j] ^= p_roundKey[(round * BLE_DM_AES_NB * 4) + (i * BLE_DM_AES_NB) + j];
      }
    }
}

// The BLE_DM_AesSubBytes Function Substitutes the values in the
// state matrix with values in an S-box.
static void BLE_DM_AesSubBytes(BLE_DM_AesState_T* p_state)
{
    uint8_t i, j;
    for (i = 0; i < 4; ++i)
    {
      for (j = 0; j < 4; ++j)
      {
          (*p_state)[j][i] = BLE_DM_AES_GET_SBOX_VALUE((*p_state)[j][i]);
      }
    }
}

// The BLE_DM_AesShiftRows() function shifts the rows in the state to the left.
// Each row is shifted with different offset.
// Offset = Row number. So the first row is not shifted.
static void BLE_DM_AesShiftRows(BLE_DM_AesState_T* p_state)
{
    uint8_t temp;

  // Rotate first row 1 columns to left  
    temp           = (*p_state)[0][1];
    (*p_state)[0][1] = (*p_state)[1][1];
    (*p_state)[1][1] = (*p_state)[2][1];
    (*p_state)[2][1] = (*p_state)[3][1];
    (*p_state)[3][1] = temp;

  // Rotate second row 2 columns to left  
    temp           = (*p_state)[0][2];
    (*p_state)[0][2] = (*p_state)[2][2];
    (*p_state)[2][2] = temp;

    temp           = (*p_state)[1][2];
    (*p_state)[1][2] = (*p_state)[3][2];
    (*p_state)[3][2] = temp;

  // Rotate third row 3 columns to left
    temp           = (*p_state)[0][3];
    (*p_state)[0][3] = (*p_state)[3][3];
    (*p_state)[3][3] = (*p_state)[2][3];
    (*p_state)[2][3] = (*p_state)[1][3];
    (*p_state)[1][3] = temp;
}

static uint8_t BLE_DM_AesXTime(uint8_t x)
{
    return ((x<<1) ^ (((x>>7) & 1) * 0x1b));
}

// BLE_DM_AesMixColumns function mixes the columns of the state matrix
static void BLE_DM_AesMixColumns(BLE_DM_AesState_T *p_state)
{
    uint8_t i;
    uint8_t tmp, tm, t;
    for (i = 0; i < 4; ++i)
    {  
        t   = (*p_state)[i][0];
        tmp = (*p_state)[i][0] ^ (*p_state)[i][1] ^ (*p_state)[i][2] ^ (*p_state)[i][3] ;
        tm  = (*p_state)[i][0] ^ (*p_state)[i][1] ; tm = BLE_DM_AesXTime(tm);  (*p_state)[i][0] ^= tm ^ tmp ;
        tm  = (*p_state)[i][1] ^ (*p_state)[i][2] ; tm = BLE_DM_AesXTime(tm);  (*p_state)[i][1] ^= tm ^ tmp ;
        tm  = (*p_state)[i][2] ^ (*p_state)[i][3] ; tm = BLE_DM_AesXTime(tm);  (*p_state)[i][2] ^= tm ^ tmp ;
        tm  = (*p_state)[i][3] ^ t ;              tm = BLE_DM_AesXTime(tm);  (*p_state)[i][3] ^= tm ^ tmp ;
    }
}


// BLE_DM_AesMixColumns function mixes the columns of the state matrix.
// The method used to multiply may be difficult to understand for the inexperienced.
// Please use the references to gain more information.
static void BLE_DM_AesInvMixColumns(BLE_DM_AesState_T *p_state)
{
    int i;
    uint8_t a, b, c, d;
    for (i = 0; i < 4; ++i)
    {
        a = (*p_state)[i][0];
        b = (*p_state)[i][1];
        c = (*p_state)[i][2];
        d = (*p_state)[i][3];

        (*p_state)[i][0] = BLE_DM_AES_MULTIPLY(a, 0x0e) ^ BLE_DM_AES_MULTIPLY(b, 0x0b) ^ BLE_DM_AES_MULTIPLY(c, 0x0d) ^ BLE_DM_AES_MULTIPLY(d, 0x09);
        (*p_state)[i][1] = BLE_DM_AES_MULTIPLY(a, 0x09) ^ BLE_DM_AES_MULTIPLY(b, 0x0e) ^ BLE_DM_AES_MULTIPLY(c, 0x0b) ^ BLE_DM_AES_MULTIPLY(d, 0x0d);
        (*p_state)[i][2] = BLE_DM_AES_MULTIPLY(a, 0x0d) ^ BLE_DM_AES_MULTIPLY(b, 0x09) ^ BLE_DM_AES_MULTIPLY(c, 0x0e) ^ BLE_DM_AES_MULTIPLY(d, 0x0b);
        (*p_state)[i][3] = BLE_DM_AES_MULTIPLY(a, 0x0b) ^ BLE_DM_AES_MULTIPLY(b, 0x0d) ^ BLE_DM_AES_MULTIPLY(c, 0x09) ^ BLE_DM_AES_MULTIPLY(d, 0x0e);
    }
}


// The BLE_DM_AesSubBytes Function Substitutes the values in the
// state matrix with values in an S-box.
static void BLE_DM_AesInvSubBytes(BLE_DM_AesState_T *p_state)
{
    uint8_t i, j;
    for (i = 0; i < 4; ++i)
    {
       for (j = 0; j < 4; ++j)
       {
           (*p_state)[j][i] = BLE_DM_AES_GET_SBOX_INVERT((*p_state)[j][i]);
       }
    }
}

static void BLE_DM_AesInvShiftRows(BLE_DM_AesState_T *p_state)
{
    uint8_t temp;

  // Rotate first row 1 columns to right  
    temp = (*p_state)[3][1];
    (*p_state)[3][1] = (*p_state)[2][1];
    (*p_state)[2][1] = (*p_state)[1][1];
    (*p_state)[1][1] = (*p_state)[0][1];
    (*p_state)[0][1] = temp;

  // Rotate second row 2 columns to right 
    temp = (*p_state)[0][2];
    (*p_state)[0][2] = (*p_state)[2][2];
    (*p_state)[2][2] = temp;

    temp = (*p_state)[1][2];
    (*p_state)[1][2] = (*p_state)[3][2];
    (*p_state)[3][2] = temp;

  // Rotate third row 3 columns to right
    temp = (*p_state)[0][3];
    (*p_state)[0][3] = (*p_state)[1][3];
    (*p_state)[1][3] = (*p_state)[2][3];
    (*p_state)[2][3] = (*p_state)[3][3];
    (*p_state)[3][3] = temp;
}


// BLE_DM_AesCipher is the main function that encrypts the PlainText.
static void BLE_DM_AesCipher(BLE_DM_AesState_T *p_state, uint8_t *p_roundKey)
{
    uint8_t round = 0;

  // Add the First round key to the state before starting the rounds.
    BLE_DM_AesAddRoundKey(0, p_state, p_roundKey); 
  
  // There will be BLE_DM_AES_NR rounds.
  // The first BLE_DM_AES_NR-1 rounds are identical.
  // These BLE_DM_AES_NR-1 rounds are executed in the loop below.
    for (round = 1; round < BLE_DM_AES_NR; ++round)
    {
       BLE_DM_AesSubBytes(p_state);
       BLE_DM_AesShiftRows(p_state);
       BLE_DM_AesMixColumns(p_state);
       BLE_DM_AesAddRoundKey(round, p_state, p_roundKey);
    }
  
  // The last round is given below.
  // The BLE_DM_AesMixColumns function is not here in the last round.
    BLE_DM_AesSubBytes(p_state);
    BLE_DM_AesShiftRows(p_state);
    BLE_DM_AesAddRoundKey(BLE_DM_AES_NR, p_state, p_roundKey);
}

static void BLE_DM_AesInvCipher(BLE_DM_AesState_T *p_state, uint8_t *p_roundKey)
{
    uint8_t round = 0;

  // Add the First round key to the state before starting the rounds.
    BLE_DM_AesAddRoundKey(BLE_DM_AES_NR, p_state, p_roundKey); 

  // There will be BLE_DM_AES_NR rounds.
  // The first BLE_DM_AES_NR-1 rounds are identical.
  // These BLE_DM_AES_NR-1 rounds are executed in the loop below.
    for (round = (BLE_DM_AES_NR - 1); round > 0; --round)
    {
       BLE_DM_AesInvShiftRows(p_state);
       BLE_DM_AesInvSubBytes(p_state);
       BLE_DM_AesAddRoundKey(round, p_state, p_roundKey);
       BLE_DM_AesInvMixColumns(p_state);
    }
  
  // The last round is given below.
  // The BLE_DM_AesMixColumns function is not here in the last round.
    BLE_DM_AesInvShiftRows(p_state);
    BLE_DM_AesInvSubBytes(p_state);
    BLE_DM_AesAddRoundKey(0, p_state, p_roundKey);
}
static void BLE_DM_AesEcbEncrypt(struct BLE_DM_AesCtx_T *p_ctx, const uint8_t *p_buf)
{
  // The next function call encrypts the PlainText with the Key using AES algorithm.
  BLE_DM_AesCipher((BLE_DM_AesState_T*)p_buf, p_ctx->roundKey);
}

static void BLE_DM_AesEcbDecrypt(struct BLE_DM_AesCtx_T *p_ctx, const uint8_t *p_buf)
{
  // The next function call decrypts the PlainText with the Key using AES algorithm.
  BLE_DM_AesInvCipher((BLE_DM_AesState_T*)p_buf, p_ctx->roundKey);
}

void BLE_DM_Aes128Encrypt(uint8_t *p_key, uint8_t *p_plaintext, uint8_t *p_ciphertext)
{
    struct BLE_DM_AesCtx_T ctx;
    memcpy(p_ciphertext, p_plaintext, 16);
    BLE_DM_AesInitCtx(&ctx, p_key);
    BLE_DM_AesEcbEncrypt(&ctx, p_ciphertext);
}

void BLE_DM_Aes128Decrypt(uint8_t *p_key, uint8_t *p_plaintext, uint8_t *p_ciphertext)
{
	struct BLE_DM_AesCtx_T ctx;
	memcpy(p_plaintext, p_ciphertext,16);
	BLE_DM_AesInitCtx(&ctx, p_key);
	BLE_DM_AesEcbDecrypt(&ctx, p_plaintext);
}

