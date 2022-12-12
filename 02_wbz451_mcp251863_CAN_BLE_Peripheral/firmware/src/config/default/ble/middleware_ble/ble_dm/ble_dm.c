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
  BLE Device Manager Middleware Source File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_dm.c

  Summary:
    This file contains the BLE Device Manager functions and event for application user.

  Description:
    This file contains the BLE Device Manager functions and event for application user.
    The "BLE_DM_Init" function shall be called in the "APP_Initialize" function to 
    initialize the this modules in the system.
 *******************************************************************************/


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "ble_dm/ble_dm.h"
#include "ble_dm/ble_dm_sm.h"
#include "ble_dm/ble_dm_info.h"
#include "ble_dm/ble_dm_dds.h"
#include "ble_dm/ble_dm_conn.h"

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

BLE_DM_EventCb_T        s_dmEventCb[BLE_DM_MAX_REGISTER_NUM];
uint8_t                 s_dmCbNum;

// *****************************************************************************
// *****************************************************************************
// Section: Functions
// *****************************************************************************
// *****************************************************************************
void BLE_DM_ConveyEvent(BLE_DM_Event_T *p_event)
{
    uint8_t             i;
    BLE_DM_InfoConn_T   *p_conn;

    p_conn = BLE_DM_InfoGetConnByHandle(p_event->connHandle);

    if (p_conn)
        p_event->peerDevId = p_conn->devId;
    else
        p_event->peerDevId = BLE_DM_PEER_DEV_ID_INVALID;

    for(i=0;i<s_dmCbNum; i++)
    {
        if(s_dmEventCb[i])
        {
            s_dmEventCb[i](p_event);
        }
    }
}

void BLE_DM_Init()
{
    BLE_DM_SmInit();
    BLE_DM_InfoInit();
    BLE_DM_ConnInit();
}

uint16_t BLE_DM_EventRegister(BLE_DM_EventCb_T eventCb)
{
    if(s_dmCbNum>=BLE_DM_MAX_REGISTER_NUM)
        return MBA_RES_NO_RESOURCE;

    s_dmEventCb[s_dmCbNum]=eventCb;
    s_dmCbNum++;

    return MBA_RES_SUCCESS;
}



void BLE_DM_BleEventHandler(STACK_Event_T *p_stackEvent)
{
    BLE_DM_Info(p_stackEvent);
    BLE_DM_Sm(p_stackEvent);
    BLE_DM_Conn(p_stackEvent);
}

uint16_t BLE_DM_Config(BLE_DM_Config_T *p_config)
{
    uint16_t result;
    result = BLE_DM_SmConfig(p_config->secAutoAccept);

    if (result != MBA_RES_SUCCESS)
        return result;
    else
        return BLE_DM_ConnConfig(&p_config->connConfig);
}

uint16_t BLE_DM_ProceedSecurity(uint16_t connHandle, uint8_t repairing)
{
    return BLE_DM_SmPairing(connHandle, repairing);
}

uint16_t BLE_DM_SetFilterAcceptList(uint8_t devCnt, uint8_t const * p_devId)
{
    return BLE_DM_InfoSetFilterAcceptList(devCnt, p_devId);
}

uint16_t BLE_DM_GetFilterAcceptList(uint8_t *p_devCnt, BLE_GAP_Addr_T *p_addr)
{
    return BLE_DM_InfoGetFilterAcceptList(p_devCnt, p_addr);
}

uint16_t BLE_DM_SetResolvingList(uint8_t devCnt, uint8_t const *p_devId, uint8_t const *p_privacyMode)
{
    return BLE_DM_InfoSetResolvingList(devCnt, p_devId, p_privacyMode);
}

uint16_t BLE_DM_DeletePairedDevice(uint8_t devId)
{
    return BLE_DM_DdsDeletePairedDevice(devId);
}

uint16_t BLE_DM_GetPairedDevice(uint8_t devId, BLE_DM_PairedDevInfo_T *p_pairedDevInfo)
{
    return BLE_DM_DdsGetPairedDevice(devId, p_pairedDevInfo);
}

uint16_t BLE_DM_DeleteAllPairedDevice()
{
    return BLE_DM_DdsDeleteAllPairedDevice();
}

void BLE_DM_GetPairedDeviceList(uint8_t *p_devId, uint8_t *p_devCnt)
{
    uint8_t devId;

    *p_devCnt = 0;

    for (devId = 0; devId < BLE_DM_MAX_PAIRED_DEVICE_NUM; devId++)
    {
        if (BLE_DM_DdsChkDeviceId(devId))
        {
            p_devId[*p_devCnt] = devId;
            (*p_devCnt)++;
        }
    }
}