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
#include "string.h"

volatile uint8 nextPacketFlag = 0;

BLE_advPacketData_t advData;

CYBLE_GATT_HANDLE_VALUE_PAIR_T tempHandle;
CYBLE_CONN_HANDLE_T connectionHandle;

uint8 testVal = 0;


void BLE_ADV_NextPacket(void)
{
    nextPacketFlag = 1;
}



uint8 BLE_ADV_Process(void)
{
    static uint8 dataIndex = 0;
    uint8 result = BLE_ADV_PROCESS_OK;
    
    if(nextPacketFlag != 0 && CyBle_GetState() == CYBLE_STATE_ADVERTISING)
    {
        if(CyBle_GetBleSsState() == CYBLE_BLESS_STATE_EVENT_CLOSE)
        {
            nextPacketFlag = 0;
            
            if(BLE_ADV_DataBuff_DataGet(&advData, dataIndex) == BLE_ADV_RESULT_OK)
            {
                BLE_ADV_DataPack(&cyBle_discoveryData, &advData);
                
                CyBle_GapUpdateAdvData( cyBle_discoveryModeInfo.advData, 
                                        cyBle_discoveryModeInfo.scanRspData);
                
                dataIndex++;
                if(dataIndex >= BLE_ADV_DataBuff_Size())
                {
                    dataIndex = 0;
                }
                result = BLE_ADV_PROCESS_PACKET_UPDATED;
            }
            else
            {
                result = BLE_ADV_PROCESS_ERR;
            }
        }
        else
        {
            result = BLE_ADV_PROCESS_UPD_WAIT;
        }
    }
    
    
    return result;
}




void BLE_AppEventHandler(uint32 event, void* eventParam)
{
    CYBLE_GATTS_WRITE_REQ_PARAM_T *wrParam;
    
    DEBUG_BLE_PrintAppEvent(event, eventParam);
    
    switch(event)
    {
        case CYBLE_EVT_STACK_ON:
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            ///////
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            break;
        
        case CYBLE_EVT_GATT_CONNECT_IND:
            connectionHandle = *(CYBLE_CONN_HANDLE_T  *)eventParam;
			break;    
            
        case CYBLE_EVT_GATTS_WRITE_REQ:
            wrParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T *)eventParam;
            
            if(wrParam->handleValPair.attrHandle == CYBLE_SF_CONTROL_TEST_CHAR_HANDLE)
            {
                testVal = wrParam->handleValPair.value.val[0];
                
                tempHandle.attrHandle = CYBLE_SF_CONTROL_TEST_CHAR_HANDLE;
                tempHandle.value.val = &testVal;
                tempHandle.value.len = 1;
                
                CyBle_GattsWriteAttributeValue(&tempHandle, 0, &connectionHandle, CYBLE_GATT_DB_PEER_INITIATED);
            }
            CyBle_GattsWriteRsp(connectionHandle);
            break;
            
        default:
            break;
    }

}




void BLE_Start(void)
{
    BLE_ADV_DataBuff_Clear();
    CyBle_Start(BLE_AppEventHandler);
}



/* [] END OF FILE */
