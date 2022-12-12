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
  GATT Header File

  Company:
    Microchip Technology Inc.

  File Name:
    gatt.h

  Summary:
    This file contains the GATT functions for application user.

  Description:
    This file contains the GATT functions and event for application user.  The
    "BLE_GATTS_Init" or "BLE_GATTC_Init" function shall be called in the "APP_Initialize" 
    function to initialize the modules in the system.
 *******************************************************************************/


/**
 * @addtogroup GATT GATT
 * @{
 * @brief Header file for the Generic Attributes library.
 * @note Definitions and prototypes for the GATT stack layer application programming interface.
 */
#ifndef GATT_H
#define GATT_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "att_uuid.h"

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************

/**@addtogroup GATT_DEFINES Defines
 * @{ */
 
 
/**@defgroup GATT_EXEC_WRITE_FLAGS Execute write flag
 * @brief The definition of flags for Execute Write Request
 * @{ */
#define GATT_EXEC_WRITE_FLAG_CANCEL_ALL                     0x00                /**< Cancel all prepared writes.*/
#define GATT_EXEC_WRITE_FLAG_WRITE                          0x01                /**< Immediately write all pending prepared values.*/
/** @} */

/**@defgroup BLE_GATT_MTU_LENGTH MTU length
 * @brief The definition of GATT MTU length
 * @{ */
#define BLE_ATT_DEFAULT_MTU_LEN                             23                  /**< ATT default MTU length. */
#define BLE_ATT_MAX_MTU_LEN                                 247                 /**< The Maximum supported MTU length of ATT stack. */
/** @} */


/**@defgroup GATT_HEADER_SIZE Header size
 * @brief The definition of GATT header size
 * @{ */
#define ATT_HANDLE_VALUE_HEADER_SIZE                        3                   /**< The ATT Handle Value Notification/Indication Header Size. */
#define ATT_WRITE_HEADER_SIZE                               3                   /**< The ATT Write Request/Command Header Size. */
#define ATT_READ_RESP_HEADER_SIZE                           1                   /**< The ATT Read Response Header Size. */
#define ATT_WRITE_RESP_HEADER_SIZE                          5                   /**< The ATT Prepare Write Response Header Size. */
#define ATT_FIND_INFO_RESP_HEADER_SIZE                      2                   /**< The ATT Find Information Response Header Size.*/
#define ATT_FIND_BY_TYPE_RESP_HEADER_SIZE                   1                   /**< The ATT Find By Type Value Response Header Size. */
#define ATT_READ_BY_TYPE_RESP_HEADER_SIZE                   2                   /**< The ATT Read By Type Response Header Size. */
#define ATT_READ_BY_GROUP_RESP_HEADER_SIZE                  2                   /**< The ATT Read By Group Type Response Header Size. */
#define ATT_PREP_WRITE_RESP_HEADER_SIZE                     5                   /**< The ATT Prepare Write Response Header Size. */
#define ATT_NOTI_INDI_HEADER_SIZE                           3                   /**< The ATT Notification/Indication Header Size. */
/** @} */


/**@defgroup GATTC_CONFIGURATION_BITS GATT client configuration definitions
 * @brief The definition of of GATT Client configuration bits
 * @{ */
#define GATTC_CONFIG_NONE                                   0x0000              /**< Not configure anyone of the supported function. */
#define GATTC_CONFIG_MANUAL_CONFIRMATION                    0x0001              /**< bit 0: Configure ATT stack for auto/manual transmission of confirmation when an indication is received. */
/** @} */

/**@defgroup GATTS_CONFIGURATION_BITS GATT server configuration definitions
* @brief The definition of GATT server configuration bits
* @{ */
#define GATTS_CONFIG_NONE                                   0x0000              /**< Not configure anyone of the supported function. */
#define GATTS_CONFIG_CACHING_SUPPORT                        0x0001              /**< bit 0: Configure GATT Server support caching function. \n
                                                                                  *  If gatt caching is supported, the API @ref GATTS_UpdateBondingInfo must be called after link connected.
                                                                                  *  Otherwise, the GATT Server won't start process the incoming packets. */
/** @} */

/**@defgroup ATT_ERROR_CODES  ATT error code
 * @brief The definition of ATT Error Codes
 * @{ */
#define ATT_ERRCODE_INVALID_HANDLE                          0x01                /**< ATT Error Code: Invalid Handle.*/
#define ATT_ERRCODE_READ_NOT_PERMITTED                      0x02                /**< ATT Error Code: Read Not Permitted.*/
#define ATT_ERRCODE_WRITE_NOT_PERMITTED                     0x03                /**< ATT Error Code: Write Not Permitted.*/
#define ATT_ERRCODE_INVALID_PDU                             0x04                /**< ATT Error Code: Invalid PDU.*/
#define ATT_ERRCODE_INSUFFICIENT_AUTHENTICATION             0x05                /**< ATT Error Code: Insufficient Authentication.*/
#define ATT_ERRCODE_REQUEST_NOT_SUPPORT                     0x06                /**< ATT Error Code: Request Not Supported.*/
#define ATT_ERRCODE_INVALID_OFFSET                          0x07                /**< ATT Error Code: Invalid Offset.*/
#define ATT_ERRCODE_INSUFFICIENT_AUTHORIZATION              0x08                /**< ATT Error Code: Insufficient Authorization.*/
#define ATT_ERRCODE_PREPARE_QUEUE_FULL                      0x09                /**< ATT Error Code: Prepare Queue Full.*/
#define ATT_ERRCODE_ATTRIBUTE_NOT_FOUND                     0x0a                /**< ATT Error Code: Attribute Not Found.*/
#define ATT_ERRCODE_ATTRIBUTE_NOT_LONG                      0x0b                /**< ATT Error Code: Attribute Not Long.*/
#define ATT_ERRCODE_INSUFFICIENT_ENCRYPTION_KEY_SIZE        0x0c                /**< ATT Error Code: Insufficient Encryption Key Size.*/
#define ATT_ERRCODE_INVALID_ATTRIBUTE_VALUE_LENGTH          0x0d                /**< ATT Error Code: Invalid Attribute Value Length.*/
#define ATT_ERRCODE_UNLIKELY_ERROR                          0x0e                /**< ATT Error Code: Unlikely Error.*/
#define ATT_ERRCODE_INSUFFICIENT_ENCRYPTION                 0x0f                /**< ATT Error Code: Insufficient Encryption.*/
#define ATT_ERRCODE_UNSUPPORTED_GROUP_TYPE                  0x10                /**< ATT Error Code: Unsupported Group Type.*/
#define ATT_ERRCODE_INSUFFICIENT_RESOURCE                   0x11                /**< ATT Error Code: Insufficient Resource.*/
#define ATT_ERRCODE_DATABASE_OUT_OF_SYNC                    0x12                /**< ATT Error Code: Database Out Of Sync.*/
#define ATT_ERRCODE_VALUE_NOT_ALLOW                         0x13                /**< ATT Error Code: Value Not Allowed.*/
#define ATT_ERRCODE_APPLICATION_ERROR                       0x80                /**< ATT Error Code: Application Error.*/
/** @} */

/**@defgroup ATT_OPCODES    ATT opcodes
 * @brief The definition of ATT Attribute Opcodes
 * @{ */
#define ATT_ERROR_RSP                                       0x01               /**< Attribute Opcode: Error Response.*/
#define ATT_EXCHANGE_MTU_REQ                                0x02               /**< Attribute Opcode: Exchange MTU Request.*/
#define ATT_EXCHANGE_MTU_RSP                                0x03               /**< Attribute Opcode: Exchange MTU Response.*/
#define ATT_FIND_INFORMATION_REQ                            0x04               /**< Attribute Opcode: Find Information Request.*/
#define ATT_FIND_INFORMATION_RSP                            0x05               /**< Attribute Opcode: Find Information Response.*/
#define ATT_FIND_BY_TYPE_VALUE_REQ                          0x06               /**< Attribute Opcode: Find By Type Value Request.*/
#define ATT_FIND_BY_TYPE_VALUE_RSP                          0x07               /**< Attribute Opcode: Find By Type Value Response.*/
#define ATT_READ_BY_TYPE_REQ                                0x08               /**< Attribute Opcode: Read By Type Request.*/
#define ATT_READ_BY_TYPE_RSP                                0x09               /**< Attribute Opcode: Read By Type Response.*/
#define ATT_READ_REQ                                        0x0a               /**< Attribute Opcode: Read Request.*/
#define ATT_READ_RSP                                        0x0b               /**< Attribute Opcode: Read Response.*/
#define ATT_READ_BLOB_REQ                                   0x0c               /**< Attribute Opcode: Read Blob Request.*/
#define ATT_READ_BLOB_RSP                                   0x0d               /**< Attribute Opcode: Read Blob Response.*/
#define ATT_READ_MULTIPLE_REQ                               0x0e               /**< Attribute Opcode: Read Multiple Request.*/
#define ATT_READ_MULTIPLE_RSP                               0x0f               /**< Attribute Opcode: Read Multiple Response.*/
#define ATT_READ_BY_GROUP_TYPE_REQ                          0x10               /**< Attribute Opcode: Read By Group Type Request.*/
#define ATT_READ_BY_GROUP_TYPE_RSP                          0x11               /**< Attribute Opcode: Read By Group Type Response.*/
#define ATT_WRITE_REQ                                       0x12               /**< Attribute Opcode: Write Request.*/
#define ATT_WRITE_RSP                                       0x13               /**< Attribute Opcode: Write Response.*/
#define ATT_WRITE_CMD                                       0x52               /**< Attribute Opcode: Write Command.*/
#define ATT_PREPARE_WRITE_REQ                               0x16               /**< Attribute Opcode: Prepare Write Request.*/
#define ATT_PREPARE_WRITE_RSP                               0x17               /**< Attribute Opcode: Prepare Write Response.*/
#define ATT_EXECUTE_WRITE_REQ                               0x18               /**< Attribute Opcode: Execute Write Request.*/
#define ATT_EXECUTE_WRITE_RSP                               0x19               /**< Attribute Opcode: Execute Write Response.*/
#define ATT_HANDLE_VALUE_NTF                                0x1b               /**< Attribute Opcode: Handle Value Notification.*/
#define ATT_HANDLE_VALUE_IND                                0x1d               /**< Attribute Opcode: Handle Value Indication.*/
#define ATT_HANDLE_VALUE_CFM                                0x1e               /**< Attribute Opcode: Handle Value Confirmation.*/
#define ATT_READ_MUTIPLE_VARIABLE_REQ                       0x20               /**< Attribute Opcode: Read Multiple Variable Request.*/
#define ATT_READ_MUTIPLE_VARIABLE_RSP                       0x21               /**< Attribute Opcode: Read Multiple Variable Response.*/
#define ATT_MUTIPLE_HANDLE_VALUE_NTF                        0x22               /**< Attribute Opcode: Multiple Handle Value Notification.*/
#define ATT_SIGNED_WRITE_COMMAND                            0xd2               /**< Attribute Opcode: Signed Write Command.*/
/** @} */

/**@defgroup ATT_PERMISSION_KEY_SIZE  Permission key size
 * @brief The definition of of permission key size
 * @note  Attribute might require permission (Encryption/Authentication Permission) to be accessed.
 *        The key size defines the minimum length of the pairing key.\n Key size shorter than this length is considered as unsafe authentication/encryption.
 *        Length ranges from 7 bytes to 16 bytes.\n Set to zero to disable the key size checking.
 * @{ */
#define ATT_PERMISSION_KEY_SIZE                             0x10                /**< Minimum length of the pairing key. */
/** @} */


/**@defgroup GATT_PROCEDURE_STATUS  Procedure status definition
 * @brief The definition of of procedure status
 * @note Some GATT procedures would not finish in one ATT request. Hence, more than one event will received in one procedure.\n
 *        Status in the event indicates if this procedure will continue or end.\n
 * @{ */
#define GATT_PROCEDURE_STATUS_CONTINUE                      0x00                /**< Querying procedure continues. Further events will be received. */
#define GATT_PROCEDURE_STATUS_FINISH                        0x01                /**< Querying procedure is complete. Last event of this procedure. */
/** @} */


/**@defgroup GATT_CLIENT_FEATURE  GATT client features
 * @brief The definition of client features in client supported features characteristic in GATT Service
 * @{ */
#define GATT_ROBUST_CACHING                                 0x01                /**< The client supports robust caching. */
#define GATT_EATT_BEARER                                    0x02                /**< The client supports enhanced ATT bearer. */
#define GATT_MULTI_HANDLE_NOTI                              0x04                /**< The client supports multiple handle value notifications. */
/** @} */


/**@defgroup GATT_ATTRIBUTE_PERMISSIONS Attribute permission
*  @brief The definition of attribute permissions.
*  @{ */
#define PERMISSION_READ                                     0x01                /**< Read access is premitted. */
#define PERMISSION_READ_AUTHEN                              0x02                /**< Read access requires encryption, MITM protection. */
#define PERMISSION_READ_AUTHEN_SC                           0x04                /**< Read access requires encryption, MITM protection, Secure Connections */
#define PERMISSION_READ_ENC                                 0x08                /**< Read access requires encryption, No MITM protection. */
#define PERMISSION_WRITE                                    0x10                /**< Write access is premitted. */
#define PERMISSION_WRITE_AUTHEN                             0x20                /**< Write access requires encryption, MITM protection. */
#define PERMISSION_WRITE_AUTHEN_SC                          0x40                /**< write access requires encryption, MITM protection, Secure Connections */
#define PERMISSION_WRITE_ENC                                0x80                /**< Write access requires encryption, No MITM protection. */
/** @} */

/**@defgroup GATT_ATTRIBUTE_SETTINGS Attribute settings
*  @brief The definition of attribute settings.
*  @{ */
#define SETTING_MANUAL_WRITE_RSP                            0x01                /**< Set if service need to know write operations on this attribute. Service also need to send response (if need) manually. */
#define SETTING_MANUAL_READ_RSP                             0x02                /**< Set if service need to know read operations on this attribute. Service also need to send response manually. */
#define SETTING_UUID_16                                     0x04                /**< Set if the UUID is 16 bytes (128 bits) in length */
#define SETTING_VARIABLE_LEN                                0x08                /**< Set if the attribute has a variable length */
#define SETTING_ALLOW_OFFSET                                0x10                /**< Set if writes are allowed with an offset */
#define SETTING_CCCD                                        0x20                /**< Set if the attribute is CCCD */
/** @} */


/**@defgroup GATT_CHARACTERISTIC_PROPERTIES Characteristic property
 * @brief The definition of properties in Characteristic declaration.
 * @{ */
#define ATT_PROP_BROADCAST                                  0x01                /**< If set, permits broadcasts of Characteristic Value using Server Characteristic Configuration Descriptor.*/
#define ATT_PROP_READ                                       0x02                /**< If set, permits reads of the Characteristic Value.*/
#define ATT_PROP_WRITE_CMD                                  0x04                /**< If set, permits writes of Characteristic Value without response.*/
#define ATT_PROP_WRITE_REQ                                  0x08                /**< If set, permits writes of Characteristic Value with response.*/
#define ATT_PROP_NOTIFY                                     0x10                /**< If set, permits notifications of a Characteristic Value without acknowledgement.*/
#define ATT_PROP_INDICATE                                   0x20                /**< If set, permits indications of Characteristic Value with acknowledgement.*/
#define ATT_PROP_AUTH_WRITES                                0x40                /**< If set, permits signed writes to the Characteristic Value.*/
#define ATT_PROP_EXTENDED_PROP                              0x80                /**< If set, additional characteristic properties are defined in the Characteristic Extended Properties Descriptor.*/
/** @} */

/**@defgroup GATT_CHARACTERISTIC_EXTENDED_PROPERTIES Characteristic extended property
 * @brief The definition of Characteristic Extended Properties bit field
 * @{ */
#define RELIABLE_WRITE                                      0x0001              /**< If set, permits reliable writes of Characteristic Value.*/
#define WRITABLE_AUXILIARIES                                0x0002              /**< If set, permits writes to the Characteristic Descriptor.*/
/** @} */

/**@defgroup GATT_CCCD_BITS Client Characteristic Configuration definition
 * @brief The definition of Client Characteristic Configuration bit field
 * @{ */
#define NOTIFICATION                                        0x0001              /**< The Characteristic Value shall be notified.*/
#define INDICATION                                          0x0002              /**< The Characteristic Value shall be indicated.*/
/** @} */

/**@defgroup GATT_SCCD_BITS Server Characteristic Configuration definition
 * @brief The definition of Server Characteristic Configuration bit field
 * @{ */
#define SCCD_BROADCAST                                      0x0001              /**< The Characteristic Value shall be broadcast.*/
/** @} */

/**@defgroup GATTS_BUILDIN_CCCD Maximium build-in CCCD number
 * @brief The definition of total CCCD number of build-in services.
 * @{ */
#define GATTS_BUILDIN_CCCD_NUM                              0x01                /**< There exist one CCCD in build-in GATT Services. */
/** @} */

/**@defgroup GATT_DB_CHANGE_STATE Database change state
 * @brief The definition of GATT Server database change-aware state
 * @{ */
#define GATT_DB_CHANGE_AWARE                                0x00                /**< The GATT database is change-aware to specific client. */
#define GATT_DB_CHANGE_UNAWARE                              0x01                /**< The GATT database is change-unaware to specific client. */
/** @} */


/**@defgroup GATTS_APP_SVC_START_HDL Valid start attribute handle
 * @brief The definition of valid attribute handle
 * @note  The application registered service should be greater than this definition
 * @{ */
#define GATTS_APP_ATTRIBUTE_START_HANDLE                    0x0050              /**< Start attribute handle of application-defined service. */
/** @} */


/**@} */ //GATT_DEFINES

/**@addtogroup GATT_ENUMS Enumerations
 * @{ */
 
/**
 *@brief Enumeration type of GATT callback events.
 *@note
 *        - Events with "GATTC" in EventID are generated on GATT Client.
 *        - Events with "GATTS" are generated on GATT Server.
 *        - Remaining events may be generated either on the GATT client or server.
 */
typedef enum GATT_EventId_T
{
    GATTC_EVT_ERROR_RESP = 0x00,                                                /**< Error Response Event. See @ref GATT_EvtError_T for event details. */
    GATTC_EVT_DISC_PRIM_SERV_RESP,                                              /**< Discover Primary Services Response Event. See @ref GATT_EvtDiscPrimServResp_T for event details. */
    GATTC_EVT_DISC_PRIM_SERV_BY_UUID_RESP,                                      /**< Discover Primary Services By UUID Response Event. See @ref GATT_EvtDiscPrimServByUuidResp_T for event details. */
    GATTC_EVT_DISC_CHAR_RESP,                                                   /**< Discover All Characteristics Response Event. See @ref GATT_EvtDiscCharResp_T for event details. */
    GATTC_EVT_DISC_DESC_RESP,                                                   /**< Discover All Descriptors Response Event. See @ref GATT_EvtDiscDescResp_T for event details. */
    GATTC_EVT_READ_USING_UUID_RESP,                                             /**< Read Using UUID Response Event. See @ref GATT_EvtReadUsingUuidResp_T for event details. */
    GATTC_EVT_READ_RESP,                                                        /**< Read Response Event. See @ref GATT_EvtReadResp_T for event details. */
    GATTC_EVT_WRITE_RESP,                                                       /**< Write Response Event. See @ref GATT_EvtWriteResp_T for event details. */
    GATTC_EVT_HV_NOTIFY,                                                        /**< Handle Value Notification Event. See @ref GATT_EvtReceiveHandleValue_T for event details. */
    GATTC_EVT_HV_INDICATE,                                                      /**< Handle Value Indication Event. See @ref GATT_EvtReceiveHandleValue_T for event details. */
    GATTS_EVT_READ,                                                             /**< Read Requests Event. See @ref GATT_EvtRead_T for event details. */
    GATTS_EVT_WRITE,                                                            /**< Write Request/Command Event. See @ref GATT_EvtWrite_T for event details. \n
                                                                                  *  Please note that App. will receive prepare/execute write requests if the additional condition matched: \n
                                                                                  *  There's no queue writes queued in the GATT. GATT cannot handle queue writes both in stack and application at the same time. */
    GATTS_EVT_HV_CONFIRM,                                                       /**< Handle Value Confirmation Event. See @ref GATT_EvtReceiveCfm_T for event details. */
    ATT_EVT_TIMEOUT,                                                            /**< ATT Stack Timeout Event. */
    ATT_EVT_UPDATE_MTU,                                                         /**< Update MTU Event. See @ref GATT_EvtUpdateMtu_T for event details. */
    GATTC_EVT_DISC_CHAR_BY_UUID_RESP,                                           /**< Discover Characteristics By UUID Response Event. See @ref GATT_EvtDiscCharResp_T for event details. */
    GATTS_EVT_SERVICE_CHANGE,                                                   /**< Service change for the specific bonded client. The information must be kept between connection. @ref GATT_EvtServiceChange_T. */
    GATTS_EVT_CLIENT_FEATURE_CHANGE,                                            /**< Support feature change for a specific bonded client. The information must be kept between connection. @ref GATT_EvtClientFeatureChange_T. */
    GATTS_EVT_CLIENT_CCCDLIST_CHANGE,                                           /**< CCCD list change for a specific bonded client. The information must be kept between connection. @ref GATT_EvtClientCccdListChange_T. */
    GATTC_EVT_PROTOCOL_AVAILABLE,                                               /**< Sequential protocol available in client role. @ref GATT_EvtProtocolAvailable_T */
    GATTS_EVT_PROTOCOL_AVAILABLE                                                /**< Sequential protocol available in server role. @ref GATT_EvtProtocolAvailable_T */
}GATT_EventId_T;

/**@} */ //GATT_ENUMS

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/**@addtogroup GATT_STRUCTS Structures
 * @{ */
 
/**@brief GATT Write Request parameters. */
typedef struct GATTC_WriteParams_T
{
    uint16_t     charHandle;                                                    /**< Handle of the characteristic to be written. */
    uint16_t     charLength;                                                    /**< Length of the characteristic to be written. For Max value refer size of charValue[] */
    uint8_t      charValue[BLE_ATT_MAX_MTU_LEN - ATT_WRITE_HEADER_SIZE];        /**< Data to be written. */
    uint8_t      writeType;                                                     /**< Type of the write operation. See @ref ATT_OPCODES. Only ATT_WRITE_REQ/ATT_WRITE_CMD/ATT_PREPARE_WRITE_REQ/ATT_EXECUTE_WRITE_REQ are allowed. */
    uint16_t     valueOffset;                                                   /**< The offset of the first octet to be written. Set to offset
                                                                                     where attribute part value is to be written for Prepare Write request.
                                                                                     For all other write types set to 0. */
    uint8_t      flags;                                                         /**< Flag. Used only when writeType is ATT_EXECUTE_WRITE_REQ
                                                                                     (See @ref GATT_EXEC_WRITE_FLAGS). Otherwise always 0). */
}   GATTC_WriteParams_T;

/**@brief GATT Discover Primary Service By UUID parameters. */
typedef struct GATTC_DiscoverPrimaryServiceByUuidParams_T
{
    uint16_t     startHandle;                                                   /**< Start handle for querying the service by UUID */
    uint16_t     endHandle;                                                     /**< End handle for querying the service by UUID */
    uint8_t      valueLength;                                                   /**< length of UUID in bytes. Should be set to 2 for 16-bit UUID and 16 for 128 bit UUID. */
    uint8_t      value[ATT_MAX_UUID_SIZE];                                      /**< UUID of particular primary service to be discovered. The format of UUID is little endian. */
}   GATTC_DiscoverPrimaryServiceByUuidParams_T;

/**@brief GATT Discover Characteristics By UUID parameters. */
typedef struct GATTC_DiscoverCharacteristicByUuidParams_T
{
    uint16_t     startHandle;                                                   /**< Start handle for querying specific characteristic. */
    uint16_t     endHandle;                                                     /**< End handle for querying specific characteristic. */
    uint8_t      uuidLength;                                                    /**< Length of the specific characteristic UUID in bytes. */
    uint8_t      uuid[ATT_MAX_UUID_SIZE];                                       /**< The specific characteristic UUID. The format of UUID is little endian. */
}   GATTC_DiscoverCharacteristicByUuidParams_T;

/**@brief GATT Read By Type Request parameters. */
typedef struct GATTC_ReadByTypeParams_T
{
    uint16_t    startHandle;                                                    /**< Starting handle for querying. */
    uint16_t    endHandle;                                                      /**< Ending handle for querying. */
    uint8_t     attrTypeLength;                                                 /**< Length of the attribute type in bytes. Should be set to 2 for 16-bit UUID and 16 for 128 bit UUID. */
    uint8_t     attrType[ATT_MAX_UUID_SIZE];                                    /**< Attribute Type i.e., Characteristic UUID. The format of UUID is little endian. */
}   GATTC_ReadByTypeParams_T;

/**@brief GATT Handle Value Notification/Indication parameters. */
typedef struct GATTS_HandleValueParams_T
{
    uint16_t    charHandle;                                                     /**< Handle of the characteristic to be notified/indicated. */
    uint16_t    charLength;                                                     /**< Length of the characteristic to be notified/indicated. Max value limited to size of charValue[].*/
    uint8_t     charValue[BLE_ATT_MAX_MTU_LEN - ATT_HANDLE_VALUE_HEADER_SIZE];  /**< Characteristic value to be notified/indicated. */
    uint8_t     sendType;                                                       /**< Flag indicating Notification or Indication. See @ref ATT_OPCODES. Only ATT_HANDLE_VALUE_NTF/ATT_HANDLE_VALUE_IND are allowed. */
}   GATTS_HandleValueParams_T;

/**@brief GATT Send Read Response parameters. */
typedef struct GATTS_SendReadRespParams_T
{
    uint16_t    attrLength;                                                     /**< Length of the read attribute. */
    uint8_t     responseType;                                                   /**< Read response type, @ref ATT_OPCODES. Only ATT_READ_RSP/ATT_READ_BLOB_RSP are allowed. */
    uint8_t     attrValue[BLE_ATT_MAX_MTU_LEN - ATT_READ_RESP_HEADER_SIZE];     /**< Value to be sent in Read response. */
}   GATTS_SendReadRespParams_T;

/**@brief GATT Send Error Response parameters. */
typedef struct GATTS_SendErrRespParams_T
{
    uint8_t     reqOpcode;                                                      /**< Request that generated this error response. See @ref ATT_OPCODES. */
    uint8_t     errorCode;                                                      /**< Reason why the request has generated an error response. See @ref ATT_ERROR_CODES. */
    uint16_t    attrHandle;                                                     /**< Attribute handle that generated this error response. */
}   GATTS_SendErrRespParams_T;

/**@brief GATT Send Read By Type Response parameters. */
typedef struct GATTS_SendReadByTypeRespParams_T
{
    uint16_t    allPairsLength;                                                         /**< Length of all handle-value pairs. */
    uint8_t     eachPairLength;                                                         /**< Length of one handle-value pair. Read By Type Response may contain multiple handle-value pairs of the same length. */
    uint8_t     attrDataList[BLE_ATT_MAX_MTU_LEN - ATT_READ_BY_TYPE_RESP_HEADER_SIZE];  /**< Handle-value pairs to be sent to Client. The data format should be little endian. */
}   GATTS_SendReadByTypeRespParams_T;

/**@brief GATT Send Write Response parameters. */
typedef struct GATTS_SendWriteRespParams_T
{
    uint8_t     responseType;                                                   /**< Write response type, @ref ATT_OPCODES. Only ATT_WRITE_RSP/ATT_PREPARE_WRITE_RSP/ATT_EXECUTE_WRITE_RSP are allowed. */
    uint16_t    attrHandle;                                                     /**< Handle of the attribute written. Use for Prepare Write Response only. */
    uint16_t    valueOffset;                                                    /**< Offset of the first octet written. Use for Prepare Write Response only. */
    uint16_t    writeLength;                                                    /**< Length of the written value. Used for Prepare Write Response only and should be same as corresponding field in Prepare Write request received. */
    uint8_t     writeValue[BLE_ATT_MAX_MTU_LEN - ATT_WRITE_RESP_HEADER_SIZE];   /**< Value of the attribute written. Used for Prepare Write Response only and should be same as as corresponding field in Prepare Write request received. */
}   GATTS_SendWriteRespParams_T;

/**@brief CCCD parameters. */
typedef struct GATTS_CccdSetting_T
{
    uint16_t    attrHandle;                                                     /**< The attribute handle of the CCCD. */
    uint16_t    acceptableValue;                                                /**< The acceptable value of the CCCD. */
} GATTS_CccdSetting_T;

/**@brief CCCD list. */
typedef struct GATTS_CccdList_T
{
    uint16_t    attrHandle;                                                     /**< The attribute handle of the CCCD. */
    uint16_t    cccdValue;                                                      /**< Value of the CCCD. */
} GATTS_CccdList_T;

/**@brief Bonding parameters. */
typedef struct GATTS_BondingParams_T
{
    uint8_t     serviceChange;                                                  /**< The service change state. */
    uint8_t     clientSupportFeature;                                           /**< Support feature of the related client. */
} GATTS_BondingParams_T;

/**@brief GATT attribute */
typedef struct GATTS_Attribute_T
{
    uint8_t     *p_uuid;                                                        /**< Pointer to the attribute's UUID (attribut type). */
    uint8_t     *p_value;                                                       /**< Pointer to the attribute's value. */
    uint16_t    *p_len;                                                         /**< Pointer to the length of the attribute's value. */
    uint16_t    maxLen;                                                         /**< Maximum length of attribute's value. */
    uint8_t     settings;                                                       /**< Attribute settings. */
    uint8_t     permissions;                                                    /**< Attribute permissions. */
} GATTS_Attribute_T;

/**@brief Service table parameters */
typedef struct GATTS_Service_T
{
    struct GATTS_Service_T          *p_next;                                    /**< For internal use only. */
    GATTS_Attribute_T               *p_attrList;                                /**< Pointer to attribute list in this service. */
    GATTS_CccdSetting_T const       *p_cccdSetting;                             /**< CCCD information of the service. Can be null. */
    uint16_t                        startHandle;                                /**< The handle of the first attribute in this group. */
    uint16_t                        endHandle;                                  /**< The handle of the last attribute in this group. */
    uint8_t                         cccdNumber;                                 /**< Number of CCCD in the service. */
} GATTS_Service_T;


/**@brief Service options. */
typedef struct GATTS_GattServiceOptions_T
{
    uint8_t     enable;                                                         /**< Enable or disable GATT service.*/
} GATTS_GattServiceOptions_T;


/**@brief Data structure for @ref GATTC_EVT_ERROR_RESP event. */
typedef struct GATT_EvtError_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint8_t     reqOpcode;                                                      /**< Request that generated this error response. */
    uint16_t    attrHandle;                                                     /**< The attribute handle that generated this error response. */
    uint8_t     errCode;                                                        /**< Reason why the request has generated an error response. See @ref ATT_ERROR_CODES.*/
}   GATT_EvtError_T;

/**@brief Data structure for @ref GATTS_EVT_READ event.*/
typedef struct GATT_EvtRead_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint16_t    attrHandle;                                                     /**< Handle of the attribute to be read. */
    uint8_t     readType;                                                       /**< Read Type. Only ATT_READ_BY_TYPE_REQ/ATT_READ_REQ/ATT_READ_BLOB_REQ are allowed. See @ref ATT_OPCODES. */
    uint16_t    readOffset;                                                     /**< Offset of the first octet to be read. Used for Read Blob request only. */
}   GATT_EvtRead_T;

/**@brief Data structure for @ref GATTS_EVT_WRITE event.*/
typedef struct GATT_EvtWrite_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint16_t    attrHandle;                                                     /**< Handle of the attribute to be written. */
    uint8_t     writeType;                                                      /**< Write Type. See @ref ATT_OPCODES. Only ATT_WRITE_REQ/ATT_WRITE_CMD/ATT_PREPARE_WRITE_REQ/ATT_EXECUTE_WRITE_REQ are allowed. */
    uint8_t     flags;                                                          /**< Flags for Execute Write Request. See @ref GATT_EXEC_WRITE_FLAGS. */
    uint16_t    valueOffset;                                                    /**< Value offset for Prepare Write Request. */
    uint16_t    writeDataLength;                                                /**< Length of the data to be written. */
    uint8_t     writeValue[BLE_ATT_MAX_MTU_LEN - ATT_WRITE_HEADER_SIZE];        /**< Value to be written to the attribute. */
}   GATT_EvtWrite_T;

/**@brief Data structure for @ref GATTC_EVT_DISC_PRIM_SERV_RESP event.*/
typedef struct GATT_EvtDiscPrimServResp_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint8_t     attrPairLength;                                                 /**< Length of each tuple in attribute data. */
    uint16_t    attrDataLength;                                                 /**< Total length of all tuples. */
    uint8_t     attrData[BLE_ATT_MAX_MTU_LEN-ATT_READ_BY_GROUP_RESP_HEADER_SIZE]; /**< Attribute data list.\n
                                                                                       Contains Tuples in following format: \<2-byte service handle\> \<2-byte End Group Handle\>\<Service UUID\> \n
                                                                                       Service handle is the handle of service discovered, End Group Handle is the handle of the last attribute of the service discovered\n
                                                                                       Service UUID may be 16 or 128-bit.\n
                                                                                       Multiple tuples received in a single event have the same service UUID length\n
                                                                                       Number of tuples = (attrDataLength/attrPairLength). \n
                                                                                       Note that the format of the data is little endian. */
    uint8_t     procedureStatus;                                                /**< "Discover All Primary Services" Procedure may not finish in one ATT request. Status indicates if further events are expected. See @ref GATT_PROCEDURE_STATUS. */
}   GATT_EvtDiscPrimServResp_T;

/**@brief Data structure for @ref GATTC_EVT_DISC_PRIM_SERV_BY_UUID_RESP event.*/
typedef struct GATT_EvtDiscPrimServByUuidResp_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint16_t    handleInfoLength;                                               /**< Total length of the handle information list in bytes. */
    uint8_t     handleInfo[BLE_ATT_MAX_MTU_LEN-ATT_FIND_BY_TYPE_RESP_HEADER_SIZE];/**< Handle information list.\n
                                                                                             Contains handle pairs in following format: \<2-byte service handle\> \<2-byte End Group Handle\> \n
                                                                                             Service handle is the handle of service discovered, End Group Handle is the handle of the last attribute of the service discovered\n
                                                                                             If the same primary service has multiple instances on the server then multiple handle pairs may exist. \n
                                                                                             Note that the format of the data is little endian. */
    uint8_t     procedureStatus;                                                /**< Discover Primary Service By UUID may not finish in one ATT request. Status indicates if further events are expected. See @ref GATT_PROCEDURE_STATUS. */
}   GATT_EvtDiscPrimServByUuidResp_T;

/**@brief Data structure for @ref GATTC_EVT_DISC_CHAR_RESP event.*/
typedef struct GATT_EvtDiscCharResp_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint8_t     attrPairLength;                                                 /**< Length of each handle-value pair in the list. */
    uint16_t    attrDataLength;                                                 /**< Total length of attribute data list. */
    uint8_t     attrData[BLE_ATT_MAX_MTU_LEN-ATT_READ_BY_TYPE_RESP_HEADER_SIZE];/**< Attribute data list.\n
                                                                                     Consists of handle-value pairs in following format: \<2-byte Characteristic declaration handle\> \<1-byte Characteristic property\> \<2-byte Value Handle\> \<Characteristic UUID\>\n
                                                                                     To extract the Characteristic property data see @ref GATT_CHARACTERISTIC_PROPERTIES \n
                                                                                     Characteristic UUID may be 16-bit or 128-bit in length.\n
                                                                                     Multiple Handle-value pairs received in a single event have the same characteristic UUID length\n
                                                                                     Number of handle-value pairs = (attrDataLength/attrPairLength\n
                                                                                     Note that the format of the data is little endian. */
    uint8_t     procedureStatus;                                                /**< Discover All Characteristics procedure may not finish in one ATT request. Status indicates if further events are expected. See @ref GATT_PROCEDURE_STATUS. */
}   GATT_EvtDiscCharResp_T;

/**@brief Data structure for @ref GATTC_EVT_DISC_DESC_RESP event.*/
typedef struct GATT_EvtDiscDescResp_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint8_t     infoDataFormat;                                                 /**< Format of the received descriptor Data.\n If 1 then p_infoData has 16-bit UUIDs.\n If 2 then p_infoData has 128-bit UUIDs.\n Other values are invalid. */
    uint16_t    infoDataLength;                                                 /**< Total length of the all received Descriptor information Data. */
    uint8_t     infoData[BLE_ATT_MAX_MTU_LEN-ATT_FIND_INFO_RESP_HEADER_SIZE];   /**< Descriptor Data.\n
                                                                                     Data consists of handle-value pairs in following format: \<2-byte Characteristic descriptor handle\> \<Characteristic Descriptor UUID\>\n
                                                                                     Number of handle-value pairs = (infoDataLength/4) if  p_infoData is 1\n
                                                                                     Number of handle-value pairs = (infoDataLength/18) if  p_infoData is 2\n
                                                                                     Note that the format of the data is little endian. */
    uint8_t     procedureStatus;                                                /**< "Discover All Descriptors" procedure may not finish in one ATT request. Status indicates if further events are expected. See @ref GATT_PROCEDURE_STATUS. */
}   GATT_EvtDiscDescResp_T;

/**@brief Data structure for @ref GATTC_EVT_READ_USING_UUID_RESP event.*/
typedef struct GATT_EvtReadUsingUuidResp_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint8_t     attrPairLength;                                                 /**< Length of each attribute handle-value pair in the list. */
    uint16_t    attrDataLength;                                                 /**< Length of attributes data list. */
    uint8_t     attrData[BLE_ATT_MAX_MTU_LEN-ATT_READ_BY_TYPE_RESP_HEADER_SIZE];/**< Attribute data list. Data consists of one or more handle-value pairs.\n
                                                                                     - Format of handle-value pair: \<2-byte Characteristic Value handle\> \<Characteristic Value Read\> \n
                                                                                     - Number of handle-value pairs = (attrDataLength/attrPairLength)\n
                                                                                     Note that the format of the data is little endian. */
}   GATT_EvtReadUsingUuidResp_T;

/**@brief Data structure for @ref GATTC_EVT_READ_RESP event.*/
typedef struct GATT_EvtReadResp_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint8_t     responseType;                                                   /**< Read response type. See @ref ATT_OPCODES. Only ATT_READ_RSP/ATT_READ_BLOB_RSP are allowed. */
    uint16_t    attrDataLength;                                                 /**< Length of the data read. */
    uint8_t     readValue[BLE_ATT_MAX_MTU_LEN-ATT_READ_RESP_HEADER_SIZE];       /**< Data Read from the handle that was specified in Read Request. */
    uint16_t    charHandle;                                                     /**< Characteristic handle for the response. */
}   GATT_EvtReadResp_T;

/**@brief Data structure for @ref GATTC_EVT_WRITE_RESP event.*/
typedef struct GATT_EvtWriteResp_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint8_t     responseType;                                                   /**< Write response type. See @ref ATT_OPCODES. Only ATT_WRITE_RSP/ATT_PREPARE_WRITE_RSP/ATT_EXECUTE_WRITE_RSP are allowed */
    uint16_t    charHandle;                                                     /**< Handle (Same as in prepare write request). Used only when responseType is @ref ATT_PREPARE_WRITE_RSP */
    uint16_t    valueOffset;                                                    /**< Write offset (Same as in prepare write request). Used only when responseType is @ref ATT_PREPARE_WRITE_RSP */
    uint16_t    writeLength;                                                    /**< Length of written value. Used only when responseType is @ref ATT_PREPARE_WRITE_RSP*/
    uint8_t     writeValue[BLE_ATT_MAX_MTU_LEN-ATT_PREP_WRITE_RESP_HEADER_SIZE];/**< Value written (Same as in prepare write request). Used only when responseType is @ref ATT_PREPARE_WRITE_RSP*/
}   GATT_EvtWriteResp_T;

/**@brief Data structure for @ref ATT_EVT_UPDATE_MTU event.*/
typedef struct GATT_EvtUpdateMtu_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint16_t    exchangedMTU;                                                   /**< The exchanged MTU after connection. */
}   GATT_EvtUpdateMtu_T;

/**@brief Data structure for @ref GATTC_EVT_HV_NOTIFY or @ref GATTC_EVT_HV_INDICATE event.*/
typedef struct GATT_EvtReceiveHandleValue_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint16_t    charHandle;                                                     /**< Handle of the attribute which is notified/indicated. */
    uint16_t    receivedLength;                                                 /**< Length of value received in notification/indication. */
    uint8_t     receivedValue[BLE_ATT_MAX_MTU_LEN-ATT_NOTI_INDI_HEADER_SIZE];   /**< Value received in Notification/Indication. */
}   GATT_EvtReceiveHandleValue_T;

/**@brief Data structure for @ref GATTS_EVT_HV_CONFIRM event.*/
typedef struct GATT_EvtReceiveCfm_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint16_t    attrHandle;                                                     /**< The confirmation is acknowledgement of indication performed on this attribute hanlde. */
}   GATT_EvtReceiveCfm_T;


/**@brief Data structure for @ref GATTS_EVT_SERVICE_CHANGE event. */
typedef struct GATT_EvtServiceChange_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. Value 0x00 to all the bonded devices. */
    uint8_t     serviceChange;                                                  /**< Service change-aware state. @ref GATT_DB_CHANGE_STATE. */
} GATT_EvtServiceChange_T;

/**@brief Data structure for @ref GATTS_EVT_CLIENT_FEATURE_CHANGE event. */
typedef struct GATT_EvtClientFeatureChange_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint8_t     clientSupportFeature;                                           /**< Bit field represents client support features. @ref GATT_CLIENT_FEATURE */
} GATT_EvtClientFeatureChange_T;

/**@brief Data structure for @ref GATTS_EVT_CLIENT_CCCDLIST_CHANGE event. */
typedef struct GATT_EvtClientCccdListChange_T
{
    GATTS_CccdList_T *p_cccdList;                                               /**< Pointer to the CCCD list */
    uint16_t         connHandle;                                                /**< Connection handle associated with this connection. */
    uint8_t          numOfCccd;                                                 /**< Number of CCCDs in the List */
} GATT_EvtClientCccdListChange_T;

/**@brief Data structure for @ref GATTC_EVT_PROTOCOL_AVAILABLE or @ref GATTS_EVT_PROTOCOL_AVAILABLE event. */
typedef struct GATT_EvtProtocolAvailable_T
{
    uint16_t         connHandle;                                                /**< Connection handle associated with this connection. */
} GATT_EvtProtocolAvailable_T;


/**@brief Union of GATT callback event data types. */
typedef union
{
    GATT_EvtError_T                       onError;                              /**< Handle @ref GATTC_EVT_ERROR_RESP */
    GATT_EvtRead_T                        onRead;                               /**< Handle @ref GATTS_EVT_READ */
    GATT_EvtWrite_T                       onWrite;                              /**< Handle @ref GATTS_EVT_WRITE */
    GATT_EvtDiscPrimServResp_T            onDiscPrimServResp;                   /**< Handle @ref GATTC_EVT_DISC_PRIM_SERV_RESP */
    GATT_EvtDiscPrimServByUuidResp_T      onDiscPrimServByUuidResp;             /**< Handle @ref GATTC_EVT_DISC_PRIM_SERV_BY_UUID_RESP */
    GATT_EvtDiscCharResp_T                onDiscCharResp;                       /**< Handle @ref GATTC_EVT_DISC_CHAR_RESP */
    GATT_EvtDiscDescResp_T                onDiscDescResp;                       /**< Handle @ref GATTC_EVT_DISC_DESC_RESP */
    GATT_EvtReadUsingUuidResp_T           onReadUsingUuidResp;                  /**< Handle @ref GATTC_EVT_READ_USING_UUID_RESP */
    GATT_EvtReadResp_T                    onReadResp;                           /**< Handle @ref GATTC_EVT_READ_RESP */
    GATT_EvtWriteResp_T                   onWriteResp;                          /**< Handle @ref GATTC_EVT_WRITE_RESP */
    GATT_EvtUpdateMtu_T                   onUpdateMTU;                          /**< Handle @ref ATT_EVT_UPDATE_MTU */
    GATT_EvtReceiveHandleValue_T          onNotification;                       /**< Handle @ref GATTC_EVT_HV_NOTIFY */
    GATT_EvtReceiveHandleValue_T          onIndication;                         /**< Handle @ref GATTC_EVT_HV_INDICATE */
    GATT_EvtReceiveCfm_T                  onConfirmation;                       /**< Handle @ref GATTS_EVT_HV_CONFIRM */
    GATT_EvtDiscCharResp_T                onDiscCharByUuid;                     /**< Handle @ref GATTC_EVT_DISC_CHAR_BY_UUID_RESP */
    GATT_EvtServiceChange_T               onServiceChange;                      /**< Handle @ref GATTS_EVT_SERVICE_CHANGE */
    GATT_EvtClientFeatureChange_T         onClientFeatureChange;                /**< Handle @ref GATTS_EVT_CLIENT_FEATURE_CHANGE */
    GATT_EvtClientCccdListChange_T        onClientCccdListChange;               /**< Handle @ref GATTS_EVT_CLIENT_CCCDLIST_CHANGE */
    GATT_EvtProtocolAvailable_T           onClientProtocolAvailable;            /**< Handle @ref GATTC_EVT_PROTOCOL_AVAILABLE */
    GATT_EvtProtocolAvailable_T           onServerProtocolAvailable;            /**< Handle @ref GATTS_EVT_PROTOCOL_AVAILABLE */
} GATT_EventField_T;

/**@brief GATT callback event.*/
typedef struct  GATT_Event_T
{
    GATT_EventId_T          eventId;                                            /**< Event ID. */
    GATT_EventField_T       eventField;                                         /**< Event field. */
} GATT_Event_T;

/**@} */ //GATT_STRUCTS

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************
/**@addtogroup GATT_FUNS Functions
 * @{ */
 
/**@brief Initialize GATT Client module.
 *
 * @param[in] configuration             Bit-field configuring GATT Client configurable functions. @ref GATTC_CONFIGURATION_BITS for bit definition. \n
 *                                      - If manual mode is configured then the API @ref GATTC_HandleValueConfirm should be called to send a 
 *                                        confirmation for an indication when event @ref GATTC_EVT_HV_INDICATE is received.\n
 *                                      - If auto mode is configured then the GATT stack takes care of sending confirmation.
 *
 * @retval MBA_RES_SUCCESS              Success initialize GATT client module.
 * @retval MBA_RES_OOM                  Internal memory allocation failure.
*/
uint16_t GATTC_Init(uint16_t configuration);

/**
 *@brief Initialize GATT Server module.
 *
 *@param[in] configuration              Bit-field configuring GATT Server configurable functions. @ref GATTS_CONFIGURATION_BITS for bit definition.
 *
 *@retval MBA_RES_SUCCESS               Success initialize GATT server module.
 *@retval MBA_RES_OOM                   Internal memory allocation failure.
*/
uint16_t GATTS_Init(uint16_t configuration);

/**
 *@brief GATT Client initiates a read operation to GATT Server when this API is called.
 *       This API should be used to read a Characteristic Value or Characteristic descriptor.
 *
 *@note  Read long attributes:
 *       - If the attribute is not long attribute, valueOffset should be set to 0 and Read request is sent to
 *         GATT Server by this API.
 *       - If the attribute is a long attribute then first (ATT_MTU-1) bytes are read with valueOffset set to 0
 *         (API uses Read Request) and rest of the bytes are read using appropriate Non-zero valueOffset (API
 *         uses Read Blob Request). The Read Blob Request should be initiated in the application by calling the API
 *         @ref GATTC_Read with non-zero valueOffset when the event @ref GATTC_EVT_READ_RESP is received.
 *         This should be repeated each time the event @ref GATTC_EVT_READ_RESP is received until expected number
 *         of bytes of the long attribute are read.
 *
 *@par Events generated
 *@ref GATTC_EVT_ERROR_RESP Generated when fail to read. \n
 *@ref GATTC_EVT_READ_RESP Generated when read successfully. \n
 *@ref ATT_EVT_TIMEOUT Generated when server does not respond the request.
 *
 *@param[in] connHandle                 Handle of the connection.
 *@param[in] charHandle                 Handle of the characteristic value or descriptor to be read.
 *@param[in] valueOffset                Non-zero offset value to initiate a read blob request.
 *
 *@retval MBA_RES_SUCCESS               Successfully starts the read operation.
 *@retval MBA_RES_OOM                   Internal memory allocation failure.
 *@retval MBA_RES_INVALID_PARA          Invalid parameters. Connection handle is not valid.
 *@retval MBA_RES_BUSY                  GATT Client is busy. Another request is ongoing.
 */
uint16_t GATTC_Read(uint16_t connHandle, uint16_t charHandle, uint16_t valueOffset);

/**
 *@brief GATT Client initiates a write operation to GATT Server.
 *       This API should be used to write a Characteristic Value or Characteristic descriptor.\n
 *       Refer @ref ATT_OPCODES (ATT_WRITE_REQ/ATT_WRITE_CMD/ATT_PREPARE_WRITE_REQ/ATT_EXECUTE_WRITE_REQ) for write types.
 *
 *@note  Write long attribute:
 *       - If the attribute is not long attribute, valueOffset should be set to 0 and writeType should be set to
 *         Write Request/Write Command as required.\n
 *       - If the attribute is a long attribute then first (ATT_MTU-3) bytes should be written with valueOffset set to 0
 *         and writeType set to @ref ATT_PREPARE_WRITE_REQ (See @ref GATTC_WriteParams_T) in the API.
 *         The subsequent prepare write request should be called with appropriate value Offset and next
 *         set of data when event @ref GATTC_EVT_WRITE_RESP is received.
 *         This should be repeated until expected number of bytes is queued up in the server. When
 *         event @ref GATTC_EVT_WRITE_RESP is received for last prepare write request, this API should be
 *         called with writeType set to @ref ATT_EXECUTE_WRITE_REQ and flags set to @ref GATT_EXEC_WRITE_FLAG_WRITE
 *         (See @ref GATTC_WriteParams_T)\n
 *
 *@par Events generated
 *@ref GATTC_EVT_ERROR_RESP Generated when fail to write. \n
 *@ref GATTC_EVT_WRITE_RESP Generated when write successfully. \n
 *@ref ATT_EVT_TIMEOUT Generated when server does not respond the request.
 *
 *@param[in] connHandle                 Handle of the connection to send write operation.
 *@param[in] p_writeParams              Pointer to the Write Request parameters. Refer @ref GATTC_WriteParams_T
 *
 *@retval MBA_RES_SUCCESS               Successfully starts the write operation.
 *@retval MBA_RES_FAIL                  Operation is not permitted.
 *@retval MBA_RES_OOM                   Internal memory allocation failure.
 *@retval MBA_RES_INVALID_PARA          Invalid parameters. One of the following reasons:\n
 *                                      - Connection handle is not valid\n
 *                                      - Invalid write parameters. See @ref GATTC_WriteParams_T for valid values.\n
 *@retval MBA_RES_NO_RESOURCE           No available resource to send write operation.
 *@retval MBA_RES_BUSY                  GATT Client is busy. Another request is ongoing.
 */
uint16_t GATTC_Write(uint16_t connHandle, GATTC_WriteParams_T *p_writeParams);

/**
 *@brief GATT Client sends Handle Value Confirmation to the GATT server when it receives a Handle Value Indication.
 *       It should be called to send a confirmation only if event @ref GATTC_EVT_HV_INDICATE is received.
 *       This event is generated if manual mode is configured (see @ref GATTC_CONFIG_MANUAL_CONFIRMATION) and an indication is
 *       received.
 *
 *@param[in] connHandle                 Handle of the connection to send Handle Value Confirmation.
 *
 *@retval MBA_RES_SUCCESS               Successfully starts the Handle Value Confirmation.
 *@retval MBA_RES_FAIL                  Operation is not permitted. Either Automatic mode is configured or an Indication was not received.
 *@retval MBA_RES_OOM                   Out Of Memory. Allocation of memory for internal data structure failed.
 *@retval MBA_RES_INVALID_PARA          Invalid parameters. Connection handle is not valid
 */
uint16_t GATTC_HandleValueConfirm(uint16_t connHandle);

/**
 *@brief GATT Client sends Exchange MTU Request to GATT Server.
 *       - If the requested MTU length is less than @ref BLE_ATT_DEFAULT_MTU_LEN then
 *       @ref BLE_ATT_DEFAULT_MTU_LEN is requested.
 *       - If the requested MTU length is greater than @ref BLE_ATT_MAX_MTU_LEN then
 *       @ref BLE_ATT_MAX_MTU_LEN is requested.
 *
 *@par Events generated
 *@ref GATTC_EVT_ERROR_RESP Generated when fail to exchange MTU. \n
 *@ref ATT_EVT_UPDATE_MTU Generated when MTU exchanges successfully. \n
 *@ref ATT_EVT_TIMEOUT Generated when server does not respond the request.
 *
 *@param[in] connHandle                 Handle of the connection to send Exchange MTU Request.
 *@param[in] mtuLen                     Requested MTU length (Range is @ref BLE_ATT_DEFAULT_MTU_LEN to @ref BLE_ATT_MAX_MTU_LEN, inclusive of both limits)
 *
 *@retval MBA_RES_SUCCESS               Successfully starts the Exchange MTU Request.
 *@retval MBA_RES_FAIL                  Operation rejected. This request cannot be performed over BR/EDR link.
 *@retval MBA_RES_OOM                   Internal memory allocation failure.
 *@retval MBA_RES_INVALID_PARA          Invalid connection handle.
 *@retval MBA_RES_BUSY                  GATT Client is busy. Another request is ongoing.
 */
uint16_t GATTC_ExchangeMTURequest(uint16_t connHandle, uint16_t mtuLen);

/**
 *@brief GATT Client configure preferred ATT MTU as GATT Client.\n
 *       When connection established with remote peer, GATT client will initiate MTU negotiation with remote peer.
 *       By default, @ref BLE_ATT_MAX_MTU_LEN will be used to negotiate with remote.
 *       If user sets preferred MTU, the set value will be used to negotiate with remote.
 *
 *@note  The API is optional. If preferred MTU is not set, @ref BLE_ATT_MAX_MTU_LEN will be used.
 *@note  Only preferred MTU setting provided in GAP central role. In GAP peripheral role, remote central will initiate MTU negotiation in most of the time.
 *@note  The setting won't be applied to the current connections. @ref GATTC_ExchangeMTURequest for MTU exchange in connected state.
 *
 *@param[in] preferredMtuCentral        Preferred ATT MTU when GAP role is central.
 *
 *@retval MBA_RES_SUCCESS               Successfully configured preferred MTU in GATT Client role.
 *@retval MBA_RES_INVALID_PARA          Invalid MTU value usage.
 */
uint16_t GATTC_SetPreferredMtu(uint16_t preferredMtuCentral);

/**
 *@brief GATT Client starts the discovery of all primary services when this API is called. All primary services in the
 *       handle range 0x0001 - 0xFFFF will be discovered with a single call to this API.\n
 *       The event @ref GATTC_EVT_DISC_PRIM_SERV_RESP may be generated multiple times until all services are discovered.\n
 *       Following events may be generated on the GATT client:
 *       - Event @ref GATTC_EVT_DISC_PRIM_SERV_RESP with procedureStatus in @ref GATT_EvtDiscPrimServResp_T set to
 *         continue. This indicates some services are found but the discovery of all services is not complete. (See p_attrData
 *         in @ref GATT_EvtDiscPrimServResp_T for extracting service data received.)\n
 *       - Event @ref GATTC_EVT_DISC_PRIM_SERV_RESP with procedureStatus in @ref GATT_EvtDiscPrimServResp_T set to
 *         Finish. This indicates termination of the procedure (End Handle for last found service is 0xFFFF. See p_attrData
 *         in @ref GATT_EvtDiscPrimServResp_T for End Group Handle of a discovered service)\n
 *       - Event @ref GATTC_EVT_ERROR_RESP with error code @ref ATT_ERRCODE_ATTRIBUTE_NOT_FOUND is generated.
 *         This indicates termination of the procedure. (End Group handle of last found service is less that 0xFFFF)\n
 *
 *
 *@par Events generated
 *@ref GATTC_EVT_ERROR_RESP Generated when service not found or discovery procedure is end. \n
 *@ref GATTC_EVT_DISC_PRIM_SERV_RESP Generated when services discovered from remote. \n
 *@ref ATT_EVT_TIMEOUT Generated when server does not respond the request.
 *
 *@param[in] connHandle                 Handle of the connection to discover the services for.
 *
 *@retval MBA_RES_SUCCESS               Successfully starts the discovering.
 *@retval MBA_RES_OOM                   Internal memory allocation failure.
 *@retval MBA_RES_INVALID_PARA          Invalid parameters. Connection handle is not valid.
 *@retval MBA_RES_BUSY                  GATT Client is busy. Another request is ongoing.
 */
uint16_t GATTC_DiscoverAllPrimaryServices(uint16_t connHandle);

/**
 *@brief GATT Client starts the procedure for discovering primary service by UUID within the given input handle range.
 *       Multiple instances of the primary service with specified UUID may be present on the GATT server.
 *       Hence, the event @ref GATTC_EVT_DISC_PRIM_SERV_BY_UUID_RESP may be generated multiple times until
 *       all the service instances are discovered.\n
 *       Following events may be generated:
 *       - Event @ref GATTC_EVT_DISC_PRIM_SERV_BY_UUID_RESP with procedureStatus in @ref GATT_EvtDiscPrimServByUuidResp_T set to
 *         continue. This indicates service instance(s) found but the discovery not complete (more instances may be present. See p_attrData
 *         in @ref GATT_EvtDiscPrimServByUuidResp_T for extracting service data received.)\n
 *       - Event @ref GATTC_EVT_DISC_PRIM_SERV_BY_UUID_RESP with procedureStatus in @ref GATT_EvtDiscPrimServByUuidResp_T set to
 *         Finish. This indicates termination of the procedure (End Group Handle of last found service instance is equal to End
 *         handle in input handle range (See @ref GATTC_DiscoverPrimaryServiceByUuidParams_T. p_attrData in @ref
 *         GATT_EvtDiscPrimServByUuidResp_T contains the End Group Handle of the service found.)
 *       - Event @ref GATTC_EVT_ERROR_RESP with error code @ref ATT_ERRCODE_ATTRIBUTE_NOT_FOUND is generated.
 *         This indicates termination of the procedure. (End Group handle of last found service is less that End handle in input handle range)\n
 *
 *
 *@par Events generated
 *@ref GATTC_EVT_ERROR_RESP Generated when service not found or discovery procedure is end. \n
 *@ref GATTC_EVT_DISC_PRIM_SERV_BY_UUID_RESP Generated when services discovered from remote. \n
 *@ref ATT_EVT_TIMEOUT Generated when server does not respond the request.
 *
 *@param[in] connHandle                 Handle of the connection to discover the services.
 *@param[in] p_discParams               Pointer to structure containing the UUID of the primary service and handle range to be queried.
 *
 *@retval MBA_RES_SUCCESS               Successfully starts the discovering.
 *@retval MBA_RES_OOM                   Internal memory allocation failure.
 *@retval MBA_RES_INVALID_PARA          Invalid parameters. Connection handle is not valid.
 *@retval MBA_RES_BUSY                  GATT Client is busy. Another request is ongoing.
 */
uint16_t GATTC_DiscoverPrimaryServiceByUUID(uint16_t connHandle, GATTC_DiscoverPrimaryServiceByUuidParams_T *p_discParams);

/**
 *@brief GATT Client starts discovery of all characteristics within the given handle range when this API is called.\n
 *       Following events may be generated:
 *       - Event @ref GATTC_EVT_DISC_CHAR_RESP with procedureStatus in @ref GATT_EvtDiscCharResp_T set to
 *         continue. This indicates characteristic declarations are found but the discovery is not yet complete (more declarations
 *         may be present). See p_attrData in @ref GATT_EvtDiscCharResp_T for extracting the characteristic details.\n
 *       - Event @ref GATTC_EVT_DISC_CHAR_RESP with procedureStatus in @ref GATT_EvtDiscCharResp_T set to
 *         Finish. This indicates termination of the procedure (Value handle of last found characteristic declaration is equal
 *         to end handle of input handle range)\n
 *       - Event @ref GATTC_EVT_ERROR_RESP with error code @ref ATT_ERRCODE_ATTRIBUTE_NOT_FOUND is generated.
 *         This indicates termination of the procedure. (Last found Value handle is not same as end handle of the input
 *         handle range or no characteristic declaration found)\n
 *
 *
 *@par Events generated
 *@ref GATTC_EVT_ERROR_RESP Generated when characteristics not found or discovery procedure is end. \n
 *@ref GATTC_EVT_DISC_CHAR_RESP Generated when characteristics discovered from remote. \n
 *@ref ATT_EVT_TIMEOUT Generated when server does not respond the request.
 *
 *@param[in] connHandle                 Handle of the connection to discover the characteristics for.
 *@param[in] startHandle                Start of handle range to be queried.
 *@param[in] endHandle                  End of handle range to be queried.
 *
 *@retval MBA_RES_SUCCESS               Successfully starts discovering the characteristics.
 *@retval MBA_RES_OOM                   Internal memory allocation failure.
 *@retval MBA_RES_INVALID_PARA          Invalid parameters. Connection handle is not valid.
 *@retval MBA_RES_BUSY                  GATT Client is busy. Another request is ongoing.
 */
uint16_t GATTC_DiscoverAllCharacteristics(uint16_t connHandle, uint16_t startHandle, uint16_t endHandle);

/**
 *@brief GATT Client starts discovery of specific characteristics within the given handle range when this API is called.\n
 *       Following events may be generated:
 *       - Event @ref GATTC_EVT_DISC_CHAR_BY_UUID_RESP with procedureStatus in @ref GATT_EvtDiscCharResp_T set to
 *         continue. This indicates specific characteristics are found but the discovery is not yet complete (more characteristics
 *         may be present). See p_attrData in @ref GATT_EvtDiscCharResp_T for extracting the characteristic details.\n
 *       - Event @ref GATTC_EVT_DISC_CHAR_BY_UUID_RESP with procedureStatus in @ref GATT_EvtDiscCharResp_T set to
 *         Finish. This indicates termination of the procedure (Value handle of last found characteristic declaration is equal
 *         to end handle of input handle range). Please note that the response may be null if no characteristic found in last query. \n
 *       - Event @ref GATTC_EVT_ERROR_RESP with error code @ref ATT_ERRCODE_ATTRIBUTE_NOT_FOUND is generated.
 *         This indicates termination of the procedure. (Last found Value handle is not same as end handle of the input
 *         handle range or no characteristic declaration found)\n
 *
 *
 *@par Events generated
 *@ref GATTC_EVT_ERROR_RESP Generated when characteristics not found or discovery procedure is end. \n
 *@ref GATTC_EVT_DISC_CHAR_BY_UUID_RESP Generated when characteristics discovered from remote. \n
 *@ref ATT_EVT_TIMEOUT Generated when server does not respond the request.
 *
 *@param[in] connHandle                 Handle of the connection to discover the characteristics for.
 *@param[in] p_discParams               Pointer to structure containing the specific characteristic UUID to be discovered and the discovered handle range.
 *
 *@retval MBA_RES_SUCCESS               Successfully starts discovering the characteristics.
 *@retval MBA_RES_OOM                   Internal memory allocation failure.
 *@retval MBA_RES_INVALID_PARA          Invalid parameters. Connection handle is not valid.
 *@retval MBA_RES_BUSY                  GATT Client is busy. Another request is ongoing.
 */
uint16_t GATTC_DiscoverCharacteristicsByUUID(uint16_t connHandle, GATTC_DiscoverCharacteristicByUuidParams_T *p_discParams);

/**
 *@brief GATT Client starts discovering all descriptors by UUID within the given handle range when this API is called.\n
 *       Following events may be generated:
 *       - Event @ref GATTC_EVT_DISC_DESC_RESP with procedureStatus in @ref GATT_EvtDiscDescResp_T set to
 *         continue. This indicates descriptors are found but the discovery is not yet complete (more descriptors
 *         may be present)\n
 *       - Event @ref GATTC_EVT_DISC_DESC_RESP with procedureStatus in @ref GATT_EvtDiscDescResp_T set to
 *         Finish. This indicates termination of the procedure (Handle of last found descriptor is equal
 *         to end handle of input handle range)\n
 *       - Event @ref GATTC_EVT_ERROR_RESP with error code @ref ATT_ERRCODE_ATTRIBUTE_NOT_FOUND is generated.
 *         This indicates termination of the procedure. (Handle of last found descriptor is not same as end handle of the input
 *         handle range or no descriptor was found)\n
 *
 *
 *@par Events generated
 *@ref GATTC_EVT_ERROR_RESP Generated when characteristic descriptors not found or discovery procedure is end. \n
 *@ref GATTC_EVT_DISC_DESC_RESP Generated when characteristic descriptors discovered from remote. \n
 *@ref ATT_EVT_TIMEOUT Generated when server does not respond the request.
 *
 *@param[in] connHandle                 Handle of the connection to discover the descriptors for.
 *@param[in] startHandle                Start of the querying handle range.
 *@param[in] endHandle                  End of the querying handle range.
 *
 *@retval MBA_RES_SUCCESS               Successfully starts the discovering.
 *@retval MBA_RES_OOM                   Internal memory allocation failure.
 *@retval MBA_RES_INVALID_PARA          Invalid parameters. Connection handle is not valid.
 *@retval MBA_RES_BUSY                  GATT Client is busy. Another request is ongoing.
 */
uint16_t GATTC_DiscoverAllDescriptors(uint16_t connHandle, uint16_t startHandle, uint16_t endHandle);

/**
 *@brief GATT Client initiates read of characteristic value for the specified characteristic UUID
 *       within the given handle range when this API is called.
 *
 *@par Events generated
 *@ref GATTC_EVT_ERROR_RESP Generated when fail to read. \n
 *@ref GATTC_EVT_READ_USING_UUID_RESP Generated when read successfully. \n
 *@ref ATT_EVT_TIMEOUT Generated when server does not respond the request.
 *
 *@param[in] connHandle                 Handle of the connection to read characteristic value for.
 *@param[in] p_readParams               Pointer to structure containing the UUID of the Characteristic and handle range to be queried.
 *
 *@retval MBA_RES_SUCCESS               Successfully initiates read using UUID procedure.
 *@retval MBA_RES_OOM                   Internal memory allocation failure.
 *@retval MBA_RES_INVALID_PARA          Invalid parameters. Connection handle is not valid.
 *@retval MBA_RES_BUSY                  GATT Client is busy. Another request is ongoing.
 */
uint16_t GATTC_ReadUsingUUID(uint16_t connHandle, GATTC_ReadByTypeParams_T *p_readParams);

/**
 *@brief This API registers service to GATT server.
 *
 *@note  Note that the start handle of the registering service should be greater than @ref GATTS_APP_SVC_START_HDL.
 *
 *@param[in] p_service                  Pointer to the registering service information.
 *@param[in] numAttributes              Number of the attributes in the registering service.
 *
 *@retval MBA_RES_SUCCESS               Successfully registering the service
 *@retval MBA_RES_FAIL                  Fail to register the service. The assigned attribute handles in the service conflict or \n
 *                                      the start handle of the service is smaller than @ref GATTS_APP_SVC_START_HDL.
 */
uint16_t GATTS_AddService(GATTS_Service_T *p_service, uint8_t numAttributes);

/**
 *@brief GATT server removes registered service.
 *
 *@param[in] startHandle                The start handle of the registered service.
 *
 *@retval MBA_RES_SUCCESS               Successfully remove the registered service.
 *@retval MBA_RES_FAIL                  Fail to remove the service. Service with the assigned start handle does not exist.
 */
uint16_t GATTS_RemoveService(uint16_t startHandle);

/**
 *@brief GATT Server sends Handle Value Notification or Indication to GATT Client when this API is called.
 *       sendType in @ref GATTS_HandleValueParams_T determines if a notification or Indication is sent.
 *       - If sendType is set to @ref ATT_HANDLE_VALUE_NTF then a notification is sent if notify property is set for the
 *         characteristic and Notification is enabled in its CCCD.
 *       - If sendType is set to @ref ATT_HANDLE_VALUE_IND then an Indication is sent if Indicate property is set for the
 *         characteristic and Indication is enabled in its CCCD.\n
 *
 *
 *@par Events generated
 *@ref GATTS_EVT_HV_CONFIRM Generated if indication is successfully sent. \n
 *@ref ATT_EVT_TIMEOUT Generated when client does not respond the indication.
 *
 *@param[in] connHandle                 Handle of the connection to send Handle Value Notification/Indication.
 *@param[in] p_hvParams                 Pointer to the Handle Value Notification/Indication Parameters.
 *
 *@retval MBA_RES_SUCCESS               Successfully starts the Handle Value Notification/Indication
 *@retval MBA_RES_FAIL                  Operation is not permitted. Memory not available to send notification/indication.
 *@retval MBA_RES_OOM                   Internal memory allocation failure.
 *@retval MBA_RES_INVALID_PARA          Invalid parameters. One of the following errors may have occurred:
 *                                      - Connection handle is not valid\n
 *                                      - Parameters specified in @ref GATTS_HandleValueParams_T have invalid/out of range values\n
 *                                      - The sending data length is exceeded the MTU.
 *                                      - Notification/Indication has to be sent but either Notify/Indicate property is not set
 *                                        for the characteristic or Notification/Indication is not enabled in the CCCD
 *@retval MBA_RES_BUSY                  Send indication when another indication is ongoing. Only available in sending indication.
 *@retval MBA_RES_NO_RESOURCE           No available resource to send the handle value.
 */
uint16_t GATTS_SendHandleValue(uint16_t connHandle, GATTS_HandleValueParams_T *p_hvParams);

/**
 *@brief GATT Server sends the read/read blob response when this API is called. responseType in
 *       @ref GATTS_SendReadRespParams_T indicates if the response is for read request or read blob request.\n
 *       Response to the GATT client is sent only if:
 *       - API initiates a Read response and a Read request was received by GATT server.
 *       - API initiates a Read Blob response and a Read Blob request was received by GATT server.
 *
 *
 *@note  If the attribute setting of the attribute is set as @ref SETTING_MANUAL_READ_RSP, the event @ref GATTS_EVT_READ
 *       with readType is @ref ATT_READ_REQ or @ref ATT_READ_BLOB_REQ will be sent to application when GATT server receives these 
 *       requests performing on this attribute. In this case, application need to call this API to send read response or 
 *       send error response if the request is not permitted. \n
 *       This API should be called to send the response only when event @ref GATTS_EVT_READ is received.
 *
 *@param[in] connHandle                 Handle of the connection to send the read response.
 *@param[in] p_respParams               Pointer to Read Response parameters. See @ref GATTS_SendReadRespParams_T
 *
 *@retval MBA_RES_SUCCESS               Successfully starts to send the read response.
 *@retval MBA_RES_FAIL                  Operation is not permitted as Read response/Read Blob response transmission was requested
 *                                      but read request/read blob request was not received
 *@retval MBA_RES_OOM                   Internal memory allocation failure.
 *@retval MBA_RES_INVALID_PARA          Invalid parameters. Connection handle is not valid.
 */
uint16_t GATTS_SendReadResponse(uint16_t connHandle, GATTS_SendReadRespParams_T *p_respParams);

/**
 *@brief GATT Server sends an error response. This API should be called when a request event is received by the application.
 *       The request is not processed by the GATT server. \n
 *       For example, This API may be called after Application receives Write Request event (@ref GATTS_EVT_WRITE)
 *       but request cannot be processed as the attribute value does not have Write permission.
 *
 *@param[in] connHandle                 Handle of the connection to send the error response.
 *@param[in] p_errParams                Pointer to Error Response parameters. See @ref GATTS_SendErrRespParams_T.
 *
 *@retval MBA_RES_SUCCESS               Successfully initiates an error response.
 *@retval MBA_RES_FAIL                  Operation is not permitted. The error response is not for the received request.
 *                                      i.e. The reqOpcode field in the @ref GATTS_SendErrRespParams_T is the matched to
 *                                      the receiving request.
 *@retval MBA_RES_OOM                   Internal memory allocation failure.
 *@retval MBA_RES_INVALID_PARA          Invalid parameters. Connection handle is not valid.
 */
uint16_t GATTS_SendErrorResponse(uint16_t connHandle, GATTS_SendErrRespParams_T *p_errParams);

/**
 *@brief GATT Server sends the Read By Type response.
 *       This API should be called to send the response only when event @ref GATTS_EVT_READ is received.
 *
 *@note  If the attribute setting of the attribute is set as @ref SETTING_MANUAL_READ_RSP, the event @ref GATTS_EVT_READ
 *       with readType is @ref ATT_READ_BY_TYPE_REQ will be sent to application when GATT server receives the request performing
 *       on this attribute. In this case, application need to call this API to send read by type response or send error 
 *       response if the request is not permitted.
 *
 *@param[in] connHandle                 Handle of the connection to send the read by type response.
 *@param[in] p_respParams               Pointer to Read By Type Response parameters. See @ref GATTS_SendReadByTypeRespParams_T
 *
 *@retval MBA_RES_SUCCESS               Successfully starts to send the read by type response.
 *@retval MBA_RES_FAIL                  Operation is not permitted if GATT server does not receive read by type request before.
 *@retval MBA_RES_OOM                   Internal memory allocation failure.
 *@retval MBA_RES_INVALID_PARA          Invalid parameters. Connection handle is not valid.
 */
uint16_t GATTS_SendReadByTypeResponse(uint16_t connHandle, GATTS_SendReadByTypeRespParams_T *p_respParams);

/**
 *@brief GATT Server sends the write/prepare write/execute write response when this API is called. ResponseType in
 *       @ref GATTS_SendWriteRespParams_T indicates if the response is for write request, prepare write request
 *       or execute write request.\n
 *       Response to the GATT client is sent only if:
 *       - API initiates a Write response and a Write request was received by GATT server.
 *       - API initiates a Prepare Write response and a Prepare Write request was received by GATT server.
 *       - API initiates a Execute Write response and a Execution Write request was received by GATT server. 
 *
 *
 *@note  If the attribute setting of the attribute is set as @ref SETTING_MANUAL_WRITE_RSP, the event @ref GATTS_EVT_WRITE
 *       with writeType is @ref ATT_WRITE_REQ or @ref ATT_PREPARE_WRITE_REQ or @ref ATT_EXECUTE_WRITE_REQ will be sent to 
 *       application when GATT server receives these requests performing on this attribute.
 *       In this case, application need to call this API to send write response or send error response if the request 
 *       is not permitted. \n
 *       This API should be called to send the response only when event @ref GATTS_EVT_WRITE is received.
 *
 *@param[in] connHandle                 Handle of the connection to send the write response.
 *@param[in] p_respParams               Pointer to Write Response parameters. See @ref GATTS_SendWriteRespParams_T
 *
 *@retval MBA_RES_SUCCESS               Successfully starts to send the write response.
 *@retval MBA_RES_FAIL                  Operation is not permitted as Write response/Prepare Write response/Execute Write response
 *                                      transmission was requested but write request/prepare write request/execute write request 
 *                                      was not received.
 *@retval MBA_RES_OOM                   Internal memory allocation failure.
 *@retval MBA_RES_INVALID_PARA          Invalid parameters. Connection handle is not valid.
 */
uint16_t GATTS_SendWriteResponse(uint16_t connHandle, GATTS_SendWriteRespParams_T *p_respParams);

/**
 *@brief This API is used to enable the service change and notify clients that service table is changed.
 *       Service might be added or removed. After all the changes, this API is used to enable the service change.
 *       All the connected client will receive indication if the indication in configured.
 *
 *@retval MBA_RES_SUCCESS               Successfully notify the connected devices th service change.
 */
uint16_t GATTS_ServiceChanged();

/**
 *@brief Notify GATT Server the relevant bonding information of the connection.
 *
 *@note  This function is suggested to be called once after connected whether the connection is bonded or not.
 *       The GATT Server requires bonding information when processing some requests on bonded connection. \n
 *       If the GATT Server initialized with gatt caching supported, i.e. @ref GATTS_Init with @ref GATTS_CONFIG_CACHING_SUPPORT,
 *       this function must be called after the link connected (whether bonded link or not). The stack GATT will start process 
 *       packets after the bonded information get.
 *
 *@param[in] connHandle                 Connection handle
 *@param[in] p_gattsParams              GATTS required bonding parameters. See @ref GATTS_BondingParams_T. Set NULL if it is non-bonded connection.
 *@param[in] numOfCccds                 Number of CCCDs of this bonded connection. Set zero if it is non-bonded connection.
 *@param[in] p_cccdList                 CCCDs list of this bonded connection. @ref GATTS_CccdList_T. Set NULL if it is non-bonded connection.
 *
 *@retval MBA_RES_SUCCESS               Successfully notify GATT updated parameters.
 *@retval MBA_RES_INVAIID_PARA          The connection handle is invalid.
 */
uint16_t GATTS_UpdateBondingInfo(uint16_t connHandle, GATTS_BondingParams_T *p_gattsParams, uint8_t numOfCccds, GATTS_CccdList_T *p_cccdList);

/**
 *@brief Gets the attribute value of a valid attribute from GATT Server. If the attribute is permitted to read, value will be return
 *       in application provided buffer.
 *
 *@note  The format of the attribute value is raw-data.
 *
 *@param[in] attrHandle                 Attribute Handle.
 *@param[out] p_attrValue               Pointer of buffer to store getting attribute value. Valid if API return status is success.
 *@param[in] p_attrLength               As input parameter, describe size of application provided buffer. \n
 *                                      As output parameter, describe actual size of getting attribute value when API return status is success.
 *
 *@retval MBA_RES_SUCCESS               Successfully gets the attribute value.
 *@retval MBA_RES_FAIL                  Operation is not permitted. The attribute handle is valid but the attribute can't be read.
 *@retval MBA_RES_INVALID_PARA          Invalid parameters.
 */
uint16_t GATTS_GetHandleValue(uint16_t attrHandle, uint8_t *p_attrValue, uint16_t *p_attrLength);

/**
 *@brief GATT Server configures the build-in GATT service.
 *       Optional service "GATT Service" can be configured enable/disable.
 *
 *@note  The function is suggested to be called when initialization. Also, can't be called in connected state.
 *       The configured option (enable/disable) should not be changed if the function is called several times.
 *       Otherwise, service change situation need to be considered in the multiple configuring build-in services case.
 *
 *@param[in] p_gattServiceOptions       Pointer to the configuration structure of GATT Service. See @ref GATTS_GattServiceOptions_T.
 *
 *@retval MBA_RES_SUCCESS               Successfully configured the build-in Services.
 *@retval MBA_RES_FAIL                  Operation is not permitted.
 */
uint16_t GATTS_ConfigureBuildInService(GATTS_GattServiceOptions_T *p_gattServiceOptions);

/**
 *@brief GATT Server configures preferred ATT MTU.
 *       By default, @ref BLE_ATT_MAX_MTU_LEN will be used to respond exchange MTU request from remote client.
 *       User specified ATT MTU will be used if the preferred MTU is configured.
 *
 *@note  The API is optional. @ref BLE_ATT_MAX_MTU_LEN will be used to respond if no configuration.
 *
 *@param[in] preferredMtuPeriph         Preferred ATT MTU when GAP role is peripheral.
 *@param[in] preferredMtuCentral        Preferred ATT MTU when GAP role is central.
 *
 *@retval MBA_RES_SUCCESS               Successfully configured preferred MTU in GATT Server role.
 *@retval MBA_RES_INVALID_PARA          Invalid MTU value usage.
 */
uint16_t GATTS_SetPreferredMtu(uint16_t preferredMtuPeriph, uint16_t preferredMtuCentral);

/**@} */ //GATT_FUNS
#endif

/**
  @}
 */

