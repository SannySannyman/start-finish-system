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

#define BLE_ADV_PROCESS_OK              0u
#define BLE_ADV_PROCESS_PACKET_UPDATED  1u
#define BLE_ADV_PROCESS_UPD_WAIT        2u
#define BLE_ADV_PROCESS_ERR             3u


void BLE_ADV_NextPacket(void);
uint8 BLE_ADV_Process(void);
void BLE_Start(void);





#endif
/* [] END OF FILE */
