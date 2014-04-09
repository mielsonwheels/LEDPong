/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <device.h>

void main()
{
    /* Place yours initialization/startup code here (e.g. MyInst_Start()) */
    PlayerBT1_Start();
        /* Set the bluetooth work in slave mode */
    /*PlayerBT1_PutString("\r\n+STWMOD=0\r\n");
	PlayerBT1_PutString("\r\n+STNA=Pioneer Kit\r\n");
	PlayerBT1_PutString("\r\n+STOAUT=1\r\n"); 
	PlayerBT1_PutString("\r\n+STAUTO=0\r\n");
	CyDelay(2000);
	PlayerBT1_PutString("\r\n+INQ=1\r\n");
    CyDelay(2000);
 */
    Player1_Rx_Start();
    extern uint8 Player1_Rx_flag, Player1_Rx;
    LCD_Start();
    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        if(Player1_Rx_flag)
        {
            Player1_Rx_flag = 0;
            PlayerBT1_PutString("a");
            LCD_Position(0,0);
            if(Player1_Rx == 1)
                LCD_PrintInt8(1);
        }
    }
}

/* [] END OF FILE */
