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

#include "DisplayData.h"

#define TEMPBUF_LEN 20
char tempBuff[TEMPBUF_LEN];

void DisplayData_ShowSkierData(BLE_advPacketData_t *skierData)
{
    if(BLE_ADV_DataBuff_Size() >0)
    {
        LEDD_Clear();
        
        LEDD_GotoXY(0, 0);
        snprintf(tempBuff, TEMPBUF_LEN, "#%03u", skierData->SkierNum);
        LEDD_Str(tempBuff);
        
        LEDD_GotoXY(25, 0);
        
        switch ((skierData->StatusByte)&STATUS_SK_MASK)
        {
            case STATUS_SK_STARTED:
                snprintf(tempBuff, TEMPBUF_LEN, "Started");
                break;
            case STATUS_SK_FINISHED:
                snprintf(tempBuff, TEMPBUF_LEN, "Finished");
                break;
            case STATUS_SK_CANCELED:
                snprintf(tempBuff, TEMPBUF_LEN, "Canceled");
                break;
            default:
                snprintf(tempBuff, TEMPBUF_LEN, "Reserved");
                break;
        }
        LEDD_Str(tempBuff);
        
        if(skierData->StatusByte == STATUS_SK_FINISHED)
        {
            LEDD_GotoXY(0, 8);
            memset(tempBuff, 0, TEMPBUF_LEN);
            strncpy(tempBuff, skierData->Text, BLE_ADV_PACKET_TEXTLEN);
            LEDD_Str(tempBuff);
            LEDD_PutCh(':');
        
            LEDD_GotoXY(31, 8);
            snprintf(tempBuff, TEMPBUF_LEN, "%02x:%02x.%02x", (uint8)((skierData->TimeResult>>16)&0xFF),
                                                 (uint8)((skierData->TimeResult>>8)&0xFF),
                                                 (uint8)((skierData->TimeResult   )&0xFF));
            LEDD_Str(tempBuff);
        }
        
        //DEBUG_DISPLAY_Print(skierData);
    }
}


/* [] END OF FILE */
