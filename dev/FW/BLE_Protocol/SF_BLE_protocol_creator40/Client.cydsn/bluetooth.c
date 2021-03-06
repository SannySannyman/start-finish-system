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
uint8 newAdvDataReceivedFlag = 0;
int8 lastRSSI = 0;
uint8 serviceModeFlag = 0;
uint8 packetCheckInitFlag = 0;
uint8 advDataReceivedFlag = 0;

void BLE_Init(void)
{
    packetCheckInitFlag = 0;
    BLE_ADV_DataBuff_Clear();
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
    uint8 result = 0;

    
    if(BLE_ADV_IsPacketValid(eventParam->data, eventParam->dataLen))
    {
        lastRSSI = eventParam->rssi;
        advDataReceivedFlag = 1;
        
        if(memcmp(prewPacket, eventParam->data, eventParam->dataLen) != 0 ||
            packetCheckInitFlag == 0) /*check for new packet*/
        {
            memcpy(prewPacket, eventParam->data, eventParam->dataLen);
            packetCheckInitFlag = 1;
            
            BLE_ADV_DataUnpack(&advData, eventParam);
            
            if((advData.StatusByte & STATUS_SERVICE_MODE_MASK) != 0)
            {
                serviceModeFlag = 1;
                BLE_ADV_DataBuff_Clear();
            }
            else
            {
                serviceModeFlag = 0;
                
                result = BLE_ADV_DataBuff_SaveData(&advData);
                if(result != BLE_ADV_RESULT_DATA_NO_CHANGES)
                {
                    newAdvDataReceivedFlag = 1;
                    
                    if(result == BLE_ADV_RESULT_DATA_ADDED)
                    {
                        DBG_PRINTF("New data :\r\n");
                    }
                    if(result == BLE_ADV_RESULT_DATA_UPDATED)
                    {
                        DBG_PRINTF("Updated data :\r\n");
                    }
                    if(result == BLE_ADV_RESULT_DATA_REPLACED)
                    {
                        DBG_PRINTF("Replaced data :\r\n");
                    }
                    
                    DEBUG_DISPLAY_Print(&advData);
                    DBG_PRINTF("\r\n");
                }
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

uint8 BLE_IsAdvDataReceived(void)
{
    uint8 retResult = 0;
    
    retResult = advDataReceivedFlag;
    advDataReceivedFlag = 0;
    
    return retResult;
}

uint8 BLE_IsNewAdvDataReceived(void)
{
    uint8 retResult = 0;
    
    retResult = newAdvDataReceivedFlag;
    newAdvDataReceivedFlag = 0;
    
    return retResult;
}

int8 BLE_GetLastRSSI(void)
{
    return lastRSSI;
}

uint8 BLE_GetServiceModeFlag(void)
{
    return serviceModeFlag;
}

/* [] END OF FILE */
