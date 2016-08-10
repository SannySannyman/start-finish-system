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
#include "DS1307.h"

DS1307_DATE_TIME DS1307_currentTimeDate ;// = {20,11,7,0,1,4,27,7,16};

/*******************************************************************************
* Function Name: DS1307_ReadTimeToStruct
********************************************************************************
*
* Summary:
*  Read current time to struct
*
* Return:
*  status the operation
* Note:
*	if the chip is not connected or is idle hang features
*
*******************************************************************************/
static uint32 DS1307_ReadTimeToStruct(void)
{
    uint8_t data[DS1307_NUMBER_OF_BYTES];
    uint32_t status;    
    int i;
    
    I2C_Start();
    
    /*reset pointer register reading*/

        status = I2C_I2CMasterSendStart(DS1307_SLAVE_ADRESS,I2C_I2C_WRITE_XFER_MODE);
        if(status == I2C_I2C_MSTR_NO_ERROR)
        {
            I2C_I2CMasterWriteByte(DS1307_NULL_ADRESS);
        }else 
        {
            return status;
        }
        I2C_I2CMasterSendStop();
    
    /*read data*/
        I2C_I2CMasterClearStatus();
        status = I2C_I2CMasterSendStart(DS1307_SLAVE_ADRESS,I2C_I2C_READ_XFER_MODE);
        if(I2C_I2C_MSTR_NO_ERROR == status) 
        {
            for(i=0; i<DS1307_NUMBER_OF_BYTES; i++)
            {   
                if(i < DS1307_NUMBER_OF_BYTES-1)
                {
                    data[i] = I2C_I2CMasterReadByte(I2C_I2C_ACK_DATA);
                }
                else
                {
                    data[i] = I2C_I2CMasterReadByte(I2C_I2C_NAK_DATA);
                }
            }
           }
           I2C_I2CMasterSendStop();
    I2C_Stop();
    
    /*write data in struct*/
    
    DS1307_currentTimeDate.second =  (data[DS1307_SEC_ADRESS]& DS1307_SEC_MASK)+(((data[DS1307_SEC_ADRESS]&DS1307_10_SEC_MASK)>>4)*10);
    DS1307_currentTimeDate.minutes = (data[DS1307_MIN_ADRESS]& DS1307_MIN_MASK)+(((data[DS1307_MIN_ADRESS]&DS1307_10_MIN_MASK)>>4)*10);
    DS1307_currentTimeDate.timeFormat = (data[DS1307_HOUR_ADRESS] & DS1307_TIME_FORMAT_MASK)>>6;
    if(DS1307_currentTimeDate.timeFormat == DS1307_12TIME_FORMAT)
    {
        DS1307_currentTimeDate.hours = (data[DS1307_HOUR_ADRESS]& DS1307_HOUR_MASK)+(((data[DS1307_HOUR_ADRESS]&DS1307_10_12HOUR_MASK)>>4)*10); 
        DS1307_currentTimeDate.AmRm = (data[DS1307_HOUR_ADRESS]&DS1307_AM_RM_MASK)>>5;
    }else 
    {
        DS1307_currentTimeDate.hours = (uint32_t)(data[DS1307_HOUR_ADRESS]& DS1307_HOUR_MASK) + (((data[DS1307_HOUR_ADRESS]&DS1307_10_24HOUR_MASK)>>4)*10);
    }
    DS1307_currentTimeDate.day = data[DS1307_DAY_ADRESS]&DS1307_DAY_MASK;
    DS1307_currentTimeDate.date = (data[DS1307_DATE_ADRESS]&DS1307_DATE_MASK) + (((data[DS1307_DATE_ADRESS]&DS1307_10_DATE_MASK)>>4)*10);
    DS1307_currentTimeDate.month  = (data[DS1307_MONTH_ADRESS]&DS1307_MONTH_MASK) + (((data[DS1307_MONTH_ADRESS]&DS1307_10_MONTH_MASK)>>4)*10);
    DS1307_currentTimeDate.year = (data[DS1307_YEAR_ADRESS]&DS1307_YEAR_MASK) + (((data[DS1307_YEAR_ADRESS]&DS1307_10_YEAR_MASK)>>4)*10);
    
    return I2C_I2C_MSTR_NO_ERROR;
}


/*******************************************************************************
* Function Name: DS1307_WriteTimeFromStruct
********************************************************************************
*
* Summary:
*  Write time from struct in chip DS1037
* Note:
*	if the chip is not connected or is idle hang features
*******************************************************************************/
static uint32_t DS1307_WriteTimeFromStruct(void)
{
    uint32_t status;
    int i;
    uint8_t data[DS1307_NUMBER_OF_BYTES] ;
    
    data[DS1307_SEC_ADRESS] = ((DS1307_currentTimeDate.second/10)<<4) + (DS1307_currentTimeDate.second%10);
    data[DS1307_MIN_ADRESS] = ((DS1307_currentTimeDate.minutes/10)<<4) + (DS1307_currentTimeDate.minutes%10);
    if(DS1307_currentTimeDate.timeFormat == DS1307_12TIME_FORMAT)
    {
        data[DS1307_HOUR_ADRESS] = ((DS1307_currentTimeDate.hours/10)<<4) + (DS1307_currentTimeDate.hours%10);
        data[DS1307_HOUR_ADRESS] |= (DS1307_currentTimeDate.AmRm << 5);
        data[DS1307_HOUR_ADRESS] |= (DS1307_currentTimeDate.timeFormat << 6);
    }else
    {
        data[DS1307_HOUR_ADRESS] = ((DS1307_currentTimeDate.hours/10)<<4) + (DS1307_currentTimeDate.hours%10);
        data[DS1307_HOUR_ADRESS] |= (DS1307_currentTimeDate.timeFormat << 6);
    }
    
    
    data[DS1307_DAY_ADRESS] = DS1307_currentTimeDate.day;
    data[DS1307_DATE_ADRESS] = ((DS1307_currentTimeDate.date/10)<<4) + (DS1307_currentTimeDate.date%10);
    data[DS1307_MONTH_ADRESS] = ((DS1307_currentTimeDate.month/10)<<4) + (DS1307_currentTimeDate.month%10);
    data[DS1307_YEAR_ADRESS] = ((DS1307_currentTimeDate.year/10)<<4) + (DS1307_currentTimeDate.year%10);
    
    I2C_Start();
    I2C_I2CMasterClearStatus();
    status = I2C_I2CMasterSendStart(DS1307_SLAVE_ADRESS, I2C_I2C_WRITE_XFER_MODE);
    I2C_I2CMasterWriteByte(DS1307_NULL_ADRESS);
    if(I2C_I2C_MSTR_NO_ERROR == status) 
    {
        for(i=0; i < DS1307_NUMBER_OF_BYTES; i++)
        {
            status = I2C_I2CMasterWriteByte(data[i]);
            if(I2C_I2C_MSTR_NO_ERROR != status)
            {
                break;
            }
        }
    }
    I2C_I2CMasterSendStop();  
	return status;
}

/*******************************************************************************
* Function Name: DS1307_ConstructTime
********************************************************************************
*
* Summary:
*  Create time in BCD format 
* Parameters:
*	timeFormat - DS1307_12TIME_FORMAT or DS1307_24TIME_FORMAT
*	stateAmPm - Am/Pm ...
*	
*******************************************************************************/
static uint32_t DS1307_ConstructTime(uint32 timeFormat, uint32 stateAmPm, uint32 hour, uint32 min, uint32 sec)
{
    uint32 retVal;

    retVal  = timeFormat << DS1307_TIME_FORMAT_OFFSET;
    retVal |= stateAmPm << DS1307_PERIOD_OF_DAY_OFFSET;

    retVal |= (hour / 10u) << DS1307_10_HOURS_OFFSET;
    retVal |= (hour % 10u) << DS1307_HOURS_OFFSET;

    retVal |= (min / 10u) << DS1307_10_MINUTES_OFFSET;
    retVal |= (min % 10u) << DS1307_MINUTES_OFFSET;

    retVal |= (sec / 10u) << DS1307_10_SECONDS_OFFSET;
    retVal |= (sec % 10u) << DS1307_SECONDS_OFFSET;

    return (retVal);
}

/*******************************************************************************
* Function Name: DS1307_ConstructDate
********************************************************************************
*
* Summary:
*  Create date in BCD format 
* Parameters:
*	month, day, year
*	
*******************************************************************************/
static uint32 DS1307_ConstructDate(uint32 month, uint32 day, uint32 year)
{
    
    /*year in D1307 save ten (16 =>2016 year)*/
    year +=2000;
    uint32 retVal;
    uint32 tmpVal = year;

    retVal  = (month / 10u) << DS1307_10_MONTH_OFFSET;
    retVal |= (month % 10u) << DS1307_MONTH_OFFSET;

    retVal |= (day / 10u) << DS1307_10_DAY_OFFSET;
    retVal |= (day % 10u) << DS1307_DAY_OFFSET;

    retVal |= (year / 1000u) << DS1307_1000_YEAR_OFFSET;
    tmpVal %= 1000u;

    retVal |= (tmpVal / 100u) << DS1307_100_YEAR_OFFSET;
    tmpVal %= 100u;

    retVal |= (tmpVal / 10u) << DS1307_10_YEAR_OFFSET;
    retVal |= (tmpVal % 10u) << DS1307_YEAR_OFFSET;

    return (retVal);
}


/*******************************************************************************
* Function Name: DS1307_DateTimeToUnix
********************************************************************************
*
* Summary:
*  Creating time a unix time format
* Parameters:
*	inputTime - time in bcd format
*	inputDate - date in bcd format
* Return:
*	Unix time
*******************************************************************************/
static uint64 DS1307_DateTimeToUnix(uint32 inputDate, uint32 inputTime)
{
    uint32 i;
    uint32 tmpYear;
    uint32 tmpMonth;
    uint32 tmpVal;
    uint64 unixTime;

    unixTime = 0u;
    
    /*GetYear*/
    tmpYear  = ((inputDate & DS1307_1000_YEAR_MASK_UNIX) >> DS1307_1000_YEAR_OFFSET) * 1000u;
    tmpYear += ((inputDate & DS1307_100_YEAR_MASK_UNIX) >> DS1307_100_YEAR_OFFSET) * 100u;
    tmpYear += ((inputDate & DS1307_10_YEAR_MASK_UNIX) >> DS1307_10_YEAR_OFFSET) * 10u;
    tmpYear += (inputDate & DS1307_YEAR_MASK_UNIX) >> DS1307_YEAR_OFFSET;

    /* Calculate seconds from epoch start up to (but not including) current year. */
    for(i = DS1307_YEAR_0; i < tmpYear; i++)
    {
        if(0u != ((((0u == (i % 4Lu)) && (0u != (i % 100Lu))) || (0u == (i % 400Lu)))))
        {
            unixTime += DS1307_SECONDS_PER_LEAP_YEAR;
        }
        else
        {
            unixTime += DS1307_SECONDS_PER_NONLEAP_YEAR;
        }
    }

    /* Calculates how many seconds had elapsed in this year prior to the current month. */
    /*GetMonth*/
    tmpMonth  = ((inputDate & DS1307_10_MONTH_MASK_UNIX) >> DS1307_10_MONTH_OFFSET) * 10u;
    tmpMonth += (inputDate & DS1307_MONTH_MASK_UNIX) >> DS1307_MONTH_OFFSET;
    
    tmpVal = DS1307_daysBeforeMonthTbl1[tmpMonth - 1u];

    if((tmpMonth > 2u) && (0u != (((0u == (tmpYear % 4Lu)) && (0u != (tmpYear % 100Lu))) || (0u == (tmpYear % 400Lu)))))
    {
        tmpVal++;
    }

    /* Calculates how many seconds are in current month days prior to today. */
    unixTime += tmpVal * DS1307_SECONDS_PER_DAY;
    /*GetDay*/
    uint32_t getDay;
    getDay  = ((inputDate & DS1307_10_DAY_MASK_UNIX) >> DS1307_10_DAY_OFFSET) * 10u;
    getDay += (inputDate & DS1307_DAY_MASK_UNIX) >> DS1307_DAY_OFFSET;
    
    unixTime += (getDay - 1u) * DS1307_SECONDS_PER_DAY;

    /* Calculates how many seconds have elapsed today up to the current hour. */
    /*GetHours*/
    tmpVal  = ((inputTime & DS1307_10_HOURS_MASK_UNIX) >> DS1307_10_HOURS_OFFSET) * 10u;
    tmpVal += (inputTime & DS1307_HOURS_MASK_UNIX) >> DS1307_HOURS_OFFSET;
    
    /*Get time format*/
    uint32_t timeFormat= ((0uL != (inputTime & (1uL << DS1307_TIME_FORMAT_OFFSET))) ? (uint32)!DS1307_12TIME_FORMAT :
                                                                                  (uint32)!DS1307_24TIME_FORMAT);

    
    uint32_t AmRm = ((DS1307_PERIOD_OF_DAY_MASK_UNIX == (inputTime & DS1307_PERIOD_OF_DAY_MASK_UNIX)) ? 1Lu : 0Lu);;
    if(((uint32)!DS1307_24TIME_FORMAT != timeFormat) &&
       ((uint32)DS1307_AM == AmRm) && (tmpVal < 12u))
    {
        tmpVal += DS1307_HOURS_PER_HALF_DAY;
    }
    unixTime += tmpVal * DS1307_SECONDS_PER_HOUR;

    /* Calculates how many seconds have elapsed today up to the current minute. */
    /*get Minutes*/
    uint32_t minutes;
    minutes  = ((inputTime & DS1307_10_MINUTES_MASK_UNIX) >> DS1307_10_MINUTES_OFFSET) * 10u;
    minutes += (inputTime & DS1307_MINUTES_MASK_UNIX) >> DS1307_MINUTES_OFFSET;
    
    unixTime += minutes * DS1307_SECONDS_PER_MINUTE;

    /* Add remaining seconds of current minute. */
    uint32_t seconds;
    seconds  = ((inputTime & DS1307_10_SECONDS_MASK_UNIX) >> DS1307_10_SECONDS_OFFSET) * 10u;
    seconds += (inputTime & DS1307_SECONDS_MASK_UNIX) >> DS1307_SECONDS_OFFSET;
    unixTime += seconds;

    return(unixTime);
}


/*******************************************************************************
* Function Name: DS1307_GetUnixTime
********************************************************************************
*
* Summary:
*  Read time for DS1307
* Return:
*	Unix time
* Note:
*	DS1307 automatic start
*******************************************************************************/
uint64_t DS1307_GetUnixTime(void)
{
    uint64_t unixTime;
    uint32_t date;
    uint32_t time;
    uint32_t status;
    
    status = DS1307_ReadTimeToStruct();
    
    if(status == I2C_I2C_MSTR_NO_ERROR)
    {
        date = DS1307_ConstructDate(DS1307_currentTimeDate.month,\
                                    DS1307_currentTimeDate.date, \
                                    DS1307_currentTimeDate.year);
        time = DS1307_ConstructTime(DS1307_currentTimeDate.timeFormat,   \
                                    DS1307_currentTimeDate.AmRm,   \
                                    DS1307_currentTimeDate.hours,   \
                                    DS1307_currentTimeDate.minutes,   \
                                    DS1307_currentTimeDate.second);
        unixTime = DS1307_DateTimeToUnix(date, time);
    }else 
    {
        unixTime = 0;
    }
    return unixTime;
}

/*******************************************************************************
* Function Name: DS1307_SetUnixTime
********************************************************************************
*
* Summary:
*  Write time in DS1307
* Parametrs:
*	unixTime
*******************************************************************************/
void DS1307_SetUnixTime( uint64 unixTime)
{
    uint32 tmpMinute;
    uint32 tmpHour;
    uint32 tmpAmPmState;
    uint32 timeFormat;

    uint32 tmpDay;
    uint32 tmpMonth;
    uint32 tmpYear;

    uint32 tmpVar;
    
    timeFormat = DS1307_24TIME_FORMAT;
    tmpAmPmState = 0u;
    tmpYear = DS1307_YEAR_0;
    tmpVar = DS1307_SECONDS_PER_NONLEAP_YEAR;

    /* Calculates current year value. Variable tmpYear
    *  increments while it contains value greater than number
    *  of seconds in current year.
    */
    while(unixTime > tmpVar)
    {
        unixTime -= tmpVar;
        tmpYear++;
        
        /*Leap year*/
        uint32_t leapYear;
        if(((0u == (tmpYear % 4Lu)) && (0u != (tmpYear % 100Lu))) || (0u == (tmpYear % 400Lu)))
        {
            leapYear = 1uL;
        }
        else
        {
            leapYear = 0uL;
        }
        
        if(0u != leapYear)
        {
            tmpVar = DS1307_SECONDS_PER_LEAP_YEAR;
        }
        else
        {
            tmpVar = DS1307_SECONDS_PER_NONLEAP_YEAR;
        }

    }

    /* Calculates current month value. tmpMonth variable increments
     * while unixTime variable value is greater than time
     * interval from beginning of current year to beginning of
     * current month
    */
    tmpMonth = 1;
    
    uint32_t daysInMonth;
    daysInMonth = DS1307_daysInMonthTbl[tmpMonth - 1u];
    if((uint32)DS1307_FEBRUARY == tmpMonth)
    {
        /*Leap year*/
        uint32_t leapYear;
        if(((0u == (tmpYear % 4Lu)) && (0u != (tmpYear % 100Lu))) || (0u == (tmpYear % 400Lu)))
        {
            leapYear = 1uL;
        }
        else
        {
            leapYear = 0uL;
        }
        
        if(0u != leapYear)
        {
            daysInMonth++;
        }
    }
    
    /*days in month*/
    daysInMonth = DS1307_daysInMonthTbl[tmpMonth - 1u];
    if((uint32)DS1307_FEBRUARY == tmpMonth)
    {
        uint32_t leapYear;
        if(((0u == (tmpYear % 4Lu)) && (0u != (tmpYear % 100Lu))) || (0u == (tmpYear % 400Lu)))
        {
            leapYear = 1uL;
        }
        else
        {
            leapYear = 0uL;
        }
        if(0u != leapYear)
        {
            daysInMonth++;
        }
    }
    tmpVar = daysInMonth * DS1307_SECONDS_PER_DAY;

    while(unixTime >= tmpVar)
    {
        unixTime -= tmpVar;
        tmpMonth++;
            /*days in month*/
        daysInMonth = DS1307_daysInMonthTbl[tmpMonth - 1u];
        if((uint32)DS1307_FEBRUARY == tmpMonth)
        {
            uint32_t leapYear;
            if(((0u == (tmpYear % 4Lu)) && (0u != (tmpYear % 100Lu))) || (0u == (tmpYear % 400Lu)))
            {
                leapYear = 1uL;
            }
            else
            {
                leapYear = 0uL;
            }
            if(0u != leapYear)
            {
               daysInMonth++;
            }
        }
            tmpVar = daysInMonth * DS1307_SECONDS_PER_DAY;
        }

    /* Calculates current day value. */
    tmpDay = (unixTime / DS1307_SECONDS_PER_DAY);
    tmpVar = tmpDay * DS1307_SECONDS_PER_DAY;
    unixTime -= (unixTime >= tmpVar) ? tmpVar : 0u;
    tmpDay += 1u;

    /* Calculates current hour value. If function works in 12-Hour mode,
     * it converts time to 12-Hours mode and calculates AmPm status */
    tmpHour = unixTime / DS1307_SECONDS_PER_HOUR;
    tmpVar  = tmpHour * DS1307_SECONDS_PER_HOUR;
    if((uint32)!DS1307_24TIME_FORMAT != timeFormat)
    {
        if(unixTime > DS1307_UNIX_TIME_PM)
        {
            tmpAmPmState = !DS1307_PM;
            tmpHour = (tmpHour > 12u) ? (tmpHour - 12u) : tmpHour;
        }
        else
        {
            tmpAmPmState = !DS1307_AM;
            tmpHour = (0u != tmpHour) ? tmpHour : 12u;
        }
    }
    unixTime -= (unixTime >= tmpVar) ? tmpVar : 0u;

    /* Calculates current minute.  */
    tmpMinute = unixTime / DS1307_SECONDS_PER_MINUTE;
    tmpVar = tmpMinute * DS1307_SECONDS_PER_MINUTE;

    /* Calculates current second. */
    unixTime -= (unixTime >= tmpVar) ? tmpVar : 0u;
    
    /*construct date*/
    uint32_t tmpDate;
    uint32 tmpVal = tmpYear;
    tmpDate  = (tmpMonth / 10u) << DS1307_10_MONTH_OFFSET;
    tmpDate |= (tmpMonth % 10u) << DS1307_MONTH_OFFSET;

    tmpDate |= (tmpDay / 10u) << DS1307_10_DAY_OFFSET;
    tmpDate |= (tmpDay % 10u) << DS1307_DAY_OFFSET;

    tmpDate |= (tmpYear / 1000u) << DS1307_1000_YEAR_OFFSET;
    tmpVal %= 1000u;

    tmpDate |= (tmpVal / 100u) << DS1307_100_YEAR_OFFSET;
    tmpVal %= 100u;

    tmpDate |= (tmpVal / 10u) << DS1307_10_YEAR_OFFSET;
    tmpDate |= (tmpVal % 10u) << DS1307_YEAR_OFFSET;
    
    /*day of week*/
    uint32_t dayOfWeek;
    uint32_t year;
    year = tmpYear;
    if(tmpMonth < (uint32)DS1307_MARCH)
    {
        tmpMonth = 12u + tmpMonth;
        year--;
    }
    /* Calculates Day of Week using Zeller's congruence algorithms.
    */
    dayOfWeek = (tmpDay + (((tmpMonth + 1u) * 26u) / 10u) + year + (year / 4u) + (6u * (year / 100u)) + (year / 400u)) % 7u;

    /* Makes correction for Saturday. Saturday number should be 7 instead of 0. */
    if(0u == dayOfWeek)
    {
        dayOfWeek = 7;
    }

    /*write data to struct*/
    DS1307_currentTimeDate.second = unixTime;
    DS1307_currentTimeDate.minutes = tmpMinute;
    DS1307_currentTimeDate.hours = tmpHour;
    DS1307_currentTimeDate.AmRm = tmpAmPmState;
    DS1307_currentTimeDate.timeFormat = !timeFormat;
    DS1307_currentTimeDate.day = dayOfWeek;
    DS1307_currentTimeDate.month = tmpMonth;
    DS1307_currentTimeDate.year = tmpYear-2000;
    DS1307_currentTimeDate.date = tmpDay;
    
    /*write in chip*/
    DS1307_WriteTimeFromStruct();
}

/*******************************************************************************
* Function Name: DS1307_Start
********************************************************************************
*
* Summary:
*  Start clock DS1307
*
*******************************************************************************/
void DS1307_Start(void)
{
    uint8_t data ;
    uint32_t status;
    
    data = DS1307_currentTimeDate.second & (~DS1307_OFF_MASK); 
    
    I2C_Start();
    I2C_I2CMasterClearStatus();
    status = I2C_I2CMasterSendStart(DS1307_SLAVE_ADRESS, I2C_I2C_WRITE_XFER_MODE);
    I2C_I2CMasterWriteByte(DS1307_NULL_ADRESS);
    if(I2C_I2C_MSTR_NO_ERROR == status) 
    {
        status = I2C_I2CMasterWriteByte(data);
    }
    I2C_I2CMasterSendStop();
}

/*******************************************************************************
* Function Name: DS1307_Stop
********************************************************************************
*
* Summary:
*  Stop clock DS1307
*
*******************************************************************************/
void DS1307_Stop(void)
{
    uint8_t data ;
    uint32_t status;
    
    data = DS1307_currentTimeDate.second | DS1307_OFF_MASK; 
    
    I2C_Start();
    I2C_I2CMasterClearStatus();
    status = I2C_I2CMasterSendStart(DS1307_SLAVE_ADRESS, I2C_I2C_WRITE_XFER_MODE);
    I2C_I2CMasterWriteByte(DS1307_NULL_ADRESS);
    if(I2C_I2C_MSTR_NO_ERROR == status) 
    {
        status = I2C_I2CMasterWriteByte(data);
    }
    I2C_I2CMasterSendStop();
}
/* [] END OF FILE */