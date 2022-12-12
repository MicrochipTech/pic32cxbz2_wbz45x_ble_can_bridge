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
  Error Code Definition Header File

  Company:
    Microchip Technology Inc.

  File Name:
    mba_error_desf.h

  Summary:
    This file contains the definitions of error codes.

  Description:
    This file contains the definitions of error codes.
 *******************************************************************************/



#ifndef MBA_ERROR_DEFS_H
#define MBA_ERROR_DEFS_H

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************
/**@addtogroup STACK_DEFINES Defines
 * @{ */
 
/**@defgroup STACK_ERR_CODE Error code definitions
 * @brief The definition of STACK API result
 * @{ */
#define MBA_RES_SUCCESS                         0x0000                                  /**< Execution successfully. */
#define MBA_RES_FAIL                            0x0001                                  /**< Execution fail. */
#define MBA_RES_OOM                             0x0002                                  /**< Out of memory. */
#define MBA_RES_INVALID_PARA                    0x0003                                  /**< Invalid parameters. */
#define MBA_RES_NO_RESOURCE                     0x0004                                  /**< No resource. */
#define MBA_RES_BAD_STATE                       0x0005                                  /**< Bad State. */
#define MBA_RES_PENDING_DUE_TO_SECURITY         0x0006                                  /**< Pending the request due to security process. */
#define MBA_RES_BUSY                            0x0007                                  /**< Execution fail due to stack is busy. */

#define MBA_RES_UNKNOWN_CONN_ID                 0x0102                                  /**< Unknown connection identifier. */
#define MBA_RES_CONN_ALREADY_EXISTS             0x010B                                  /**< Connection already exists. */
#define MBA_RES_COMMAND_DISALLOWED              0x010C                                  /**< Command disallowed. */
#define MBA_RES_UNSUPPORT_REMOTE_FEATURE        0x011A                                  /**< Unsupported remote feature. */
#define MBA_RES_UNKNOWN_ADV_ID                  0x0142                                  /**< Unknown advertising identifier. */
/** @} */

/**@} */ //STACK_DEFINES
#endif
