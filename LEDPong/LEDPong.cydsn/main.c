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
    char8 Player1_Rx = 0;
	uint8 pos = 0, count = 0;
    LCD_Start();
    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
    	Player1_Rx = PlayerBT1_GetChar();
		if(Player1_Rx > 0u)
		{
			 count++;        
            /* If the count value reaches the count 16 start from first location */
            if(count % 16 == 0u) 
            {
                pos = 0u; /* resets the count value */
                /* Display will be cleared when reached count value 16 */
                LCD_ClearDisplay();
            }
		
            LCD_Position(0u, pos++);
            LCD_PutChar(Player1_Rx);         /* Print the received character */

            LCD_Position(1u, 0u);
            LCD_PrintInt8(count);    /* Prints the count in the LCD */
		}
    }
}

/* [] END OF FILE */
