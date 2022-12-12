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
  Host HCI Definitions Header File

  Company:
    Microchip Technology Inc.

  File Name:
    host_hci_defs.h

  Summary:
    This file contains the HCI definitions for Host HCI usage.

  Description:
    This file contains the HCI definitions for Host HCI usage.
 *******************************************************************************/


#ifndef HOST_HCI_DEFS_H
#define HOST_HCI_DEFS_H

/** @defgroup HOST_HCI HOST HCI
 *  @brief Bluetooth Host Controller Interface definitions
 *  @{ */

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************

/**@addtogroup HOST_HCI_DEFINES Defines
 * @{ */

/**@defgroup HCI_BD_ADDRESS_LEN Bluetooth Device Address length
 * @brief The definition of Bluetooth Device Address length.
 * @{ */
#define HCI_BD_ADDRESS_LEN                                  0x06        /**< Length of Bluetooth Device address. */
/** @} */

/**@defgroup HCI_ADV_DEFS Advertising definitions
 * @brief The definition of parameters in advertising
 * @{ */
#define HCI_MAX_ADV_LENGTH                                  0x1F        /**< Maximum length of advertising data in bytes. */
#define HCI_MAX_ADV_REPORTS                                 0x01        /**< Implemented maximum number of advertising report in @ref HCI_EvtLeAdvReport_T event. Number defined in the spec. is 0x19. */
/** @} */

/**@defgroup HCI_KEY_LEN Maximum key length
 * @brief The definition of maximum key length
 * @{ */
#define HCI_MAX_KEY_LENGTH                                  0x10        /**< Maximum length of key in bytes. */
/** @} */

/**@defgroup HCI_MAX_EXT_ADV_SET Maximum number of extended advertising sets
 * @brief The definition of maximum extended advertising sets
 * @{ */
#define HCI_MAX_EXTENDED_ADVERTISING_SETS                   0x3F        /**< Maximum number of extended advertising sets defined in HCI_LE_SET_EXTENDED_ADVERTISING_ENABLE command. */
/** @} */

/**@defgroup HCI_MAX_EXT_ADV_DATA_LEN Maximum length of extended advertising data
 * @brief The definition of maximum length of extended advertising data
 * @{ */
#define HCI_CMD_MAX_EXTENDED_ADVERTISING_DATA_LENGTH        0xFB        /**< Maximum length of extended advertising data defined in HCI_LE_SET_EXTENDED_ADVERTISING_DATA command. */
#define HCI_EVT_MAX_EXTENDED_ADVERTISING_DATA_LENGTH        0xE5        /**< Maximum length of extended advertising data defined in HCI_LE_EXTENDED_ADVERTISING_REPORT command. */
/** @} */

/**@defgroup HCI_MAX_PADV_DATA_LEN Maximum length of periodic advertising data
 * @brief The definition of maximum length of periodic advertising data
 * @{ */
#define HCI_CMD_MAX_PERIODIC_ADVERTISING_DATA_LENGTH        0xFC        /**< Maximum length of periodic advertising data defined in HCI_LE_SET_PERIODIC_ADVERTISING_DATA command. */
#define HCI_EVT_MAX_PERIODIC_ADVERTISING_DATA_LENGTH        0xF7        /**< Maximum length of periodic advertising data defined in HCI_LE_PERIODIC_ADVERTISING_REPORT event. */
/** @} */

/**@defgroup HCI_EXT_SCAN_PHY_NUM Number of supported PHYs in LE extended scan
 * @brief The definition of number of supported PHYs in LE extended scan
 * @{ */
#define HCI_SUPPORTED_EXT_SCAN_PHYS                         0x02        /**< Number of supported PHYs in LE extended scan defined in HCI_LE_SET_EXTENDED_SCAN_PARAM command. */
/** @} */

/**@defgroup HCI_EXT_CREATE_CONN_PHY_NUM Number of supported PHYs in LE extended create connection
 * @brief The definition of number of supported PHYs in LE extended create connection
 * @{ */
#define HCI_SUPPORTED_EXT_CREATE_CONNECTION_PHYS            0x03        /**< Number of supported PHYs in LE extended create connection defined in HCI_LE_SET_EXTENDED_CREATE_CONNECTION command. */
/** @} */

/**@defgroup HCI_MAX_CONN_NUM Maximum allowed connections
 * @brief The definition of number of allowed connections
 * @{ */
#define HCI_MAX_NUM_CONN_HANDLE                             0x06        /**< Maximum allowed connections. */
/** @} */

/**@defgroup HCI_FEATURES_LENGTH Length of Bit Mask List of supported features
 * @brief The definition of length of Bit Mask List of supported features
 * @{ */
#define HCI_FEATURES_BITMASK_LENGTH                         0x08        /**< Length of Bit Mask List of supported features. */
/** @} */

/**@defgroup HCI_LTK_RAND_SIZE Size of random number when encryption with LTK
 * @brief The definition of size of random number when encryption with LTK
 * @{ */
#define HCI_LTK_RANDOM_SIZE                                 0x08        /**< Size of random number (in octets). */
/** @} */

/**@defgroup HCI_LE_TRANSMITTER_SPL_RANGE The range of Switching Pattern Length
 * @brief The definition of switching wattern length.
 * @{ */
#define HCI_LE_TRANSMITTER_SPL_MIN                          0x02        /**< Minimum value of Switching Pattern Length.*/
#define HCI_LE_TRANSMITTER_SPL_MAX                          0x4B        /**< Maximum value of Switching Pattern Length.*/
/** @} */

/**@defgroup HCI_PHY_OPTION LE PHY definitions
 * @brief The definition of LE PHYs
 * @{ */
#define HCI_PHY_OPTION_1M                                   (1 << 0)    /**< LE 1M PHY */
#define HCI_PHY_OPTION_2M                                   (1 << 1)    /**< LE 2M PHY */
#define HCI_PHY_OPTION_CODED                                (1 << 2)    /**< LE Coded PHY */
/** @} */

/**@defgroup HCI_OGF HCI OpCode Group Field definition
 * @brief The definition of HCI OpCode Group Field
 * @{ */
#define HCI_LC                                              0x01        /**< Link Control commands. */
#define HCI_LP                                              0x02        /**< Link Policy commands. */
#define HCI_HC                                              0x03        /**< Host Controller and Baseband commands. */
#define HCI_IP                                              0x04        /**< Informational Parameters commands. */
#define HCI_SP                                              0x05        /**< Status Parameters commands. */
#define HCI_TC                                              0x06        /**< Testing Commands. */
#define HCI_LE_CTRL                                         0x08        /**< LE Controller commands. */
#define MANUFACTURER_SPEC                                   0x3F        /**< Vendor-Specific debug commands. */
/** @} */

/**@defgroup HCI_OCF_LC HCI OpCode Command Field definitions of Link Control commands group
 * @brief The definitions of HCI OpCode Command Field of Link Control controller commands group
 * @{ */
#define HCI_DISCONNECT                                      0x06        /**< Disconnect command. */
/** @} */

/**@defgroup HCI_OCF_HC HCI OpCode Command Field definitions of Host Controller and Baseband commands group
 * @brief The definitions of HCI OpCode Command Field of Host Controller and Baseband controller commands group
 * @{ */
#define HCI_READ_AUTHENTICATED_PAYLOAD_TIMEOUT              0x7B        /**< Read Authenticated Payload Timeout command. */
#define HCI_WRITE_AUTHENTICATED_PAYLOAD_TIMEOUT             0x7C        /**< Write Authenticated Payload Timeout command. */
/** @} */

/**@defgroup HCI_OCF_IP HCI OpCode Command Field definitions of Informational Parameters commands group
 * @brief The definitions of HCI OpCode Command Field of Informational Parameters controller commands group
 * @{ */
#define HCI_READ_BD_ADDR                                    0x09        /**< Read BD_ADDR command. */
/** @} */

/**@defgroup HCI_OCF_SP HCI OpCode Command Field definitions of Status Parameters commands group
 * @brief The definitions of HCI OpCode Command Field of Status Parameters controller commands group
 * @{ */
#define HCI_READ_RSSI                                       0x05        /**< Read RSSI command. */
/** @} */

/**@defgroup HCI_OCF_LE HCI OpCode Command Field definitions of LE controller commands group
 * @brief The definitions of HCI OpCode Command Field of LE controller commands group
 * @{ */
#define HCI_LE_SET_RANDOM_ADDRESS                           0x05        /**< LE Set Random Address command. */
#define HCI_LE_SET_ADVERTISING_PARAMS                       0x06        /**< LE Set Advertising Parameters command. */
#define HCI_LE_SET_ADVERTISING_DATA                         0x08        /**< LE Set Advertising Data command. */
#define HCI_LE_SET_SCAN_RESPONSE_DATA                       0x09        /**< LE Set Scan Response Data command. */
#define HCI_LE_SET_ADVERTISING_ENABLE                       0x0A        /**< LE Set Advertising Enable command. */
#define HCI_LE_SET_SCAN_PARAMS                              0x0B        /**< LE Set Scan Parameters command. */
#define HCI_LE_SET_SCAN_ENABLE                              0x0C        /**< LE Set Scan Enable command. */
#define HCI_LE_CREATE_CONNECTION                            0x0D        /**< LE Create Connection command. */
#define HCI_LE_CREATE_CONNECTION_CANCEL                     0x0E        /**< LE Create Connection Cancel command. */
#define HCI_LE_CLEAR_FILTER_ACCEPT_LIST                     0x10        /**< LE Clear Filter Accept List command. */
#define HCI_LE_ADD_DEVICE_TO_FILTER_ACCEPT_LIST             0x11        /**< LE Add Device To Filter Accept List command. */
#define HCI_LE_CONNECTION_UPDATE                            0x13        /**< LE Connection Update command. */
#define HCI_LE_SET_HOST_CHANNEL_CLASSIFICATION              0x14        /**< LE Set Host Channel Classification command. */
#define HCI_LE_READ_CHANNEL_MAP                             0x15        /**< LE Read Channel Map command. */
#define HCI_LE_READ_REMOTE_FEATURES                         0X16        /**< LE Read Remote Features command. */
#define HCI_LE_ENABLE_ENCRYPTION                            0x19        /**< LE Enable Encryption command. */
#define HCI_LE_LONG_TERM_KEY_REQ_REPLY                      0x1A        /**< LE Long Term Key Request Reply command. */
#define HCI_LE_LONG_TERM_KEY_REQ_NEGATIVE_REPLY             0x1B        /**< LE Long Term Key Request Negative Reply command. */
#define HCI_LE_RECEIVER_TEST_V1                             0x1D        /**< LE Receiver Test command (version 1). */
#define HCI_LE_TRANSMITTER_TEST_V1                          0x1E        /**< LE Transmitter Test command (version 1). */
#define HCI_LE_TEST_END                                     0x1F        /**< LE Test End command. */
#define HCI_LE_REMOTE_CONN_PARAM_REQ_REPLY                  0x20        /**< LE Remote Connection Parameter Request Reply command. */
#define HCI_LE_REMOTE_CONN_PARAM_REQ_NEGATIVE_REPLY         0x21        /**< LE Remote Connection Parameter Request Negative Reply command. */
#define HCI_LE_SET_DATA_LENGTH                              0x22        /**< LE Set Data Length command. */
#define HCI_LE_ADD_DEVICE_TO_RESOLVING_LIST                 0x27        /**< LE Add Device To Resolving List command. */
#define HCI_LE_CLEAR_RESOLVING_LIST                         0x29        /**< LE Clear Resolving List command. */
#define HCI_LE_SET_ADDR_RESOLUTION_ENABLE                   0x2D        /**< LE Set Address Resolution Enable command. */
#define HCI_LE_SET_RPA_TIMEOUT                              0x2E        /**< LE Set Resolvable Private Address Timeout. */
#define HCI_LE_READ_PHY                                     0x30        /**< LE Read PHY command. */
#define HCI_LE_SET_DEFAULT_PHY                              0x31        /**< LE Set Default PHY command. */
#define HCI_LE_SET_PHY                                      0x32        /**< LE Set PHY command. */
#define HCI_LE_RECEIVER_TEST_V2                             0x33        /**< LE Receiver Test command (version 2). */
#define HCI_LE_TRANSMITTER_TEST_V2                          0x34        /**< LE Transmitter Test command (version 2). */
#define HCI_LE_SET_ADVERTISING_SET_RANDOM_ADDR              0x35        /**< LE Set Advertising Set Random Address command.  */
#define HCI_LE_SET_EXTENDED_ADVERTISING_PARAM               0x36        /**< LE Set Extended Advertising Parameters command. */
#define HCI_LE_SET_EXTENDED_ADVERTISING_DATA                0x37        /**< LE Set Extended Advertising Data command. */
#define HCI_LE_SET_EXTENDED_SCAN_RSP_DATA                   0x38        /**< LE Set Extended Scan Response Data command. */
#define HCI_LE_SET_EXTENDED_ADVERTISING_ENABLE              0x39        /**< LE Set Extended Advertising Enable command. */
#define HCI_LE_REMOVE_ADVERTISING_SET                       0x3C        /**< LE Remove Advertising Set command. */
#define HCI_LE_CLEAR_ADVERTISING_SETS                       0x3D        /**< LE Clear Advertising Sets command. */
#define HCI_LE_SET_PERIODIC_ADVERTISING_PARAM               0x3E        /**< LE Set Periodic Advertising Parameters command. */
#define HCI_LE_SET_PERIODIC_ADVERTISING_DATA                0x3F        /**< LE Set Periodic Advertising Data command. */
#define HCI_LE_SET_PERIODIC_ADVERTISING_ENABLE              0x40        /**< LE Set Periodic Advertising Enable command. */
#define HCI_LE_SET_EXTENDED_SCAN_PARAM                      0x41        /**< LE Set Extended Scan Parameters command. */
#define HCI_LE_SET_EXTENDED_SCAN_ENABLE                     0x42        /**< LE Set Extended Scan Enable command. */
#define HCI_LE_EXTENDED_CREATE_CONNECTION                   0x43        /**< LE Extended Create Connection command. */
#define HCI_LE_PERIODIC_ADVERTISING_CREATE_SYNC             0x44        /**< LE Periodic Advertising Create Sync command. */
#define HCI_LE_PERIODIC_ADVERTISING_CREATE_SYNC_CANCEL      0x45        /**< LE Periodic Advertising Create Sync Cancel command. */
#define HCI_LE_PERIODIC_ADVERTISING_TERMINATE_SYNC          0x46        /**< LE Periodic Advertising Terminate Sync command. */
#define HCI_LE_ADD_DEV_TO_PERIODIC_ADVERTISER_LIST          0x47        /**< LE Add Device To Periodic Advertiser List command. */
#define HCI_LE_CLEAR_PERIODIC_ADVERTISER_LIST               0x49        /**< LE Clear Periodic Advertiser List command. */
#define HCI_LE_READ_TRANSMIT_POWER                          0x4B        /**< LE Read Transmit Power command. */
#define HCI_LE_SET_PRIVACY_MODE                             0x4E        /**< LE Set Privacy Mode command. */
#define HCI_LE_RECEIVER_TEST_V3                             0x4F        /**< LE Receiver Test command (version 3). */
#define HCI_LE_TRANSMITTER_TEST_V3                          0x50        /**< LE Transmitter Test command (version 3). */
#define HCI_LE_SET_PERIODIC_ADVERTISING_RECEIVE_ENABLE      0x59        /**< LE Set Periodic Advertising Reveive Enable command. */
#define HCI_LE_ENHANCED_READ_TRANSMIT_POWER_LEVEL           0x76        /**< LE Enhanced Read Transmit Power Level command. */
#define HCI_LE_READ_REMOTE_TRANSMIT_POWER_LEVEL             0x77        /**< LE Read Remote Transmit Power Level command. */
#define HCI_LE_SET_TRANSMIT_POWER_REPORTING_ENABLE          0x7A        /**< LE Set Transmit Power Reporting Enable command. */
#define HCI_LE_TRANSMITTER_TEST_V4                          0x7B        /**< LE Transmitter Test command (version 4). */
/** @} */

/**@defgroup HCI_EVT_CODE HCI event code definition
 * @brief The definitions of HCI event code.
 * @{ */
#define HCI_DISCONNECTION_COMPLETE                          0x05        /**< Disconnection Complete event. */
#define HCI_ENCRYPTION_CHANGE                               0x08        /**< Encryption Change event. */
#define HCI_READ_REMOTE_VERSION_INFORMATION_COMPLETE        0x0C        /**< Read Remote Version Information Complete event. */
#define HCI_COMMAND_COMPLETE                                0x0E        /**< Command Complete event. */
#define HCI_COMMAND_STATUS                                  0x0F        /**< Command Status event. */
#define HCI_NBR_OF_COMPLETED_PACKETS                        0x13        /**< Number Of Completed Packets event. */
#define HCI_ENCRYPTION_KEY_REFRESH_COMPLETE                 0x30        /**< Encryption Key Refresh Complete event. */
#define HCI_LE_META_EVENT                                   0x3E        /**< LE Meta event. */
#define HCI_AUTHENTICATED_PAYLOAD_TIMEOUT_EXPIRED           0x57        /**< Authenticated Payload Timeout Expired event. */
/** @} */

/**@defgroup HCI_LE_META_SUB_EVT_CODE HCI subevent code definition of LE_META event
 * @brief The definitions of subevent code of HCI LE_META event.
 * @{ */
#define HCI_LE_CONNECT_COMPLETE                             0x01        /**< LE Connection Complete event. */
#define HCI_LE_ADVERTISING_REPORT                           0x02        /**< LE Advertising Report event. */
#define HCI_LE_CONNECTION_UPDATE_COMPLETE                   0x03        /**< LE Connection Update Complete event. */
#define HCI_LE_READ_REMOTE_FEATURES_COMPLETE                0x04        /**< LE Read Remote Features Complete event. */
#define HCI_LE_LONG_TERM_KEY_REQUEST                        0x05        /**< LE Long Term Key Request event. */
#define HCI_LE_REMOTE_CONNECTION_PARAMETER_REQUEST          0x06        /**< LE Remote Connection Parameter Request event. */
#define HCI_LE_DATA_LENGTH_CHANGE                           0x07        /**< LE Data Length Change event. */
#define HCI_LE_ENHANCED_CONNECTION_COMPLETE                 0x0A        /**< LE Enhanced Connection Complete event. */
#define HCI_LE_DIRECT_ADVERTISING_REPORT                    0x0B        /**< LE Directed Advertising Report event. */
#define HCI_LE_PHY_UPDATE_COMPLETE                          0x0C        /**< LE PHY Update Complete event. */
#define HCI_LE_EXTENDED_ADVERTISING_REPORT                  0x0D        /**< LE Extended Advertising Report event. */
#define HCI_LE_PERIODIC_ADVERTISING_SYNC_ESTABLISHED        0x0E        /**< LE Periodic Advertising Sync Established event. */
#define HCI_LE_PERIODIC_ADVERTISING_REPORT                  0x0F        /**< LE Periodic Advertising Report event. */
#define HCI_LE_PERIODIC_ADVERTISING_SYNC_LOST               0x10        /**< LE Periodic Advertising Sync Lost event. */
#define HCI_LE_SCAN_TIMEOUT                                 0x11        /**< LE Scan Timeout event. */
#define HCI_LE_ADVERTISING_SET_TERMINATED                   0x12        /**< LE Advertising Set Terminated event. */
#define HCI_LE_SCAN_REQUEST_RECEIVED                        0x13        /**< LE Scan Request Received event. */
#define HCI_LE_CHANNEL_SELECTION_ALGORITHM                  0x14        /**< LE Channel Selection Algorithm event. */
#define HCI_LE_TRANSMIT_POWER_REPORTING                     0x21        /**< LE Transmit Power Reporting event. */
/** @} */

/**@defgroup HCI_CMD_SIZE Pre-defined size of HCI command packet
 * @brief The size of parameters of each HCI command packet.
 * @{ */
#define HCI_CMD_SIZE_DISCONNECT                             0x03        /**< See @ref HCI_Disconnect_T. */
#define HCI_CMD_SIZE_READ_AUTH_PAYLOAD_TO                   0x02        /**< See @ref HCI_ReadAuthenticatedPayloadTimeout_T. */
#define HCI_CMD_SIZE_WRITE_AUTH_PAYLOAD_TO                  0x04        /**< See @ref HCI_WriteAuthenticatedPayloadTimeout_T. */
#define HCI_CMD_SIZE_READ_BD_ADDR                           0x00        /**< No parameters. */
#define HCI_CMD_SIZE_READ_RSSI                              0x02        /**< See @ref HCI_ReadRssi_T. */
#define HCI_CMD_SIZE_LE_SET_RANDOM_ADDR                     0x06        /**< See @ref HCI_LE_SetRandomAddress_T. */
#define HCI_CMD_SIZE_LE_SET_ADV_PARAMS                      0x0F        /**< See @ref HCI_LE_SetAdvertisingParameters_T. */
#define HCI_CMD_SIZE_LE_SET_ADV_DATA                        0x20        /**< See @ref HCI_LE_SetAdvertisingData_T. */
#define HCI_CMD_SIZE_LE_SET_SCAN_RSP_DATA                   0x20        /**< See @ref HCI_LE_SetScanResponseData_T. */
#define HCI_CMD_SIZE_LE_SET_ADV_ENABLE                      0x01        /**< See @ref HCI_LE_SetAdvertisingEnable_T. */
#define HCI_CMD_SIZE_LE_SET_SCAN_PARAMS                     0x07        /**< See @ref HCI_LE_SetScanParameters_T. */
#define HCI_CMD_SIZE_LE_SET_SCAN_ENABLE                     0x02        /**< See @ref HCI_LE_SetScanEnable_T. */
#define HCI_CMD_SIZE_LE_CREATE_CONN                         0x19        /**< See @ref HCI_LE_CreateConnection_T. */
#define HCI_CMD_SIZE_LE_CREATE_CONN_CANCEL                  0x00        /**< No parameters. */
#define HCI_CMD_SIZE_LE_CLEAR_FILTER_ACCEPT_LIST            0x00        /**< No parameters. */
#define HCI_CMD_SIZE_LE_ADD_DEV_TO_FILTER_ACCEPT_LIST       0x07        /**< See @ref HCI_LE_AddDeviceToFilterAcceptList_T. */
#define HCI_CMD_SIZE_LE_CONN_UPDATE                         0x0E        /**< See @ref HCI_LE_ConnectionUpdate_T. */
#define HCI_CMD_SIZE_LE_SET_HOST_CHANNEL_CLASSIFY           0x05        /**< 37 1-bit fields (5 octets). */
#define HCI_CMD_SIZE_LE_READ_CHANNEL_MAP                    0x02        /**< See @ref HCI_LE_ReadChannelMap_T. */
#define HCI_CMD_SIZE_LE_READ_REMOTE_FEATURES                0x02        /**< See @ref HCI_LE_ReadRemoteFeatures_T. */
#define HCI_CMD_SIZE_LE_ENABLE_ENCRYPTION                   0x1C        /**< See @ref HCI_LE_EnableEncryption_T. */
#define HCI_CMD_SIZE_LE_LTK_REQ_REPLY                       0x12        /**< See @ref HCI_LE_LongTermKeyRequestReply_T. */
#define HCI_CMD_SIZE_LE_LTK_REQ_NEG_REPLY                   0x02        /**< See @ref HCI_LE_LongTermKeyRequestNegativeReply_T. */
#define HCI_CMD_SIZE_LE_RECEIVER_TEST_V1                    0x01        /**< See @ref HCI_LE_ReceiverTestV1_T. */
#define HCI_CMD_SIZE_LE_TRANSMITTER_TEST_V1                 0x03        /**< See @ref HCI_LE_TransmitterTestV1_T. */
#define HCI_CMD_SIZE_LE_TEST_END                            0x00        /**< No parameters. */
#define HCI_CMD_SIZE_LE_REMOTE_CONN_PARAMS_REQ_REPLY        0x0E        /**< See @ref HCI_LE_RemoteConnParamReqReply_T. */
#define HCI_CMD_SIZE_LE_REMOTE_CONN_PARAMS_REQ_NEG_REPLY    0x03        /**< See @ref HCI_LE_RemoteConnParamReqNegReply_T. */
#define HCI_CMD_SIZE_LE_SET_DATA_LENGTH                     0x06        /**< See @ref HCI_LE_SetDataLength_T. */
#define HCI_CMD_SIZE_LE_ADD_DEV_TO_RES_LIST                 0x27        /**< See @ref HCI_LE_AddDeviceToResolvingList_T. */
#define HCI_CMD_SIZE_LE_CLEAR_RES_LIST                      0x00        /**< No parameters. */
#define HCI_CMD_SIZE_LE_SET_ADDR_RES_ENABLE                 0x01        /**< See @ref HCI_LE_SetAddressResolutionEnable_T. */
#define HCI_CMD_SIZE_LE_SET_RPA_TIMEOUT                     0x02        /**< See @ref HCI_LE_SetRpaTimeout_T. */
#define HCI_CMD_SIZE_LE_READ_PHY                            0x02        /**< See @ref HCI_LE_ReadPhy_T. */
#define HCI_CMD_SIZE_LE_SET_DEFAULT_PHY                     0x03        /**< See @ref HCI_LE_SetDefaultPhy_T. */
#define HCI_CMD_SIZE_LE_SET_PHY                             0x07        /**< See @ref HCI_LE_SetPhy_T. */
#define HCI_CMD_SIZE_LE_RECEIVER_TEST_V2                    0x03        /**< See @ref HCI_LE_ReceiverTestV2_T. */
#define HCI_CMD_SIZE_LE_TRANSMITTER_TEST_V2                 0x04        /**< See @ref HCI_LE_TransmitterTestV2_T. */
#define HCI_CMD_SIZE_LE_SET_ADV_SET_RANDOM_ADDR             0x07        /**< See @ref HCI_LE_SetAdvertisingSetRandomAddr_T. */
#define HCI_CMD_SIZE_LE_SET_EXT_ADV_PARAMS                  0x19        /**< See @ref HCI_LE_SetExtAdvertisingParameters_T. */
#define HCI_CMD_SIZE_LE_SET_EXT_ADV_DATA                    0xFF        /**< See @ref HCI_LE_SetExtAdvertisingData_T. */
#define HCI_CMD_SIZE_LE_SET_EXT_SCAN_RSP_DATA               0xFF        /**< See @ref HCI_LE_SetExtScanRespData_T. */
#define HCI_CMD_SIZE_LE_SET_EXT_ADV_ENABLE                  0xFE        /**< See @ref HCI_LE_SetExtAdvertisingEnable_T. */
#define HCI_CMD_SIZE_LE_REMOVE_ADV_SET                      0x01        /**< See @ref HCI_LE_RemoveAdvertisingSet_T. */
#define HCI_CMD_SIZE_LE_CLEAR_ADV_SET                       0x00        /**< No parameters. */
#define HCI_CMD_SIZE_LE_SET_PERIODIC_ADV_PARAMS             0x07        /**< See @ref HCI_LE_SetPeriodicAdvertisingParams_T. */
#define HCI_CMD_SIZE_LE_SET_PERIODIC_ADV_DATA               0xFF        /**< See @ref HCI_LE_SetPeriodicAdvertisingData_T. */
#define HCI_CMD_SIZE_LE_SET_PERIODIC_ADV_ENABLE             0x02        /**< See @ref HCI_LE_SetPeriodicAdvertisingEnable_T. */
#define HCI_CMD_SIZE_LE_SET_EXT_SCAN_PARAMS                 0x0D        /**< See @ref HCI_LE_SetExtScanParams_T. */
#define HCI_CMD_SIZE_LE_SET_EXT_SCAN_ENABLE                 0x06        /**< See @ref HCI_LE_SetExtScanEnable_T. */
#define HCI_CMD_SIZE_LE_EXT_CREATE_CONN                     0x3A        /**< See @ref HCI_LE_ExtCreateConnParam_T. */
#define HCI_CMD_SIZE_LE_PERIODIC_ADV_CREATE_SYNC            0x0E        /**< See @ref HCI_LE_PeriodicAdvertisingCreateSync_T. */
#define HCI_CMD_SIZE_LE_PERIODIC_ADV_CREATE_SYNC_CANCEL     0x00        /**< No parameters. */
#define HCI_CMD_SIZE_LE_PERIODIC_ADV_TERMINATE_SYNC         0x02        /**< See @ref HCI_LE_PeriodicAdvertisingTerminateSync_T. */
#define HCI_CMD_SIZE_LE_ADD_DEV_TO_PERIODIC_ADV_LIST        0x08        /**< See @ref HCI_LE_AddDevToPeriodicAdvList_T. */
#define HCI_CMD_SIZE_LE_CLEAR_PERIODIC_ADV_LIST             0x00        /**< No parameters. */
#define HCI_CMD_SIZE_LE_READ_TRANSMIT_POWER                 0x00        /**< No parameters. */
#define HCI_CMD_SIZE_LE_SET_PRIVACY_MODE                    0x08        /**< @ref HCI_LE_SetPrivacyMode_T. */
#define HCI_CMD_SIZE_LE_SET_PERIODIC_ADV_RX_ENABLE          0x03        /**< See @ref HCI_LE_SetPeriodicAdvReceiveEnable_T. */
#define HCI_CMD_SIZE_LE_ENHANCED_READ_TRANSMIT_POWER_LEVEL  0x03        /**< See @ref HCI_LE_EnhancedReadTransmitPowerLevel_T. */
#define HCI_CMD_SIZE_LE_READ_REMOTE_TRANSMIT_POWER_LEVEL    0x03        /**< See @ref HCI_LE_ReadRemoteTransmitPowerLevel_T. */
#define HCI_CMD_SIZE_LE_SET_TRANSMIT_POWER_REPORTING_ENABLE 0x04        /**< See @ref HCI_LE_SetTransmitPowerReportingEnable_T. */
#define HCI_CMD_SIZE_LE_TRANSMITTER_TEST_V4                 0x08        /**< See @ref HCI_LE_TransmitterTestV4_T. */
/** @} */

/**@defgroup HCI_EVT_SIZE Pre-defined size of HCI event packet
 * @brief The size of parameters of each HCI event packet.
 * @{ */
#define HCI_EVT_SIZE_DISCONNECTION                          0x04        /**< See @ref HCI_EvtDisconnect_T. */
#define HCI_EVT_SIZE_ENCRYPTION_CHANGE                      0x04        /**< See @ref HCI_EvtEncryptChange_T. */
#define HCI_EVT_SIZE_REMOTE_VERSION_INFORMATION_COMPLETE    0x08        /**< See @ref HCI_EvtReadRemoteVer_T. */
#define HCI_EVT_SIZE_NBR_OF_COMPLETED_PKTS                  0x19        /**< See @ref HCI_EvtNumOfCompletePacket_T. */
#define HCI_EVT_SIZE_KEY_REFRESH_COMPLETE                   0x03        /**< See @ref HCI_EvtKeyRefreshComplete_T. */
#define HCI_EVT_SIZE_AUTH_PAYLOAD_TO_EXPIRED                0x02        /**< See @ref HCI_EvtAuthPayloadTimeout_T. */
/** @} */

/**@defgroup HCI_LE_META_SUB_EVT_SIZE HCI subevent size definition of LE_META event
 * @brief The size of parameters of each subevent in HCI LE_META event.
 * @{ */
#define HCI_EVT_SIZE_LE_CONNECT_COMPLETE                    0x12        /**< See @ref HCI_EvtLeConnect_T. */
#define HCI_EVT_SIZE_LE_ADV_REPORT                          0x2A        /**< See @ref HCI_EvtLeAdvReport_T. */
#define HCI_EVT_SIZE_LE_CONNECTION_UPDATE_COMPLETE          0x09        /**< See @ref HCI_EvtLeConnParamUpdate_T. */
#define HCI_EVT_SIZE_LE_READ_REMOTE_FEATURES_COMPLETE       0x0B        /**< See @ref HCI_EvtLeReadRemoteFeature_T. */
#define HCI_EVT_SIZE_LE_LONG_TERM_KEY_REQUEST               0x0C        /**< See @ref HCI_EvtLeLongTermKeyReq_T. */
#define HCI_EVT_SIZE_LE_REMOTE_CONNECTION_UPDATE_REQUEST    0x0A        /**< See @ref HCI_EvtLeRemoteConnParamsReq_T. */
#define HCI_EVT_SIZE_LE_DATA_LENGTH_CHANGE                  0x0A        /**< See @ref HCI_EvtLeDataLengthChange_T. */
#define HCI_EVT_SIZE_LE_ENHANCED_CONNECTION_COMPLETE        0x1E        /**< See @ref HCI_EvtLeEnhanceConnect_T. */
#define HCI_EVT_SIZE_LE_DIRECT_ADV_REPORT                   0x11        /**< See @ref HCI_EvtLeDirectAdvReport_T. */
#define HCI_EVT_SIZE_LE_PHY_UPDATE_COMPLETE                 0x05        /**< See @ref HCI_EvtLePhyUpdate_T. */
#define HCI_EVT_SIZE_LE_EXTENDED_ADV_REPORT                 0xFE        /**< See @ref HCI_EvtLeExtAdvReport_T. */
#define HCI_EVT_SIZE_LE_PERIODIC_ADV_SYNC_ESTABLISHED       0x0F        /**< See @ref HCI_EvtLePeriodicAdvSyncEst_T. */
#define HCI_EVT_SIZE_LE_PERIODIC_ADV_REPORT                 0xFE        /**< See @ref HCI_EvtLePeriodicAdvReport_T. */
#define HCI_EVT_SIZE_LE_PERIODIC_ADV_SYNC_LOST              0x02        /**< See @ref HCI_EvtLePeriodicAdvSyncLost_T. */
#define HCI_EVT_SIZE_LE_SCAN_TIMEOUT                        0x00        /**< No parameters. */
#define HCI_EVT_SIZE_LE_ADV_SET_TERMINATED                  0x05        /**< See @ref HCI_EvtLeAdvSetTerminated_T. */
#define HCI_EVT_SIZE_LE_SCAN_REQUEST_RECEIVED               0x08        /**< See @ref HCI_EvtLeScanReqReceived_T. */
#define HCI_EVT_SIZE_LE_CHANNEL_SELECT_ALGORITHM            0x03        /**< See @ref HCI_EvtLeChannelSelectAlgorithm_T. */
#define HCI_EVT_SIZE_LE_TX_POWER_REPORTING                  0x08        /**< See @ref HCI_EvtLeTxPowerReporting_T. */
/** @} */


/**@defgroup HCI_CC_EVT_SIZE Pre-defined size of HCI command complete event packet
 * @brief The size of parameters of HCI command complete event in different opcode.
 * @{ */
#define HCI_CC_EVT_SIZE_STATUS                              0x01        /**< Size of command complete event whose returned parameter containing only status parameter. */
#define HCI_CC_EVT_SIZE_READ_AUTH_PAYLOAD_TO                0x05        /**< @ref HCI_CC_ReadAuthenticatedPayloadTimeout_T. */
#define HCI_CC_EVT_SIZE_WRITE_AUTH_PAYLOAD_TO               0x03        /**< @ref HCI_CC_WriteAuthenticatedPayloadTimeout_T. */
#define HCI_CC_EVT_SIZE_READ_BD_ADDR                        0x07        /**< @ref HCI_CC_ReadBdAddr_T. */
#define HCI_CC_EVT_SIZE_READ_RSSI                           0x04        /**< @ref HCI_CC_ReadRssi_T. */
#define HCI_CC_EVT_SIZE_READ_CHANNEL_MAP                    0x08        /**< @ref HCI_CC_LE_ReadChannelMap_T. */
#define HCI_CC_EVT_SIZE_LTK_REQUEST_REPLY                   0x03        /**< @ref HCI_CC_LE_LtkReqReply_T. */
#define HCI_CC_EVT_SIZE_LTK_REQUEST_NEGATIVE_REPLY          0x03        /**< @ref HCI_CC_LE_LtkReqNegativeReply_T. */
#define HCI_CC_EVT_SIZE_TEST_END                            0x03        /**< @ref HCI_CC_LE_TestEnd_T. */
#define HCI_CC_EVT_SIZE_REMOTE_CONN_PARAM_REQ_REPLY         0x03        /**< @ref HCI_CC_LE_RemoteConnParamReqReply_T. */
#define HCI_CC_EVT_SIZE_REMOTE_CONN_PARAM_REQ_NEG_REPLY     0x03        /**< @ref HCI_CC_LE_RemoteConnParamReqNegReply_T. */
#define HCI_CC_EVT_SIZE_SET_DATA_LENGTH                     0x03        /**< @ref HCI_CC_LE_SetDataLength_T. */
#define HCI_CC_EVT_SIZE_READ_PHY                            0x05        /**< @ref HCI_CC_LE_ReadPhy_T. */
#define HCI_CC_EVT_SIZE_SET_EXT_ADV_PARAMS                  0x02        /**< @ref HCI_CC_LE_SetExtAdvertisingParameters_T. */
#define HCI_CC_EVT_SIZE_READ_TRANSMIT_POWER                 0x03        /**< @ref HCI_CC_LE_ReadTransmitPower_T. */
#define HCI_CC_EVT_SIZE_ENHANCED_READ_TRANSMIT_POWER        0x06        /**< @ref HCI_CC_LE_EnhancedReadTransmitPower_T. */
#define HCI_CC_EVT_SIZE_SET_TRANSMIT_POWER_REPORTING_ENABLE 0x03        /**< @ref HCI_CC_LE_SetTransmitPowerReportingEnable_T. */
/** @} */

/**@} */ //HOST_HCI_DEFINES

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

/**@addtogroup HOST_HCI_STRUCTS Structures
 * @{ */

/**@brief Parameters of disconnect command. */
typedef struct HCI_Disconnect_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint8_t     reason;                                                         /**< Reason for disconnection. */
} HCI_Disconnect_T;

/**@brief Parameter of read authenticated payload timeout command. */
typedef struct HCI_ReadAuthenticatedPayloadTimeout_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
} HCI_ReadAuthenticatedPayloadTimeout_T;

/**@brief Parameters of write authenticated payload timeout command. */
typedef struct HCI_WriteAuthenticatedPayloadTimeout_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint16_t    authenticatedPayloadTimeout;                                    /**< Maximum amount of time specified between packets authenticated by a valid MIC. */
} HCI_WriteAuthenticatedPayloadTimeout_T;

/**@brief Parameter of read RSSI command. */
typedef struct HCI_ReadRssi_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
} HCI_ReadRssi_T;

/**@brief Parameter of set random address command. */
typedef  struct HCI_LE_SetRandomAddress_T
{
    uint8_t     randomAddr[HCI_BD_ADDRESS_LEN];                                 /**< Random address. */
} HCI_LE_SetRandomAddress_T;

/**@brief Parameters of set advertising parameters command. */
typedef  struct HCI_LE_SetAdvertisingParameters_T
{
    uint16_t    intervalMin;                                                    /**< Minimum advertising interval. (Unit: 0.625ms) */
    uint16_t    intervalMax;                                                    /**< Maximum advertising interval. (Unit: 0.625ms) */
    uint8_t     type;                                                           /**< Advertising type. */
    uint8_t     ownAddrType;                                                    /**< Own bluetooth address type. */
    uint8_t     peerAddrType;                                                   /**< Remote peer bluetooth address type. */
    uint8_t     peerAddr[HCI_BD_ADDRESS_LEN];                                   /**< Remote peer bluetooth address. */
    uint8_t     advChannelMap;                                                  /**< Advertising Channel Map. */
    uint8_t     filterPolicy;                                                   /**< Advertising filter policy. */
} HCI_LE_SetAdvertisingParameters_T;

/**@brief Parameters of set advertising data command. */
typedef struct HCI_LE_SetAdvertisingData_T
{
    uint8_t     advLen;                                                         /**< Length of advertising data, see @ref HCI_MAX_ADV_LENGTH for the maximum length. */
    uint8_t     advData[HCI_MAX_ADV_LENGTH];                                    /**< Advertising data */
} HCI_LE_SetAdvertisingData_T;

/**@brief Parameters of set scan response data command. */
typedef struct HCI_LE_SetScanResponseData_T
{
    uint8_t     advScanRspLen;                                                  /**< Length of scan response data, see @ref HCI_MAX_ADV_LENGTH for the maximum length. */
    uint8_t     advScanRspData[HCI_MAX_ADV_LENGTH];                             /**< Scan response data. */
} HCI_LE_SetScanResponseData_T;

/**@brief Parameter of set advertising enable command. */
typedef struct HCI_LE_SetAdvertisingEnable_T
{
    uint8_t     enable;                                                         /**< Enable or disable advertising. */
} HCI_LE_SetAdvertisingEnable_T;

/**@brief Parameters of set scan parematers command. */
typedef  struct HCI_LE_SetScanParameters_T
{
    uint8_t     scanType;                                                       /**< Scanning type. */
    uint16_t    scanInterval;                                                   /**< Scanning interval. */
    uint16_t    scanWindow;                                                     /**< Scanning window. It shall be set to a value smaller or equal to the value set for the scanInterval. */
    uint8_t     ownAddrType;                                                    /**< Own bluetooth address type. */
    uint8_t     filterPolicy;                                                   /**< Scanning filter policy. */
        uint8_t     disChannel;                                                 /**< Disable specific channel during scanning. (proprietary)*/
} HCI_LE_SetScanParameters_T;

/**@brief Parameters of set scan enable command. */
typedef struct HCI_LE_SetScanEnable_T
{
    uint8_t     enable;                                                         /**< Enable or disable scanning. */
    uint8_t     filterDuplicates;                                               /**< Duplicate filter policy. */
} HCI_LE_SetScanEnable_T;

/**@brief Parameters of create connection command. */
typedef struct HCI_LE_CreateConnection_T
{
    uint16_t    scanInterval;                                                   /**< Scanning interval. */
    uint16_t    scanWindow;                                                     /**< Scanning window. It shall be set to a value smaller or equal to the value set for the scanInterval. */
    uint8_t     filterPolicy;                                                   /**< Initiator filter policy. It is used to determine whether the Filter Accept List is used. If the Filter Accept List is not used, the peerAddr argument specify the address type and address of the advertising device to connect to. */
    uint8_t     peerAddrType;                                                   /**< Remote peer bluetooth address type. It is invalid once filterPolicy is enable. */
    uint8_t     peerAddr[HCI_BD_ADDRESS_LEN];                                   /**< Remote peer bluetooth address. It is invalid once filterPolicy is enable. */
    uint8_t     ownAddrType;                                                    /**< Own bluetooth address type. */
    uint16_t    intervalMin;                                                    /**< Minimum allowed connection interval. The value shall not be greater than maximum allowed connection interval. */
    uint16_t    intervalMax;                                                    /**< Maximum allowed connection interval. */
    uint16_t    latency;                                                        /**< Peripheral latency for the connection in terms of number of connection events. */
    uint16_t    supervisionTimeout;                                             /**< Supervision timeout of the connection. The timeout in milliseconds shall be larger than (1 + latency) * intervalMax * 2, where intervalMax is given in milliseconds. */
    uint16_t    minCeLength;                                                    /**< Minimum length of connection event needed for this LE connection. */
    uint16_t    maxCeLength;                                                    /**< Maximum length of connection event needed for this LE connection. */
} HCI_LE_CreateConnection_T;

/**@brief Parameters of add device to filter accept list command. */
typedef struct HCI_LE_AddDeviceToFilterAcceptList_T
{
    uint8_t     addrType;                                                       /**< Address type. */
    uint8_t     addr[HCI_BD_ADDRESS_LEN];                                       /**< Bluetooth address. */
} HCI_LE_AddDeviceToFilterAcceptList_T;

/**@brief Parameters of connection update command. */
typedef struct HCI_LE_ConnectionUpdate_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint16_t    intervalMin;                                                    /**< Minimum allowed connection interval. The value shall not be greater than maximum allowed connection interval. */
    uint16_t    intervalMax;                                                    /**< Maximum allowed connection interval. */
    uint16_t    latency;                                                        /**< Peripheral latency for the connection in number of connection events. */
    uint16_t    supervisionTimeout;                                             /**< Supervision timeout of the connection. The timeout in milliseconds shall be larger than (1 + latency) * intervalMax * 2, where intervalMax is given in milliseconds. */
    uint16_t    minCeLength;                                                    /**< Minimum length of connection event needed for this LE connection. */
    uint16_t    maxCeLength;                                                    /**< Maximum length of connection event needed for this LE connection. */
} HCI_LE_ConnectionUpdate_T;

/**@brief Parameter of read channel map command. */
typedef struct HCI_LE_ReadChannelMap_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
} HCI_LE_ReadChannelMap_T;

/**@brief Parameter of read remote features command. */
typedef struct HCI_LE_ReadRemoteFeatures_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
} HCI_LE_ReadRemoteFeatures_T;

/**@brief Parameters of enable encryption command. */
typedef struct HCI_LE_EnableEncryption_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint8_t     randomNum[HCI_LTK_RANDOM_SIZE];                                 /**< 64 bit random number. */
    uint16_t    encryptedDiversifier;                                           /**< Encrypted diversifier.*/
    uint8_t     longTermKey[HCI_MAX_KEY_LENGTH];                                /**< 128 bit long term key. */
} HCI_LE_EnableEncryption_T;

/**@brief Parameters of long term key request reply command. */
typedef struct HCI_LE_LongTermKeyRequestReply_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint8_t     longTermKey[HCI_MAX_KEY_LENGTH];                                /**< 128 bit long term key. */
} HCI_LE_LongTermKeyRequestReply_T;

/**@brief Parameter of long term key request negative reply command. */
typedef struct HCI_LE_LongTermKeyRequestNegativeReply_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
} HCI_LE_LongTermKeyRequestNegativeReply_T;

/**@brief Parameter of receiver test (version 1) command. */
typedef struct HCI_LE_ReceiverTestV1_T
{
    uint8_t     rxChannel;                                                      /**< The RF channel to be used by the receiver. */
} HCI_LE_ReceiverTestV1_T;

/**@brief Parameters of transmitter test (version 1) command. */
typedef struct HCI_LE_TransmitterTestV1_T
{
    uint8_t     txChannel;                                                      /**< The RF channel to be used by the transmitter. */
    uint8_t     testDataLen;                                                    /**< The length of the payload of the test reference packets. */
    uint8_t     packetPayload;                                                  /**< The contents of the payload of the test reference packets. */
} HCI_LE_TransmitterTestV1_T;

/**@brief Parameters of remote connection parameter request reply command. */
typedef  struct HCI_LE_RemoteConnParamReqReply_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint16_t    intervalMin;                                                    /**< Minimum allowed connection interval. The value shall not be greater than maximum allowed connection interval. */
    uint16_t    intervalMax;                                                    /**< Maximum allowed connection interval. */
    uint16_t    latency;                                                        /**< Maximum allowed peripheral latency for the connection in number of connection events. */
    uint16_t    supervisionTimeout;                                             /**< Supervision timeout of the connection. The timeout in milliseconds shall be larger than (1 + latency) * intervalMax * 2, where intervalMax is given in milliseconds. */
    uint16_t    minCeLength;                                                    /**< Minimum length of connection event needed for this LE connection. */
    uint16_t    maxCeLength;                                                    /**< Maximum length of connection event needed for this LE connection. */
} HCI_LE_RemoteConnParamReqReply_T;

/**@brief Parameters of remote connection parameter request negative reply command. */
typedef  struct HCI_LE_RemoteConnParamReqNegReply_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint8_t     reason;                                                         /**< Reason that the connection parameter request was rejected. */
} HCI_LE_RemoteConnParamReqNegReply_T;

/**@brief Parameters of set data length command. */
typedef struct HCI_LE_SetDataLength_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint16_t    txOctets;                                                       /**< Preferred maximum number of payload octets that the local Controller should include in a single LL Data PDU on this connection. */
    uint16_t    txTime;                                                         /**< Preferred maximum number of microseconds that the local Controller should use to transmit a single Link Layer packet containing an LL Data PDU on this connection. */
} HCI_LE_SetDataLength_T;

/**@brief Parameters of add device to resolving list command. */
typedef struct HCI_LE_AddDeviceToResolvingList_T
{
    uint8_t     peerIdAddrType;                                                 /**< Address type of the peer device. */
    uint8_t     peerIdAddr[HCI_BD_ADDRESS_LEN];                                 /**< Bluetooth address of the peer device. */
    uint8_t     peerIrk[HCI_MAX_KEY_LENGTH];                                    /**< IRK of the peer device. */
    uint8_t     localIrk[HCI_MAX_KEY_LENGTH];                                   /**< IRK of the local device. */
} HCI_LE_AddDeviceToResolvingList_T;

/**@brief Parameter of set address resolution enable command. */
typedef struct HCI_LE_SetAddressResolutionEnable_T
{
    uint8_t     addressResolutionEnable;                                        /**< Address resolution in controller enabled or disabled. */
} HCI_LE_SetAddressResolutionEnable_T;

/**@brief Parameter of set resolvable private address timeout command. */
typedef struct HCI_LE_SetRpaTimeout_T
{
    uint16_t    rpaTimeout;                                                     /**< Timeout value in seconds to use a new resolvable private address. */
} HCI_LE_SetRpaTimeout_T;

/**@brief Parameter of read phy command. */
typedef struct HCI_LE_ReadPhy_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
} HCI_LE_ReadPhy_T;

/**@brief Parameters of set default phy command. */
typedef struct HCI_LE_SetDefaultPhy_T
{
    uint8_t     allPhys;                                                        /**< A bit field that allows the Host to specify whether it has preference or not among the PHYs that the Controller supports in a given direction. */
    uint8_t     txPhys;                                                         /**< A bit field that indicates the transmitter PHYs that the Host prefers the Controller to use. */
    uint8_t     rxPhys;                                                         /**< A bit field that indicates the receiver PHYs that the Host prefers the Controller to use. */
} HCI_LE_SetDefaultPhy_T;

/**@brief Parameters of set phy command. */
typedef struct HCI_LE_SetPhy_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint8_t     allPhys;                                                        /**< A bit field that allows the Host to specify whether it has preference or not among the PHYs that the Controller supports in a given direction. */
    uint8_t     txPhys;                                                         /**< A bit field that indicates the transmitter PHYs that the Host prefers the Controller to use. */
    uint8_t     rxPhys;                                                         /**< A bit field that indicates the receiver PHYs that the Host prefers the Controller to use. */
    uint16_t    phyOptions;                                                     /**< A bit field that allows the Host to specify options for PHYs. */
} HCI_LE_SetPhy_T;

/**@brief Parameters of receiver test (version 2) command. */
typedef struct HCI_LE_ReceiverTestV2_T
{
    uint8_t     rxChannel;                                                      /**< RF channel of receiver. */
    uint8_t     phy;                                                            /**< The PHY to be used by the receiver. */
    uint8_t     modulationIndex;                                                /**< Specifie whether the controller should assume the receiver has a stable modulation index. */
} HCI_LE_ReceiverTestV2_T;

/**@brief Parameters of transmitter test (version 2) command. */
typedef struct HCI_LE_TransmitterTestV2_T
{
    uint8_t     txChannel;                                                      /**< The RF channel to be used by the transmitter. */
    uint8_t     testDataLen;                                                    /**< The length of the payload of the test reference packets. */
    uint8_t     packetPayload;                                                  /**< The contents of the payload of the test reference packets. */
    uint8_t     phy;                                                            /**< The PHY to be used by the transmitter. */
} HCI_LE_TransmitterTestV2_T;

/**@brief Parameters of set advertising set random address command. */
typedef struct HCI_LE_SetAdvertisingSetRandomAddr_T
{
    uint8_t     advHandle;                                                      /**< Used to identify an advertising set. */
    uint8_t     advRandomAddr[HCI_BD_ADDRESS_LEN];                              /**< Used random address for the advertising set specified by advertising handle. */
} HCI_LE_SetAdvertisingSetRandomAddr_T;

/**@brief Parameters of set extended advertising parameters command. */
typedef  struct HCI_LE_SetExtAdvertisingParameters_T
{
    uint8_t     advhandle;                                                      /**< Used to identify an advertising set. */
    uint16_t    evtProperies;                                                   /**< Advertising event properties. */
    uint8_t     priIntervalMin[3];                                              /**< Minimum advertising interval undirected and low duty cycle directed advertising. (Unit: 0.625ms) */
    uint8_t     priIntervalMax[3];                                              /**< Maximum advertising interval undirected and low duty cycle directed advertising. (Unit: 0.625ms) */
    uint8_t     priChannelMap;                                                  /**< Advertising channel map. */
    uint8_t     ownAddrType;                                                    /**< Own bluetooth address type. */
    uint8_t     peerAddrType;                                                   /**< Remote peer bluetooth address type. */
    uint8_t     peerAddr[HCI_BD_ADDRESS_LEN];                                   /**< Remote peer bluetooth address. */
    uint8_t     filterPolicy;                                                   /**< Advertising filter policy. */
    int8_t      txPower;                                                        /**< Advertising tx power. */
    uint8_t     priPhy;                                                         /**< Primary advertisement PHY. */
    uint8_t     secMaxSkip;                                                     /**< Maximum advertising events the Controller can skip before sending the AUX_ADV_IND packets on the secondary advertising physical channel. */
    uint8_t     secPhy;                                                         /**< Secondary advertisement PHY. */
    uint8_t     advSid;                                                         /**< Value of the Advertising SID subfield in the ADI field of the PDU. */
    uint8_t     scanReqNotifiEnable;                                            /**< Scan request notifications enabled or disabled. */
} HCI_LE_SetExtAdvertisingParameters_T;

/**@brief Parameters of set extended advertising data command. */
typedef struct HCI_LE_SetExtAdvertisingData_T
{
    uint8_t     advHandle;                                                      /**< Used to identify an advertising set. */
    uint8_t     operation;                                                      /**< The operation of the advertising data. */
    uint8_t     fragPreference;                                                 /**< Fragment preference of the advertising data. */
    uint8_t     advLen;                                                         /**< Length of extended advertising data, see @ref HCI_CMD_MAX_EXTENDED_ADVERTISING_DATA_LENGTH for the maximum length. */
    uint8_t     advData[HCI_CMD_MAX_EXTENDED_ADVERTISING_DATA_LENGTH];          /**< Advertising data. */
} HCI_LE_SetExtAdvertisingData_T;

/**@brief Parameters of set extended scan response data command. */
typedef struct HCI_LE_SetExtScanRespData_T
{
    uint8_t     advHandle;                                                      /**< Used to identify an advertising set. */
    uint8_t     operation;                                                      /**< The operation of the scan response data. */
    uint8_t     fragPreference;                                                 /**< Fragment preference of the scan response data. */
    uint8_t     scanRspLen;                                                     /**< Length of scan response data, see @ref HCI_CMD_MAX_EXTENDED_ADVERTISING_DATA_LENGTH for the maximum length. */
    uint8_t     scanRspData[HCI_CMD_MAX_EXTENDED_ADVERTISING_DATA_LENGTH];      /**< Scan response data. */
} HCI_LE_SetExtScanRespData_T;

/**@brief Parameters of an advertising set. */
typedef struct HCI_LE_ExtAdvertisingSet_T
{
    uint8_t     advHandle;                                                      /**< Used to identify an advertising set. */
    uint16_t    duration;                                                       /**< Indicate the duration for which that advertising set is enabled. */
    uint8_t     maxExtAdvEvts;                                                  /**< Maximum number of extended advertising events the Controller shall attempt to send prior to terminating the extended advertising. */
} HCI_LE_ExtAdvertisingSet_T;

/**@brief Parameters of set extended advertising enable command. */
typedef struct HCI_LE_SetExtAdvertisingEnable_T
{
    uint8_t                     enable;                                         /**< Enable or disable extended advertising. */
    uint8_t                     numOfSets;                                      /**< The number of advertising to be enabled or disabled. */
    HCI_LE_ExtAdvertisingSet_T  advSet[HCI_MAX_EXTENDED_ADVERTISING_SETS];      /**< Advertising set parameter array. */
} HCI_LE_SetExtAdvertisingEnable_T;

/**@brief Parameter of remove advertising set command. */
typedef struct HCI_LE_RemoveAdvertisingSet_T
{
    uint8_t     advHandle;                                                      /**< Used to identify an advertising set. */
} HCI_LE_RemoveAdvertisingSet_T;

/**@brief Parameters of set periodic advertising parameters command. */
typedef  struct HCI_LE_SetPeriodicAdvertisingParams_T
{
    uint8_t     advHandle;                                                      /**< Used to identify an advertising set. */
    uint16_t    intervalMin;                                                    /**< Minimum advertising interval. (Unit: 0.625ms) */
    uint16_t    intervalMax;                                                    /**< Maximum advertising interval. (Unit: 0.625ms) */
    uint16_t    properties;                                                     /**< Indicate which fields should be included in the advertising packet. */
} HCI_LE_SetPeriodicAdvertisingParams_T;

/**@brief Parameters of set periodic advertising data command. */
typedef struct HCI_LE_SetPeriodicAdvertisingData_T
{
    uint8_t     advHandle;                                                      /**< Used to identify an advertising set. */
    uint8_t     operation;                                                      /**< The operation of the advertising data. */
    uint8_t     advLen;                                                         /**< Length of periodic advertising data, see @ref HCI_CMD_MAX_PERIODIC_ADVERTISING_DATA_LENGTH for the maximum length. */
    uint8_t     advData[HCI_CMD_MAX_PERIODIC_ADVERTISING_DATA_LENGTH];          /**< Periodic advertising data. */
} HCI_LE_SetPeriodicAdvertisingData_T;

/**@brief Parameters of set periodic advertising enable command. */
typedef struct HCI_LE_SetPeriodicAdvertisingEnable_T
{
    uint8_t     enable;                                                         /**< Enable or disable periodic advertising. */
    uint8_t     advHandle;                                                      /**< Used to identify an advertising set. */
} HCI_LE_SetPeriodicAdvertisingEnable_T;

/**@brief Parameters of extended scan in each phy. */
typedef struct HCI_LE_ExtScanParamsByPhy_T
{
    uint8_t     scanType;                                                       /**< Scanning type. */
    uint16_t    scanInterval;                                                   /**< Scanning interval. */
    uint16_t    scanWindow;                                                     /**< Scanning window. It shall be set to a value smaller or equal to the value set for the scanInterval. */
    uint8_t     disChannel;                                                     /**< Disable specific channel during scanning. (proprietary)*/
} HCI_LE_ExtScanParamsByPhy_T;

/**@brief Parameters of set extended scan parameters command. */
typedef struct HCI_LE_SetExtScanParams_T
{
    uint8_t                         ownAddrType;                                /**< Own bluetooth address type. */
    uint8_t                         scanFilterPolicy;                           /**< Scanning filter policy. */
    uint8_t                         scanPhys;                                   /**< Scanning PHY. @ref HCI_PHY_OPTION. */
    HCI_LE_ExtScanParamsByPhy_T     paramsByPhy[HCI_SUPPORTED_EXT_SCAN_PHYS];   /**< Scanning parameters by each PHY. */
} HCI_LE_SetExtScanParams_T;

/**@brief Parameters of set extended scan enable command. */
typedef struct HCI_LE_SetExtScanEnable_T
{
    uint8_t     enable;                                                         /**< Enable or disable extended scanning. */
    uint8_t     filterDuplicates;                                               /**< Duplicate filter policy. */
    uint16_t    duration;                                                       /**< Scanning duration. */
    uint16_t    period;                                                         /**< Time interval from last scan duration until it begins the next scan duration. */
} HCI_LE_SetExtScanEnable_T;

/**@brief Parameters of extended create connection in each phy. */
typedef struct HCI_LE_ExtCreateConnByPhy_T
{
    uint16_t    scanInterval;                                                   /**< Scanning interval. */
    uint16_t    scanWindow;                                                     /**< Scanning window. It shall be set to a value smaller or equal to the value set for the scanInterval. */
    uint16_t    intervalMin;                                                    /**< Minimum allowed connection interval. The value shall not be greater than maximum allowed connection interval. */
    uint16_t    intervalMax;                                                    /**< Maximum allowed connection interval. */
    uint16_t    latency;                                                        /**< Peripheral latency for the connection in number of connection events. */
    uint16_t    supervisionTimeout;                                             /**< Supervision timeout of the connection. The timeout in milliseconds shall be larger than (1 + latency) * intervalMax * 2, where intervalMax is given in milliseconds. */
    uint16_t    minCeLength;                                                    /**< Minimum length of connection event needed for this LE connection. */
    uint16_t    maxCeLength;                                                    /**< Maximum length of connection event needed for this LE connection. */
} HCI_LE_ExtCreateConnByPhy_T;

/**@brief Parameters of extended create connection command. */
typedef struct HCI_LE_ExtCreateConnParam_T
{
    uint8_t                     initFilterPolicy;                                       /**< Initiator filter policy. */
    uint8_t                     ownAddrType;                                            /**< Own bluetooth address type. */
    uint8_t                     peerAddrType;                                           /**< Remote peer bluetooth address type. */
    uint8_t                     peerAddr[HCI_BD_ADDRESS_LEN];                           /**< Remote peer bluetooth address. */
    uint8_t                     initPhys;                                               /**< Indicate the PHY(s) on which the advertising packets should be received on the primary advertising physical channel. */
    HCI_LE_ExtCreateConnByPhy_T paramsByPhy[HCI_SUPPORTED_EXT_CREATE_CONNECTION_PHYS];  /**< Extended create connection parameters by each phy. */
} HCI_LE_ExtCreateConnParam_T;

/**@brief Parameters of periodic advertising create sync command. */
typedef struct HCI_LE_PeriodicAdvertisingCreateSync_T
{
    uint8_t     options;                                                        /**< Determine whether the Periodic Advertiser List is used and whether the report of this periodic advertising train are initially enabled or disabled. */
    uint8_t     advSid;                                                         /**< Value of the Advertising SID subfield in the ADI field of the PDU. */
    uint8_t     advAddrType;                                                    /**< Advertisier bluetooth address type. */
    uint8_t     advAddr[HCI_BD_ADDRESS_LEN];                                    /**< Advertisier bluetooth address. */
    uint16_t    skip;                                                           /**< The maximum number of periodic advertising events that can be skipped after a successful receive. */
    uint16_t    syncTimeout;                                                    /**< Synchronization timeout for the periodic advertising train. */
    uint8_t     syncCteType;                                                    /**< Synchronization Constant Tone Extension setting. */
} HCI_LE_PeriodicAdvertisingCreateSync_T;

/**@brief Parameter of terminate sync command. */
typedef struct HCI_LE_PeriodicAdvertisingTerminateSync_T
{
    uint16_t    syncHandle;                                                     /**< Identify the periodic advertising train. */
} HCI_LE_PeriodicAdvertisingTerminateSync_T;

/**@brief Parameters of add device to periodic advertiser list command. */
typedef struct HCI_LE_AddDevToPeriodicAdvList_T
{
    uint8_t     advAddrType;                                                    /**< Advertisier bluetooth address type. */
    uint8_t     advAddr[HCI_BD_ADDRESS_LEN];                                    /**< Advertisier bluetooth address. */
    uint8_t     advSid;                                                         /**< Value of the Advertising SID subfield in the ADI field of the PDU. */
} HCI_LE_AddDevToPeriodicAdvList_T;

/**@brief Parameters of set privacy mode command. */
typedef struct HCI_LE_SetPrivacyMode_T
{
    uint8_t     peerIdentifyAddrType;                                           /**< Peer identity bluetooth address type. */
    uint8_t     peerIdentifyAddr[HCI_BD_ADDRESS_LEN];                           /**< Peer identity bluetooth address. */
    uint8_t     privacyMode;                                                    /**< Privacy mode. */
} HCI_LE_SetPrivacyMode_T;

/**@brief Parameters of set periodic advertising receive enable command. */
typedef struct HCI_LE_SetPeriodicAdvReceiveEnable_T
{
    uint16_t    syncHandle;                                                     /**< Identify the periodic advertising train. */
    uint8_t     enable;                                                         /**< Report enabled or disabled. */
} HCI_LE_SetPeriodicAdvReceiveEnable_T;

/**@brief Parameters of enhanced read transmit power level command. */
typedef struct HCI_LE_EnhancedReadTransmitPowerLevel_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint8_t     phy;                                                            /**< Indicate transmit power of which PHY. */
} HCI_LE_EnhancedReadTransmitPowerLevel_T;

/**@brief Parameters of read remote transmit power level command. */
typedef struct HCI_LE_ReadRemoteTransmitPowerLevel_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint8_t     phy;                                                            /**< Indicate transmit power of which PHY. */
} HCI_LE_ReadRemoteTransmitPowerLevel_T;

/**@brief Parameters of set transmit power reporting enable command. */
typedef struct HCI_LE_SetTransmitPowerReportingEnable_T
{
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint8_t     localEnable;                                                    /**< Disable or enable local transmit power reports. */
    uint8_t     remoteEnable;                                                   /**< Disable or enable remote transmit power reports. */
} HCI_LE_SetTransmitPowerReportingEnable_T;

/**@brief Parameters of transmitter test (version 4) command. */
typedef struct HCI_LE_TransmitterTestV4_T
{
    uint8_t     txChannel;                                                      /**< The RF channel to be used by the transmitter. */
    uint8_t     testDataLen;                                                    /**< The length of the Payload of the test reference packets. */
    uint8_t     packetPayload;                                                  /**< The contents of the Payload of the test reference packets. */
    uint8_t     phy;                                                            /**< The PHY to be used by the transmitter. */
    uint8_t     cteLen;                                                         /**< The length of the Constant Tone Extension in the test reference packets. */
    uint8_t     cteType;                                                        /**< The type of the Constant Tone Extension in the test reference packets. */
    uint8_t     switchingPatternLen;                                            /**< The number of Antenna IDs in the pattern. */
    uint8_t     antennaIds[HCI_LE_TRANSMITTER_SPL_MAX];                         /**< List of Antenna IDs in the pattern. */
    int8_t      txPowerLevel;                                                   /**< The transmit power level to be used by the transmitter. */
} HCI_LE_TransmitterTestV4_T;

/**@brief Structure of command complete event without additional parameters. */
typedef struct HCI_CC_Status_T
{
    uint8_t     status;                                                         /**< Status of the executed command. */
} HCI_CC_Status_T;

/**@brief Parameters of read authenticated payload timeout command complete event. */
typedef struct HCI_CC_ReadAuthenticatedPayloadTimeout_T
{
    uint8_t     status;                                                         /**< Status of the executed command. */
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint16_t    authenticatedPayloadTimeout;                                    /**< Maximum amount of time specified between packets authenticated by a valid MIC. */
} HCI_CC_ReadAuthenticatedPayloadTimeout_T;

/**@brief Parameters of write authenticated payload timeout command complete event. */
typedef struct HCI_CC_WriteAuthenticatedPayloadTimeout_T
{
    uint8_t     status;                                                         /**< Status of the executed command. */
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
} HCI_CC_WriteAuthenticatedPayloadTimeout_T;

/**@brief Parameters of read BD_ADDR command complete event. */
typedef struct HCI_CC_ReadBdAddr_T
{
    uint8_t     status;                                                         /**< Status of the executed command. */
    uint8_t     bdAddr[HCI_BD_ADDRESS_LEN];                                     /**< BD_ADDR of the device. */
} HCI_CC_ReadBdAddr_T;

/**@brief Parameters of read rssi command complete event. */
typedef struct HCI_CC_ReadRssi_T
{
    uint8_t     status;                                                         /**< Status of the executed command. */
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    int8_t      rssi;                                                           /**< RSSI value. */
} HCI_CC_ReadRssi_T;

/**@brief Parameters of read channel map command complete event. */
typedef struct HCI_CC_LE_ReadChannelMap_T
{
    uint8_t     status;                                                         /**< Status of the executed command. */
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint8_t     channelMap[5];                                                  /**< 37 1-bit fields representing channel usage. */
} HCI_CC_LE_ReadChannelMap_T;

/**@brief Parameters of long term key request reply command complete event. */
typedef struct HCI_CC_LE_LtkReqReply_T
{
    uint8_t     status;                                                         /**< Status of the executed command. */
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
} HCI_CC_LE_LtkReqReply_T;

/**@brief Parameters of long term key request negative reply command complete event. */
typedef struct HCI_CC_LE_LtkReqNegativeReply_T
{
    uint8_t     status;                                                         /**< Status of the executed command. */
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
} HCI_CC_LE_LtkReqNegativeReply_T;

/**@brief Parameters of test end command complete event. */
typedef struct HCI_CC_LE_TestEnd_T
{
    uint8_t     status;                                                         /**< Status of the executed command. */
    uint16_t    numPacket;                                                      /**< Number of packets received. */
} HCI_CC_LE_TestEnd_T;

/**@brief Parameters of remote connection parameters request reply command complete event. */
typedef struct HCI_CC_LE_RemoteConnParamReqReply_T
{
    uint8_t     status;                                                         /**< Status of the executed command. */
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
} HCI_CC_LE_RemoteConnParamReqReply_T;

/**@brief Parameters of remote connection parameters request negative reply command complete event. */
typedef struct HCI_CC_LE_RemoteConnParamReqNegReply_T
{
    uint8_t     status;                                                         /**< Status of the executed command. */
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
} HCI_CC_LE_RemoteConnParamReqNegReply_T;

/**@brief Parameters of set data length command complete event. */
typedef struct HCI_CC_LE_SetDataLength_T
{
    uint8_t     status;                                                         /**< Status of the executed command. */
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
} HCI_CC_LE_SetDataLength_T;

/**@brief Parameters of read phy command complete event. */
typedef struct HCI_CC_LE_ReadPhy_T
{
    uint8_t     status;                                                         /**< Status of the executed command. */
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint8_t     txPhy;                                                          /**< The transmitter PHY for the connection. */
    uint8_t     rxPhy;                                                          /**< The receiver PHY for the connection. */
} HCI_CC_LE_ReadPhy_T;

/**@brief Parameters of set extended advertising parameters command complete event. */
typedef struct HCI_CC_LE_SetExtAdvertisingParameters_T
{
    uint8_t     status;                                                         /**< Status of the executed command. */
    int8_t      selectTxPower;                                                  /**< Selected transmit power. */
} HCI_CC_LE_SetExtAdvertisingParameters_T;

/**@brief Parameters of read transmit power command complete event. */
typedef struct HCI_CC_LE_ReadTransmitPower_T
{
    uint8_t     status;                                                         /**< Status of the executed command. */
    int8_t      minTxPower;                                                     /**< Minimum transmit power. */
    int8_t      maxTxPower;                                                     /**< Maximum transmit power. */
} HCI_CC_LE_ReadTransmitPower_T;

/**@brief Parameters of enhanced read transmit power command complete event. */
typedef struct HCI_CC_LE_EnhancedReadTransmitPower_T
{
    uint8_t     status;                                                         /**< Status of the executed command. */
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
    uint8_t     phy;                                                            /**< Indicate transmit power of which PHY. */
    uint8_t     currentTxPowerLevel;                                            /**< Current transmit power. */
    uint8_t     maxTxPowerLevel;                                                /**< Maximum transmit power. */
} HCI_CC_LE_EnhancedReadTransmitPower_T;

/**@brief Parameters of set transmit power reporting enable command complete event. */
typedef struct HCI_CC_LE_SetTransmitPowerReportingEnable_T
{
    uint8_t     status;                                                         /**< Status of the executed command. */
    uint16_t    connHandle;                                                     /**< Connection handle associated with this connection. */
} HCI_CC_LE_SetTransmitPowerReportingEnable_T;

/**@brief Indicate a connection is terminated. */
typedef struct HCI_EvtDisconnect_T
{
    uint8_t                 status;                                             /**< The status for disconnection. */
    uint16_t                connHandle;                                         /**< Connection handle associated with this connection. */
    uint8_t                 reason;                                             /**< The reason for disconnection. */
} HCI_EvtDisconnect_T;

/**@brief Indicate that the change of the encryption mode has been completed. */
typedef struct HCI_EvtEncryptChange_T
{
    uint8_t                 status;                                             /**< Encryption status. */
    uint16_t                connHandle;                                         /**< Connection handle associated with this connection. */
    uint8_t                 encEnable;                                          /**< Encryption Enable. */
} HCI_EvtEncryptChange_T;

/**@brief Indicate the completion of the process obtaining the version information of the remote Controller. */
typedef struct HCI_EvtReadRemoteVer_T
{
    uint8_t             status;                                                 /**< Status of read remote version information complete response. */
    uint16_t            connHandle;                                             /**< Connection handle associated with this connection. */
    uint8_t             version;                                                /**< Version of the current LMP in the remote controller. */
    uint16_t            manuName;                                               /**< Manufacturer name of the remote controller. */
    uint16_t            subVersion;                                             /**< Subversion of the LMP in the remote controller. */
} HCI_EvtReadRemoteVer_T;

/**@brief Indicate the number of completed packets of specific connection. */
typedef struct HCI_CompletePacket_T
{
    uint16_t                connHandle;                                         /**< Connection handle associated with this connection. */
    uint16_t                numPackets;                                         /**< Number of completed packet. */
} HCI_CompletePacket_T;

/**@brief Indicate the Host how many HCI Data packets have been completed for each Connection_Handle 
          since the previous @ref HCI_NBR_OF_COMPLETED_PACKETS event was sent to the Host. */
typedef struct HCI_EvtNumOfCompletePacket_T
{
    uint8_t                 numHandles;                                         /**< Number of connection handle. */
    HCI_CompletePacket_T    completePacket[HCI_MAX_NUM_CONN_HANDLE];            /**< Number of packets of each connection. */
} HCI_EvtNumOfCompletePacket_T;

/**@brief Indicate that the the encryption key was refreshed. */
typedef struct HCI_EvtKeyRefreshComplete_T
{
    uint8_t                 status;                                             /**< Encryption key refresh status. */
    uint16_t                connHandle;                                         /**< Connection handle associated with this connection. */
} HCI_EvtKeyRefreshComplete_T;

/**@brief Indicate host that a new connection has been created. */
typedef struct HCI_EvtLeConnect_T
{
    uint8_t                 status;                                             /**< Status of the connection. */
    uint16_t                connHandle;                                         /**< Connection handle associated with this connection. */
    uint8_t                 role;                                               /**< Role of the connection. Central or Peripheral. */
    uint8_t                 peerAddrType;                                       /**< Remote peer bluetooth address type. */
    uint8_t                 peerAddr[HCI_BD_ADDRESS_LEN];                       /**< Remote peer bluetooth address. */
    uint16_t                connInterval;                                       /**< Connection interval used on this connection. */
    uint16_t                connLatency;                                        /**< Peripheral latency for the connection in terms of number of connection events. */
    uint16_t                supervisionTimeout;                                 /**< Supervision timeout of the connection. The timeout in milliseconds shall be larger than (1 + latency) * intervalMax * 2, where intervalMax is given in milliseconds. */
    uint8_t                 centralClkAcc;                                      /**< Central clock accuracy. */
} HCI_EvtLeConnect_T;

/**@brief Parameters of advertising report details. */
typedef struct HCI_AdvReportDetails_T
{
    uint8_t                 eventType;                                          /**< Event type. */
    uint8_t                 addrType;                                           /**< Address type. */
    uint8_t                 addr[HCI_BD_ADDRESS_LEN];                           /**< Bluetooth address. */
    uint8_t                 advLength;                                          /**< Length of advertising data. */
    uint8_t                 advData[HCI_MAX_ADV_LENGTH];                        /**< Advertising data. */
    int8_t                  rssi;                                               /**< RSSI value. */
} HCI_AdvReportDetails_T;

/**@brief Indicate that one or more Bluetooth devices have responded to an active scan or have broadcast advertisements that were received during a passive scan. */
typedef struct HCI_EvtLeAdvReport_T
{
    uint8_t                 numReports;                                         /**< Number of responses in event. */
    HCI_AdvReportDetails_T  reports[HCI_MAX_ADV_REPORTS];                       /**< Details of each report. */
} HCI_EvtLeAdvReport_T;

/**@brief Indicate that the Controller process to update the connection has completed. */
typedef struct HCI_EvtLeConnParamUpdate_T
{
    uint8_t                 status;                                             /**< Status of connection parameter update process. */
    uint16_t                connHandle;                                         /**< Connection handle associated with this connection. */
    uint16_t                connInterval;                                       /**< Connection interval used on this connection. */
    uint16_t                connLatency;                                        /**< Peripheral latency for the connection in number of connection events. */
    uint16_t                supervisionTimeout;                                 /**< Supervision timeout of the connection. The timeout in milliseconds shall be larger than (1 + latency) * intervalMax * 2, where intervalMax is given in milliseconds. */
} HCI_EvtLeConnParamUpdate_T;

/**@brief Indicate the completion of the process of the controller obtaining the supported features of remote Bluetooth device. */
typedef struct HCI_EvtLeReadRemoteFeature_T
{
    uint8_t                 status;                                             /**< Status of the read remote feature process. */
    uint16_t                connHandle;                                         /**< Connection handle associated with this connection. */
    uint8_t                 leFeatures[HCI_FEATURES_BITMASK_LENGTH];            /**< Bit Mask List of LE features. */
} HCI_EvtLeReadRemoteFeature_T;

/**@brief Indicate that the peer device, in the central role, is attempting to encrypt or re-encrypt the link and is requesting the Long Term Key from the Host. */
typedef struct HCI_EvtLeLongTermKeyReq_T
{
    uint16_t                connHandle;                                         /**< Connection handle associated with this connection. */
    uint8_t                 randomNum[HCI_LTK_RANDOM_SIZE];                     /**< 64-bit random number. */
    uint16_t                encDiver;                                           /**< 16-bit encrypted diversifier. */
} HCI_EvtLeLongTermKeyReq_T;

/**@brief Indicate the host that the remote device is requesting a change in the connection parameters. */
typedef struct HCI_EvtLeRemoteConnParamsReq_T
{
    uint16_t                connHandle;                                         /**< Connection handle. */
    uint16_t                intervalMin;                                        /**< Minimum value of the connection interval requested by the remote device. */
    uint16_t                intervalMax;                                        /**< Maximum value of the connection interval requested by the remote device. */
    uint16_t                latency;                                            /**< Peripheral latency for the connection in number of connection events. */
    uint16_t                supervisionTimeout;                                 /**< Supervision timeout. */
} HCI_EvtLeRemoteConnParamsReq_T;

/**@brief Notify the host of a change to either the maximum LL Data PDU Payload length or the maximum transmission time of packets containing LL Data PDUs in either direction. */
typedef struct HCI_EvtLeDataLengthChange_T
{
    uint16_t                connHandle;                                         /**< Connection handle. */
    uint16_t                maxTxOctects;                                       /**< The maximum number of payload octets in a LLData PDU that the local Controller will send on this connection. */
    uint16_t                maxTxTime;                                          /**< The maximum time that the local Controller will take to send a Link Layer packet
                                                                                     containing an LL Data PDU on this connection. */
    uint16_t                maxRxOctets;                                        /**< The maximum number of payload octets in a Link Layer packet that the local Controller expects to receive on this connection. */
    uint16_t                maxRxTime;                                          /**< The maximum time that the local Controller expects to take to receive Link Layer packet on this connection. */
} HCI_EvtLeDataLengthChange_T;

/**@brief Indicate the host that a new connection has been created. */
typedef struct HCI_EvtLeEnhanceConnect_T
{
    uint8_t                 status;                                             /**< Status of the connection complete. */
    uint16_t                connHandle;                                         /**< Connection handle associated with this connection. */
    uint8_t                 role;                                               /**< Role of the connection. Central or Peripheral. */
    uint8_t                 peerAddrType;                                       /**< Remote peer bluetooth address type. */
    uint8_t                 peerAddr[HCI_BD_ADDRESS_LEN];                       /**< Remote peer bluetooth address. */
    uint8_t                 localRpa[HCI_BD_ADDRESS_LEN];                       /**< Resolvable Private Address being used by the local device for this connection. */
    uint8_t                 peerRpa[HCI_BD_ADDRESS_LEN];                        /**< Resolvable Private Address being used by the peer device for this connection. */
    uint16_t                connInterval;                                       /**< Connection interval used on this connection. */
    uint16_t                connLatency;                                        /**< Peripheral latency for the connection in number of connection events. */
    uint16_t                supervisionTimeout;                                 /**< Supervision timeout of the connection. The timeout in milliseconds shall be larger than (1 + latency) * intervalMax * 2, where intervalMax is given in milliseconds. */
    uint8_t                 centralClkAcc;                                      /**< Central clock accuracy. */
} HCI_EvtLeEnhanceConnect_T;

/**@brief Parameters of direct advertising report details. */
typedef struct HCI_DirectAdvReportDetails_T
{
    uint8_t                 eventType;                                          /**< Event type. */
    uint8_t                 addrType;                                           /**< Address type. */
    uint8_t                 addr[HCI_BD_ADDRESS_LEN];                           /**< Bluetooth address. */
    uint8_t                 directAddrType;                                     /**< Address type of direct advertising. */
    uint8_t                 directAddr[HCI_BD_ADDRESS_LEN];                     /**< Bluetooth address of direct advertising. */
    int8_t                  rssi;                                               /**< RSSI value. */
} HCI_DirectAdvReportDetails_T;

/**@brief Indicate that directed advertisements have been received. */
typedef struct HCI_EvtLeDirectAdvReport_T
{
    uint8_t                         numReports;                                 /**< Number of responses in event. */
    HCI_DirectAdvReportDetails_T    reports[HCI_MAX_ADV_REPORTS];               /**< Details of each report. */
} HCI_EvtLeDirectAdvReport_T;

/**@brief Indicate that the controller has changed the transmitter PHY or receiver PHY in use. */
typedef struct HCI_EvtLePhyUpdate_T
{
    uint8_t                 status;                                             /**< Status of PHY update process. */
    uint16_t                connHandle;                                         /**< Connection handle associated with this connection. */
    uint8_t                 txPhy;                                              /**< The transmitter PHY for the connection. */
    uint8_t                 rxPhy;                                              /**< The receiver PHY for the connection. */
} HCI_EvtLePhyUpdate_T;

/**@brief Parameters of extended advertising report details. */
typedef struct HCI_ExtAdvReportDetails_T
{
    uint16_t                eventType;                                          /**< Event type */
    uint8_t                 addrType;                                           /**< Address type. */
    uint8_t                 addr[HCI_BD_ADDRESS_LEN];                           /**< Bluetooth address. */
    uint8_t                 priPhy;                                             /**< Primary advertisement PHY. */
    uint8_t                 secPhy;                                             /**< Secondary advertisement PHY. */
    uint8_t                 sid;                                                /**< Value of the Advertising SID subfield in the ADI field of the PDU. */
    int8_t                  txPower;                                            /**< Advertising tx power. */
    int8_t                  rssi;                                               /**< RSSI value. */
    uint16_t                periodicAdvInterval;                                /**< Periodic advertising interval. */
    uint8_t                 directAddrType;                                     /**< Address type of direct advertising. */
    uint8_t                 directAddr[HCI_BD_ADDRESS_LEN];                     /**< Bluetooth address of direct advertising. */
    uint8_t                 advLength;                                          /**< Length of advertising data. */
    uint8_t                 advData[HCI_EVT_MAX_EXTENDED_ADVERTISING_DATA_LENGTH];  /**< Advertising data. */
} HCI_ExtAdvReportDetails_T;

/**@brief Indicate that one or more Bluetooth devices have responded to an active scan or have broadcast advertisements that were received during a passive scan. */
typedef struct HCI_EvtLeExtAdvReport_T
{
    uint8_t                     numReports;                                     /**< Number of responses in event. */
    HCI_ExtAdvReportDetails_T   reports[HCI_MAX_ADV_REPORTS];                   /**< Details of each report. */
} HCI_EvtLeExtAdvReport_T;

/**@brief Indicate that the controller has received the first periodic advertising packet from an advertiser. */
typedef struct HCI_EvtLePeriodicAdvSyncEst_T
{
    uint8_t                 status;                                             /**< Status of periodic advertising sync. */
    uint16_t                syncHandle;                                         /**< Identifying the periodic advertising train. */
    uint8_t                 advSid;                                             /**< Value of the Advertising SID subfield in the ADI field of the PDU. */
    uint8_t                 advAddrType;                                        /**< Advertising address type. */
    uint8_t                 advAddr[HCI_BD_ADDRESS_LEN];                        /**< Advertising bluetooth address. */
    uint8_t                 advPhy;                                             /**< Advertiser PHY. */
    uint16_t                periodicAdvInterval;                                /**< Periodic advertising interval. */
    uint8_t                 advClkAccuracy;                                     /**< Advertiser clock accuracy. */
} HCI_EvtLePeriodicAdvSyncEst_T;

/**@brief Indicate that the controller has received a Periodic Advertising packet. */
typedef struct HCI_EvtLePeriodicAdvReport_T
{
    uint16_t                syncHandle;                                         /**< Identifying the periodic advertising train. */
    uint8_t                 txPower;                                            /**< Advertising tx power. */
    int8_t                  rssi;                                               /**< RSSI value. */
    uint8_t                 cteType;                                            /**< Type of Constant Tone Extension. */
    uint8_t                 dataStatus;                                         /**< Status of advertising data. */
    uint8_t                 advLength;                                          /**< Length of advertising data. */
    uint8_t                 advData[HCI_EVT_MAX_PERIODIC_ADVERTISING_DATA_LENGTH];  /**< Data received from a periodic advertising packet. */
} HCI_EvtLePeriodicAdvReport_T;

/**@brief Indicate that the controller has not received a periodic advertising packet from the train identified by syncHandle within the timeout period. */
typedef struct HCI_EvtLePeriodicAdvSyncLost_T
{
    uint16_t                syncHandle;                                         /**< Identifying the periodic advertising train. */
} HCI_EvtLePeriodicAdvSyncLost_T;

/**@brief Indicate that the controller has terminated advertising in the advertising sets specified by the advHandle parameter. */
typedef struct HCI_EvtLeAdvSetTerminated_T
{
    uint8_t                 status;                                             /**< Status of terminating advertising set. */
    uint8_t                 advHandle;                                          /**< Used to identify an advertising set. */
    uint16_t                connHandle;                                         /**< Connection handle associated with this connection. */
    uint8_t                 numComplExtAdvEvents;                               /**< Number of completed extended advertising events transmitted by the controller. */
} HCI_EvtLeAdvSetTerminated_T;

/**@brief Indicate that a SCAN_REQ PDU or an AUX_SCAN_REQ PDU has been received by the advertiser. */
typedef struct HCI_EvtLeScanReqReceived_T
{
    uint8_t                 advHandle;                                          /**< Used to identify an advertising set. */
    uint8_t                 scannerAddrType;                                    /**< Scanner address type. */
    uint8_t                 scannerAddr[HCI_BD_ADDRESS_LEN];                    /**< Scanner bluetooth address. */
} HCI_EvtLeScanReqReceived_T;

/**@brief Indicate which channel selection algorithm is used on a data physical channel connection. */
typedef struct HCI_EvtLeChannelSelectAlgorithm_T
{
    uint16_t                connHandle;                                         /**< Connection handle associated with this connection. */
    uint8_t                 channelSelectAlgorithm;                             /**< Used LE Channel Selection Algorithm. */
} HCI_EvtLeChannelSelectAlgorithm_T;

/**@brief Report the transmit power level of specific connection. */
typedef struct HCI_EvtLeTxPowerReporting_T
{
    uint8_t                 status;                                             /**< Executed status of HCI_LE_Read_Remote_Transmit_Power_Level command.*/
    uint16_t                connHandle;                                         /**< Connection handle associated with this connection. */
    uint8_t                 reason;                                             /**< The reason for changed. */
    uint8_t                 phy;                                                /**< PHY type. */
    int8_t                  txPowerLevel;                                       /**< Indicate the transmit power level for the PHY. */
    uint8_t                 txPowerLevelFlag;                                   /**< Indicate if transmit power level reach its min/max level. */
    int8_t                  delta;                                              /**< Change in power level for transmitter being reported. */
} HCI_EvtLeTxPowerReporting_T;

/**@brief Event content indicating that a packet containing a valid MIC of the connection was not received within the authenticated payload timeout. */
typedef struct HCI_EvtAuthPayloadTimeout_T
{
    uint16_t                connHandle;                                         /**< Connection handle associated with this connection. */
} HCI_EvtAuthPayloadTimeout_T;

/**@} */ //HOST_HCI_STRUCTS

/** @} */ // end of HOST_HCI

#endif

