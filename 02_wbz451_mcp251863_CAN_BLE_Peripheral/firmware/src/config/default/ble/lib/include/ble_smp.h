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
  BLE SMP Header File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_smp.h

  Summary:
    This file contains the BLE SMP functions for application user.

  Description:
    This file contains the BLE SMP functions and event for application user.  The
    "BLE_SMP_Init" function shall be called in the "APP_Initialize" function to 
    initialize the this modules in the system
 *******************************************************************************/


/**
 * @addtogroup BLE_SMP
 * @{
 * @brief Header file for the BLE Security Manager library.
 * @note Definitions and prototypes for the BLE SMP stack layer application programming interface.
 */
#ifndef BLE_SMP_H
#define BLE_SMP_H

#include "ble_gap.h"
// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************

/**@addtogroup BLE_SMP_DEFINESS Defines
 * @{ */
 
/**@defgroup BLE_SMP_IO_CAPABILITY_DEF IO capability
 * @brief The definition of SMP IO Capabilities
 * @{ */
#define BLE_SMP_IO_DISPLAYONLY                              0x00        /**< Device has the ability to display or communicate a 6 digit decimal number but does not have the ability to indicate yes or no. */
#define BLE_SMP_IO_DISPLAYYESNO                             0x01        /**< Device has at least two buttons that can be easily mapped to yes and no and also has the ability to display or communicate a 6 digit decimal number. */
#define BLE_SMP_IO_KEYBOARDONLY                             0x02        /**< Device has a numeric keyboard that can input the numbers 0 through 9 and a confirmation but does not have the ability to display or communicate a 6 digit decimal number. */
#define BLE_SMP_IO_NOINPUTNOOUTPUT                          0x03        /**< Device does not have the abilities to indicate yes or no and display or communicate a 6 digit decimal number. */
#define BLE_SMP_IO_KEYBOARDDISPLAY                          0x04        /**< Device has a numeric keyboard that can input the numbers 0 through 9 and a confirmation and has the ability to display or communicate a 6 digit decimal number. */
/** @} */


/**@defgroup BLE_SMP_OPTION Pairing options
 * @brief The definition of pairing options
 * @note Possible combinations are :
 * - BLE_SMP_OPTION_NONE : No bonding, LE legacy pairing is used
 * - BLE_SMP_OPTION_BONDING    : Bonding requested, LE legacy pairing is used
 * - BLE_SMP_OPTION_SECURE_CONNECTION : No Bonding. If both devices support LE Secure Connections, use LE
 *                                                                  Secure Connections; otherwise use LE legacy pairing.
 * - BLE_SMP_OPTION_BONDING | BLE_SMP_OPTION_SECURE_CONNECTION : Bonding Requested. If both devices support LE Secure Connections, use LE
 *                                                               Secure Connections; otherwise use LE legacy pairing.
 * - BLE_SMP_OPTION_MITM : No bonding, LE legacy pairing is used. MITM protection is required.
 * - BLE_SMP_OPTION_BONDING | BLE_SMP_OPTION_MITM : Bonding requested, LE legacy pairing is used. MITM protection is required.
 * - BLE_SMP_OPTION_MITM | BLE_SMP_OPTION_SECURE_CONNECTION : No Bonding. MITM protection is required. If both devices support LE Secure Connections, use LE
 *                                                                                        Secure Connections; otherwise use LE legacy pairing.
 * - BLE_SMP_OPTION_BONDING | BLE_SMP_OPTION_MITM | BLE_SMP_OPTION_SECURE_CONNECTION : Bonding Requested. MITM protection is required. If both devices support LE Secure Connections, use LE
 *                                                                                     Secure Connections; otherwise use LE legacy pairing. 
 * - BLE_SMP_OPTION_SECURE_CONNECTION | BLE_SMP_OPTION_KEYPRESS : No Bonding. If both devices support LE Secure Connections, use LE
 *                                                                  Secure Connections; otherwise use LE legacy pairing.
 *                                                                  Enable keypress notifications.
 * - BLE_SMP_OPTION_BONDING | BLE_SMP_OPTION_SECURE_CONNECTION | BLE_SMP_OPTION_KEYPRESS : Bonding Requested. If both devices support LE Secure Connections, use LE
 *                                                               Secure Connections; otherwise use LE legacy pairing.
 *                                                               Enable keypress notifications.
 * - BLE_SMP_OPTION_MITM | BLE_SMP_OPTION_SECURE_CONNECTION | BLE_SMP_OPTION_KEYPRESS : No Bonding. MITM protection is required. If both devices support LE Secure Connections, use LE
 *                                                                                        Secure Connections; otherwise use LE legacy pairing.
 *                                                                                        Enable keypress notifications.
 * - BLE_SMP_OPTION_BONDING | BLE_SMP_OPTION_MITM | BLE_SMP_OPTION_SECURE_CONNECTION | BLE_SMP_OPTION_KEYPRESS : Bonding Requested. MITM protection is required. If both devices support LE Secure Connections, use LE
 *                                                                                                               Secure Connections; otherwise use LE legacy pairing. 
 *                                                                                                               Enable keypress notifications.
 *
 * @{ */
#define BLE_SMP_OPTION_NONE                                 0x00        /**< Do not allow a bond to be created with a peer device. The keys are not stored*/
#define BLE_SMP_OPTION_BONDING                              0x01        /**< Allows two connected devices to exchange and store security and identity information to create a trusted relationship . */
#define BLE_SMP_OPTION_MITM                                 0x04        /**< Request MITM protection. */
#define BLE_SMP_OPTION_SECURE_CONNECTION                    0x08        /**< Request LE Secure Connections pairing. */
#define BLE_SMP_OPTION_KEYPRESS                             0x10        /**< Enable keypress notifications. */
/** @} */


/**@defgroup BLE_SMP_CONFIRM Confirm result
 * @brief The definition of user confirm result
 * @{ */
#define BLE_SMP_CONFIRM_YES                                 0x00        /**< User confirms "YES". */
#define BLE_SMP_CONFIRM_NO                                  0x01        /**< User confirms "NO". */
/** @} */


/**@defgroup BLE_SMP_PAIRING_RESULT Pairing result
 * @brief The definition of pairing result
 * @{ */
#define BLE_SMP_PAIRING_SUCCESS                             0x00        /**< Pairing process is successful. */
#define BLE_SMP_PAIRING_FAIL                                0x01        /**< Pairing process failed. */
#define BLE_SMP_PAIRING_TIMEOUT                             0x02        /**< Pairing process timeout. */
/** @} */

/**@defgroup BLE_SMP_PAIRING_FAIL_REASON Pairing fail reason
 * @brief The definition of the reason for pairing fail.
 * @{ */
#define BLE_SMP_REASON_PASSKEY_ENTRY_FAILED                 0x01        /**< The user input of passkey failed. */
#define BLE_SMP_REASON_OOB_NOT_AVAILABLE                    0x02        /**< The OOB data is not available. */
#define BLE_SMP_REASON_AUTH_REQ                             0x03        /**< Authentication requirements cannot be met due to IO capabilities of one or both devices. */
#define BLE_SMP_REASON_CONFIRM_VALUE_FAILED                 0x04        /**< The confirm value does not match. */
#define BLE_SMP_REASON_PAIRING_NOT_SUPPORTED                0x05        /**< Pairing is not supported by the device. */
#define BLE_SMP_REASON_ENCRYPT_KEY_SIZE                     0x06        /**< Encryption key size is insufficient. */
#define BLE_SMP_REASON_COMMAND_NOT_SUPPORTED                0x07        /**< The SMP command received is not supported on this device. */
#define BLE_SMP_REASON_UNSPECIFIED_REASON                   0x08        /**< Pairing failed due to an unspecified reason. */
#define BLE_SMP_REASON_REPEATED_ATTEMPTS                    0x09        /**< Too little time has elapsed since last pairing request or security request. */
#define BLE_SMP_REASON_INVALID_PARAMETERS                   0x0A        /**< The command length is invalid. */
#define BLE_SMP_REASON_DHKEY_CHECK_FAILED                   0x0B        /**< DHKey Check value received doesnâ??t match the one calculated by the local device. */
#define BLE_SMP_REASON_NUMERIC_COMPARISON_FAILED            0x0C        /**< The confirm values in the numeric comparison protocol do not match. */
/** @} */


/**@defgroup BLE_SMP_FLAG_KEY_VALID Key flags
 * @brief The definition of valid remote keys flag
 * @{ */
#define BLE_SMP_FLAG_ENCRYPT_INFO                           (1<<0)      /**< Indicate LTK is valid. */
#define BLE_SMP_FLAG_CENTRAL_ID                             (1<<1)      /**< Indicate EDIV and Rand are valid. */
#define BLE_SMP_FLAG_ID_INFO                                (1<<2)      /**< Indicate IRK is valid. */
#define BLE_SMP_FLAG_ID_ADDR_INFO                           (1<<3)      /**< Indicate identity address is valid. */
#define BLE_SMP_FLAG_SIGNING_INFO                           (1<<4)      /**< Indicate SRK is valid. */
/** @} */

/**@defgroup BLE_SMP_KEYPRESS_NOTI_TYPE Keypress notification type
 * @brief The definition of keypress notification type
 * @{ */
#define BLE_SMP_KEYPRESS_STARTED                            0x00        /**< Passkey entry started. */
#define BLE_SMP_KEYPRESS_DIGIT_ENTERED                      0x01        /**< Passkey digit entered. */
#define BLE_SMP_KEYPRESS_DIGIT_ERASED                       0x02        /**< Passkey digit erased. */
#define BLE_SMP_KEYPRESS_CLEARED                            0x03        /**< Passkey cleared. */
#define BLE_SMP_KEYPRESS_COMPLETED                          0x04        /**< Passkey entry completed. */
/** @} */


/**@} */ //BLE_SMP_DEFINES

/**@addtogroup BLE_SMP_ENUMS Enumerations
 * @{ */
 
/** @brief Enumeration type of BLE SMP callback events.*/
typedef enum BLE_SMP_EventId_T
{
    BLE_SMP_EVT_PAIRING_COMPLETE,                                       /**< Pairing process is completed event. See @ref BLE_SMP_EvtPairingComplete_T structure for eventField. */
    BLE_SMP_EVT_SECURITY_REQUEST,                                       /**< Received peripheral security request from remote device event. See @ref BLE_SMP_EvtSecurityReq_T structure for eventField. */
    BLE_SMP_EVT_NUMERIC_COMPARISON_CONFIRM_REQUEST,                     /**< Received confirmation request for 6-digit values during pairing process (Numeric comparison) event. See @ref BLE_SMP_EvtDisplayCompareValueReq_T structure for eventField. */
    BLE_SMP_EVT_INPUT_PASSKEY_REQUEST,                                  /**< Passkey is requested to be input during pairing process (Passkey entry) event. See @ref BLE_SMP_EvtInputPasskeyReq_T structure for eventField. */
    BLE_SMP_EVT_DISPLAY_PASSKEY_REQUEST,                                /**< Request to display passkey during pairing process (Passkey entry) event. See @ref BLE_SMP_EvtDisplayPasskeyReq_T structure for eventField. */
    BLE_SMP_EVT_NOTIFY_KEYS,                                            /**< Notify keys. See @ref BLE_SMP_EvtNotifyKeys_T structure for eventField. */        
    BLE_SMP_EVT_PAIRING_REQUEST,                                        /**< Received pairing request from remote device event. See @ref BLE_SMP_EvtPairingReq_T structure for eventField. */
    BLE_SMP_EVT_INPUT_OOB_DATA_REQUEST,                                 /**< OOB data for legacy pairing is requested to be input during pairing process (Out of Band) event. See @ref BLE_SMP_EvtInputOobData_T structure for eventField. */
    BLE_SMP_EVT_INPUT_SC_OOB_DATA_REQUEST,                              /**< OOB data for Secure Connections pairing is requested to be input during pairing process (Out of Band) event. See @ref BLE_SMP_EvtInputScOobData_T structure for eventField. */
    BLE_SMP_EVT_KEYPRESS,                                               /**< Keypress notification from the remote device. See @ref BLE_SMP_EvtKeypress_T structure for eventField. */
    BLE_SMP_EVT_GEN_SC_OOB_DATA_DONE                                    /**< Generate SC OOB data is completed event. See @ref BLE_SMP_EvtGenScOobDataDone_T structure for eventField. */
}BLE_SMP_EventId_T;
/**@} */ //BLE_SMP_ENUMS

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

/**@addtogroup BLE_SMP_STRUCTS Structures
 * @{ */
 
/**@brief Pairing parameters. */
typedef struct BLE_SMP_Config_T
{
    uint8_t ioCapability;                                               /**< Input and output capabilities of a device handle. See @ref BLE_SMP_IO_CAPABILITY_DEF. */
    uint8_t authReqFlag;                                                /**< Authentication Requirement Flag. See @ref BLE_SMP_OPTION. */
    bool    oobDataFlag;                                                /**< OOB data flag. 
                                                                             - In LE legacy pairing, set true to indicate device has OOB authentication data.
                                                                             If both devices have OOB authentication data, then OOB pairing method shall be used.
                                                                             - In LE Secure Connections pairing, set true to indicate device has the OOB authentication data from remote device.
                                                                             If one or both devices have the OOB authentication data from remote device, then OOB pairing method shall be used. */
    bool    scOnly;                                                     /**< Secure Connections only mode. Set true to enable secure connection only mode. */
    bool    authPairingRequired;                                        /**< Set true if authenticated pairing method is required. If local device plays as peripheral role in the connection and the final mapping method in pairing is unauthenticated.  Then pairing fail packet will be issued automatically after receiving pairing request packet. */
}BLE_SMP_Config_T;

/** @brief Pairing information.*/
typedef struct BLE_SMP_PairInfo_T
{
    uint8_t                 auth:1;                                     /**< Set true if it's authenticated pairing */
    uint8_t                 lesc:1;                                     /**< Set true if key is generated by using LE security connection */
    uint8_t                 reserve:6;                                  /**< Reserved */
}BLE_SMP_PairInfo_T;


/** @brief Encryption information.*/
typedef struct BLE_SMP_EncInfo_T
{
    uint8_t                 ltk[16];                                    /**< The long term key */
    uint8_t                 ediv[2];                                    /**< The encrypted diversifier value */
    uint8_t                 rand[8];                                    /**< The randon number value */
    uint8_t                 lesc:1;                                     /**< Key generated using LE security connection */
    uint8_t                 auth:1;                                     /**< Is Authenticated Key? */
    uint8_t                 ltkLen:6;                                   /**< The LTK length in bytes */
}BLE_SMP_EncInfo_T;

/** @brief Identity information.*/
typedef struct BLE_SMP_IdInfo_T
{
    uint8_t                 irk[16];                                    /**< The identity resolving key */
    BLE_GAP_Addr_T          addr;                                       /**< The identity address */
}BLE_SMP_IdInfo_T;

/** @brief Signing information.*/
typedef struct BLE_SMP_SignInfo_T
{
    uint8_t                 srk[16];                                    /**< The signature resolving key*/
}BLE_SMP_SignInfo_T;

/** @brief Security keys.*/
typedef struct BLE_SMP_SecKeys_T
{
    BLE_SMP_EncInfo_T       encInfo;                                    /**< The encryption information */
    BLE_SMP_IdInfo_T        idInfo;                                     /**< The identity information */
    BLE_SMP_SignInfo_T      signInfo;                                   /**< The signing information */
}BLE_SMP_SecKeys_T;

/** @brief Key list.*/
typedef struct BLE_SMP_KeyList_T
{
    BLE_SMP_SecKeys_T       local;                                      /**< Local security keys */
    BLE_SMP_SecKeys_T       remote;                                     /**< Remote security keys */
} BLE_SMP_KeyList_T;


/**@brief Data structure for @ref BLE_SMP_EVT_PAIRING_COMPLETE event. */
typedef struct  BLE_SMP_EvtPairingComplete_T
{
    uint16_t                connHandle;                                 /**< Connection handle associated with this connection. */
    uint8_t                 status;                                     /**< Status of pairing procedure. See @ref BLE_SMP_PAIRING_RESULT. */
    uint8_t                 failReason;                                 /**< The failReason field indicates why the pairing failed if the status is BLE_SMP_PAIRING_FAIL. See @ref BLE_SMP_PAIRING_FAIL_REASON. */
    bool                    bond;                                       /**< The remote is bonded or not */
    uint8_t                 encryptKey[16];                             /**< Encryption key associated with this connection.*/    
    BLE_SMP_SecKeys_T       local;                                      /**< Local security keys */
    BLE_SMP_SecKeys_T       remote;                                     /**< Remote security keys */

} BLE_SMP_EvtPairingComplete_T;


/**@brief Data structure for @ref BLE_SMP_EVT_NUMERIC_COMPARISON_CONFIRM_REQUEST event.  */
typedef struct  BLE_SMP_EvtDisplayCompareValueReq_T
{
    uint16_t                connHandle;                                 /**< Connection handle associated with this connection. */
    uint8_t                 value[6];                                   /**< 6-digit confirmation value that users needs to match and confirm. The value is in ASCII format. */
} BLE_SMP_EvtDisplayCompareValueReq_T;


/**@brief Data structure for @ref BLE_SMP_EVT_DISPLAY_PASSKEY_REQUEST event.  */
typedef struct  BLE_SMP_EvtDisplayPasskeyReq_T
{
    uint16_t                connHandle;                                 /**< Connection handle associated with this connection. */
} BLE_SMP_EvtDisplayPasskeyReq_T;


/**@brief Data structure @ref BLE_SMP_EVT_INPUT_PASSKEY_REQUEST event */
typedef struct  BLE_SMP_EvtInputPasskeyReq_T
{
    uint16_t                connHandle;                                 /**< Connection handle associated with this connection. */
    bool                    keypress;                                   /**< Is required to inform the remote device when keys have been entered or erased.
                                                                             If this is true, please using @ref BLE_SMP_Keypress to send keypress notifications. */
} BLE_SMP_EvtInputPasskeyReq_T;


/**@brief Data structure for @ref BLE_SMP_EVT_INPUT_OOB_DATA_REQUEST event. */
typedef struct  BLE_SMP_EvtInputOobData_T
{
    uint16_t                connHandle;                                 /**< Connection handle associated with this connection. */
} BLE_SMP_EvtInputOobData_T;

/**@brief Data structure for @ref BLE_SMP_EVT_INPUT_SC_OOB_DATA_REQUEST event. */
typedef struct  BLE_SMP_EvtInputScOobData_T
{
    uint16_t                connHandle;                                 /**< Connection handle associated with this connection. */
} BLE_SMP_EvtInputScOobData_T;


/**@brief Data structure for @ref BLE_SMP_EVT_SECURITY_REQUEST event. */
typedef struct  BLE_SMP_EvtSecurityReq_T
{
    uint16_t                connHandle;                                 /**< Connection handle associated with this connection. */
    uint8_t                 authReq;                                    /**< Authentication requirement flag. See @ref BLE_SMP_OPTION. */
} BLE_SMP_EvtSecurityReq_T;

/**@brief Data structure for @ref BLE_SMP_EVT_NOTIFY_KEYS event. */
typedef struct  BLE_SMP_EvtNotifyKeys_T
{
    uint16_t                connHandle;                                 /**< Connection handle associated with this connection. */
    BLE_SMP_KeyList_T       keys;                                       /**< Keys associated with this connection. */
} BLE_SMP_EvtNotifyKeys_T;


/**@brief Data structure for @ref BLE_SMP_EVT_PAIRING_REQUEST) event. */
typedef struct  BLE_SMP_EvtPairingReq_T
{
    uint16_t                connHandle;                                 /**< Connection handle associated with this connection. */
    uint8_t                 authReq;                                    /**< Authentication requirement flag. See @ref BLE_SMP_OPTION. */
} BLE_SMP_EvtPairingReq_T;

/**@brief Data structure for @ref BLE_SMP_EVT_KEYPRESS event. */
typedef struct  BLE_SMP_EvtKeypress_T
{
    uint16_t                connHandle;                                 /**< Connection handle associated with this connection. */
    uint8_t                 notifyType;                                 /**< Notification type. See @ref BLE_SMP_KEYPRESS_NOTI_TYPE. */
} BLE_SMP_EvtKeypress_T;

/**@brief Data structure for @ref BLE_SMP_EVT_GEN_SC_OOB_DATA_DONE event. */
typedef struct  BLE_SMP_EvtGenScOobDataDone_T
{
    uint8_t                 confirm[16];                                /**< The Confirm Value. */
    uint8_t                 rand[16];                                   /**< The Random Number. */
} BLE_SMP_EvtGenScOobDataDone_T;


/**@brief Union of BLE SMP callback event data types. */
typedef union
{
    BLE_SMP_EvtPairingComplete_T         evtPairingComplete;            /**< Handle @ref BLE_SMP_EVT_PAIRING_COMPLETE. */
    BLE_SMP_EvtInputPasskeyReq_T         evtInputPasskeyReq;            /**< Handle @ref BLE_SMP_EVT_INPUT_PASSKEY_REQUEST. */
    BLE_SMP_EvtDisplayCompareValueReq_T  evtDisplayCompareValueReq;     /**< Handle @ref BLE_SMP_EVT_NUMERIC_COMPARISON_CONFIRM_REQUEST. */
    BLE_SMP_EvtDisplayPasskeyReq_T       evtDisplayPasskeyReq;          /**< Handle @ref BLE_SMP_EVT_DISPLAY_PASSKEY_REQUEST. */
    BLE_SMP_EvtSecurityReq_T             evtSecurityReq;                /**< Handle @ref BLE_SMP_EVT_SECURITY_REQUEST. */
    BLE_SMP_EvtNotifyKeys_T              evtNotifyKeys;                 /**< Handle @ref BLE_SMP_EVT_NOTIFY_KEYS. */
    BLE_SMP_EvtPairingReq_T              evtPairingReq;                 /**< Handle @ref BLE_SMP_EVT_PAIRING_REQUEST. */
    BLE_SMP_EvtInputOobData_T            evtInputOobData;               /**< Handle @ref BLE_SMP_EVT_INPUT_OOB_DATA_REQUEST. */
    BLE_SMP_EvtInputScOobData_T          evtInputScOobData;             /**< Handle @ref BLE_SMP_EVT_INPUT_SC_OOB_DATA_REQUEST. */
    BLE_SMP_EvtKeypress_T                evtKeypress;                   /**< Handle @ref BLE_SMP_EVT_KEYPRESS. */
    BLE_SMP_EvtGenScOobDataDone_T        evtGenScOobDataDone;           /**< Handle @ref BLE_SMP_EVT_GEN_SC_OOB_DATA_DONE. */
} BLE_SMP_EventField_T;

/**@brief BLE SMP callback event. */
typedef struct  BLE_SMP_Event_T
{
    BLE_SMP_EventId_T       eventId;                                    /**< Event ID. */
    BLE_SMP_EventField_T    eventField;                                 /**< Event field. */
} BLE_SMP_Event_T;

/**@} */ //BLE_SMP_STRUCTS

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************
/**@addtogroup BLE_SMP_FUNS Functions
 * @{ */
 
/**@brief Initialize BLE SMP main module.
 *
 * @retval MBA_RES_SUCCESS                  Successfully initialize the BLE SMP main module.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
*/
uint16_t BLE_SMP_Init();


/**@brief Configure SMP pairing parameters. 
 * @note  MITM (man-in-the-middle protection) is requested if ioCapability is other than NoInputNoOutput.
 *        If this API is not called then following are the defaults:
 *        - ioCapability : @ref BLE_SMP_IO_NOINPUTNOOUTPUT
 *        - oob: Set false to indicate device does not have OOB authentication data
 *        - authReqFlag : @ref BLE_SMP_OPTION_BONDING | @ref BLE_SMP_OPTION_SECURE_CONNECTION
 *        - scOnly: Set true to enable LE secure connection only
 *
 * @param[in] p_config                      Pointer to the @ref BLE_SMP_Config_T structure buffer.
 *
 * @retval MBA_RES_SUCCESS                  Successfully configure SMP pairing parameters.
 * @retval MBA_RES_INVALID_PARA             The configured parameter(s) is/are invalid.
 */
uint16_t BLE_SMP_Config(BLE_SMP_Config_T * p_config);


/**@brief Reply to a passkey request event with passkey information.
 * @note  The API should be called in response to passkey entry request or passkey display request.
 *        Hence, it should be called in SMP callback function when @ref BLE_SMP_EVT_INPUT_PASSKEY_REQUEST event or
 *        @ref BLE_SMP_EVT_DISPLAY_PASSKEY_REQUEST event is generated.
 *        These events are received only when passkey entry method is selected for pairing (LE secure connections or Legacy pairing).\n
 *
 * @par Events generated
 *      This API is called during pairing procedure, please see the events generated of @ref BLE_SMP_InitiatePairing.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] p_passkey                     Pointer to the passkey buffer. The length of passkey should be 6 bytes in ASCII format.
 *
 * @retval MBA_RES_SUCCESS                  Successfully reply with passkey for pairing process.
 * @retval MBA_RES_FAIL                     The specified connection handle is invalid.
 */
uint16_t BLE_SMP_PasskeyReply(uint16_t connHandle, uint8_t *p_passkey);


/**@brief Reply to a passkey request event if local device cannot provide the information.
 * @note  The API should be called in response to passkey entry request or passkey display request.
 *        Hence, it should be called in SMP callback function when @ref BLE_SMP_EVT_INPUT_PASSKEY_REQUEST event or
 *        @ref BLE_SMP_EVT_DISPLAY_PASSKEY_REQUEST event is generated.
 *        These events are received only when passkey entry method is selected for pairing (LE secure connections or Legacy pairing).\n
 *
 * @par Events generated
 *      This API is called during pairing procedure, please see the events generated of @ref BLE_SMP_InitiatePairing.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 *
 * @retval MBA_RES_SUCCESS                  Successfully reply passkey is not available.
 * @retval MBA_RES_FAIL                     The specified connection handle is invalid.
 */
uint16_t BLE_SMP_PasskeyNegativeReply(uint16_t connHandle);


/**@brief Confirm the confirmation value between two devices.
 * @note  Only valid while pairing method is numeric comparison. (Only used for LE secure connections).
 *        The API should be called when user confirmation request event is generated
 *        (@ref BLE_SMP_EVT_NUMERIC_COMPARISON_CONFIRM_REQUEST)
 *        If user confirmation (outcome) is Yes then Pairing continues else pairing process ends in a failure.
 *
 * @par Events generated
 *      This API is called during pairing procedure, please see the events generated of @ref BLE_SMP_InitiatePairing.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] outcome                       See @ref BLE_SMP_CONFIRM. The result of user confirm.
 *
 * @retval MBA_RES_SUCCESS                  Successfully sent user confirmation (Yes or No).
 * @retval MBA_RES_INVALID_PARA             Outcome is invalid (other than Yes or No). See @ref BLE_SMP_CONFIRM
 * @retval MBA_RES_FAIL                     The specified connection handle is invalid.
 */
uint16_t BLE_SMP_NumericComparisonConfirmReply(uint16_t connHandle, uint8_t outcome);


/**@brief Send the OOB data for pairing process. The API should be called in response to OOB data request.
 *        Hence, it should be called in SMP callback function when @ref BLE_SMP_EVT_INPUT_OOB_DATA_REQUEST event is generated.
 *        These events are received only when OOB method is selected for Legacy pairing.
 *@note
 *        - If event @ref BLE_SMP_EVT_INPUT_OOB_DATA_REQUEST is received then the OOB data may be generated by application.
 *
 * @par Events generated
 *      This API is called during pairing procedure, please see the events generated of @ref BLE_SMP_InitiatePairing.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] p_oobData                     Pointer to the OOB data. Set NULL if local device cannot provide the information. The length of OOB data should be 16 bytes key value.
 *
 * @retval MBA_RES_SUCCESS                  Successfully replied with passkey for pairing process.
 * @retval MBA_RES_FAIL                     The specified connection handle is invalid.
 * @retval MBA_RES_BAD_STATE                The OOB data for Secure Connections if requested. It should call @ref BLE_SMP_ScOobDataReply to reply OOB data.
 */
uint16_t BLE_SMP_OobDataReply(uint16_t connHandle, uint8_t *p_oobData);


/**@brief Send the OOB data for pairing process. The API should be called in response to OOB data request.
 *        Hence, it should be called in SMP callback function when @ref BLE_SMP_EVT_INPUT_SC_OOB_DATA_REQUEST event is generated.
 *        These events are received only when OOB method is selected for LE Secure Connections pairing.
 *@note
 *        - If event @ref BLE_SMP_EVT_INPUT_SC_OOB_DATA_REQUEST is received then the OOB data may be generated by application.
 *
 * @par Events generated
 *      This API is called during pairing procedure, please see the events generated of @ref BLE_SMP_InitiatePairing.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] p_confirm                     Pointer to the Confirm Value. Set NULL if local device cannot provide the information. The length of Confirm Value should be 16 bytes value.
 * @param[in] p_rand                        Pointer to the Random Number. Set NULL if local device cannot provide the information. The length of Random Number should be 16 bytes value.
 *
 * @retval MBA_RES_SUCCESS                  Successfully replied with the OOB data for pairing process.
 * @retval MBA_RES_FAIL                     The specified connection handle is invalid.
 * @retval MBA_RES_BAD_STATE                The OOB data for Legacy pairing if requested. It should call @ref BLE_SMP_OobDataReply to reply OOB data.
 */
uint16_t BLE_SMP_ScOobDataReply(uint16_t connHandle, uint8_t *p_confirm, uint8_t *p_rand);


/**@brief Generate the OOB data for the next LE Secure Connections pairing process.
 *        The API should be called and wait @ref BLE_SMP_EVT_GEN_SC_OOB_DATA_DONE event before starting pairing.
 *        Hence, it is better be called before connection is established.
 *@note
 *        - The OOB data may be send by application.
 *
 * @par Events generated
 *      When the SC OOB data is generated successfully, the @ref BLE_SMP_EVT_GEN_SC_OOB_DATA_DONE event is generated.
 *
 * @retval MBA_RES_SUCCESS                  Successfully start to generate the SC OOB data for pairing process.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_BUSY                     Generation fail due to SMP is busy.
 */
uint16_t BLE_SMP_GenerateScOobData();


/**@brief Initiate pairing procedure. 
 * @note  If Pairing is initiated (unbonded devices) then following happens:
 *        - Phase 1: Pairing Feature Exchange
 *        - Phase 2 (LE legacy pairing): Short Term Key (STK) Generation
 *        - Phase 2 (LE Secure Connections): Long Term Key (LTK) Generation
 *        - Phase 3: Transport Specific Key Distribution
 *        The pairing method for Phase 2 is chosen based on IO Capabilities and Authentication request
 *        flag.
 *        For phase 3:
 *        - LE Secure connection pairing: CSRK and IRK may be distributed
 *        - LE Legacy pairing: Encryption key (LTK, EDIV, Rand), CSRK and IRK may be distributed
 *
 * @par Events generated
 *      Depending on the pairing parameters configured by @ref BLE_SMP_Config and the pairing feature exchanges with the peer, the following events may be generated:\n
 * @ref BLE_SMP_EVT_PAIRING_COMPLETE Generated when pairing process is completed or failed.\n
 * @ref BLE_SMP_EVT_NUMERIC_COMPARISON_CONFIRM_REQUEST Generated when received confirmation request for 6-digit values during pairing process (Numeric comparison).\n
 * @ref BLE_SMP_EVT_INPUT_PASSKEY_REQUEST Generated when passkey is requested to be input during pairing process (Passkey entry).\n
 * @ref BLE_SMP_EVT_DISPLAY_PASSKEY_REQUEST Generated when request to display passkey during pairing process (Passkey entry).\n
 * @ref BLE_SMP_EVT_NOTIFY_KEYS Generated when key distribution finished.\n
 * @ref BLE_SMP_EVT_PAIRING_REQUEST Generated when received pairing request from remote device.\n
 * @ref BLE_SMP_EVT_INPUT_OOB_DATA_REQUEST Generated when OOB data for legacy pairing is requested to be input during pairing process (Out of Band).\n
 * @ref BLE_SMP_EVT_INPUT_SC_OOB_DATA_REQUEST Generated when OOB data for Secure Connections pairing is requested to be input during pairing process (Out of Band).\n
 * @ref BLE_SMP_EVT_KEYPRESS Generated when keypress notification from the remote device.\n
 * 
 * @param[in] connHandle                    Connection handle associated with this connection.
 *
 * @retval MBA_RES_SUCCESS                  Pairing procedure started successfully.
 * @retval MBA_RES_FAIL                     The specified connection handle is invalid.
 */
uint16_t BLE_SMP_InitiatePairing(uint16_t connHandle);


/**@brief Generate six bytes random passkey in ASCII format. 
 * @note  This API should be called in SMP callback function when
 *        @ref BLE_SMP_EVT_DISPLAY_PASSKEY_REQUEST event is generated. Following this API
 *        @ref BLE_SMP_PasskeyReply should be called to send the passkey generated to the SDK
 *        and the passkey should be displayed to the user.
 *
 * @param[out] p_passkey                    Pointer to buffer into which generated passkey is stored.
 *
 */
void BLE_SMP_GeneratePasskey(uint8_t *p_passkey);


/**@brief Update paired device information to SMP
 * @note  This function is suggested to be called once after connected if the connection is bonded.
 *        SMP requires bonding information to check permission when processing requests. \n
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] encryptKeySize                Encryption key size.
 * @param[in] p_pairInfo                    Pointer to the pairing information buffer. See @ref BLE_SMP_PairInfo_T.
 *
 * @retval MBA_RES_SUCCESS                  Successfully update the information to SMP.
 * @retval MBA_RES_INVALID_PARA             Invalid connection handle.
 */
uint16_t BLE_SMP_UpdateBondingInfo(uint16_t connHandle, uint8_t encryptKeySize, BLE_SMP_PairInfo_T *p_pairInfo);


/**@brief Accept the pairing request.
 * @note  This API should be called to continue pairing procedure when receiving @ref BLE_SMP_EVT_PAIRING_REQUEST.
 *
 * @par Events generated
 *      This API is called during pairing procedure, please see the events generated of @ref BLE_SMP_InitiatePairing.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 *
 * @retval MBA_RES_SUCCESS                  Successfully issue pairing response with accept parameter.
 * @retval MBA_RES_INVALID_PARA             The parameter is invalid.
 */
uint16_t BLE_SMP_AcceptPairingRequest(uint16_t connHandle);


/**@brief Reject the pairing request.
 * @note  This API should be called to reject pairing procedure when receiving @ref BLE_SMP_EVT_PAIRING_REQUEST.
 *
 *
 * @par Events generated
 *      This API is called during pairing procedure, please see the events generated of @ref BLE_SMP_InitiatePairing.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 *
 * @retval MBA_RES_SUCCESS                  Successfully issue pairing response with reject parameter.
 * @retval MBA_RES_INVALID_PARA             The parameter is invalid.
 */
uint16_t BLE_SMP_RejectPairingRequest(uint16_t connHandle);


/**@brief Reject the security request issued by peer device.
 * @note  This API should be called to reject security request when receiving @ref BLE_SMP_EVT_SECURITY_REQUEST.
 *        This API is only valid if device is central role.
 *
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 *
 * @retval MBA_RES_SUCCESS                  Successfully reject security request issued by peer device.
 * @retval MBA_RES_INVALID_PARA             The parameter is invalid.
 */
uint16_t BLE_SMP_RejectSecRequest(uint16_t connHandle);


/**@brief Send a keypress notification message to inform the remote device when keys have been entered or erased.
 * @note  This API should be called only if receiving @ref BLE_SMP_EVT_INPUT_PASSKEY_REQUEST and keypress field of @ref BLE_SMP_EvtInputPasskeyReq_T is true.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] notifyType                    Notification type. See @ref BLE_SMP_KEYPRESS_NOTI_TYPE.
 *
 * @retval MBA_RES_SUCCESS                  Successfully issue a keypress notification.
 * @retval MBA_RES_INVALID_PARA             The parameter is invalid.
 */
uint16_t BLE_SMP_Keypress(uint16_t connHandle, uint8_t notifyType);


/**@brief Accept BLE SMP debug key during pairing procedure.
 * @note  If this API is called, then @ref BLE_SMP_EnableDebugMode API is prohibited.
 *
 * @retval MBA_RES_SUCCESS                  Successfully set to accept debug key.
 * @retval MBA_RES_FAIL                     Fail to set to accept debug key due to @ref BLE_SMP_EnableDebugMode API is called.
*/
uint16_t BLE_SMP_AcceptDebugKey();


/**@brief Enable BLE SMP debug mode.
 * @note  Debug public key will be used if debug mode is enabled.\n
 *        If this API is called, then @ref BLE_SMP_AcceptDebugKey API is prohibited.
 *
 * @retval MBA_RES_SUCCESS                  Successfully enable SMP debug mode.
 * @retval MBA_RES_FAIL                     Fail to enable debug mode due to @ref BLE_SMP_AcceptDebugKey API is called.
*/
uint16_t BLE_SMP_EnableDebugMode();

/**@} */ //BLE_SMP_FUNS
#endif

/**
  @}
*/
