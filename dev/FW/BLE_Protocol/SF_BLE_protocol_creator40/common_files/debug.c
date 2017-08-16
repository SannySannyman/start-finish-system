#include <project.h>
#include "debug.h"


#ifdef DEBUG_UART_ENABLED
int _write(int file, char *ptr, int len)
{
    int x;
    file = file;
    for (x = 0; x < len; x++)
    {
        UART_DEBUG_UartPutChar(*ptr++);
    }
    return len;
}
#endif


void DEBUG_Init(void)
{
    UART_DEBUG_Start();
}

void DEBUG_PrintByteArr(uint8 *data, uint16 len)
{
    uint16 i = 0;
    
    for(i = 0; i < len; i++)
    {
        DBG_PRINTF("%02x", data[i]);
        
        if(i < len - 1)
        {
            DBG_PRINTF(":");
        }
    }
}

void DEBUG_BLE_PrintApiResult(CYBLE_API_RESULT_T apiResult)
{
    DBG_PRINTF("0x%.2x ", apiResult);
    
    switch(apiResult)
    {
        case CYBLE_ERROR_OK:
            DBG_PRINTF("ok\r\n");
            break;
            
        case CYBLE_ERROR_INVALID_PARAMETER:
            DBG_PRINTF("invalid parameter\r\n");
            break;
            
        case CYBLE_ERROR_INVALID_OPERATION:
            DBG_PRINTF("invalid operation\r\n");
            break;
            
        case CYBLE_ERROR_NO_DEVICE_ENTITY:
            DBG_PRINTF("no device entity\r\n");
            break;
            
        case CYBLE_ERROR_NTF_DISABLED:
            DBG_PRINTF("notification is disabled\r\n");
            break;
            
        case CYBLE_ERROR_IND_DISABLED:
            DBG_PRINTF("indication is disabled\r\n");
            break;
            
        case CYBLE_ERROR_CHAR_IS_NOT_DISCOVERED:
            DBG_PRINTF("characteristic is not discovered\r\n");
            break;
            
        case CYBLE_ERROR_INVALID_STATE:
            DBG_PRINTF("invalid state\r\n");
            break;
            
        case CYBLE_ERROR_GATT_DB_INVALID_ATTR_HANDLE:
            DBG_PRINTF("invalid attribute handle\r\n");
            break;
            
        case CYBLE_ERROR_FLASH_WRITE_NOT_PERMITED:
            DBG_PRINTF("flash write not permitted\r\n");
            break;
            
        default:
            DBG_PRINTF("other api result\r\n");
            break;
    }
}


void DEBUG_BLE_PrintState(void)
{
    DBG_PRINTF("state: ");
    switch(CyBle_GetState())
    {
        case CYBLE_STATE_STOPPED:
            DBG_PRINTF("stopped\r\n");
            break;
            
        case CYBLE_STATE_INITIALIZING:
            DBG_PRINTF("initializing\r\n");
            break;
            
        case CYBLE_STATE_CONNECTED:
            DBG_PRINTF("connected\r\n");
            break;
            
#if(CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_BROADCASTER)
        case CYBLE_STATE_ADVERTISING:
            DBG_PRINTF("advertising\r\n");
            break;
#endif /* CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_BROADCASTER */

#if(CYBLE_GAP_ROLE_CENTRAL || CYBLE_GAP_ROLE_OBSERVER)
        case CYBLE_STATE_SCANNING:
            DBG_PRINTF("scanning\r\n");
            break;
#endif /* CYBLE_GAP_ROLE_CENTRAL || CYBLE_GAP_ROLE_OBSERVER */

#if(CYBLE_GAP_ROLE_CENTRAL)
        case CYBLE_STATE_CONNECTING:
            DBG_PRINTF("connecting\r\n");
            break;
#endif /* CYBLE_GAP_ROLE_CENTRAL */

        case CYBLE_STATE_DISCONNECTED:
            DBG_PRINTF("disconnected\r\n");
            break;
        
        default:
            DBG_PRINTF("unknown\r\n");
            break;
    }
}


void DEBUG_BLE_PrintAppEvent(uint32 event, void* eventParam)
{
    //CYBLE_API_RESULT_T apiResult;
    
    switch(event)
    {
        case CYBLE_EVT_STACK_ON:
            DBG_PRINTF("CYBLE_EVT_STACK_ON \r\n");
            break;

        case CYBLE_EVT_TIMEOUT: /* 0x01 -> GAP limited discoverable mode timeout. */
                                /* 0x02 -> GAP pairing process timeout. */
                                /* 0x03 -> GATT response timeout. */
            DBG_PRINTF("CYBLE_EVT_TIMEOUT: %d \r\n", *(uint8 *)eventParam);
            break;

        case CYBLE_EVT_HCI_STATUS:
            DBG_PRINTF("CYBLE_EVT_HCI_STATUS: %x\r\n", *(uint8 *)eventParam);
            break;
        /**********************************************************
        *                       GAP Events
        ***********************************************************/
        case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
            DBG_PRINTF("CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP: ");
            DEBUG_BLE_PrintState();
            break;    
            
        case CYBLE_EVT_GAPC_SCAN_START_STOP:
            DBG_PRINTF("CYBLE_EVT_GAPC_SCAN_START_STOP \r\n");
            DEBUG_BLE_PrintState();
            break;
            
        case CYBLE_EVT_GAP_SMP_NEGOTIATED_AUTH_INFO:
            DBG_PRINTF("CYBLE_EVT_GAP_SMP_NEGOTIATED_AUTH_INFO \r\n");
            break;
            
        case CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT:
            //DBG_PRINTF("CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT \r\n");
            break;
            
        case CYBLE_EVT_GAP_AUTH_REQ:
            DBG_PRINTF("CYBLE_EVT_GAP_AUTH_REQ \r\n");
            break;

        case CYBLE_EVT_GAP_PASSKEY_ENTRY_REQUEST:
            DBG_PRINTF("CYBLE_EVT_GAP_PASSKEY_ENTRY_REQUEST \r\n");
            break;

        case CYBLE_EVT_GAP_PASSKEY_DISPLAY_REQUEST:
            DBG_PRINTF("CYBLE_EVT_GAP_PASSKEY_DISPLAY_REQUEST: %6.6ld \r\n", *(uint32 *)eventParam);
            break;

        case CYBLE_EVT_GAP_AUTH_FAILED:
            DBG_PRINTF("CYBLE_EVT_GAP_AUTH_FAILED, reason: ");
            switch(*(CYBLE_GAP_AUTH_FAILED_REASON_T *)eventParam)
            {
                case CYBLE_GAP_AUTH_ERROR_CONFIRM_VALUE_NOT_MATCH:
                    DBG_PRINTF("CONFIRM_VALUE_NOT_MATCH\r\n");
                    break;
                    
                case CYBLE_GAP_AUTH_ERROR_INSUFFICIENT_ENCRYPTION_KEY_SIZE:
                    DBG_PRINTF("INSUFFICIENT_ENCRYPTION_KEY_SIZE\r\n");
                    break;
                
                case CYBLE_GAP_AUTH_ERROR_UNSPECIFIED_REASON:
                    DBG_PRINTF("UNSPECIFIED_REASON\r\n");
                    break;
                    
                case CYBLE_GAP_AUTH_ERROR_AUTHENTICATION_TIMEOUT:
                    DBG_PRINTF("AUTHENTICATION_TIMEOUT\r\n");
                    break;
                    
                default:
                    DBG_PRINTF("0x%x \r\n", *(CYBLE_GAP_AUTH_FAILED_REASON_T *)eventParam);
                    break;
            }
            break;

        case CYBLE_EVT_GAP_DEVICE_CONNECTED:
            DBG_PRINTF("CYBLE_EVT_GAP_DEVICE_CONNECTED: %x \r\n", cyBle_connHandle.bdHandle);
            break;

        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            DBG_PRINTF("CYBLE_EVT_GAP_DEVICE_DISCONNECTED, reason: %x \r\n", *(uint8*)eventParam);
            break;

        case CYBLE_EVT_GAP_AUTH_COMPLETE:
            DBG_PRINTF("CYBLE_EVT_GAP_AUTH_COMPLETE: security:%x, bonding:%x, ekeySize:%x, authErr %x \r\n",
                        ((CYBLE_GAP_AUTH_INFO_T *)eventParam)->security,
                        ((CYBLE_GAP_AUTH_INFO_T *)eventParam)->bonding, 
                        ((CYBLE_GAP_AUTH_INFO_T *)eventParam)->ekeySize, 
                        ((CYBLE_GAP_AUTH_INFO_T *)eventParam)->authErr);
            break;

        case CYBLE_EVT_GAP_ENCRYPT_CHANGE:
            DBG_PRINTF("CYBLE_EVT_GAP_ENCRYPT_CHANGE: %d \r\n", *(uint8 *)eventParam);
            break;

        case CYBLE_EVT_GATT_CONNECT_IND:
            DBG_PRINTF("CYBLE_EVT_GATT_CONNECT_IND \r\n");
            break;
            
        case CYBLE_EVT_GATT_DISCONNECT_IND:
            DBG_PRINTF("CYBLE_EVT_GATT_DISCONNECT_IND \r\n");
            break;
            
        case CYBLE_EVT_GATTS_XCNHG_MTU_REQ:
            DBG_PRINTF("CYBLE_EVT_GATTS_XCNHG_MTU_REQ \r\n");
            break;
            
        case CYBLE_EVT_GATTS_WRITE_REQ:
            DBG_PRINTF("CYBLE_EVT_GATTS_WRITE_REQ: dataLen: %u\r\n", 
                        ((CYBLE_GATTS_WRITE_REQ_PARAM_T *)eventParam)->
                        handleValPair.value.len);
            
            DBG_PRINTF("data: ");
            DEBUG_PrintByteArr(((CYBLE_GATTS_WRITE_REQ_PARAM_T *)eventParam)-> 
                                    handleValPair.value.val, 
                                ((CYBLE_GATTS_WRITE_REQ_PARAM_T *)eventParam)->
                                    handleValPair.value.len);
            DBG_PRINTF("\r\n");
            
            DBG_PRINTF("attrHandle: %04x\r\n", 
                                ((CYBLE_GATTS_WRITE_REQ_PARAM_T *)eventParam)->
                                    handleValPair.attrHandle);
            break;
            
        case CYBLE_EVT_GATTS_WRITE_CMD_REQ:
            DBG_PRINTF("CYBLE_EVT_GATTS_WRITE_CMD_REQ \r\n");
            DBG_PRINTF("data: ");
            DEBUG_PrintByteArr(((CYBLE_GATTS_WRITE_CMD_REQ_PARAM_T *)eventParam)-> 
                                    handleValPair.value.val, 
                                ((CYBLE_GATTS_WRITE_CMD_REQ_PARAM_T *)eventParam)->
                                    handleValPair.value.len);
            DBG_PRINTF("\r\n");
            break;
            
        case CYBLE_EVT_GATTS_READ_CHAR_VAL_ACCESS_REQ:
            DBG_PRINTF("CYBLE_EVT_GATTS_READ_CHAR_VAL_ACCESS_REQ \r\n");
            DBG_PRINTF("attrHandle: %04x\r\n", 
                                ((CYBLE_GATTS_CHAR_VAL_READ_REQ_T *)eventParam)->
                                    attrHandle);
            
            break;
            
        /**********************************************************
        *                       Other Events
        ***********************************************************/
        case CYBLE_EVT_PENDING_FLASH_WRITE:
            /* Inform application that flash write is pending. Stack internal data 
            * structures are modified and require to be stored in Flash using 
            * CyBle_StoreBondingData() */
            DBG_PRINTF("CYBLE_EVT_PENDING_FLASH_WRITE \r\n");
            break;

        default:
            DBG_PRINTF("Other event: %lx \r\n", event);
            break;
    }
}



void DEBUG_BLE_PrintScanProgress(CYBLE_GAPC_ADV_REPORT_T* eventParam)
{
    DBG_PRINTF("Scan result: \r\n");
    DBG_PRINTF("event type:");
    switch (eventParam->eventType)
    {
        case CYBLE_GAPC_CONN_UNDIRECTED_ADV:
            DBG_PRINTF("CONN_UNDIRECTED_ADV\r\n");
            break;
            
        case CYBLE_GAPC_CONN_DIRECTED_ADV:
            DBG_PRINTF("CONN_DIRECTED_ADV\r\n");
            break;
            
        case CYBLE_GAPC_SCAN_UNDIRECTED_ADV:
            DBG_PRINTF("DIRECTED_ADV\r\n");
            break;
            
        case CYBLE_GAPC_NON_CONN_UNDIRECTED_ADV:
            DBG_PRINTF("NON_CONN_UNDIRECTED_ADV\r\n");
            break;
            
        case CYBLE_GAPC_SCAN_RSP:
            DBG_PRINTF("SCAN_RSP\r\n");
            break;
    }
    
    if(eventParam->eventType != CYBLE_GAPC_SCAN_RSP)
    {      
        DBG_PRINTF("ADV data: ");
        DEBUG_PrintByteArr(eventParam->data, eventParam->dataLen);
        DBG_PRINTF("\r\n");
    }
    
    DBG_PRINTF("dataLen: %i \r\n", eventParam->dataLen);

}


void DEBUG_DISPLAY_Print(BLE_advPacketData_t *data)
{
    char tempBuff[BLE_ADV_PACKET_TEXTLEN+1];
    
    DBG_PRINTF("Try number: %u\r\n", data->TryNum);
    DBG_PRINTF("Skier num: %u\r\n", data->SkierNum);
    DBG_PRINTF("Status: %x, Skier ", data->StatusByte);
    switch((data->StatusByte)&STATUS_SK_MASK)
    {
        case STATUS_SK_STARTED:
            DBG_PRINTF("Started");
            break;
        
        case STATUS_SK_FINISHED:
            DBG_PRINTF("Finished");
            break;
            
        case STATUS_SK_CANCELED:
            DBG_PRINTF("Canceled");
            break;
            
        default:
            DBG_PRINTF("Err");
            break;
    }
    
    DBG_PRINTF("\r\n");
    
    DBG_PRINTF("Time start: %02x:%02x:%02x.%02x\r\n", 
                (uint8)((data->TimeStart>>24)&0xFF),
                (uint8)((data->TimeStart>>16)&0xFF),
                (uint8)((data->TimeStart>>8)&0xFF),
                (uint8)((data->TimeStart   )&0xFF));
    
    DBG_PRINTF("Time finish: %02x:%02x:%02x.%02x\r\n", 
                (uint8)((data->TimeFinish>>24)&0xFF),
                (uint8)((data->TimeFinish>>16)&0xFF),
                (uint8)((data->TimeFinish>>8)&0xFF),
                (uint8)((data->TimeFinish   )&0xFF));
    
    DBG_PRINTF("Time result: %02x:%02x:%02x.%02x\r\n", 
                (uint8)((data->TimeResult>>24)&0xFF),
                (uint8)((data->TimeResult>>16)&0xFF),
                (uint8)((data->TimeResult>>8)&0xFF),
                (uint8)((data->TimeResult   )&0xFF));
    
    strncpy(tempBuff, data->Text, BLE_ADV_PACKET_TEXTLEN+1);
    DBG_PRINTF("Text: %s\r\n", tempBuff);
    DBG_PRINTF("\r\n");
    
}

/* [] END OF FILE */
