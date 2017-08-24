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
#ifndef DISPLAYDATA_H
    #define DISPLAYDATA_H

#include "project.h"
#include "bluetooth.h"
#include "LED_Display.h"

#define BLINK_INTERVAL      1000
    
#define DISPLAYDATA_STARTSHOW_OK    0
#define DISPLAYDATA_STARTSHOW_BUSY  1  
    
enum
{
    SHOWMODE_ON,
    SHOWMODE_BLINK
};
    



typedef struct
{
    uint8 SkierNum;
    uint8 StatusByte;
    uint32 ResultTime;
    char Txt[BLE_ADV_PACKET_TEXTBUFFLEN];
    uint16 ShowTime;
    uint8 ShowMode;
}DisplayInfo_t;


void DisplayData_Init(void);
void DisplayData_ShowSkierData(BLE_advPacketData_t *skierData);
uint8 DisplayData_IsBusy(void);
void DisplayData_StopShow(void);
uint8 DisplayData_StartShow(uint16 showTime, uint8 showMode);
void DisplayData_Process(void);


#endif



/* [] END OF FILE */
