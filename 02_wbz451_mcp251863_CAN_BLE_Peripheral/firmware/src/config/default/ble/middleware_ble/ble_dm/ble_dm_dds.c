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
  Device Information Middleware Source File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_dm_dds.c

  Summary:
    This file contains the Device Data Storage functions for 
    BLE Device Manager module internal use.

  Description:
    This file contains the Device Data Storage functions for 
    BLE Device Manager module internal use.
 *******************************************************************************/


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include <string.h>
#include "crypto/crypto.h"
#include "ble_dm/ble_dm_dds.h"
#include "ble_dm/ble_dm_aes.h"
#include "pds.h"


typedef enum BLE_DM_PdsBleItem_T{
    PDS_BLE_ITEM_ID_1 = (PDS_MODULE_BT_OFFSET),
    PDS_BLE_ITEM_ID_2,
    PDS_BLE_ITEM_ID_3,
    PDS_BLE_ITEM_ID_4,
    PDS_BLE_ITEM_ID_5,
    PDS_BLE_ITEM_ID_6,
    PDS_BLE_ITEM_ID_7,
    PDS_BLE_ITEM_ID_8
}BLE_DM_PdsBleItem_T;

#define BLE_DM_DDS_FILE_PAIRED_START       PDS_BLE_ITEM_ID_1

//#define BLE_DM_DDS_DIR_PAIRED_DEVICE       PDS_BLE_DIR_ID_1

// *****************************************************************************
// *****************************************************************************
// Section: Local Variables
// *****************************************************************************
// *****************************************************************************

BLE_DM_PairedDevInfo_T s_pairedInfo;

PDS_DECLARE_FILE(PDS_BLE_ITEM_ID_1, sizeof(BLE_DM_PairedDevInfo_T), &s_pairedInfo,FILE_INTEGRITY_CONTROL_MARK);
PDS_DECLARE_FILE(PDS_BLE_ITEM_ID_2, sizeof(BLE_DM_PairedDevInfo_T), &s_pairedInfo,FILE_INTEGRITY_CONTROL_MARK);
PDS_DECLARE_FILE(PDS_BLE_ITEM_ID_3, sizeof(BLE_DM_PairedDevInfo_T), &s_pairedInfo,FILE_INTEGRITY_CONTROL_MARK);
PDS_DECLARE_FILE(PDS_BLE_ITEM_ID_4, sizeof(BLE_DM_PairedDevInfo_T), &s_pairedInfo,FILE_INTEGRITY_CONTROL_MARK);
PDS_DECLARE_FILE(PDS_BLE_ITEM_ID_5, sizeof(BLE_DM_PairedDevInfo_T), &s_pairedInfo,FILE_INTEGRITY_CONTROL_MARK);
PDS_DECLARE_FILE(PDS_BLE_ITEM_ID_6, sizeof(BLE_DM_PairedDevInfo_T), &s_pairedInfo,FILE_INTEGRITY_CONTROL_MARK);
PDS_DECLARE_FILE(PDS_BLE_ITEM_ID_7, sizeof(BLE_DM_PairedDevInfo_T), &s_pairedInfo,FILE_INTEGRITY_CONTROL_MARK);
PDS_DECLARE_FILE(PDS_BLE_ITEM_ID_8, sizeof(BLE_DM_PairedDevInfo_T), &s_pairedInfo,FILE_INTEGRITY_CONTROL_MARK);

// *****************************************************************************
// *****************************************************************************
// Section: Functions
// *****************************************************************************
// *****************************************************************************

static uint8_t ble_dm_DdsCheckResolveAddress(uint8_t *p_remoteIrk, uint8_t *p_remoteAddr)
{
    uint8_t data[16], temp[16];
    uint8_t i;
    CRYPT_AES_CTX mcAes;

    /* convert irk as aes key */
    for(i=0; i<16; i++)
      temp[i]=p_remoteIrk[15-i];

    CRYPT_AES_KeySet(&mcAes, temp, 16, NULL, CRYPT_AES_ENCRYPTION);

    /* get prand from address */
    memset(&data[0], 0, 13);
    for(i=0; i<3; i++)
      data[13+i]=p_remoteAddr[5-i];

    /* calculate localHash value */
    CRYPT_AES_DIRECT_Encrypt(&mcAes, temp, data);

    /* extract hash value from address */
    for(i=0; i<3; i++)
      data[i]=p_remoteAddr[2-i];

    /* compare localHash with hash from address */
    return (memcmp(temp + 13, data, 3) == 0);
}


uint16_t BLE_DM_DdsGetPairedDevice(uint8_t devId, BLE_DM_PairedDevInfo_T * p_pairedDevInfo)
{
    if (devId >= BLE_DM_MAX_PAIRED_DEVICE_NUM
        || PDS_IsAbleToRestore(BLE_DM_DDS_FILE_PAIRED_START + devId) == false)
        return MBA_RES_INVALID_PARA;

    if (PDS_Restore(BLE_DM_DDS_FILE_PAIRED_START + devId))
    {
        memcpy(p_pairedDevInfo, &s_pairedInfo, sizeof(BLE_DM_PairedDevInfo_T));
        return MBA_RES_SUCCESS;
    }
    else
        return MBA_RES_FAIL;
}

uint16_t BLE_DM_DdsSetPairedDevice(uint8_t devId, BLE_DM_PairedDevInfo_T *p_pairedDevInfo)
{
    if (devId >= BLE_DM_MAX_PAIRED_DEVICE_NUM)
        return MBA_RES_INVALID_PARA;

    memcpy(&s_pairedInfo, p_pairedDevInfo, sizeof(BLE_DM_PairedDevInfo_T));

    if (PDS_Store(BLE_DM_DDS_FILE_PAIRED_START + devId))
    {
        return MBA_RES_SUCCESS;
    }
    else
        return MBA_RES_FAIL;
}

uint8_t BLE_DM_DdsGetFreeDeviceId()
{
    uint8_t devId;

    for (devId = 0; devId < BLE_DM_MAX_PAIRED_DEVICE_NUM; devId++)
    {
        if (!PDS_IsAbleToRestore(BLE_DM_DDS_FILE_PAIRED_START + devId))
        {
            break;
        }
    }

    return devId;
}

uint8_t BLE_DM_DdsGetDeviceId(BLE_GAP_Addr_T *p_bdAddr)
{
    uint8_t devId;

    /* check if non-resolvable private address? */
    if (p_bdAddr->addrType == BLE_GAP_ADDR_TYPE_RANDOM_NON_RESOLVABLE)
        return BLE_DM_MAX_PAIRED_DEVICE_NUM;
    
    for (devId = 0; devId < BLE_DM_MAX_PAIRED_DEVICE_NUM; devId++)
    {
        if (PDS_IsAbleToRestore(BLE_DM_DDS_FILE_PAIRED_START + devId))
        {
            if (PDS_Restore(BLE_DM_DDS_FILE_PAIRED_START + devId))
            {
                if (p_bdAddr->addrType == BLE_GAP_ADDR_TYPE_RANDOM_RESOLVABLE)
                {
                    if (ble_dm_DdsCheckResolveAddress(s_pairedInfo.remoteIrk, p_bdAddr->addr))
                        break;
                }
                else
                {
                    if (memcmp(p_bdAddr->addr, s_pairedInfo.remoteAddr.addr, GAP_MAX_BD_ADDRESS_LEN) == 0)
                    {
                        break;
                    }
                }
            }
        }
    }

    return devId;
}

uint16_t BLE_DM_DdsDeletePairedDevice(uint8_t devId)
{
    if (devId >= BLE_DM_MAX_PAIRED_DEVICE_NUM)
        return MBA_RES_INVALID_PARA;

    if (PDS_Delete(BLE_DM_DDS_FILE_PAIRED_START + devId) == PDS_SUCCESS)
    {
        return MBA_RES_SUCCESS;
    }
    else
        return MBA_RES_FAIL;
}

uint16_t BLE_DM_DdsDeleteAllPairedDevice()
{
    uint8_t devId;

    for (devId = 0; devId < BLE_DM_MAX_PAIRED_DEVICE_NUM; devId++)
    {
        if (PDS_Delete(BLE_DM_DDS_FILE_PAIRED_START + devId) != PDS_SUCCESS)
            return MBA_RES_FAIL;
    }

    return MBA_RES_SUCCESS;
}

bool BLE_DM_DdsChkDeviceId(uint8_t devId)
{
    return PDS_IsAbleToRestore(BLE_DM_DDS_FILE_PAIRED_START + devId);
}


