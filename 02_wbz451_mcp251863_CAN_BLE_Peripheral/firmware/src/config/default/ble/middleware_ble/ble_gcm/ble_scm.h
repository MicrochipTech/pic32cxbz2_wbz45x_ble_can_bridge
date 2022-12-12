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
  BLE Service Change Manager Middleware Header File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_scm.h

  Summary:
    This file contains the BLE Service Change Manager functions and event for application user.

  Description:
    This file contains the BLE Service Change Manager functions and event for application user.
    The "BLE_SCM_Init" function shall be called in the "APP_Initialize" function to 
    initialize the this modules in the system.
 *******************************************************************************/


/**
 * @addtogroup BLE_SCM
 * @{
 * @brief Header file for the BLE Service Change Manager (ble_scm) module.
 * @note Definitions and prototypes for the BLE Service Change Manager application programming interface.
 */
 
#ifndef BLE_SCM_H
#define BLE_SCM_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include "stack_mgr.h"
#include "ble_dd.h"

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************

/**@addtogroup BLE_SCM_DEFINES Defines
 * @{ */
 
/**@defgroup BLE_SCM_DISC_NUM Number of discovering characteristics of GATT service
 * @brief The definition of number of characteristics
 * @{ */
#define BLE_SCM_GATT_DISC_CHAR_NUM                  0x03    /**< Number of characteristic to discovery of GATT Service. */
/** @} */

/**@} */ //BLE_SCM_DEFINES


/**@addtogroup BLE_SCM_ENUMS Enumerations
 * @{ */

/**@brief The definition of BLE_SCM module event ID. */
typedef enum BLE_SCM_EventId_T
{
    BLE_SCM_EVT_SVC_CHANGE,                 /**< Receive service change indication from remote. @ref BLE_SCM_EvtServiceChange_T */
    BLE_SCM_EVT_BONDED_CHAR_INFO,           /**< Characteristic handles information of GATT Service of remote bonded device. Application needs to take care the bonded information. e.g., storing information to persistent storage. @ref BLE_SCM_EvtBondedCharInfo_T. */
    BLE_SCM_EVT_CONFIGURED,                 /**< Generated when GATT client configure procedures are done. @ref BLE_SCM_EvtConfigured_T. */
    BLE_SCM_EVT_DISC_COMPLETE,              /**< Generated when discovery of GATT service of remote connection is completed. @ref BLE_SCM_EvtDiscComplete_T. */
    BLE_SCM_EVT_END
}BLE_SCM_EventId_T;

/**@} */ //BLE_SCM_ENUMS

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/**@addtogroup BLE_SCM_STRUCTS Structures
 * @{ */

/**@brief Data structure for @ref BLE_SCM_EVT_BONDED_CHAR_INFO event. */
typedef struct BLE_SCM_EvtBondedCharInfo_T
{
    uint16_t                    connHandle;                             /**< Connection handle associated with this connection. */
    BLE_DD_CharInfo_T           charInfo[BLE_SCM_GATT_DISC_CHAR_NUM];   /**< Characteristic information of GATT service of this bonded remote peer. */
} BLE_SCM_EvtBondedCharInfo_T;

/**@brief Data structure for @ref BLE_SCM_EVT_SVC_CHANGE event. */
typedef struct BLE_SCM_EvtServiceChange_T
{
    uint16_t                    connHandle;                             /**< Connection handle associated with this connection. */
    uint16_t                    scStartHandle;                          /**< Start attribute handle of service change at remote. */
    uint16_t                    scEndHandle;                            /**< End attribute handle of service change at remote. */
} BLE_SCM_EvtServiceChange_T;

/**@brief Data structure for @ref BLE_SCM_EVT_CONFIGURED event. */
typedef struct BLE_SCM_EvtConfigured_T
{
    uint16_t                    connHandle;                             /**< Connection handle associated with this connection. */
} BLE_SCM_EvtConfigured_T;

/**@brief Data structure for @ref BLE_SCM_EVT_DISC_COMPLETE event. */
typedef struct BLE_SCM_EvtDiscComplete_T
{
    uint16_t                    connHandle;                             /**< Connection handle associated with this connection. */
} BLE_SCM_EvtDiscComplete_T;

/**@brief Union of BLE_SCM callback event data types. */
typedef union
{
    BLE_SCM_EvtServiceChange_T  evtServiceChange;                       /**< Handle @ref BLE_SCM_EVT_SVC_CHANGE. */
    BLE_SCM_EvtBondedCharInfo_T evtBondedCharInfo;                      /**< Handle @ref BLE_SCM_EVT_BONDED_CHAR_INFO. */
    BLE_SCM_EvtConfigured_T     evtConfigured;                          /**< Handle @ref BLE_SCM_EVT_CONFIGURED. */
    BLE_SCM_EvtDiscComplete_T   evtDiscComplete;                        /**< Handle @ref BLE_SCM_EVT_DISC_COMPLETE. */
} BLE_SCM_EventField_T;

/**@brief BLE_SCM callback event. */
typedef struct  BLE_SCM_Event_T
{
    BLE_SCM_EventId_T           eventId;                                /**< Event ID.*/
    BLE_SCM_EventField_T        eventField;                             /**< Event field. */
} BLE_SCM_Event_T;

/**@brief BLE_SCM callback type. This callback function sends BLE_SCM events to the application. */
typedef void (*BLE_SCM_EventCb_T)(BLE_SCM_Event_T *p_event);

/**@} */ //BLE_SCM_STRUCTS

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************
/**@addtogroup BLE_SCM_FUNS Functions
 * @{ */

/**@brief Initialize BLE_SCM module.
 *
 * @note This module is required only when GATT client is supported and service change status needs to be taken care at remote.
 * @note This module required BLE_DD supported.
 *
*/
void BLE_SCM_Init();

/**@brief Register BLE_SCM callback.
 * @note This API should be called in the application initialization routine
 *
 * @param[in] eventCb           Client callback function.
 *
*/
void BLE_SCM_EventRegister(BLE_SCM_EventCb_T eventCb);

/**@brief Handle BLE events
 * @note  This function should be called for every BLE event
 *
 * @param[in] p_stackEvent      Pointer to @ref STACK_Event_T structure buffer.
 *
*/
void BLE_SCM_BleEventHandler(STACK_Event_T *p_stackEvent);

/**@brief Handle BLE_DD events
 * @note  This function should be called for every BLE_DD event
 *
 * @param[in] p_event           Pointer to @ref BLE_DD_Event_T structure buffer.
 *
*/
void BLE_SCM_BleDdEventHandler(BLE_DD_Event_T *p_event);

/**@brief Set characteristics handles information of bonded connection.
 * @note  Application help to cache handle information and set back to BLE_SCM when bonded link connected.
 *
 * @param[in] connHandle        Connection handle associated with this connection.
 * @param[in] p_charInfo        Point to the characteristic information of GATT service of this bonded remote peer. The maximum number is @ref BLE_SCM_GATT_DISC_CHAR_NUM.
 *
*/
void BLE_SCM_SetBondedCharInfo(uint16_t connHandle, BLE_DD_CharInfo_T *p_charInfo);

/**@} */ //BLE_SCM_FUNS

#endif

/**
  @}
*/
