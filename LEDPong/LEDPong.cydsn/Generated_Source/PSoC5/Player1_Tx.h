/*******************************************************************************
* File Name: Player1_Tx.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_Player1_Tx_H)
#define CY_ISR_Player1_Tx_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Player1_Tx_Start(void);
void Player1_Tx_StartEx(cyisraddress address);
void Player1_Tx_Stop(void);

CY_ISR_PROTO(Player1_Tx_Interrupt);

void Player1_Tx_SetVector(cyisraddress address);
cyisraddress Player1_Tx_GetVector(void);

void Player1_Tx_SetPriority(uint8 priority);
uint8 Player1_Tx_GetPriority(void);

void Player1_Tx_Enable(void);
uint8 Player1_Tx_GetState(void);
void Player1_Tx_Disable(void);

void Player1_Tx_SetPending(void);
void Player1_Tx_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Player1_Tx ISR. */
#define Player1_Tx_INTC_VECTOR            ((reg32 *) Player1_Tx__INTC_VECT)

/* Address of the Player1_Tx ISR priority. */
#define Player1_Tx_INTC_PRIOR             ((reg8 *) Player1_Tx__INTC_PRIOR_REG)

/* Priority of the Player1_Tx interrupt. */
#define Player1_Tx_INTC_PRIOR_NUMBER      Player1_Tx__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Player1_Tx interrupt. */
#define Player1_Tx_INTC_SET_EN            ((reg32 *) Player1_Tx__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Player1_Tx interrupt. */
#define Player1_Tx_INTC_CLR_EN            ((reg32 *) Player1_Tx__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Player1_Tx interrupt state to pending. */
#define Player1_Tx_INTC_SET_PD            ((reg32 *) Player1_Tx__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Player1_Tx interrupt. */
#define Player1_Tx_INTC_CLR_PD            ((reg32 *) Player1_Tx__INTC_CLR_PD_REG)


#endif /* CY_ISR_Player1_Tx_H */


/* [] END OF FILE */
