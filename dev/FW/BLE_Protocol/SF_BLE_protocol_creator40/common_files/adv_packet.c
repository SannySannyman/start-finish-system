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
#include "..\common_files\adv_packet.h"


static struct
{
    BLE_advPacketData_t Data[BLE_ADV_PACKET_COUNT];
    uint8 ItemNum;
    uint8 WritePtr;
}advDataBuff;


void BLE_ADV_DataClearBuff()
{
    advDataBuff.ItemNum = 0;
    advDataBuff.WritePtr = 0;
}

uint8 BLE_ADV_DataSkierSearch(uint8 skierNum)
{
    uint8 dataBuffIndex = 0xFF;
    uint8 i = 0;
    
    for(i = 0; i < advDataBuff.ItemNum; i++)
    {
        if(skierNum == advDataBuff.Data[i].SkierNum)
        {
            dataBuffIndex = i;
            break;
        }
    }
    
    return dataBuffIndex;
}



uint8 BLE_ADV_DataAddReplace(const BLE_advPacketData_t *newData)
{
    uint8 result;
    uint8 buffIndex = 0;
    uint8 writeFlag = 0;
      
    buffIndex = BLE_ADV_DataSkierSearch(newData->SkierNum);
    
    if(buffIndex == BLE_ADV_RESULT_SEARCH_NOT_FOUND)
    {
        buffIndex = advDataBuff.WritePtr;
        writeFlag = 1;
        result = BLE_ADV_RESULT_DATA_ADDED;

        if(advDataBuff.ItemNum < BLE_ADV_PACKET_COUNT)
        {
            advDataBuff.ItemNum++;
        }
        
        advDataBuff.WritePtr++;
        
        if(advDataBuff.WritePtr >= advDataBuff.ItemNum)
        {
            advDataBuff.WritePtr = 0;
        } 
    }
    else
    {
        if((advDataBuff.Data[buffIndex].StatusByte&STATUS_SK_MASK) != 
                    (newData->StatusByte&STATUS_SK_MASK))
        {
            writeFlag = 1;
            result = BLE_ADV_RESULT_DATA_REPLACED;
        }
        else
        {
            result = BLE_ADV_RESULT_DATA_NO_CHANGES;
        }
    }
    
    if(writeFlag != 0)
    {
        advDataBuff.Data[buffIndex].TryNum = newData->TryNum;
        advDataBuff.Data[buffIndex].SkierNum = newData->SkierNum;
        advDataBuff.Data[buffIndex].StatusByte = newData->StatusByte;
        advDataBuff.Data[buffIndex].TimeStart = newData->TimeStart;
        advDataBuff.Data[buffIndex].TimeFinish = newData->TimeFinish;
        advDataBuff.Data[buffIndex].TimeResult = newData->TimeResult;
        strncpy(advDataBuff.Data[buffIndex].Text, 
                newData->Text, 
                BLE_ADV_PACKET_TEXTLEN);
    }
    return result;
}


uint8 BLE_ADV_DataGet(BLE_advPacketData_t *data, uint8 dataIndex)
{
    if(dataIndex < advDataBuff.ItemNum)
    {
        data->TryNum = advDataBuff.Data[dataIndex].TryNum;
        data->SkierNum = advDataBuff.Data[dataIndex].SkierNum;
        data->StatusByte = advDataBuff.Data[dataIndex].StatusByte;
        data->TimeStart = advDataBuff.Data[dataIndex].TimeStart;
        data->TimeFinish = advDataBuff.Data[dataIndex].TimeFinish;
        data->TimeResult = advDataBuff.Data[dataIndex].TimeResult;
        strncpy(data->Text, 
                advDataBuff.Data[dataIndex].Text, 
                BLE_ADV_PACKET_TEXTLEN);
        
        return BLE_ADV_RESULT_OK;
    }
    else
    {
        return BLE_ADV_RESULT_ERR_BAD_PARAM;
    }
}


uint8 BLE_ADV_DataGetBuffSize(void)
{
    return advDataBuff.ItemNum;
}


void BLE_ADV_DataPack(CYBLE_GAPP_DISC_DATA_T *discData, 
                        const BLE_advPacketData_t *data)
{

    if(data->SkierNum == 0)
    {
        asm("nop");
    }
    
    discData->advData[ADV_PACKET_UUID_DATALEN] = ADV_PACKET_LEN - 4; /* Length */
    discData->advData[ADV_PACKET_SERVICEDATA] = 0x16;      /* Service Data */
    discData->advData[ADV_PACKET_UUID_LSB] = BLE_CUSTOM_SERVICE_UUID_LSB;
    discData->advData[ADV_PACKET_UUID_MSB] = BLE_CUSTOM_SERVICE_UUID_MSB;
    
    discData->advData[ADV_PACKET_TRY_NUM_B1] = (data->TryNum>>8)&0xFF;
    discData->advData[ADV_PACKET_TRY_NUM_B0] = (data->TryNum   )&0xFF;
    
    discData->advData[ADV_PACKET_SKIER_NUM] = data->SkierNum;
    discData->advData[ADV_PACKET_STATUS_BYTE] = data->StatusByte;
    
	discData->advData[ADV_PACKET_TIME_START_B3] = (data->TimeStart>>24)&0xFF;
	discData->advData[ADV_PACKET_TIME_START_B2] = (data->TimeStart>>16)&0xFF;
	discData->advData[ADV_PACKET_TIME_START_B1] = (data->TimeStart>>8)&0xFF;
	discData->advData[ADV_PACKET_TIME_START_B0] = (data->TimeStart)&0xFF;
	
	discData->advData[ADV_PACKET_TIME_FINISH_B3] = (data->TimeFinish>>24)&0xFF;
	discData->advData[ADV_PACKET_TIME_FINISH_B2] = (data->TimeFinish>>16)&0xFF;
	discData->advData[ADV_PACKET_TIME_FINISH_B1] = (data->TimeFinish>>8)&0xFF;
	discData->advData[ADV_PACKET_TIME_FINISH_B0] = (data->TimeFinish)&0xFF;
	
	discData->advData[ADV_PACKET_TIME_RESULT_B3] = (data->TimeResult>>24)&0xFF;
	discData->advData[ADV_PACKET_TIME_RESULT_B2] = (data->TimeResult>>16)&0xFF;
	discData->advData[ADV_PACKET_TIME_RESULT_B1] = (data->TimeResult>>8)&0xFF;
	discData->advData[ADV_PACKET_TIME_RESULT_B0] = (data->TimeResult)&0xFF;
	
    memcpy(&discData->advData[ADV_PACKET_TXT_START], 
            data->Text, 
            BLE_ADV_PACKET_TEXTLEN);
    
    discData->advData[ADV_PACKET_ENDBYTE] = BLE_ADV_PACKET_ENDBYTE;
    
    discData->advDataLen = ADV_PACKET_LEN;

}


void BLE_ADV_DataUnpack(BLE_advPacketData_t *data, 
                        const CYBLE_GAPC_ADV_REPORT_T* report)
{
    data->TryNum =  
        (report->data[ADV_PACKET_TRY_NUM_B1]<<8)|
        (report->data[ADV_PACKET_TRY_NUM_B0]);
    
    data->SkierNum = report->data[ADV_PACKET_SKIER_NUM];
    data->StatusByte = report->data[ADV_PACKET_STATUS_BYTE];
    
    data->TimeStart =  
        (report->data[ADV_PACKET_TIME_START_B3]<<24)|
        (report->data[ADV_PACKET_TIME_START_B2]<<16)|
        (report->data[ADV_PACKET_TIME_START_B1]<<8)|
        (report->data[ADV_PACKET_TIME_START_B0]);
    
    data->TimeFinish =
        (report->data[ADV_PACKET_TIME_FINISH_B3]<<24)|
        (report->data[ADV_PACKET_TIME_FINISH_B2]<<16)|
        (report->data[ADV_PACKET_TIME_FINISH_B1]<<8)|
        (report->data[ADV_PACKET_TIME_FINISH_B0]);
    
    data->TimeResult = 
        (report->data[ADV_PACKET_TIME_RESULT_B3]<<24)|
        (report->data[ADV_PACKET_TIME_RESULT_B2]<<16)|
        (report->data[ADV_PACKET_TIME_RESULT_B1]<<8)|
        (report->data[ADV_PACKET_TIME_RESULT_B0]);
    
    memcpy( data->Text, 
            &report->data[ADV_PACKET_TXT_START], 
            BLE_ADV_PACKET_TEXTLEN);
}


uint8 BLE_ADV_IsDataValid(uint8 *data, uint8 len)
{   
    if(len == ADV_PACKET_LEN)
    {
        if( data[ADV_PACKET_UUID_LSB] == BLE_CUSTOM_SERVICE_UUID_LSB &&
            data[ADV_PACKET_UUID_MSB] == BLE_CUSTOM_SERVICE_UUID_MSB &&
            data[ADV_PACKET_ENDBYTE] == BLE_ADV_PACKET_ENDBYTE)
        {
            return 1;
        }
    }

    return 0;
}

/* [] END OF FILE */
