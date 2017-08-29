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
#ifndef BLUETOOTH_H
    #define BLUETOOTH_H

#include "project.h"
#include "..\common_files\debug.h"
#include "..\common_files\adv_packet.h"


void BLE_Init(void);
uint8 BLE_IsAdvDataReceived(void);
uint8 BLE_IsNewAdvDataReceived(void);
int8 BLE_GetLastRSSI(void);
uint8 BLE_GetServiceModeFlag(void);

#endif



/* [] END OF FILE */
