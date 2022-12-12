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
  Bluetooth Sys Log Header File

  Company:
    Microchip Technology Inc.

  File Name:
    bt_sys_log.h

  Summary:
    This file contains the BT system log definitions for the project.

  Description:
    This file contains the BT system log definitions for the project.
 *******************************************************************************/


/**
 * @addtogroup BT_SYS
 * @{
 */

#ifndef BT_SYS_LOG_H
#define BT_SYS_LOG_H

/** @defgroup BT_SYS_LOG Bluetooth System Log
 *  @brief This module defines the interface of the Bluetooth system log.
 *  @{ */

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdbool.h>
#include <stdint.h>

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************

/**@addtogroup BT_SYS_LOG_ENUMS Enumerations
 * @{ */

/**@brief Log type. */
typedef enum BT_SYS_LogType_T
{
    BT_SYS_LOG_TYPE_HCI_COMMAND = (0x0100+0x0001),          /**< HCI Command. */
    BT_SYS_LOG_TYPE_HCI_ACL_TX,                             /**< HCI ACL Tx Packet. */
    BT_SYS_LOG_TYPE_HCI_ACL_RX,                             /**< HCI ACL Rx Packet. */
    BT_SYS_LOG_TYPE_HCI_EVENT,                              /**< HCI Event. */
    BT_SYS_LOG_TYPE_HCI_END
} BT_SYS_LogType_T;

/**@} */ //BT_SYS_LOG_ENUMS

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************

/**@addtogroup BT_SYS_LOG_STRUCTS Structures
 * @{ */

/**@brief BT system log callback event. */
typedef struct BT_SYS_LogEvent_T
{
    uint16_t    logType;                            /**< Log type. */
    uint16_t    logId;                              /**< Log ID or connection handle when logType is @ref BT_SYS_LOG_TYPE_HCI_ACL_TX or @ref BT_SYS_LOG_TYPE_HCI_ACL_RX. */
    uint16_t    paramsLength;                       /**< Length of return parameters. Value 0 represents no parameters. */
    uint16_t    payloadLength;                      /**< Length of log payload. */
    uint8_t     *p_logPayload;                      /**< Log payload. Value 0 represents no payload. */
    uint8_t     *p_returnParams;                    /**< Return parameters. */
} BT_SYS_LogEvent_T;

/**@brief BT system log callback type. This callback function sends log events to the application. */
typedef void (*BT_SYS_LogEventCb_T)(BT_SYS_LogEvent_T *p_event);


/**@} */ //BT_SYS_LOG_STRUCTS


/**@addtogroup BT_SYS_LOG_FUNS Functions
 * @{ */

/**@brief The API is used to enable BT log message indication.
 *
 * @param[in] logCb                                 BT system log callback.
 *
 */
void BT_SYS_LogEnable(BT_SYS_LogEventCb_T logCb);

/**@} */ //BT_SYS_LOG_FUNS

/**
  @}
*/

#endif//BT_SYS_LOG_H

/**
  @}
*/
