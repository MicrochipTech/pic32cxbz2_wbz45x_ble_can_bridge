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
  Device Information Middleware Header File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_dm_info.h

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
 
#ifndef BLE_DM_INFO_H
#define BLE_DM_INFO_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include "stack_mgr.h"
#include "ble_gap.h"


// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
typedef struct BLE_DM_InfoConn_T
{
    uint16_t        connHandle;
    uint8_t         role;
    uint8_t         state;
    BLE_GAP_Addr_T  remoteAddr;
    bool            encryptKeyValid;
    uint8_t         encryptKey[16];
    uint8_t         pairOption;
    uint8_t         encKeySize;
    uint8_t         devId;
} BLE_DM_InfoConn_T;

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************

/**@brief Initialize BLE_DM_InfoInit module.
 *
*/
void BLE_DM_InfoInit();


/**@brief Function for handling BLE events.
 *        This function should be called for every BLE event
 *
 * @param[in] p_stackEvent        Pointer to BLE events buffer.
 *
*/
void BLE_DM_Info(STACK_Event_T *p_stackEvent);

BLE_DM_InfoConn_T *BLE_DM_InfoGetConnByHandle(uint16_t connHandle);

uint16_t BLE_DM_InfoSetFilterAcceptList(uint8_t devCnt, uint8_t const *p_devId);

uint16_t BLE_DM_InfoGetFilterAcceptList(uint8_t *p_devCnt, BLE_GAP_Addr_T *p_addr);

uint16_t BLE_DM_InfoSetResolvingList(uint8_t devCnt, uint8_t const *p_devId, uint8_t const *p_privacyMode);

#endif

/**
  @}
*/

