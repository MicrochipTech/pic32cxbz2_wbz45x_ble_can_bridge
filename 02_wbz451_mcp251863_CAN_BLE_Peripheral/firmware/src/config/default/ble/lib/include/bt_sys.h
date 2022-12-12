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
  Bluetooth System Header File

  Company:
    Microchip Technology Inc.

  File Name:
    bt_sys.h

  Summary:
    This file contains the BLE System functions for the project.

  Description:
    This file contains the BLE System functions for the project. The "BT_SYS_Init"
    function shall be called in the "SYS_Initialize" function to initialize the
    this modules in the system. And the "BM_Task"  shall be called in the "SYS_Tasks".
 *******************************************************************************/


/**
 * @addtogroup BT_SYS
 * @{
 */

#ifndef BT_SYS_H
#define BT_SYS_H

/** @defgroup BT_SYS_INT Bluetooth System Interface
 *  @brief This module defines the interface of the Bluetooth system.
 *  @{ */

#include <stdbool.h>
#include <stdint.h>

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************

/**@addtogroup BT_SYS_DEFINES Defines
 * @{ */

/**@defgroup BT_SYS_ADDR_LEN Length of Bluetooth address
 * @brief Length of Bluetooth address.
 * @{ */
#define BT_SYS_DEV_ADDR_LEN             7           /**< Length of the Bluetooth address. */
/**@} */ //BT_SYS_ADDR_LEN


/**@defgroup BT_SYS_TRACE_MASK Trace Mask
 * @brief The definition of trace mask.
 * @{ */
#define BT_SYS_TRACE_INFO_LL_H          1           /**< LL trace high priority information. */
#define BT_SYS_TRACE_INFO_LL_L          (1<<1)      /**< LL trace low priority information. */
#define BT_SYS_TRACE_INFO_HOST          (1<<2)      /**< Host trace info. */
/**@} */ //BT_SYS_TRACE_MASK


/**@defgroup BT_SYS_RF_SUSPEND_STATUS Rf Suspned Status
 * @brief The definition of rf suspend status
 * @{ */
#define BT_SYS_RF_NOT_SUSPEND               0          /**< BLE RF is not allowed to suspend. */
#define BT_SYS_RF_SUSPENDED_NO_SLEEP        1          /**< BLE RF is allowed to suspended without ble sleep mode. */
#define BT_SYS_RF_SUSPENDED_WITH_SLEEP      2          /**< BLE RF is allowed to suspended with ble sleep mode. */
/**@} */ //BT_SYS_RF_SUSPEND

/**@} */ //BT_SYS_DEFINES

// *****************************************************************************
// *****************************************************************************
// SSection: Data Types
// *****************************************************************************

/**@addtogroup BT_SYS_STRUCTS Structures
 * @{ */

/**@brief Bluetooth system configuration. */
typedef struct BT_SYS_Cfg_T
{
    uint8_t     addrValid:1;                        /**< Set true if devAddr field is valid. */
    uint8_t     rssiOffsetValid:1;                  /**< Set true if rssiOffset field is valid. */
    uint8_t     antennaGainValid:1;                 /**< Set true if antennaGain field is valid. */
    uint8_t     devAddr[BT_SYS_DEV_ADDR_LEN];       /**< Device address. */
    int8_t      rssiOffset;                         /**< RSSI offset. */
    int8_t      antennaGain;                        /**< Antenna gain. */
} BT_SYS_Cfg_T;

/**@brief BT system trace callback type. This callback function sends trace events to the application. */
typedef void (*BT_SYS_TraceEventCb_T)(uint8_t length, uint8_t *p_tracePayload);

/**@brief Bluetooth system initialization. */
typedef struct BT_SYS_Option_T
{
    uint32_t        cmnMemSize;                         /**< Common memory size. */
    uint8_t         *p_cmnMemAddr;                      /**< Common memory address. */
    uint32_t        *p_sramVecorTable;                  /**< Vector table. */
} BT_SYS_Option_T;

/**@} */ //BT_SYS_STRUCTS

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************

/**@addtogroup BT_SYS_FUNS Functions
 * @{ */

/**@brief Initialize Bluetooth system
 *
 * @param[in] p_reqQueueHandle                  OS handle for Bluetooth internal task.
 * @param[in] p_osalApiList                     OSAL api list.
 * @param[in] p_option                          Initialization option.
 * @param[in] p_cfg                             System configuration.
 *
 * @retval true                                 Success to initialize BT.
 * @retval false                                Fail to initialize BT.
 */
bool BT_SYS_Init(void *p_reqQueueHandle, void *p_osalApiList, BT_SYS_Option_T *p_option, BT_SYS_Cfg_T *p_cfg);


/**@brief Retrieve BT version.
 *
 * @param[out] p_version                        Point to version buffer.
 *
 */
void BT_SYS_ReadVersion(uint32_t *p_version);


/**@brief Query if BT is ready for idle.
 *
 * @retval true                                     Ready for idle.
 * @retval false                                    Not ready for idle.
 */
bool BT_SYS_Ready4Idle();


/**@brief Query if BT is sleeping.
 *
 * @retval true                                     BT is sleeping.
 * @retval false                                    BT is not sleeping.
 */
bool BT_SYS_GetSleepMode();


/**@brief Request BT enter sleep mode.
 *
 * @param[in] ulRtcFrequency                        RTC frequency.
 * @param[in] ulRtcCurrentCnt                       RTC current count.
 *
 * @retval true                                     BT is ready for idle and enter sleep.
 * @retval false                                    BT is already sleeping or BT is not ready for idle.
 */
bool BT_SYS_EnterSleepMode(uint32_t ulRtcFrequency, uint32_t ulRtcCurrentCnt);


/**@brief Query if BT allow system enter sleep mode.
 *
 * @param[in] ulRtcFrequency                        RTC frequency.
 * @param[in] ulRtcCurrentCnt                       RTC current count.
 *
 * @retval true                                     BT is sleeping and BT is ready for System enter sleep.
 * @retval false                                    BT is not sleeping or BT is not ready for System enter sleep.
 */
bool BT_SYS_AllowSystemSleep(uint32_t ulRtcFrequency, uint32_t ulRtcCurrentCnt);


/**@brief Request BT enter deep sleep mode.
 *
 * @retval None
 */
void BT_SYS_EnterDeepSleepMode();


/**@brief Request BT suspend RF.
 *
 * @param[in] enable                                Set true to suspend RF. Otherwise set false.
 *
 * @retval BT_SYS_RF_SUSPEND_STATUS                  BT system RF Suspend status. See @ref BT_SYS_RF_SUSPEND_STATUS.
 */
uint8_t BT_SYS_RfSuspendReq(uint8_t enable);


/**@brief Enable BT trace message indication.
 *
 * @param[in] traceMask                             BT system trace mask. See @ref BT_SYS_TRACE_MASK.
 * @param[in] traceCb                               BT system trace callback.
 *
 */
void BT_SYS_TraceEnable(uint32_t traceMask, BT_SYS_TraceEventCb_T traceCb);

/**@brief Enable BT time sensitive trace message indication.
 *
 * @param[in] traceMask                             BT system trace mask. See @ref BT_SYS_TRACE_MASK.
 * @param[in] traceCb                               BT system trace callback.
 *
 */
void BT_SYS_TraceTimeSensEnable(uint32_t traceMask, BT_SYS_TraceEventCb_T traceCb);

/**@brief Hook Bluetooth task
 *
 * @param[in] p_param Pointer that will be used as the parameter for the task
 *
 */
void BM_Task(void *p_param);

/**@} */ //BT_SYS_FUNS

/**
  @}
*/

#endif//BT_SYS_H

/**
  @}
*/
