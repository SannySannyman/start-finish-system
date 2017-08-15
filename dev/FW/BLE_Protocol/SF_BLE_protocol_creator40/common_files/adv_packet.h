#ifndef ADV_PACKET_H
    #define ADV_PACKET_H
    
#include "project.h"

#define BLE_ADV_PACKET_COUNT    5
#define BLE_ADV_PACKET_TEXTLEN  4
#define BLE_ADV_PACKET_TEXTBUFFLEN  (BLE_ADV_PACKET_TEXTLEN+1)
#define BLE_ADV_PACKET_ENDBYTE      (0xDD)
#define BLE_CUSTOM_SERVICE_UUID_LSB (0xA1)
#define BLE_CUSTOM_SERVICE_UUID_MSB (0xE5)

    
enum
{
    ADV_PACKET_UUID_DATALEN = 3,
    ADV_PACKET_SERVICEDATA,
    ADV_PACKET_UUID_LSB,
    ADV_PACKET_UUID_MSB,
    
    ADV_PACKET_TRY_NUM_B1,
    ADV_PACKET_TRY_NUM_B0,
    
    ADV_PACKET_SKIER_NUM,
    ADV_PACKET_STATUS_BYTE,
    
    ADV_PACKET_TIME_START_B3,
    ADV_PACKET_TIME_START_B2,
    ADV_PACKET_TIME_START_B1,
    ADV_PACKET_TIME_START_B0,
     
    ADV_PACKET_TIME_FINISH_B3,
    ADV_PACKET_TIME_FINISH_B2,
    ADV_PACKET_TIME_FINISH_B1,
    ADV_PACKET_TIME_FINISH_B0,
    
    ADV_PACKET_TIME_RESULT_B3,
    ADV_PACKET_TIME_RESULT_B2,
    ADV_PACKET_TIME_RESULT_B1,
    ADV_PACKET_TIME_RESULT_B0,
    
    ADV_PACKET_TXT_START,
    
    ADV_PACKET_ENDBYTE = ADV_PACKET_TXT_START + BLE_ADV_PACKET_TEXTLEN,
    ADV_PACKET_LEN
    
};    
    
enum
{
    STATUS_SK_STARTED = 1,
    STATUS_SK_FINISHED,
    STATUS_SK_CANCELED
};

#define STATUS_SK_MASK (0x03)

typedef struct
{
    uint16 TryNum;
    uint8 SkierNum;
    uint8 StatusByte;
    uint32 TimeStart;
    uint32 TimeFinish;
    uint32 TimeResult;
    char Text[BLE_ADV_PACKET_TEXTBUFFLEN];
}BLE_advPacketData_t;
    


#define BLE_ADV_RESULT_OK                   0u
#define BLE_ADV_RESULT_ERR_BAD_PARAM        1u

#define BLE_ADV_RESULT_DATA_ADDED           0u
#define BLE_ADV_RESULT_DATA_REPLACED        1u
#define BLE_ADV_RESULT_DATA_NO_CHANGES      2u


#define BLE_ADV_RESULT_PACKET_NO_CHANGES    0u
#define BLE_ADV_RESULT_PACKET_UPDATED       1u
#define BLE_ADV_RESULT_PACKET_UPD_WAIT      2u

#define BLE_ADV_RESULT_SEARCH_NOT_FOUND     0xFFu

//typedef struct
//{
//    BLE_advPacketData_t Data[BLE_ADV_PACKET_COUNT];
//    uint8 ItemNum;
//    uint8 NextItem;
//}BLE_advPacketsContent_t;


void BLE_ADV_DataClearBuff();
uint8 BLE_ADV_DataSkierSearch(uint8 skierNum);
uint8 BLE_ADV_DataAddReplace(const BLE_advPacketData_t *newData);
uint8 BLE_ADV_DataGet(BLE_advPacketData_t *data, uint8 dataIndex);
uint8 BLE_ADV_DataGetBuffSize(void);
void BLE_ADV_DataPack(CYBLE_GAPP_DISC_DATA_T *discData, const BLE_advPacketData_t *data);
void BLE_ADV_DataUnpack(BLE_advPacketData_t *data, const CYBLE_GAPC_ADV_REPORT_T* report);
uint8 BLE_ADV_IsDataValid(uint8 *data, uint8 len);

#endif