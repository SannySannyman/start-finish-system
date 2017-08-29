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

#include "DisplayData.h"

#define TEMPBUF_LEN 20

BLE_advPacketData_t tempData;

typedef enum
{
    DISPLAYSTATE_OFF,
    DISPLAYSTATE_COUNTDOWN,
    DISPLAYSTATE_FOREVER
}displayState_t;


char tempBuff[TEMPBUF_LEN];

volatile uint16 displayShowTimer = 0;
volatile uint16 displayBlinkTimer = 0;
volatile displayState_t displayState = DISPLAYSTATE_OFF;
uint8 displayShowMode = SHOWMODE_ON;

void DisplayData_ISR_Handler(void)
{
    if(displayState != DISPLAYSTATE_OFF)
    {
        if(displayShowMode == SHOWMODE_BLINK)
        {
            displayBlinkTimer++;
            if(displayBlinkTimer >= BLINK_INTERVAL)
            {
                displayBlinkTimer = 0;
                LEDD_SetEnable(~LEDD_GetEnable());
            }
        }
        
        if(displayState == DISPLAYSTATE_COUNTDOWN)
        {
            displayShowTimer--;
            if(displayShowTimer <= 0)
            {
                LEDD_SetEnable(0);
                displayState = DISPLAYSTATE_OFF;
                displayBlinkTimer = 0;
            }
        }
    }
}


void DisplayData_Init(void)
{
    uint8 i = 0;
    
    LEDD_SetEnable(0);
    displayShowTimer = 0;
    displayBlinkTimer = 0;
    displayState = DISPLAYSTATE_OFF;
    displayShowMode = SHOWMODE_ON;
    
    CySysTickStart();
    
    for (i = 0u; i < CY_SYS_SYST_NUM_OF_CALLBACKS; ++i)
    {
        if (CySysTickGetCallback(i) == NULL)
        {
            CySysTickSetCallback(i, DisplayData_ISR_Handler);
            break;
        }
    }
    
}

void DisplayData_ShowSkierData(BLE_advPacketData_t *skierData)
{
    if(BLE_ADV_DataBuff_Size() >0)
    {
        LEDD_Clear();
        
        LEDD_GotoXY(0, 0);
        snprintf(tempBuff, TEMPBUF_LEN, "#%03u", skierData->SkierNum);
        LEDD_Str(tempBuff);
        
        LEDD_GotoXY(25, 0);
        
        switch ((skierData->StatusByte)&STATUS_SK_MASK)
        {
            case STATUS_SK_STARTED:
                snprintf(tempBuff, TEMPBUF_LEN, "Started");
                break;
            case STATUS_SK_FINISHED:
                snprintf(tempBuff, TEMPBUF_LEN, "Finished");
                break;
            case STATUS_SK_CANCELED:
                snprintf(tempBuff, TEMPBUF_LEN, "Canceled");
                break;
            default:
                snprintf(tempBuff, TEMPBUF_LEN, "Reserved");
                break;
        }
        LEDD_Str(tempBuff);
        
        if(skierData->StatusByte == STATUS_SK_FINISHED)
        {
            LEDD_GotoXY(0, 8);
            memset(tempBuff, 0, TEMPBUF_LEN);
            strncpy(tempBuff, skierData->Text, BLE_ADV_PACKET_TEXTLEN);
            LEDD_Str(tempBuff);
            LEDD_PutCh(':');
        
            LEDD_GotoXY(31, 8);
            snprintf(tempBuff, TEMPBUF_LEN, "%02x:%02x.%02x", (uint8)((skierData->TimeResult>>16)&0xFF),
                                                 (uint8)((skierData->TimeResult>>8)&0xFF),
                                                 (uint8)((skierData->TimeResult   )&0xFF));
            LEDD_Str(tempBuff);
        }
        
        //DEBUG_DISPLAY_Print(skierData);
    }
}

uint8 DisplayData_IsBusy(void)
{
    if(displayState == DISPLAYSTATE_OFF || displayState == DISPLAYSTATE_FOREVER)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}



void DisplayData_StopShow(void)
{
    
    LEDD_SetEnable(0);
    displayBlinkTimer = 0;
    displayState = DISPLAYSTATE_OFF;
}




uint8 DisplayData_StartShow(uint16 showTime, uint8 showMode)
{
    if(!DisplayData_IsBusy())
    {
        displayBlinkTimer = 0;
        displayShowMode = showMode;
        
        if(showTime == 0)
        {
            displayState = DISPLAYSTATE_FOREVER;
        }
        else
        {
            displayShowTimer = showTime;
            displayState = DISPLAYSTATE_COUNTDOWN;
        }
        
        LEDD_SetEnable(1);
        
        return DISPLAYDATA_STARTSHOW_OK;
    }
    else
    {
        return DISPLAYDATA_STARTSHOW_BUSY;
    }
}


void DisplayData_Process(void)
{
    static int16 avgRSSI = 0;
    static uint8 RSSIcnt = 0;
    
    if(BLE_GetServiceModeFlag() == 1)
    {
        if(BLE_IsAdvDataReceived())
        {
            avgRSSI += BLE_GetLastRSSI();
            RSSIcnt++;
            
            if(RSSIcnt >= RSSI_AVG_NUM)
            {
                RSSIcnt = 0;
                avgRSSI /= RSSI_AVG_NUM;
                
                LEDD_Clear();
                LEDD_GotoXY(0, 8);
                snprintf(tempBuff, TEMPBUF_LEN, "RSSI = %i", avgRSSI);
                LEDD_Str(tempBuff);
                DisplayData_StartShow(0, SHOWMODE_ON);
                
                avgRSSI = 0;
            }
        }
    }
    
    else if(BLE_IsNewAdvDataReceived())
    {
        if(DisplayData_IsBusy())
        {
            DisplayData_StopShow();
        }
        
        BLE_ADV_DataBuff_DataGetLatest(&tempData);
        DisplayData_ShowSkierData(&tempData);
        
        if((tempData.StatusByte&STATUS_SK_MASK) == STATUS_SK_STARTED)
        {
            DisplayData_StartShow(5000, SHOWMODE_BLINK);
        }
        else
        {
            DisplayData_StartShow(5000, SHOWMODE_ON);
        }
    }
}

/* [] END OF FILE */
