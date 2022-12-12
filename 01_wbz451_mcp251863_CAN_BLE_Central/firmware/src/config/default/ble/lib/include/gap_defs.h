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
  GAP Definition Header File

  Company:
    Microchip Technology Inc.

  File Name:
    gap_defs.h

  Summary:
    This file contains the GAP definitions.

  Description:
    This file contains the GAP definitions.
 *******************************************************************************/


/**
 *@addtogroup BLE_GAP
 *@{
 *@brief Header file for the BT/BLE Generic Access Profile library.
 * @note Definitions and prototypes for the BT/BLE GAP stack layer application programming interface.
 */
#ifndef GAP_DEFS_H
#define GAP_DEFS_H

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************
/**@addtogroup BLE_GAP_DEFINES Defines
 * @{ */
 
 
/**@defgroup GAP_STATUS Status definitions
 * @brief The definitions list the various possible status.
 * @{ */
#define GAP_STATUS_SUCCESS                                   0x00        /**< Successful status. */
#define GAP_STATUS_UNKNOWN_HCI_COMMAND                       0x01        /**< Unknown HCI Command. */
#define GAP_STATUS_UNKNOWN_CONNECTION_IDENTIFIER             0x02        /**< Unknown Connection Identifier. */
#define GAP_STATUS_HARDWARE_FAILURE                          0x03        /**< Hardware Failure. */
#define GAP_STATUS_PAGE_TIMEOUT                              0x04        /**< Page Timeout. */
#define GAP_STATUS_AUTHENTICATION_FAILURE                    0x05        /**< Authentication Failure. */
#define GAP_STATUS_PIN_KEY_MISSING                           0x06        /**< PIN or Key Missing. */
#define GAP_STATUS_MEMORY_CAPACITY_EXCEEDED                  0x07        /**< Memory Capacity Exceeded. */
#define GAP_STATUS_CONNECTION_TIMEOUT                        0x08        /**< Connection Timeout. */
#define GAP_STATUS_CONNECTION_LIMIT_EXCEEDED                 0x09        /**< Connection Limit Exceeded. */
#define GAP_STATUS_SYNCHRONOUS_CONNECTION_LIMIT_EXCEEDED     0x0A        /**< Synchronous Connection Limit To A Device Exceeded. */
#define GAP_STATUS_CONNECTION_ALREADY_EXISTS                 0x0B        /**< Connection Already Exists. */
#define GAP_STATUS_COMMAND_DISALLOWED                        0x0C        /**< Command Disallowed. */
#define GAP_STATUS_REJECTED_DUE_TO_LIMITED_RESOURCES         0x0D        /**< Connection Rejected due to Limited Resources. */
#define GAP_STATUS_REJECTED_DUE_TO_SECURITY_REASONS          0x0E        /**< Connection Rejected due To Security Reasons. */
#define GAP_STATUS_REJECTED_DUE_TO_UNACCEPTABLE_BDADDR       0x0F        /**< Connection Rejected due to Unacceptable BD_ADDR. */
#define GAP_STATUS_CONNECTION_ACCEPT_TIMEOUT                 0x10        /**< Connection Accept Timeout Exceeded. */
#define GAP_STATUS_UNSUPPORTED_FEATURE                       0x11        /**< Unsupported Feature or Parameter Value. */
#define GAP_STATUS_INVALID_HCI_COMMAND_PARAMETERS            0x12        /**< Invalid HCI Command Parameters. */
#define GAP_STATUS_REMOTE_TERMINATE_CONNECTION               0x13        /**< Remote User Terminated Connection. */
#define GAP_STATUS_REMOTE_TERMINATE_CONNECTION_LOW_RESOURCE  0x14        /**< Remote Device Terminated Connection due to Low Resources. */
#define GAP_STATUS_REMOTE_TERMINATE_CONNECTION_POWEROFF      0x15        /**< Remote Device Terminated Connection due to Power Off. */
#define GAP_STATUS_LOCAL_HOST_TERMINATE_CONNECTION           0x16        /**< Connection Terminated By Local Host. */
#define GAP_STATUS_REPEATED_ATTEMPTS                         0x17        /**< Repeated Attempts. */
#define GAP_STATUS_PAIRING_NOT_ALLOWED                       0x18        /**< Pairing Not Allowed. */
#define GAP_STATUS_UNKNOWN_LMP_PDU                           0x19        /**< Unknown LMP PDU. */
#define GAP_STATUS_UNSUPPORTED_REMOTE_FEATURE                0x1A        /**< Unsupported Remote Feature / Unsupported LMP Feature. */
#define GAP_STATUS_SCO_OFFSET_REJECT                         0x1B        /**< SCO Offset Rejected. */
#define GAP_STATUS_SCO_INTEVAL_REJECT                        0x1C        /**< SCO Interval Rejected. */
#define GAP_STATUS_SCO_AIR_MODE_REJECT                       0x1D        /**< SCO Air Mode Rejected. */
#define GAP_STATUS_INVALID_LMP_PARAMETERS                    0x1E        /**< Invalid LMP Parameters / Invalid LL Parameters. */
#define GAP_STATUS_UNSPECIFIED_ERROR                         0x1F        /**< Unspecified Error. */
#define GAP_STATUS_UNSUPPORTED_LMP_PARAMETERS                0x20        /**< Unsupported LMP Parameter Value / Unsupported LL Parameter Value. */
#define GAP_STATUS_ROLE_CHANGE_NOT_ALLOW                     0x21        /**< Role Change Not Allowed. */
#define GAP_STATUS_LMP_RESPONSE_TIMEOUT                      0x22        /**< LMP Response Timeout / LL Response Timeout. */
#define GAP_STATUS_LMP_ERROR_TRANSACTION_COLLISION           0x23        /**< LMP Error Transaction Collision / LL Procedure Collision. */
#define GAP_STATUS_LMP_PDU_NOT_ALLOW                         0x24        /**< LMP PDU Not Allowed. */
#define GAP_STATUS_ENCRYPTION_MODE_NOT_ACCEPTABLE            0x25        /**< Encryption Mode Not Acceptable. */
#define GAP_STATUS_LINK_KEY_CANNOT_BE_CHANGED                0x26        /**< Link Key cannot be Changed. */
#define GAP_STATUS_REQUESTED_QOS_NOT_SUPPORT                 0x27        /**< Requested QoS Not Supported. */
#define GAP_STATUS_INSTANT_PASSED                            0x28        /**< Instant Passed. */
#define GAP_STATUS_PAIRING_WITH_UNIT_KEY_NOT_SUPPORT         0x29        /**< Pairing With Unit Key Not Supported. */
#define GAP_STATUS_DIFFERENT_TRANSACTION_COLLISION           0x2A        /**< Different Transaction Collision. */
#define GAP_STATUS_RESERVED_FOR_FUTURE_USE1                  0x2B        /**< Reserved for Future Use. */
#define GAP_STATUS_QOS_UNACCEPTABLE_PARAMETER                0x2C        /**< QoS Unacceptable Parameter. */
#define GAP_STATUS_QOS_REJECTED                              0x2D        /**< QoS Rejected. */
#define GAP_STATUS_CHANNEL_CLASSIFICATION_NOT_SUPPORT        0x2E        /**< Channel Classification Not Supported. */
#define GAP_STATUS_INSUFFICIENT_SECURITY                     0x2F        /**< Insufficient Security. */
#define GAP_STATUS_PARAMETER_OUT_OF_MANDATORY_RANGE          0x30        /**< Parameter Out Of Mandatory Range. */
#define GAP_STATUS_RESERVED_FOR_FUTURE_USE2                  0x31        /**< Reserved for Future Use. */
#define GAP_STATUS_ROLE_SWITCH_PENDING                       0x32        /**< Role Switch Pending. */
#define GAP_STATUS_RESERVED_FOR_FUTURE_USE3                  0x33        /**< Reserved for Future Use. */
#define GAP_STATUS_RESERVED_SLOT_VIOLATION                   0x34        /**< Reserved Slot Violation. */
#define GAP_STATUS_ROLE_SWITCH_FAILED                        0x35        /**< Role Switch Failed. */
#define GAP_STATUS_EXTENDED_INQUIRY_RESPONSE_TOO_LARGE       0x36        /**< Extended Inquiry Response Too Large. */
#define GAP_STATUS_SECURE_SIMPLE_PAIRING_NOT_SUPPORT         0x37        /**< Secure Simple Pairing Not Supported By Host. */
#define GAP_STATUS_HOST_BUSY_PAIRING                         0x38        /**< Host Busy - Pairing. */
#define GAP_STATUS_CONNECTION_REJECT_NON_SUITABLE_CHANNEL    0x39        /**< Connection Rejected due to No Suitable Channel Found. */
#define GAP_STATUS_CONTROLLER_BUSY                           0x3A        /**< Controller Busy. */
#define GAP_STATUS_UNACCEPTABLE_CONNECTION_PARAMETERS        0x3B        /**< Unacceptable Connection Parameters. */
#define GAP_STATUS_ADVERTISING_TIMEOUT                       0x3C        /**< Advertising Timeout. */
#define GAP_STATUS_CONNECTION_TERMINATE_MIC_FAILURE          0x3D        /**< Connection Terminated due to MIC Failure. */
#define GAP_STATUS_CONNECTION_FAILED_TO_BE_ESTABLISHED       0x3E        /**< Connection Failed to be Established. */
#define GAP_STATUS_MAC_CONNECTION_FAILED                     0x3F        /**< MAC Connection Failed. */
#define GAP_STATUS_COARSE_CLOCK_ADJUSTMENT_REJECTED          0x40        /**< Coarse Clock Adjustment Rejected but Will Try to Adjust Using Clock Dragging. */
#define GAP_STATUS_TYPE0_SUBMAP_NOT_DEFINED                  0x41        /**< Type0 Submap Not Defined. */
#define GAP_STATUS_UNKNOWN_ADVERTISING_IDENTIFIER            0x42        /**< Unknown Advertising Identifier. */
#define GAP_STATUS_LIMIT_REACHED                             0x43        /**< Limit Reached. */
#define GAP_STATUS_OPERATION_CANCELLED_BY_HOST               0x44        /**< Operation Cancelled by Host. */
/** @} */

/**@defgroup GAP_MAX_ADDRESS_LEN Address length
 * @brief The definition of maximum Bluetooth address length.
 * @{ */
#define GAP_MAX_BD_ADDRESS_LEN                               0x06        /**< Maximum length of BD address . */
/** @} */


/**@defgroup GAP_MAX_DEVICE_NAME_LEN Maximum device name length
 * @brief The definition of maximum length of device name
 * @{ */
#define GAP_MAX_DEVICE_NAME_LEN                              0x20        /**< Maximum length of device name. */
/** @} */


/**@defgroup GAP_DISC_REASON Disconnect reason
 * @brief The definition of disconnection reason.
 * @{ */
#define GAP_DISC_REASON_AUTH_FAIL                            0x05        /**< Authentication failure */
#define GAP_DISC_REASON_REMOTE_TERMINATE                     0x13        /**< Remote User Terminated Connection */
#define GAP_DISC_REASON_LOW_RESOURCES                        0x14        /**< Remote Device Terminated Connection due to Low Resources */
#define GAP_DISC_REASON_POWER_OFF                            0x15        /**< Remote Device Terminated Connection due to Power Off */
#define GAP_DISC_REASON_UNSUPPORTED                          0x1A        /**< Unsupported Remote Feature / Unsupported LMP Feature */
#define GAP_DISC_REASON_KEY_LEN_UNSUPPORTED                  0x29        /**< Pairing with Unit Key Not Supported */
#define GAP_DISC_REASON_UNACCEPTABLE_CP                      0x3B        /**< Unacceptable Connection Parameters */
/** @} */


/**@defgroup GAP_APPEARANCE_DEF Appearance definition
 * @brief The definition of appearance
 * @{ */
#define GAP_APPEARANCE_UNKNOWN                                  0        /**< Unknown. */
#define GAP_APPEARANCE_GENERIC_PHONE                           64        /**< Generic Phone. */
#define GAP_APPEARANCE_GENERIC_COMPUTER                       128        /**< Generic Computer. */
#define GAP_APPEARANCE_GENERIC_WATCH                          192        /**< Generic Watch. */
#define GAP_APPEARANCE_GENERIC_HID                            960        /**< Human Interface Device (HID). */
#define GAP_APPEARANCE_GENERIC_GLUCOSE_METER                 1024        /**< Generic Glucose Meter. */
#define GAP_APPEARANCE_GENERIC_CYCLING                       1152        /**< Generic Cycling. */
#define GAP_APPEARANCE_GENERIC_WEIGHT_SCALE                  3200        /**< Generic Weight Scale. */
/** @} */


/**@} */ //BLE_GAP_DEFINES
#endif


/**
  @}
*/
