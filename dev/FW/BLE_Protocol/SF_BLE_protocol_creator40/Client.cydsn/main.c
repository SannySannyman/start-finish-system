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


CY_ISR(isr_DisplayNext_Handler)
{
    displayNextFlag = 1;
    Timer_Display_ClearInterrupt(Timer_Display_INTR_MASK_TC);
}

int main(void)
{
    uint8 num = 0;
    BLE_advPacketData_t skierData;
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    DEBUG_Init();
    BLE_Init();
    LEDD_Init();
    Timer_Display_Start();
    isr_DisplayNext_StartEx(isr_DisplayNext_Handler);
    
    LEDD_GotoXY(0, 0);
    LEDD_Str("SF System v1.0");

    for(;;)
    {
        CyBle_ProcessEvents();
        if(displayNextFlag == 1)
        {
            displayNextFlag = 0;
            
            if(BLE_ADV_RESULT_OK == BLE_ADV_DataBuff_DataGet(&skierData, num))
            {
                DisplayData_ShowSkierData(&skierData);
            }
            
            num++;
            if(num >= BLE_ADV_DataBuff_Size())
            {
                num = 0;
            }
        }
    }
}

/* [] END OF FILE */
