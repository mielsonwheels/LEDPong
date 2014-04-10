/*******************************************************************************
* File Name: Player1_Rx.c  
* Version 1.70
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include <CYDEVICE_TRM.H>
#include <CYLIB.H>
#include <Player1_Rx.H>

#if !defined(Player1_Rx__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START Player1_Rx_intc` */
unsigned int Player1_Rx = 0;
uint8 Player1_Rx_flag = 0;
/* `#END` */

#ifndef CYINT_IRQ_BASE
#define CYINT_IRQ_BASE      16
#endif /* CYINT_IRQ_BASE */
#ifndef CYINT_VECT_TABLE
#define CYINT_VECT_TABLE    ((cyisraddress **) CYREG_NVIC_VECT_OFFSET)
#endif /* CYINT_VECT_TABLE */

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: Player1_Rx_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void Player1_Rx_Start(void)
{
    /* For all we know the interrupt is active. */
    Player1_Rx_Disable();

    /* Set the ISR to point to the Player1_Rx Interrupt. */
    Player1_Rx_SetVector(&Player1_Rx_Interrupt);

    /* Set the priority. */
    Player1_Rx_SetPriority((uint8)Player1_Rx_INTC_PRIOR_NUMBER);

    /* Enable it. */
    Player1_Rx_Enable();
}


/*******************************************************************************
* Function Name: Player1_Rx_StartEx
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void Player1_Rx_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    Player1_Rx_Disable();

    /* Set the ISR to point to the Player1_Rx Interrupt. */
    Player1_Rx_SetVector(address);

    /* Set the priority. */
    Player1_Rx_SetPriority((uint8)Player1_Rx_INTC_PRIOR_NUMBER);

    /* Enable it. */
    Player1_Rx_Enable();
}


/*******************************************************************************
* Function Name: Player1_Rx_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
void Player1_Rx_Stop(void)
{
    /* Disable this interrupt. */
    Player1_Rx_Disable();

    /* Set the ISR to point to the passive one. */
    Player1_Rx_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: Player1_Rx_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for Player1_Rx.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(Player1_Rx_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START Player1_Rx_Interrupt` */
    Player1_Rx = PlayerBT1_ReadRxData();
    Player1_Rx_flag = 1;
    /* `#END` */
}


/*******************************************************************************
* Function Name: Player1_Rx_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling Player1_Rx_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use Player1_Rx_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void Player1_Rx_SetVector(cyisraddress address)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + (uint32)Player1_Rx__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: Player1_Rx_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress Player1_Rx_GetVector(void)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + (uint32)Player1_Rx__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: Player1_Rx_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling Player1_Rx_Start
*   or Player1_Rx_StartEx will override any effect this method 
*   would have had. This method should only be called after 
*   Player1_Rx_Start or Player1_Rx_StartEx has been called. To set 
*   the initial priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void Player1_Rx_SetPriority(uint8 priority)
{
    *Player1_Rx_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: Player1_Rx_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt. 0 - 7, 0 being the highest.
*
*******************************************************************************/
uint8 Player1_Rx_GetPriority(void)
{
    uint8 priority;


    priority = *Player1_Rx_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: Player1_Rx_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void Player1_Rx_Enable(void)
{
    /* Enable the general interrupt. */
    *Player1_Rx_INTC_SET_EN = Player1_Rx__INTC_MASK;
}


/*******************************************************************************
* Function Name: Player1_Rx_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 Player1_Rx_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*Player1_Rx_INTC_SET_EN & (uint32)Player1_Rx__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: Player1_Rx_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void Player1_Rx_Disable(void)
{
    /* Disable the general interrupt. */
    *Player1_Rx_INTC_CLR_EN = Player1_Rx__INTC_MASK;
}


/*******************************************************************************
* Function Name: Player1_Rx_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void Player1_Rx_SetPending(void)
{
    *Player1_Rx_INTC_SET_PD = Player1_Rx__INTC_MASK;
}


/*******************************************************************************
* Function Name: Player1_Rx_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void Player1_Rx_ClearPending(void)
{
    *Player1_Rx_INTC_CLR_PD = Player1_Rx__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
