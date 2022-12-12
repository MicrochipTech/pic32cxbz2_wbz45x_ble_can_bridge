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
   BLE Connection Middleware Header File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_dm_conn.h

  Summary:
    This file contains the Device Information functions for 
    BLE Device Manager module internal use.

  Description:
    This file contains the Device Information functions for 
    BLE Device Manager module internal use.
 *******************************************************************************/


/**
 * @addtogroup BLE_DM_INFO BLE_DM_INFO
 * @{
 * @brief Header file for the BLE Device Manager (ble_dm_info) internal module.
 */
 
#ifndef BLE_DM_CONN_H
#define BLE_DM_CONN_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <string.h>
#include <stdint.h>
#include "stack_mgr.h"


// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************

/**@brief Initialize BLE_DM_ConnInit module.
 *
*/
void BLE_DM_ConnInit();


/**@brief Function for handling BLE events.
 *        This function should be called for every BLE event
 *
 * @param[in] p_stackEvent        Pointer to BLE events buffer.
 *
*/
void BLE_DM_Conn(STACK_Event_T *p_stackEvent);

/**@brief Initialize configuration parameters of BLE_DM_CONN module.\n 
 *        User can configure automatic or manual reply when receive gap/l2cap connection parameters update requests. \n
 *        If user choose to reply manually, related events BLE_L2CAP_EVT_CONN_PARA_UPDATE_REQ or BLE_GAP_EVT_REMOTE_CONN_PARAM_REQUEST need to handle by user-self.
 *        Either accept or reject. Connection will be terminated if such requests are not handled properly. \n
 *        If automatic reply is adopted, related parameters min/max acceptable connection interval, min/max acceptable Peripheral latency need to be set properly.
 *        The BLE_DM_CONN module will accept or reject these requests based on the acceptable parameters range.
 *
 * @param[in] p_config              Pointer to configuration parameters. @ref BLE_DM_ConnConfig_T.
 *
 * @retval MBA_RES_SUCCESS          Successfully initialize the configuration parameters.
 * @retval MBA_RES_INVALID_PARA     The invalid acceptable parameters are used.
*/
uint16_t BLE_DM_ConnConfig(BLE_DM_ConnConfig_T *p_config);

#endif

/**
  @}
*/

