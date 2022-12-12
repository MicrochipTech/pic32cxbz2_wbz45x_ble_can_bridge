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
  BLE GAP Header File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_gap.h

  Summary:
    This file contains the BLE GAP functions for application user.

  Description:
    This file contains the BLE GAP functions and event for application user.  The
    "BLE_GAP_Init" function shall be called in the "APP_Initialize" function to 
    initialize the this modules in the system.
 *******************************************************************************/


/**
 * @addtogroup BLE_GAP
 * @{
 */
#ifndef BLE_GAP_H
#define BLE_GAP_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdbool.h>
#include <stdint.h>
#include "gap_defs.h"

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************

/**@addtogroup BLE_GAP_DEFINES Defines
 * @{ */
 
/**@defgroup BLE_GAP_MAX_CONN_HANDLE Maximum connection handle
 * @brief The definition of maximum allowed GAP connection handle
 * @{ */
#define BLE_GAP_MAX_CONN_HANDLE                                 0xEFF       /**< Maximum BLE GAP connection handle */
/** @} */ 

/**@defgroup BLE_GAP_MAX_ADV_HANDLE Maximum advertising handle
 * @brief The definition of maximum allowed Advertising handle
 * @{ */
#define BLE_GAP_MAX_ADV_HANDLE                                  0xEF        /**< Maximum BLE ADV handle */
/** @} */ 
 
/**@defgroup BLE_GAP_MAX_LINK_NBR Maximum connection number
 * @brief The definition of maximum allowed link number of GAP connections
 * @{ */
#define BLE_GAP_MAX_LINK_NBR                                    0x06        /**< Maximum allowed BLE GAP connections */
/** @} */

 
/**@defgroup BLE_GAP_ADV_INTERVAL Advertising interval
 * @brief Range for advertising interval. (Unit: 0.625 ms) Default value is 0x0800
 * @{ */
#define BLE_GAP_ADV_INTERVAL_MIN                                0x0020      /**< Minimum advertising interval. 20 ms */
#define BLE_GAP_ADV_INTERVAL_MAX                                0x4000      /**< Maximum advertising interval. 10.24 sec */
/** @} */


/**@defgroup BLE_GAP_ADV_TYPE Advertising type
 * @brief The definition of advertising types.
 * @{ */
#define BLE_GAP_ADV_TYPE_ADV_IND                                0x00        /**< Connectable undirected advertising (ADV_IND) (default). */
#define BLE_GAP_ADV_TYPE_ADV_DIRECT_IND                         0x01        /**< Connectable high duty cycle directed advertising (ADV_DIRECT_IND, high duty cycle). */
#define BLE_GAP_ADV_TYPE_ADV_SCAN_IND                           0x02        /**< Scannable undirected advertising (ADV_SCAN_IND). */
#define BLE_GAP_ADV_TYPE_ADV_NONCONN_IND                        0x03        /**< Non connectable undirected advertising (ADV_NONCONN_IND). */
#define BLE_GAP_ADV_TYPE_ADV_DIRECT_IND_LOW                     0x04        /**< Connectable low duty cycle directed advertising (ADV_DIRECT_IND, low duty cycle). */
/** @} */


/**@defgroup BLE_GAP_ADDR_TYPE Address type
 * @brief The definition of address types
 * @{ */
#define BLE_GAP_ADDR_TYPE_PUBLIC                                0x00        /**< Public device address (default). */
#define BLE_GAP_ADDR_TYPE_RANDOM_STATIC                         0x01        /**< Static random device address. */
#define BLE_GAP_ADDR_TYPE_RANDOM_RESOLVABLE                     0x02        /**< Private resolvable random device address. */
#define BLE_GAP_ADDR_TYPE_RANDOM_NON_RESOLVABLE                 0x03        /**< Private non resolvable random device address. */
/** @} */


/**@defgroup BLE_GAP_CP_RANGE  Connection parameters range
 * @brief Range of connection parameters.
 * @{ */
#define BLE_GAP_CP_MIN_CONN_INTVAL_MIN                          0x0006      /**< Minimum value of the connection interval. (Unit: 1.25 ms) */
#define BLE_GAP_CP_MIN_CONN_INTVAL_MAX                          0x0C80      /**< Minimum value of the connection interval. (Unit: 1.25 ms) */
#define BLE_GAP_CP_MAX_CONN_INTVAL_MIN                          0x0006      /**< Maximum value of the connection interval. (Unit: 1.25 ms) */
#define BLE_GAP_CP_MAX_CONN_INTVAL_MAX                          0x0C80      /**< Maximum value of the connection interval. (Unit: 1.25 ms) */
#define BLE_GAP_CP_LATENCY_MIN                                  0x0000      /**< Minimum allowed peripheral latency for the connection specified as the number of connection events. */
#define BLE_GAP_CP_LATENCY_MAX                                  0x01F3      /**< Maximum allowed peripheral latency for the connection specified as the number of connection events. */
#define BLE_GAP_CP_CONN_SUPERVISION_TIMEOUT_MIN                 0x000A      /**< Minimum of supervision timeout for the connection. (Unit: 10 ms) */
#define BLE_GAP_CP_CONN_SUPERVISION_TIMEOUT_MAX                 0x0C80      /**< Maximum of supervision timeout for the connection. (Unit: 10 ms) */
/** @} */


/**@defgroup BLE_GAP_ROLE Connection roles
 * @brief The definition of GAP role in connection state.
 * @{ */
#define BLE_GAP_ROLE_CENTRAL                                    0x00        /**< MBA plays Center role in connection state . */
#define BLE_GAP_ROLE_PERIPHERAL                                 0x01        /**< MBA plays Peripheral role in connection state . */
/** @} */


/**@defgroup BLE_GAP_ENCRYPT_STATUS Encryption status
 * @brief The definition of encryption status
 * @{ */
#define BLE_GAP_ENCRYPT_SUCCESS                                 0x00        /**< The link is encrypted successfully. */
#define BLE_GAP_ENCRYPT_FAIL                                    0x01        /**< The link encryption failed. */
/** @} */


/**@defgroup BLE_GAP_ADV_CHANNEL Advertising channel
 * @brief The definition of channel map bit field for advertising
 * @{ */
#define BLE_GAP_ADV_CHANNEL_37                                  0x01        /**< Use channel 37 for advertising. */
#define BLE_GAP_ADV_CHANNEL_38                                  0x02        /**< Use channel 38 for advertising. */
#define BLE_GAP_ADV_CHANNEL_39                                  0x04        /**< Use channel 39 for advertising. */
#define BLE_GAP_ADV_CHANNEL_ALL                                 0x07        /**< Use channels 37, 38 and 39 for advertising. */
/** @} */

/**@defgroup BLE_GAP_ADV_FILTER_POLICY Advertising filter policy
 * @brief The definition of advertising filter policy
 * @{ */
#define BLE_GAP_ADV_FILTER_DEFAULT                              0x00        /**< Default setting. Process scan and connection requests from all devices. */
#define BLE_GAP_ADV_FILTER_SCAN                                 0x01        /**< Process connection requests from all devices and only scan requests from devices that are in the filter accept list. */
#define BLE_GAP_ADV_FILTER_CONNECT                              0x02        /**< Process scan requests from all devices and only connection requests from devices that are in the filter accept list */
#define BLE_GAP_ADV_FILTER_SCAN_CONNECT                         0x03        /**< Process scan and connection requests only from devices in the filter accept list. */
/** @} */

/**@defgroup BLE_GAP_ADV_OPTION Advertising option
 * @brief The definition of advertising option
 * @{ */
#define BLE_GAP_ADV_OPTION_STORE_PARAMS                         0x00        /**< Store advertising parameters to BACKUP RAM. Once this option is enabled, only one advertising event would be executed.\n
                                                                                 This option is valid only if the parameter "enable" in the @ref BLE_GAP_SetAdvParams API is set to true. */
#define BLE_GAP_ADV_OPTION_LOAD_PARAMS                          0x01        /**< load advertising parameters from BACKUP RAM. Once this option is enabled, only one advertising event would be executed.\n
                                                                                 This option is valid only if the parameter "enable" in the @ref BLE_GAP_SetAdvParams API is set to true. */
/** @} */


/**@defgroup BLE_GAP_SCAN_FP Scan filter policy
 * @brief The definition of scanning filter policy
 * @{ */
#define BLE_GAP_SCAN_FP_ACCEPT_ALL                              0x00        /**< Default setting. Accept all advertising except directed advertising packets not addressed to this device. */
#define BLE_GAP_SCAN_FP_ACCEPT_LIST                             0x01        /**< Accept only advertisement packets from devices in the filter accept list. */
#define BLE_GAP_SCAN_FP_NOT_RESOLVED_DIRECTED                   0x02        /**< Accept advertising packets like @ref BLE_GAP_SCAN_FP_ACCEPT_ALL.
                                                                                 Directed advertising PDUs where the TargetA is a resolvable private address that cannot be resolved are also accepted.
                                                                                 Valid only for @ref BLE_GAP_SetExtScanningParams. */
#define BLE_GAP_SCAN_FP_ACCEPT_LIST_NOT_RESOLVED_DIRECTED       0x03        /**< Accept advertising packets like @ref BLE_GAP_SCAN_FP_ACCEPT_LIST.
                                                                                 Directed advertising PDUs where the TargetA is a resolvable private address that cannot be resolved are also accepted.
                                                                                 Valid only for @ref BLE_GAP_SetExtScanningParams. */
/** @} */
                                                                                 
/**@defgroup BLE_GAP_SCAN_CHANNEL Scan channel
 * @brief The definition of channel map bit field for scan
 * @{ */
#define BLE_GAP_SCAN_CHANNEL_37                                  0x01        /**< Channel 37 for scan. */
#define BLE_GAP_SCAN_CHANNEL_38                                  0x02        /**< Channel 38 for scan. */
#define BLE_GAP_SCAN_CHANNEL_39                                  0x04        /**< Channel 39 for scan. */
/** @} */


/**@defgroup BLE_GAP_INIT_FP Initiator filter policy
 * @brief The definition of initiator filter policy
 * @{ */
#define BLE_GAP_INIT_FP_FILTER_ACCEPT_LIST_NOT_USED             0x00        /**< Default setting. filter accept list is not used to determine which advertiser to connect to. */
#define BLE_GAP_INIT_FP_FILTER_ACCEPT_LIST_USED                 0x01        /**< filter accept list is used to determine which advertiser to connect to. Peer address shall be ignored. */
/** @} */


/**@defgroup BLE_GAP_SCAN_INTERVAL Scan interval
 * @brief Range of LE scan interval. (Unit: 0.625 ms) Default value is 0x10.
 * @{ */
#define BLE_GAP_SCAN_INTERVAL_MIN                               0x0004      /**< Minimum LE scan interval. 2.5 ms */
#define BLE_GAP_SCAN_INTERVAL_MAX                               0x4000      /**< Maximum LE scan interval. 10.24 sec */
/** @} */


/**@defgroup BLE_GAP_SCAN_WINDOW Scan window
 * @brief Range of LE scan window. (Unit: 0.625 ms) Default value is 0x10.
 * @{ */
#define BLE_GAP_SCAN_WINDOW_MIN                                 0x0004      /**< Minimum LE scan window. 2.5 ms */
#define BLE_GAP_SCAN_WINDOW_MAX                                 0x4000      /**< Maximum LE scan window. 10.24 sec */
/** @} */


/**@defgroup BLE_GAP_SCAN_TYPE Scan type
 * @brief The definition of scan types.
 * @{ */
#define BLE_GAP_SCAN_TYPE_PASSIVE_SCAN                          0x00        /**< Passive Scanning. No SCAN_REQ packets shall be sent (default). */
#define BLE_GAP_SCAN_TYPE_ACTIVE_SCAN                           0x01        /**< Active scanning. SCAN_REQ packets may be sent. */
/** @} */


/**@defgroup BLE_GAP_SCAN_FD Scan filter duplicate option
 * @brief The definition of filter duplicate setting for scanning.
 * @{ */
#define BLE_GAP_SCAN_FD_DISABLE                                 0x00        /**< Duplicate filtering disabled. */
#define BLE_GAP_SCAN_FD_ENABLE                                  0x01        /**< Duplicate filtering enabled. */
#define BLE_GAP_SCAN_FD_ENABLE_RESET                            0x02        /**< Duplicate filtering enabled. Valid only for @ref BLE_GAP_ExtScanningEnable_T */
/** @} */

/**@defgroup BLE_GAP_SCAN_MODES Scan modes
 * @brief The definition of scanning mode.
 * @{ */
#define BLE_GAP_SCAN_MODE_GENERAL_DISCOVERY                     0x00        /**< Devices in general or limited advertising mode will be reported. */
#define BLE_GAP_SCAN_MODE_LIMITED_DISCOVERY                     0x01        /**< Only devices in limited advertising mode will be reported. */
#define BLE_GAP_SCAN_MODE_OBSERVER                              0x02        /**< No filter policy. GAP will report all the advertisings. */
/** @} */


/**@defgroup BLE_GAP_ADV_REPORT_EVT_TYPE Event type of advertising report
 * @brief The definition of event type of advertising report.
 * @{ */
#define BLE_GAP_ADV_REPORT_EVT_TYPE_ADV_IND                     0x00        /**< Connectable undirected advertising (ADV_IND) Report Event. */
#define BLE_GAP_ADV_REPORT_EVT_TYPE_ADV_DIRECT_IND              0x01        /**< Connectable directed advertising (ADV_DIRECT_IND) Report Event. */
#define BLE_GAP_ADV_REPORT_EVT_TYPE_ADV_SCAN_IND                0x02        /**< Scannable undirected advertising (ADV_SCAN_IND) Report Event. */
#define BLE_GAP_ADV_REPORT_EVT_TYPE_ADV_NONCONN_IND             0x03        /**< Non connectable undirected advertising (ADV_NONCONN_IND) Report Event. */
#define BLE_GAP_ADV_REPORT_EVT_TYPE_SCAN_RSP                    0x04        /**< Scan Response (SCAN_RSP) Report Event. */
#define BLE_GAP_ADV_REPORT_EVT_TYPE_AUX_ADV_IND                 0x07        /**< Connectable undirected advertising (AUX_ADV_IND) Report Event. */
/** @} */

/**@defgroup BLE_GAP_EXT_ADV_EVT_PROP Event properties of advertising report
 * @brief The definition of extended advertising event properties.
 * @{ */
#define BLE_GAP_EXT_ADV_EVT_PROP_CONNECTABLE_ADV                (1 << 0)    /**< Connectable advertising */
#define BLE_GAP_EXT_ADV_EVT_PROP_SCANNABLE_ADV                  (1 << 1)    /**< Scannable advertising */
#define BLE_GAP_EXT_ADV_EVT_PROP_DIRECTED_ADV                   (1 << 2)    /**< Directed advertising */
#define BLE_GAP_EXT_ADV_EVT_PROP_HIGH_DUTY_DIRECTED_CONN_ADV    (1 << 3)    /**< High Duty Cycle Directed Connectable advertising (<= 3.75 ms Advertising Interval) */
#define BLE_GAP_EXT_ADV_EVT_PROP_LEGACY_ADV                     (1 << 4)    /**< Use legacy advertising PDUs */
#define BLE_GAP_EXT_ADV_EVT_PROP_OMIT_ADDRESS                   (1 << 5)    /**< Omit advertiser's address from all PDUs ("anonymous advertising") */
#define BLE_GAP_EXT_ADV_EVT_PROP_TX_POWER                       (1 << 6)    /**< Include TxPower in the extended header of the advertising PDU */
#define BLE_GAP_EXT_ADV_EVT_PROP_ALL                            (BLE_GAP_EXT_ADV_EVT_PROP_CONNECTABLE_ADV \
                                                                |BLE_GAP_EXT_ADV_EVT_PROP_SCANNABLE_ADV \
                                                                |BLE_GAP_EXT_ADV_EVT_PROP_DIRECTED_ADV  \
                                                                |BLE_GAP_EXT_ADV_EVT_PROP_HIGH_DUTY_DIRECTED_CONN_ADV \
                                                                |BLE_GAP_EXT_ADV_EVT_PROP_LEGACY_ADV    \
                                                                |BLE_GAP_EXT_ADV_EVT_PROP_OMIT_ADDRESS  \
                                                                |BLE_GAP_EXT_ADV_EVT_PROP_TX_POWER) /**< All properties */
/** @} */

/**@defgroup BLE_GAP_EXT_ADV_DATA_OPERAION Operation of extended advertising data
 * @brief The definition of extended advertising event operations.
 * @{ */
#define BLE_GAP_EXT_ADV_DATA_OP_INTERMEDIATE                    0x00        /**< Intermediate fragment of fragmented extended advertising data */
#define BLE_GAP_EXT_ADV_DATA_OP_FIRST_FRAG                      0x01        /**< First fragment of fragmented extended advertising data */
#define BLE_GAP_EXT_ADV_DATA_OP_LAST_FRAG                       0x02        /**< Last fragment of fragmented extended advertising data */
#define BLE_GAP_EXT_ADV_DATA_OP_COMPLETE                        0x03        /**< Complete extended advertising data */
#define BLE_GAP_EXT_ADV_DATA_OP_UNCHANGED                       0x04        /**< Unchanged data (just update the Advertising DID) */
/** @} */

/**@defgroup BLE_GAP_EXT_ADV_DATA_FRAG_PREF Fragment preference of extended advertising data
 * @brief The definition of extended advertising event fragment preference.
 * @{ */
#define BLE_GAP_EXT_ADV_DATA_FRAG_PREF_ALL                      0x00        /**< BLE Stack may fragment all advertising data */
#define BLE_GAP_EXT_ADV_DATA_FRAG_PREF_MIN                      0x01        /**< BLE Stack should not fragment or should minimize fragmentation of advertising data */
/** @} */

/**@defgroup BLE_GAP_EXT_PRIMARY_ADV_INTERVAL Extended primary advertising interval
 * @brief Range of LE extended primary advertising interval. (Unit: 0.625 ms)
 * @{ */
#define BLE_GAP_EXT_PRIMARY_ADV_INTERVAL_MIN                    0x0020      /**< Minimum LE extended primary adv interval. 20 ms */
#define BLE_GAP_EXT_PRIMARY_ADV_INTERVAL_MAX                    0x1F4000    /**< Maximum LE extended primary adv interval. 1280 sec */
/** @} */

/**@defgroup BLE_GAP_PERIODIC_ADV_PROP Property of periodic advertising
 * @brief The definition of periodic advertising properties.
 * @{ */
#define BLE_GAP_PERIODIC_ADV_PROP_TX_POWER                      (1 << 6)    /**< Include TxPower in the advertising PDU */
/** @} */

/**@defgroup BLE_GAP_PERIODIC_ADV_DATA_OPERAION Operation of periodic advertising data
 * @brief The definition of periodic advertising event operations.
 * @{ */
#define BLE_GAP_PERIODIC_ADV_DATA_OP_INTERMEDIATE               0x00        /**< Intermediate fragment of fragmented periodic advertising data */
#define BLE_GAP_PERIODIC_ADV_DATA_OP_FIRST_FRAG                 0x01        /**< First fragment of fragmented periodic advertising data */
#define BLE_GAP_PERIODIC_ADV_DATA_OP_LAST_FRAG                  0x02        /**< Last fragment of fragmented periodic advertising data */
#define BLE_GAP_PERIODIC_ADV_DATA_OP_COMPLETE                   0x03        /**< Complete periodic advertising data */
/** @} */


/**@defgroup BLE_GAP_PERIODIC_ACA The accuracy of the periodic advertiser's clock
 * @brief The definition of periodic advertising advertiser clock accuracy.
 * @{ */
#define BLE_GAP_PERIODIC_ACA_500_PPM                            0x00        /**< 500 ppm */
#define BLE_GAP_PERIODIC_ACA_250_PPM                            0x01        /**< 250 ppm */
#define BLE_GAP_PERIODIC_ACA_150_PPM                            0x02        /**< 150 ppm */
#define BLE_GAP_PERIODIC_ACA_100_PPM                            0x03        /**< 100 ppm */
#define BLE_GAP_PERIODIC_ACA_75_PPM                             0x04        /**< 750 ppm */
#define BLE_GAP_PERIODIC_ACA_50_PPM                             0x05        /**< 50 ppm */
#define BLE_GAP_PERIODIC_ACA_30_PPM                             0x06        /**< 30 ppm */
#define BLE_GAP_PERIODIC_ACA_20_PPM                             0x07        /**< 20 ppm */
/** @} */

/**@defgroup BLE_GAP_CTE_TYPE Type of Constant Tone Extension
 * @brief The definition of CTE type.
 * @{ */
#define BLE_GAP_CTE_TYPE_AOA                                    0x00        /**< AoA Constant Tone Extension. */
#define BLE_GAP_CTE_TYPE_AOD_WITH_1US                           0x01        /**< AoD Constant Tone Extension with 1 us slots. */
#define BLE_GAP_CTE_TYPE_AOD_WITH_2US                           0x02        /**< AoD Constant Tone Extension with 2 us slots. */
#define BLE_GAP_CTE_TYPE_NO                                     0x03        /**< No Constant Tone Extension. */
/** @} */

/**@defgroup BLE_GAP_DATA_STATUS Received data status
 * @brief The definition of data status.
 * @{ */
#define BLE_GAP_DATA_STATUS_COMPLETE                            0x00        /**< Data complete. */
#define BLE_GAP_DATA_STATUS_MORE_DATA                           0x01        /**< Data incomplete, more data to come. */
#define BLE_GAP_DATA_STATUS_DATA_TRUNCATED                      0x02        /**< Data incomplete, data truncated, no more to come. */

/** @} */

/**@defgroup BLE_GAP_PERIODIC_ADV_FRAGMENT_DATA_LEN Maximum periodic advertising fragment data length
 * @brief The definition of maximum periodic advertising fragment data length
 * @{ */
#define BLE_GAP_PERIODIC_ADV_FRAGMENT_MAX_LENGTH              	0xF7        /**< Maximum length of periodic advertising fragment data in bytes. */
/** @} */


/**@defgroup BLE_GAP_EXT_SCAN_DATA_LEN Extended scan data length
 * @brief Range of extended scan data length.
 * @{ */
#define BLE_GAP_EXT_SCAN_DATA_LEN_MIN                           0x004A      /**< Minimum extended scan data length. */
#define BLE_GAP_EXT_SCAN_DATA_LEN_MAX                           0x0672      /**< Maximum extended scan data length. */
/** @} */

/**@defgroup BLE_GAP_EXT_SCAN_2ND_ADV_NUM Maximum secondary adv for extended scan
 * @brief The definition of maximum secondary adv for extended scan.
 * @{ */
#define BLE_GAP_EXT_SCAN_2ND_ADV_NUM                            0x10       /**< Maximum secondary advertising packets apply to extended scan. */
/** @} */


/**@defgroup BLE_GAP_EXT_SCAN_INTERVAL Extended scan interval
 * @brief Range of LE extended scan interval. (Unit: 0.625 ms)
 * @{ */
#define BLE_GAP_EXT_SCAN_INTERVAL_MIN                           0x0004      /**< Minimum LE extened scan interval. 2.5 ms */
#define BLE_GAP_EXT_SCAN_INTERVAL_MAX                           0xFFFF      /**< Maximum LE extened scan interval. 40.959375 sec */
/** @} */


/**@defgroup BLE_GAP_EXT_SCAN_WINDOW Extended scan window
 * @brief Range of LE extended scan window. (Unit: 0.625 ms)
 * @{ */
#define BLE_GAP_EXT_SCAN_WINDOW_MIN                             0x0004      /**< Minimum LE extened scan window. 2.5 ms */
#define BLE_GAP_EXT_SCAN_WINDOW_MAX                             0xFFFF      /**< Maximum LE extened scan window. 40.959375 sec */
/** @} */

/**@defgroup BLE_GAP_PRIODIC_ADV_INTERVAL Periodic advertising interval
 * @brief Range of LE periodic advertising interval. (Unit: 1.25 ms)
 * @{ */
#define BLE_GAP_PERIODIC_ADV_INTERVAL_MIN                       0x0006      /**< Minimum LE periodic adv interval. 7.5 ms */
#define BLE_GAP_PERIODIC_ADV_INTERVAL_MAX                       0xFFFF      /**< Maximum LE periodic adv interval. 81.91875 sec */
/** @} */


/**@defgroup BLE_GAP_EXT_ADV_REPORT_EVT_TYPE Event type for extended advertising report
 * @brief The definition of rxtended advertising report event type.
 * @{ */
#define BLE_GAP_EXT_ADV_REPORT_EVT_TYPE_CONNECTABLE             (1 << 0)    /**< Connectable advertising. */
#define BLE_GAP_EXT_ADV_REPORT_EVT_TYPE_SCANNABLE               (1 << 1)    /**< Scannable advertising. */
#define BLE_GAP_EXT_ADV_REPORT_EVT_TYPE_DIRECTED                (1 << 2)    /**< Directed advertising. */
#define BLE_GAP_EXT_ADV_REPORT_EVT_TYPE_SCAN_RSP                (1 << 3)    /**< Scan Response. */
#define BLE_GAP_EXT_ADV_REPORT_EVT_TYPE_LEGACY                  (1 << 4)    /**< Legacy advertising PDUs used. */
/** @} */


/**@defgroup BLE_GAP_EXT_ADV_REPORT_DATA_STATUS Data status for extended advertising report
 * @brief The definition of extended advertising report data status.
 * @{ */
#define BLE_GAP_EXT_ADV_REPORT_DATA_STATUS_COMPLETE             0x00        /**< Complete. */
#define BLE_GAP_EXT_ADV_REPORT_DATA_STATUS_MORE                 0x01        /**< Incomplete, more data to come. */
#define BLE_GAP_EXT_ADV_REPORT_DATA_STATUS_TRUNCATED            0x02        /**< Incomplete, data truncated, no more to come. */
/** @} */

/**@defgroup BLE_GAP_EXT_ADV_REPORT_PHY PHY setting for extended advertising report
 * @brief The definition of extended advertising report phy.
 * @{ */
#define BLE_GAP_EXT_ADV_REPORT_PHY_NO                           0x00        /**< No packets on the secondary advertising channel. */
#define BLE_GAP_EXT_ADV_REPORT_PHY_1M                           0x01        /**< Advertiser PHY is LE 1M. */
#define BLE_GAP_EXT_ADV_REPORT_PHY_2M                           0x02        /**< Advertiser PHY is LE 2M. */
#define BLE_GAP_EXT_ADV_REPORT_PHY_CODED                        0x03        /**< Advertiser PHY is LE Coded. */
/** @} */


/**@defgroup BLE_GAP_PRIVACY_MODE Privacy mode
 * @brief The definition of privacy mode.
 * @{ */
#define BLE_GAP_PRIVACY_MODE_NETWORK                            0x00        /**< Use Network Privacy Mode. */
#define BLE_GAP_PRIVACY_MODE_DEVICE                             0x01        /**< Use Device Privacy Mode. */
#define BLE_GAP_PRIVACY_MODE_OFF                                0xFF        /**< Privacy Mode is disabled. */
/** @} */


/**@defgroup BLE_GAP_RPA_TIMEOUT RPA timeout
 * @brief The definition of RPA timeout.
 * @{ */
#define BLE_GAP_RPA_TIMEOUT_MIN                                 0x0001        /**< Minimum RPA timeout. */
#define BLE_GAP_RPA_TIMEOUT_MAX                                 0x0E10        /**< Maximum RPA timeout. */
/** @} */


/**@defgroup BLE_GAP_ADV_DATA_LEN Maximum advertising data length
 * @brief The definition of maximum advertising data length
 * @{ */
#define BLE_GAP_ADV_MAX_LENGTH                                  0x1F        /**< Maximum length of advertising data in bytes. */
/** @} */

/**@defgroup BLE_GAP_EXT_ADV_FRAGMENT_DATA_LEN Maximum extended advertising fragment data length
 * @brief The definition of maximum extended advertising fragment data length
 * @{ */
#define BLE_GAP_EXT_ADV_FRAGMENT_MAX_LENGTH                 	  0xE5        /**< Maximum length of extended advertising fragment data in bytes. */
/** @} */


/**@defgroup BLE_GAP_ADV_SID_RANGE Advertising SID range
 * @brief Range of advertising Set ID.
 * @{ */
#define BLE_GAP_ADV_SID_MIN                                     0x00        /**< The minimum advertising SID value. */
#define BLE_GAP_ADV_SID_MAX                                     0x0F        /**< The maximum advertising SID value. */
/** @} */


/**@defgroup BLE_GAP_SYNC_CREATE_OPTION Options for creating sync
 * @brief The definition of creating sync options.
 * @{ */
#define BLE_GAP_SYNC_CREATE_OPTION_USE_ADV_LIST                 (1 << 0)    /**< Use the Periodic Advertiser List to determine which advertiser to listen to. */
#define BLE_GAP_SYNC_CREATE_OPTION_REPORT_DISABLED              (1 << 1)    /**< Reporting initially disabled. */
/** @} */

/**@defgroup BLE_GAP_SYNC_TIMEOUT Synchronization timeout
 * @brief Synchronization timeout for the periodic advertising train.
 * @{ */
#define BLE_GAP_SYNC_TIMEOUT_MIN                                0x000A      /**< The minimum synchronization timeout value. */
#define BLE_GAP_SYNC_TIMEOUT_MAX                                0x4000      /**< The maximum synchronization timeout value. */
/** @} */

/**@defgroup BLE_GAP_SYNC_SKIP Maximum number of skipped periodic advertising event
 * @brief Maximum number of periodic advertising can be skipped.
 * @{ */
#define BLE_GAP_SYNC_SKIP_MAX                                   0x1F3       /**< The maximum periodic advertising event can be skipped. */
/** @} */


/**@defgroup BLE_GAP_MAX_FILTER_ACCEPT_LIST_NUM Maximum filter accept list number
 * @brief The definition of maximum number of filter accept list
 * @{ */
#define BLE_GAP_MAX_FILTER_ACCEPT_LIST_NUM                      0x08        /**< Maximum number of filter accept list. */
/** @} */

/**@defgroup BLE_GAP_MAX_RESOLV_NUM Maximum resolving list number
 * @brief The definition of maximum number of resolving list
 * @{ */
#define BLE_GAP_MAX_RESOLV_NUM                                  0x08        /**< Maximum number of resolving list. */
/** @} */


/**@defgroup BLE_GAP_PHY_OPTION PHY option for transmit and receive
 * @brief The definition of PHY option for TX and RX
 * @{ */
#define BLE_GAP_PHY_OPTION_NO_PREF                              0           /**< No preference. */
#define BLE_GAP_PHY_OPTION_1M                                   (1 <<0)     /**< Prefers to use the LE 1M PHY (possibly among others). */
#define BLE_GAP_PHY_OPTION_2M                                   (1 <<1)     /**< Prefers to use the LE 2M PHY (possibly among others). */
#define BLE_GAP_PHY_OPTION_CODED                                (1 <<2)     /**< Prefers to use the LE Coded PHY (possibly among others). */
/** @} */


/**@defgroup BLE_GAP_PHY_PREF Preferred PHY preference
 * @brief The definition of PHY preference
 * @{ */
#define BLE_GAP_PHY_PREF_NO                                     0           /**< No preferred coding when transmitting on the LE Coded PHY. */
#define BLE_GAP_PHY_PREF_S2                                     1           /**< Prefers that S=2 coding be used when transmitting on the LE Coded PHY. */
#define BLE_GAP_PHY_PREF_S8                                     2           /**< Prefers that S=8 coding be used when transmitting on the LE Coded PHY. */
/** @} */


/**@defgroup BLE_GAP_PHY_TYPE PHY type
 * @brief The definition of PHY type.
 * @{ */
#define BLE_GAP_PHY_TYPE_LE_1M                                  0x01        /**< The connection is LE 1M PHY */
#define BLE_GAP_PHY_TYPE_LE_2M                                  0x02        /**< The connection is LE 2M PHY */
#define BLE_GAP_PHY_TYPE_LE_CODED                               0x03        /**< The connection is LE Coded PHY*/
/** @} */


/**@defgroup BLE_GAP_MAX_DEV_NUM Maximum sync devices number
 * @brief The definition of maximum number of device could be set to advertiser list
 * @{ */
#define BLE_GAP_MAX_DEV_NUM                                     0x08        /**< Maximum number of resolving list. */
/** @} */


/**@defgroup BLE_GAP_TRANSMITTER_PHY_TYPE Transmitter PHY type
 * @brief The definition of transmitter test packet PHY type.
 * @{ */
#define BLE_GAP_TRANSMITTER_LE_1M_PHY                           0x01        /**< Transmitter set to use the LE 1M PHY */
#define BLE_GAP_TRANSMITTER_LE_2M_PHY                           0x02        /**< Transmitter set to use the LE 2M PHY */
#define BLE_GAP_TRANSMITTER_LE_CODED_PHY_S_8                    0x03        /**< Transmitter set to use the LE Coded PHY with S=8 data coding */
#define BLE_GAP_TRANSMITTER_LE_CODED_PHY_S_2                    0x04        /**< Transmitter set to use the LE Coded PHY with S=2 data coding */
/** @} */

/**@defgroup BLE_SCAN_FILTER_ARRAY_SIZE Scan filter length
 * @brief The definition of maximum length of scan filter field
 * @{ */
#define BLE_GAP_SCAN_SERVICE_DATA_MAX_LEN                       16          /**< Maximum service data array size. */
#define BLE_GAP_SCAN_MSD_MAX_LEN                                16          /**< Maximum manufacturer specific data array size. */
#define BLE_GAP_SCAN_NAME_MAX_LEN                               16          /**< Maximum name filter array size. */
/** @} */


/**@defgroup BLE_GAP_TX_POWER_REPORTING_REASON  TX power change reason
 * @brief The definition of disconnection reason.
 * @{ */
#define BLE_GAP_LOCAL_TX_POWER_CHANGED                          0           /**< Local transmit Power changed */
#define BLE_GAP_REMOTE_TX_POWER_CHANGED                         1           /**< Remote transmit Power changed */
#define BLE_GAP_READ_REMOTE_POWER_COMPLETED                     2           /**< Execute @ref BLE_GAP_ReadRemoteTxPowerLevel complete */
/** @} */

/**@defgroup BLE_GAP_EXT_ADV_DATA_LEN Maximum extended advertising data length
 * @brief The definition of maximum number of extended advertising data length
 * @{ */
#define BLE_GAP_EXT_ADV_DATA_LEN                                251         /**< Maximum extended advertising data length. */
/** @} */

/**@defgroup BLE_GAP_PERI_ADV_DATA_LEN Maximum periodic advertising data length
 * @brief The definition of maximum number of periodic advertising data length
 * @{ */
#define BLE_GAP_PERI_ADV_DATA_LEN                               252         /**< Maximum extended periodic data length. */
/** @} */

/**@} */ //BLE_GAP_DEFINES

/**@addtogroup BLE_GAP_ENUMS Enumerations
 * @{ */
 
/**@brief GAP events delivered to application from BLE Stack. */
typedef enum BLE_GAP_EventId_T
{
    BLE_GAP_EVT_CONNECTED,                                                  /**< BLE link is established. See @ref BLE_GAP_EvtConnect_T for the event details. */
    BLE_GAP_EVT_DISCONNECTED,                                               /**< BLE link is terminated. See @ref BLE_GAP_EvtDisconnect_T for the event details. */
    BLE_GAP_EVT_CONN_PARAM_UPDATE,                                          /**< The connection parameters of BLE link are updated. See @ref BLE_GAP_EvtConnParamUpdateParams_T for the event details. */
    BLE_GAP_EVT_ENCRYPT_STATUS,                                             /**< The encryption status of BLE link. See @ref BLE_GAP_EvtEncryptStatus_T for the event content. */
    BLE_GAP_EVT_ADV_REPORT,                                                 /**< Received advertising report. See @ref BLE_GAP_EvtAdvReport_T for the event details. */
    BLE_GAP_EVT_ENC_INFO_REQUEST,                                           /**< See @ref BLE_GAP_EvtEncInfoRequest_T for the event content. */
    BLE_GAP_EVT_REMOTE_CONN_PARAM_REQUEST,                                  /**< If remote device supports Link Layer Connection Parameters Request procedure, this request will receive when remote device
                                                                                 wants to change the connection parameters. See @ref BLE_GAP_EvtRemoteConnParamRequest_T for the event content. */
    BLE_GAP_EVT_EXT_ADV_REPORT,                                             /**< Received extended advertising report. See @ref BLE_GAP_EvtExtAdvReport_T for the event details. */
    BLE_GAP_EVT_ADV_TIMEOUT,                                                /**< Advertising terminated because timeout. */
    BLE_GAP_EVT_TX_BUF_AVAILABLE,                                           /**< Notify the ACL tx buffer is available. See @ref BLE_GAP_EvtTxBufAvailable_T. */
    BLE_GAP_EVT_DEVICE_NAME_CHANGED,                                        /**< The device name was changed by remote device via Generic Assess service. @ref BLE_GAP_EvtDeviceNameChanged_T for the event content. */
    BLE_GAP_EVT_AUTH_PAYLOAD_TIMEOUT,                                       /**< Authenticated payload timeout. @ref BLE_GAP_EvtAuthPayloadTimeout_T for the event content. */
    BLE_GAP_EVT_PHY_UPDATE,                                                 /**< PHY update. @ref BLE_GAP_EvtPhyUpdate_T for the event content. */
    BLE_GAP_EVT_SCAN_REQ_RECEIVED,                                          /**< Received scan request. @ref BLE_GAP_EvtScanReqReceived_T for the event content. */
    BLE_GAP_EVT_DIRECT_ADV_REPORT,                                          /**< Received direct advertising report. @ref BLE_GAP_EvtDirectAdvReport_T for the event content. */
    BLE_GAP_EVT_PERI_ADV_SYNC_EST,                                          /**< Periodic advertising sync established. @ref BLE_GAP_EvtPeriAdvSyncEst_T for the event content. */
    BLE_GAP_EVT_PERI_ADV_REPORT,                                            /**< Received periodic advertising report. @ref BLE_GAP_EvtPeriAdvReport_T for the event content. */
    BLE_GAP_EVT_PERI_ADV_SYNC_LOST,                                         /**< Periodic advertising sync lost. @ref BLE_GAP_EvtPeriAdvSyncLost_T for the event content. */
    BLE_GAP_EVT_ADV_SET_TERMINATED,                                         /**< Advertising set terminated. @ref BLE_GAP_EvtAdvSetTerminated_T for the event content. */
    BLE_GAP_EVT_SCAN_TIMEOUT,                                               /**< Scan terminated because timeout. */
    BLE_GAP_EVT_TRANSMIT_POWER_REPORTING,                                   /**< Report tx power level on the ACL connection identified by the Connection_Handle. @ref BLE_GAP_EvtTxPowerReporting_T for the event content. */
    BLE_GAP_EVT_ADV_COMPL,                                                  /**< Enable one time advertising is completed. See @ref BLE_GAP_EvtAdvCompl_T for the event content. */
    BLE_GAP_EVT_END
}BLE_GAP_EventId_T;

/**@} */ //BLE_GAP_ENUMS

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/**@addtogroup BLE_GAP_STRUCTS Structures
 * @{ */
 
/**@brief Bluetooth address. */
typedef struct BLE_GAP_Addr_T
{
    uint8_t                 addrType;                               /**< See @ref BLE_GAP_ADDR_TYPE. */
    uint8_t                 addr[GAP_MAX_BD_ADDRESS_LEN];           /**< Bluetooth address, LSB format. */
} BLE_GAP_Addr_T;


/**@brief Advertising parameters. */
typedef struct BLE_GAP_AdvParams_T
{
    uint16_t                intervalMin;                            /**< Minimum advertising interval, see @ref BLE_GAP_ADV_INTERVAL. (Unit: 0.625ms) */
    uint16_t                intervalMax;                            /**< Maximum advertising interval, see @ref BLE_GAP_ADV_INTERVAL. (Unit: 0.625ms) */
    uint8_t                 type;                                   /**< Advertising type, see @ref BLE_GAP_ADV_TYPE. */
    BLE_GAP_Addr_T          peerAddr;                               /**< Remote bluetooth address and address type, see @ref BLE_GAP_Addr_T.*/
    uint8_t                 advChannelMap;                          /**< Advertising Channel Map. See @ref BLE_GAP_ADV_CHANNEL */
    uint8_t                 filterPolicy;                           /**< Advertising filter policy. See @ref BLE_GAP_ADV_FILTER_POLICY */
} BLE_GAP_AdvParams_T;


/**@brief Connection parameters. */
typedef struct BLE_GAP_ConnParams_T
{
    uint16_t                intervalMin;                            /**< Define minimum allowed connection interval. The value shall not be greater than maximum allowed connection interval. See @ref BLE_GAP_CP_RANGE. */
    uint16_t                intervalMax;                            /**< Define maximum allowed connection interval. See @ref BLE_GAP_CP_RANGE. */
    uint16_t                latency;                                /**< Peripheral latency for the connection in terms of number of connection events, see @ref BLE_GAP_CP_RANGE. */
    uint16_t                supervisionTimeout;                     /**< Supervision timeout of the connection. The timeout in milliseconds shall be larger than (1 + latency) * intervalMax * 2, where intervalMax is given in milliseconds. See @ref BLE_GAP_CP_RANGE. */
} BLE_GAP_ConnParams_T;

/**@brief Advertising data. */
typedef struct BLE_GAP_AdvDataParams_T
{
    uint8_t                 advLen;                                 /**< Length of advertising data, see @ref BLE_GAP_ADV_DATA_LEN for the maximum length. */
    uint8_t                 advData[BLE_GAP_ADV_MAX_LENGTH];        /**< Advertising data */
} BLE_GAP_AdvDataParams_T;


/**@brief Resolving list.*/
typedef struct BLE_GAP_ResolvingListParams_T
{
    BLE_GAP_Addr_T          peerIdAddr;                             /**< Peer identity address. */
    uint8_t                 peerIrk[16];                            /**< IRK of the peer device. */
    uint8_t                 localIrk[16];                           /**< IRK of the local device. */
    uint8_t                 privacyMode;                            /**< Privacy mode. See @ref BLE_GAP_PRIVACY_MODE */
} BLE_GAP_ResolvingListParams_T;


/**@brief Privacy parameters. */
typedef struct BLE_GAP_LocalPrivacyParams_T
{
    uint8_t                 privacyAddrType;                        /**< Privacy address type. See @ref BLE_GAP_ADDR_TYPE.
                                                                        Only BLE_GAP_ADDR_TYPE_RANDOM_RESOLVABLE 
                                                                        or BLE_GAP_ADDR_TYPE_RANDOM_NON_RESOLVABLE is allowed. */
    uint16_t                addrTimeout;                            /**< Timeout interval before the device changes Random Privacy Device Address. See @ref BLE_GAP_RPA_TIMEOUT. (Unit: 1 Seconds). */
    uint8_t                 localIrk[16];                           /**< IRK (Identity Resolving Key) of the local device. Set to 0 to use default IRK. */
} BLE_GAP_LocalPrivacyParams_T;


/**@brief Scanning parameters. */
typedef struct BLE_GAP_ScanningParams_T
{
    uint8_t                 type;                                   /**< Scanning type. See @ref BLE_GAP_SCAN_TYPE. */
    uint16_t                interval;                               /**< Scanning interval. See @ref BLE_GAP_SCAN_INTERVAL. (Unit: 0.625ms) */
    uint16_t                window;                                 /**< Scanning window. See @ref BLE_GAP_SCAN_WINDOW. (Unit: 0.625ms) */
    uint8_t                 filterPolicy;                           /**< Scanning filter policy. See @ref BLE_GAP_SCAN_FP. */
    uint8_t                 disChannel;                             /**< Disable specific channel during scanning. See @ref BLE_GAP_SCAN_CHANNEL.*/
} BLE_GAP_ScanningParams_T;

/**@brief Create connection parameters. */
typedef struct BLE_GAP_CreateConnParams_T
{
    uint16_t                scanInterval;                           /**< Recommended scan interval setting. See @ref BLE_GAP_SCAN_INTERVAL. */
    uint16_t                scanWindow;                             /**< Recommended scan window setting. It shall be set to a value smaller or equal to the value set for the scanInterval. See @ref BLE_GAP_SCAN_WINDOW. */
    uint8_t                 filterPolicy;                           /**< Initiator filter policy. It is used to determine whether the Filter Accept List is used. If the Filter Accept List is not used, the peerAddr argument specify the address type and address of the advertising device to connect to. See @ref BLE_GAP_INIT_FP. */
    BLE_GAP_Addr_T          peerAddr;                               /**< The address of peer connectable device, see @ref BLE_GAP_Addr_T. It is invalid once filterPolicy is enable. */
    BLE_GAP_ConnParams_T    connParams;                             /**< GAP connection parameters. See @ref BLE_GAP_ConnParams_T. */
} BLE_GAP_CreateConnParams_T;

/**@brief Supplement parameters for extended create connection. */
typedef struct BLE_GAP_ExtCreateConnParams_T
{
    bool                    enable;                                 /**< Set to true if following configuration is valid. */
    uint16_t                scanInterval;                           /**< Scan interval, see @ref BLE_GAP_EXT_SCAN_INTERVAL. */
    uint16_t                scanWindow;                             /**< Scan window, see @ref BLE_GAP_EXT_SCAN_WINDOW. */
    BLE_GAP_ConnParams_T    connParams;                             /**< GAP connection parameters. See @ref BLE_GAP_ConnParams_T. */
}BLE_GAP_ExtCreateConnParams_T;


/**@brief Extended create connection phy setting. */
typedef struct BLE_GAP_ExtCreateConnPhy_T
{
    BLE_GAP_ExtCreateConnParams_T    le1mPhy;                         /**< Scan connectable advertisements on the LE 1M PHY. Connection parameters for the LE 1M PHY are provided */
    BLE_GAP_ExtCreateConnParams_T    le2mPhy;                         /**< Connection parameters for the LE 2M PHY are provided. */
    BLE_GAP_ExtCreateConnParams_T    leCodedPhy;                      /**< Scan connectable advertisements on the LE Coded PHY. Connection parameters for the LE Coded PHY are provided. */
}BLE_GAP_ExtCreateConnPhy_T;


/**@brief Extended advertising parameters. */
typedef struct BLE_GAP_ExtAdvParams_T
{
    uint8_t                 advHandle;                              /**< Identifies the advertising set whose parameters are being configured
                                                                         (Range: 0 to 0xEF). See @ref BLE_GAP_MAX_ADV_HANDLE */
    uint16_t                evtProperies;                           /**< The type of advertising event that is being configured and its basic properties.
                                                                         The bit combination of @ref BLE_GAP_EXT_ADV_EVT_PROP */
    uint32_t                priIntervalMin;                         /**< Minimum advertising interval, (Range: 0x20 to 0x1F4000). (Unit: 0.625ms)
                                                                         See @ref BLE_GAP_EXT_PRIMARY_ADV_INTERVAL */
    uint32_t                priIntervalMax;                         /**< Maximum advertising interval, (Range: 0x20 to 0x1F4000). (Unit: 0.625ms)
                                                                         See @ref BLE_GAP_EXT_PRIMARY_ADV_INTERVAL */
    uint8_t                 priChannelMap;                          /**< Advertising Channel Map. See @ref BLE_GAP_ADV_CHANNEL 
                                                                         BLE_GAP_ADV_CHANNEL_ALL can't be used*/
    BLE_GAP_Addr_T          peerAddr;                               /**< Remote bluetooth address and address type, see @ref BLE_GAP_Addr_T.*/
    uint8_t                 filterPolicy;                           /**< Advertising filter policy. See @ref BLE_GAP_ADV_FILTER_POLICY */
    int8_t                  txPower;                                /**< The maximum power level at which the advertising packets are to be transmitted on the advertising channels.
                                                                         Set to 0x7F if user has no perference of extended advertising TX power level. Level will be adjusted if value is not in range. */
    uint8_t                 priPhy;                                 /**< Indicates the PHY on which the advertising packets are transmitted on the primary advertising channel.
                                                                         2M can't be used for primary advertising. See @ref BLE_GAP_PHY_TYPE.*/
    uint8_t                 secMaxSkip;                             /**< The maximum number of advertising events that can be skipped before the AUX_ADV_IND can be sent. */
    uint8_t                 secPhy;                                 /**< Indicates the PHY on which the advertising packets are transmitted on the secondary advertising channel.
                                                                         See @ref BLE_GAP_PHY_TYPE */
    uint8_t                 sid;                                    /**< The value to be transmitted in the Advertising SID subfield of the ADI field of the Extended Header.
                                                                         See @ref BLE_GAP_ADV_SID_RANGE */
    bool                    scanReqNotifiEnable;                    /**< Indicates whether the notifications shall be sent upon the receipt of a scan request PDU.
                                                                         Set true to enable notification. Set false to disable notification. */
} BLE_GAP_ExtAdvParams_T;


/**@brief Extended advertising parameters. */
typedef struct BLE_GAP_ExtAdvDataParams_T
{
    uint8_t                 advHandle;                              /**< Identifies the advertising set whose parameters are being configured
                                                                         (Range: 0 to 0xEF). See @ref BLE_GAP_MAX_ADV_HANDLE */
    uint8_t                 operation;                              /**< Set the advertising data in one or more operations. See @ref BLE_GAP_EXT_ADV_DATA_OPERAION
                                                                         BLE_GAP_EXT_ADV_DATA_OP_UNCHANGED can't be used in BLE_GAP_SetExtScanRspData*/
    uint8_t                 fragPreference;                         /**< Configure whether advertising data should be fragmented. See @ref BLE_GAP_EXT_ADV_DATA_FRAG_PREF */
    uint8_t                 advLen;                                 /**< Length of advertising data, valid value is 0 ~ 251. */
    uint8_t                 *p_advData;                             /**< Advertising data */
} BLE_GAP_ExtAdvDataParams_T;


/**@brief Extended advertising enable parameters.*/
typedef struct BLE_GAP_ExtAdvEnableParams_T
{
    uint8_t                 advHandle;                              /**< Identifies which advertising set to be enabled or disabled
                                                                         (Range: 0 to 0xEF). See @ref BLE_GAP_MAX_ADV_HANDLE */
    uint16_t                duration;                               /**< Indicate the duration for which that advertising set is enabled. Set 0x0000 to countinue advertising until user disables it. Unit: 10 ms. */
    uint8_t                 maxExtAdvEvts;                          /**< Indicate the maximum number of extended advertising events that shall be sent prior to disabling the extended advertising set even if the duration parameter has not expired. */
}BLE_GAP_ExtAdvEnableParams_T;

/**@brief Periodic advertising parameters. */
typedef struct BLE_GAP_PeriAdvParams_T
{
    uint8_t                 advHandle;                              /**< Identifies the advertising set whose periodic advertising parameters are being configured
                                                                        (Range: 0 to 0xEF). See @ref BLE_GAP_MAX_ADV_HANDLE */
    uint16_t                intervalMin;                            /**< Minimum advertising interval, see @ref BLE_GAP_PRIODIC_ADV_INTERVAL. Unit: 1.25ms */
    uint16_t                intervalMax;                            /**< Maximum advertising interval, see @ref BLE_GAP_PRIODIC_ADV_INTERVAL. Unit: 1.25ms */
    uint16_t                properties;                             /**< Indicate which fields should be included in the advertising packet. The bit combination of @ref BLE_GAP_PERIODIC_ADV_PROP*/
} BLE_GAP_PeriAdvParams_T;


/**@brief Periodic advertising data. */
typedef struct BLE_GAP_PeriAdvDataParams_T
{
    uint8_t                 advHandle;                              /**< Identifies the advertising set whose periodic advertising parameters are being configured
                                                                         (Range: 0 to 0xEF). See @ref BLE_GAP_MAX_ADV_HANDLE */
    uint8_t                 operation;                              /**< Set the advertising data in one or more operations. See @ref BLE_GAP_PERIODIC_ADV_DATA_OPERAION */
    uint8_t                 advLen;                                 /**< Length of advertising data, valid value is 0 ~ 252. See @ref BLE_GAP_PERI_ADV_DATA_LEN */
    uint8_t                 *p_advData;                             /**< Advertising data */
} BLE_GAP_PeriAdvDataParams_T;

/**@brief Device name characteristic. */
typedef struct BLE_GAP_CharDeviceName_T
{
    bool                    enableWriteProperty;                    /**< Set true to enable write property. */
} BLE_GAP_CharDeviceName_T;

/**@brief Appearance characteristic. */
typedef struct BLE_GAP_CharAppearance_T
{
    uint16_t                appearance;                             /**< The enumerated value as defined by Bluetooth Assigned Numbers document for Appearance characteristic. @ref GAP_APPEARANCE_DEF */
} BLE_GAP_CharAppearance_T;

/**@brief Peripheral prefered connection parameter characteristic. */
typedef struct BLE_GAP_CharPeriPreferConnParams_T
{
    bool                    enable;                                 /**< If ture to enable the characteristic of "Peripheral Preferred Connection Parameters". Otherwise, disable it. */
    uint16_t                minConnInterval;                        /**< Defines minimum value for the connection interval. See @ref BLE_GAP_CP_RANGE. */
    uint16_t                maxConnInterval;                        /**< Defines maximum value for the connection interval. See @ref BLE_GAP_CP_RANGE. */
    uint16_t                peripheralLatency;                      /**< Defines the peripheral latency for the connection. See @ref BLE_GAP_CP_RANGE. */
    uint16_t                connSupervisionTimeoutMulti;            /**< Defines the connection supervisor timeout multiplier as a multiple of 10ms. */
} BLE_GAP_CharPeriPreferConnParams_T;


/**@brief Build-in service option. */
typedef struct BLE_GAP_ServiceOption_T
{
    BLE_GAP_CharDeviceName_T                charDeviceName;             /**< Device name characteristic. */
    BLE_GAP_CharAppearance_T                charAppearance;             /**< Appearance characteristic. */
    BLE_GAP_CharPeriPreferConnParams_T      charPeriPreferConnParam;    /**< Peripheral preferred connection parameters characteristic. */
} BLE_GAP_ServiceOption_T;


/**@brief Extended scan parameters. */
typedef struct BLE_GAP_ExtScanningParams_T
{
    bool                    enable;                                 /**< Set to true if the following configuration is valid. */
    uint8_t                 type;                                   /**< Scanning type, see @ref BLE_GAP_SCAN_TYPE. */
    uint16_t                interval;                               /**< Scanning interval, see @ref BLE_GAP_EXT_SCAN_INTERVAL. (Unit: 0.625ms) */
    uint16_t                window;                                 /**< Scanning window, see @ref BLE_GAP_EXT_SCAN_WINDOW. (Unit: 0.625ms) */
    uint8_t                 disChannel;                             /**< Disable specific channel during scanning. See @ref BLE_GAP_SCAN_CHANNEL.*/
} BLE_GAP_ExtScanningParams_T;

/**@brief Extended scan phy setting. */
typedef struct BLE_GAP_ExtScanningPhy_T
{
    BLE_GAP_ExtScanningParams_T    le1mPhy;                         /**< Scan advertisements on the LE 1M PHY. */
    BLE_GAP_ExtScanningParams_T    leCodedPhy;                      /**< Scan advertisements on the LE Coded PHY. */
} BLE_GAP_ExtScanningPhy_T;

/**@brief Extended scan enable parameters. */
typedef struct BLE_GAP_ExtScanningEnable_T
{
    bool                    enable;                                 /**< Determines whether scanning is enabled or disabled */
    uint8_t                 filterDuplicates;                       /**< Controls whether the Link Layer should filter out duplicate advertising reports. See @ref BLE_GAP_SCAN_FD */
    uint16_t                duration;                               /**< Scan duration.(Unit: 10 ms) Set 0x0000 to scan continuously until explicitly disable. */
    uint16_t                period;                                 /**< Time interval from when BLE Stack started its last duration until it begins the subsequent duration. (Unit: 1.28 sec) Set 0x0000 to disable periodic scanning. */
} BLE_GAP_ExtScanningEnable_T;


/**@brief Create sync parameters. */
typedef struct BLE_GAP_CreateSync_T
{
    uint8_t                 options;                                /**< Determine whether the Periodic Advertiser List is used and whether the reporting are initially enabled or disabled. See @ref BLE_GAP_SYNC_CREATE_OPTION. */
    uint8_t                 advSid;                                 /**< Advertising SID. It used to identify the Periodic Advertising. See @ref BLE_GAP_ADV_SID_RANGE. */
    BLE_GAP_Addr_T          advAddr;                                /**< Public or random (static) identity address. */
    uint16_t                skip;                                   /**< The maximum number of periodic advertising events that can be skipped after a successful receive. (Valid value: 0x0000 to 0x01F3)
                                                                         See @ref BLE_GAP_SYNC_SKIP*/
    uint16_t                syncTimeout;                            /**< Synchronization timeout for the periodic advertising train. (Unit: 10 ms) See @ref BLE_GAP_SYNC_TIMEOUT. \n The timeout value should be greater than or equal to (2+skip)*(interval of period advertising). */
}BLE_GAP_CreateSync_T;


/**@brief Set sync device parameters. */
typedef struct BLE_GAP_SyncSetDev_T
{
    BLE_GAP_Addr_T          advAddr;                                /**< Advertiser address type. Public or random (static) identity address. */
    uint8_t                 advSid;                                 /**< Advertising SID. It used to identify the Periodic Advertising. See @ref BLE_GAP_ADV_SID_RANGE. */
}BLE_GAP_SyncSetDev_T;

/**@brief Manufacturer specific data filter parameters */
typedef struct
{
    uint8_t                 companyId[2];                           /**< Two bytes of Manufacture Company Identifier that is unique numbers assigned by the Bluetooth SIG to member companies. See detail in https://www.bluetooth.com/specifications/assigned-numbers/company-identifiers/. */
    uint8_t                 msdLen;                                 /**< Length of compared manufacture specific data. */
    uint8_t                 msd[BLE_GAP_SCAN_MSD_MAX_LEN];          /**< Contents of manufacture specific data. */
} BLE_GAP_ScanFilterMsd_T;

/**@brief Service data filter parameters */
typedef struct
{
    uint8_t                 uuidLen;                                /**< Byte length of Service UUID. There are 3 Service UUID format definition. The valid UUID length is 2, 4 or 16 for 16-bit, 32-bit or 128-bit Service UUID. */
    uint8_t                 uuidData[16];                           /**< Contents of Compared Service UUID. */
    uint8_t                 svcDataLen;                             /**< Length of compared Service Data. The max value is @ref BLE_GAP_SCAN_SERVICE_DATA_MAX_LEN. */
    uint8_t                 svcData[BLE_GAP_SCAN_SERVICE_DATA_MAX_LEN];   /**< Contents of Compared Service Data. */
} BLE_GAP_ScanFilterServiceData_T;

/**@brief Name filter parameters */
typedef struct
{
    uint8_t                 nameLen;                                /**< Length of compared target name. */
    uint8_t                 targetName[BLE_GAP_SCAN_NAME_MAX_LEN];  /**< Name contents for Name Filter comparison. */
} BLE_GAP_ScanFilterName_T;

/**@brief Scan filter parameters */
typedef struct
{
    uint8_t                         nameFilterEnable    : 1;        /**< Name filter option setting. Set true to enable name filter, otherwise set false. */
    uint8_t                         svcDataFilterEnable : 1;        /**< Service data filter option setting. Set true to enable service data filter, otherwise set false. */
    uint8_t                         msdFilterEnable     : 1;        /**< Manufacture specific data Filter option setting. Set true to enable manufacture specific filter, otherwise set false. */
    BLE_GAP_ScanFilterName_T        nameFilter;                     /**< Name filter. */
    BLE_GAP_ScanFilterServiceData_T serviceDataFilter;              /**< Service data filter. */
    BLE_GAP_ScanFilterMsd_T         msdFilter;                      /**< Manufacturer specific data filter. */
} BLE_GAP_ScanFilterConfig_T;

/**@brief Data structure for @ref BLE_GAP_EVT_DISCONNECTED event. */
typedef struct BLE_GAP_EvtDisconnect_T
{
    uint16_t                connHandle;                             /**< Connection handle associated with this connection. */
    uint8_t                 reason;                                 /**< The reason for disconnection. See @ref GAP_DISC_REASON. */
} BLE_GAP_EvtDisconnect_T;

/**@brief Data structure for @ref BLE_GAP_EVT_CONNECTED event. */
typedef struct BLE_GAP_EvtConnect_T
{
    uint8_t                 status;                                 /**< Status of this connection. */
    uint16_t                connHandle;                             /**< Connection handle associated with this connection. */
    uint8_t                 role;                                   /**< GAP role. See @ref BLE_GAP_ROLE. */
    BLE_GAP_Addr_T          remoteAddr;                             /**< Remote bluetooth address. See @ref BLE_GAP_Addr_T. */
    uint8_t                 localRpaAddr[GAP_MAX_BD_ADDRESS_LEN];   /**< Resolvable private address being used by the local device for this connection. 
                                                                         This is only valid if local privacy enable, otherwise all zeros. 
                                                                     */
    uint8_t                 remoteRpaAddr[GAP_MAX_BD_ADDRESS_LEN];    /**< Resolvable private address being used by the peer device for this connection.
                                                                         This is only valid if peer address is resolved by resolving list successfully,
                                                                         otherwise all zeros.
                                                                     */
    uint16_t                interval;                               /**< Connection interval used on this connection. Range should be @ref BLE_GAP_CP_RANGE. */
    uint16_t                latency;                                /**< Peripheral latency for the connection in terms of number of connection events, see @ref BLE_GAP_CP_RANGE. */
    uint16_t                supervisionTimeout;                     /**< Supervision timeout for the LE Link. See @ref BLE_GAP_CP_RANGE. */
} BLE_GAP_EvtConnect_T;

/**@brief Data structure for @ref BLE_GAP_EVT_CONN_PARAM_UPDATE event. */
typedef struct BLE_GAP_EvtConnParamUpdateParams_T
{
    uint16_t                connHandle;                             /**< Connection handle associated with this connection. */
    uint8_t                 status;                                 /**< Status of connection parameter update. 0: Connection parameters update is successful. Others: Update failed. */
    BLE_GAP_ConnParams_T    connParam;                              /**< Connection parameters. See @ref BLE_GAP_ConnParams_T. */
} BLE_GAP_EvtConnParamUpdateParams_T;


/**@brief Data structure for @ref BLE_GAP_EVT_ENCRYPT_STATUS event. */
typedef struct BLE_GAP_EvtEncryptStatus_T
{
    uint16_t                connHandle;                             /**< Connection handle associated with this connection. */
    uint8_t                 status;                                 /**< Encryption status. See @ref BLE_GAP_ENCRYPT_STATUS for possible values */
} BLE_GAP_EvtEncryptStatus_T;


/**@brief Data structure for @ref BLE_GAP_EVT_ADV_REPORT event. */
typedef struct BLE_GAP_EvtAdvReport_T
{
    uint8_t                 eventType;                              /**< Event type. See @ref BLE_GAP_ADV_REPORT_EVT_TYPE. */
    BLE_GAP_Addr_T          addr;                                   /**< Address type. See @ref BLE_GAP_ADDR_TYPE. */
    uint8_t                 length;                                 /**< Length of advertising data. */
    uint8_t                 advData[BLE_GAP_ADV_MAX_LENGTH];        /**< Advertising data. */
    int8_t                  rssi;                                   /**< RSSI value. */
} BLE_GAP_EvtAdvReport_T;


/**@brief Data structure for @ref BLE_GAP_EVT_ENC_INFO_REQUEST event. */
typedef struct BLE_GAP_EvtEncInfoRequest_T
{
    uint16_t                connHandle;                             /**< Connection handle associated with this connection. */
} BLE_GAP_EvtEncInfoRequest_T;

/**@brief Data structure for @ref BLE_GAP_EVT_REMOTE_CONN_PARAM_REQUEST event. */
typedef struct BLE_GAP_EvtRemoteConnParamRequest_T
{
    uint16_t                connHandle;                             /**< Connection handle associated with this connection. */
    uint16_t                intervalMin;                            /**< Minimum value of the connection interval requested by the remote device. */
    uint16_t                intervalMax;                            /**< Maximum value of the connection interval requested by the remote device. */
    uint16_t                latency;                                /**< Latency. */
    uint16_t                timeout;                                /**< Supervision timeout. */
} BLE_GAP_EvtRemoteConnParamRequest_T;


/**@brief Data structure for @ref BLE_GAP_EVT_ADV_REPORT event. */
typedef struct BLE_GAP_EvtExtAdvReport_T
{
    uint8_t                 eventType;                              /**< Event type. See @ref BLE_GAP_EXT_ADV_REPORT_EVT_TYPE. */
    uint8_t                 dataStatus;                             /**< Data status. See @ref BLE_GAP_EXT_ADV_REPORT_DATA_STATUS */
    BLE_GAP_Addr_T          addr;                                   /**< Address type. See @ref BLE_GAP_ADDR_TYPE.  */
    uint8_t                 priPhy;                                 /**< Primary PHY. See @ref BLE_GAP_EXT_ADV_REPORT_PHY */
    uint8_t                 secPhy;                                 /**< Secondary PHY. See @ref BLE_GAP_EXT_ADV_REPORT_PHY */
    uint8_t                 sid;                                    /**< Advertising SID. 0x00 ~ 0x0F: Value of the Advertising SID subfield in the ADI field of the PDU. 0xFF: No ADI field in the PDU*/
    int8_t                  txPower;                                /**< Tx power. unit: dBm */
    int8_t                  rssi;                                   /**< RSSI value. */
    uint16_t                periodAdvInterval;                      /**< Interval of the periodic advertising. Unit: 1.25 ms */
    BLE_GAP_Addr_T          directAddr;                             /**< Directed address type. See @ref BLE_GAP_ADDR_TYPE. */
    uint8_t                 length;                                 /**< Length of advertising data. */
    uint8_t                 advData[BLE_GAP_EXT_ADV_FRAGMENT_MAX_LENGTH];   /**< Fragmented advertising data. */
} BLE_GAP_EvtExtAdvReport_T;

/**@brief Data structure for @ref BLE_GAP_EVT_TX_BUF_AVAILABLE event.*/
typedef struct BLE_GAP_EvtTxBufAvailable_T
{
    uint16_t                connHandle;                             /**< Connection handle associated with this connection. */
} BLE_GAP_EvtTxBufAvailable_T;

/**@brief Data structure for @ref BLE_GAP_EVT_DEVICE_NAME_CHANGED event.*/
typedef struct BLE_GAP_EvtDeviceNameChanged_T
{
    uint8_t                 length;                                 /**< The length of device name. */
    uint8_t                 devName[GAP_MAX_DEVICE_NAME_LEN];       /**< Device Name. */
} BLE_GAP_EvtDeviceNameChanged_T;

/**@brief Data structure for @ref BLE_GAP_EVT_AUTH_PAYLOAD_TIMEOUT event.*/
typedef struct BLE_GAP_EvtAuthPayloadTimeout_T
{
    uint16_t                connHandle;                             /**< Connection handle associated with this connection. */
} BLE_GAP_EvtAuthPayloadTimeout_T;

/**@brief Data structure for @ref BLE_GAP_EVT_PHY_UPDATE event.*/
typedef struct BLE_GAP_EvtPhyUpdate_T
{
    uint16_t                connHandle;                             /**< Connection handle associated with this connection. */
    uint8_t                 status;                                 /**< Status of phy update. */
    uint8_t                 txPhy;                                  /**< TX PHY. See @ref BLE_GAP_PHY_TYPE. */
    uint8_t                 rxPhy;                                  /**< RX PHY. See @ref BLE_GAP_PHY_TYPE. */
}BLE_GAP_EvtPhyUpdate_T;

/**@brief Data structure for @ref BLE_GAP_EVT_SCAN_REQ_RECEIVED event.*/
typedef struct BLE_GAP_EvtScanReqReceived_T
{
    uint8_t                 advHandle;                              /**< Advertising handle. */
    BLE_GAP_Addr_T          scannerAddr;                            /**< Scanner address. */
}BLE_GAP_EvtScanReqReceived_T;


/**@brief Data structure for @ref BLE_GAP_EVT_DIRECT_ADV_REPORT event.*/
typedef struct BLE_GAP_EvtDirectAdvReport_T
{
    uint8_t                 numReports;                             /**< Number of advertising reports. */
    uint8_t                 eventType;                              /**< Even type. See @ref BLE_GAP_ADV_REPORT_EVT_TYPE. It should be BLE_GAP_ADV_REPORT_EVT_TYPE_ADV_DIRECT_IND. */
    BLE_GAP_Addr_T          addr;                                   /**< Identity Address of the advertising device. */
    BLE_GAP_Addr_T          directAddr;                             /**< Random Device Address. */
    int8_t                  rssi;                                   /**< RSSI. */
}BLE_GAP_EvtDirectAdvReport_T;


/**@brief Data structure for @ref BLE_GAP_EVT_PERI_ADV_SYNC_EST event.*/
typedef struct BLE_GAP_EvtPeriAdvSyncEst_T
{
    uint8_t                 status;                                 /**< Status. */
    uint16_t                syncHandle;                             /**< Sync handle. */
    uint8_t                 advSid;                                 /**< Advertising SID. */
    BLE_GAP_Addr_T          advAddr;                                /**< Advertising address. */
    uint8_t                 advPhy;                                 /**< Advertising PHY. See @ref BLE_GAP_PHY_TYPE. */
    uint16_t                periAdvInterval;                        /**< Periodic advertising interval.(Unit: 1.25ms) */
    uint8_t                 advClkAccuracy;                         /**< Advertiser clock accuracy. See @ref BLE_GAP_PERIODIC_ACA */
}BLE_GAP_EvtPeriAdvSyncEst_T;

/**@brief Data structure for @ref BLE_GAP_EVT_PERI_ADV_REPORT event.*/
typedef struct BLE_GAP_EvtPeriAdvReport_T
{
    uint16_t                syncHandle;                             /**< Sync handle. */
    uint8_t                 txPwr;                                  /**< Tx power. (Unit: dBm) */
    int8_t                  rssi;                                   /**< RSSI. (Unit: dBm) */
    uint8_t                 cteType;                                /**< CTE type. See @ref BLE_GAP_CTE_TYPE. */
    uint8_t                 dataStatus;                             /**< Data status. See @ref BLE_GAP_DATA_STATUS. */
    uint8_t                 dataLength;                             /**< Data length */
    uint8_t                 advData[BLE_GAP_PERIODIC_ADV_FRAGMENT_MAX_LENGTH];    /**< Advertising data. */
}BLE_GAP_EvtPeriAdvReport_T;

/**@brief Data structure for @ref BLE_GAP_EVT_PERI_ADV_SYNC_LOST event.*/
typedef struct BLE_GAP_EvtPeriAdvSyncLost_T
{
    uint16_t                syncHandle;                             /**< Sync handle. */
}BLE_GAP_EvtPeriAdvSyncLost_T;


/**@brief Data structure for @ref BLE_GAP_EVT_ADV_SET_TERMINATED event.*/
typedef struct BLE_GAP_EvtAdvSetTerminated_T
{
    uint8_t                 status;                                 /**< Status of adv set terminated. See @ref GAP_STATUS */
    uint8_t                 advHandle;                              /**< Advertising handle in which advertising has ended. */
    uint16_t                connHandle;                             /**< Connection handle of the connection whose creation ended the advertising. */
    uint8_t                 numComplExtAdvEvents;                   /**< Number of completed extended advertising events transmitted. */
}BLE_GAP_EvtAdvSetTerminated_T;

/**@brief Data structure for @ref BLE_GAP_EVT_TRANSMIT_POWER_REPORTING event.*/
typedef struct BLE_GAP_EvtTxPowerReporting_T
{
    uint8_t                 status;                                 /**< Status of tx power reporting. See @ref GAP_STATUS */
    uint16_t                connHandle;                             /**< Connection handle of the connection whose creation ended the advertising. */
    uint8_t                 reason;                                 /**< The reason for changed, see @ref BLE_GAP_TX_POWER_REPORTING_REASON. */
    uint8_t                 phy;                                    /**< PHY type. See @ref BLE_GAP_TRANSMITTER_PHY_TYPE. */
    int8_t                  txPowerLevel;                           /**< Indicate the transmit power level for the PHY. */
    uint8_t                 txPowerLevelFlag;                       /**< Indicate if transmit power level reach its min/max level. */
    int8_t                  delta;                                  /**< Change in power level for transmitter being reported. */
}BLE_GAP_EvtTxPowerReporting_T;

/**@brief Data structure for @ref BLE_GAP_EVT_ADV_COMPL event.*/
typedef struct BLE_GAP_EvtAdvCompl_T
{
    uint8_t                 status;                                 /**< Status of Deep Sleep Advertising. See @ref GAP_STATUS */
}BLE_GAP_EvtAdvCompl_T;


/**@brief Union of BLE GAP callback event data types. */
typedef union
{
    BLE_GAP_EvtConnect_T                   evtConnect;              /**< Handle @ref BLE_GAP_EVT_CONNECTED */
    BLE_GAP_EvtDisconnect_T                evtDisconnect;           /**< Handle @ref BLE_GAP_EVT_DISCONNECTED */
    BLE_GAP_EvtConnParamUpdateParams_T     evtConnParamUpdate;      /**< Handle @ref BLE_GAP_EVT_CONN_PARAM_UPDATE */
    BLE_GAP_EvtEncryptStatus_T             evtEncryptStatus;        /**< Handle @ref BLE_GAP_EVT_ENCRYPT_STATUS */
    BLE_GAP_EvtAdvReport_T                 evtAdvReport;            /**< Handle @ref BLE_GAP_EVT_ADV_REPORT */
    BLE_GAP_EvtEncInfoRequest_T            evtEncInfoReq;           /**< Handle @ref BLE_GAP_EVT_ENC_INFO_REQUEST.*/
    BLE_GAP_EvtRemoteConnParamRequest_T    evtRemoteConnParamReq;   /**< Handle @ref BLE_GAP_EVT_REMOTE_CONN_PARAM_REQUEST.*/
    BLE_GAP_EvtExtAdvReport_T              evtExtAdvReport;         /**< Handle @ref BLE_GAP_EVT_EXT_ADV_REPORT */
    BLE_GAP_EvtTxBufAvailable_T            evtTxBufAvailable;       /**< Handle @ref BLE_GAP_EVT_TX_BUF_AVAILABLE. */
    BLE_GAP_EvtDeviceNameChanged_T         evtDevNameChanged;       /**< Handle @ref BLE_GAP_EVT_DEVICE_NAME_CHANGED */
    BLE_GAP_EvtAuthPayloadTimeout_T        evtAuthPayloadTimeout;   /**< Handle @ref BLE_GAP_EVT_AUTH_PAYLOAD_TIMEOUT */
    BLE_GAP_EvtPhyUpdate_T                 evtPhyUpdate;            /**< Handle @ref BLE_GAP_EVT_PHY_UPDATE */
    BLE_GAP_EvtScanReqReceived_T           evtScanReqReceived;      /**< Handle @ref BLE_GAP_EVT_SCAN_REQ_RECEIVED */
    BLE_GAP_EvtDirectAdvReport_T           evtDirectAdvReport;      /**< Handle @ref BLE_GAP_EVT_DIRECT_ADV_REPORT */
    BLE_GAP_EvtPeriAdvSyncEst_T            evtPeriAdvSyncEst;       /**< Handle @ref BLE_GAP_EVT_PERI_ADV_SYNC_EST */
    BLE_GAP_EvtPeriAdvReport_T             evtPeriAdvReport;        /**< Handle @ref BLE_GAP_EVT_PERI_ADV_REPORT */
    BLE_GAP_EvtPeriAdvSyncLost_T           evtPeriAdvSyncLost;      /**< Handle @ref BLE_GAP_EVT_PERI_ADV_SYNC_LOST */
    BLE_GAP_EvtAdvSetTerminated_T          evtAdvSetTerminated;     /**< Handle @ref BLE_GAP_EVT_ADV_SET_TERMINATED */
    BLE_GAP_EvtTxPowerReporting_T          evtTxPowerReporting;     /**< Handle @ref BLE_GAP_EVT_TRANSMIT_POWER_REPORTING */
    BLE_GAP_EvtAdvCompl_T                  evtAdvCompl;             /**< Handle @ref BLE_GAP_EVT_ADV_COMPL */
} BLE_GAP_EventField_T;

/**@brief BLE GAP callback event.*/
typedef struct  BLE_GAP_Event_T
{
    BLE_GAP_EventId_T       eventId;                                /**< Event ID. */
    BLE_GAP_EventField_T    eventField;                             /**< Event field */
} BLE_GAP_Event_T;

/**@} */ //BLE_GAP_STRUCTS

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************
/**@addtogroup BLE_GAP_FUNS Functions
 * @{ */
 
/**@brief Initialize BLE GAP main module.
 *
 * @retval MBA_RES_SUCCESS                  Successfully initialize BLE GAP main module.
 * @retval MBA_RES_FAIL                     Fail to initialize BLE GAP main module.
 */
uint16_t BLE_GAP_Init();


/**@brief Initialize BLE GAP legacy advertising module.
 *
 * @retval MBA_RES_SUCCESS                  Successfully initialize BLE GAP Advertising module.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 */
uint16_t BLE_GAP_AdvInit();


/**@brief Initialize BLE GAP legacy scan module.
 *
 * @retval MBA_RES_SUCCESS                  Successfully initialize BLE GAP scan module.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 */
uint16_t BLE_GAP_ScanInit();


/**@brief Initialize BLE GAP extended advertising module.
 * @note  @ref BLE_GAP_AdvInit is also required for this module enabling.
 *
 * @retval MBA_RES_SUCCESS                  Successfully initialize BLE GAP extended advertising module.
 */
uint16_t BLE_GAP_ExtAdvInit();


/**@brief Initialize BLE GAP periodic advertising module.
 * @note  Periodic advertising belongs to extended advertising feature.\n
 *        @ref BLE_GAP_AdvInit and @ref BLE_GAP_ExtAdvInit are also required for this module enabling.
 *
 * @retval MBA_RES_SUCCESS                  Successfully initialize BLE GAP periodic advertising module.
 */
uint16_t BLE_GAP_PeriodicAdvInit();


/**@brief Initialize BLE GAP extended scanning module.
 * @note  @ref BLE_GAP_ScanInit is also required for this module enabling.
 *
 * @param[in] maxDataLen                    This is the maximum pdu payload size that the scan is able to receive. See @ref BLE_GAP_EXT_SCAN_DATA_LEN.
 * @param[in] maxNumOfSecPkts               This is the maximum advertising packets on the secondary channel that the scan is able to receive. See @ref BLE_GAP_EXT_SCAN_2ND_ADV_NUM.
 *                                          If value 0 is used, The maximum number would be adjusted automatically.
 *
 * @retval MBA_RES_SUCCESS                  Successfully initialize BLE GAP extended scanning module.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 */
uint16_t BLE_GAP_ExtScanInit(uint16_t maxDataLen, uint8_t maxNumOfSecPkts);


/**@brief Initialize BLE GAP connection peripheral module.
 *
 * @retval MBA_RES_SUCCESS                  Successfully initialize BLE GAP connection peripheral module.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 */
uint16_t BLE_GAP_ConnPeripheralInit();


/**@brief Initialize BLE GAP connection central module.
 *
 * @retval MBA_RES_SUCCESS                  Successfully initialize BLE GAP connection central module.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 */
uint16_t BLE_GAP_ConnCentralInit();


/**@brief Initialize BLE GAP extended connection central module.
 * @note  @ref BLE_GAP_ConnCentralInit is also required for this module enabling.
 *
 * @retval MBA_RES_SUCCESS                  Successfully initialize BLE GAP extended connection central module.
 */
uint16_t BLE_GAP_ExtConnCentralInit();


/**@brief Initialize BLE GAP sync module. The sync is refer to periodic advertising synchronization.
 * @note  Sync belongs to extended advertising feature.
 *
 * @retval MBA_RES_SUCCESS                  Successfully initialize BLE GAP sync module.
 */
uint16_t BLE_GAP_SyncInit();


/**@brief Set the Bluetooth device address (identity address). Type of address must be @ref BLE_GAP_ADDR_TYPE_PUBLIC or @ref BLE_GAP_ADDR_TYPE_RANDOM_STATIC.
 *        The address identifies the device to other Bluetooth devices.
 *
 * @param[in] p_addr                        Pointer to the device address buffer.
 *
 * @retval MBA_RES_SUCCESS                  Successfully set the device address.
 * @retval MBA_RES_FAIL                     Fail to set device addr. Some types of address can be set by application.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 */
uint16_t BLE_GAP_SetDeviceAddr(BLE_GAP_Addr_T *p_addr);


/**@brief Get the device address.
 *
 * @param[out] p_addr                       Pointer to the device address buffer.
 *
 * @retval MBA_RES_SUCCESS                  Successfully get the device address.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 */
uint16_t BLE_GAP_GetDeviceAddr(BLE_GAP_Addr_T *p_addr);


/**@brief Set the local device name.
 *
 * @param[in] len                           Length of the device name. See @ref GAP_MAX_DEVICE_NAME_LEN.
 * @param[in] p_deviceName                  Pointer to a device name buffer (UTF-8 string).
 *
 * @retval MBA_RES_SUCCESS                  Successfully set the local device name.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters, if length of the device name is more than 32 bytes.
 */
uint16_t BLE_GAP_SetDeviceName(uint8_t len, uint8_t *p_deviceName);


/**@brief Get local device name with the length information.
 *
 * @param[out] p_len                        Pointer to length of device name buffer.
 * @param[out] p_deviceName                 Pointer to device name buffer.
 *
 * @retval MBA_RES_SUCCESS                  Successfully get the local device name.
 */
uint16_t BLE_GAP_GetDeviceName(uint8_t *p_len, uint8_t *p_deviceName);


/**@brief Set advertising data from the input "p_advData".
 * @note  If advertising is currently enabled, the new data shall be used in
 *        subsequent advertising events. If an advertising event is in progress 
 *        when this command is issued, the new data may not be used for that event.\n
 *        This API belongs to legacy advertising feature. It will be disallowed if any one API belongs extended advertising feature is issued before. @ref BLE_GAP_ADV_CATS for details of advertising APIs.\n
 *        @ref BLE_GAP_AdvInit is required for this API.
 *
 * @param[in] p_advData                     Pointer to the structure containing advertising data to be set.
 *
 * @retval MBA_RES_SUCCESS                  Successfully set advertising data.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters, advertisement data length is more than @ref BLE_GAP_ADV_DATA_LEN.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed when extended Adv. feature is in-use.
 */
uint16_t BLE_GAP_SetAdvData(BLE_GAP_AdvDataParams_T *p_advData);


/**@brief Set scan response data.
 * @note  If advertising is currently enabled, the new data shall be used in
 *        subsequent advertising events. If an advertising event is in progress 
 *        when this command is issued, the new data may not be used for that event.\n
 *        This API belongs to legacy advertising feature. It will be disallowed if any one API belongs extended advertising feature is issued before. @ref BLE_GAP_ADV_CATS for details of advertising APIs.\n
 *        @ref BLE_GAP_AdvInit is required for this API.
 *
 * @param[in] p_scanData                    Pointer to the structure containing scan response data to be set. See @ref BLE_GAP_AdvDataParams_T.
 *
 * @retval MBA_RES_SUCCESS                  Successfully set scan response data.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters, scan response data length is more than @ref BLE_GAP_ADV_DATA_LEN.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed when extended Adv. feature is in-use.
 */
uint16_t BLE_GAP_SetScanRspData(BLE_GAP_AdvDataParams_T *p_scanData);


/**@brief Set advertising parameters.
 * @note  This command shall not be issued when advertising is enabled.\n
 *        This API belongs to legacy advertising feature. It will be disallowed if any one API belongs extended advertising feature is issued before. @ref BLE_GAP_ADV_CATS for details of advertising APIs.\n
 *        @ref BLE_GAP_AdvInit is required for this API.
 *
 * @param[in] p_advParams                   Pointer to advertising parameters buffer. See @ref BLE_GAP_AdvParams_T.
 *
 * @retval MBA_RES_SUCCESS                  Successfully set advertising parameters.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 */
uint16_t BLE_GAP_SetAdvParams(BLE_GAP_AdvParams_T *p_advParams);


/**@brief Start or stop advertising.
 * @note  The duration is only valid when advertising type is not set to Directed Advertising.
 *        The advertising shall be continuous within the duration or until the disable command is issued
 *        or until a connection is created or until the Advertising is timed out due to high duty cycle Directed Advertising.
 *        In these cases, advertising is then disabled.\n
 *        This API belongs to legacy advertising feature. It will be disallowed if any one API belongs extended advertising feature is issued before. @ref BLE_GAP_ADV_CATS for details of advertising APIs.\n
 *        @ref BLE_GAP_AdvInit is required for this API.\n\n
 *
 *        @ref BLE_GAP_SetAdvParams API should be called before this API to set appropriate
 *        advertising parameters.\n
 *        @ref BLE_GAP_SetAdvData or BLE_GAP_SetScanRspData API should be called before this API to set appropriate
 *        advertising/scan response data.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_CONNECTED Generated when connection established. \n
 * @ref BLE_GAP_EVT_ADV_TIMEOUT Generated when adv. enabled and timeout (by duration).
 *
 * @param[in] enable                        Advertising control option.
 * @param[in] duration                      Duration for advertising. (Unit: 10 ms) Set to 0 to continuously advertise.
 *
 * @retval MBA_RES_SUCCESS                  Successfully start or stop advertising.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed when extended Adv. feature is in-use.
 */
uint16_t BLE_GAP_SetAdvEnable(bool enable, uint16_t duration);


/**@brief Start one time advertising event.
 * @note  This API belongs to legacy advertising feature. It will be disallowed if any one API belongs extended advertising feature is issued before. @ref BLE_GAP_ADV_CATS for details of advertising APIs.\n
 *        @ref BLE_GAP_AdvInit is required for this API.\n\n
 *
 *        If option is set to BLE_GAP_ADV_OPTION_STORE_PARAMS, @ref BLE_GAP_SetAdvParams, @ref BLE_GAP_SetAdvData or BLE_GAP_SetScanRspData API should be called before this API to set appropriate parameters.\n
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_ADV_COMPL Generated when one time advertising event is completed.
 * When connection is established, @ref BLE_GAP_EVT_CONNECTED will be generated instead @ref BLE_GAP_EVT_ADV_COMPL event.
 *
 * @param[in] option                        Option for one time advertising. See @ref BLE_GAP_ADV_OPTION.
 *
 * @retval MBA_RES_SUCCESS                  Successfully start advertising.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed when extended Adv. feature is in-use.
 */
uint16_t BLE_GAP_EnableOneTimeAdv(uint8_t option);


/**@brief Unlock BLE data traffic.
 * @note BLE_stack will lock BLE data traffic while @ref BLE_GAP_EnableOneTimeAdv is called and connection established automatically.\n
 *       Application should call BLE_GAP_TrafficUnlock to unlock BLE data traffic after all of necessary BLE modules are initialized.
 *
 * @retval MBA_RES_SUCCESS                  Successfully unlock BLE data traffic.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 */
uint16_t BLE_GAP_TrafficUnlock();


/**@brief Terminate an existing connection.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_DISCONNECTED Generated when disconnected.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] reason                        Disconnection reason. See @ref GAP_STATUS
 *
 * @retval MBA_RES_SUCCESS                  Successfully issue a disconnection.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid connection handle.
 */
uint16_t BLE_GAP_Disconnect(uint16_t connHandle, uint8_t reason);


/**@brief Update connection parameters of an existing connection.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_CONN_PARAM_UPDATE Generated when connection parameters update complete.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] p_connParams                  Pointer to the @ref BLE_GAP_ConnParams_T structure buffer.
 *
 * @retval MBA_RES_SUCCESS                  Successfully update the connection parameters.
 * @retval MBA_RES_FAIL                     Connection update is in progress.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters, if any of the connection update parameters are out of range.
 *                                          See @ref BLE_GAP_CP_RANGE for range).
 *                                          (OR) Connection with the specified handle does not exist.
 * @retval MBA_RES_UNSUPPORT_REMOTE_FEATURE Unsupported remote feature.
 */
uint16_t BLE_GAP_UpdateConnParam(uint16_t connHandle, BLE_GAP_ConnParams_T *p_connParams);


/**@brief Get the absolute Received Signal Strength Indication (RSSI) value. (Units: dBm)
 * @note  The meaning of the RSSI metric is an absolute receiver signal strength value in dBm.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[out] p_rssi                       Pointer to the buffer to store RSSI value.
 *
 * @retval MBA_RES_SUCCESS                  Successfully get RSSI value.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Connection with the specified handle does not exist.
 */
uint16_t BLE_GAP_GetRssi(uint16_t connHandle, int8_t *p_rssi);


/**@brief Add devices to the filter accept list.
 * @note This API is not permitted in the following three scenarios:
 *       - The advertising filter policy uses the filter accept list and advertising is enabled.
 *       - The scanning filter policy uses the filter accept list and scanning is enabled.
 *       - The initiator filter policy uses the filter accept list and a create connection command is outstanding.
 *
 * @param[in] num                           Number of address set. See @ref BLE_GAP_MAX_FILTER_ACCEPT_LIST_NUM
 * @param[in] p_addr                        Pointer to @ref BLE_GAP_Addr_T structure buffer.
 *
 * @retval MBA_RES_SUCCESS                  Successfully add the device to the filter accept list
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters, if address type does not match any of the @ref BLE_GAP_ADDR_TYPE.
 */
uint16_t BLE_GAP_SetFilterAcceptList(uint8_t num, BLE_GAP_Addr_T *p_addr);


/**@brief Set devices to the resolving list
 * @note This API is not permitted in the following three scenarios:
 *      - Advertising is enabled
 *      - Scanning is enabled
 *      - @ref BLE_GAP_CreateConnection, @ref BLE_GAP_ExtCreateConnection or @ref BLE_GAP_CreateSync API is outstanding.
 *
 * @param[in] num                           The number of the resolving list included. See @ref BLE_GAP_MAX_RESOLV_NUM.
 * @param[in] p_resolvingList               Pointer to @ref BLE_GAP_ResolvingListParams_T structure buffer.
 *
 * @retval MBA_RES_SUCCESS                  Successfully add the device to the resolving list
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             When number exceeds @ref BLE_GAP_MAX_RESOLV_NUM.
 * @retval MBA_RES_BAD_STATE                Resolving list cannot be configured while advertising, scanning or creating a connection.
 */
uint16_t BLE_GAP_SetResolvingList(uint8_t num, BLE_GAP_ResolvingListParams_T *p_resolvingList);


/**@brief Get the current local privacy mode setting parameters.
 *
 * @param[out] p_enable                     True if local privacy is enabled, otherwise false.
 * @param[out] p_privacyParams              Pointer to @ref BLE_GAP_LocalPrivacyParams_T structure buffer to store current privacy parameters.
 *
 * @retval MBA_RES_SUCCESS                  Successfully get privacy parameters
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 */
uint16_t BLE_GAP_GetLocalPrivacy(bool * p_enable, BLE_GAP_LocalPrivacyParams_T *p_privacyParams);


/**@brief Configure the privacy parameters
 *
 * @note Local Privacy settings cannot be changed while advertising, scanning or creating connection.
 *
 * @param[in] enable                        True to enable local privacy, false to disable local privacy.
 * @param[in] p_privacyParams               Pointer to @ref BLE_GAP_LocalPrivacyParams_T structure buffer.
 *                                          If enable local privacy, the configurations must be legal.
 *                                          If disable local privacy, this parameter can be NULL or not.
 *
 * @retval MBA_RES_SUCCESS                  Successfully configure privacy parameters
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 * @retval MBA_RES_BAD_STATE                Privacy parameters cannot be configured while advertising, scanning or creating a connection.
 */
uint16_t BLE_GAP_SetLocalPrivacy(bool enable, BLE_GAP_LocalPrivacyParams_T *p_privacyParams);


/**@brief Set the Scanning Parameters.
 * @note  This API should not be called when scanning is enabled.\n
 *        This API belongs to legacy advertising feature. It will be disallowed if any one API belongs extended advertising feature is issued before. @ref BLE_GAP_ADV_CATS for details of advertising APIs.\n
 *        @ref BLE_GAP_ScanInit is required for this API.
 *
 * @param[in] p_scanParams                  Pointer to @ref BLE_GAP_ScanningParams_T structure buffer.
 *
 * @retval MBA_RES_SUCCESS                  Successfully set scanning parameters.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters, if any of the scanning parameters are out of range.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed when extended Adv. feature is in-use.
 */
uint16_t BLE_GAP_SetScanningParam(BLE_GAP_ScanningParams_T *p_scanParams);


/**@brief Start or stop scanning.
 * @note  Scanning is used to discover advertising devices nearby.
 *        If the enable parameter is set to true and scanning is already enabled,
 *        any change to the filterDuplicate setting shall take effect.\n
 *        This API belongs to legacy advertising feature. It will be disallowed if any one API belongs extended advertising feature is issued before. @ref BLE_GAP_ADV_CATS for details of advertising APIs.\n
 *        @ref BLE_GAP_ScanInit is required for this API.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_ADV_REPORT Generated when scan enabled. \n
 * @ref BLE_GAP_EVT_DIRECT_ADV_REPORT Generated when scan enabled and direct adv. received. \n
 * @ref BLE_GAP_EVT_SCAN_TIMEOUT Generated when scan enabled and timeout (by duration).
 *
 * @param[in] enable                        Start or stop scanning. Set true to start scanning.
 * @param[in] filterDuplicate               Duplicate Filter policy, see @ref BLE_GAP_SCAN_FD.
 *                                          Only BLE_GAP_SCAN_FD_DISABLE /BLE_GAP_SCAN_FD_ENABLE are valid
 * @param[in] mode                          Scan mode. See @ref BLE_GAP_SCAN_MODES.
 * @param[in] duration                      Scan duration (unit :100 ms)
 *
 *
 * @retval MBA_RES_SUCCESS                  Successfully enable or disable scanning.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters, if any of the parameters are out of range.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed when extended Adv. feature is in-use.
 */
uint16_t BLE_GAP_SetScanningEnable(bool enable, uint8_t filterDuplicate, uint8_t mode, uint16_t duration);


/**@brief Create a BLE connection to a connectable advertiser.\n
 * @note  This API belongs to legacy advertising feature. It will be disallowed if any one API belongs extended advertising feature is issued before. @ref BLE_GAP_ADV_CATS for details of advertising APIs.\n
 *        @ref BLE_GAP_ConnCentralInit is required for this API.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_CONNECTED Generated when connection established.
 *
 * @param[in] p_createConnParam             Pointer to connection parameters. See @ref BLE_GAP_CreateConnParams_T.
 *
 * @retval MBA_RES_SUCCESS                  Successfully created a BLE link with specified device.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters,if any of the create connection parameters are out of range. See @ref BLE_GAP_CreateConnParams_T for ranges.
 * @retval MBA_RES_NO_RESOURCE              Exceed maximum connections.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 */
uint16_t BLE_GAP_CreateConnection(BLE_GAP_CreateConnParams_T *p_createConnParam);


/**@brief Cancel the current connecting procedure before successful connection establishment.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_CONNECTED Generated with corresponding status code.
 *
 * @retval MBA_RES_SUCCESS                  Successfully cancel the current connecting procedure.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 */
uint16_t BLE_GAP_CreateConnectionCancel();


/**@brief Create a BLE connection to a connectable advertiser.
 * @note  This API belongs to extended advertising feature. It will be disallowed if any one API belongs legacy advertising feature is issued before. @ref BLE_GAP_ADV_CATS for details of advertising APIs.\n
 *        @ref BLE_GAP_ConnCentralInit and @ref BLE_GAP_ExtConnCentralInit are required for this API.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_CONNECTED Generated when connection established.
 *
 * @param[in] filterPolicy                  This parameter is used to determine whether the filter accept List is used. See @ref BLE_GAP_INIT_FP .
 * @param[in] p_peerAddr                    Pointer to the @ref BLE_GAP_Addr_T structure buffer. Remote bluetooth address and address type
 * @param[in] p_createConnPhy               Pointer to the @ref BLE_GAP_ExtCreateConnPhy_T structure buffer.
 *
 * @retval MBA_RES_SUCCESS                  Successfully issue the create connection.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 */
uint16_t BLE_GAP_ExtCreateConnection(uint8_t filterPolicy, BLE_GAP_Addr_T *p_peerAddr, BLE_GAP_ExtCreateConnPhy_T *p_createConnPhy);


/**@brief Set local channel map. If this API is not called then by default status of all 37 channels is treated unknown.
 * @note  If this API is used, the application should send it within 10 seconds of knowing that the channel
 *        classification has changed. The interval between two successive API calls should be at least one second.\n
 *        BLE Stack uses this channel map as an input along with its own assessment of the channels.
 *        This API is effective only for BLE Central role.
 *
 * @param[in] p_map                         5-byte channel map array containing 37 1-bit fields corresponding to 37 data channels.\n
 *                                          0 indicates corresponding channel is bad and 1 indicates channel status is unknown. \n
 *                                          The most significant bits are reserved and shall be set to 0.
 *
 * @retval MBA_RES_SUCCESS                  Successfully Set the channel map.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters, if any of the bits Corresponding to advertising channels are set
 *                                          (3 Most significant bits of p_map[4]).
 */
uint16_t BLE_GAP_SetChannelMap(uint8_t *p_map);


/**@brief  Get the channel map for the specific connection.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[out] p_map                        5-byte channel map array containing 37 1-bit fields corresponding to 37 data channels.\n
 *                                          0 indicates corresponding channel is bad and 1 indicates channel status is unknown. \n
 *                                          The most significant bits are reserved and shall be set to 0.
 *
 *
 * @retval MBA_RES_SUCCESS                  Successfully read the channel map.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_UNKNOWN_CONN_ID          Unknown connection identifier.
 */
uint16_t BLE_GAP_ReadChannelMap(uint16_t connHandle, uint8_t *p_map);


/**@brief Reply to an LE encrypt information request event if local device cannot provide the information. \n
 *        This API is called to reply @ref BLE_GAP_EVT_ENC_INFO_REQUEST event.
 * @note  This API shall be called only if device is peripheral role.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_ENCRYPT_STATUS Generated when encrypted status update.
 *
 * @retval MBA_RES_SUCCESS                  Successfully issue a negative reply of LE encrypt information request event.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 */
uint16_t BLE_GAP_EncInfoReqNegativeReply(uint16_t connHandle);


/**@brief Reply to an LE encrypt information request event.
 *        This API is called to reply @ref BLE_GAP_EVT_ENC_INFO_REQUEST event.
 * @note  This API shall be called only if device is peripheral role.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_ENCRYPT_STATUS Generated when encrypted status update. \n
 * @ref BLE_GAP_EVT_DISCONNECTED Generated when encryption information is wrong.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] p_ltk                         Pointer to 128 bit long term key (ltk).
 *
 * @retval MBA_RES_SUCCESS                  Successfully issue a reply of LE encrypt information request event.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 */
uint16_t BLE_GAP_EncInfoReqReply(uint16_t connHandle, uint8_t *p_ltk);


/**@brief Reply to an LE remote connection parameters request event if device accepts the remote devices request to change connection parameters. \n
 *        This API is called to reply @ref BLE_GAP_EVT_REMOTE_CONN_PARAM_REQUEST event.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] p_connParams                  Pointer to the connection parameter. See @ref BLE_GAP_ConnParams_T.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_CONN_PARAM_UPDATE Generated when connection parameters update complete.
 *
 * @retval MBA_RES_SUCCESS                  Successfully issue a reply of LE remote connection parameters request event.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 */
uint16_t BLE_GAP_RemoteConnParamsReqReply(uint16_t connHandle,  BLE_GAP_ConnParams_T *p_connParams);


/**@brief Reply to an LE remote connection parameters request event if device rejects the remote devices request to change connection parameters. \n
 *        This API is called to reply @ref BLE_GAP_EVT_REMOTE_CONN_PARAM_REQUEST event.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] reason                        The reason of remote connection parameter request negative reply. See @ref GAP_STATUS. 
 *
 * @retval MBA_RES_SUCCESS                  Successfully issue a negative reply of LE remote connection parameters request event.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 */
uint16_t BLE_GAP_RemoteConnParamsReqNegativeReply(uint16_t connHandle, uint8_t reason);


/**@brief Authenticate the given encryption key associated with the remote device specified by the connection,
 *        and once authenticated will encrypt the connection.
 * @note  This command shall only be used when the local devices role is Central.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_ENCRYPT_STATUS Generated when encrypted status update. \n
 * @ref BLE_GAP_EVT_DISCONNECTED Generated when encryption fail.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] p_random                      Pointer to 64 bit random number.
 * @param[in] p_ediv                        Pointer to 16 bit encrypted diversifier.
 * @param[in] p_ltk                         Pointer to 128 bit long term key (ltk).
 *
 * @retval MBA_RES_SUCCESS                  Successfully started.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 */
uint16_t BLE_GAP_EnableEncryption(uint16_t connHandle, uint8_t *p_random, uint8_t *p_ediv, uint8_t *p_ltk);


/**@brief Set RF Tx power level preset value for Advertising physical channel PDUs. (Advertising physical channel PDUs means all of advertising, scanning and initiating PDU).
 *        Advertising PDU Tx power setting for specific Advertising handle can be revised by @ref BLE_GAP_SetExtAdvParams.
 *        It is recommended to called during application code initialization. 
 *
 * @param[in] advTxPower                    The advertising transmit power.
 * @param[out] p_selectedTxPower            Point to the real transmit power level. (Unit: dBm)
 *
 * @retval MBA_RES_SUCCESS                  Successfully set the transmit power level.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
*/
uint16_t BLE_GAP_SetAdvTxPowerLevel(int8_t advTxPower, int8_t *p_selectedTxPower);


/**@brief Set RF Tx power level preset value for LE connection Data physical channel PDU. 
 *        If both connected devices support LE Power Control feature, RF Tx power level will be adjusted by BLE stack automatically.
 *
 * @param[in] connTxPower                   The transmit power after connected and before the LE transmit power control protocol been activated.
 * @param[out] p_selectedTxPower            Point to the real transmit power level. (Unit: dBm)
 *
 * @retval MBA_RES_SUCCESS                  Successfully set the transmit power level.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
*/
uint16_t BLE_GAP_SetConnTxPowerLevel(int8_t connTxPower, int8_t *p_selectedTxPower);


/**@brief Read the current and maximum transmit power value of specific LE connection handle. (unit: dBm) 
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] phy                           PHY. See @ref BLE_GAP_TRANSMITTER_PHY_TYPE.
 * @param[out] p_txPower                    Pointer to current transmit power level. (Unit: dBm)
 * @param[out] p_txPowerMax                 Pointer to maximum transmit power level. (Unit: dBm)
 *
 * @retval MBA_RES_SUCCESS                  Successfully get the transmit power level.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 */
uint16_t BLE_GAP_ReadTxPowerLevel(uint16_t connHandle, uint8_t phy, int8_t *p_txPower, int8_t *p_txPowerMax);


/**@brief Read the transmit power level used by remote device on the specific connection.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_TRANSMIT_POWER_REPORTING Generated for Tx power level information.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] phy                           PHY. See @ref BLE_GAP_TRANSMITTER_PHY_TYPE.
 *
 * @retval MBA_RES_SUCCESS                  Successfully issue the request.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 */
uint16_t BLE_GAP_ReadRemoteTxPowerLevel(uint16_t connHandle, uint8_t phy);

/**@brief Read the maximum and minimum factory RF transmit power level.
 *
 * @param[out] p_minTxPower                 Point to the minimum transmit power level. (Unit: dBm)
 * @param[out] p_maxTxPower                 Point to the maximum transmit power level. (Unit: dBm)
 *
 * @retval MBA_RES_SUCCESS                  Successfully issue the request.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 */
uint16_t BLE_GAP_ReadFactoryTxPowerLevel(int8_t *p_minTxPower, int8_t *p_maxTxPower);


/**@brief Set the golden receive power range.
 *
 * @param[out] upperLimit                   The golden range upper value. No higher than -30dBm. (Unit: dBm)
 * @param[out] lowerLimit                   The golden range lower value. No lower than -80dBm.
 * @param[out] stepDecreasePower            The maximum decrease power for each single step. (Unit: dBm)
 *
 * @retval MBA_RES_SUCCESS                  Successfully set golden receive power range.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 */
uint16_t BLE_GAP_SetGoldenRxPowerRange(int8_t upperLimit, int8_t lowerLimit, uint8_t stepDecreasePower);


/**@brief Enable or disable the reporting to the transmit power level
 *        changes in the local and remote device for the specific connection.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] localEnable                   Enable or disable local transmit power reports. Set true to enable the local transmit power reports.
 * @param[in] remoteEnable                  Enable or disable remote transmit power reports. Set true to enable the remote transmit power reports.
 *
 * @retval MBA_RES_SUCCESS                  Successfully issue the request.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 */
uint16_t BLE_GAP_SetTxPowerReportingEnable(uint16_t connHandle, bool localEnable, bool remoteEnable);


/**@brief Configure the extended advertising parameters.
 * @note  This API belongs to extended advertising feature. It will be disallowed if any one API belongs legacy advertising feature is issued before. @ref BLE_GAP_ADV_CATS for details of advertising APIs.\n
 *        @ref BLE_GAP_AdvInit and @ref BLE_GAP_ExtAdvInit are required for this API. \n\n
 *
 *        Coding scheme is S=8 (S: Transmitted Symbols) in advertising PDU when coded phy is used. @ref BLE_GAP_SetExtAdvCodingScheme is provided to change the coding scheme.
 *        The API is suggested to call after BLE_GAP_SetExtAdvParams API. \n\n
 *
 *        If legacy advertising PDU types are being used, and the advertising set already
 *        contains data, the type shall be one that supports advertising data and the
 *        amount of data shall not exceed 31 bytes.\n
 *        If extended advertising PDU types are being used then:\n
 *        - The advertisement shall not be both connectable and scannable.
 *        - High duty cycle directed connectable advertising shall not be used (bit 3 = 0).\n
 *
 * @param[in] p_extAdvParams                Pointer to @ref BLE_GAP_ExtAdvParams_T structure buffer.
 * @param[out] p_selectedTxPower            Point to the real transmit power level. (Unit: dBm)
 *
 * @retval MBA_RES_SUCCESS                  Successfully configure the extended advertising parameters.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 */
uint16_t BLE_GAP_SetExtAdvParams(BLE_GAP_ExtAdvParams_T *p_extAdvParams, int8_t *p_selectedTxPower);

/**@brief Set preferred phy for extended advertising. When coded phy is used in extended advertising,
 *        there are two coding schemes can be chosen (Transmitted Symbols: S=2 or S=8). This API is provided to configure coding scheme
 *        when using coded phy in extended advertising.
 *
 * @note  @ref BLE_GAP_AdvInit and @ref BLE_GAP_ExtAdvInit are required for this API. \n\n
 *
 * @param[in] codingScheme                  The coding scheme of adverting PDUs. 0 is S=8 coding and 1 is S=2 coding.
 *
 * @retval MBA_RES_SUCCESS                  Successfully setting the extended advertising coding scheme.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed if adv. is not initialized.
 */
uint16_t BLE_GAP_SetExtAdvCodingScheme(uint8_t codingScheme);


/**@brief Configure extended advertising data.
 * @note  This API may be issued at any time after an advertising set identified by the advHandle
 *        parameter has been created using the @ref BLE_GAP_SetExtAdvParams API.
 *        No matter advertising in that set is enabled or disabled.\n
 *        This API belongs to extended advertising feature. It will be disallowed if any one API that belongs to legacy advertising feature is issued before. @ref BLE_GAP_ADV_CATS for details of advertising APIs.\n
 *        @ref BLE_GAP_AdvInit and @ref BLE_GAP_ExtAdvInit are required for this API.
 *
 * @param[in] p_advDataParam                 Pointer to @ref BLE_GAP_ExtAdvDataParams_T structure buffer.
 *
 * @retval MBA_RES_SUCCESS                  Successfully configure extended advertising data.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 * @retval MBA_RES_UNKNOWN_ADV_ID           Unknown advertising identifier.
 */
uint16_t BLE_GAP_SetExtAdvData(BLE_GAP_ExtAdvDataParams_T *p_advDataParam);


/**@brief Configure extended scan response data.
 * @note  This API may be issued at any time after an advertising set identified by the advHandle
 *        parameter has been created using the @ref BLE_GAP_SetExtAdvParams API.
 *        No matter advertising in that set is enabled or disabled.\n
 *        This API belongs to extended advertising feature. It will be disallowed if any one API that belongs to legacy advertising feature is issued before. @ref BLE_GAP_ADV_CATS for details of advertising APIs.\n
 *        @ref BLE_GAP_AdvInit and @ref BLE_GAP_ExtAdvInit are required for this API.
 *
 * @param[in] p_scanDataParam               Pointer to @ref BLE_GAP_ExtAdvDataParams_T structure buffer.
 *
 * @retval MBA_RES_SUCCESS                  Successfully configure extended scan response data.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 * @retval MBA_RES_UNKNOWN_ADV_ID           Unknown advertising identifier.
 */
uint16_t BLE_GAP_SetExtScanRspData(BLE_GAP_ExtAdvDataParams_T *p_scanDataParam);


/**@brief Enable or disable one or more advertising sets using the advertising sets identified by the advHandle.
 * @note  If enable set to false and numOfSets set to 0x00, then all advertising sets are disabled. \n
 *        Advertising will be disabled after set maximum extended advertising events were sent even if the set duration has not expired.
 *        Details in @ref BLE_GAP_ExtAdvEnableParams_T. \n
 *        This API belongs to extended advertising feature. It will be disallowed if any one API that belongs to legacy advertising feature is issued before. @ref BLE_GAP_ADV_CATS for details of advertising APIs.\n
 *        @ref BLE_GAP_AdvInit and @ref BLE_GAP_ExtAdvInit are required for this API. \n\n
 *
 *        @ref BLE_GAP_SetExtAdvParams should be called before this API to set appropriate
 *        advertising parameters.\n
 *        @ref BLE_GAP_SetExtAdvData and @ref BLE_GAP_SetExtScanRspData should be called before this API to set appropriate
 *        advertising/scan response data.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_CONNECTED Generated when connectable advertising is started and connection is established. \n
 * @ref BLE_GAP_EVT_SCAN_REQ_RECEIVED Generated when ext. adv. enabled. \n
 * @ref BLE_GAP_EVT_ADV_SET_TERMINATED Generated when ext. adv. enabled and timeout (by duration).
 *
 * @param[in] enable                        Enable or disable one or more advertising sets. Set true to start the extended advertising.
 * @param[in] numOfSets                     The number of advertising sets contained in the p_advParam.
 * @param[in] p_advParam                    Pointer to @ref BLE_GAP_ExtAdvEnableParams_T structure buffer.
 *
 * @retval MBA_RES_SUCCESS                  Successfully enable or disable one or more advertising sets.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 * @retval MBA_RES_UNKNOWN_ADV_ID           Unknown advertising identifier.
 */
uint16_t BLE_GAP_SetExtAdvEnable(bool enable, uint8_t numOfSets, BLE_GAP_ExtAdvEnableParams_T *p_advParam);


/**@brief Remove an advertising set.
 * @note  This API belongs to extended advertising feature. It will be disallowed if any one API that belongs to legacy advertising feature is issued before. @ref BLE_GAP_ADV_CATS for details of advertising APIs.\n
 *        @ref BLE_GAP_AdvInit and @ref BLE_GAP_ExtAdvInit are required for this API.
 *
 * @param[in] advHandle                     Advertising handle.
 *
 * @retval MBA_RES_SUCCESS                  Successfully remove an advertising set.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 * @retval MBA_RES_UNKNOWN_ADV_ID           Unknown advertising identifier.
 */
uint16_t BLE_GAP_RemoveExtAdvSet(uint8_t advHandle);


/**@brief Remove all existing advertising sets.
 * @note  This API belongs to extended advertising feature. It will be disallowed if any one API that belongs to legacy advertising feature is issued before. @ref BLE_GAP_ADV_CATS for details of advertising APIs.\n
 *        @ref BLE_GAP_AdvInit and @ref BLE_GAP_ExtAdvInit are required for this API.
 *
 * @retval MBA_RES_SUCCESS                  Successfully remove all advertising sets.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 */
uint16_t BLE_GAP_ClearExtAdvSet();


/**@brief Retrieve the advertising address in the advertising events corresponding to the advertising handle. 
 *
 * @param[in] advHandle                     Advertising handle. Value 0xF0 to get the address of legacy advertising.
 * @param[in] p_addr                        Pointer to the @ref BLE_GAP_Addr_T structure buffer. Advertisier bluetooth address and address type.
 *
 * @retval MBA_RES_SUCCESS                  Successfully get the advertisier advertising address.
 * @retval MBA_RES_FAIL                     Anonymous advertisement. No address provided.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 * @retval MBA_RES_UNKNOWN_ADV_ID           Unknown advertising identifier.
 */
uint16_t BLE_GAP_GetAdvAddr(uint8_t advHandle, BLE_GAP_Addr_T *p_addr);


/**@brief Configure periodic advertising parameters.
 * @note  If the advHandle does not identify an advertising set that is already
 *        configured for periodic advertising and it is unable to support more periodic advertising at present.\n
 *        This API belongs to extended advertising feature. It will be disallowed if any one API that belongs to legacy advertising feature is issued before. @ref BLE_GAP_ADV_CATS for details of advertising APIs.\n
 *        @ref BLE_GAP_AdvInit, @ref BLE_GAP_ExtAdvInit and @ref BLE_GAP_PeriodicAdvInit are required for this API.
 *
 * @param[in] p_periAdvParams               Pointer to @ref BLE_GAP_PeriAdvParams_T structure buffer.
 *
 * @retval MBA_RES_SUCCESS                  Successfully configure periodic advertising parameters.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 * @retval MBA_RES_UNKNOWN_ADV_ID           Unknown advertising identifier.
 */
uint16_t BLE_GAP_SetPeriAdvParams(BLE_GAP_PeriAdvParams_T *p_periAdvParams);


/**@brief Set periodic advertising data.
 * @note  This API may be issued at any time.
 *        If periodic advertising is currently enabled for the specified advertising set, the new data in
 *        subsequent periodic advertising events shall be used for this advertising set.
 *        If a periodic advertising event is in progress when this command is issued, the old or new data may be used for that event.\n
 *        This API belongs to extended advertising feature. It will be disallowed if any one API that belongs to legacy advertising feature is issued before. @ref BLE_GAP_ADV_CATS for details of advertising APIs.\n
 *        @ref BLE_GAP_AdvInit, @ref BLE_GAP_ExtAdvInit and @ref BLE_GAP_PeriodicAdvInit are required for this API.
 *
 * @param[in] p_advDataParam                Pointer to @ref BLE_GAP_PeriAdvDataParams_T structure buffer.
 *
 * @retval MBA_RES_SUCCESS                  Successfully set periodic advertising data.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 * @retval MBA_RES_UNKNOWN_ADV_ID           Unknown advertising identifier.
 */
uint16_t BLE_GAP_SetPeriAdvData(BLE_GAP_PeriAdvDataParams_T *p_advDataParam);


/**@brief Enable or disable the periodic advertising for the advertising set specified by the advHandle.
 * @note  If the advertising set is not currently enabled (see @ref BLE_GAP_SetExtAdvEnable API), the periodic
 *        advertising is not started until the advertising set is enabled.\n
 *        The periodic advertising should continue until this API is called with enable set to false.\n
 *        This API belongs to extended advertising feature. It will be disallowed if any one API that belongs to legacy advertising feature is issued before. @ref BLE_GAP_ADV_CATS for details of advertising APIs.\n
 *        @ref BLE_GAP_AdvInit, @ref BLE_GAP_ExtAdvInit and @ref BLE_GAP_PeriodicAdvInit are required for this API.
 *
 * @param[in] enable                        Enable or disable the periodic advertising.
 * @param[in] advHandle                     Identifies which advertising set to be enabled or disabled.
 *
 * @retval MBA_RES_SUCCESS                  Successfully enable or disable the periodic advertising.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters. 
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 * @retval MBA_RES_UNKNOWN_ADV_ID           Unknown advertising identifier.
 */
uint16_t BLE_GAP_SetPeriAdvEnable(bool enable, uint8_t advHandle);


/**@brief Set the extended scan parameters to be used on the advertising physical channels.
 * @note  This API belongs to extended advertising feature. It will be disallowed if any one API that belongs to legacy advertising feature is issued before. @ref BLE_GAP_ADV_CATS for details of advertising APIs.\n
 *        @ref BLE_GAP_ScanInit and @ref BLE_GAP_ExtScanInit are required for this API.
 *
 * @param[in] filterPolicy                  Scanning filter policy. See @ref BLE_GAP_SCAN_FP.
 * @param[in] p_extScanPhy                  Pointer to @ref BLE_GAP_ExtScanningPhy_T structure buffer.
 *
 * @retval MBA_RES_SUCCESS                  Successfully set the extended scan parameters.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 */
uint16_t BLE_GAP_SetExtScanningParams(uint8_t filterPolicy, BLE_GAP_ExtScanningPhy_T *p_extScanPhy);

/**@brief Enable or disable extended scanning.
 * @note  If this API with enable set to true is called while scanning is already enabled, the timers used for duration and
 *        period are reset to the new parameter values and a new scan period is started.\n
 *        The duration of a scan period refers to the time spent scanning on both the primary and secondary advertising physical channels.\n
 *        If scanning is started and advertising packet or scan response is received then the
 *        event @ref BLE_GAP_EVT_EXT_ADV_REPORT is generated.\n
 *        This API belongs to extended advertising feature. It will be disallowed if any one API that belongs to legacy advertising feature is issued before. @ref BLE_GAP_ADV_CATS for details of advertising APIs.\n
 *        @ref BLE_GAP_ScanInit and @ref BLE_GAP_ExtScanInit are required for this API.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_EXT_ADV_REPORT Generated when ext. scan enabled. \n
 * @ref BLE_GAP_EVT_SCAN_TIMEOUT Generated when ext. scan enabled and timeout (by duration).
 *
 * @param[in] mode                          Scan mode. See @ref BLE_GAP_SCAN_MODES.
 * @param[in] p_enable                      Pointer to @ref BLE_GAP_ExtScanningEnable_T structure buffer.
 *
 *
 * @retval MBA_RES_SUCCESS                  Successfully enable or disable extended scanning.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 */
uint16_t BLE_GAP_SetExtScanningEnable(uint8_t mode, BLE_GAP_ExtScanningEnable_T *p_enable);


/**@brief Set the PHY preferences for the specified connection.
 * @note  The Controller might not be able to make the change. Event will generate if one of the phy changes.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_PHY_UPDATE Generated when phy updated.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] txPhys                        TX PHYs. A bit field that indicates the transmitter PHYs that the user prefers to use.
 *                                          See @ref BLE_GAP_PHY_OPTION.
 * @param[in] rxPhys                        RX PHYs. A bit field that indicates the receiver PHYs that the user prefers to use.
 *                                          See @ref BLE_GAP_PHY_OPTION.
 * @param[in] phyOptions                    PHY options. See @ref BLE_GAP_PHY_PREF.
 *
 * @retval MBA_RES_SUCCESS                  Successfully set the PHY preferences for the specified connection.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 * @retval MBA_RES_UNKNOWN_CONN_ID          Unknown connection identifier.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 */
uint16_t BLE_GAP_SetPhy(uint16_t connHandle, uint8_t txPhys, uint8_t rxPhys, uint8_t phyOptions);


/**@brief Read the current transmitter PHY and receiver PHY on the specified connection
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] p_txPhy                       Pointer to TX PHY buffer. See @ref BLE_GAP_PHY_TYPE for the definition.
 * @param[in] p_rxPhy                       Pointer to RX PHY buffer. See @ref BLE_GAP_PHY_TYPE for the definition.
 *
 *
 * @retval MBA_RES_SUCCESS                  Successfully read the current transmitter PHY and receiver PHY.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_UNKNOWN_CONN_ID          Unknown connection identifier.
 */
uint16_t BLE_GAP_ReadPhy(uint16_t connHandle, uint8_t *p_txPhy, uint8_t *p_rxPhy);


/**@brief Specify the preferred values for the transmitter PHY and receiver PHY to be used for all subsequent connections.
 *
 * @param[in] txPhys                        Indicates the transmitter PHYs that the user prefers to use.
 * @param[in] rxPhys                        Indicates the receiver PHYs that the user prefers to use.
 *
 * @retval MBA_RES_SUCCESS                  Successfully specify the preferred values for the transmitter PHY and receiver PHY to be used for all subsequent connections.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 */
uint16_t BLE_GAP_SetDefaultPhy(uint8_t txPhys, uint8_t rxPhys);


/**@brief Read authenticated payload timeout value.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[out] p_authPayloadTo              Pointer to authenticated payload timeout parameter (Unit: 10ms).
 *
 * @retval MBA_RES_SUCCESS                  Successfully read the authenticated payload timeout parameter.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_UNKNOWN_CONN_ID          Unknown connection identifier.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 */
uint16_t BLE_GAP_ReadAuthPayloadTimeout(uint16_t connHandle, uint16_t *p_authPayloadTo);


/**@brief Write authenticated payload timeout parameter.
 * @note  This configuration determine when to use the LE ping sequence.
 *
 * @param[in] connHandle                    Connection handle associated with this connection.
 * @param[in] authPayloadTo                 Authenticated payload timeout parameter (Unit: 10 ms).
 *                                          The authPayloadTo shall be equal to or greater than connInterval*(1 + peripheralLatency).
 *                                          Refer to @ref BLE_GAP_EvtConnect_T.
 *
 * @retval MBA_RES_SUCCESS                  Successfully write the authenticated payload timeout parameter.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_UNKNOWN_CONN_ID          Unknown connection identifier.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 */
uint16_t BLE_GAP_WriteAuthPayloadTimeout(uint16_t connHandle, uint16_t authPayloadTo);


/**@brief Configure the build-in Generic Access services.
 *        Optional characteristics and characteristic value can be configured in mandatory "Generic Access Service".
 * @note  The function is suggested to be called when initialization. Also, it can't be called in connected state.
 *        The configured option (enable/disable) should not be changed if the function is called.
 *        Otherwise, service change situation need to be considered in the multiple configuring build-in services case.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_DEVICE_NAME_CHANGED Generated when device name characteristic is configured as writable and is written by remote connected peer.
 *
 * @param[in] p_serviceOptions               Pointer to the @ref BLE_GAP_ServiceOption_T structure buffer.
 *
 * @retval MBA_RES_SUCCESS                   Successfully configure the build-in Services.
 * @retval MBA_RES_OOM                       Internal memory allocation failure.
 */
uint16_t BLE_GAP_ConfigureBuildInService(BLE_GAP_ServiceOption_T *p_serviceOptions);


/**@brief Synchronize with a periodic advertising train from an advertiser and begin receiving periodic advertising packets.
 * @note  This API may be called whether or not scanning is enabled and scanning may be enabled and disabled while this command is pending.
 *        However, synchronization can only occur when scanning is enabled. See @ref BLE_GAP_SetExtScanningEnable. \n
 *        This API belongs to extended advertising feature. It will be disallowed if any one API that belongs to legacy advertising feature is issued before. @ref BLE_GAP_ADV_CATS for details of advertising APIs.\n
 *        @ref BLE_GAP_ScanInit, @ref BLE_GAP_ExtScanInit and @ref BLE_GAP_SyncInit are required for this API.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_PERI_ADV_SYNC_EST Generated when sync. established. \n
 * @ref BLE_GAP_EVT_PERI_ADV_REPORT Generated when enabling to receive the report.
 *
 * @param[in] p_periSync                    Pointer to @ref BLE_GAP_CreateSync_T structure buffer.
 *
 * @retval MBA_RES_SUCCESS                  Successfully issue a request to synchronize with a periodic advertising.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 * @retval MBA_RES_CONN_ALREADY_EXISTS      Connection already exists.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 */
uint16_t BLE_GAP_CreateSync(BLE_GAP_CreateSync_T *p_periSync);


/**@brief Cancel the @ref BLE_GAP_CreateSync procedure while it is pending.
 * @note  This API belongs to extended advertising feature. It will be disallowed if any one API that belongs to legacy advertising feature is issued before. @ref BLE_GAP_ADV_CATS for details of advertising APIs.\n
 *        @ref BLE_GAP_ScanInit, @ref BLE_GAP_ExtScanInit and @ref BLE_GAP_SyncInit are required for this API.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_PERI_ADV_SYNC_EST Generated with corresponding status code.
 *
 * @retval MBA_RES_SUCCESS                  Successfully cancel the @ref BLE_GAP_CreateSync procedure.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 */
uint16_t BLE_GAP_CreateSyncCancel();


/**@brief Stop reception of the periodic advertising train identified by the input "syncHandle".
 * @note  This API belongs to extended advertising feature. It will be disallowed if any one API that belongs to legacy advertising feature is issued before. @ref BLE_GAP_ADV_CATS for details of advertising APIs.\n
 *        @ref BLE_GAP_ScanInit, @ref BLE_GAP_ExtScanInit and @ref BLE_GAP_SyncInit are required for this API.
 *
 * @param[in] syncHandle                    Identity of the periodic advertising train. Range: 0x0000 to 0X0EFF
 *
 * @retval MBA_RES_SUCCESS                  Successfully stop reception of the periodic advertising train.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 * @retval MBA_RES_UNKNOWN_ADV_ID           Unknown advertising identifier.
 */
uint16_t BLE_GAP_TerminateSync(uint16_t syncHandle);


/**@brief Set one or multiple entries to the Periodic Advertiser list.
 *
 * @param[in] num                           Number of devices need to be set. See @ref BLE_GAP_MAX_DEV_NUM
 * @param[in] p_syncSetDev                  Pointer to the @ref BLE_GAP_SyncSetDev_T structure buffer. 
 * 
 * @retval MBA_RES_SUCCESS                  Successfully Set one or multiple entries to the Periodic Advertiser list.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 */
uint16_t BLE_GAP_SetDevToPeriAdvList(uint8_t num, BLE_GAP_SyncSetDev_T *p_syncSetDev);


/**@brief Enables or disables reports for the periodic advertising train identified by input "syncHandle".
 * @note  This API belongs to extended advertising feature. It will be disallowed if any one API that belongs to legacy advertising feature is issued before. @ref BLE_GAP_ADV_CATS for details of advertising APIs.\n
 *        @ref BLE_GAP_ScanInit, @ref BLE_GAP_ExtScanInit and @ref BLE_GAP_SyncInit are required for this API.
 *
 * @par Events generated
 * @ref BLE_GAP_EVT_PERI_ADV_REPORT Generated when enabled.
 *
 * @param[in] syncHandle                    Identity of the periodic advertising train.
 * @param[in] enable                        Enable or disable reports. Set true to enable reports.
 *
 * @retval MBA_RES_SUCCESS                  Successfully enables or disables reports for the periodic advertising train.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_COMMAND_DISALLOWED       Command disallowed.
 * @retval MBA_RES_UNKNOWN_ADV_ID           Unknown advertising identifier.
 */
uint16_t BLE_GAP_SetPeriAdvRxEnable(uint16_t syncHandle, bool enable);


/**@brief Set the scanning filter parameters to filter received advertising or scan response PDU.
 *        There are 3 Advertising Data Type (AD_Type) contents filter options can be enabled individually.
 *        While either option is enabled and PDU contents with specific AD_Type data that same as compared target parameters, LE Stack will report this received PDU 
 *        by @ref BLE_GAP_EVT_ADV_REPORT or @ref BLE_GAP_EVT_EXT_ADV_REPORT event.
 *        -   Name Filter: To filter the contents of Shortened Local Name (AD_Type=0x08) or Full Complete Local Name (AD_Type=0x09). 
 *        -   Service Data Filter: To filter the contents of Service Data (AD_Type=0x16).
 *        -   Manufacture Data Filter: To filter the contents of Manufacturer Specific Data (AD_Type=0xFF)
 *
 * @note This scanning filter is an advanced filtering procedure after filterPolicy setting in the @ref BLE_GAP_SetScanningParam API or BLE_GAP_SetScanningParam API.
 *
 * @param[in] p_param                       Pointer to @ref BLE_GAP_ScanFilterConfig_T structure buffer.
 *
 * @retval MBA_RES_SUCCESS                  Successfully set the scanning filter parameters.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 */
uint16_t BLE_GAP_SetScanningFilter(BLE_GAP_ScanFilterConfig_T *p_param);

/**@} */ //BLE_GAP_FUNS
#endif

/**
  @}
*/
