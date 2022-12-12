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
  Device Information Middleware Source File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_dm_dds.h

  Summary:
    This file contains the Device Data Storage functions for 
    BLE Device Manager module internal use.

  Description:
    This file contains the Device Data Storage functions for 
    BLE Device Manager module internal use.
 *******************************************************************************/


/**
 * @addtogroup BLE_DM_PDB BLE_DM_PDB
 * @{
 * @brief Header file for the BLE Device Manager (ble_dm_dds) internal module.
 */
 
#ifndef BLE_DM_DDS_H
#define BLE_DM_DDS_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************


#include <stdint.h>
#include <stdbool.h>
#include "ble_dm.h"

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************


uint16_t BLE_DM_DdsGetPairedDevice(uint8_t devId, BLE_DM_PairedDevInfo_T *p_pairedDevInfo);
uint16_t BLE_DM_DdsSetPairedDevice(uint8_t devId, BLE_DM_PairedDevInfo_T *p_pairedDevInfo);
uint8_t BLE_DM_DdsGetFreeDeviceId();
uint8_t BLE_DM_DdsGetDeviceId(BLE_GAP_Addr_T *p_bdAddr);
uint16_t BLE_DM_DdsDeletePairedDevice(uint8_t devId);
uint16_t BLE_DM_DdsDeleteAllPairedDevice();
bool BLE_DM_DdsChkDeviceId(uint8_t devId);


#endif

/**
  @}
*/

