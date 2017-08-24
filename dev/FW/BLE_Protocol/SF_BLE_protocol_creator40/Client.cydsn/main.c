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

#define BLE_ADV_PACKET_COUNT 10

#include "project.h"
#include "..\common_files\debug.h"
#include "bluetooth.h"
#include "LED_Display.h"
#include "DisplayData.h"

volatile uint8 displayNextFlag = 0;


int main(void)
{    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    DEBUG_Init();
    BLE_Init();
    LEDD_Init();
    DisplayData_Init();
    
    LEDD_GotoXY(0, 0);
    LEDD_Str("SF System v1.0");
    DisplayData_StartShow(0, SHOWMODE_BLINK);

    for(;;)
    {
        CyBle_ProcessEvents();
        DisplayData_Process();
    }
}

/* [] END OF FILE */
