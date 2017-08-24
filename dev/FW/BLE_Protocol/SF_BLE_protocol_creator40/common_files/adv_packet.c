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
#include "..\common_files\debug.h"

static struct
{
    BLE_advPacketData_t Data[BLE_ADV_PACKET_COUNT];
    uint8 ItemNum;
    uint8 WritePtr;
}advDataBuff;


void BLE_ADV_DataBuff_Clear()
{
    advDataBuff.ItemNum = 0;
    advDataBuff.WritePtr = 0;
}

uint8 BLE_ADV_DataBuff_SkierSearch(uint8 skierNum)
{
    uint8 dataBuffIndex = BLE_ADV_RESULT_SEARCH_NOT_FOUND;
    uint8 i = 0;
    
    for(i = 0; i < advDataBuff.ItemNum; i++)
    {
        if(skierNum == advDataBuff.Data[i].SkierNum)
        {
            dataBuffIndex = i;
            break;
        }
    }
    
    //    DBG_PRINTF("Search for skier #%03u\r\n", skierNum);
    //    
    //    for(i = 0; i < advDataBuff.ItemNum; i++)
    //    {
    //        DBG_PRINTF("%03u\r\n", advDataBuff.Data[i].SkierNum);
    //    }
    //DBG_PRINTF("Search result: %u\r\n", dataBuffIndex);
    return dataBuffIndex;
}

uint8 BLE_ADV_DataBuff_GetOldestTryNumIndex(void)
{
    uint16 oldestTryNum = 0;
    uint8 oldestIndex = 0;
    uint8 i = 0;
    
    if(advDataBuff.ItemNum > 0)     //buff not empty
    {
        oldestTryNum = advDataBuff.Data[0].TryNum;
        
        for(i = 1; i < advDataBuff.ItemNum; i++)
        {
            if(advDataBuff.Data[i].TryNum < oldestTryNum)
            {
                oldestTryNum = advDataBuff.Data[i].TryNum;
                oldestIndex = i;
            }
        }
    }

    return oldestIndex;
}


uint8 BLE_ADV_DataBuff_GetLatestTryNumIndex(void)
{
    uint16 latestTryNum = 0;
    uint8 latestIndex = 0;
    uint8 i = 0;
    
    if(advDataBuff.ItemNum > 0)     //buff not empty
    {
        latestTryNum = advDataBuff.Data[0].TryNum;
        
        for(i = 1; i < advDataBuff.ItemNum; i++)
        {
            if(advDataBuff.Data[i].TryNum > latestTryNum)
            {
                latestTryNum = advDataBuff.Data[i].TryNum;
                latestIndex = i;
            }
        }
    }

    return latestIndex;
}


uint8 BLE_ADV_DataBuff_GetMinTryNum(void)
{
    uint16 minTryNum = 0;
    uint8 i = 0;
    
    if(advDataBuff.ItemNum > 0)     //buff not empty
    {
        minTryNum = advDataBuff.Data[0].TryNum;
        
        for(i = 1; i < advDataBuff.ItemNum; i++)
        {
            if(advDataBuff.Data[i].TryNum < minTryNum)
            {
                minTryNum = advDataBuff.Data[i].TryNum;
            }
        }
    }
    
    return minTryNum;
}

void BLE_ADV_DataBuff_WriteData(const BLE_advPacketData_t *newData, uint8 writeIndex)
{
    
    if(writeIndex >= advDataBuff.ItemNum ||
        writeIndex == BLE_ADV_ARG_WRITE_NEXT)
    {
        writeIndex = advDataBuff.WritePtr;
        
        advDataBuff.WritePtr++;
        
        if(advDataBuff.WritePtr >= BLE_ADV_PACKET_COUNT)
        {
            advDataBuff.WritePtr = 0;
        }
        
        if(advDataBuff.ItemNum < BLE_ADV_PACKET_COUNT)
        {
            advDataBuff.ItemNum++;
        }
    }
    
    advDataBuff.Data[writeIndex].TryNum = newData->TryNum;
    advDataBuff.Data[writeIndex].SkierNum = newData->SkierNum;
    advDataBuff.Data[writeIndex].StatusByte = newData->StatusByte;
    advDataBuff.Data[writeIndex].TimeStart = newData->TimeStart;
    advDataBuff.Data[writeIndex].TimeFinish = newData->TimeFinish;
    advDataBuff.Data[writeIndex].TimeResult = newData->TimeResult;
    strncpy(advDataBuff.Data[writeIndex].Text, 
            newData->Text, 
            BLE_ADV_PACKET_TEXTLEN);
}

uint8 BLE_ADV_DataBuff_SaveData(const BLE_advPacketData_t *newData)
{
    uint8 result = BLE_ADV_RESULT_DATA_NO_CHANGES;
    uint8 writeIndex = 0;
    uint8 writeFlag = 0;
    uint8 searchResult = BLE_ADV_RESULT_SEARCH_NOT_FOUND;
    
    searchResult = BLE_ADV_DataBuff_SkierSearch(newData->SkierNum);
    
    if(searchResult == BLE_ADV_RESULT_SEARCH_NOT_FOUND) //new data
    {
        if(advDataBuff.ItemNum < BLE_ADV_PACKET_COUNT)  //buff not full
        {
            writeIndex = BLE_ADV_ARG_WRITE_NEXT;
            result = BLE_ADV_RESULT_DATA_ADDED;
        }
        else    //buffer full
        {
            writeIndex = BLE_ADV_DataBuff_GetOldestTryNumIndex();
            if(newData->TryNum < BLE_ADV_DataBuff_GetMinTryNum())   //try num less then all avalible in full buffer
            {
                BLE_ADV_DataBuff_Clear();
            }
            result = BLE_ADV_RESULT_DATA_REPLACED;
        }
        writeFlag = 1;
    }
    else    //skier num already in buff
    {
        if((advDataBuff.Data[searchResult].StatusByte&STATUS_SK_MASK) != 
           (newData->StatusByte&STATUS_SK_MASK) || 
           (advDataBuff.Data[searchResult].TryNum != newData->TryNum))              
                //new status or try number - updated data
        {
            writeIndex =  searchResult;
            writeFlag = 1;
            
            result = BLE_ADV_RESULT_DATA_UPDATED;
        }
        else    //old status - same as data in buff
        {
            result = BLE_ADV_RESULT_DATA_NO_CHANGES;
        }
    }
    
    if(writeFlag != 0)
    {
        BLE_ADV_DataBuff_WriteData(newData, writeIndex);
    }
    
    return result;
}

uint8 BLE_ADV_DataBuff_Size(void)
{
    return advDataBuff.ItemNum;
}

uint8 BLE_ADV_DataBuff_DataGet(BLE_advPacketData_t *data, uint8 dataIndex)
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


uint8 BLE_ADV_DataBuff_DataGetLatest(BLE_advPacketData_t *data)
{
    uint8 index = 0;
    
    index = BLE_ADV_DataBuff_GetLatestTryNumIndex();
    
    return BLE_ADV_DataBuff_DataGet(data, index);
}


void BLE_ADV_DataPack(CYBLE_GAPP_DISC_DATA_T *discData, 
                        const BLE_advPacketData_t *data)
{   
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


uint8 BLE_ADV_IsPacketValid(uint8 *data, uint8 len)
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
