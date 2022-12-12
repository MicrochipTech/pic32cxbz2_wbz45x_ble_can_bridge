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
  BLE Log Middleware Header File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_log.h

  Summary:
    This file contains the BLE Log functions for this project.

  Description:
    This file contains the BLE Log functions for this project.
 *******************************************************************************/


/**
 * @addtogroup BLE_LOG
 * @{
 * @brief Header file for the BLE Log (ble_log) module.
 * @note Definitions and prototypes for the BLE Log application programming interface.
 */

#ifndef BLE_LOG_H
#define BLE_LOG_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include <string.h>
#include "bt_sys_log.h"

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************

/**@addtogroup BLE_LOG_DEFINES Defines
 * @{ */

/**@defgroup BLE_LOG_TYPE Definitions of BLE log
 * @brief The definition of BLE log
 * @{ */
#define BLE_LOG_TYPE_HCI_COMMAND            0x01                                            /**< HCI Command. */
#define BLE_LOG_TYPE_HCI_ACL_TX             0x02                                            /**< HCI ACL Tx Packet. */
#define BLE_LOG_TYPE_HCI_ACL_RX             0x03                                            /**< HCI ACL Rx Packet. */
#define BLE_LOG_TYPE_HCI_EVENT              0x04                                            /**< HCI Event. */
/** @} */


/**@} */ //BLE_LOG_DEFINES

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************

/**@addtogroup BLE_LOG_STRUCTS Structures
 * @{ */

/**@brief BLE_LOG callback type. This callback function sends BLE_LOG events to the application. */
typedef void (*BLE_LOG_EventCb_T)(uint8_t logType, uint16_t logLength, uint8_t *p_logPayload);

/**@} */ //BLE_LOG_STRUCTS

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************

/**@addtogroup BLE_LOG_FUNS Functions
 * @{ */

/**@brief Register BLE_LOG callback.
 *
 * @param[in] eventCb       Client callback function.
*/
void BLE_LOG_EventRegister(BLE_LOG_EventCb_T eventCb);

/**@brief Handling BT_SYS_Log comes from ble_stack lib. BT_SYS_Log is the debug log with ble_stack HCI traffic information.
 *
 * @param[in] p_log         Pointer to @ref BT_SYS_LogEvent_T buffer. 
*/
void BLE_LOG_StackLogHandler(BT_SYS_LogEvent_T *p_log);

/**@} */ //BLE_LOG_FUNS
#endif

/**
  @}
*/

