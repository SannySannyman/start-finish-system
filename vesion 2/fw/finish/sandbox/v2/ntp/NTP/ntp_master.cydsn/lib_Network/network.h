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
#ifndef _NETWORK_H
    #define _NETWORK_H

#include <UART_XB.h>
#include <UART_XB_SPI_UART.h>
#include <project.h>

#include <stdio.h>
#include <lib_Network\svt.h>

#define DEBUG_PC

#ifdef DEBUG_PC
    #include <SW_UART_DEBUG.h>
#endif


#define READ_OK     1
#define NO_READ     0
#define WRITE_OK    1
#define NO_WRITE    0
#define READY       1
#define NO_READY    0

#define MIN_DELAYMS 150

#define NEW_SKIER_IN_TARCK   1

/*size buffer*/
#define DATA_BUFFER   50
#define RX_BUFFER   

#define ADRESS_READY        8
#define ADRESS_REBOOT       9
#define ADRESS_COUNT_SK     10

/*network status*/
#define NETWORK_CONN        1
#define NETWORK_DISCONN     0
#define NETWORK_TIMEOUT     30

#define MASK_HIGH   0xFFFFFFFF00000000
#define MASK_LOW    0x00000000FFFFFFFF
#define DATA_SHIFT  32

#define TIMEOUT_FIN_READY   3

typedef struct
{
    uint8_t IDpacket;
    uint8_t ready;
    uint8_t reboot;
    uint8_t countSkiers;
    uint64_t tmpTime;
    uint16_t tmpMsTime;
    uint8_t readStatus;
}FinishData;

typedef struct
{
    uint8_t IDpacket;
    uint64_t unixStartTime;
    uint16_t startMsTime;
    uint8_t newSkier;
    uint8_t writeStatus;
}StartData;

FinishData inData;
StartData outData;

char previousData[100];

static uint32_t networkStatus;
static int noConnect;
static int finNoReady;

void InitNetwork(void);
uint32_t NetworkStatus(void);
void SendSkierStart(uint64_t unixTimeStart, uint32_t recentMs);
uint32_t FinWriteInDB(void);
uint32_t FinReady(void);

void SendData(void);
uint32_t ReceiveData(void);

#endif
/* [] END OF FILE */