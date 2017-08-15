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

typedef struct
{
    uint8 SkierNum;
    uint8 StatusByte;
    uint32 ResultTime;
    char Txt[BLE_ADV_PACKET_TEXTBUFFLEN];
    uint16 ShowTime;
    uint8 ShowMode;
}DisplayInfo_t;

void DisplayData_ShowSkierData(BLE_advPacketData_t *skierData);


#endif



/* [] END OF FILE */
