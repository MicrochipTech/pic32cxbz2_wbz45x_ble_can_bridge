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
  Security Manager Middleware Header File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_dm_sm.h

  Summary:
    This file contains the Security Manager functions for 
    BLE Device Manager module internal use.

  Description:
    This file contains the Security Manager functions for 
    BLE Device Manager module internal use.
 *******************************************************************************/


/**
 * @addtogroup BLE_DM_SM BLE DM SM
 * @{
 * @brief Header file for the BLE Device Manager (ble_dm_sm) internal module.
 */
 
#ifndef BLE_DM_SM_H
#define BLE_DM_SM_H

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************

void BLE_DM_Sm(STACK_Event_T *p_stackEvent);

uint16_t BLE_DM_SmConfig(bool autoAccept);

uint16_t BLE_DM_SmPairing(uint16_t connHandle, uint8_t repairing);

void BLE_DM_SmInit();

#endif

/**
  @}
*/
