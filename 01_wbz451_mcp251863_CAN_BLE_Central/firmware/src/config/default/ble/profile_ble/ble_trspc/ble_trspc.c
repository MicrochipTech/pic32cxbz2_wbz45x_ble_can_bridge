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
  BLE Transparent Client Profile Source File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_trspc.c

  Summary:
    This file contains the BLE Transparent Client functions for application user.

  Description:
    This file contains the BLE Transparent Client functions for application user.
 *******************************************************************************/


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "osal/osal_freertos.h"
#include "mba_error_defs.h"
#include "ble_gap.h"
#include "gatt.h"
#include "ble_util/mw_assert.h"
#include "ble_util/byte_stream.h"
#include "ble_trspc/ble_trspc.h"


// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************

/**@defgroup BLE_TRSPC_CCCD BLE_TRSPC_CCCD
 * @brief The definition of Client Characteristic Configuration Descriptor
 * @{ */
#define BLE_TRSPC_CCCD_DISABLE                  0x0000         /**< Definition of Client Characteristic Configuration Descriptor disable. */
#define BLE_TRSPC_CCCD_NOTIFY                   NOTIFICATION   /**< Definition of Client Characteristic Configuration Descriptor enable NOTIFY property. */
/** @} */

/**@defgroup BLE_TRSPC_CBFC_OPCODE BLE_TRSPC_CBFC_OPCODE
 * @brief The definition of BLE transparent credit based flow control
 * @{ */
#define BLE_TRSPC_CBFC_OPCODE_SUCCESS           0x00    /**< Definition of response for successful operation. */
#define BLE_TRSPC_CBFC_OPCODE_DL_ENABLED        0x14    /**< Definition of Op Code for Credit Based Flow Control Protocol, Enable CBFC downlink. */
#define BLE_TRSPC_CBFC_OPCODE_UL_ENABLED        0x15    /**< Definition of Op Code for Credit Based Flow Control Protocol: Enable CBFC uplink. */
/** @} */

/**@defgroup BLE_TRSPC_VENDOR_OPCODE BLE_TRSPC_VENDOR_OPCODE
 * @brief The definition of BLE transparent vendor opcodes
 * @{ */
#define BLE_TRSPC_VENDOR_OPCODE_MIN             0x20    /**< Definition of Op Code range in TRS vendor commands. */
#define BLE_TRSPC_VENDOR_OPCODE_MAX             0xFF    /**< Definition of Op Code range in TRS vendor commands. */
/** @} */

/**@defgroup BLE_TRSPC_INIT_CREDIT BLE_TRSPC_INIT_CREDIT
 * @brief The definition of initial credit value.
 * @{ */
#define BLE_TRSPC_INIT_CREDIT                   0x10     /**< Definition of initial credit */
/** @} */

/**@defgroup BLE_TRSPC_MAX_BUF BLE_TRSPC_MAX_BUF
 * @brief The definition of maximum buffer list.
 * @{ */
#define BLE_TRSPC_MAX_BUF_IN                    (BLE_TRSPC_INIT_CREDIT*BLE_TRSPC_MAX_CONN_NBR)     /**< Maximum incoming queue number */
/** @} */

/**@defgroup BLE_TRSPC_MAX_RETURN_CREDIT BLE_TRSPC_MAX_RETURN_CREDIT
 * @brief The definition of maximum return credit number.
 * @{ */
#define BLE_TRSPC_MAX_RETURN_CREDIT             (13)     /**< Maximum return credit number */
/** @} */

/**@defgroup BLE_TRSPC_CBFC_PROC BLE_TRSPC_CBFC_PROC
 * @brief The definition of CBFC procedure in connect/disconnect process.
 * @{ */
#define CBFC_PROC_IDLE                          0x00    /**< CBFC procdure: Idle. */
#define CBFC_PROC_ENABLE_SESSION                0x01    /**< CBFC procdure: Enable Control Point CCCD. */
#define CBFC_PROC_ENABLE_TCP_CCCD               0x02    /**< CBFC procdure: Enable TCP CCCD. */
#define CBFC_PROC_ENABLE_TDD_CBFC               0x03    /**< CBFC procdure: Enable TDD CBFC. */
#define CBFC_PROC_ENABLE_TUD_CCCD               0x04    /**< CBFC procdure: Enable TUD CCCD. */
#define CBFC_PROC_DISABLE_TUD_CCCD              0x05    /**< CBFC procdure: Disable TUD CCCD. */
/** @} */

/**@defgroup BLE_TRSPC_VENCOM_PROC BLE_TRSPC_VENCOM_PROC
 * @brief The definition of vendor command response procedure.
 * @{ */
#define VENCOM_PROC_IDLE                        0x00    /**< Vendor command response procdure: Idle. */
#define VENCOM_PROC_ENABLE                      0x01    /**< Vendor command response procdure: Enable. */
/** @} */

/**@defgroup BLE_TRSPC_CBFC_CONFIG BLE_TRSPC_CBFC_CONFIG
 * @brief The definition of credit base flow control configuration.
 * @{ */
#define BLE_TRSPC_CBFC_DISABLED                 0x00    /**< Definition of ble transparent service credit based downlink/uplink disable. */
#define BLE_TRSPC_CBFC_DL_ENABLED               0x01    /**< Definition of ble transparent service credit based downlink enable. */
#define BLE_TRSPC_CBFC_UL_ENABLED               0x02    /**< Definition of ble transparent service credit based uplink enable. */
/** @} */

/**@defgroup BLE_TRSPC_CP_STATUS BLE_TRSPC_CP_STATUS
 * @brief The definition of BLE transparent service control point status.
 * @{ */
#define BLE_TRSPC_CP_STATUS_DISABLED            0x00    /**< Transparent control point CCCD is disabled. */
#define BLE_TRSPC_CP_STATUS_ENABLED             0x80    /**< Transparent control point CCCD is enabled (Notify). */
/** @} */

/**@defgroup BLE_TRSPC_UUID BLE_TRSPC_UUID
 * @brief The definition of UUID in TRS
 * @{ */
#define UUID_MCHP_TRANS_SVC                     0x55,0xE4,0x05,0xD2,0xAF,0x9F,0xA9,0x8F,0xE5,0x4A,0x7D,0xFE,0x43,0x53,0x53,0x49         /**< Definition of MCHP proprietary service UUID in little endian. */
#define UUID_MCHP_CHAR_TUD                      0x16,0x96,0x24,0x47,0xC6,0x23,0x61,0xBA,0xD9,0x4B,0x4D,0x1E,0x43,0x53,0x53,0x49         /**< Definition of MCHP Transparent TUD characteristic UUID in little endian. */
#define UUID_MCHP_CHAR_TDD                      0xB3,0x9B,0x72,0x34,0xBE,0xEC,0xD4,0xA8,0xF4,0x43,0x41,0x88,0x43,0x53,0x53,0x49         /**< Definition of MCHP Transparent TDD characteristic UUID in little endian. */
#define UUID_MCHP_CHAR_TCP                      0x7e,0x3b,0x07,0xff,0x1c,0x51,0x49,0x2f,0xb3,0x39,0x8a,0x4c,0x43,0x53,0x53,0x49         /**< Definition of MCHP Transparent TCP characteristic UUID in little endian. */
/** @} */

/**@brief Enumeration type of BLE transparent profile characteristics. */
typedef enum BLE_TRSPC_CharIndex_T
{
    TRSPC_INDEX_CHARTUD = 0x00,         /**< Index of transparent transparent Uplink Data Characteristic. */
    TRSPC_INDEX_CHARTUDCCCD,            /**< Index of transparent Uplink Data Characteristic CCCD. */
    TRSPC_INDEX_CHARTDD,                /**< Index of transparent transparent Downlink Data Characteristic. */
    TRSPC_INDEX_CHARTCP,                /**< Index of transparent Control Point characteristic. */
    TRSPC_INDEX_CHARTCPCCCD,            /**< Index of transparent Control Point CCCD. */
    TRSPC_CHAR_NUM                      /**< Total number of TRS characteristics. */
}BLE_TRSPC_CharIndex_T;

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

/**@brief The structure contains information about BLE transparent profile packetIn. */
typedef struct BLE_TRSPC_PacketList_T
{
    uint16_t                   length;                  /**< Data length. */
    uint8_t                    *p_packet;               /**< Pointer to the TX/RX data buffer */
} BLE_TRSPC_PacketList_T;

/**@brief The structure contains information about packet input queue format of BLE transparent profile. */
typedef struct BLE_TRSPC_QueueIn_T
{
    uint8_t                    usedNum;                    /**< The number of data list of packetIn buffer. */
    uint8_t                    writeIndex;                 /**< The Index of data, written in packet buffer. */
    uint8_t                    readIndex;                  /**< The Index of data, read in packet buffer. */
    BLE_TRSPC_PacketList_T     packetList[BLE_TRSPC_INIT_CREDIT];  /**< Written in packet buffer. @ref BLE_TRSPC_PacketList_T.*/  
} BLE_TRSPC_QueueIn_T;

/**@brief The structure contains information about BLE transparent profile connection parameters for recording connection information. */
typedef struct BLE_TRSPC_ConnList_T
{
    uint8_t                     trsState;               /**< BLE transparent service current state. @ref BLE_TRSPC_STATUS.*/
    uint8_t                     connIndex;
    uint16_t                    connHandle;             /**< Connection handle associated with this connection. */
    uint16_t                    attMtu;                 /**< Record the current connection MTU size. */
    uint8_t                     cbfcConfig;             /**< Credit based flow control usage of uplink/downlink. */
    uint8_t                     cbfcProcedure;          /**< Record ongoing credit based flow control configuration procedure. */
    uint8_t                     localCredit;            /**< Credit number of TRS downlink (Client to Server). */
    uint8_t                     peerCredit;             /**< Credit number of TRS uplink (Server to Client). */
    uint8_t                     vendorCmdProc;          /**< Vendor command reponse procedure. */
    BLE_TRSPC_QueueIn_T         inputQueue;             /**< Input queue to store Rx packets. */
    uint8_t                     cbfcRetryProcedure;     /**< Record credit based flow control configuration procedure for retry used. */
    uint8_t                     sessionReqAuth;         /**< Data Session need authenticated. */
} BLE_TRSPC_ConnList_T;

// *****************************************************************************
// *****************************************************************************
// Section: Local Variables
// *****************************************************************************
// *****************************************************************************
static BLE_TRSPC_EventCb_T      bleTrspcProcess;
static BLE_TRSPC_ConnList_T     s_trspcConnList[BLE_TRSPC_MAX_CONN_NBR];
static BLE_DD_CharInfo_T        s_trsCharInfoList[BLE_TRSPC_MAX_CONN_NBR][TRSPC_CHAR_NUM];

static const uint8_t            discSvcUuid[] =     {UUID_MCHP_TRANS_SVC};

static const ATT_Uuid_T         discCharTud =       { {UUID_MCHP_CHAR_TUD}, ATT_UUID_LENGTH_16 };
static const ATT_Uuid_T         discCharTudCccd =   { {UINT16_TO_BYTES(UUID_DESCRIPTOR_CLIENT_CHAR_CONFIG)}, ATT_UUID_LENGTH_2 };
static const ATT_Uuid_T         discCharTdd =       { {UUID_MCHP_CHAR_TDD}, ATT_UUID_LENGTH_16 };
static const ATT_Uuid_T         discCharTcp =       { {UUID_MCHP_CHAR_TCP}, ATT_UUID_LENGTH_16 };
static const ATT_Uuid_T         discCharTcpCccd =   { {UINT16_TO_BYTES(UUID_DESCRIPTOR_CLIENT_CHAR_CONFIG)}, ATT_UUID_LENGTH_2 };

static BLE_DD_DiscChar_T        trsTud =            { &discCharTud, 0 };
static BLE_DD_DiscChar_T        trsTudCccd =        { &discCharTudCccd, CHAR_SET_DESCRIPTOR };
static BLE_DD_DiscChar_T        trsTdd =            { &discCharTdd, 0 };
static BLE_DD_DiscChar_T        trsTcp =            { &discCharTcp, 0 };
static BLE_DD_DiscChar_T        trsTcpCccd =        { &discCharTcpCccd, CHAR_SET_DESCRIPTOR };

static BLE_DD_DiscChar_T        *trsDiscCharList[] =
{
    &trsTud,                    /* Transparent Uplink Data Characteristic */
    &trsTudCccd,                /* Transparent Uplink Data Characteristic CCCD */
    &trsTdd,                    /* Transparent Downlink Data Characteristic */
    &trsTcp,                    /* Transparent Control Point Characteristic */
    &trsTcpCccd                 /* Transparent Control Point Characteristic CCCD*/
};

static BLE_DD_CharList_T        s_trsCharList[BLE_TRSPC_MAX_CONN_NBR];

MW_ASSERT((BLE_TRSPC_MAX_CONN_NBR*BLE_TRSPC_INIT_CREDIT)==BLE_TRSPC_MAX_BUF_IN);

// *****************************************************************************
// *****************************************************************************
// Section: Functions
// *****************************************************************************
// *****************************************************************************

static void ble_trspc_ProcessQueuedTask(void);
static void ble_trspc_OnLinkEncrypted(uint16_t connHandle);

static void ble_trspc_InitConnList(BLE_TRSPC_ConnList_T *p_conn)
{
    memset((uint8_t *)p_conn, 0, sizeof(BLE_TRSPC_ConnList_T));
    p_conn->attMtu= BLE_ATT_DEFAULT_MTU_LEN;
}

static BLE_TRSPC_ConnList_T *ble_trspc_GetConnListByHandle(uint16_t connHandle)
{
    uint8_t i;

    for(i=0; i<BLE_TRSPC_MAX_CONN_NBR; i++)
    {
        if (s_trspcConnList[i].connHandle == connHandle)
        {
            return &s_trspcConnList[i];
        }
    }

    return NULL;
}

static BLE_TRSPC_ConnList_T *ble_trspc_GetFreeConnList()
{
    uint8_t i;

    for(i=0; i<BLE_TRSPC_MAX_CONN_NBR; i++)
    {
        if (s_trspcConnList[i].connHandle == 0)
        {
            s_trspcConnList[i].connIndex = i;
            return &s_trspcConnList[i];
        }
    }

    return NULL;
}

static void ble_trspc_InitCharList(BLE_DD_CharList_T *p_charList, uint8_t connIndex)
{
    uint8_t i;

    p_charList->connHandle = 0;
    p_charList->p_charInfo = (BLE_DD_CharInfo_T *) &(s_trsCharInfoList[connIndex]);

    for(i=0; i<TRSPC_CHAR_NUM; i++)
    {
        s_trsCharInfoList[connIndex][i].charHandle = 0;
        s_trsCharInfoList[connIndex][i].property = 0;
    }
}

static uint16_t ble_trspc_EnableControlPointCccd(BLE_TRSPC_ConnList_T *p_conn)
{
    GATTC_WriteParams_T *p_writeParams;
    uint16_t result;

    p_writeParams = OSAL_Malloc(sizeof(GATTC_WriteParams_T));
    if (p_writeParams != NULL)
    {
        p_writeParams->charHandle = s_trsCharInfoList[p_conn->connIndex][TRSPC_INDEX_CHARTCPCCCD].charHandle;
        p_writeParams->charLength = 0x02;
        U16_TO_BUF_LE(p_writeParams->charValue, BLE_TRSPC_CCCD_NOTIFY);
        p_writeParams->writeType = ATT_WRITE_REQ;
        p_writeParams->valueOffset = 0x0000;
        p_writeParams->flags = 0;

        result = GATTC_Write(p_conn->connHandle, p_writeParams);
        if (result == MBA_RES_SUCCESS)
        {
            p_conn->cbfcProcedure = CBFC_PROC_ENABLE_TCP_CCCD;
            p_conn->cbfcRetryProcedure = CBFC_PROC_IDLE;
        }
        else
        {
            p_conn->cbfcRetryProcedure = CBFC_PROC_ENABLE_SESSION;
        }
        OSAL_Free(p_writeParams);
    }
    else
    {
        result = MBA_RES_OOM;
    }

    return result;
}

static void ble_trspc_EnableDownlinkCreditBaseFlowControl(BLE_TRSPC_ConnList_T *p_conn)
{
    GATTC_WriteParams_T *p_writeParams;
    uint16_t result;

    p_writeParams = OSAL_Malloc(sizeof(GATTC_WriteParams_T));
    if (p_writeParams != NULL)
    {
        p_writeParams->charHandle = s_trsCharInfoList[p_conn->connIndex][TRSPC_INDEX_CHARTCP].charHandle;
        p_writeParams->charLength = 0x01;
        p_writeParams->charValue[0] = BLE_TRSPC_CBFC_OPCODE_DL_ENABLED;
        p_writeParams->writeType = ATT_WRITE_REQ;
        p_writeParams->valueOffset = 0x0000;
        p_writeParams->flags = 0;

        result = GATTC_Write(p_conn->connHandle, p_writeParams);
        if (result == MBA_RES_SUCCESS)
        {
            p_conn->cbfcProcedure = CBFC_PROC_ENABLE_TDD_CBFC;
            p_conn->cbfcRetryProcedure = CBFC_PROC_IDLE;
        }
        else
        {
            p_conn->cbfcRetryProcedure = CBFC_PROC_ENABLE_TCP_CCCD;
        }
        OSAL_Free(p_writeParams);
    }
}

static void ble_trspc_ClientReturnCredit(BLE_TRSPC_ConnList_T *p_conn)
{
    GATTC_WriteParams_T *p_writeParams;
    uint16_t result;

    p_writeParams = OSAL_Malloc(sizeof(GATTC_WriteParams_T));
    if (p_writeParams != NULL)
    {
        p_writeParams->charHandle = s_trsCharInfoList[p_conn->connIndex][TRSPC_INDEX_CHARTCP].charHandle;
        p_writeParams->charLength = 0x02;
        p_writeParams->charValue[0] = BLE_TRSPC_CBFC_OPCODE_UL_ENABLED;
        p_writeParams->charValue[1] = p_conn->peerCredit;
        p_writeParams->writeType = ATT_WRITE_REQ;
        p_writeParams->valueOffset = 0x0000;
        p_writeParams->flags = 0;

        result = GATTC_Write(p_conn->connHandle, p_writeParams);
        if (result == MBA_RES_SUCCESS)
        {
            p_conn->peerCredit = 0;
        }
        OSAL_Free(p_writeParams);
    }
}

static uint16_t ble_trspc_ConfigureUplinkDataCccd(BLE_TRSPC_ConnList_T *p_conn, uint16_t cccdValue)
{
    GATTC_WriteParams_T *p_writeParams;
    uint16_t result;

    p_writeParams = OSAL_Malloc(sizeof(GATTC_WriteParams_T));
    if (p_writeParams != NULL)
    {
        p_writeParams->charHandle = s_trsCharInfoList[p_conn->connIndex][TRSPC_INDEX_CHARTUDCCCD].charHandle;
        p_writeParams->charLength = sizeof(cccdValue);
        U16_TO_BUF_LE(p_writeParams->charValue, cccdValue);
        p_writeParams->writeType = ATT_WRITE_REQ;
        p_writeParams->valueOffset = 0x0000;
        p_writeParams->flags = 0;

        result = GATTC_Write(p_conn->connHandle, p_writeParams);
        if (result == MBA_RES_SUCCESS)
        {
            if (cccdValue == BLE_TRSPC_CCCD_NOTIFY)
            {
                p_conn->cbfcProcedure = CBFC_PROC_ENABLE_TUD_CCCD;
            }
            else
            {
                p_conn->cbfcProcedure = CBFC_PROC_DISABLE_TUD_CCCD;
            }
            p_conn->cbfcRetryProcedure = CBFC_PROC_IDLE;
        }
        else
        {
            p_conn->cbfcRetryProcedure = CBFC_PROC_ENABLE_TDD_CBFC;
        }
        OSAL_Free(p_writeParams);
    }
    else
    {
        result = MBA_RES_OOM;
    }

    return result;
}

uint16_t ble_trspc_EnableDataSession(uint16_t connHandle, uint8_t cbfcConfig)
{
    BLE_TRSPC_ConnList_T *p_conn;
    uint16_t result;

    p_conn = ble_trspc_GetConnListByHandle(connHandle);

    if (p_conn != NULL)
    {
        p_conn->cbfcConfig |= cbfcConfig;

        if (p_conn->cbfcConfig&BLE_TRSPC_CBFC_DL_ENABLED)
        {
            result = ble_trspc_EnableControlPointCccd(p_conn);
        }
        else
        {
            p_conn->trsState |= BLE_TRSPC_DL_STATUS_NONCBFCENABLED;
            if (p_conn->cbfcConfig&BLE_TRSPC_CBFC_UL_ENABLED)
            {
                result = ble_trspc_ConfigureUplinkDataCccd(p_conn, BLE_TRSPC_CCCD_NOTIFY);
            }
            else
            {
                result = MBA_RES_INVALID_PARA;
            }
        }
    }
    else
    {
        result = MBA_RES_FAIL;
    }

    return result;
}

static void ble_trspc_RcvData(BLE_TRSPC_ConnList_T *p_conn, uint16_t receivedLen, uint8_t *p_receivedValue)
{
    if (p_conn->inputQueue.usedNum < BLE_TRSPC_INIT_CREDIT)
    {
        BLE_TRSPC_Event_T evtPara;
        uint8_t *p_buffer = NULL;

        memset((uint8_t *) &evtPara, 0, sizeof(evtPara));
        p_buffer = OSAL_Malloc(receivedLen);

        if (p_buffer == NULL)
        {
            evtPara.eventId = BLE_TRSPC_EVT_ERR_NO_MEM;
            if (bleTrspcProcess)
            {
                bleTrspcProcess(&evtPara);
            }
            return;
        }

        memcpy(p_buffer, p_receivedValue, receivedLen);
        p_conn->inputQueue.packetList[p_conn->inputQueue.writeIndex].length = receivedLen;
        p_conn->inputQueue.packetList[p_conn->inputQueue.writeIndex].p_packet = p_buffer;
        p_conn->inputQueue.writeIndex++;
        if (p_conn->inputQueue.writeIndex >= BLE_TRSPC_INIT_CREDIT)
            p_conn->inputQueue.writeIndex = 0;

        p_conn->inputQueue.usedNum++;

        evtPara.eventId = BLE_TRSPC_EVT_RECEIVE_DATA;
        evtPara.eventField.onReceiveData.connHandle = p_conn->connHandle;
        if (bleTrspcProcess)
        {
            bleTrspcProcess(&evtPara);
        }
    }
}

static void ble_trspc_ProcGattWriteResp(BLE_TRSPC_ConnList_T *p_conn)
{
    BLE_TRSPC_Event_T evtPara;

    memset((uint8_t *) &evtPara, 0, sizeof(evtPara));

    switch (p_conn->cbfcProcedure)
    {
        case CBFC_PROC_ENABLE_SESSION:
        {
            ble_trspc_EnableControlPointCccd(p_conn);
        }
        break;
        case CBFC_PROC_ENABLE_TCP_CCCD:
        {
            p_conn->cbfcProcedure = CBFC_PROC_IDLE;
            p_conn->trsState |= BLE_TRSPC_CP_STATUS_ENABLED;
            ble_trspc_EnableDownlinkCreditBaseFlowControl(p_conn);
        }
        break;

        case CBFC_PROC_ENABLE_TDD_CBFC:
        {
            p_conn->cbfcProcedure = CBFC_PROC_IDLE;
            if (p_conn->cbfcConfig&BLE_TRSPC_CBFC_UL_ENABLED)
            {
                ble_trspc_ConfigureUplinkDataCccd(p_conn, BLE_TRSPC_CCCD_NOTIFY);
            }
        }
        break;

        case CBFC_PROC_ENABLE_TUD_CCCD:
        {
            p_conn->cbfcProcedure = CBFC_PROC_IDLE;
            p_conn->trsState |= BLE_TRSPC_UL_STATUS_CBFCENABLED;
            /* Initialize and give credits after connected */
            p_conn->peerCredit = BLE_TRSPC_INIT_CREDIT;
            ble_trspc_ClientReturnCredit(p_conn);

            if (bleTrspcProcess)
            {
                evtPara.eventId = BLE_TRSPC_EVT_UL_STATUS;
                evtPara.eventField.onUplinkStatus.connHandle = p_conn->connHandle;
                evtPara.eventField.onUplinkStatus.status = BLE_TRSPC_UL_STATUS_CBFCENABLED;
                bleTrspcProcess(&evtPara);
            }
        }
        break;

        case CBFC_PROC_DISABLE_TUD_CCCD:
        {
            p_conn->cbfcProcedure = CBFC_PROC_IDLE;
            p_conn->trsState &= (~BLE_TRSPC_UL_STATUS_CBFCENABLED);
            if (bleTrspcProcess)
            {
                evtPara.eventId = BLE_TRSPC_EVT_UL_STATUS;
                evtPara.eventField.onUplinkStatus.connHandle = p_conn->connHandle;
                evtPara.eventField.onUplinkStatus.status = BLE_TRSPC_UL_STATUS_DISABLED;
                bleTrspcProcess(&evtPara);
            }

            /* Reset credit */
            p_conn->peerCredit = 0;
        }
        break;

        default:
        {
            if (p_conn->vendorCmdProc)
            {
                p_conn->vendorCmdProc = VENCOM_PROC_IDLE;
                if (bleTrspcProcess)
                {
                    evtPara.eventId = BLE_TRSPC_EVT_VENDOR_CMD_RSP;
                    evtPara.eventField.onVendorCmdRsp.connHandle = p_conn->connHandle;
                    bleTrspcProcess(&evtPara);
                }
            }
        }
        break;
    }
}

static void ble_trspc_ProcGattNotification(BLE_TRSPC_ConnList_T *p_conn, GATT_EvtReceiveHandleValue_T *p_event , uint16_t charHandle)
{
    BLE_TRSPC_Event_T evtPara;

    memset((uint8_t *) &evtPara, 0, sizeof(evtPara));

    if (charHandle == s_trsCharInfoList[p_conn->connIndex][TRSPC_INDEX_CHARTUD].charHandle)
    {
        ble_trspc_RcvData(p_conn, p_event->receivedLength, p_event->receivedValue);
    }
    else if (charHandle == s_trsCharInfoList[p_conn->connIndex][TRSPC_INDEX_CHARTCP].charHandle)
    {
        /* Opcode: response */
        if (p_event->receivedValue[0] == BLE_TRSPC_CBFC_OPCODE_SUCCESS)
        {
            /* Request opcode of response */
            if (p_event->receivedValue[1] == BLE_TRSPC_CBFC_OPCODE_DL_ENABLED)
            {
                p_conn->trsState |= BLE_TRSPC_DL_STATUS_CBFCENABLED;
                BUF_BE_TO_U16(&p_conn->attMtu, &p_event->receivedValue[2]);
                p_conn->localCredit += p_event->receivedValue[4];

                if (bleTrspcProcess)
                {
                    evtPara.eventId = BLE_TRSPC_EVT_DL_STATUS;
                    evtPara.eventField.onDownlinkStatus.connHandle = p_conn->connHandle;
                    evtPara.eventField.onDownlinkStatus.status = BLE_TRSPC_DL_STATUS_CBFCENABLED;
                    evtPara.eventField.onDownlinkStatus.currentCreditNumber = p_conn->localCredit;
                    bleTrspcProcess(&evtPara);
                }
            }
        }
        else if ((p_event->receivedValue[0]>=BLE_TRSPC_VENDOR_OPCODE_MIN) && (p_event->receivedValue[0]<=BLE_TRSPC_VENDOR_OPCODE_MAX))
        {
            if (bleTrspcProcess)
            {
                evtPara.eventId = BLE_TRSPC_EVT_VENDOR_CMD;
                evtPara.eventField.onVendorCmd.connHandle = p_conn->connHandle;
                evtPara.eventField.onVendorCmd.payloadLength = p_event->receivedLength;
                evtPara.eventField.onVendorCmd.p_payLoad = p_event->receivedValue;

                bleTrspcProcess(&evtPara);
            }
        }
    }
}

void ble_trspc_GattEventProcess(GATT_Event_T *p_event)
{
    BLE_TRSPC_ConnList_T *p_conn = NULL;

    switch (p_event->eventId)
    {
        case ATT_EVT_TIMEOUT:
        {
            /* Reset link information */
        }
        break;

        case ATT_EVT_UPDATE_MTU:
        {
            p_conn = ble_trspc_GetConnListByHandle(p_event->eventField.onUpdateMTU.connHandle);
            if (p_conn != NULL)
            {
                p_conn->attMtu = p_event->eventField.onUpdateMTU.exchangedMTU;
            }
        }
        break;

        case GATTC_EVT_ERROR_RESP:
            p_conn = ble_trspc_GetConnListByHandle(p_event->eventField.onError.connHandle);
            if (p_conn != NULL)
            {
                if (p_event->eventField.onError.reqOpcode == ATT_WRITE_REQ &&
                    p_event->eventField.onError.errCode == ATT_ERRCODE_INSUFFICIENT_AUTHENTICATION &&
                    p_event->eventField.onError.attrHandle == s_trsCharInfoList[p_conn->connIndex][TRSPC_INDEX_CHARTCPCCCD].charHandle)
                {
                    p_conn->sessionReqAuth = 1;
                }
            }
            break;

        case GATTC_EVT_WRITE_RESP:
        {
            p_conn = ble_trspc_GetConnListByHandle(p_event->eventField.onWriteResp.connHandle);

            if (p_conn != NULL)
            {
                if (p_event->eventField.onWriteResp.charHandle != s_trsCharInfoList[p_conn->connIndex][TRSPC_INDEX_CHARTUD].charHandle &&
                    p_event->eventField.onWriteResp.charHandle != s_trsCharInfoList[p_conn->connIndex][TRSPC_INDEX_CHARTUDCCCD].charHandle &&
                    p_event->eventField.onWriteResp.charHandle != s_trsCharInfoList[p_conn->connIndex][TRSPC_INDEX_CHARTDD].charHandle &&
                    p_event->eventField.onWriteResp.charHandle != s_trsCharInfoList[p_conn->connIndex][TRSPC_INDEX_CHARTCP].charHandle &&
                    p_event->eventField.onWriteResp.charHandle != s_trsCharInfoList[p_conn->connIndex][TRSPC_INDEX_CHARTCPCCCD].charHandle)
                {
                    break;
                }

                ble_trspc_ProcGattWriteResp(p_conn);
            }
        }
        break;

        case GATTC_EVT_HV_NOTIFY:
        {
            p_conn = ble_trspc_GetConnListByHandle(p_event->eventField.onNotification.connHandle);

            if (p_conn != NULL)
            {
                ble_trspc_ProcGattNotification(p_conn, &p_event->eventField.onNotification, p_event->eventField.onNotification.charHandle);
            }
        }
        break;

        case GATTC_EVT_PROTOCOL_AVAILABLE:
            p_conn = ble_trspc_GetConnListByHandle(p_event->eventField.onClientProtocolAvailable.connHandle);
            if (p_conn != NULL && p_conn->cbfcRetryProcedure)
            {
                p_conn->cbfcProcedure = p_conn->cbfcRetryProcedure;
                p_conn->cbfcRetryProcedure = CBFC_PROC_IDLE;
                ble_trspc_ProcGattWriteResp(p_conn);
            }
            else if (p_conn != NULL)
            {
                ble_trspc_ProcessQueuedTask();
            }
        break;

        default:
            break;
    }
}

static bool ble_trspc_CheckQueuedTask(void)
{
    uint8_t i;

    for (i = 0; i < BLE_TRSPC_MAX_CONN_NBR; i++)
    {
        if ((s_trspcConnList[i].connHandle != 0) && (s_trspcConnList[i].peerCredit >= BLE_TRSPC_MAX_RETURN_CREDIT))
        {
            return true;
        }
    }

    return false;
}

static void ble_trspc_ProcessQueuedTask(void)
{
    uint8_t i;

    for(i = 0; i < BLE_TRSPC_MAX_CONN_NBR; i++)
    {
        if (s_trspcConnList[i].connHandle != 0)
        {
            if (s_trspcConnList[i].peerCredit >= BLE_TRSPC_MAX_RETURN_CREDIT)
                ble_trspc_ClientReturnCredit(&s_trspcConnList[i]);
        }
    }
}

void ble_trspc_GapEventProcess(BLE_GAP_Event_T *p_event)
{
    BLE_TRSPC_ConnList_T *p_conn = NULL;

    switch(p_event->eventId)
    {
        case BLE_GAP_EVT_CONNECTED:
        {
            if ((p_event->eventField.evtConnect.status == GAP_STATUS_SUCCESS))
            {
                p_conn = ble_trspc_GetFreeConnList();
                if (p_conn != NULL)
                {
                    p_conn->connHandle = p_event->eventField.evtConnect.connHandle;
                }
            }
        }
        break;

        case BLE_GAP_EVT_DISCONNECTED:
        {
            p_conn = ble_trspc_GetConnListByHandle(p_event->eventField.evtDisconnect.connHandle);
            if (p_conn != NULL)
            {
                // Flush all queued data.
                while (p_conn->inputQueue.usedNum > 0)
                {
                    if (p_conn->inputQueue.packetList[p_conn->inputQueue.readIndex].p_packet)
                    {
                        OSAL_Free(p_conn->inputQueue.packetList[p_conn->inputQueue.readIndex].p_packet);
                        p_conn->inputQueue.packetList[p_conn->inputQueue.readIndex].p_packet = NULL;
                    }

                    p_conn->inputQueue.readIndex++;
                    if (p_conn->inputQueue.readIndex >= BLE_TRSPC_INIT_CREDIT)
                        p_conn->inputQueue.readIndex = 0;

                    p_conn->inputQueue.usedNum--;
                }
                ble_trspc_InitConnList(p_conn);
            }
        }
        break;

        case BLE_GAP_EVT_TX_BUF_AVAILABLE:
        {
            ble_trspc_ProcessQueuedTask();
        }
        break;

        case BLE_GAP_EVT_ENCRYPT_STATUS:
        {
            if (p_event->eventField.evtEncryptStatus.status == BLE_GAP_ENCRYPT_SUCCESS)
            {
                ble_trspc_OnLinkEncrypted(p_event->eventField.evtEncryptStatus.connHandle);
            }
        }
        break;

        default:
        break;
    }
}

static void ble_trspc_OnLinkEncrypted(uint16_t connHandle)
{
    uint8_t i;
    BLE_TRSPC_ConnList_T *p_conn;

    p_conn = ble_trspc_GetConnListByHandle(connHandle);
    
    /* Check if TRS characteristics are found or not. */
    for (i=0; i<BLE_TRSPC_MAX_CONN_NBR; i++)
    {
        if (s_trsCharList[i].connHandle == connHandle)
        {
            /* By checking the discovered handles exist or not. */
            if (s_trsCharList[i].p_charInfo[TRSPC_INDEX_CHARTCP].charHandle != 0)
            {
                if (p_conn != NULL && p_conn->sessionReqAuth == 1)
                {
                    ble_trspc_EnableDataSession(connHandle, (BLE_TRSPC_CBFC_DL_ENABLED|BLE_TRSPC_CBFC_UL_ENABLED));
                }
            }
            break;
        }
    }
}


void BLE_TRSPC_EventRegister(BLE_TRSPC_EventCb_T bleTranCliHandler)
{
    bleTrspcProcess = bleTranCliHandler;
}

uint16_t BLE_TRSPC_Init()
{
    BLE_DD_DiscSvc_T trsDisc;
    uint8_t i;

    /* Reset connection information */
    for (i = 0; i < BLE_TRSPC_MAX_CONN_NBR; i++)
    {
        ble_trspc_InitConnList(&s_trspcConnList[i]);
        ble_trspc_InitCharList(&s_trsCharList[i], i);
    }

    trsDisc.svcUuid.uuidLength = ATT_UUID_LENGTH_16;
    memcpy(trsDisc.svcUuid.uuid, discSvcUuid, ATT_UUID_LENGTH_16);
    trsDisc.p_discChars = trsDiscCharList;
    trsDisc.p_charList = s_trsCharList;
    trsDisc.discCharsNum = TRSPC_CHAR_NUM;
    return BLE_DD_ServiceDiscoveryRegister(&trsDisc);
}

uint16_t BLE_TRSPC_SendVendorCommand(uint16_t connHandle, uint8_t commandID, uint8_t commandLength, uint8_t *p_commandPayload)
{
    BLE_TRSPC_ConnList_T *p_conn;
    GATTC_WriteParams_T *p_writeParams;
    uint16_t result;

    p_conn = ble_trspc_GetConnListByHandle(connHandle);
    if (p_conn == NULL)
        return MBA_RES_FAIL;

    if (!(p_conn->trsState&BLE_TRSPC_CP_STATUS_ENABLED))
    {
        return MBA_RES_FAIL;
    }

    if (commandID < BLE_TRSPC_VENDOR_OPCODE_MIN)
    {
        return MBA_RES_INVALID_PARA;
    }

    if (commandLength > (p_conn->attMtu-ATT_WRITE_HEADER_SIZE-1))
    {
        return MBA_RES_INVALID_PARA;
    }

    p_writeParams = OSAL_Malloc(sizeof(GATTC_WriteParams_T));
    if (p_writeParams != NULL)
    {
        p_writeParams->charHandle = s_trsCharInfoList[p_conn->connIndex][TRSPC_INDEX_CHARTCP].charHandle;
        p_writeParams->charLength = (commandLength+1);
        p_writeParams->charValue[0] = commandID;
        memcpy(&p_writeParams->charValue[1], p_commandPayload, commandLength);
        p_writeParams->writeType = ATT_WRITE_REQ;
        p_writeParams->valueOffset = 0x0000;
        p_writeParams->flags = 0;
        result = GATTC_Write(p_conn->connHandle, p_writeParams);
        if (result == MBA_RES_SUCCESS)
            p_conn->vendorCmdProc = VENCOM_PROC_ENABLE;
        OSAL_Free(p_writeParams);
        return result;
    }
    else
    {
        return MBA_RES_OOM;
    }
}

uint16_t BLE_TRSPC_SendData(uint16_t connHandle, uint16_t len, uint8_t *p_data)
{
    GATTC_WriteParams_T *p_writeParams;
    BLE_TRSPC_ConnList_T *p_conn;
    uint16_t result;

    p_conn = ble_trspc_GetConnListByHandle(connHandle);
    if (p_conn == NULL)
    {
        return MBA_RES_FAIL;
    }

    if ((p_conn->trsState&BLE_TRSPC_DL_STATUS_CBFCENABLED) && (p_conn->localCredit == 0))
    {
        return MBA_RES_NO_RESOURCE;
    }

    if (ble_trspc_CheckQueuedTask())
    {
        return MBA_RES_NO_RESOURCE;
    }

    if (len > (p_conn->attMtu - ATT_WRITE_HEADER_SIZE))
    {
        return MBA_RES_FAIL;
    }

    p_writeParams = OSAL_Malloc(sizeof(GATTC_WriteParams_T));

    if (p_writeParams == NULL)
    {
        return MBA_RES_OOM;
    }

    if (p_conn->trsState & BLE_TRSPC_DL_STATUS_CBFCENABLED)
    {
        p_writeParams->writeType = ATT_WRITE_CMD;
    }
    else if (p_conn->trsState & BLE_TRSPC_DL_STATUS_NONCBFCENABLED)
    {
        p_writeParams->writeType = ATT_WRITE_REQ;
    }
    else
    {
        OSAL_Free(p_writeParams);
        return MBA_RES_BAD_STATE;
    }

    p_writeParams->charHandle = s_trsCharInfoList[p_conn->connIndex][TRSPC_INDEX_CHARTDD].charHandle;
    p_writeParams->charLength = len;
    memcpy(p_writeParams->charValue, p_data, len);
    p_writeParams->valueOffset = 0;
    p_writeParams->flags = 0;
    result = GATTC_Write(connHandle, p_writeParams);
    OSAL_Free(p_writeParams);

    if (result == MBA_RES_SUCCESS)
    {
        if (p_conn->trsState & BLE_TRSPC_DL_STATUS_CBFCENABLED)
            p_conn->localCredit--;
    }

    return result;
}

void BLE_TRSPC_GetDataLength(uint16_t connHandle, uint16_t *p_dataLength)
{
    BLE_TRSPC_ConnList_T *p_conn = NULL;

    p_conn = ble_trspc_GetConnListByHandle(connHandle);
    if (p_conn)
    {
        if ((p_conn->inputQueue.usedNum) > 0)
        {
            *p_dataLength = p_conn->inputQueue.packetList[p_conn->inputQueue.readIndex].length;
        }
        else
            *p_dataLength = 0;
    }
    else
        *p_dataLength = 0;
}

uint16_t BLE_TRSPC_GetData(uint16_t connHandle, uint8_t *p_data)
{
    BLE_TRSPC_ConnList_T *p_conn = NULL;

    p_conn = ble_trspc_GetConnListByHandle(connHandle);
    if (p_conn)
    {
        if ((p_conn->inputQueue.usedNum) > 0)
        {
            if (p_conn->inputQueue.packetList[p_conn->inputQueue.readIndex].p_packet)
            {
                memcpy(p_data, p_conn->inputQueue.packetList[p_conn->inputQueue.readIndex].p_packet, 
                    p_conn->inputQueue.packetList[p_conn->inputQueue.readIndex].length);
                OSAL_Free(p_conn->inputQueue.packetList[p_conn->inputQueue.readIndex].p_packet);
                p_conn->inputQueue.packetList[p_conn->inputQueue.readIndex].p_packet = NULL;
            }

            p_conn->inputQueue.readIndex++;
            if (p_conn->inputQueue.readIndex >= BLE_TRSPC_INIT_CREDIT)
                p_conn->inputQueue.readIndex = 0;

            p_conn->inputQueue.usedNum --;

            if (p_conn->trsState & BLE_TRSPC_UL_STATUS_CBFCENABLED)
            {
                p_conn->peerCredit++;
                if (p_conn->peerCredit >= BLE_TRSPC_MAX_RETURN_CREDIT)
                    ble_trspc_ClientReturnCredit(p_conn);
            }

            return MBA_RES_SUCCESS;
        }
        else
            return MBA_RES_FAIL;
    }
    else
        return MBA_RES_FAIL;
}

void BLE_TRSPC_BleEventHandler(STACK_Event_T *p_stackEvent)
{
    switch (p_stackEvent->groupId)
    {
        case STACK_GRP_BLE_GAP:
        {
            ble_trspc_GapEventProcess((BLE_GAP_Event_T *)p_stackEvent->p_event);
        }
        break;

        case STACK_GRP_GATT:
        {
            ble_trspc_GattEventProcess((GATT_Event_T *)p_stackEvent->p_event);
        }
        break;

        default:
        break;
    }
}

void BLE_TRSPC_BleDdEventHandler(BLE_DD_Event_T *p_event)
{
    switch (p_event->eventId)
    {
        case BLE_DD_EVT_DISC_COMPLETE:
        {
            uint8_t i;
            BLE_TRSPC_ConnList_T *p_conn;

            /* Check if TRS characteristics are found or not. */
            for (i=0; i<BLE_TRSPC_MAX_CONN_NBR; i++)
            {
                if (s_trsCharList[i].connHandle == p_event->eventField.evtDiscResult.connHandle)
                {
                    /* By checking the discovered handles exist or not. */
                    if (s_trsCharList[i].p_charInfo[TRSPC_INDEX_CHARTCP].charHandle != 0)
                    {
                        if (bleTrspcProcess)
                        {
                            BLE_TRSPC_Event_T evtPara;

                            evtPara.eventId = BLE_TRSPC_EVT_DISC_COMPLETE;
                            evtPara.eventField.onUplinkStatus.connHandle = p_event->eventField.evtDiscResult.connHandle;
                            bleTrspcProcess(&evtPara);
                        }

                        p_conn = ble_trspc_GetConnListByHandle(p_event->eventField.evtDiscResult.connHandle);
                        if (p_conn != NULL && p_conn->sessionReqAuth == 0)
                        {
                            ble_trspc_EnableDataSession(p_event->eventField.evtDiscResult.connHandle, (BLE_TRSPC_CBFC_DL_ENABLED|BLE_TRSPC_CBFC_UL_ENABLED));
                        }
                    }
                }
            }
        }
        break;

        default:
        break;
    }
}



