/*******************************************************************************
* File Name: PlayerBT1_INT.c
* Version 2.30
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
* Note:
*  Any unusual or non-standard behavior should be noted here. Other-
*  wise, this section should remain blank.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PlayerBT1.h"
#include "CyLib.h"


/***************************************
* Custom Declratations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if( (PlayerBT1_RX_ENABLED || PlayerBT1_HD_ENABLED) && \
     (PlayerBT1_RXBUFFERSIZE > PlayerBT1_FIFO_LENGTH))


    /*******************************************************************************
    * Function Name: PlayerBT1_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  PlayerBT1_rxBuffer - RAM buffer pointer for save received data.
    *  PlayerBT1_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  PlayerBT1_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  PlayerBT1_rxBufferOverflow - software overflow flag. Set to one
    *     when PlayerBT1_rxBufferWrite index overtakes
    *     PlayerBT1_rxBufferRead index.
    *  PlayerBT1_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when PlayerBT1_rxBufferWrite is equal to
    *    PlayerBT1_rxBufferRead
    *  PlayerBT1_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  PlayerBT1_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(PlayerBT1_RXISR)
    {
        uint8 readData;
        uint8 increment_pointer = 0u;
        #if(CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 */

        /* User code required at start of ISR */
        /* `#START PlayerBT1_RXISR_START` */

        /* `#END` */

        #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
            int_en = EA;
            CyGlobalIntEnable;
        #endif /* CY_PSOC3 */

        readData = PlayerBT1_RXSTATUS_REG;

        if((readData & (PlayerBT1_RX_STS_BREAK | PlayerBT1_RX_STS_PAR_ERROR |
                        PlayerBT1_RX_STS_STOP_ERROR | PlayerBT1_RX_STS_OVERRUN)) != 0u)
        {
            /* ERROR handling. */
            /* `#START PlayerBT1_RXISR_ERROR` */

            /* `#END` */
        }

        while((readData & PlayerBT1_RX_STS_FIFO_NOTEMPTY) != 0u)
        {

            #if (PlayerBT1_RXHW_ADDRESS_ENABLED)
                if(PlayerBT1_rxAddressMode == (uint8)PlayerBT1__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readData & PlayerBT1_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readData & PlayerBT1_RX_STS_ADDR_MATCH) != 0u)
                        {
                            PlayerBT1_rxAddressDetected = 1u;
                        }
                        else
                        {
                            PlayerBT1_rxAddressDetected = 0u;
                        }
                    }

                    readData = PlayerBT1_RXDATA_REG;
                    if(PlayerBT1_rxAddressDetected != 0u)
                    {   /* store only addressed data */
                        PlayerBT1_rxBuffer[PlayerBT1_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* without software addressing */
                {
                    PlayerBT1_rxBuffer[PlayerBT1_rxBufferWrite] = PlayerBT1_RXDATA_REG;
                    increment_pointer = 1u;
                }
            #else  /* without addressing */
                PlayerBT1_rxBuffer[PlayerBT1_rxBufferWrite] = PlayerBT1_RXDATA_REG;
                increment_pointer = 1u;
            #endif /* End SW_DETECT_TO_BUFFER */

            /* do not increment buffer pointer when skip not adderessed data */
            if( increment_pointer != 0u )
            {
                if(PlayerBT1_rxBufferLoopDetect != 0u)
                {   /* Set Software Buffer status Overflow */
                    PlayerBT1_rxBufferOverflow = 1u;
                }
                /* Set next pointer. */
                PlayerBT1_rxBufferWrite++;

                /* Check pointer for a loop condition */
                if(PlayerBT1_rxBufferWrite >= PlayerBT1_RXBUFFERSIZE)
                {
                    PlayerBT1_rxBufferWrite = 0u;
                }
                /* Detect pre-overload condition and set flag */
                if(PlayerBT1_rxBufferWrite == PlayerBT1_rxBufferRead)
                {
                    PlayerBT1_rxBufferLoopDetect = 1u;
                    /* When Hardware Flow Control selected */
                    #if(PlayerBT1_FLOW_CONTROL != 0u)
                    /* Disable RX interrupt mask, it will be enabled when user read data from the buffer using APIs */
                        PlayerBT1_RXSTATUS_MASK_REG  &= (uint8)~PlayerBT1_RX_STS_FIFO_NOTEMPTY;
                        CyIntClearPending(PlayerBT1_RX_VECT_NUM);
                        break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                    #endif /* End PlayerBT1_FLOW_CONTROL != 0 */
                }
            }

            /* Check again if there is data. */
            readData = PlayerBT1_RXSTATUS_REG;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START PlayerBT1_RXISR_END` */

        /* `#END` */

        #if(CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 */

    }

#endif /* End PlayerBT1_RX_ENABLED && (PlayerBT1_RXBUFFERSIZE > PlayerBT1_FIFO_LENGTH) */


#if(PlayerBT1_TX_ENABLED && (PlayerBT1_TXBUFFERSIZE > PlayerBT1_FIFO_LENGTH))


    /*******************************************************************************
    * Function Name: PlayerBT1_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  PlayerBT1_txBuffer - RAM buffer pointer for transmit data from.
    *  PlayerBT1_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmited byte.
    *  PlayerBT1_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(PlayerBT1_TXISR)
    {

        #if(CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 */

        /* User code required at start of ISR */
        /* `#START PlayerBT1_TXISR_START` */

        /* `#END` */

        #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
            int_en = EA;
            CyGlobalIntEnable;
        #endif /* CY_PSOC3 */

        while((PlayerBT1_txBufferRead != PlayerBT1_txBufferWrite) &&
             ((PlayerBT1_TXSTATUS_REG & PlayerBT1_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer. */
            if(PlayerBT1_txBufferRead >= PlayerBT1_TXBUFFERSIZE)
            {
                PlayerBT1_txBufferRead = 0u;
            }

            PlayerBT1_TXDATA_REG = PlayerBT1_txBuffer[PlayerBT1_txBufferRead];

            /* Set next pointer. */
            PlayerBT1_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START PlayerBT1_TXISR_END` */

        /* `#END` */

        #if(CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 */

    }

#endif /* End PlayerBT1_TX_ENABLED && (PlayerBT1_TXBUFFERSIZE > PlayerBT1_FIFO_LENGTH) */


/* [] END OF FILE */
