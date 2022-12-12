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
  Security Manager Middleware Source File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_dm_sm.c

  Summary:
    This file contains the Security Manager functions for 
    BLE Device Manager module internal use.

  Description:
    This file contains the Security Manager functions for 
    BLE Device Manager module internal use.
 *******************************************************************************/


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <string.h>
#include "osal/osal_freertos_extend.h"
#include "ble_dm/ble_dm.h"
#include "ble_dm/ble_dm_internal.h"
#include "ble_dm/ble_dm_info.h"
#include "ble_dm/ble_dm_dds.h"

// *****************************************************************************
// *****************************************************************************
// Section: Local Variables
// *****************************************************************************
// *****************************************************************************

static bool s_autoAccept;

// *****************************************************************************
// *****************************************************************************
// Section: Functions
// *****************************************************************************
// *****************************************************************************

static void ble_dm_SmConveyStartEvt(uint16_t connHandle, BLE_DM_SecurityProc_T procedure)
{
    BLE_DM_Event_T  dmEvt;
    dmEvt.eventId = BLE_DM_EVT_SECURITY_START;
    dmEvt.connHandle = connHandle;
    dmEvt.eventField.evtSecurityStart.procedure = procedure;
    BLE_DM_ConveyEvent(&dmEvt);
}

static void ble_dm_SmConveySuccessEvt(uint16_t connHandle, BLE_DM_SecurityProc_T procedure, uint8_t bonded)
{
    BLE_DM_Event_T  dmEvt;
    dmEvt.eventId = BLE_DM_EVT_SECURITY_SUCCESS;
    dmEvt.connHandle = connHandle;
    dmEvt.eventField.evtSecuritySuccess.procedure = procedure;
    dmEvt.eventField.evtSecuritySuccess.bonded = bonded;
    BLE_DM_ConveyEvent(&dmEvt);
}

static void ble_dm_SmConveyFailEvt(uint16_t connHandle, BLE_DM_SecurityProc_T procedure, uint8_t error, uint8_t reason)
{
     BLE_DM_Event_T  dmEvt;
     dmEvt.eventId = BLE_DM_EVT_SECURITY_FAIL;
     dmEvt.connHandle = connHandle;
     dmEvt.eventField.evtSecurityFail.procedure = procedure;
     dmEvt.eventField.evtSecurityFail.error = error;
     dmEvt.eventField.evtSecurityFail.reason = reason;
     BLE_DM_ConveyEvent(&dmEvt);
}


void ble_dm_SecurityManager(BLE_SMP_Event_T *p_event)
{
    switch (p_event->eventId)
    {
        case BLE_SMP_EVT_SECURITY_REQUEST:
        {
            if (s_autoAccept)
            {
                BLE_DM_InfoConn_T   *p_conn;
                uint16_t            result;

                p_conn = BLE_DM_InfoGetConnByHandle(p_event->eventField.evtSecurityReq.connHandle);

                if (p_conn == NULL)
                    return;

                if (p_conn->role == BLE_GAP_ROLE_CENTRAL)
                {
                    BLE_DM_PairedDevInfo_T bonding;
                    if (BLE_DM_DdsGetPairedDevice(p_conn->devId, &bonding) == MBA_RES_SUCCESS)
                    {
                        result = BLE_GAP_EnableEncryption(p_conn->connHandle, bonding.rv, bonding.ediv, bonding.ltk);

                        if (result == MBA_RES_SUCCESS)
                            ble_dm_SmConveyStartEvt(p_conn->connHandle, DM_SECURITY_PROC_ENCRYPTION);            
                    }
                    else
                    {
                        result = BLE_SMP_InitiatePairing(p_conn->connHandle);

                        if (result == MBA_RES_SUCCESS)
                            ble_dm_SmConveyStartEvt(p_conn->connHandle, DM_SECURITY_PROC_PAIRING);
                    }               
                }
            }
        }
        break;

        case BLE_SMP_EVT_PAIRING_REQUEST:
        {
            if (s_autoAccept)
            {
                BLE_DM_InfoConn_T   *p_conn;
                uint16_t            result;
                
                p_conn = BLE_DM_InfoGetConnByHandle(p_event->eventField.evtPairingReq.connHandle);
                
                if (p_conn == NULL)
                    return;

                if (p_conn->role == BLE_GAP_ROLE_PERIPHERAL)
                {
                    result = BLE_SMP_AcceptPairingRequest(p_event->eventField.evtPairingReq.connHandle);

                    if (MBA_RES_SUCCESS == result)
                    {
                        ble_dm_SmConveyStartEvt(p_event->eventField.evtPairingReq.connHandle, DM_SECURITY_PROC_PAIRING);
                    }
                }
            }
        }
        break;
        case BLE_SMP_EVT_PAIRING_COMPLETE:
        {
           if(p_event->eventField.evtPairingComplete.status == BLE_SMP_PAIRING_SUCCESS)
           {
                BLE_DM_InfoConn_T   *p_conn;

                p_conn = BLE_DM_InfoGetConnByHandle(p_event->eventField.evtPairingComplete.connHandle);
                if (p_conn==NULL)
                {
                    return;
                }

                ble_dm_SmConveySuccessEvt(p_event->eventField.evtPairingComplete.connHandle, DM_SECURITY_PROC_PAIRING, p_event->eventField.evtPairingComplete.bond);

                p_conn->encryptKeyValid = true;
                memcpy(p_conn->encryptKey, p_event->eventField.evtPairingComplete.encryptKey, 16);

                if (p_conn->role == BLE_GAP_ROLE_CENTRAL)
                    ble_dm_SmConveyStartEvt(p_conn->connHandle, DM_SECURITY_PROC_ENCRYPTION);
           }
           else
           {
                ble_dm_SmConveyFailEvt(p_event->eventField.evtPairingComplete.connHandle, DM_SECURITY_PROC_PAIRING
                    , p_event->eventField.evtPairingComplete.status, p_event->eventField.evtPairingComplete.failReason);
           }
        }
        break;
        case BLE_SMP_EVT_NOTIFY_KEYS:
        {
            BLE_SMP_KeyList_T       *p_key;
            uint8_t                 devId;
            BLE_DM_InfoConn_T       *p_conn;
            BLE_DM_PairedDevInfo_T  *p_devInfo;

            p_conn = BLE_DM_InfoGetConnByHandle(p_event->eventField.evtNotifyKeys.connHandle);
            if (p_conn == NULL)
                return;

            p_devInfo = OSAL_Malloc(sizeof(BLE_DM_PairedDevInfo_T));
            if (p_devInfo == NULL) return;
            
            p_key = &p_event->eventField.evtNotifyKeys.keys;

            p_devInfo->remoteAddr = p_key->remote.idInfo.addr;

            devId = BLE_DM_DdsGetDeviceId(&p_devInfo->remoteAddr);
            if (devId == BLE_DM_MAX_PAIRED_DEVICE_NUM)
            {
                devId = BLE_DM_DdsGetFreeDeviceId();
                if (devId == BLE_DM_MAX_PAIRED_DEVICE_NUM)
                {
                    BLE_DM_Event_T  dmEvt;
                    dmEvt.eventId = BLE_DM_EVT_PAIRED_DEVICE_FULL;
                    dmEvt.connHandle = p_conn->connHandle;
                    dmEvt.eventField.evtPairedDevFull.pairedDeviceNum = BLE_DM_MAX_PAIRED_DEVICE_NUM;
                    BLE_DM_ConveyEvent(&dmEvt);

                    devId = BLE_DM_DdsGetFreeDeviceId();

                    /* appliation does not delete device in callback function */
                    if (devId == BLE_DM_MAX_PAIRED_DEVICE_NUM)
                    {
                        OSAL_Free(p_devInfo);
                        break;
                    }
                }
            }

            p_conn->devId = devId;

            if (p_conn->role == BLE_GAP_ROLE_CENTRAL)
            {
                if (p_key->local.encInfo.lesc)
                {
                    memcpy(p_devInfo->ltk, (uint8_t *)(&p_key->local.encInfo.ltk[0]), 16);
                }
                else
                {
                    memcpy(p_devInfo->ltk, (uint8_t *)(&p_key->remote.encInfo.ltk[0]), 16);
                    memcpy(p_devInfo->rv, (uint8_t *)(&p_key->remote.encInfo.rand[0]), 8);
                    memcpy(p_devInfo->ediv, (uint8_t *)(&p_key->remote.encInfo.ediv[0]), 2);
                }

                memcpy(p_devInfo->remoteIrk, (uint8_t *)(&p_key->remote.idInfo.irk[0]), 16);
            }
            else
            {
                memcpy(p_devInfo->ltk, (uint8_t *)(&p_key->local.encInfo.ltk[0]), 16);
                memcpy(p_conn->encryptKey, (uint8_t *)&p_key->local.encInfo.ltk[0], 16);
                memcpy(p_devInfo->remoteIrk, (uint8_t *)(&p_key->remote.idInfo.irk[0]), 16);
            }

            p_devInfo->encryptKeySize=p_key->local.encInfo.ltkLen;

            p_devInfo->auth=p_key->local.encInfo.auth;
            p_devInfo->lesc=p_key->local.encInfo.lesc;

            BLE_DM_DdsSetPairedDevice(devId, p_devInfo);

            OSAL_Free(p_devInfo);

            {
                 BLE_DM_Event_T  dmEvt;
                 dmEvt.eventId = BLE_DM_EVT_PAIRED_DEVICE_UPDATED;
                 dmEvt.connHandle = p_conn->connHandle;
                 BLE_DM_ConveyEvent(&dmEvt);
            }
        }
        break;

        default:
        break;

    }
}

void BLE_DM_Sm(STACK_Event_T *p_stackEvent)
{
    if (p_stackEvent->groupId == STACK_GRP_BLE_SMP)
    {
        ble_dm_SecurityManager((BLE_SMP_Event_T *)p_stackEvent->p_event);
    }
    else if (p_stackEvent->groupId == STACK_GRP_BLE_GAP)
    {
        BLE_GAP_Event_T *p_evt = (BLE_GAP_Event_T *) p_stackEvent->p_event;

        if ( p_evt->eventId == BLE_GAP_EVT_ENC_INFO_REQUEST)
        {
            BLE_DM_InfoConn_T *p_conn;

            p_conn = BLE_DM_InfoGetConnByHandle(p_evt->eventField.evtEncInfoReq.connHandle);
            if (p_conn == NULL)
                return;

            ble_dm_SmConveyStartEvt(p_conn->connHandle, DM_SECURITY_PROC_ENCRYPTION);

            if (p_conn->encryptKeyValid == false)
            {
                BLE_DM_PairedDevInfo_T bonding;
                
                if (BLE_DM_DdsGetPairedDevice(p_conn->devId, &bonding) == MBA_RES_SUCCESS)
                {
                    if (MBA_RES_SUCCESS != BLE_GAP_EncInfoReqReply(p_conn->connHandle, bonding.ltk))
                        ble_dm_SmConveyFailEvt(p_evt->eventField.evtEncryptStatus.connHandle, DM_SECURITY_PROC_ENCRYPTION
                        , 0x00, 0x00);
                }
                else
                {
                    BLE_GAP_EncInfoReqNegativeReply(p_conn->connHandle);

                    ble_dm_SmConveyFailEvt(p_evt->eventField.evtEncryptStatus.connHandle, DM_SECURITY_PROC_ENCRYPTION
                    , 0x00, 0x00);
                }
            }
            else 
            {
                if (MBA_RES_SUCCESS != BLE_GAP_EncInfoReqReply(p_conn->connHandle, p_conn->encryptKey))
                    ble_dm_SmConveyFailEvt(p_evt->eventField.evtEncryptStatus.connHandle, DM_SECURITY_PROC_ENCRYPTION
                    , 0x00, 0x00);
            }
        }
        else if (p_evt->eventId == BLE_GAP_EVT_ENCRYPT_STATUS)
        {
            if (p_evt->eventField.evtEncryptStatus.status == BLE_GAP_ENCRYPT_SUCCESS)
            {
                ble_dm_SmConveySuccessEvt(p_evt->eventField.evtEncryptStatus.connHandle, DM_SECURITY_PROC_ENCRYPTION, 0x00);
            }
            else
            {
                ble_dm_SmConveyFailEvt(p_evt->eventField.evtEncryptStatus.connHandle, DM_SECURITY_PROC_ENCRYPTION
                    , 0x00, 0x00);
            }
        }
    }
}

uint16_t BLE_DM_SmConfig(bool autoAccept)
{
    s_autoAccept = autoAccept;
    return MBA_RES_SUCCESS;
}

uint16_t BLE_DM_SmPairing(uint16_t connHandle, uint8_t repairing)
{
    BLE_DM_InfoConn_T   *p_conn;
    uint16_t            result;

    p_conn = BLE_DM_InfoGetConnByHandle(connHandle);

    if (p_conn == NULL)
        return MBA_RES_INVALID_PARA;

    if (p_conn->role == BLE_GAP_ROLE_CENTRAL)
    {
        BLE_DM_PairedDevInfo_T bonding;
        if (!repairing && BLE_DM_DdsGetPairedDevice(p_conn->devId, &bonding) == MBA_RES_SUCCESS)
        {
            result = BLE_GAP_EnableEncryption(connHandle, bonding.rv, bonding.ediv, bonding.ltk);

            if (result == MBA_RES_SUCCESS)
                ble_dm_SmConveyStartEvt(connHandle, DM_SECURITY_PROC_ENCRYPTION);
        }
        else
        {
            result = BLE_SMP_InitiatePairing(connHandle);

            if (result == MBA_RES_SUCCESS)
                ble_dm_SmConveyStartEvt(connHandle, DM_SECURITY_PROC_PAIRING);
        }

        return result;
    }
    else
    {
        return BLE_SMP_InitiatePairing(connHandle);
    }
}

void BLE_DM_SmInit()
{
    s_autoAccept = true;
}
