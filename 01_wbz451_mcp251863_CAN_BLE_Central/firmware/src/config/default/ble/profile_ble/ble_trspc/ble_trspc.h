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
  BLE Transparent Client Profile Source File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_trspc.h

  Summary:
    This file contains the BLE Transparent Client functions for application user.

  Description:
    This file contains the BLE Transparent Client functions for application user.
 *******************************************************************************/


/**
 * @addtogroup BLE_TRPC
 * @{
 * @brief Header file for the BLE Transparent Profile Client role library.
 * @note Definitions and prototypes for the BLE Transparent profile stack layer application programming interface.
 */
#ifndef BLE_TRSPC_H
#define BLE_TRSPC_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "stack_mgr.h"
#include "ble_gcm/ble_dd.h"

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************
/**@addtogroup BLE_TRPC_DEFINES Defines
 * @{ */

/**@defgroup BLE_TRSPC_MAX_CONN_NBR Maximum connection number
 * @brief The definition of Memory size.
 * @{ */
#define BLE_TRSPC_MAX_CONN_NBR                  BLE_GAP_MAX_LINK_NBR    /**< Maximum allowing Conncetion Numbers for MBADK. */
/** @} */


/**@defgroup BLE_TRSPC_UL_STATUS Definition of uplink status
 * @brief The definition of BLE transparent service uplink status.
 * @{ */
#define BLE_TRSPC_UL_STATUS_DISABLED            0x00    /**< Transparent uplink is disabled. */
#define BLE_TRSPC_UL_STATUS_CBFCENABLED         0x01    /**< Transparent uplink is enabled with credit based flow control */
/** @} */

/**@defgroup BLE_TRSPC_DL_STATUS Definition of downlink status
 * @brief The definition of BLE transparent service downlink status.
 * @{ */
#define BLE_TRSPC_DL_STATUS_DISABLED            0x00    /**< Transparent downlink is disabled. */
#define BLE_TRSPC_DL_STATUS_NONCBFCENABLED      0x10    /**< Transparent downlink is enabled without credit based flow control */
#define BLE_TRSPC_DL_STATUS_CBFCENABLED         0x20    /**< Transparent downlink is enabled with credit based flow control */
/** @} */


/**@} */ //BLE_TRPC_DEFINES


/**@addtogroup BLE_TRPC_ENUMS Enumerations
 * @{ */

/**@brief Enumeration type of BLE transparent profile callback events. */
typedef enum BLE_TRSPC_EventId_T
{
    BLE_TRSPC_EVT_NULL = 0x00,
    BLE_TRSPC_EVT_UL_STATUS,                            /**< Transparent Profile Uplink status update event. See @ref BLE_TRSPC_EvtUplinkStatus_T for event details. */
    BLE_TRSPC_EVT_DL_STATUS,                            /**< Transparent Profile Downlink status update event. See @ref BLE_TRSPC_EvtDownlinkStatus_T for event details. */
    BLE_TRSPC_EVT_RECEIVE_DATA,                         /**< Transparent Profile Data Channel received notification event. See @ref BLE_TRSPC_EvtReceiveData_T for event details. */
    BLE_TRSPC_EVT_VENDOR_CMD,                           /**< Transparent Profile vendor command received notification event. See @ref BLE_TRSPC_EvtVendorCmd_T for event details. */
    BLE_TRSPC_EVT_VENDOR_CMD_RSP,                       /**< Transparent Profile Vendor command response received notification event. See @ref BLE_TRSPC_EvtVendorCmdRsp_T for event details. */
    BLE_TRSPC_EVT_DISC_COMPLETE,                        /**< Transparent Profile discovery complete event. See @ref BLE_TRSPC_EvtDiscComplete_T for event details. */
    BLE_TRSPC_EVT_ERR_NO_MEM,                           /**< Profile internal error occurs due to insufficient heap memory. */
    BLE_TRSPC_EVT_END
}BLE_TRSPC_EventId_T;

/**@} */ //BLE_TRPC_ENUMS


// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/**@addtogroup BLE_TRPC_STRUCTS Structures
 * @{ */

/**@brief Data structure for @ref BLE_TRSPC_EVT_UL_STATUS event. */
typedef struct BLE_TRSPC_EvtUplinkStatus_T
{
    uint16_t         connHandle;                        /**< Connection handle associated with this connection. */
    uint8_t          status;                            /**< Connection status. See @ref BLE_TRSPC_UL_STATUS.*/
}   BLE_TRSPC_EvtUplinkStatus_T;

/**@brief Data structure for @ref BLE_TRSPC_EVT_DL_STATUS event. */
typedef struct BLE_TRSPC_EvtDownlinkStatus_T
{
    uint16_t        connHandle;                         /**< Connection handle associated with this connection. */
    uint8_t         status;                             /**< Connection status. See @ref BLE_TRSPC_DL_STATUS.*/
    uint8_t         currentCreditNumber;                /**< The current available credit number of the downlink in this connection */
}   BLE_TRSPC_EvtDownlinkStatus_T;

/**@brief Data structure for @ref BLE_TRSPC_EVT_RECEIVE_DATA event. */
typedef struct BLE_TRSPC_EvtReceiveData_T
{
    uint16_t         connHandle;                        /**< Connection handle associated with this connection. */
}   BLE_TRSPC_EvtReceiveData_T;

/**@brief Data structure for @ref BLE_TRSPC_EVT_VENDOR_CMD event. */
typedef struct BLE_TRSPC_EvtVendorCmd_T
{
    uint16_t        connHandle;                         /**< Connection handle associated with this connection. */
    uint8_t         payloadLength;                      /**< Length of payload. */
    uint8_t         *p_payLoad;                         /**< Vendor command payload pointer. */
}   BLE_TRSPC_EvtVendorCmd_T;

/**@brief Data structure for @ref BLE_TRSPC_EVT_VENDOR_CMD_RSP event. */
typedef struct BLE_TRSPC_EvtVendorCmdRsp_T
{
    uint16_t        connHandle;                         /**< Connection handle associated with this connection. */
}   BLE_TRSPC_EvtVendorCmdRsp_T;

/**@brief Data structure for @ref BLE_TRSPC_EVT_DISC_COMPLETE event. */
typedef struct BLE_TRSPC_EvtDiscComplete_T
{
    uint16_t        connHandle;                         /**< Connection handle associated with this connection. */
}   BLE_TRSPC_EvtDiscComplete_T;

/**@brief The union of BLE Transparent profile client event types. */
typedef union
{
    BLE_TRSPC_EvtUplinkStatus_T     onUplinkStatus;     /**< Handle @ref BLE_TRSPC_EVT_UL_STATUS. */
    BLE_TRSPC_EvtDownlinkStatus_T   onDownlinkStatus;   /**< Handle @ref BLE_TRSPC_EVT_DL_STATUS. */
    BLE_TRSPC_EvtReceiveData_T      onReceiveData;      /**< Handle @ref BLE_TRSPC_EVT_RECEIVE_DATA. */
    BLE_TRSPC_EvtVendorCmd_T        onVendorCmd;        /**< Handle @ref BLE_TRSPC_EVT_VENDOR_CMD. */
    BLE_TRSPC_EvtVendorCmdRsp_T     onVendorCmdRsp;     /**< Handle @ref BLE_TRSPC_EVT_VENDOR_CMD_RSP. */
    BLE_TRSPC_EvtDiscComplete_T     onDiscComplete;     /**< Handle @ref BLE_TRSPC_EVT_DISC_COMPLETE. */
} BLE_TRSPC_EventField_T;


/**@brief BLE Transparent profile client callback event. */
typedef struct  BLE_TRSPC_Event_T
{
    BLE_TRSPC_EventId_T         eventId;                /**< Event ID.*/
    BLE_TRSPC_EventField_T      eventField;             /**< Event field. */
} BLE_TRSPC_Event_T;

/**@brief BLE Transparent profile cliet callback type. This callback function sends BLE Transparent profile client events to the application. */
typedef void(*BLE_TRSPC_EventCb_T)(BLE_TRSPC_Event_T *p_event);

/**@} */ //BLE_TRPC_STRUCTS


// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************
/**@addtogroup BLE_TRPC_FUNS Functions
 * @{ */

/**@brief Initialize TRS client profile.
 *
 * @retval MBA_RES_SUCCESS                  Successfully initialize the TRS client profile.
 * @retval MBA_RES_FAIL                     Fail to registering TRS discovery to BLE_DD module.
 *
 */
uint16_t BLE_TRSPC_Init();

/**@brief Register BLE Transparent profile client callback. 
 *
 * @param[in] bleTranCliHandler             Client callback function.
 *
 */
void BLE_TRSPC_EventRegister(BLE_TRSPC_EventCb_T bleTranCliHandler);

/**@brief Send vendor command.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] commandID                     Command id of the vendor command
 * @param[in] commandLength                 Length of payload in vendor commnad
 * @param[in] p_commandPayload              Pointer to the payload of vendor command
 *
 * @retval MBA_RES_SUCCESS                  Successfully issue a send vendor command.
 * @retval MBA_RES_FAIL                     Invalid connection or the CCCD of TCP is not enabled.
 * @retval MBA_RES_OOM                      No available memory.
 * @retval MBA_RES_INVALID_PARA             Error commandID usage or commandLength invalid.
 *
 */
uint16_t BLE_TRSPC_SendVendorCommand(uint16_t connHandle, uint8_t commandID, uint8_t commandLength, uint8_t *p_commandPayload);

/**@brief Send transparent data.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] len                           Data length.
 * @param[in] p_data                        Pointer to the transparent data.
 *
 * @retval MBA_RES_SUCCESS                  Successfully issue a send data.
 * @retval MBA_RES_OOM                      No available memory.
 * @retval MBA_RES_INVALID_PARA             Parameter does not meet the spec.
 *
 */
uint16_t BLE_TRSPC_SendData(uint16_t connHandle, uint16_t len, uint8_t *p_data);

/**@brief Get queued data length.
 *
 * @param[in]  connHandle                   Connection handle associated with the queued data
 * @param[out] p_dataLength                 Data length.
 *
 */
void BLE_TRSPC_GetDataLength(uint16_t connHandle, uint16_t *p_dataLength);

/**@brief Get queued data.
 *
 * @param[in]  connHandle                   Connection handle associated with the queued data
 * @param[out] p_data                       Pointer to the data buffer
 *
 * @retval MBA_RES_SUCCESS                  Successfully issue a flow ctrl stop.
 * @retval MBA_RES_FAIL                     No data in the input queue.
 *
 */
uint16_t BLE_TRSPC_GetData(uint16_t connHandle, uint8_t *p_data);

/**@brief Handle BLE_Stack events.
 *        This API should be called in the application while caching BLE_Stack events
 *
 * @param[in] p_stackEvent                  Pointer to BLE_Stack events buffer.
 *
 */
void BLE_TRSPC_BleEventHandler(STACK_Event_T *p_stackEvent);

/**@brief Handle BLE_DD (Database Discovery middleware) events.
 *        This API should be called in the application while caching BLE_DD events
 *
 * @param[in] p_event                       Pointer to BLE_DD events buffer.
 *
 */
void BLE_TRSPC_BleDdEventHandler(BLE_DD_Event_T *p_event);

/**@} */ //BLE_TRPC_FUNS

#endif

/**
  @}
 */
