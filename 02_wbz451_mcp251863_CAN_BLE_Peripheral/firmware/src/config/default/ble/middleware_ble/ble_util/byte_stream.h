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
  Byte Stream Header File

  Company:
    Microchip Technology Inc.

  File Name:
   byte_stream.h

  Summary:
    This file contains the endian transit functions for this project.

  Description:
    This file contains the endian transit functions for this project.
 *******************************************************************************/


/**
 * @addtogroup BYTE_STREAM BYTE_STREAM
 * @{
 * @brief Header file for the byte-stream translation definitions.
 */

#ifndef BYTE_STREAM_H
#define BYTE_STREAM_H

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************

/** @brief Retrieve an uint16_t data in little endian format from an address of byte array.
 * @{ */
#define BUF_LE_TO_U16(p_value, p_src)\
    *p_value = ((uint16_t)*(p_src)) + (((uint16_t)*(p_src+1))<<8);
/** @} */

/** @brief Retrieve an uint16_t data in big endian format from an address of byte array.
 * @{ */
#define BUF_BE_TO_U16(p_value, p_src)\
    *p_value = (((uint16_t)*(p_src))<<8) + (uint16_t)*(p_src+1);
/** @} */

/** @brief Copy a variable length data from a buffer. Endian of the data will be changed.
 * @{ */
#define BUF_TO_VARIABLE(p_value, p_src, length)\
{\
    uint8_t idx;\
    for (idx=0; idx<length; idx++)\
    {\
        *(p_value+length-1-idx) = (p_src)[idx];\
    }\
}
/** @} */

/** @brief Copy a variable length data from a buffer. Endian of the data remains.
 * @{ */
#define BUF_COPY_TO_VARIABLE(p_value, p_src, length)\
        memcpy((uint8_t *)p_value, (uint8_t *)(p_src), length);
/** @} */


/** @brief Set an uint16_t value in big endian format to a byte array.
 * @{ */
#define U16_TO_BUF_LE(p_dest, src)\
    *(p_dest) = (uint8_t)src;\
    *(p_dest+1) = (uint8_t)(src >> 8);
/** @} */

/** @brief Set an uint16_t value in big endian format to a byte array.
 * @{ */
#define U16_TO_BUF_BE(p_dest, src)\
    *(p_dest) = (uint8_t)(src>>8);\
    *(p_dest+1) = (uint8_t)src;
/** @} */

/** @brief Set an uint32_t value in little endian format to a byte array.
 * @{ */
#define U32_TO_BUF_LE(p_dest, src)\
    *(p_dest) = (uint8_t)src;\
    *(p_dest+1) = (uint8_t)(src >> 8);\
    *(p_dest+2) = (uint8_t)(src >> 16);\
    *(p_dest+3) = (uint8_t)(src >> 24);
/** @} */

/** @brief Set an uint32_t value in big endian format to a byte array.
 * @{ */
#define U32_TO_BUF_BE(p_dest, src)\
    *(p_dest) = (uint8_t)(src >> 24);\
    *(p_dest+1) = (uint8_t)(src >> 16);\
    *(p_dest+2) = (uint8_t)(src >> 8);\
    *(p_dest+3) = (uint8_t)src;
/** @} */

/** @brief Copy a variable-length data to an address. Endian of data will be changed.
 * @{ */
#define VARIABLE_TO_BUF(p_dest, p_src, length)\
{\
    uint8_t idx;\
    for (idx=0; idx<length; idx++)\
    {\
        *(p_dest+(length-1)-idx) = *(p_src+idx);\
    }\
}
/** @} */

/** @brief Copy a variable-length data to an address. Endian of data remains.
 * @{ */
#define VARIABLE_COPY_TO_BUF(p_dest, p_src, length)\
    memcpy(p_dest, p_src, length);
/** @} */


/** @brief Retrieve an uint8_t data from a byte stream
 * @{ */
#define STREAM_TO_U8(p_value, p_src)\
    *p_value=*(p_src)[0];\
    (*p_src)++;
/** @} */

/** @brief Retrieve an uint16_t data from an address of little endian stream
 * @{ */
#define STREAM_LE_TO_U16(p_value, p_src)\
    *p_value=((uint16_t)(*p_src)[0]) + (((uint16_t)(*p_src)[1])<<8);\
    (*p_src)+=2;
/** @} */

/** @brief Retrieve an uint16_t data from an address of big endian stream
 * @{ */
#define STREAM_BE_TO_U16(p_value, p_src)\
    *p_value=((uint16_t)(*p_src)[1]) + (((uint16_t)(*p_src)[0])<<8);\
    (*p_src)+=2;
/** @} */

/** @brief Retrieve an uint32_t data from an address of little endian stream
 * @{ */
#define STREAM_LE_TO_U32(p_value, p_src)\
    *p_value=((uint32_t)(*p_src)[0]) + (((uint32_t)(*p_src)[1])<<8) + (((uint32_t)(*p_src)[2])<<16)+ (((uint32_t)(*p_src)[3])<<24);\
    (*p_src)+=4;
/** @} */

/** @brief Retrieve an uint32_t data from an address of big endian stream
 * @{ */
#define STREAM_BE_TO_U32(p_value, p_src)\
    *p_value=((uint32_t)(*p_src)[3]) + (((uint32_t)(*p_src)[2])<<8) + (((uint32_t)(*p_src)[1])<<16)+ (((uint32_t)(*p_src)[0])<<24);\
    (*p_src)+=4;
/** @} */

/** @brief Copy a variable length data from a byte stream. Endian of the data will be changed.
 * @{ */
#define STREAM_TO_VARIABLE(p_value, p_src, length)\
{\
    uint8_t idx;\
    for (idx=0; idx<length; idx++)\
    {\
        *(p_value+length-1-idx) = (*p_src)[idx];\
    }\
    (*p_src)+=length;\
}
/** @} */

/** @brief Copy a variable length data from a byte stream. Endian of the data remains.
 * @{ */
#define STREAM_COPY_TO_VARIABLE(p_value, p_src, length)\
        memcpy((uint8_t *)p_value, (uint8_t *)(*p_src), length);\
        (*p_src)+=length;
/** @} */


/** @brief Insert an uint8_t value to a byte stream
 * @{ */
#define U8_TO_STREAM(p_dest, value)\
    (*p_dest)[0] = value;\
    (*p_dest)++;
/** @} */


/** @brief Insert an uint16_t value in little endian format to a byte stream
 * @{ */
#define U16_TO_STREAM_LE(p_dest, value)\
    memcpy(*p_dest, (uint8_t *)&value, 2);\
    (*p_dest)+=2;
/** @} */

/** @brief Insert an uint16_t value in big endian format to a byte stream
 * @{ */
#define U16_TO_STREAM_BE(p_dest, value)\
    (*p_dest)[0] = (uint8_t)(value>>8);\
    (*p_dest)[1] = (uint8_t)value;\
    (*p_dest)+=2;
/** @} */

/** @brief Insert an uint32_t value in little endian format to a byte stream
 * @{ */

#define U32_TO_STREAM_LE(p_dest, value)\
    memcpy(*p_dest, (uint8_t *)&value, 4);\
    (*p_dest)+=4;
/** @} */

/** @brief Insert an uint32_t value in big endian format to a byte stream
 * @{ */
#define U32_TO_STREAM_BE(p_dest, value)\
    (*p_dest)[0] = (uint8_t)(value >> 24);\
    (*p_dest)[1] = (uint8_t)(value >> 16);\
    (*p_dest)[2] = (uint8_t)(value >> 8);\
    (*p_dest)[3] = (uint8_t)value;\
    (*p_dest)+=4;
/** @} */

/** @brief Copy a variable-length data to an address. Endian of data will be changed.
 * @{ */
#define VARIABLE_TO_STREAM(p_dest, p_src, length)\
{\
    uint8_t idx;\
    for (idx=0; idx<length; idx++)\
    {\
        (*p_dest)[(length-1)-idx]= *(p_src+idx);\
    }\
    (*p_dest)+=length;\
}
/** @} */

/** @brief Copy a variable-length data to an address. Endian of data remains.
 * @{ */
#define VARIABLE_COPY_TO_STREAM(p_dest, p_src, length)\
    memcpy((uint8_t *)*p_dest, (uint8_t *)p_src, length);\
    (*p_dest)+=length;
/** @} */


/**@defgroup INTERGER_TO_ARRAY_BYTES INTERGER_TO_ARRAY_BYTES
 * @brief Macros for converting integers to array of bytes in little endian format
 * @{ */

/**@brief convert uint16_t to array of bytes. */
#define UINT16_TO_BYTES(n)        ((uint8_t) (n)), ((uint8_t)((n) >> 8))
/**@brief convert little endian uint32_t to array of bytes. */
#define UINT32_TO_BYTES(n)        ((uint8_t) (n)), ((uint8_t)((n) >> 8)), ((uint8_t)((n) >> 16)), ((uint8_t)((n) >> 24))

/**@brief convert uint16_t to array of bytes in big endian format. */
#define UINT16_TO_BYTES_BE(n)     ((uint8_t)((n) >> 8)), ((uint8_t) (n))


/**@}*/

#endif

/** @} */

