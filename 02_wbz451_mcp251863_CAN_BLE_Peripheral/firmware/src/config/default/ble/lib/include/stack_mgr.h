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
  Stack Manager Header File

  Company:
    Microchip Technology Inc.

  File Name:
    stack_mgr.h

  Summary:
    This file contains the BLE Stack functions for application user.

  Description:
    This file contains the BLE Stack functions and event for application user.
    Application shall call the "STACK_EventRegister" in the "APP_Initialize" function 
    to receive the BLE relevant events.
 *******************************************************************************/


/**
 * @addtogroup STACK_MGR STACK
 * @{
 * @brief This module defines the STACK interface to the BLE Library
 */

#ifndef STACK_MGR_H
#define STACK_MGR_H

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************

/**@addtogroup STACK_DEFINES Defines
 * @{ */
 
/**@} */ //STACK_DEFINES

/**@addtogroup STACK_ENUMS Enumerations
 * @{ */

/**@brief The definitions of stack group id*/
typedef enum STACK_GroupId_T{
    STACK_GRP_NONE,
    STACK_GRP_BLE_GAP,                      /**< Stack group: BLE GAP. */
    STACK_GRP_BLE_L2CAP,                    /**< Stack group: BLE L2CAP. */
    STACK_GRP_BLE_SMP,                      /**< Stack group: BLE SMP. */
    STACK_GRP_GATT,                         /**< Stack group: GATT. */

    STACK_GRP_END
}STACK_GroupId_T;

/**@} */ //STACK_ENUMS
// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/**@addtogroup STACK_STRUCTS Structures
 * @{ */
 
/**@brief STACK callback event. */
typedef struct STACK_Event_T
{
    STACK_GroupId_T     groupId;                    /**< Group id. See @ref STACK_GroupId_T */
    uint16_t            evtLen;                     /**< Length of the event */
    uint8_t             *p_event;                   /**< Pointer to the event field */
} STACK_Event_T;

/**@brief STACK callback type. This callback function sends STACK events to the application. */
typedef void (*STACK_EventCb_T)(STACK_Event_T *p_event);

/**@} */ //STACK_STRUCTS

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************
/**@addtogroup STACK_FUNS Functions
 * @{ */
 
/**
 *@brief Register STACK callback.
 *
 *@param[in] eventCb        Client callback function.
 *
*/
void STACK_EventRegister(STACK_EventCb_T eventCb);

/**@} */ //STACK_FUNS

#endif

/**
  @}
 */

