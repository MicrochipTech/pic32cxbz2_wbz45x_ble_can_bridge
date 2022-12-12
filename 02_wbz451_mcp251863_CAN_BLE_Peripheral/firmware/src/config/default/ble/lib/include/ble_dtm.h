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
  BLE DTM Header File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_dtm.h

  Summary:
    This file contains the BLE DTM functions for application user.

  Description:
    This file contains the BLE DTM functions and event for application user.  The
    "BLE_DTM_Init" function shall be called in the "APP_Initialize" function to 
    initialize the this modules in the system.
 *******************************************************************************/


/**
 * @addtogroup BLE_DTM
 * @{
 */
#ifndef BLE_DTM_H
#define BLE_DTM_H

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

/**@addtogroup BLE_DTM_DEFINES Defines
 * @{ */

/**@defgroup BLE_DTM_CHANNEL_RANGE Receiver or transmitter channel
 * @brief Range of RX/TX channel defintion.
 * @{ */
#define BLE_DTM_CHANNEL_MIN                                     0x00        /**< Minimum value of channel definition.*/
#define BLE_DTM_CHANNEL_MAX                                     0x27        /**< Maximum value of channel definition.*/
/** @} */

/**@defgroup BLE_DTM_TRANSMITTER_PAYLOAD_TYPE Transmitter payload type
 * @brief The definition of transmitter test packet payload type.
 * @{ */
#define BLE_DTM_TRANSMITTER_TEST_PAYLOAD_0                      0x00        /**< PRBS9 sequence â??11111111100000111101â?¦â?? (in transmission order) */
#define BLE_DTM_TRANSMITTER_TEST_PAYLOAD_1                      0x01        /**< Repeated â??11110000â?? (in transmission order) sequence*/
#define BLE_DTM_TRANSMITTER_TEST_PAYLOAD_2                      0x02        /**< Repeated â??10101010â?? (in transmission order) sequence*/
#define BLE_DTM_TRANSMITTER_TEST_PAYLOAD_3                      0x03        /**< PRBS15 sequence */
#define BLE_DTM_TRANSMITTER_TEST_PAYLOAD_4                      0x04        /**< Repeated â??11111111â?? (in transmission order) sequence */
#define BLE_DTM_TRANSMITTER_TEST_PAYLOAD_5                      0x05        /**< Repeated â??00000000â?? (in transmission order) sequence */
#define BLE_DTM_TRANSMITTER_TEST_PAYLOAD_6                      0x06        /**< Repeated â??00001111â?? (in transmission order) sequence */
#define BLE_DTM_TRANSMITTER_TEST_PAYLOAD_7                      0x07        /**< Repeated â??01010101â?? (in transmission order) sequence */
/** @} */

/**@defgroup BLE_DTM_TRANSMITTER_PHY_TYPE Transmitter PHY type
 * @brief The definition of transmitter test packet PHY type.
 * @{ */
#define BLE_DTM_TRANSMITTER_LE_1M_PHY                           0x01        /**< Transmitter set to use the LE 1M PHY */
#define BLE_DTM_TRANSMITTER_LE_2M_PHY                           0x02        /**< Transmitter set to use the LE 2M PHY */
#define BLE_DTM_TRANSMITTER_LE_CODED_PHY_S_8                    0x03        /**< Transmitter set to use the LE Coded PHY with S=8 data coding */
#define BLE_DTM_TRANSMITTER_LE_CODED_PHY_S_2                    0x04        /**< Transmitter set to use the LE Coded PHY with S=2 data coding */
/** @} */

/**@defgroup BLE_DTM_RECEIVER_PHY_TYPE Receiver PHY type
 * @brief The definition of receiver test packet PHY type.
 * @{ */
#define BLE_DTM_RECEIVER_LE_1M_PHY                              0x01        /**< Receiver set to use the LE 1M PHY */
#define BLE_DTM_RECEIVER_LE_2M_PHY                              0x02        /**< Receiver set to use the LE 2M PHY */
#define BLE_DTM_RECEIVER_LE_CODED_PHY                           0x03        /**< Receiver set to use the LE Coded PHY*/
/** @} */

/**@defgroup BLE_DTM_CW_CHANNEL_RANGE Channel range of continuous wave test
 * @brief Range of Continuous Wave (CW) test defintion.
 * @{ */
#define BLE_DTM_CW_CHANNEL_MIN                                  0x00        /**< Minimum value of channel definition.*/
#define BLE_DTM_CW_CHANNEL_MAX                                  0x4E        /**< Maximum value of channel definition.*/
/** @} */

/**@} */ //BLE_DTM_DEFINES

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/**@addtogroup BLE_DTM_STRUCTS Structures
 * @{ */

/**@brief Transmitter test parameters */
typedef struct BLE_DTM_TransmitterTestParams_T
{
    uint8_t                 txChannel;                              /**< The RF channel which is used by the transmitter. Channel= (F â?? 2402) / 2 (Frequency Range : 2402 MHz to 2480 MHz) See @ref BLE_DTM_CHANNEL_RANGE. */
    uint8_t                 testDataLen;                            /**< The length of the payload of the test reference packets. */
    uint8_t                 packetPayload;                          /**< The contents of the payload of the test reference packets. See @ref BLE_DTM_TRANSMITTER_PAYLOAD_TYPE.*/
    uint8_t                 phy;                                    /**< The PHY which is used by the transmitter. See @ref BLE_DTM_TRANSMITTER_PHY_TYPE. */
    int8_t                  transmitPowerLevel;                     /**< The transmit power level which is used by the transmitter. Range: -127 to +20. (Units: dBm) \n
                                                                         Set to 0x7E to use the minimum transmit power level. \n
                                                                         Set to 0x7F to use the maximum transmit power level. \n
                                                                         If the parameter is set to a value other than 0x7E or 0x7F, then ble stack makes the requested change or makes closest change that it is capable of doing. */
} BLE_DTM_TransmitterTestParams_T;

/**@} */ //BLE_DTM_STRUCTS

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************
/**@addtogroup BLE_DTM_FUNS Functions
 * @{ */

/**@brief Initialize BLE DTM (Directed Test Mode) module.
 *
 * @retval MBA_RES_SUCCESS                  Successfully initialize BLE DTM module.
 */
uint16_t BLE_DTM_Init();

/**@brief Stop any test which is in progress.
 * @note  @ref BLE_DTM_Init is required for this API.
 *
 * @param[out] p_packetCount                Pointer to the packet count parameter buffer. The number of count shall be zero for a transmitter test and shall be received packets for a reveiver test.
 * @param[out] p_avgRssi                    Pointer to the average rssi value buffer.
 *
 * @retval MBA_RES_SUCCESS                  Successfully stop the test which is in progress.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 *
 */
uint16_t BLE_DTM_EndTest(uint16_t *p_packetCount, int8_t *p_avgRssi);


/**@brief Start a test where the device generates test reference packets at a fixed interval
 * @note  @ref BLE_DTM_Init is required for this API.
 *
 * @param[in] p_transTestParams             Pointer to the transmitter test parameter. See @ref BLE_DTM_TransmitterTestParams_T.
 *
 * @retval MBA_RES_SUCCESS                  Successfully set the BLE transmitter test.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 */
uint16_t BLE_DTM_EnhancedTransmitterTest(BLE_DTM_TransmitterTestParams_T *p_transTestParams);


/**@brief Start a test where the device receives test reference packets at a fixed interval.
 * @note  @ref BLE_DTM_Init is required for this API.
 *
 * @param[in] rxChannel                     Channel= (F â?? 2402) / 2 (Frequency Range : 2402 MHz to 2480 MHz) See @ref BLE_DTM_CHANNEL_RANGE 
 * @param[in] phy                           PHY type setting. See @ref BLE_DTM_RECEIVER_PHY_TYPE.
 *
 * @retval MBA_RES_SUCCESS                  Successfully start the receiver test.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 */
uint16_t BLE_DTM_EnhancedReceiverTest(uint8_t rxChannel, uint8_t phy);

/**@brief Start a Continuous Wave (CW) test with specific channel and power.
 * @note  @ref BLE_DTM_Init is required for this API.
 *
 * @param[in] txChannel                     Channel = (F â?? 2402) (Frequency Range : 2402 MHz to 2480 MHz) See @ref BLE_DTM_CW_CHANNEL_RANGE. 
 * @param[in] txPower                       The transmit power level to be used by the transmitter. Range: -127 to +20. Units: dBm.
 *
 * @retval MBA_RES_SUCCESS                  Successfully start the CW test.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 * @retval MBA_RES_INVALID_PARA             Invalid parameters.
 */
uint16_t BLE_DTM_StartCwTest(uint8_t txChannel, int8_t txPower);

/**@brief Stop the Continuous Wave (CW) test.
 * @note  @ref BLE_DTM_Init is required for this API.
 *
 * @retval MBA_RES_SUCCESS                  Successfully stop the CW test.
 * @retval MBA_RES_OOM                      Internal memory allocation failure.
 */
uint16_t BLE_DTM_StopCwTest();

/**@} */ //BLE_DTM_FUNS
#endif

/**
  @}
*/
