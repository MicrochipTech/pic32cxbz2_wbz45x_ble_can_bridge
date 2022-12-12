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
  BLE Connection Middleware Source File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_dm_conn.c

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
#include "ble_dm/ble_dm_conn.h"
#include "ble_dm/ble_dm_info.h"
#include "ble_dm/ble_dm_internal.h"

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

typedef struct BLE_DM_ConnUpdateDb_T
{
    uint16_t                    connHandle;                 /**< The connection handle. */
    bool                        isProcedureInitiator;       /**< Record the update procedure is initiated by this module or remote */
} BLE_DM_ConnUpdateDb_T;

typedef struct BLE_DM_ConnCtrl_T
{
    BLE_DM_ConnUpdateDb_T       updateDb[BLE_GAP_MAX_LINK_NBR];         /**< Connection update instances for each link. */
    BLE_DM_ConnConfig_T         userConnConfig;
    bool                        autoReplyUpdate;                        /**< Automatically accept connection parameter update request from peer. */
} BLE_DM_ConnCtrl_T;

// *****************************************************************************
// *****************************************************************************
// Section: Local Variables
// *****************************************************************************
// *****************************************************************************

BLE_DM_ConnCtrl_T               s_dmConnCtrl;

// *****************************************************************************
// *****************************************************************************
// Section: Functions
// *****************************************************************************
// *****************************************************************************

static void ble_dm_ConnInitUpdateDb(BLE_DM_ConnUpdateDb_T *p_conn)
{
    memset((uint8_t *)p_conn, 0, sizeof(BLE_DM_ConnUpdateDb_T));
}

static BLE_DM_ConnUpdateDb_T *ble_dm_ConnFindConnByHandle(uint16_t connHandle)
{
    uint8_t i;

    for (i=0; i<BLE_GAP_MAX_LINK_NBR; i++)
    {
        if (s_dmConnCtrl.updateDb[i].connHandle == connHandle)
        {
            return &s_dmConnCtrl.updateDb[i];
        }
    }
    return NULL;
}

void BLE_DM_ConnInit()
{
    uint8_t i;

    for (i=0; i<BLE_GAP_MAX_LINK_NBR; i++)
    {
        ble_dm_ConnInitUpdateDb(&s_dmConnCtrl.updateDb[i]);
    }
}

static void ble_dm_ConnProcGapConnected(BLE_GAP_Event_T *p_event)
{
    if ((p_event->eventField.evtConnect.status == GAP_STATUS_SUCCESS))
    {
        BLE_DM_ConnUpdateDb_T *p_conn;
    
        /* Find free connection instance */
        p_conn = ble_dm_ConnFindConnByHandle(0);

        if (p_conn != NULL)
        {
            p_conn->connHandle = p_event->eventField.evtConnect.connHandle;
        }
    }
}

static void ble_dm_ConnProcGapDisconnected(BLE_GAP_Event_T *p_event)
{
    BLE_DM_ConnUpdateDb_T *p_conn;

    p_conn = ble_dm_ConnFindConnByHandle(p_event->eventField.evtDisconnect.connHandle);

    if (p_conn != NULL)
    {
        ble_dm_ConnInitUpdateDb(p_conn);
    }
}

static void ble_dm_ConnProcGapConnParamUpdate(BLE_GAP_Event_T *p_event)
{
    BLE_DM_ConnUpdateDb_T *p_conn;

    p_conn = ble_dm_ConnFindConnByHandle(p_event->eventField.evtConnParamUpdate.connHandle);

    if (p_conn != NULL)
    {
        if (p_conn->isProcedureInitiator)
        {
            BLE_DM_Event_T  dmEvt;

            if (p_event->eventField.evtConnParamUpdate.status == 0)
            {
                dmEvt.eventId = BLE_DM_EVT_CONN_UPDATE_SUCCESS;
            }
            else
            {
                dmEvt.eventId = BLE_DM_EVT_CONN_UPDATE_FAIL;
            }

            dmEvt.connHandle = p_event->eventField.evtConnParamUpdate.connHandle;
            BLE_DM_ConveyEvent(&dmEvt);
            p_conn->isProcedureInitiator = false;
        }
    }
}

static bool ble_dm_ConnCheckRemoteUpdateParams(uint16_t minInterval, uint16_t maxInterval, uint16_t latency, uint16_t timeout)
{
    uint16_t minRequireTimeout;

    /* Check if value in Spec. suggested range. */
    if ((minInterval<BLE_GAP_CP_MIN_CONN_INTVAL_MIN) || (minInterval>BLE_GAP_CP_MIN_CONN_INTVAL_MAX) ||
        (maxInterval<BLE_GAP_CP_MAX_CONN_INTVAL_MIN) || (maxInterval>BLE_GAP_CP_MAX_CONN_INTVAL_MAX) ||
        (latency<BLE_GAP_CP_LATENCY_MIN) || (latency>BLE_GAP_CP_LATENCY_MAX) ||
        (timeout<BLE_GAP_CP_CONN_SUPERVISION_TIMEOUT_MIN) || (timeout>BLE_GAP_CP_CONN_SUPERVISION_TIMEOUT_MAX) ||
        (minInterval>maxInterval))
    {
        return false;
    }

    /* Check if parameters cause timeout */
    minRequireTimeout = (maxInterval*(1+latency))*2;    // Uint: 1.25 ms
    if ((timeout*8) < minRequireTimeout)                // Compare with uint: 1.25 ms
    {
        return false;
    }

    /* Check if parameters are in user preferred range */
    if ((s_dmConnCtrl.userConnConfig.maxAcceptConnInterval < minInterval) || (s_dmConnCtrl.userConnConfig.minAcceptConnInterval > maxInterval) ||
        (s_dmConnCtrl.userConnConfig.maxAcceptPeripheralLatency < latency) || (s_dmConnCtrl.userConnConfig.minAcceptPeripheralLatency > latency))
    {
        return false;
    }

    return true;
}

static void ble_dm_ConnProcGapRemoteConnUpdateReq(BLE_GAP_Event_T *p_event)
{
    BLE_GAP_ConnParams_T    connParams;
    bool                    paramsValid;

    if (s_dmConnCtrl.autoReplyUpdate)
    {
        paramsValid = ble_dm_ConnCheckRemoteUpdateParams(p_event->eventField.evtRemoteConnParamReq.intervalMin, p_event->eventField.evtRemoteConnParamReq.intervalMax,
                                                         p_event->eventField.evtRemoteConnParamReq.latency, p_event->eventField.evtRemoteConnParamReq.timeout);

        if (paramsValid)
        {
            connParams.intervalMin = p_event->eventField.evtRemoteConnParamReq.intervalMin;
            connParams.intervalMax = p_event->eventField.evtRemoteConnParamReq.intervalMax;
            connParams.latency = p_event->eventField.evtRemoteConnParamReq.latency;
            connParams.supervisionTimeout = p_event->eventField.evtRemoteConnParamReq.timeout;
            BLE_GAP_RemoteConnParamsReqReply(p_event->eventField.evtRemoteConnParamReq.connHandle, &connParams);
        }
        else
        {
            BLE_GAP_RemoteConnParamsReqNegativeReply(p_event->eventField.evtRemoteConnParamReq.connHandle, GAP_STATUS_UNACCEPTABLE_CONNECTION_PARAMETERS);
        }
    }
}

static void ble_dm_ConnStackEvtBleGapHandler(BLE_GAP_Event_T *p_event)
{
    switch (p_event->eventId)
    {
        case BLE_GAP_EVT_CONNECTED:
        {
            ble_dm_ConnProcGapConnected(p_event);
        }
        break;

        case BLE_GAP_EVT_DISCONNECTED:
        {
            ble_dm_ConnProcGapDisconnected(p_event);
        }
        break;

        case BLE_GAP_EVT_CONN_PARAM_UPDATE:
        {
            ble_dm_ConnProcGapConnParamUpdate(p_event);
        }
        break;

        case BLE_GAP_EVT_REMOTE_CONN_PARAM_REQUEST:
        {
            ble_dm_ConnProcGapRemoteConnUpdateReq(p_event);
        }
        break;

        default:
        break;
    }
}

static void ble_dm_ConnProcL2capConnParamUpdateReq(BLE_L2CAP_Event_T *p_event)
{
    BLE_DM_ConnUpdateDb_T *p_conn;

    p_conn = ble_dm_ConnFindConnByHandle(p_event->eventField.evtConnParamUpdateReq.connHandle);

    if (p_conn != NULL)
    {
        bool paramsValid;

        if (s_dmConnCtrl.autoReplyUpdate)
        {
            paramsValid = ble_dm_ConnCheckRemoteUpdateParams(p_event->eventField.evtConnParamUpdateReq.intervalMin, p_event->eventField.evtConnParamUpdateReq.intervalMax,
                                                             p_event->eventField.evtConnParamUpdateReq.latency, p_event->eventField.evtConnParamUpdateReq.timeout);
            if (paramsValid)
            {
                /* Accept request. Send L2CAP response and send LL conn. update request. */
                BLE_GAP_ConnParams_T paras;

                BLE_L2CAP_ConnParamUpdateRsp(p_event->eventField.evtConnParamUpdateReq.connHandle, BLE_L2CAP_CONN_PARAMS_ACCEPT);

                paras.intervalMin = p_event->eventField.evtConnParamUpdateReq.intervalMin;
                paras.intervalMax = p_event->eventField.evtConnParamUpdateReq.intervalMax;
                paras.latency = p_event->eventField.evtConnParamUpdateReq.latency;
                paras.supervisionTimeout = p_event->eventField.evtConnParamUpdateReq.timeout;
                BLE_GAP_UpdateConnParam(p_event->eventField.evtConnParamUpdateReq.connHandle, &paras);
            }
            else
            {
                /* Reject request. Send L2CAP response. */
                BLE_L2CAP_ConnParamUpdateRsp(p_event->eventField.evtConnParamUpdateReq.connHandle, BLE_L2CAP_CONN_PARAMS_REJECT);
            }
        }
    }
}

static void ble_dm_ConnProcL2capConnParamUpdateResp(BLE_L2CAP_Event_T *p_event)
{
    BLE_DM_ConnUpdateDb_T *p_conn;

    p_conn = ble_dm_ConnFindConnByHandle(p_event->eventField.evtConnParamUpdateRsp.connHandle);

    if (p_conn != NULL)
    {
        if ((p_event->eventField.evtConnParamUpdateRsp.result != MBA_RES_SUCCESS) && (p_conn->isProcedureInitiator))
        {
            BLE_DM_Event_T  dmEvt;

            dmEvt.eventId = BLE_DM_EVT_CONN_UPDATE_FAIL;
            dmEvt.connHandle = p_event->eventField.evtConnParamUpdateRsp.connHandle;
            BLE_DM_ConveyEvent(&dmEvt);
            p_conn->isProcedureInitiator = false;
        }
    }
}

static void ble_dm_ConnStackEvtBleL2capHandler(BLE_L2CAP_Event_T *p_event)
{
    switch (p_event->eventId)
    {
        case BLE_L2CAP_EVT_CONN_PARA_UPDATE_REQ:
        {
            ble_dm_ConnProcL2capConnParamUpdateReq(p_event);
        }
        break;

        case BLE_L2CAP_EVT_CONN_PARA_UPDATE_RSP:
        {
            ble_dm_ConnProcL2capConnParamUpdateResp(p_event);
        }
        break;

        default:
        break;
    }
}

void BLE_DM_Conn(STACK_Event_T *p_stackEvent)
{
    switch (p_stackEvent->groupId)
    {
        case STACK_GRP_BLE_GAP:
        {
            ble_dm_ConnStackEvtBleGapHandler((BLE_GAP_Event_T *)p_stackEvent->p_event);
        }
        break;

        case STACK_GRP_BLE_L2CAP:
        {
            ble_dm_ConnStackEvtBleL2capHandler((BLE_L2CAP_Event_T *)p_stackEvent->p_event);
        }
        break;

        default:
        break;
    }
}

uint16_t BLE_DM_ConnConfig(BLE_DM_ConnConfig_T *p_config)
{
    if (p_config->autoReplyUpdateRequest)
    {
        if ((p_config->maxAcceptConnInterval < p_config->minAcceptConnInterval) ||
            (p_config->maxAcceptPeripheralLatency < p_config->minAcceptPeripheralLatency) ||
            (p_config->minAcceptConnInterval < BLE_GAP_CP_MIN_CONN_INTVAL_MIN) ||
            (p_config->maxAcceptConnInterval > BLE_GAP_CP_MAX_CONN_INTVAL_MAX) ||
            (p_config->maxAcceptPeripheralLatency > BLE_GAP_CP_LATENCY_MAX))
        {
            s_dmConnCtrl.autoReplyUpdate = false;
            return MBA_RES_INVALID_PARA;
        }
        else
        {
            s_dmConnCtrl.autoReplyUpdate = true;
            s_dmConnCtrl.userConnConfig.minAcceptConnInterval = p_config->minAcceptConnInterval;
            s_dmConnCtrl.userConnConfig.maxAcceptConnInterval = p_config->maxAcceptConnInterval;
            s_dmConnCtrl.userConnConfig.minAcceptPeripheralLatency = p_config->minAcceptPeripheralLatency;
            s_dmConnCtrl.userConnConfig.maxAcceptPeripheralLatency = p_config->maxAcceptPeripheralLatency;
            s_dmConnCtrl.userConnConfig.autoReplyUpdateRequest = p_config->autoReplyUpdateRequest;
            return MBA_RES_SUCCESS;
        }
    }
    else
    {
        s_dmConnCtrl.autoReplyUpdate = false;
        return MBA_RES_SUCCESS;
    }
}

uint16_t BLE_DM_ConnectionParameterUpdate(uint16_t connHandle, BLE_DM_ConnParamUpdate_T *p_params)
{
    BLE_DM_ConnUpdateDb_T *p_conn;
    BLE_DM_InfoConn_T *p_infoConn;
    uint16_t error;

    p_conn = ble_dm_ConnFindConnByHandle(connHandle);
    p_infoConn = BLE_DM_InfoGetConnByHandle(connHandle);

    if ((p_conn != NULL) && (p_infoConn != NULL))
    {
        BLE_GAP_ConnParams_T connParams;

        connParams.intervalMin = p_params->intervalMin;
        connParams.intervalMax = p_params->intervalMax;
        connParams.latency = p_params->latency;
        connParams.supervisionTimeout = p_params->timeout;
        /* minCeLength/maxCeLength is controlled by controller */
        error = BLE_GAP_UpdateConnParam(connHandle, &connParams);

        if ((error == MBA_RES_UNSUPPORT_REMOTE_FEATURE) && (p_infoConn->role == BLE_GAP_ROLE_PERIPHERAL))
        {
            error = BLE_L2CAP_ConnParamUpdateReq(connHandle, p_params->intervalMin, p_params->intervalMax, p_params->latency, p_params->timeout);
        }

        if (error == MBA_RES_SUCCESS)
        {
            p_conn->isProcedureInitiator = true;
        }
    }
    else
    {
        error = MBA_RES_INVALID_PARA;
    }
    return error;
}

