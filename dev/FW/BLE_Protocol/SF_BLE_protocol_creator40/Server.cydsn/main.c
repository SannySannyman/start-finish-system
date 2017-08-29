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
#include "project.h"
#include "..\common_files\debug.h"
#include "bluetooth.h"
#include <stdio.h>
#include <stdlib.h>

#define TIME_BYTESIZE 4

const uint8 maxArr[TIME_BYTESIZE] = {24, 60, 60, 100};
volatile uint8 btnPressedFlag = 0;

CY_ISR(isr_Timer_Handler)
{
    static uint8 cnt = 0;
    static uint8 tempBtnStatus = 0;
    
    cnt++;
    if(cnt >= 4)
    {
        BLE_ADV_NextPacket();
    }
    
    if(Pin_Button_Read() == 0)
    {
        tempBtnStatus = 1;
    }
    else 
    {
        if(tempBtnStatus == 1)
        {
            tempBtnStatus = 0;
            btnPressedFlag = 1;
        }
    }
    
    Timer_ClearInterrupt(Timer_INTR_MASK_TC);
}

uint32 GenRandTime()
{
    uint32 time = 0;
    uint8 genVal = 0;
    int8 i = 0;
    
    
    for(i = 0; i < TIME_BYTESIZE; i++)
    {
        genVal = rand() % maxArr[i];
        
        time <<=4;
        time |= genVal/10;
        time <<=4;
        time |= genVal%10;
        
    }
    
    return time;
}

int main(void)
{
    BLE_advPacketData_t data;
    uint16 tryNum = 1;
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    DEBUG_Init();
    
    Timer_Start();
    isr_Timer_StartEx(isr_Timer_Handler);
    BLE_Init();
    
    snprintf(data.Text, BLE_ADV_PACKET_TEXTBUFFLEN, "Time");
      
    for(;;)
    {
        CyBle_ProcessEvents();
        
        BLE_ADV_Process();
        
        if(btnPressedFlag == 1)
        {
            btnPressedFlag = 0;
            
            data.TryNum = tryNum;
            data.SkierNum = (rand()%255)+1;
            data.StatusByte = rand()%3+1;
            data.TimeStart = GenRandTime();
            data.TimeFinish = GenRandTime();
            data.TimeResult = GenRandTime();     
            BLE_ADV_DataBuff_SaveData(&data);
            
            DBG_PRINTF("Generated data:\r\n");
            DEBUG_DISPLAY_Print(&data);
            DBG_PRINTF("\r\n");
            
            tryNum++;
            if(tryNum <= 0)
            {
                tryNum = 1;
            }
            

            Pin_GreenLED_Write(~Pin_GreenLED_Read());
        }
        
        
    }
}

/* [] END OF FILE */
