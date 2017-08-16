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

CY_ISR(isr_Timer_Handler)
{
    BLE_ADV_NextPacket();
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
    uint8 result;
    uint8 cnt = 0;
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    DEBUG_Init();
    
    Timer_Start();
    isr_Timer_StartEx(isr_Timer_Handler);
    BLE_Start();
    
    data.TryNum = tryNum++;
    data.SkierNum = 12;
    data.StatusByte = STATUS_SK_STARTED;
    data.TimeStart = 0x12345678;
    data.TimeFinish = 0x23456789;
    data.TimeResult = 0x11111111;
    snprintf(data.Text, BLE_ADV_PACKET_TEXTBUFFLEN, "Time");
    
    BLE_ADV_DataBuff_SaveData(&data);
      
    for(;;)
    {
        CyBle_ProcessEvents();
        
        result = BLE_ADV_Process();
        if(result == BLE_ADV_RESULT_PACKET_UPDATED)
        {
            cnt++;
            if(cnt >= 10)
            {
                cnt = 0;

                data.TryNum = tryNum;
                data.SkierNum = (rand()%255)+1;
                data.StatusByte = rand()%3+1;
                data.TimeStart = GenRandTime();
                data.TimeFinish = GenRandTime();
                data.TimeResult = GenRandTime();     
                BLE_ADV_DataBuff_SaveData(&data);
                
                if(tryNum <= 0)
                {
                    tryNum = 1;
                }
                tryNum++;
                
            }
            Pin_GreenLED_Write(~Pin_GreenLED_Read());
        }
        
        
    }
}

/* [] END OF FILE */
