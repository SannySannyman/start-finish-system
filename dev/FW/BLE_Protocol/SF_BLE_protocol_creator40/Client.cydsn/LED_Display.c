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

#include "LED_Display.h"
#include <string.h>

volatile uint8 rowCnt = 0;
uint16 LEDChIdx = 0;

//uint8 displayBuff[LED_DISPLAY_BUFFSIZE];
struct 
{
    uint16 X;
    uint16 Y;
}txtPos;

void DisplaySendByte(void)
{
    static int16 byteCnt = LEDD_SECTORSIZE - 1;
    uint16 addr = 0;
    
    if(byteCnt >= 0)
    {
        addr = (byteCnt % LEDD_MUXNUM)*LEDD_SECTORSIZE + 
            ((LEDD_X_BYTENUM-1) - byteCnt/LEDD_MUXNUM) + rowCnt*LEDD_X_BYTENUM;
            
        SPI_DISP_WriteByte(~displayBuff[addr]);
        byteCnt--;
    }
    else
    {
        OE_Control_Write(0);
        DISP_AB_Write(rowCnt);
        DISP_L_Write(1);
        asm("nop");
        DISP_L_Write(0);
        OE_Control_Write(1);
        
        rowCnt++;
        if(rowCnt >= LEDD_MUXNUM)
        {
            rowCnt = 0;
        }
        byteCnt = LEDD_SECTORSIZE - 1;
    }
}

CY_ISR(SPI_DISP_Handler)
{
    DisplaySendByte();
}


CY_ISR(DISP_Handler)
{
    DisplaySendByte();
}

void LEDD_Clear(void)
{
    memset(displayBuff, 0x00, LEDD_BUFFSIZE);
}

void LEDD_Init(void)
{
    SPI_DISP_Start();
    //DISP_OE_Write(1);
    PWM_LEDD_Start();
    PWM_LEDD_WriteCompare(7);
    isr_DISP_StartEx(DISP_Handler);
    isr_SPI_DISP_Tx_StartEx(SPI_DISP_Handler);
    LEDD_Clear();
    txtPos.X = 0;
    txtPos.Y = 0;
}


LEDDResponse_t LEDD_SetPixel(uint8 x, uint8 y, LEDDPixelMode_t mode)
{
    uint16 addr = 0;
    uint8 offset = 0;
    uint8 tempByte = 0;
    
    if(x>= LEDD_X_RES || y >= LEDD_Y_RES)
    {
        return LEDD_OUT_OF_BORDER;
    }
    
    offset =  x % 8;
    addr = (x / 8) + LEDD_X_BYTENUM * y;
    
    tempByte = displayBuff[addr];
    
    switch(mode)
    {
        case LEDD_PIXEL_ON: 
            tempByte |= 0x80>>offset;
            break;
        case LEDD_PIXEL_OFF: 
            tempByte &= ~(0x80>>offset);
            break;
        case LEDD_PIXEL_XOR: 
            tempByte ^= 0x80>>offset;
            break;
    }
    displayBuff[addr] = tempByte;
    return LEDD_OK;
}


LEDDResponse_t LEDD_Line (uint8 x1, uint8 y1, uint8 x2, uint8 y2, LEDDPixelMode_t mode)
{
    int16 dx, dy, stepx, stepy, fraction;
    uint8 response;

    // dy   y2 - y1
    // -- = -------
    // dx   x2 - x1

    dy = y2 - y1;
    dx = x2 - x1;

    if ( dy < 0 )
    {
        dy    = -dy;
        stepy = -1;
    }
    else
    {
        stepy = 1;
    }

    if ( dx < 0 )
    {
        dx    = -dx;
        stepx = -1;
    }
    else
    {
        stepx = 1;
    }

    dx <<= 1;
    dy <<= 1;

    response = LEDD_SetPixel( x1, y1, mode );
    if(response != LEDD_OK)
    {
        return response;
    }

    if ( dx > dy )
    {
        fraction = dy - ( dx >> 1);
        while ( x1 != x2 )
        {
            if ( fraction >= 0 )
            {
                y1 += stepy;
                fraction -= dx;
            }
            x1 += stepx;
            fraction += dy;

            response = LEDD_SetPixel( x1, y1, mode );
            if(response != LEDD_OK)
            {
                return response;
            }

        }
    }
    else
    {
        fraction = dx - ( dy >> 1);
        while ( y1 != y2 )
        {
            if ( fraction >= 0 )
            {
                x1 += stepx;
                fraction -= dy;
            }
            y1 += stepy;
            fraction += dx;

            response = LEDD_SetPixel( x1, y1, mode );
            if(response != LEDD_OK)
            {
                return response;
            }
        }
    }

    return LEDD_OK;
}

void LEDD_DownShiftCyc(void)
{
    int16 cnt = 0;
    uint8 tempBuff[LEDD_Y_SHIFTBUFFSIZE];
    
    for(cnt = 0; cnt < LEDD_X_BYTENUM; cnt++)
    {
        tempBuff[cnt] = displayBuff[cnt+(LEDD_BUFFSIZE-LEDD_X_BYTENUM)];
    }
    
    for(cnt = LEDD_BUFFSIZE-1; cnt >= LEDD_X_BYTENUM; cnt --)
    {
            displayBuff[cnt] = displayBuff[cnt-LEDD_X_BYTENUM];
    }
    
    for(cnt = 0; cnt < LEDD_X_BYTENUM; cnt++)
    {
        displayBuff[cnt] = tempBuff[cnt];
    }
}

void LEDD_DownShift(void)
{
    int16 cnt = 0;
    
    for(cnt = LEDD_BUFFSIZE-1; cnt >= LEDD_X_BYTENUM; cnt --)
    {
            displayBuff[cnt] = displayBuff[cnt-LEDD_X_BYTENUM];
    }
    
    for(cnt = 0; cnt < LEDD_X_BYTENUM; cnt++)
    {
        displayBuff[cnt] = 0x00;
    }

}

LEDDResponse_t LEDD_GotoXY(uint16 x, uint16 y)
{
    if(x < LEDD_X_RES && y < LEDD_Y_RES)
    {
        txtPos.X = x;
        txtPos.Y = y;
        return LEDD_OK;
    }
    else
    {
        
        return LEDD_OUT_OF_BORDER;
    }
    
}


LEDDResponse_t LEDD_PutCh(uint8 ch)
{
    int8 cntX = 0;
    int8 cntY = 0;
    int8 txtByteOffset = 0;
    uint8 txtByteNum = 0;
    uint8 chWidth = 0;
    uint32 temp = 0;
    int16 addr = 0;
    uint8 rowLen = 0;
    LEDDResponse_t responce = LEDD_OK;
    
    txtByteOffset = txtPos.X % 8;
    txtByteNum = txtPos.X / 8;
     
    
    
    if (ch >= ' ')
    {
        //ASCII[0x21-0x7F]
        ch -= ' ';
    }
    
    chWidth = FontDescr[ch].chWidth;
    
    
    if(txtPos.X + chWidth > LEDD_X_RES)
    {
        responce = LEDD_OUT_OF_BORDER;
    }
    else
    {
        txtPos.X += chWidth;
        if(txtPos.X < LEDD_X_RES)
        {
            txtPos.X++; //adding symbol interval
        }
    
        
        for(cntY = LEDD_FONT_HEIGHT-1; cntY >=0; cntY --)
        {
            if(chWidth > 0)
            {
                rowLen = (FontDescr[ch].chWidth-1)/8+1;
            }
            else
            {
                rowLen = 0;
            }
            
            temp = 0;
            
            for(cntX = 0; cntX < 4; cntX ++)
            {
                temp <<= 8;
                
                if(cntX < rowLen)
                {
                    temp |= fontArr[FontDescr[ch].offset + cntY*rowLen + cntX];
                }
            }
            
            temp >>= txtByteOffset;
            
            for(cntX = 0; cntX < (chWidth-1 + txtByteOffset)/8+1; cntX ++)
            {
                addr = txtByteNum + cntX + ((cntY + txtPos.Y)* LEDD_X_BYTENUM);
                if((addr < LEDD_BUFFSIZE) && (addr >= 0))
                {
                    displayBuff[addr] |= temp >> ((3 - cntX) * 8);
                }
                else
                {
                    //responce = LEDD_OUT_OF_BORDER;
                }
            } 
        }
    }
    
    return responce;
}

LEDDResponse_t LEDD_Str (const char *dataArray)
{
    uint8 tmpIdx=0;
    LEDDResponse_t response;
    
    while(dataArray[tmpIdx] != '\0')
    {
        response = LEDD_PutCh(dataArray[tmpIdx]);

        if(response != LEDD_OK)
            return response;

        tmpIdx++;
    }
    return LEDD_OK;
}

uint16 LEDD_GetXpos(void)
{
    return txtPos.X;
}

uint16 LEDD_GetYpos(void)
{
    return txtPos.Y;
}

/* [] END OF FILE */
