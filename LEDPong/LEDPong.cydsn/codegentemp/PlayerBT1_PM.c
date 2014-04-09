/*******************************************************************************
* File Name: PlayerBT1_PM.c
* Version 2.30
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PlayerBT1.h"


/***************************************
* Local data allocation
***************************************/

static PlayerBT1_BACKUP_STRUCT  PlayerBT1_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: PlayerBT1_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  PlayerBT1_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void PlayerBT1_SaveConfig(void)
{
    #if (CY_UDB_V0)

        #if(PlayerBT1_CONTROL_REG_REMOVED == 0u)
            PlayerBT1_backup.cr = PlayerBT1_CONTROL_REG;
        #endif /* End PlayerBT1_CONTROL_REG_REMOVED */

        #if( (PlayerBT1_RX_ENABLED) || (PlayerBT1_HD_ENABLED) )
            PlayerBT1_backup.rx_period = PlayerBT1_RXBITCTR_PERIOD_REG;
            PlayerBT1_backup.rx_mask = PlayerBT1_RXSTATUS_MASK_REG;
            #if (PlayerBT1_RXHW_ADDRESS_ENABLED)
                PlayerBT1_backup.rx_addr1 = PlayerBT1_RXADDRESS1_REG;
                PlayerBT1_backup.rx_addr2 = PlayerBT1_RXADDRESS2_REG;
            #endif /* End PlayerBT1_RXHW_ADDRESS_ENABLED */
        #endif /* End PlayerBT1_RX_ENABLED | PlayerBT1_HD_ENABLED*/

        #if(PlayerBT1_TX_ENABLED)
            #if(PlayerBT1_TXCLKGEN_DP)
                PlayerBT1_backup.tx_clk_ctr = PlayerBT1_TXBITCLKGEN_CTR_REG;
                PlayerBT1_backup.tx_clk_compl = PlayerBT1_TXBITCLKTX_COMPLETE_REG;
            #else
                PlayerBT1_backup.tx_period = PlayerBT1_TXBITCTR_PERIOD_REG;
            #endif /*End PlayerBT1_TXCLKGEN_DP */
            PlayerBT1_backup.tx_mask = PlayerBT1_TXSTATUS_MASK_REG;
        #endif /*End PlayerBT1_TX_ENABLED */


    #else /* CY_UDB_V1 */

        #if(PlayerBT1_CONTROL_REG_REMOVED == 0u)
            PlayerBT1_backup.cr = PlayerBT1_CONTROL_REG;
        #endif /* End PlayerBT1_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: PlayerBT1_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  PlayerBT1_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void PlayerBT1_RestoreConfig(void)
{

    #if (CY_UDB_V0)

        #if(PlayerBT1_CONTROL_REG_REMOVED == 0u)
            PlayerBT1_CONTROL_REG = PlayerBT1_backup.cr;
        #endif /* End PlayerBT1_CONTROL_REG_REMOVED */

        #if( (PlayerBT1_RX_ENABLED) || (PlayerBT1_HD_ENABLED) )
            PlayerBT1_RXBITCTR_PERIOD_REG = PlayerBT1_backup.rx_period;
            PlayerBT1_RXSTATUS_MASK_REG = PlayerBT1_backup.rx_mask;
            #if (PlayerBT1_RXHW_ADDRESS_ENABLED)
                PlayerBT1_RXADDRESS1_REG = PlayerBT1_backup.rx_addr1;
                PlayerBT1_RXADDRESS2_REG = PlayerBT1_backup.rx_addr2;
            #endif /* End PlayerBT1_RXHW_ADDRESS_ENABLED */
        #endif  /* End (PlayerBT1_RX_ENABLED) || (PlayerBT1_HD_ENABLED) */

        #if(PlayerBT1_TX_ENABLED)
            #if(PlayerBT1_TXCLKGEN_DP)
                PlayerBT1_TXBITCLKGEN_CTR_REG = PlayerBT1_backup.tx_clk_ctr;
                PlayerBT1_TXBITCLKTX_COMPLETE_REG = PlayerBT1_backup.tx_clk_compl;
            #else
                PlayerBT1_TXBITCTR_PERIOD_REG = PlayerBT1_backup.tx_period;
            #endif /*End PlayerBT1_TXCLKGEN_DP */
            PlayerBT1_TXSTATUS_MASK_REG = PlayerBT1_backup.tx_mask;
        #endif /*End PlayerBT1_TX_ENABLED */

    #else /* CY_UDB_V1 */

        #if(PlayerBT1_CONTROL_REG_REMOVED == 0u)
            PlayerBT1_CONTROL_REG = PlayerBT1_backup.cr;
        #endif /* End PlayerBT1_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: PlayerBT1_Sleep
********************************************************************************
*
* Summary:
*  Stops and saves the user configuration. Should be called
*  just prior to entering sleep.
*
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  PlayerBT1_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void PlayerBT1_Sleep(void)
{

    #if(PlayerBT1_RX_ENABLED || PlayerBT1_HD_ENABLED)
        if((PlayerBT1_RXSTATUS_ACTL_REG  & PlayerBT1_INT_ENABLE) != 0u)
        {
            PlayerBT1_backup.enableState = 1u;
        }
        else
        {
            PlayerBT1_backup.enableState = 0u;
        }
    #else
        if((PlayerBT1_TXSTATUS_ACTL_REG  & PlayerBT1_INT_ENABLE) !=0u)
        {
            PlayerBT1_backup.enableState = 1u;
        }
        else
        {
            PlayerBT1_backup.enableState = 0u;
        }
    #endif /* End PlayerBT1_RX_ENABLED || PlayerBT1_HD_ENABLED*/

    PlayerBT1_Stop();
    PlayerBT1_SaveConfig();
}


/*******************************************************************************
* Function Name: PlayerBT1_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  PlayerBT1_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void PlayerBT1_Wakeup(void)
{
    PlayerBT1_RestoreConfig();
    #if( (PlayerBT1_RX_ENABLED) || (PlayerBT1_HD_ENABLED) )
        PlayerBT1_ClearRxBuffer();
    #endif /* End (PlayerBT1_RX_ENABLED) || (PlayerBT1_HD_ENABLED) */
    #if(PlayerBT1_TX_ENABLED || PlayerBT1_HD_ENABLED)
        PlayerBT1_ClearTxBuffer();
    #endif /* End PlayerBT1_TX_ENABLED || PlayerBT1_HD_ENABLED */

    if(PlayerBT1_backup.enableState != 0u)
    {
        PlayerBT1_Enable();
    }
}


/* [] END OF FILE */
