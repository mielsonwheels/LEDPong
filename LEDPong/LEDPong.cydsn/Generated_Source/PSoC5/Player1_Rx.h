/*******************************************************************************
* File Name: Player1_Rx.h
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
#if !defined(CY_ISR_Player1_Rx_H)
#define CY_ISR_Player1_Rx_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Player1_Rx_Start(void);
void Player1_Rx_StartEx(cyisraddress address);
void Player1_Rx_Stop(void);

CY_ISR_PROTO(Player1_Rx_Interrupt);

void Player1_Rx_SetVector(cyisraddress address);
cyisraddress Player1_Rx_GetVector(void);

void Player1_Rx_SetPriority(uint8 priority);
uint8 Player1_Rx_GetPriority(void);

void Player1_Rx_Enable(void);
uint8 Player1_Rx_GetState(void);
void Player1_Rx_Disable(void);

void Player1_Rx_SetPending(void);
void Player1_Rx_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Player1_Rx ISR. */
#define Player1_Rx_INTC_VECTOR            ((reg32 *) Player1_Rx__INTC_VECT)

/* Address of the Player1_Rx ISR priority. */
#define Player1_Rx_INTC_PRIOR             ((reg8 *) Player1_Rx__INTC_PRIOR_REG)

/* Priority of the Player1_Rx interrupt. */
#define Player1_Rx_INTC_PRIOR_NUMBER      Player1_Rx__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Player1_Rx interrupt. */
#define Player1_Rx_INTC_SET_EN            ((reg32 *) Player1_Rx__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Player1_Rx interrupt. */
#define Player1_Rx_INTC_CLR_EN            ((reg32 *) Player1_Rx__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Player1_Rx interrupt state to pending. */
#define Player1_Rx_INTC_SET_PD            ((reg32 *) Player1_Rx__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Player1_Rx interrupt. */
#define Player1_Rx_INTC_CLR_PD            ((reg32 *) Player1_Rx__INTC_CLR_PD_REG)


#endif /* CY_ISR_Player1_Rx_H */


/* [] END OF FILE */
