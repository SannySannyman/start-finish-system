#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <project.h>
#include "..\common_files\adv_packet.h"
    
#define DEBUG_UART_ENABLED    
    
#ifdef DEBUG_UART_ENABLED
    #define DBG_PRINTF(...)          (printf(__VA_ARGS__))
#else
    #define DBG_PRINTF(...)
#endif /* DEBUG_UART_ENABLED */

void DEBUG_Init(void);
void DEBUG_BLE_PrintApiResult(CYBLE_API_RESULT_T apiResult);
void DEBUG_BLE_PrintState(void);
void DEBUG_BLE_PrintAppEvent(uint32 event, void* eventParam);
void DEBUG_DISPLAY_Print(BLE_advPacketData_t *data);
void DEBUG_PrintByteArr(uint8 *data, uint16 len);
void DEBUG_BLE_PrintScanProgress(CYBLE_GAPC_ADV_REPORT_T* eventParam);

#endif
/* [] END OF FILE */
