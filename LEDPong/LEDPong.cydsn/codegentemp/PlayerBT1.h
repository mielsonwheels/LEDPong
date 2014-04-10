/*******************************************************************************
* File Name: PlayerBT1.h
* Version 2.30
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_UART_PlayerBT1_H)
#define CY_UART_PlayerBT1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

#define PlayerBT1_RX_ENABLED                     (1u)
#define PlayerBT1_TX_ENABLED                     (1u)
#define PlayerBT1_HD_ENABLED                     (0u)
#define PlayerBT1_RX_INTERRUPT_ENABLED           (0u)
#define PlayerBT1_TX_INTERRUPT_ENABLED           (0u)
#define PlayerBT1_INTERNAL_CLOCK_USED            (1u)
#define PlayerBT1_RXHW_ADDRESS_ENABLED           (0u)
#define PlayerBT1_OVER_SAMPLE_COUNT              (8u)
#define PlayerBT1_PARITY_TYPE                    (0u)
#define PlayerBT1_PARITY_TYPE_SW                 (0u)
#define PlayerBT1_BREAK_DETECT                   (0u)
#define PlayerBT1_BREAK_BITS_TX                  (13u)
#define PlayerBT1_BREAK_BITS_RX                  (13u)
#define PlayerBT1_TXCLKGEN_DP                    (1u)
#define PlayerBT1_USE23POLLING                   (1u)
#define PlayerBT1_FLOW_CONTROL                   (0u)
#define PlayerBT1_CLK_FREQ                       (0u)
#define PlayerBT1_TXBUFFERSIZE                   (4u)
#define PlayerBT1_RXBUFFERSIZE                   (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_30 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#ifdef PlayerBT1_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG
    #define PlayerBT1_CONTROL_REG_REMOVED            (0u)
#else
    #define PlayerBT1_CONTROL_REG_REMOVED            (1u)
#endif /* End PlayerBT1_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct PlayerBT1_backupStruct_
{
    uint8 enableState;

    #if(PlayerBT1_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End PlayerBT1_CONTROL_REG_REMOVED */
    #if( (PlayerBT1_RX_ENABLED) || (PlayerBT1_HD_ENABLED) )
        uint8 rx_period;
        #if (CY_UDB_V0)
            uint8 rx_mask;
            #if (PlayerBT1_RXHW_ADDRESS_ENABLED)
                uint8 rx_addr1;
                uint8 rx_addr2;
            #endif /* End PlayerBT1_RXHW_ADDRESS_ENABLED */
        #endif /* End CY_UDB_V0 */
    #endif  /* End (PlayerBT1_RX_ENABLED) || (PlayerBT1_HD_ENABLED)*/

    #if(PlayerBT1_TX_ENABLED)
        #if(PlayerBT1_TXCLKGEN_DP)
            uint8 tx_clk_ctr;
            #if (CY_UDB_V0)
                uint8 tx_clk_compl;
            #endif  /* End CY_UDB_V0 */
        #else
            uint8 tx_period;
        #endif /*End PlayerBT1_TXCLKGEN_DP */
        #if (CY_UDB_V0)
            uint8 tx_mask;
        #endif  /* End CY_UDB_V0 */
    #endif /*End PlayerBT1_TX_ENABLED */
} PlayerBT1_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void PlayerBT1_Start(void) ;
void PlayerBT1_Stop(void) ;
uint8 PlayerBT1_ReadControlRegister(void) ;
void PlayerBT1_WriteControlRegister(uint8 control) ;

void PlayerBT1_Init(void) ;
void PlayerBT1_Enable(void) ;
void PlayerBT1_SaveConfig(void) ;
void PlayerBT1_RestoreConfig(void) ;
void PlayerBT1_Sleep(void) ;
void PlayerBT1_Wakeup(void) ;

/* Only if RX is enabled */
#if( (PlayerBT1_RX_ENABLED) || (PlayerBT1_HD_ENABLED) )

    #if(PlayerBT1_RX_INTERRUPT_ENABLED)
        void  PlayerBT1_EnableRxInt(void) ;
        void  PlayerBT1_DisableRxInt(void) ;
        CY_ISR_PROTO(PlayerBT1_RXISR);
    #endif /* PlayerBT1_RX_INTERRUPT_ENABLED */

    void PlayerBT1_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void PlayerBT1_SetRxAddress1(uint8 address) ;
    void PlayerBT1_SetRxAddress2(uint8 address) ;

    void  PlayerBT1_SetRxInterruptMode(uint8 intSrc) ;
    uint8 PlayerBT1_ReadRxData(void) ;
    uint8 PlayerBT1_ReadRxStatus(void) ;
    uint8 PlayerBT1_GetChar(void) ;
    uint16 PlayerBT1_GetByte(void) ;
    uint8 PlayerBT1_GetRxBufferSize(void)
                                                            ;
    void PlayerBT1_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define PlayerBT1_GetRxInterruptSource   PlayerBT1_ReadRxStatus

#endif /* End (PlayerBT1_RX_ENABLED) || (PlayerBT1_HD_ENABLED) */

/* Only if TX is enabled */
#if(PlayerBT1_TX_ENABLED || PlayerBT1_HD_ENABLED)

    #if(PlayerBT1_TX_INTERRUPT_ENABLED)
        void PlayerBT1_EnableTxInt(void) ;
        void PlayerBT1_DisableTxInt(void) ;
        CY_ISR_PROTO(PlayerBT1_TXISR);
    #endif /* PlayerBT1_TX_INTERRUPT_ENABLED */

    void PlayerBT1_SetTxInterruptMode(uint8 intSrc) ;
    void PlayerBT1_WriteTxData(uint8 txDataByte) ;
    uint8 PlayerBT1_ReadTxStatus(void) ;
    void PlayerBT1_PutChar(uint8 txDataByte) ;
    void PlayerBT1_PutString(const char8 string[]) ;
    void PlayerBT1_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void PlayerBT1_PutCRLF(uint8 txDataByte) ;
    void PlayerBT1_ClearTxBuffer(void) ;
    void PlayerBT1_SetTxAddressMode(uint8 addressMode) ;
    void PlayerBT1_SendBreak(uint8 retMode) ;
    uint8 PlayerBT1_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define PlayerBT1_PutStringConst         PlayerBT1_PutString
    #define PlayerBT1_PutArrayConst          PlayerBT1_PutArray
    #define PlayerBT1_GetTxInterruptSource   PlayerBT1_ReadTxStatus

#endif /* End PlayerBT1_TX_ENABLED || PlayerBT1_HD_ENABLED */

#if(PlayerBT1_HD_ENABLED)
    void PlayerBT1_LoadRxConfig(void) ;
    void PlayerBT1_LoadTxConfig(void) ;
#endif /* End PlayerBT1_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_PlayerBT1) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    PlayerBT1_CyBtldrCommStart(void) CYSMALL ;
    void    PlayerBT1_CyBtldrCommStop(void) CYSMALL ;
    void    PlayerBT1_CyBtldrCommReset(void) CYSMALL ;
    cystatus PlayerBT1_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus PlayerBT1_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_PlayerBT1)
        #define CyBtldrCommStart    PlayerBT1_CyBtldrCommStart
        #define CyBtldrCommStop     PlayerBT1_CyBtldrCommStop
        #define CyBtldrCommReset    PlayerBT1_CyBtldrCommReset
        #define CyBtldrCommWrite    PlayerBT1_CyBtldrCommWrite
        #define CyBtldrCommRead     PlayerBT1_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_PlayerBT1) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define PlayerBT1_BYTE2BYTE_TIME_OUT (25u)

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define PlayerBT1_SET_SPACE                              (0x00u)
#define PlayerBT1_SET_MARK                               (0x01u)

/* Status Register definitions */
#if( (PlayerBT1_TX_ENABLED) || (PlayerBT1_HD_ENABLED) )
    #if(PlayerBT1_TX_INTERRUPT_ENABLED)
        #define PlayerBT1_TX_VECT_NUM            (uint8)PlayerBT1_TXInternalInterrupt__INTC_NUMBER
        #define PlayerBT1_TX_PRIOR_NUM           (uint8)PlayerBT1_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* PlayerBT1_TX_INTERRUPT_ENABLED */
    #if(PlayerBT1_TX_ENABLED)
        #define PlayerBT1_TX_STS_COMPLETE_SHIFT          (0x00u)
        #define PlayerBT1_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
        #define PlayerBT1_TX_STS_FIFO_FULL_SHIFT         (0x02u)
        #define PlayerBT1_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #endif /* PlayerBT1_TX_ENABLED */
    #if(PlayerBT1_HD_ENABLED)
        #define PlayerBT1_TX_STS_COMPLETE_SHIFT          (0x00u)
        #define PlayerBT1_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
        #define PlayerBT1_TX_STS_FIFO_FULL_SHIFT         (0x05u)  /*needs MD=0*/
        #define PlayerBT1_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #endif /* PlayerBT1_HD_ENABLED */
    #define PlayerBT1_TX_STS_COMPLETE            (uint8)(0x01u << PlayerBT1_TX_STS_COMPLETE_SHIFT)
    #define PlayerBT1_TX_STS_FIFO_EMPTY          (uint8)(0x01u << PlayerBT1_TX_STS_FIFO_EMPTY_SHIFT)
    #define PlayerBT1_TX_STS_FIFO_FULL           (uint8)(0x01u << PlayerBT1_TX_STS_FIFO_FULL_SHIFT)
    #define PlayerBT1_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << PlayerBT1_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (PlayerBT1_TX_ENABLED) || (PlayerBT1_HD_ENABLED)*/

#if( (PlayerBT1_RX_ENABLED) || (PlayerBT1_HD_ENABLED) )
    #if(PlayerBT1_RX_INTERRUPT_ENABLED)
        #define PlayerBT1_RX_VECT_NUM            (uint8)PlayerBT1_RXInternalInterrupt__INTC_NUMBER
        #define PlayerBT1_RX_PRIOR_NUM           (uint8)PlayerBT1_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* PlayerBT1_RX_INTERRUPT_ENABLED */
    #define PlayerBT1_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define PlayerBT1_RX_STS_BREAK_SHIFT             (0x01u)
    #define PlayerBT1_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define PlayerBT1_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define PlayerBT1_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define PlayerBT1_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define PlayerBT1_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define PlayerBT1_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define PlayerBT1_RX_STS_MRKSPC           (uint8)(0x01u << PlayerBT1_RX_STS_MRKSPC_SHIFT)
    #define PlayerBT1_RX_STS_BREAK            (uint8)(0x01u << PlayerBT1_RX_STS_BREAK_SHIFT)
    #define PlayerBT1_RX_STS_PAR_ERROR        (uint8)(0x01u << PlayerBT1_RX_STS_PAR_ERROR_SHIFT)
    #define PlayerBT1_RX_STS_STOP_ERROR       (uint8)(0x01u << PlayerBT1_RX_STS_STOP_ERROR_SHIFT)
    #define PlayerBT1_RX_STS_OVERRUN          (uint8)(0x01u << PlayerBT1_RX_STS_OVERRUN_SHIFT)
    #define PlayerBT1_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << PlayerBT1_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define PlayerBT1_RX_STS_ADDR_MATCH       (uint8)(0x01u << PlayerBT1_RX_STS_ADDR_MATCH_SHIFT)
    #define PlayerBT1_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << PlayerBT1_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define PlayerBT1_RX_HW_MASK                     (0x7Fu)
#endif /* End (PlayerBT1_RX_ENABLED) || (PlayerBT1_HD_ENABLED) */

/* Control Register definitions */
#define PlayerBT1_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define PlayerBT1_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define PlayerBT1_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define PlayerBT1_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define PlayerBT1_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define PlayerBT1_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define PlayerBT1_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define PlayerBT1_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define PlayerBT1_CTRL_HD_SEND               (uint8)(0x01u << PlayerBT1_CTRL_HD_SEND_SHIFT)
#define PlayerBT1_CTRL_HD_SEND_BREAK         (uint8)(0x01u << PlayerBT1_CTRL_HD_SEND_BREAK_SHIFT)
#define PlayerBT1_CTRL_MARK                  (uint8)(0x01u << PlayerBT1_CTRL_MARK_SHIFT)
#define PlayerBT1_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << PlayerBT1_CTRL_PARITY_TYPE0_SHIFT)
#define PlayerBT1_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << PlayerBT1_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define PlayerBT1_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define PlayerBT1_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define PlayerBT1_SEND_BREAK                         (0x00u)
#define PlayerBT1_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define PlayerBT1_REINIT                             (0x02u)
#define PlayerBT1_SEND_WAIT_REINIT                   (0x03u)

#define PlayerBT1_OVER_SAMPLE_8                      (8u)
#define PlayerBT1_OVER_SAMPLE_16                     (16u)

#define PlayerBT1_BIT_CENTER                         (PlayerBT1_OVER_SAMPLE_COUNT - 1u)

#define PlayerBT1_FIFO_LENGTH                        (4u)
#define PlayerBT1_NUMBER_OF_START_BIT                (1u)
#define PlayerBT1_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation*/
#define PlayerBT1_TXBITCTR_BREAKBITS8X   ((PlayerBT1_BREAK_BITS_TX * PlayerBT1_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation*/
#define PlayerBT1_TXBITCTR_BREAKBITS ((PlayerBT1_BREAK_BITS_TX * PlayerBT1_OVER_SAMPLE_COUNT) - 1u)

#define PlayerBT1_HALF_BIT_COUNT   \
                            (((PlayerBT1_OVER_SAMPLE_COUNT / 2u) + (PlayerBT1_USE23POLLING * 1u)) - 2u)
#if (PlayerBT1_OVER_SAMPLE_COUNT == PlayerBT1_OVER_SAMPLE_8)
    #define PlayerBT1_HD_TXBITCTR_INIT   (((PlayerBT1_BREAK_BITS_TX + \
                            PlayerBT1_NUMBER_OF_START_BIT) * PlayerBT1_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define PlayerBT1_RXBITCTR_INIT  ((((PlayerBT1_BREAK_BITS_RX + PlayerBT1_NUMBER_OF_START_BIT) \
                            * PlayerBT1_OVER_SAMPLE_COUNT) + PlayerBT1_HALF_BIT_COUNT) - 1u)


#else /* PlayerBT1_OVER_SAMPLE_COUNT == PlayerBT1_OVER_SAMPLE_16 */
    #define PlayerBT1_HD_TXBITCTR_INIT   ((8u * PlayerBT1_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount=16 */
    #define PlayerBT1_RXBITCTR_INIT      (((7u * PlayerBT1_OVER_SAMPLE_COUNT) - 1u) + \
                                                      PlayerBT1_HALF_BIT_COUNT)
#endif /* End PlayerBT1_OVER_SAMPLE_COUNT */
#define PlayerBT1_HD_RXBITCTR_INIT                   PlayerBT1_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 PlayerBT1_initVar;
#if( PlayerBT1_TX_ENABLED && (PlayerBT1_TXBUFFERSIZE > PlayerBT1_FIFO_LENGTH))
    extern volatile uint8 PlayerBT1_txBuffer[PlayerBT1_TXBUFFERSIZE];
    extern volatile uint8 PlayerBT1_txBufferRead;
    extern uint8 PlayerBT1_txBufferWrite;
#endif /* End PlayerBT1_TX_ENABLED */
#if( ( PlayerBT1_RX_ENABLED || PlayerBT1_HD_ENABLED ) && \
     (PlayerBT1_RXBUFFERSIZE > PlayerBT1_FIFO_LENGTH) )
    extern volatile uint8 PlayerBT1_rxBuffer[PlayerBT1_RXBUFFERSIZE];
    extern volatile uint8 PlayerBT1_rxBufferRead;
    extern volatile uint8 PlayerBT1_rxBufferWrite;
    extern volatile uint8 PlayerBT1_rxBufferLoopDetect;
    extern volatile uint8 PlayerBT1_rxBufferOverflow;
    #if (PlayerBT1_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 PlayerBT1_rxAddressMode;
        extern volatile uint8 PlayerBT1_rxAddressDetected;
    #endif /* End EnableHWAddress */
#endif /* End PlayerBT1_RX_ENABLED */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define PlayerBT1__B_UART__AM_SW_BYTE_BYTE 1
#define PlayerBT1__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define PlayerBT1__B_UART__AM_HW_BYTE_BY_BYTE 3
#define PlayerBT1__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define PlayerBT1__B_UART__AM_NONE 0

#define PlayerBT1__B_UART__NONE_REVB 0
#define PlayerBT1__B_UART__EVEN_REVB 1
#define PlayerBT1__B_UART__ODD_REVB 2
#define PlayerBT1__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define PlayerBT1_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define PlayerBT1_NUMBER_OF_STOP_BITS    (1u)

#if (PlayerBT1_RXHW_ADDRESS_ENABLED)
    #define PlayerBT1_RXADDRESSMODE      (0u)
    #define PlayerBT1_RXHWADDRESS1       (0u)
    #define PlayerBT1_RXHWADDRESS2       (0u)
    /* Backward compatible define */
    #define PlayerBT1_RXAddressMode      PlayerBT1_RXADDRESSMODE
#endif /* End EnableHWAddress */

#define PlayerBT1_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << PlayerBT1_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << PlayerBT1_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << PlayerBT1_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << PlayerBT1_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << PlayerBT1_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << PlayerBT1_RX_STS_BREAK_SHIFT) \
                                        | (0 << PlayerBT1_RX_STS_OVERRUN_SHIFT))

#define PlayerBT1_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << PlayerBT1_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << PlayerBT1_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << PlayerBT1_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << PlayerBT1_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef PlayerBT1_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG
    #define PlayerBT1_CONTROL_REG \
                            (* (reg8 *) PlayerBT1_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG )
    #define PlayerBT1_CONTROL_PTR \
                            (  (reg8 *) PlayerBT1_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG )
#endif /* End PlayerBT1_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG */

#if(PlayerBT1_TX_ENABLED)
    #define PlayerBT1_TXDATA_REG          (* (reg8 *) PlayerBT1_BUART_sTX_TxShifter_u0__F0_REG)
    #define PlayerBT1_TXDATA_PTR          (  (reg8 *) PlayerBT1_BUART_sTX_TxShifter_u0__F0_REG)
    #define PlayerBT1_TXDATA_AUX_CTL_REG  (* (reg8 *) PlayerBT1_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define PlayerBT1_TXDATA_AUX_CTL_PTR  (  (reg8 *) PlayerBT1_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define PlayerBT1_TXSTATUS_REG        (* (reg8 *) PlayerBT1_BUART_sTX_TxSts__STATUS_REG)
    #define PlayerBT1_TXSTATUS_PTR        (  (reg8 *) PlayerBT1_BUART_sTX_TxSts__STATUS_REG)
    #define PlayerBT1_TXSTATUS_MASK_REG   (* (reg8 *) PlayerBT1_BUART_sTX_TxSts__MASK_REG)
    #define PlayerBT1_TXSTATUS_MASK_PTR   (  (reg8 *) PlayerBT1_BUART_sTX_TxSts__MASK_REG)
    #define PlayerBT1_TXSTATUS_ACTL_REG   (* (reg8 *) PlayerBT1_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define PlayerBT1_TXSTATUS_ACTL_PTR   (  (reg8 *) PlayerBT1_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(PlayerBT1_TXCLKGEN_DP)
        #define PlayerBT1_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) PlayerBT1_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define PlayerBT1_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) PlayerBT1_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define PlayerBT1_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) PlayerBT1_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define PlayerBT1_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) PlayerBT1_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define PlayerBT1_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) PlayerBT1_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define PlayerBT1_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) PlayerBT1_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define PlayerBT1_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) PlayerBT1_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define PlayerBT1_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) PlayerBT1_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define PlayerBT1_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) PlayerBT1_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define PlayerBT1_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) PlayerBT1_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* PlayerBT1_TXCLKGEN_DP */

#endif /* End PlayerBT1_TX_ENABLED */

#if(PlayerBT1_HD_ENABLED)

    #define PlayerBT1_TXDATA_REG             (* (reg8 *) PlayerBT1_BUART_sRX_RxShifter_u0__F1_REG )
    #define PlayerBT1_TXDATA_PTR             (  (reg8 *) PlayerBT1_BUART_sRX_RxShifter_u0__F1_REG )
    #define PlayerBT1_TXDATA_AUX_CTL_REG     (* (reg8 *) PlayerBT1_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define PlayerBT1_TXDATA_AUX_CTL_PTR     (  (reg8 *) PlayerBT1_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define PlayerBT1_TXSTATUS_REG           (* (reg8 *) PlayerBT1_BUART_sRX_RxSts__STATUS_REG )
    #define PlayerBT1_TXSTATUS_PTR           (  (reg8 *) PlayerBT1_BUART_sRX_RxSts__STATUS_REG )
    #define PlayerBT1_TXSTATUS_MASK_REG      (* (reg8 *) PlayerBT1_BUART_sRX_RxSts__MASK_REG )
    #define PlayerBT1_TXSTATUS_MASK_PTR      (  (reg8 *) PlayerBT1_BUART_sRX_RxSts__MASK_REG )
    #define PlayerBT1_TXSTATUS_ACTL_REG      (* (reg8 *) PlayerBT1_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define PlayerBT1_TXSTATUS_ACTL_PTR      (  (reg8 *) PlayerBT1_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End PlayerBT1_HD_ENABLED */

#if( (PlayerBT1_RX_ENABLED) || (PlayerBT1_HD_ENABLED) )
    #define PlayerBT1_RXDATA_REG             (* (reg8 *) PlayerBT1_BUART_sRX_RxShifter_u0__F0_REG )
    #define PlayerBT1_RXDATA_PTR             (  (reg8 *) PlayerBT1_BUART_sRX_RxShifter_u0__F0_REG )
    #define PlayerBT1_RXADDRESS1_REG         (* (reg8 *) PlayerBT1_BUART_sRX_RxShifter_u0__D0_REG )
    #define PlayerBT1_RXADDRESS1_PTR         (  (reg8 *) PlayerBT1_BUART_sRX_RxShifter_u0__D0_REG )
    #define PlayerBT1_RXADDRESS2_REG         (* (reg8 *) PlayerBT1_BUART_sRX_RxShifter_u0__D1_REG )
    #define PlayerBT1_RXADDRESS2_PTR         (  (reg8 *) PlayerBT1_BUART_sRX_RxShifter_u0__D1_REG )
    #define PlayerBT1_RXDATA_AUX_CTL_REG     (* (reg8 *) PlayerBT1_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define PlayerBT1_RXBITCTR_PERIOD_REG    (* (reg8 *) PlayerBT1_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define PlayerBT1_RXBITCTR_PERIOD_PTR    (  (reg8 *) PlayerBT1_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define PlayerBT1_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) PlayerBT1_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define PlayerBT1_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) PlayerBT1_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define PlayerBT1_RXBITCTR_COUNTER_REG   (* (reg8 *) PlayerBT1_BUART_sRX_RxBitCounter__COUNT_REG )
    #define PlayerBT1_RXBITCTR_COUNTER_PTR   (  (reg8 *) PlayerBT1_BUART_sRX_RxBitCounter__COUNT_REG )

    #define PlayerBT1_RXSTATUS_REG           (* (reg8 *) PlayerBT1_BUART_sRX_RxSts__STATUS_REG )
    #define PlayerBT1_RXSTATUS_PTR           (  (reg8 *) PlayerBT1_BUART_sRX_RxSts__STATUS_REG )
    #define PlayerBT1_RXSTATUS_MASK_REG      (* (reg8 *) PlayerBT1_BUART_sRX_RxSts__MASK_REG )
    #define PlayerBT1_RXSTATUS_MASK_PTR      (  (reg8 *) PlayerBT1_BUART_sRX_RxSts__MASK_REG )
    #define PlayerBT1_RXSTATUS_ACTL_REG      (* (reg8 *) PlayerBT1_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define PlayerBT1_RXSTATUS_ACTL_PTR      (  (reg8 *) PlayerBT1_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (PlayerBT1_RX_ENABLED) || (PlayerBT1_HD_ENABLED) */

#if(PlayerBT1_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define PlayerBT1_INTCLOCK_CLKEN_REG     (* (reg8 *) PlayerBT1_IntClock__PM_ACT_CFG)
    #define PlayerBT1_INTCLOCK_CLKEN_PTR     (  (reg8 *) PlayerBT1_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define PlayerBT1_INTCLOCK_CLKEN_MASK    PlayerBT1_IntClock__PM_ACT_MSK
#endif /* End PlayerBT1_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(PlayerBT1_TX_ENABLED)
    #define PlayerBT1_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End PlayerBT1_TX_ENABLED */

#if(PlayerBT1_HD_ENABLED)
    #define PlayerBT1_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End PlayerBT1_HD_ENABLED */

#if( (PlayerBT1_RX_ENABLED) || (PlayerBT1_HD_ENABLED) )
    #define PlayerBT1_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (PlayerBT1_RX_ENABLED) || (PlayerBT1_HD_ENABLED) */


/***************************************
* Renamed global variables or defines
* for backward compatible
***************************************/

#define PlayerBT1_initvar                    PlayerBT1_initVar

#define PlayerBT1_RX_Enabled                 PlayerBT1_RX_ENABLED
#define PlayerBT1_TX_Enabled                 PlayerBT1_TX_ENABLED
#define PlayerBT1_HD_Enabled                 PlayerBT1_HD_ENABLED
#define PlayerBT1_RX_IntInterruptEnabled     PlayerBT1_RX_INTERRUPT_ENABLED
#define PlayerBT1_TX_IntInterruptEnabled     PlayerBT1_TX_INTERRUPT_ENABLED
#define PlayerBT1_InternalClockUsed          PlayerBT1_INTERNAL_CLOCK_USED
#define PlayerBT1_RXHW_Address_Enabled       PlayerBT1_RXHW_ADDRESS_ENABLED
#define PlayerBT1_OverSampleCount            PlayerBT1_OVER_SAMPLE_COUNT
#define PlayerBT1_ParityType                 PlayerBT1_PARITY_TYPE

#if( PlayerBT1_TX_ENABLED && (PlayerBT1_TXBUFFERSIZE > PlayerBT1_FIFO_LENGTH))
    #define PlayerBT1_TXBUFFER               PlayerBT1_txBuffer
    #define PlayerBT1_TXBUFFERREAD           PlayerBT1_txBufferRead
    #define PlayerBT1_TXBUFFERWRITE          PlayerBT1_txBufferWrite
#endif /* End PlayerBT1_TX_ENABLED */
#if( ( PlayerBT1_RX_ENABLED || PlayerBT1_HD_ENABLED ) && \
     (PlayerBT1_RXBUFFERSIZE > PlayerBT1_FIFO_LENGTH) )
    #define PlayerBT1_RXBUFFER               PlayerBT1_rxBuffer
    #define PlayerBT1_RXBUFFERREAD           PlayerBT1_rxBufferRead
    #define PlayerBT1_RXBUFFERWRITE          PlayerBT1_rxBufferWrite
    #define PlayerBT1_RXBUFFERLOOPDETECT     PlayerBT1_rxBufferLoopDetect
    #define PlayerBT1_RXBUFFER_OVERFLOW      PlayerBT1_rxBufferOverflow
#endif /* End PlayerBT1_RX_ENABLED */

#ifdef PlayerBT1_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG
    #define PlayerBT1_CONTROL                PlayerBT1_CONTROL_REG
#endif /* End PlayerBT1_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG */

#if(PlayerBT1_TX_ENABLED)
    #define PlayerBT1_TXDATA                 PlayerBT1_TXDATA_REG
    #define PlayerBT1_TXSTATUS               PlayerBT1_TXSTATUS_REG
    #define PlayerBT1_TXSTATUS_MASK          PlayerBT1_TXSTATUS_MASK_REG
    #define PlayerBT1_TXSTATUS_ACTL          PlayerBT1_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(PlayerBT1_TXCLKGEN_DP)
        #define PlayerBT1_TXBITCLKGEN_CTR        PlayerBT1_TXBITCLKGEN_CTR_REG
        #define PlayerBT1_TXBITCLKTX_COMPLETE    PlayerBT1_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define PlayerBT1_TXBITCTR_PERIOD        PlayerBT1_TXBITCTR_PERIOD_REG
        #define PlayerBT1_TXBITCTR_CONTROL       PlayerBT1_TXBITCTR_CONTROL_REG
        #define PlayerBT1_TXBITCTR_COUNTER       PlayerBT1_TXBITCTR_COUNTER_REG
    #endif /* PlayerBT1_TXCLKGEN_DP */
#endif /* End PlayerBT1_TX_ENABLED */

#if(PlayerBT1_HD_ENABLED)
    #define PlayerBT1_TXDATA                 PlayerBT1_TXDATA_REG
    #define PlayerBT1_TXSTATUS               PlayerBT1_TXSTATUS_REG
    #define PlayerBT1_TXSTATUS_MASK          PlayerBT1_TXSTATUS_MASK_REG
    #define PlayerBT1_TXSTATUS_ACTL          PlayerBT1_TXSTATUS_ACTL_REG
#endif /* End PlayerBT1_HD_ENABLED */

#if( (PlayerBT1_RX_ENABLED) || (PlayerBT1_HD_ENABLED) )
    #define PlayerBT1_RXDATA                 PlayerBT1_RXDATA_REG
    #define PlayerBT1_RXADDRESS1             PlayerBT1_RXADDRESS1_REG
    #define PlayerBT1_RXADDRESS2             PlayerBT1_RXADDRESS2_REG
    #define PlayerBT1_RXBITCTR_PERIOD        PlayerBT1_RXBITCTR_PERIOD_REG
    #define PlayerBT1_RXBITCTR_CONTROL       PlayerBT1_RXBITCTR_CONTROL_REG
    #define PlayerBT1_RXBITCTR_COUNTER       PlayerBT1_RXBITCTR_COUNTER_REG
    #define PlayerBT1_RXSTATUS               PlayerBT1_RXSTATUS_REG
    #define PlayerBT1_RXSTATUS_MASK          PlayerBT1_RXSTATUS_MASK_REG
    #define PlayerBT1_RXSTATUS_ACTL          PlayerBT1_RXSTATUS_ACTL_REG
#endif /* End  (PlayerBT1_RX_ENABLED) || (PlayerBT1_HD_ENABLED) */

#if(PlayerBT1_INTERNAL_CLOCK_USED)
    #define PlayerBT1_INTCLOCK_CLKEN         PlayerBT1_INTCLOCK_CLKEN_REG
#endif /* End PlayerBT1_INTERNAL_CLOCK_USED */

#define PlayerBT1_WAIT_FOR_COMLETE_REINIT    PlayerBT1_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_PlayerBT1_H */


/* [] END OF FILE */
