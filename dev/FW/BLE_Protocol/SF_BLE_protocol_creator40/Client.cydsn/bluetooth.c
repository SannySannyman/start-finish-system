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
#include "bluetooth.h"

BLE_advPacketData_t advData;
void BLE_AppEventHandler(uint32 event, void* eventParam);

void BLE_Init(void)
{
    BLE_ADV_DataClearBuff();
    CyBle_Start(BLE_AppEventHandler);
}

void BLE_StartScan(uint8 scanIntervalType)
{
    CYBLE_API_RESULT_T apiResult;
    apiResult = CyBle_GapcStartScan(scanIntervalType);
	if(apiResult != CYBLE_ERROR_OK)
    {
        DBG_PRINTF("StartScan API Error: ");
        DEBUG_BLE_PrintApiResult(apiResult);
    }
    else
    {
        DBG_PRINTF("Start Scan \r\n");
    }
}


void BLE_ScanProgressEventHandler(CYBLE_GAPC_ADV_REPORT_T* eventParam)
{
    static uint8 prewPacket[CYBLE_GAP_MAX_ADV_DATA_LEN];
    uint8 dataIndex = 0;
    uint8 result = 0;

    
    if(BLE_ADV_IsDataValid(eventParam->data, eventParam->dataLen))
    {
        if(memcmp(prewPacket, eventParam->data, eventParam->dataLen) != 0) /*check for new packet*/
        {
            memcpy(prewPacket, eventParam->data, eventParam->dataLen);
            
            BLE_ADV_DataUnpack(&advData, eventParam);
            
            result = BLE_ADV_DataAddReplace(&advData);
            if(result != BLE_ADV_RESULT_DATA_NO_CHANGES)
            {
                if(result == BLE_ADV_RESULT_DATA_ADDED)
                {
                    DBG_PRINTF("New data :\n\r");
                }
                if(result == BLE_ADV_RESULT_DATA_REPLACED)
                {
                    DBG_PRINTF("Replaced data :\n\r");
                }
                
                DEBUG_DISPLAY_Print(&advData);
                DBG_PRINTF("\n\r");
            }
        }
        
        Pin_RedLED_Write(~Pin_RedLED_Read());
    }
}


void BLE_AppEventHandler(uint32 event, void* eventParam)
{
    switch(event)
    {
        case CYBLE_EVT_STACK_ON:
            BLE_StartScan(CYBLE_SCANNING_FAST);
            break;

        case CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT:
            BLE_ScanProgressEventHandler((CYBLE_GAPC_ADV_REPORT_T *)eventParam);
            break;
            
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            BLE_StartScan(CYBLE_SCANNING_FAST);
            break;

        default:
            break;
    }
    
    DEBUG_BLE_PrintAppEvent(event, eventParam);
}



/* [] END OF FILE */
