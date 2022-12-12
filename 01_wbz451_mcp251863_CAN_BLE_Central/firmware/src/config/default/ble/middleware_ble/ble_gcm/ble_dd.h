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
  BLE Database Discovery Middleware Header File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_dd.h

  Summary:
    This file contains the BLE Database Discovery functions and event for application user.

  Description:
    This file contains the BLE Database Discovery functions and event for application user.
    The "BLE_DD_Init" function shall be called in the "APP_Initialize" function to 
    initialize the this modules in the system.
 *******************************************************************************/


/**
 * @addtogroup BLE_DD
 * @{
 * @brief Header file for the BLE Database Discovery (ble_dd) module.
 * @note Definitions and prototypes for the BLE Database Discovery application programming interface.
 */
 
#ifndef BLE_DD_H
#define BLE_DD_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include "stack_mgr.h"
#include "att_uuid.h"
#include "ble_gap.h"

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************

/**@addtogroup BLE_DD_DEFINES Defines
 * @{ */
 
/**@defgroup BLE_DD_CHAR_SETTING Characteristic setting
 * @brief The definition of characteristic setting for discovery
 * @{ */
#define CHAR_SET_DESCRIPTOR                         0x01    /**< Set if this is a characteristic descriptor */
/** @} */


/**@defgroup BLE_DD_MAX_REG_NUM Maximum register services number
 * @brief The definition of maximum registering services allowed in BLE_DD module
 * @{ */
#define BLE_DD_MAX_DISC_SVC_NUM                     0x06    /**< Maximum registering services allowed */
/** @} */


/**@} */ //BLE_DD_DEFINES

/**@addtogroup BLE_DD_ENUMS Enumerations
 * @{ */
 
/**@brief The definition of BLE_DD module event ID. */
typedef enum BLE_DD_EventId_T
{
    BLE_DD_EVT_DISC_COMPLETE,               /**< The discovery of all service is completed. @ref BLE_DD_EvtDiscResult_T */
    BLE_DD_EVT_SEC_REQUIRED,                /**< Encryption/authentication permission is required accessing characteristic at remote. Application might need to initiate encryption/authentication to remote. @ref BLE_DD_EvtSecRequire_T */
    BLE_DD_EVT_CONNECTED,                   /**< BLE link is established. See @ref BLE_DD_EvtConnect_T for the event details. */
    BLE_DD_EVT_DISCONNECTED,                /**< BLE link is terminated. See @ref BLE_DD_EvtDisconnect_T for the event details. */
    BLE_DD_EVT_END
}BLE_DD_EventId_T;

/**@} */ //BLE_DD_ENUMS
// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/**@addtogroup BLE_DD_STRUCTS Structures
 * @{ */
 
/**@brief Parameters configuration. */
typedef struct BLE_DD_Config_T
{
    uint8_t                 waitForSecurity:1;      /**< Configure if security is required before database discovery. Set true to enable. */
    uint8_t                 initDiscInCentral:1;    /**< Configure discovery option when the gap role of connection is central. Set true to enable. */
    uint8_t                 initDiscInPeripheral:1; /**< Configure discovery option when the gap role of connection is peripheral. Set true to enable. */
    uint8_t                 disableConnectedDisc:1; /**< Configure discovery function when connection established. Discovery might be optional for bonded link. Note: This is one-time option. Disable unnecessary discovery when connected at each time. */
    uint8_t                 reserved:4;             /**< Reserved for future used. */
} BLE_DD_Config_T;

/**@brief Characteristic information. */
typedef struct BLE_DD_CharInfo_T
{
    uint16_t                charHandle;             /**< Handle of the characteristic. */
    uint8_t                 property;               /**< The field is only meaningful when the type of characteristic is characteristic declaration. */
} BLE_DD_CharInfo_T;

/**@brief Characteristic list parameters. */
typedef struct BLE_DD_CharList_T
{
    uint16_t                connHandle;             /**< Connection handle associated with this connection. */
    BLE_DD_CharInfo_T       *p_charInfo;            /**< Pointer to the characteristic information. */
} BLE_DD_CharList_T;

/**@brief Characteristic for discovery procedure. */
typedef struct BLE_DD_DiscChar_T
{
    ATT_Uuid_T const        *p_uuid;                /**< Pointer to UUID. */
    uint8_t                 settings;               /**< Characteristic discovery settings. */
} BLE_DD_DiscChar_T;

/**@brief Service for discovery procedure. */
typedef struct BLE_DD_DiscSvc_T
{
    ATT_Uuid_T              svcUuid;                /**< UUID of the service to be discovered. */
    BLE_DD_DiscChar_T       **p_discChars;          /**< Characteristic list of the service to be discoverd. Note: only assigned characteristic will be discovered. */
    BLE_DD_CharList_T       *p_charList;            /**< Structure storing discovered information of the characteristic. Application/profile need to provide the storage. */
    uint8_t                 discCharsNum;           /**< Number of the characteristics in the list. */
} BLE_DD_DiscSvc_T;


/**@brief Data structure for @ref BLE_DD_EVT_DISC_COMPLETE event. */
typedef struct BLE_DD_EvtDiscResult_T
{
    uint16_t                connHandle;             /**< Connection handle associated with this connection. */
} BLE_DD_EvtDiscResult_T;

/**@brief Data structure for @ref BLE_DD_EVT_SEC_REQUIRED event. */
typedef struct BLE_DD_EvtSecRequire_T
{
    uint16_t                connHandle;             /**< Connection handle associated with this connection. */
} BLE_DD_EvtSecRequire_T;

/**@brief Data structure for @ref BLE_DD_EVT_CONNECTED event. */
typedef struct BLE_DD_EvtConnect_T
{
    uint16_t                connHandle;             /**< Connection handle associated with this connection. */
} BLE_DD_EvtConnect_T;

/**@brief Data structure for @ref BLE_DD_EVT_DISCONNECTED event. */
typedef struct BLE_DD_EvtDisconnect_T
{
    uint16_t                connHandle;             /**< Connection handle associated with this connection. */
} BLE_DD_EvtDisconnect_T;

/**@brief Union of BLE_DD callback event data types. */
typedef union
{
    BLE_DD_EvtDiscResult_T  evtDiscResult;          /**< Handle @ref BLE_DD_EVT_DISC_COMPLETE. */
    BLE_DD_EvtSecRequire_T  evtSecRequire;          /**< Handle @ref BLE_DD_EVT_SEC_REQUIRED. */
    BLE_DD_EvtConnect_T     evtConnect;             /**< Handle @ref BLE_DD_EVT_CONNECTED. */
    BLE_DD_EvtDisconnect_T  evtDisconnect;          /**< Handle @ref BLE_DD_EVT_DISCONNECTED. */
} BLE_DD_EventField_T;

/**@brief BLE_DD callback event. */
typedef struct  BLE_DD_Event_T
{
    BLE_DD_EventId_T        eventId;                /**< Event ID. */
    BLE_DD_EventField_T     eventField;             /**< Event field. */
} BLE_DD_Event_T;


/**@brief BLE_DD callback type. This callback function sends BLE_DD events to the application. */
typedef void (*BLE_DD_EventCb_T)(BLE_DD_Event_T *p_event);

/**@} */ //BLE_DD_STRUCTS

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************
/**@addtogroup BLE_DD_FUNS Functions
 * @{ */
 
/**@brief Initialize BLE_DD module.
 *
*/
void BLE_DD_Init();


/**@brief Register BLE_DD callback.
 * @note This API should be called in the application initialization routine
 *
 * @param[in] eventCb           Pointer to the @ref BLE_DD_EventCb_T structure buffer.
 *
*/
void BLE_DD_EventRegister(BLE_DD_EventCb_T eventCb);

/**@brief Register specific service to the database discovery module.
 * @note  Discovery of the service will be started by module after connected by configurations.
 *
 * @param[in] p_discSvc          Pointer to the @ref BLE_DD_DiscSvc_T structure buffer.
 *
 * @retval MBA_RES_SUCCESS       Successfully register service for discovery.
 * @retval MBA_RES_FAIL          Exceeds maximum number of registering service.
*/
uint16_t BLE_DD_ServiceDiscoveryRegister(BLE_DD_DiscSvc_T *p_discSvc);

/**@brief Handle BLE events
 * @note  This function should be called for every BLE event
 *
 * @param[in] p_config          Pointer to the @ref BLE_DD_Config_T structure buffer.
 * @param[in] p_stackEvent      Pointer to @ref STACK_Event_T structure buffer.
 *
*/
void BLE_DD_BleEventHandler(BLE_DD_Config_T *p_config, STACK_Event_T *p_stackEvent);

/**@brief Restart database discovery for specific connection
 * @note  This function shall only be called when remote services changed and application wants to restart database discovery.
 *
 * @param[in] connHandle        Connection handle associated with this connection.
 *
 * @retval MBA_RES_SUCCESS      Successfully restart discovery.
 * @retval MBA_RES_OOM          Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA The connHandle is invalid.
*/
uint16_t BLE_DD_RestartServicesDiscovery(uint16_t connHandle);

/**@} */ //BLE_DD_FUNS
#endif

/**
  @}
*/
