// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END

/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <string.h>
#include "app.h"
#include "definitions.h"
#include "app_ble.h"
#include "ble_trsps/ble_trsps.h"

//#define ENABLE_CONSOLE_PRINT

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

uint16_t conn_hdl;
DRV_HANDLE canSPIHandle = DRV_HANDLE_INVALID;

typedef struct CAN_MSG_t {
    union {
        CAN_TX_MSGOBJ txObj;
        CAN_RX_MSGOBJ rxObj;
    }msgObj;
    uint8_t can_data[MAX_DATA_BYTES];
}CAN_MSG_t;

bool ramInitialized = false;

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


void CAN_Receive_Callback(void)
{
    APP_Msg_T appCANMsg;
    appCANMsg.msgId = APP_MSG_CAN_RECV_CB;
    OSAL_QUEUE_SendISR(&appData.appQueue, &appCANMsg);
}

void APP_ReceiveMessage_Tasks()
{
    APP_Msg_T appCANMsgQueue;
    CAN_MSG_t *canMsg = (CAN_MSG_t *)&appCANMsgQueue.msgData;
    CAN_RX_FIFO_EVENT rxFlags;

    DRV_CANFDSPI_ReceiveChannelEventGet(DRV_CANFDSPI_INDEX_0, APP_RX_FIFO, &rxFlags);
    if (rxFlags & CAN_RX_FIFO_NOT_EMPTY_EVENT)
    {
        DRV_CANFDSPI_ReceiveMessageGet(DRV_CANFDSPI_INDEX_0, APP_RX_FIFO, &canMsg->msgObj.rxObj, canMsg->can_data, MAX_DATA_BYTES);
#ifdef ENABLE_CONSOLE_PRINT
        SYS_CONSOLE_PRINT("New Message Received from CAN BUS\r\nMessage ID: 0x%X, DLC: 0x%X\r\nMessage: ", canMsg->msgObj.rxObj.bF.id.SID, canMsg->msgObj.rxObj.bF.ctrl.DLC);
        for(uint8_t i = 0; i<canMsg->msgObj.rxObj.bF.ctrl.DLC; i++)
        {
            SYS_CONSOLE_PRINT(" 0x%X",canMsg->can_data[i]);
        }
        SYS_CONSOLE_PRINT("\r\n\n");
#endif        
        appCANMsgQueue.msgId = APP_MSG_BLE_TX_CAN_RX_EVT;
        OSAL_QUEUE_Send(&appData.appQueue, &appCANMsgQueue, 0);
    }
}

void APP_CANFDSPI_Init()
{
    CAN_BITTIME_SETUP selectedBitTime = CAN_500K_2M;
    
    CAN_CONFIG config;
    CAN_TX_FIFO_CONFIG txConfig;
    CAN_RX_FIFO_CONFIG rxConfig;
    REG_CiFLTOBJ fObj;
    REG_CiMASK mObj;
    
    // Reset device
    DRV_CANFDSPI_Reset(DRV_CANFDSPI_INDEX_0);

    // Enable ECC and initialize RAM
    DRV_CANFDSPI_EccEnable(DRV_CANFDSPI_INDEX_0);

    if (!ramInitialized) {
        DRV_CANFDSPI_RamInit(DRV_CANFDSPI_INDEX_0, 0xFF);
        ramInitialized = true;
    }

    // Configure device
    DRV_CANFDSPI_ConfigureObjectReset(&config);
    config.IsoCrcEnable = 1;
    config.StoreInTEF = 0;

    DRV_CANFDSPI_Configure(DRV_CANFDSPI_INDEX_0, &config);

    // Setup TX FIFO
    DRV_CANFDSPI_TransmitChannelConfigureObjectReset(&txConfig);
    txConfig.FifoSize = 7;
    txConfig.PayLoadSize = CAN_PLSIZE_8;
    txConfig.TxPriority = 1;

    DRV_CANFDSPI_TransmitChannelConfigure(DRV_CANFDSPI_INDEX_0, APP_TX_FIFO, &txConfig);

    // Setup RX FIFO
    DRV_CANFDSPI_ReceiveChannelConfigureObjectReset(&rxConfig);
    rxConfig.FifoSize = 15;
    rxConfig.PayLoadSize = CAN_PLSIZE_8;

    DRV_CANFDSPI_ReceiveChannelConfigure(DRV_CANFDSPI_INDEX_0, APP_RX_FIFO, &rxConfig);

    // Setup RX Filter
    fObj.word = 0;
    fObj.bF.SID = 0xda;
    fObj.bF.EXIDE = 0;
    fObj.bF.EID = 0x00;

    DRV_CANFDSPI_FilterObjectConfigure(DRV_CANFDSPI_INDEX_0, CAN_FILTER0, &fObj.bF);

    // Setup RX Mask
    mObj.word = 0;
    mObj.bF.MSID = 0x0;
    mObj.bF.MIDE = 1; // Only allow standard IDs
    mObj.bF.MEID = 0x0;
    DRV_CANFDSPI_FilterMaskConfigure(DRV_CANFDSPI_INDEX_0, CAN_FILTER0, &mObj.bF);

    // Link FIFO and Filter
    DRV_CANFDSPI_FilterToFifoLink(DRV_CANFDSPI_INDEX_0, CAN_FILTER0, APP_RX_FIFO, true);

    // Setup Bit Time
    DRV_CANFDSPI_BitTimeConfigure(DRV_CANFDSPI_INDEX_0, selectedBitTime, CAN_SSP_MODE_AUTO, CAN_SYSCLK_40M);

    // Setup Transmit and Receive Interrupts
    DRV_CANFDSPI_GpioModeConfigure(DRV_CANFDSPI_INDEX_0, GPIO_MODE_INT, GPIO_MODE_INT);
    DRV_CANFDSPI_TransmitChannelEventEnable(DRV_CANFDSPI_INDEX_0, APP_TX_FIFO, CAN_TX_FIFO_NOT_FULL_EVENT);
    DRV_CANFDSPI_ReceiveChannelEventEnable(DRV_CANFDSPI_INDEX_0, APP_RX_FIFO, CAN_RX_FIFO_NOT_EMPTY_EVENT);
    DRV_CANFDSPI_ModuleEventEnable(DRV_CANFDSPI_INDEX_0, /*CAN_TX_EVENT |*/ CAN_RX_EVENT);

    // Select Normal Mode
    DRV_CANFDSPI_OperationModeSelect(DRV_CANFDSPI_INDEX_0, CAN_NORMAL_MODE);
    
    CAN_STDBY_Clear();
    EIC_CallbackRegister(EIC_PIN_2, (EIC_CALLBACK)CAN_Receive_Callback, 0);
    EIC_InterruptEnable(EIC_PIN_2);
}

void PrintBtAddress(uint8_t *addr)
{
    uint8_t i;
    SYS_CONSOLE_PRINT("Addr: ");
    for(i = 0; i < GAP_MAX_BD_ADDRESS_LEN; i++)
    {
        SYS_CONSOLE_PRINT("%02X",addr[5-i]);
    }
    SYS_CONSOLE_PRINT("\r\n");
}

bool APP_TestRamAccess(void)
{
    uint8_t rxd[MAX_DATA_BYTES];
    uint8_t txd[MAX_DATA_BYTES];
    
    for (uint8_t i = 0; i < MAX_DATA_BYTES; i++)
    {
        txd[i] = rand() & 0xff;
        rxd[i] = 0xff;
    }

    // Write data to RAM
    DRV_CANFDSPI_WriteByteArray(DRV_CANFDSPI_INDEX_0, cRAMADDR_START, txd, MAX_DATA_BYTES);

    // Read data back from RAM
    DRV_CANFDSPI_ReadByteArray(DRV_CANFDSPI_INDEX_0, cRAMADDR_START, rxd, MAX_DATA_BYTES);

    // Verify
    for (uint8_t i = 0; i < MAX_DATA_BYTES; i++)
    {
        if(txd[i] != rxd[i])
        {
            // Data mismatch
            return false;
        }

    }
    return true;
}

void APP_TransmitMessageQueue(CAN_MSG_t *canMsg)
{

    uint8_t attempts = MAX_TXQUEUE_ATTEMPTS;
    CAN_TX_FIFO_EVENT txFlags;
    uint8_t tec;
    uint8_t rec;
    CAN_ERROR_STATE errorFlags;

    // Check if FIFO is not full
    do {
        DRV_CANFDSPI_TransmitChannelEventGet(DRV_CANFDSPI_INDEX_0, APP_TX_FIFO, &txFlags);
        if (attempts == 0)
        {
            DRV_CANFDSPI_ErrorCountStateGet(DRV_CANFDSPI_INDEX_0, &tec, &rec, &errorFlags);
            SYS_CONSOLE_PRINT("[CAN] Tx Failed: 0x%X\r\n",errorFlags);
            return;
        }
        attempts--;
    }
    while (!(txFlags & CAN_TX_FIFO_NOT_FULL_EVENT));

    // Load message and transmit
    uint8_t n = DRV_CANFDSPI_DlcToDataBytes(canMsg->msgObj.txObj.bF.ctrl.DLC);

    DRV_CANFDSPI_TransmitChannelLoad(DRV_CANFDSPI_INDEX_0, APP_TX_FIFO, &canMsg->msgObj.txObj, canMsg->can_data, n, true);
    GREEN_LED_Clear();
#ifdef ENABLE_CONSOLE_PRINT
    SYS_CONSOLE_PRINT("New Message Received from BLE\r\nMessage ID: 0x%X, DLC: 0x%X\r\nMessage: ", canMsg->msgObj.txObj.bF.id.SID, canMsg->msgObj.txObj.bF.ctrl.DLC);
    for(uint8_t i = 0; i<canMsg->msgObj.txObj.bF.ctrl.DLC; i++)
    {
        SYS_CONSOLE_PRINT(" 0x%X",canMsg->can_data[i]);
    }
    SYS_CONSOLE_PRINT("\r\n[CAN] TX Done\r\n");
#endif
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;


    appData.appQueue = xQueueCreate( 64, sizeof(APP_Msg_T) );
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    APP_Msg_T    appMsg[1];
    APP_Msg_T   *p_appMsg;
    p_appMsg=appMsg;

    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            bool appInitialized = true;
            //appData.appQueue = xQueueCreate( 10, sizeof(APP_Msg_T) );
            
            DRV_SPI_TRANSFER_SETUP setup;
            canSPIHandle = DRV_SPI_Open(DRV_SPI_INDEX_0, DRV_IO_INTENT_READWRITE);
            setup.baudRateInHz = 10000000;
            setup.clockPhase = DRV_SPI_CLOCK_PHASE_VALID_LEADING_EDGE;
            setup.clockPolarity = DRV_SPI_CLOCK_POLARITY_IDLE_LOW;
            setup.dataBits = DRV_SPI_DATA_BITS_8;
            setup.chipSelect = GPIO_PIN_RA9;
            setup.csPolarity = DRV_SPI_CS_POLARITY_ACTIVE_LOW;
            DRV_SPI_TransferSetup ( canSPIHandle, &setup );
            
            APP_BleStackInit();
            APP_CANFDSPI_Init();

            SYS_CONSOLE_MESSAGE("BLE - CAN Peripheral Application\r\n");
            BLE_GAP_SetAdvEnable(true, 0);
            if (appInitialized)
            {
                appData.state = APP_STATE_TEST_RAM;
            }
            break;
        }
        case APP_STATE_TEST_RAM:
        {
            if(APP_TestRamAccess())
            {
                SYS_CONSOLE_PRINT("RAM Test: Passed\r\n");
            }
            else
            {
                SYS_CONSOLE_PRINT("RAM Test: Failed\r\n");
            }
            appData.state = APP_STATE_SERVICE_TASKS;
            break;
        }
        case APP_STATE_SERVICE_TASKS:
        {
            if (OSAL_QUEUE_Receive(&appData.appQueue, &appMsg, OSAL_WAIT_FOREVER))
            {
                if(p_appMsg->msgId==APP_MSG_BLE_STACK_EVT)
                {
                    // Pass BLE Stack Event Message to User Application for handling
                    APP_BleStackEvtHandler((STACK_Event_T *)p_appMsg->msgData);
                }
                else if(p_appMsg->msgId==APP_MSG_BLE_STACK_LOG)
                {
                    // Pass BLE LOG Event Message to User Application for handling
                    APP_BleStackLogHandler((BT_SYS_LogEvent_T *)p_appMsg->msgData);
                }
                else if (p_appMsg->msgId==APP_MSG_CAN_RECV_CB)
                {
                    BLUE_LED_Set();
                    APP_ReceiveMessage_Tasks();
                }
                else if(p_appMsg->msgId==APP_MSG_BLE_TX_CAN_RX_EVT)
                {
                    BLUE_LED_Clear();
                    CAN_MSG_t *canMsg = (CAN_MSG_t *)&p_appMsg->msgData;
                    uint8_t size = sizeof(CAN_RX_MSGOBJ) + canMsg->msgObj.rxObj.bF.ctrl.DLC;
                    BLE_TRSPS_SendData(conn_hdl, size, p_appMsg->msgData);
                }
                else if (p_appMsg->msgId==APP_MSG_BLE_RX_CAN_TX_EVT)
                {
                    GREEN_LED_Set();
                    CAN_MSG_t *canMsg = (CAN_MSG_t *)&p_appMsg->msgData[1];
                    APP_TransmitMessageQueue(canMsg);
                }
            }
            break;
        }

        /* TODO: implement your application state machine.*/


        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}


/*******************************************************************************
 End of File
 */
