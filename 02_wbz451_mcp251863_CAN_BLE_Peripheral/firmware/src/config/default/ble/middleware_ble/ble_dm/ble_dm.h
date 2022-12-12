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
  BLE Device Manager Middleware Header File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_dm.h

  Summary:
    This file contains the BLE Device Manager functions and event for application user.

  Description:
    This file contains the BLE Device Manager functions and event for application user.
    The "BLE_DM_Init" function shall be called in the "APP_Initialize" function to 
    initialize the this modules in the system.
 *******************************************************************************/


/**
 * @addtogroup BLE_DM
 * @{
 * @brief Header file for the BLE Device Manager (ble_dm) module.
 * @note Definitions and prototypes for the BLE Device Manager application programming interface.
 */
 
#ifndef BLE_DM_H
#define BLE_DM_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdbool.h>
#include <stdint.h>
#include "mba_error_defs.h"
#include "stack_mgr.h"
#include "gap_defs.h"
#include "ble_gap.h"
#include "ble_l2cap.h"
#include "gatt.h"
#include "ble_smp.h"


// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************
/**@addtogroup BLE_DM_DEFINES Defines
 * @{ */

/**@defgroup BLE_DM_MAX_RETISTER_NUM Maximum registration number
 * @brief The definition of maximum number of BLE_DM register
 * @{ */
#define BLE_DM_MAX_REGISTER_NUM                 2                               /**< Maximum BLE_DM register num. */
/** @} */


/**@defgroup BLE_DM_MAX_PAIRED_DEVICE_NUM Maximum paired record number
 * @brief The definition of maximum number of paired device store in flash
 * @{ */
#define BLE_DM_MAX_PAIRED_DEVICE_NUM            8                               /**< Maximum number of paired device store in flash. */
/** @} */


/**@defgroup BLE_DM_PEER_DEV_ID_INVALID Invalid peer device ID
 * @brief The definition of invalid peer device id
 * @{ */
#define BLE_DM_PEER_DEV_ID_INVALID              BLE_DM_MAX_PAIRED_DEVICE_NUM    /**< Definition of invalid peer device id. */
/** @} */

/**@defgroup BLE_DM_MAX_FILTER_ACCEPT_LIST_NUM Maximum filter accept list num
 * @brief The definition of maximum number of paired devices in the filter accept list
 * @{ */
#define BLE_DM_MAX_FILTER_ACCEPT_LIST_NUM       BLE_DM_MAX_PAIRED_DEVICE_NUM                /**< Maximum number of filter accept list. */
/** @} */

/**@defgroup BLE_DM_MAX_RESOLVING_LIST_NUM Maximum resolving list num
 * @brief The definition of maximum number of paired devices in the resolving list
 * @{ */
#define BLE_DM_MAX_RESOLVING_LIST_NUM           BLE_DM_MAX_PAIRED_DEVICE_NUM                /**< Maximum number of resolving list. */
/** @} */



/**@} */ //BLE_DM_DEFINES


/**@addtogroup BLE_DM_ENUMS Enumerations
 * @{ */

/**@brief Enumeration type of BLE DM callback events. */
typedef enum BLE_DM_EventId_T
{
    BLE_DM_EVT_DISCONNECTED,                    /**< BLE link is terminated. See @ref BLE_DM_Event_T for the event details. */
    BLE_DM_EVT_CONNECTED,                       /**< BLE link is established. See @ref BLE_DM_Event_T for the event details. */
    BLE_DM_EVT_SECURITY_START,                  /**< Security procedure has started. See @ref BLE_DM_EvtSecurityStart_T. for the event detail */
    BLE_DM_EVT_SECURITY_SUCCESS,                /**< Security procedure has finished successfully. See @ref BLE_DM_EvtSecuritySuccess_T. for the event detail */
    BLE_DM_EVT_SECURITY_FAIL,                   /**< Security procedure has failed. See @ref BLE_DM_EvtSecurityFail_T. for the event detail */
    BLE_DM_EVT_PAIRED_DEVICE_FULL,              /**< The maximum record number of paired device have been reached. DM cannot store the latest bonding data to flash. To solve this problem, delete paired device that is not needed anymore. See the @ref BLE_DM_EvtPairedDeviceFull_T for the event content. */
    BLE_DM_EVT_PAIRED_DEVICE_UPDATED,           /**< A paired device have been updated. Application can use peerDevId get paired device information by @ref BLE_DM_GetPairedDevice. */
    BLE_DM_EVT_CONN_UPDATE_SUCCESS,             /**< Connection parameter update triggered by @ref BLE_DM_ConnectionParameterUpdate is success. See @ref BLE_DM_Event_T for the event details.*/
    BLE_DM_EVT_CONN_UPDATE_FAIL,                /**< Connection parameter update triggered by @ref BLE_DM_ConnectionParameterUpdate is fail. See @ref BLE_DM_Event_T for the event details.*/

    BLE_DM_EVT_END
}BLE_DM_EventId_T;

/**@brief Enumeration of security process.
 */
typedef enum BLE_DM_SecurityProc_T
{
    DM_SECURITY_PROC_PAIRING,                   /**< Pairing procedure. */
    DM_SECURITY_PROC_ENCRYPTION,                /**< Encrypt the link. */
} BLE_DM_SecurityProc_T;

/**@} */ //BLE_DM_ENUMS

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/**@addtogroup BLE_DM_STRUCTS Structures
 * @{ */

/**@brief Data structure for @ref BLE_DM_EVT_SECURITY_START event. */
typedef struct BLE_DM_EvtSecurityStart_T
{
    BLE_DM_SecurityProc_T           procedure;              /**< The procedure that has started. */
} BLE_DM_EvtSecurityStart_T;

/**@brief Data structure for @ref BLE_DM_EVT_SECURITY_SUCCESS event. */
typedef struct BLE_DM_EvtSecuritySuccess_T
{
    BLE_DM_SecurityProc_T           procedure;              /**< The procedure that has finished successfully. */
    uint8_t                         bonded;                 /**< The pairing procedure is bonded or not.*/
} BLE_DM_EvtSecuritySuccess_T;


/**@brief Data structure for @ref BLE_DM_EVT_SECURITY_FAIL event. */
typedef struct BLE_DM_EvtSecurityFail_T
{
    BLE_DM_SecurityProc_T           procedure;              /**< The procedure that has failed. */
    uint8_t                         error;                  /**< The error for failure occurred. See @ref BLE_SMP_PAIRING_RESULT if procedure is @ref DM_SECURITY_PROC_PAIRING. */
    uint8_t                         reason;                 /**< The reason for error occurred. See @ref BLE_SMP_PAIRING_FAIL_REASON if error is BLE_SMP_PAIRING_FAIL */
} BLE_DM_EvtSecurityFail_T;


/**@brief Data structure for @ref BLE_DM_EVT_PAIRED_DEVICE_FULL event. */
typedef struct BLE_DM_EvtPairedDeviceFull_T
{
    uint8_t                         pairedDeviceNum;        /**< The number of paired device that have been recorded in the flash.*/
} BLE_DM_EvtPairedDeviceFull_T;


/**@brief Union of BLE_DM callback event data types. */
typedef union
{
    BLE_DM_EvtSecurityStart_T       evtSecurityStart;       /**< Handles @ref BLE_DM_EVT_SECURITY_START.*/
    BLE_DM_EvtSecuritySuccess_T     evtSecuritySuccess;     /**< Handles @ref BLE_DM_EVT_SECURITY_SUCCESS.*/
    BLE_DM_EvtSecurityFail_T        evtSecurityFail;        /**< Handles @ref BLE_DM_EVT_SECURITY_FAIL.*/
    BLE_DM_EvtPairedDeviceFull_T    evtPairedDevFull;       /**< Handles @ref BLE_DM_EVT_PAIRED_DEVICE_FULL. */
} BLE_DM_EventField_T;

/**@brief BLE_DM callback event. */
typedef struct  BLE_DM_Event_T
{
    BLE_DM_EventId_T                eventId;                /**< Event ID.*/
    uint16_t                        connHandle;             /**< Connection handle associated with this connection. */
    uint8_t                         peerDevId;              /**< Peer device ID. */
    BLE_DM_EventField_T             eventField;             /**< Event field. */
} BLE_DM_Event_T;

/**@brief The structure contains information about configuration used for BLE_DM_Conn submodule in BLE_DM. */
typedef struct BLE_DM_ConnConfig_T
{
    uint16_t                        minAcceptConnInterval;          /**< Minimum acceptable connection interval. */
    uint16_t                        maxAcceptConnInterval;          /**< Maximum acceptable connection interval. */
    uint16_t                        minAcceptPeripheralLatency;     /**< Minimum acceptable Peripheral latency. */
    uint16_t                        maxAcceptPeripheralLatency;     /**< Maximum acceptable Peripheral latency. */
    bool                            autoReplyUpdateRequest;         /**< Set true to enable automatic reply when receiving BLE_L2CAP_EVT_CONN_PARA_UPDATE_REQ or BLE_GAP_EVT_REMOTE_CONN_PARAM_REQUEST. Otherwise set false. */
} BLE_DM_ConnConfig_T;

/**@brief The structure contains information about configuration used for BLE_DM module. */
typedef struct BLE_DM_Config_T
{
    BLE_DM_ConnConfig_T             connConfig;                    /**< Configuration parameters of BLE_DM_CONN module. @ref BLE_DM_ConnConfig_T. */
    bool                            secAutoAccept;                 /**< Configuration parameter of BLE_DM_SM module. Whether to accept and response pairing request or security request automatically. See true to enable. */
} BLE_DM_Config_T;

/**@brief The structure contains information about paired device information. */
typedef struct BLE_DM_PairedDevInfo_T
{
    BLE_GAP_Addr_T                  remoteAddr;                    /**< Paired device bluetooth address. */
    uint8_t                         remoteIrk[16];                 /**< Paired device BLE identity resolving key. */
    uint8_t                         rv[8];                         /**< Paired device BLE rand value */
    uint8_t                         ediv[2];                       /**< Paired device BLE encrypted diversifier. */
    uint8_t                         ltk[16];                       /**< Paired device BLE Link key. */
    uint8_t                         lesc:1;                        /**< Paired device using LE secure connection. */
    uint8_t                         auth:1;                        /**< Paired device using authenticated pairing method. */
    uint8_t                         encryptKeySize:6;              /**< Paired device BLE encrpytion key size */
}BLE_DM_PairedDevInfo_T;

/**@brief The structure contains information about connection parameter update. */
typedef struct BLE_DM_ConnParamUpdate_T
{
    uint16_t                        intervalMin;                    /**< Minimum value for the connection interval. */
    uint16_t                        intervalMax;                    /**< Maximum value for the connection interval. */
    uint16_t                        latency;                        /**< Peripheral latency for the connection in number of connection events. */
    uint16_t                        timeout;                        /**< Supervision timeout for the LE link. */
} BLE_DM_ConnParamUpdate_T;


/**@brief BLE_DM callback type. This callback function sends BLE_DM events to the application. */
typedef void (*BLE_DM_EventCb_T)(BLE_DM_Event_T *p_event);

/**@} */ //BLE_DM_STRUCTS

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************
/**@addtogroup BLE_DM_FUNS Functions
 * @{ */
 
/**@brief Initialize BLE_DM module.
 *
*/
void BLE_DM_Init();


/**@brief Register BLE_DM callback.
 * @note  This API should be called in the application initialization routine.
 *
 * @param[in] eventCb           Client callback function.
 *
 * @retval MBA_RES_SUCCESS      Successfully register BLE_DM callback function.
 * @retval MBA_RES_NO_RESOURCE  Fail to register DM callback funcation.
 * 
*/
uint16_t BLE_DM_EventRegister(BLE_DM_EventCb_T eventCb);


/**@brief Handle BLE events.
 * @note  This API should be called in the application while caching BLE events
 *
 * @param[in] p_stackEvent        Pointer to BLE events buffer.
*/
void BLE_DM_BleEventHandler(STACK_Event_T *p_stackEvent);

/**@brief Configure BLE_DM module.
 *       
 *
 * @param[in] p_config          Pointer to the @ref BLE_DM_Config_T structure buffer.
 *
 * @retval MBA_RES_SUCCESS      Successfully build configuration.
 * @retval MBA_RES_INVALID_PARA The parameter in p_config is invalid.
*/
uint16_t BLE_DM_Config(BLE_DM_Config_T *p_config);

/**@brief Proceed the security process.
 * @note
 *        For Central role, BLE_DM will call BLE_GAP_StartEncryption API to initiate encryption 
 *        procedure if paired information recorded in the PDS for peer connected device. 
 *        Otherwise BLE_SMP_InitiatePairing API will be called by BLE_DM to start pairing procedure.
 *
 *        For Peripheral role, BLE DM call BLE_SMP_InitiatePairing API to trigger SMP security request. 
 *        It is up to the remote Central then to initiate pairing or encryption procedure.
 *
 * @param[in] connHandle    Connection handle associated with this connection.
 * @param[in] repairing     Whether to force a pairing procedure even if there is an existing
 *                          pairing record. This argument is only for the Central role.
 *
 * @retval MBA_RES_SUCCESS      Successfully build configuration.
 * @retval MBA_RES_OOM          Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA The connHandle is invalid.
*/
uint16_t BLE_DM_ProceedSecurity(uint16_t connHandle, uint8_t repairing);

/**@brief Set filter accept list.
 * 
 * @param[in] devCnt             The number of paired device to add to filter accept list. The number must be less than or equel to
 *                               @ref BLE_DM_MAX_FILTER_ACCEPT_LIST_NUM. Pass zero to clear filter accept list.
 * @param[in] p_devId            The paired device list to add to filter accept list. Pass NULL to clear filter accept list.
 *
 * @retval MBA_RES_SUCCESS      Successfully set or clear filter accept list.
 * @retval MBA_RES_INVALID_PARA The devCnt is greater than @ref BLE_DM_MAX_FILTER_ACCEPT_LIST_NUM.
*/
uint16_t BLE_DM_SetFilterAcceptList(uint8_t devCnt, uint8_t const *p_devId);

/**@brief Get filter accept list.
 * 
 * @param[out] p_devCnt          The number of devices in filter accept list.
 * @param[out] p_addr            Pointer to the @ref BLE_GAP_Addr_T structure buffer.
 *
 * @retval MBA_RES_SUCCESS       Successfully get filter accept list.
*/
uint16_t BLE_DM_GetFilterAcceptList(uint8_t *p_devCnt, BLE_GAP_Addr_T *p_addr);

/**@brief Set resolving list.
 * 
 * @param[in] devCnt             The number of paired device to add to resolving list. The number must be less than or equel to
 *                               @ref BLE_DM_MAX_RESOLVING_LIST_NUM. Pass zero to clear resolving list.
 * @param[in] p_devId            The paired device list to add to resolving list. Pass NULL to clear resolving list.
 * @param[in] p_privacyMode;     The privacy mode list (see @ref BLE_GAP_PRIVACY_MODE.). Each entry in the array maps to the entry in p_devId at the same index.
 *                               Pass NULL to clear resolving list.
 *
 * @retval MBA_RES_SUCCESS      Successfully set or clear resolving list.
 * @retval MBA_RES_INVALID_PARA The devCnt is greater than @ref BLE_DM_MAX_RESOLVING_LIST_NUM.
*/
uint16_t BLE_DM_SetResolvingList(uint8_t devCnt, uint8_t const *p_devId, uint8_t const * p_privacyMode);


/**@brief Delete specific paired device information. 
 * @note  Application could use the @ref BLE_DM_GetPairedDeviceList API to get the paired device list of device IDs.
 *
 * @param[in] devId                  Paired device ID of paired information.
 *
 * @retval MBA_RES_SUCCESS           Successfully deleted specific paired device information.
 * @retval MBA_RES_INVALID_PARA      Invalid parameters, if device ID does not recognize a valid pairing device.
 * @retval MBA_RES_FAIL              The delete operation failure.
*/
uint16_t BLE_DM_DeletePairedDevice(uint8_t devId);

/**@brief Get the single paired device information via device ID.
 *
 * @param[in] devId                  The device ID. Should be in the range of 0 ~ (@ref BLE_DM_MAX_PAIRED_DEVICE_NUM - 1).
 * @param[out] p_pairedDevInfo       Pointer to @ref BLE_DM_PairedDevInfo_T structure buffer.
 *
 * @retval MBA_RES_SUCCESS           Successfully get single paired devices information.
 * @retval MBA_RES_INVALID_PARA      DevId exceeds the maximum range or the number of paired devices
 * @retval MBA_RES_FAIL              The get operation failure.
 */
uint16_t BLE_DM_GetPairedDevice(uint8_t devId, BLE_DM_PairedDevInfo_T *p_pairedDevInfo);

/**@brief Delete all paired device information.
 *
 *
 * @retval MBA_RES_SUCCESS           Successfully deleted all paired device information.
 * @retval MBA_RES_FAIL              The delete operation failure.
*/
uint16_t BLE_DM_DeleteAllPairedDevice();

/**@brief Get the paired device list of device IDs.
 *
 * @param[out] p_devId               Pointer to the device IDs list buffer. See @ref BLE_DM_MAX_PAIRED_DEVICE_NUM for the maximum size definition.
 * @param[out] p_devCnt              The number of valid device IDs in p_devId.
 *
 * @retval void
*/
void BLE_DM_GetPairedDeviceList(uint8_t *p_devId, uint8_t *p_devCnt);

/**@brief Change connection parameters of the specific connection.
 *
 * @param[in] connHandle            Connection handle associated with this connection.
 * @param[in] p_params              Pointer to the @ref BLE_DM_ConnParamUpdate_T structure buffer.
 *
 * @retval MBA_RES_SUCCESS          Successfully send the update request to remote device.
 * @retval MBA_RES_FAIL             The update procedure is disallowed in certain condition.
 * @retval MBA_RES_OOM              Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA     Invalid connection handle.
*/
uint16_t BLE_DM_ConnectionParameterUpdate(uint16_t connHandle, BLE_DM_ConnParamUpdate_T *p_params);

/**@} */ //BLE_DM_FUNS

#endif

/**
  @}
*/
