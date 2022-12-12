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
    ble_dm_info.c

  Summary:
    This file contains the Device Information functions for 
    BLE Device Manager module internal use.

  Description:
    This file contains the Device Information functions for 
    BLE Device Manager module internal use.
 *******************************************************************************/


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <string.h>
#include "osal/osal_freertos_extend.h"
#include "mba_error_defs.h"
#include "ble_gap.h"
#include "ble_dm/ble_dm_internal.h"
#include "ble_dm/ble_dm_info.h"
#include "ble_dm/ble_dm_dds.h"


// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************
typedef enum BLE_DM_InfoState_T
{
    BLE_DM_INFO_STATE_IDLE = 0x00,
    BLE_DM_INFO_STATE_CONNECTED
}BLE_DM_InfoState_T;





/**************************************************************************************************
  Variables
**************************************************************************************************/
BLE_DM_InfoConn_T       s_dmInfoRole[BLE_GAP_MAX_LINK_NBR];

static uint8_t          s_dmInfoFilterAcceptListCnt;
static uint8_t          s_dmInfoFilterAcceptList[BLE_DM_MAX_FILTER_ACCEPT_LIST_NUM];


/**************************************************************************************************
  Function
**************************************************************************************************/

static BLE_DM_InfoConn_T *ble_dm_InfoGetFreeConn(void)
{
    uint8_t i;

    for (i = 0; i < BLE_GAP_MAX_LINK_NBR; i++)
    {
        if (s_dmInfoRole[i].state == BLE_DM_INFO_STATE_IDLE)
        {
            memset((uint8_t *)&s_dmInfoRole[i], 0, sizeof(BLE_DM_InfoConn_T));
            return &s_dmInfoRole[i];
        }
    }
    return NULL;
}

BLE_DM_InfoConn_T *BLE_DM_InfoGetConnByHandle(uint16_t connHandle)
{
    uint8_t i;

    for (i = 0; i < BLE_GAP_MAX_LINK_NBR; i++)
    {
        if (s_dmInfoRole[i].connHandle == connHandle)
        {
            return &s_dmInfoRole[i];
        }
    }
    return NULL;
}


void BLE_DM_InfoInit()
{
    memset(s_dmInfoRole, 0x00, sizeof(s_dmInfoRole));
    s_dmInfoFilterAcceptListCnt = 0;
}

void BLE_DM_Info(STACK_Event_T *p_stackEvent)
{
    switch (p_stackEvent->groupId)
    {
        case STACK_GRP_BLE_GAP:
        {
            BLE_GAP_Event_T     *p_gapEvt = (BLE_GAP_Event_T *)p_stackEvent->p_event;
            BLE_DM_InfoConn_T   *p_conn;

            if (p_gapEvt->eventId == BLE_GAP_EVT_CONNECTED)
            {
                if ((p_gapEvt->eventField.evtConnect.status == GAP_STATUS_SUCCESS))
                {
                    BLE_DM_Event_T          dmEvt;

                    p_conn = ble_dm_InfoGetFreeConn();
                    if (p_conn)
                    {
                        p_conn->connHandle = p_gapEvt->eventField.evtConnect.connHandle;
                        p_conn->role = p_gapEvt->eventField.evtConnect.role;
                        p_conn->remoteAddr = p_gapEvt->eventField.evtConnect.remoteAddr;
                        p_conn->state = BLE_DM_INFO_STATE_CONNECTED;
                        p_conn->devId = BLE_DM_DdsGetDeviceId(&p_conn->remoteAddr);

                        if (p_conn->devId != BLE_DM_PEER_DEV_ID_INVALID)
                        {
                            BLE_DM_PairedDevInfo_T  devInfo;
                            BLE_SMP_PairInfo_T      pairInfo;

                            BLE_DM_DdsGetPairedDevice(p_conn->devId, &devInfo);
                            pairInfo.lesc=devInfo.lesc;
                            pairInfo.auth=devInfo.auth;
                            BLE_SMP_UpdateBondingInfo(p_conn->connHandle, devInfo.encryptKeySize, &pairInfo);
                        }

                        dmEvt.connHandle=p_gapEvt->eventField.evtConnect.connHandle;
                        dmEvt.eventId=BLE_DM_EVT_CONNECTED;                    
                        BLE_DM_ConveyEvent(&dmEvt);
                   }
                }
            }
            else if (p_gapEvt->eventId == BLE_GAP_EVT_DISCONNECTED)
            {
                BLE_DM_Event_T          dmEvt;
                uint8_t i;

                dmEvt.eventId=BLE_DM_EVT_DISCONNECTED;
                dmEvt.connHandle=p_gapEvt->eventField.evtDisconnect.connHandle;
                
                
                p_conn = BLE_DM_InfoGetConnByHandle(p_gapEvt->eventField.evtDisconnect.connHandle);
                if (p_conn)
                {
                    dmEvt.peerDevId = p_conn->devId;
                    memset(p_conn, 0x00, sizeof(BLE_DM_InfoConn_T));
                }
                else
                    dmEvt.peerDevId = BLE_DM_PEER_DEV_ID_INVALID;

                for(i=0;i<s_dmCbNum; i++)
                {
                    if(s_dmEventCb[i])
                    {
                        s_dmEventCb[i](&dmEvt);
                    }
                }
            }
        }
        break;

        default:
        break;
    }
}

uint16_t BLE_DM_InfoSetFilterAcceptList(uint8_t devCnt, uint8_t const * p_devId)
{
    uint16_t result;
    uint8_t i;

    if (p_devId == NULL || devCnt == 0)
    {
        result = BLE_GAP_SetFilterAcceptList(0, NULL);
        if (result == MBA_RES_SUCCESS)
        {
            s_dmInfoFilterAcceptListCnt = 0;
        }

        return result;
    }

    if (devCnt > BLE_DM_MAX_FILTER_ACCEPT_LIST_NUM)
        return MBA_RES_INVALID_PARA;

    BLE_GAP_Addr_T addr[BLE_DM_MAX_FILTER_ACCEPT_LIST_NUM];


    /* Get address by peer id */
    for (i = 0; i < devCnt; i++)
    {
        BLE_DM_PairedDevInfo_T pairedInfo;

        if ((result = BLE_DM_DdsGetPairedDevice(p_devId[i], &pairedInfo)) != MBA_RES_SUCCESS)
            return result;

        if (pairedInfo.remoteAddr.addrType != BLE_GAP_ADDR_TYPE_PUBLIC 
            && pairedInfo.remoteAddr.addrType != BLE_GAP_ADDR_TYPE_RANDOM_STATIC)
            return MBA_RES_INVALID_PARA;

        addr[i] = pairedInfo.remoteAddr;
    }

    result = BLE_GAP_SetFilterAcceptList(devCnt,addr);

    /* copy the devices added successfully to s_imFilterAcceptList */
    memcpy(s_dmInfoFilterAcceptList, p_devId, sizeof(uint8_t) * i);
    s_dmInfoFilterAcceptListCnt = i;


    return result;
}


uint16_t BLE_DM_InfoGetFilterAcceptList(uint8_t *p_devCnt, BLE_GAP_Addr_T *p_addr)
{
    BLE_DM_PairedDevInfo_T pairedInfo;

    for (uint8_t i = 0; i < s_dmInfoFilterAcceptListCnt; i++)
    {
        if (MBA_RES_SUCCESS != BLE_DM_DdsGetPairedDevice(s_dmInfoFilterAcceptList[i], &pairedInfo))
            return MBA_RES_FAIL;

        p_addr[i] = pairedInfo.remoteAddr;
    }

    *p_devCnt = s_dmInfoFilterAcceptListCnt;

    return MBA_RES_SUCCESS;
}

uint16_t BLE_DM_InfoSetResolvingList(uint8_t devCnt, uint8_t const *p_devId, uint8_t const *p_privacyMode)
{
    uint16_t                        result;
    uint8_t                         i;
    BLE_GAP_ResolvingListParams_T   *p_resolvingList;
    BLE_GAP_LocalPrivacyParams_T    privacy;
    bool                            enable;

    result = MBA_RES_SUCCESS;

    if (p_devId == NULL || devCnt == 0 || p_privacyMode == NULL)
    {
        result = BLE_GAP_SetResolvingList(0, NULL);
        return result;
    }

    if (devCnt > BLE_DM_MAX_RESOLVING_LIST_NUM)
        return MBA_RES_INVALID_PARA;

    BLE_GAP_GetLocalPrivacy(&enable, &privacy);

    p_resolvingList = OSAL_Malloc(sizeof(BLE_GAP_ResolvingListParams_T) * devCnt);
    if (p_resolvingList == NULL)
        return MBA_RES_OOM;

    /* Get address by peer id */
    for (i = 0; i < devCnt; i++)
    {
        BLE_DM_PairedDevInfo_T pairedInfo;

        if ((result = BLE_DM_DdsGetPairedDevice(p_devId[i], &pairedInfo)) != MBA_RES_SUCCESS)
            break;

        if ((pairedInfo.remoteAddr.addrType != BLE_GAP_ADDR_TYPE_PUBLIC 
            && pairedInfo.remoteAddr.addrType != BLE_GAP_ADDR_TYPE_RANDOM_STATIC)
            || (p_privacyMode[i] > BLE_GAP_PRIVACY_MODE_DEVICE))
        {
            result = MBA_RES_INVALID_PARA;
            break;
        }

        memcpy(p_resolvingList[i].localIrk, privacy.localIrk, 16);
        memcpy(p_resolvingList[i].peerIrk, pairedInfo.remoteIrk, 16);
        p_resolvingList[i].peerIdAddr = pairedInfo.remoteAddr;
        p_resolvingList[i].privacyMode = p_privacyMode[i];
    }

    if (result == MBA_RES_SUCCESS)
        result = BLE_GAP_SetResolvingList(devCnt,p_resolvingList);

    OSAL_Free(p_resolvingList);

    return result;
}

