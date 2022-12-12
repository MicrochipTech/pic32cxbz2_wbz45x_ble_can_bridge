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
  BLE Database Discovery Middleware Source File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_dd.c

  Summary:
    This file contains the BLE Database Discovery functions and event for application user.

  Description:
    This file contains the BLE Database Discovery functions and event for application user.
    The "BLE_DD_Init" function shall be called in the "APP_Initialize" function to 
    initialize the this modules in the system.
 *******************************************************************************/


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <string.h>
#include "osal/osal_freertos_extend.h"
#include "mba_error_defs.h"
#include "gatt.h"
#include "ble_util/byte_stream.h"
#include "ble_gcm/ble_dd.h"


// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************

#define DISC_CHAR_UUID2_RSP_LENGTH                  0x07    /**< Length of handle-value pair of Characteristic Declaration with UUID length is 2 bytes. */
#define DISC_CHAR_UUID16_RSP_LENGTH                 0x15    /**< Length of handle-value pair of Characteristic Declaration with UUID length is 16 bytes. */

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/**@brief The structure of service discovery buffer. */
typedef struct BLE_DD_DiscInstance_T
{
    uint16_t                svcStartHandle;                     /**< Internal used. Service start handle. */
    uint16_t                svcEndHandle;                       /**< Internal used. Service end handle. */
    uint8_t                 isSvcFound;                         /**< Internal used. Service is found or not in primary service discovery step. */
    uint8_t                 queuedReqByProtocol;                /**< Internal used. Queued request if ATT protocol is busy. */
    uint8_t                 queuedReqBySecurity;                /**< Internal used. Queued request if ATT is blocked by security. */
} BLE_DD_DiscInstance_T;

/**@brief The structure of connection instance of database discovery module. */
typedef struct BLE_DD_Conn_T
{
    BLE_DD_DiscInstance_T   *p_discInstance;                    /**< Pointer to the discovery buffer. */
    BLE_DD_CharInfo_T       *p_charInfoList;                    /**< Pointer to characteristic information list for the discovering service. */
    uint16_t                connHandle;                         /**< Connection handle. */
    uint8_t                 connIndex;                          /**< The index of this connection in connection database array */
    uint8_t                 gapRole;                            /**< GAP role of the connection. */
    uint8_t                 discSvcIndex;                       /**< The index of service that the discovery is ongoing. */
    bool                    isDiscovering;                      /**< Internal used. Record if discovery is ongoing. */
    bool                    disableDiscovery;                   /**< Disable discovery of the connection. Application caches characteristic handles and no need to discover again. */
} BLE_DD_Conn_T;

/**@brief The database of database discovery module. */
typedef struct BLE_DD_Ctrl_T
{
    BLE_DD_Conn_T           conn[BLE_GAP_MAX_LINK_NBR];         /**< Connection database for database discovery module. */
    BLE_DD_DiscSvc_T        services[BLE_DD_MAX_DISC_SVC_NUM];  /**< Service information registered by profile/application to be discovered. */
    uint8_t                 numOfService;                       /**< Number of registered service. Maximum @ref BLE_DD_MAX_DISC_SVC_NUM */
} BLE_DD_Ctrl_T;

// *****************************************************************************
// *****************************************************************************
// Section: Local Variables
// *****************************************************************************
// *****************************************************************************
BLE_DD_EventCb_T            s_ddEventCb;            /* Events callback function. */
BLE_DD_Ctrl_T               s_ddCtrl;                 /* DD module database. */

// *****************************************************************************
// *****************************************************************************
// Section: Functions
// *****************************************************************************
// *****************************************************************************
static void ble_dd_InitConn(BLE_DD_Conn_T *p_conn)
{
    if (p_conn->p_discInstance != NULL)
    {
        OSAL_Free(p_conn->p_discInstance);
    }

    memset((uint8_t *)p_conn, 0, sizeof(BLE_DD_Conn_T));
    p_conn->p_discInstance = NULL;
    p_conn->p_charInfoList = NULL;
}

static BLE_DD_Conn_T *ble_dd_FindConnByHandle(uint16_t connHandle)
{
    uint8_t i;

    for (i=0; i<BLE_GAP_MAX_LINK_NBR; i++)
    {
        if (s_ddCtrl.conn[i].connHandle == connHandle)
        {
            s_ddCtrl.conn[i].connIndex = i;
            return &s_ddCtrl.conn[i];
        }
    }
    return NULL;
}

void ble_dd_SendDiscCompleteEvent(BLE_DD_Conn_T *p_conn)
{
    if (s_ddEventCb != NULL)
    {
        BLE_DD_Event_T ddEvent;

        ddEvent.eventId = BLE_DD_EVT_DISC_COMPLETE;
        ddEvent.eventField.evtDiscResult.connHandle = p_conn->connHandle;
        s_ddEventCb(&ddEvent);
    }
}

void ble_dd_ServiceDiscovery(BLE_DD_Conn_T *p_conn)
{
    GATTC_DiscoverPrimaryServiceByUuidParams_T discParams;

    p_conn->p_charInfoList = s_ddCtrl.services[p_conn->discSvcIndex].p_charList[p_conn->connIndex].p_charInfo;
    memset((uint8_t *)p_conn->p_charInfoList, 0, sizeof(BLE_DD_CharInfo_T)*s_ddCtrl.services[p_conn->discSvcIndex].discCharsNum);
    memset((uint8_t *)p_conn->p_discInstance, 0, sizeof(BLE_DD_DiscInstance_T));

    discParams.startHandle = 0x0001;
    discParams.endHandle = 0xFFFF;
    discParams.valueLength = s_ddCtrl.services[p_conn->discSvcIndex].svcUuid.uuidLength;
    memcpy(discParams.value ,s_ddCtrl.services[p_conn->discSvcIndex].svcUuid.uuid, s_ddCtrl.services[p_conn->discSvcIndex].svcUuid.uuidLength);
    if (GATTC_DiscoverPrimaryServiceByUUID(p_conn->connHandle, &discParams) == MBA_RES_BUSY)
    {
        p_conn->p_discInstance->queuedReqByProtocol = ATT_FIND_BY_TYPE_VALUE_REQ;
    }
}

void ble_dd_NextServiceDiscovery(BLE_DD_Conn_T *p_conn)
{
    p_conn->discSvcIndex++;
    if (p_conn->discSvcIndex < s_ddCtrl.numOfService)
    {
        ble_dd_ServiceDiscovery(p_conn);
    }
    else
    {
        p_conn->isDiscovering = false;
        ble_dd_SendDiscCompleteEvent(p_conn);
    }
}

static uint16_t ble_dd_DescriptorDiscovery(BLE_DD_Conn_T *p_conn)
{
    BLE_DD_DiscChar_T   **p_discChar;
    uint16_t            result = MBA_RES_SUCCESS;
    uint8_t             idx;

    p_discChar = s_ddCtrl.services[p_conn->discSvcIndex].p_discChars;

    for (idx=0; idx<s_ddCtrl.services[p_conn->discSvcIndex].discCharsNum; idx++, p_discChar++)
    {
        /* Check if there's descriptor to discover */
        if ((*p_discChar)->settings & CHAR_SET_DESCRIPTOR)
        {
            if (GATTC_DiscoverAllDescriptors(p_conn->connHandle, p_conn->p_discInstance->svcStartHandle , p_conn->p_discInstance->svcEndHandle) == MBA_RES_BUSY)
            {
                p_conn->p_discInstance->queuedReqByProtocol = ATT_FIND_INFORMATION_REQ;
            }
            result = MBA_RES_FAIL;
            break;
        }
    }

    return result;
}

static void ble_dd_ProcCharDiscResp(BLE_DD_Conn_T *p_conn, GATT_Event_T *p_event)
{
    BLE_DD_DiscChar_T   **p_discChar;
    uint16_t            procIdx = 0;
    uint8_t             uuidLength, idx;
    uint8_t             *p_uuid;

    /* ATT has error checking. There should be only these 2 cases. */
    if (p_event->eventField.onDiscCharResp.attrPairLength == DISC_CHAR_UUID16_RSP_LENGTH)
    {
        uuidLength = ATT_UUID_LENGTH_16;
    }
    else
    {
        uuidLength = ATT_UUID_LENGTH_2;
    }

    /* Process each characteristic declaration in response */
    while (procIdx < p_event->eventField.onDiscCharResp.attrDataLength)
    {
        p_uuid = &p_event->eventField.onDiscCharResp.attrData[procIdx+5];

        /* Process each discover characteristic with each characteristic declaration */
        for (idx=0, p_discChar = s_ddCtrl.services[p_conn->discSvcIndex].p_discChars; idx<s_ddCtrl.services[p_conn->discSvcIndex].discCharsNum; idx++, p_discChar++)
        {
            if (((*p_discChar)->settings & CHAR_SET_DESCRIPTOR) == 0)
            {
                if (((*p_discChar)->p_uuid->uuidLength == uuidLength) && (memcmp((*p_discChar)->p_uuid->uuid, p_uuid, uuidLength) == 0))
                {
                    /* Characteristic found, record handle. */
                    BUF_LE_TO_U16(&p_conn->p_charInfoList[idx].charHandle, &p_event->eventField.onDiscCharResp.attrData[procIdx+3]);
                    p_conn->p_charInfoList[idx].property = p_event->eventField.onDiscCharResp.attrData[procIdx+2];
                }
            }
        }
        procIdx += p_event->eventField.onDiscCharResp.attrPairLength;
    }
}

static void ble_dd_ProcDescDiscResp(BLE_DD_Conn_T *p_conn, GATT_Event_T *p_event)
{
    BLE_DD_DiscChar_T   **p_discChar;
    uint16_t            procIdx = 0;
    uint8_t             uuidLength, idx;
    uint8_t             *p_uuid;

    /* GATT has filtering. The format of information data should only be 0x01 (16-bit UUID). */
    uuidLength = ATT_UUID_LENGTH_2;

    /* Process each handle-uuid pair in response */
    while (procIdx < p_event->eventField.onDiscDescResp.infoDataLength)
    {
        p_uuid = &p_event->eventField.onDiscDescResp.infoData[procIdx+2];

        /* Process each discover characteristic with each characteristic declaration */
        for (idx=0, p_discChar = s_ddCtrl.services[p_conn->discSvcIndex].p_discChars; idx<s_ddCtrl.services[p_conn->discSvcIndex].discCharsNum; idx++, p_discChar++)
        {
            if ((((*p_discChar)->settings & CHAR_SET_DESCRIPTOR) != 0) && (p_conn->p_charInfoList[idx].charHandle == 0))
            {
                if (((*p_discChar)->p_uuid->uuidLength == uuidLength) && (memcmp((*p_discChar)->p_uuid->uuid, p_uuid, uuidLength) == 0))
                {
                    /* Characteristic descriptor found, record handle. */
                    BUF_LE_TO_U16(&p_conn->p_charInfoList[idx].charHandle, &p_event->eventField.onDiscDescResp.infoData[procIdx]);
                    break;
                }
            }
        }
        procIdx += (2+uuidLength);
    }
}

void ble_dd_StackEvtBleGapHandler(BLE_DD_Config_T *p_config, BLE_GAP_Event_T *p_event)
{
    switch (p_event->eventId)
    {
        case BLE_GAP_EVT_CONNECTED:
        {
            if ((p_event->eventField.evtConnect.status == GAP_STATUS_SUCCESS))
            {
                BLE_DD_Conn_T   *p_conn;
                uint8_t         i;

                /* Find free connection instance */
                p_conn = ble_dd_FindConnByHandle(0);

                if (p_conn != NULL)
                {
                    BLE_DD_Event_T ddEvent;

                    p_conn->connHandle = p_event->eventField.evtConnect.connHandle;
                    p_conn->discSvcIndex = 0;
                    p_conn->gapRole = p_event->eventField.evtConnect.role;
                    p_conn->p_discInstance = OSAL_Malloc(sizeof(BLE_DD_DiscInstance_T));

                    for (i=0; i<s_ddCtrl.numOfService; i++)
                    {
                        s_ddCtrl.services[i].p_charList[p_conn->connIndex].connHandle = p_event->eventField.evtConnect.connHandle;
                    }

                    if (p_conn->p_discInstance != NULL)
                    {
                        memset((uint8_t *)p_conn->p_discInstance, 0, sizeof(BLE_DD_DiscInstance_T));

                        if (p_config->disableConnectedDisc == 0)
                        {
                            if (((p_config->initDiscInCentral) && (p_conn->gapRole == BLE_GAP_ROLE_CENTRAL)) ||
                                ((p_config->initDiscInPeripheral) && (p_conn->gapRole == BLE_GAP_ROLE_PERIPHERAL)))
                            {
                                if (p_config->waitForSecurity == false)
                                {
                                    p_conn->isDiscovering = true;
                                    ble_dd_ServiceDiscovery(p_conn);
                                }
                            }
                        }
                        else
                        {
                            p_config->disableConnectedDisc = 0;
                            p_conn->disableDiscovery = true;
                        }
                    }

                    ddEvent.eventId = BLE_DD_EVT_CONNECTED;
                    ddEvent.eventField.evtConnect.connHandle = p_conn->connHandle;
                    s_ddEventCb(&ddEvent);                
                }
            }
        }
        break;

        case BLE_GAP_EVT_DISCONNECTED:
        {
            BLE_DD_Conn_T *p_conn;

            /* Find connection instance */
            p_conn = ble_dd_FindConnByHandle(p_event->eventField.evtDisconnect.connHandle);
            if (p_conn != NULL)
            {
                BLE_DD_Event_T ddEvent;

                ble_dd_InitConn(p_conn);
                ddEvent.eventId = BLE_DD_EVT_DISCONNECTED;
                ddEvent.eventField.evtDisconnect.connHandle = p_event->eventField.evtDisconnect.connHandle;
                s_ddEventCb(&ddEvent);
            }
        }
        break;

        case BLE_GAP_EVT_ENCRYPT_STATUS:
        {
            if (p_event->eventField.evtEncryptStatus.status == BLE_GAP_ENCRYPT_SUCCESS)
            {
                BLE_DD_Conn_T *p_conn;

                /* Find connection instance */
                p_conn = ble_dd_FindConnByHandle(p_event->eventField.evtEncryptStatus.connHandle);

                if (p_conn != NULL)
                {
                    if ((p_conn->p_discInstance != NULL) && (p_conn->p_discInstance->queuedReqBySecurity))
                    {
                        if (p_conn->p_discInstance->queuedReqBySecurity == ATT_FIND_BY_TYPE_VALUE_REQ)
                        {
                            ble_dd_ServiceDiscovery(p_conn);
                        }
                        else if (p_conn->p_discInstance->queuedReqBySecurity == ATT_READ_BY_TYPE_REQ)
                        {
                            if (GATTC_DiscoverAllCharacteristics(p_conn->connHandle, p_conn->p_discInstance->svcStartHandle, p_conn->p_discInstance->svcEndHandle) == MBA_RES_BUSY)
                            {
                                p_conn->p_discInstance->queuedReqByProtocol = ATT_READ_BY_TYPE_REQ;
                            }
                        }
                        else if (p_conn->p_discInstance->queuedReqBySecurity == ATT_FIND_INFORMATION_REQ)
                        {
                            if (GATTC_DiscoverAllDescriptors(p_conn->connHandle, p_conn->p_discInstance->svcStartHandle , p_conn->p_discInstance->svcEndHandle) == MBA_RES_BUSY)
                            {
                                p_conn->p_discInstance->queuedReqByProtocol = ATT_FIND_INFORMATION_REQ;
                            }
                        }
                        p_conn->p_discInstance->queuedReqBySecurity = 0;
                    }
                    else
                    {
                        if ((p_config->waitForSecurity == true) && (s_ddCtrl.numOfService > 0) && (p_conn->p_discInstance != NULL) && (p_conn->disableDiscovery == false))
                        {
                            if (((p_config->initDiscInCentral) && (p_conn->gapRole == BLE_GAP_ROLE_CENTRAL)) ||
                                ((p_config->initDiscInPeripheral) && (p_conn->gapRole == BLE_GAP_ROLE_PERIPHERAL)))
                            {
                                p_conn->isDiscovering = true;
                                ble_dd_ServiceDiscovery(p_conn);
                            }
                        }
                    }
                }
            }
        }
        break;

        default:
        break;
    }
}

void ble_dd_StackEvtBleGattcHandler(GATT_Event_T *p_event)
{
    switch (p_event->eventId)
    {
        case GATTC_EVT_ERROR_RESP:
        {
            BLE_DD_Conn_T *p_conn;

            p_conn = ble_dd_FindConnByHandle(p_event->eventField.onError.connHandle);

            if (p_conn != NULL)
            {
                /* Ignore responses when dd is not discovering */
                if (p_conn->isDiscovering == false)
                    return;

                /* Require security permission to access characteristics. Inform application and pause the discovery. */
                if ((p_event->eventField.onError.errCode == ATT_ERRCODE_INSUFFICIENT_ENCRYPTION) || (p_event->eventField.onError.errCode == ATT_ERRCODE_INSUFFICIENT_AUTHENTICATION))
                {
                    p_conn->p_discInstance->queuedReqBySecurity = p_event->eventField.onError.reqOpcode;
                    if (s_ddEventCb != NULL)
                    {
                        BLE_DD_Event_T ddEvent;

                        ddEvent.eventId = BLE_DD_EVT_SEC_REQUIRED;
                        ddEvent.eventField.evtDiscResult.connHandle = p_conn->connHandle;
                        s_ddEventCb(&ddEvent);
                    }
                    return;
                }

                if (p_event->eventField.onError.reqOpcode == ATT_FIND_BY_TYPE_VALUE_REQ)
                {
                    if (p_conn->p_discInstance->isSvcFound)
                    {
                        /* Service found. Send characteristic discovery */
                        if (GATTC_DiscoverAllCharacteristics(p_conn->connHandle, p_conn->p_discInstance->svcStartHandle, p_conn->p_discInstance->svcEndHandle) == MBA_RES_BUSY)
                        {
                            p_conn->p_discInstance->queuedReqByProtocol = ATT_READ_BY_TYPE_REQ;
                        }
                    }
                    else
                    {
                        /* Move to next service discovery if exists */
                        ble_dd_NextServiceDiscovery(p_conn);
                    }
                }
                else if (p_event->eventField.onError.reqOpcode == ATT_READ_BY_TYPE_REQ)
                {
                    uint16_t result;

                    /* Characteristic discovery finish. Check if there's descriptor to discover. */
                    result = ble_dd_DescriptorDiscovery(p_conn);

                    /* No descriptor need to discover. Discovery of one service is finished. */
                    if (result == MBA_RES_SUCCESS)
                    {
                        /* Move to next service discovery if exists */
                        ble_dd_NextServiceDiscovery(p_conn);
                    }
                }
                else if (p_event->eventField.onError.reqOpcode == ATT_FIND_INFORMATION_REQ)
                {
                    /* Move to next service discovery if exists */
                    ble_dd_NextServiceDiscovery(p_conn);
                }
            }
        }
        break;

        case GATTC_EVT_DISC_PRIM_SERV_BY_UUID_RESP:
        {
            BLE_DD_Conn_T *p_conn;

            p_conn = ble_dd_FindConnByHandle(p_event->eventField.onDiscPrimServByUuidResp.connHandle);

            /* Ignore responses when dd is not discovering */
            if (p_conn->isDiscovering == false)
                return;

            if (p_conn != NULL)
            {
                BUF_LE_TO_U16(&p_conn->p_discInstance->svcStartHandle, &p_event->eventField.onDiscPrimServByUuidResp.handleInfo[0]);
                BUF_LE_TO_U16(&p_conn->p_discInstance->svcEndHandle, &p_event->eventField.onDiscPrimServByUuidResp.handleInfo[2]);
                p_conn->p_discInstance->isSvcFound = 1;

                if (p_event->eventField.onDiscPrimServByUuidResp.procedureStatus == GATT_PROCEDURE_STATUS_FINISH)
                {
                    /* Send characteristic discovery directly if procedure is finished */
                    if (GATTC_DiscoverAllCharacteristics(p_conn->connHandle, p_conn->p_discInstance->svcStartHandle, p_conn->p_discInstance->svcEndHandle) == MBA_RES_BUSY)
                    {
                        p_conn->p_discInstance->queuedReqByProtocol = ATT_READ_BY_TYPE_REQ;
                    }
                }
            }
        }
        break;

        case GATTC_EVT_DISC_CHAR_RESP:
        {
            BLE_DD_Conn_T *p_conn;

            p_conn = ble_dd_FindConnByHandle(p_event->eventField.onDiscPrimServByUuidResp.connHandle);

            /* Ignore responses when dd is not discovering */
            if (p_conn->isDiscovering == false)
                return;

            if (p_conn != NULL)
            {
                ble_dd_ProcCharDiscResp(p_conn, p_event);

                /* Move to descriptor discovery or next service discovery when procedure finish. */
                if (p_event->eventField.onDiscCharResp.procedureStatus == GATT_PROCEDURE_STATUS_FINISH)
                {
                    uint16_t result;

                    /* Characteristic discovery finish. Check if there's descriptor to discover. */
                    result = ble_dd_DescriptorDiscovery(p_conn);

                    if (result == MBA_RES_SUCCESS)
                    {
                        /* Move to next service discovery if exists */
                        ble_dd_NextServiceDiscovery(p_conn);
                    }
                }
            }
        }
        break;

        case GATTC_EVT_DISC_DESC_RESP:
        {
            BLE_DD_Conn_T *p_conn;

            p_conn = ble_dd_FindConnByHandle(p_event->eventField.onDiscDescResp.connHandle);

            /* Ignore responses when dd is not discovering */
            if (p_conn->isDiscovering == false)
                return;

            if (p_conn != NULL)
            {
                if (p_event->eventField.onDiscDescResp.infoDataLength)
                {
                    ble_dd_ProcDescDiscResp(p_conn, p_event);
                }

                /* Move to next service discovery when procedure finish. */
                if (p_event->eventField.onDiscDescResp.procedureStatus == GATT_PROCEDURE_STATUS_FINISH)
                {
                    /* Move to next service discovery if exists */
                    ble_dd_NextServiceDiscovery(p_conn);
                }
            }
        }
        break;

        case GATTC_EVT_PROTOCOL_AVAILABLE:
        {
            BLE_DD_Conn_T *p_conn;

            p_conn = ble_dd_FindConnByHandle(p_event->eventField.onClientProtocolAvailable.connHandle);

            /* Ignore responses when dd is not discovering */
            if (p_conn->isDiscovering == false)
                return;

            if (p_conn != NULL)
            {
                if (p_conn->p_discInstance->queuedReqByProtocol == ATT_FIND_BY_TYPE_VALUE_REQ)
                {
                    p_conn->p_discInstance->queuedReqByProtocol = 0;
                    ble_dd_ServiceDiscovery(p_conn);
                }
                else if (p_conn->p_discInstance->queuedReqByProtocol == ATT_READ_BY_TYPE_REQ)
                {
                    p_conn->p_discInstance->queuedReqByProtocol = 0;
                    if (GATTC_DiscoverAllCharacteristics(p_conn->connHandle, p_conn->p_discInstance->svcStartHandle, p_conn->p_discInstance->svcEndHandle) == MBA_RES_BUSY)
                    {
                        p_conn->p_discInstance->queuedReqByProtocol = ATT_READ_BY_TYPE_REQ;
                    }
                }
                else if (p_conn->p_discInstance->queuedReqByProtocol == ATT_FIND_INFORMATION_REQ)
                {
                    p_conn->p_discInstance->queuedReqByProtocol = 0;
                    if (GATTC_DiscoverAllDescriptors(p_conn->connHandle, p_conn->p_discInstance->svcStartHandle , p_conn->p_discInstance->svcEndHandle) == MBA_RES_BUSY)
                    {
                        p_conn->p_discInstance->queuedReqByProtocol = ATT_FIND_INFORMATION_REQ;
                    }
                }
            }
        }
        break;

        default:
        break;
    }
}

void BLE_DD_Init()
{
    uint8_t i;

    memset((uint8_t *)&s_ddCtrl, 0, sizeof(BLE_DD_Ctrl_T));
    for (i=0; i<BLE_GAP_MAX_LINK_NBR; i++)
    {
        s_ddCtrl.conn[i].p_discInstance = NULL;
    }
}

void BLE_DD_EventRegister(BLE_DD_EventCb_T eventCb)
{
    s_ddEventCb = eventCb;
}

uint16_t BLE_DD_ServiceDiscoveryRegister(BLE_DD_DiscSvc_T *p_discSvc)
{
    if (s_ddCtrl.numOfService < BLE_DD_MAX_DISC_SVC_NUM)
    {
        memcpy((uint8_t *)&s_ddCtrl.services[s_ddCtrl.numOfService], (uint8_t *)p_discSvc, sizeof(BLE_DD_DiscSvc_T));
        s_ddCtrl.numOfService += 1;
        return MBA_RES_SUCCESS;
    }
    else
    {
        return MBA_RES_FAIL;
    }
}

void BLE_DD_BleEventHandler(BLE_DD_Config_T *p_config, STACK_Event_T *p_stackEvent)
{
    switch (p_stackEvent->groupId)
    {
        case STACK_GRP_BLE_GAP:
        {
            if (p_config != NULL)
            {
                ble_dd_StackEvtBleGapHandler(p_config, (BLE_GAP_Event_T *)p_stackEvent->p_event);
            }
        }
        break;

        case STACK_GRP_GATT:
        {
            ble_dd_StackEvtBleGattcHandler((GATT_Event_T *)p_stackEvent->p_event);
        }
        break;

        default:
        break;
    }
}

uint16_t BLE_DD_RestartServicesDiscovery(uint16_t connHandle)
{
    BLE_DD_Conn_T *p_conn;

    p_conn = ble_dd_FindConnByHandle(connHandle);

    if (p_conn != NULL)
    {
        if (p_conn->p_discInstance != NULL)
        {
            memset((uint8_t *)p_conn->p_discInstance, 0, sizeof(BLE_DD_DiscInstance_T));
            p_conn->discSvcIndex = 0;
            p_conn->isDiscovering = true;
            ble_dd_ServiceDiscovery(p_conn);
            return MBA_RES_SUCCESS;
        }
        else
        {
            return MBA_RES_OOM;
        }
    }
    else
    {
        return MBA_RES_INVALID_PARA;
    }
}

