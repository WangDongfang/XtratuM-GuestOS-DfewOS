/****************************************Copyright (c)*****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**                                      
**                                 http://www.embedtools.com
**
**--------------File Info----------------------------------------------------------------------------------
** File name:               timeLib.h
** Last modified Date:      2011-7-2 14:12:25
** Last Version:            1.0.0
** Descriptions:            This file support a software timer lib structure and APIs
**
**---------------------------------------------------------------------------------------------------------
** Created by:              WangDongfang
** Last modified Date:      2011-7-2 14:12:25
** Version:                 1.0.0
** Descriptions:            This file support a software timer lib structure and APIs
**
**---------------------------------------------------------------------------------------------------------
** Modified by:             WangDongfang
** Modified date:           2011-10-21
** Version:                 1.0.0
** Description:             porting to dfewos
**
**********************************************************************************************************/

#ifndef __timeLib_H
#define __timeLib_H

#define OS_DFEWOS

#ifdef OS_VXWORKS

#include <vxWorks.h>
#include <tickLib.h>
#include <semLib.h>
#include <sysLib.h>
#include <stdio.h>

#elif defined(OS_DFEWOS)

#include <dfewos.h>
#define printf      serial_printf
#define STATUS      OS_STATUS
#define OK          OS_STATUS_OK
#define ERROR       OS_STATUS_ERROR
#define tickGet()   tick_get()
#define UINT32      uint32
#define sysClkRateGet() SYS_CLK_RATE

#endif

/**********************************************************************************************************
  The structure to store time elements
**********************************************************************************************************/
struct time_socket {
    int iYear;	                                                   /* years since 0        - [1000,9999] */
    int iMon;		                                               /* months since January     - [1, 12] */
    int iDay;	                                                   /* day of the month         - [1, 31] */

    int iHour;	                                                   /* hours after midnight     - [0, 23] */
    int iMin;		                                               /* minutes after the hour   - [0, 59] */
    int iSec;		                                               /* seconds after the minute - [0, 59] */

    int iWday;	                                                   /* days since Sunday        - [0,  6] */
    int iYday;	                                                   /* days since January 1     - [0,365] */
};
typedef struct time_socket  TIME_SOCKET;

/**********************************************************************************************************
** Function name:           setYear
** Descriptions:            设置年份
** input parameters:        iYear: 年份, 取值范围: [1000, 9999]
** output parameters:       NONE
** Returned value:          OK:    设置成功
                            ERROR: 设置失败
** Created by:              WangDongfang
** Created Date:            2010-07-02
**---------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**---------------------------------------------------------------------------------------------------------
**********************************************************************************************************/
STATUS setYear(int iYear);

/**********************************************************************************************************
** Function name:           setMonth
** Descriptions:            设置月份
** input parameters:        iMonth: 月份, 取值范围: [1, 12]
** output parameters:       NONE
** Returned value:          OK:     设置成功
                            ERROR:  设置失败
** Created by:              WangDongfang
** Created Date:            2010-07-02
**---------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**---------------------------------------------------------------------------------------------------------
**********************************************************************************************************/
STATUS setMonth(int iMonth);

/**********************************************************************************************************
** Function name:           setDay
** Descriptions:            设置日期
** input parameters:        iDay:  日期, 不能超出当前月份最大天数, 取值范围: [1, 31]
** output parameters:       NONE
** Returned value:          OK:    设置成功
                            ERROR: 设置失败
** Created by:              WangDongfang
** Created Date:            2010-07-02
**---------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**---------------------------------------------------------------------------------------------------------
**********************************************************************************************************/
STATUS setDay(int iDay);

/**********************************************************************************************************
** Function name:           setHour
** Descriptions:            设置时
** input parameters:        iHour: 时, 取值范围: [0, 23]
** output parameters:       NONE
** Returned value:          OK:    设置成功
                            ERROR: 设置失败
** Created by:              WangDongfang
** Created Date:            2010-07-02
**---------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**---------------------------------------------------------------------------------------------------------
**********************************************************************************************************/
STATUS setHour(int iHour);

/**********************************************************************************************************
** Function name:           setMinute
** Descriptions:            设置分
** input parameters:        iMinute: 分, 取值范围: [0, 59]
** output parameters:       NONE
** Returned value:          OK:      设置成功
                            ERROR:   设置失败
** Created by:              WangDongfang
** Created Date:            2010-07-02
**---------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**---------------------------------------------------------------------------------------------------------
**********************************************************************************************************/
STATUS setMinute(int iMinute);

/**********************************************************************************************************
** Function name:           setSecond
** Descriptions:            设置秒
** input parameters:        iSecond: 秒, 取值范围: [0, 59]
** output parameters:       NONE
** Returned value:          OK:    设置成功
                            ERROR: 设置失败
** Created by:              WangDongfang
** Created Date:            2010-07-02
**---------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**---------------------------------------------------------------------------------------------------------
**********************************************************************************************************/
STATUS setSecond(int iSecond);

/**********************************************************************************************************
** Function name:           timeSet
** Descriptions:            设置年,月,日,时,分,秒
** input parameters:        tsNowTime: 时间结构体。其成员变量iYear, iMon, iDay, iHour, iMin, iSec必须设置
                                       为以上所指定的范围, 成员变量iWday, iYday忽略
** output parameters:       NONE
** Returned value:          OK:    设置成功
                            ERROR: 设置失败
** Created by:              WangDongfang
** Created Date:            2010-07-02
**---------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**---------------------------------------------------------------------------------------------------------
**********************************************************************************************************/
STATUS timeSet(TIME_SOCKET tsNowTime);

/**********************************************************************************************************
** Function name:           getYear
** Descriptions:            读取当前年份
** input parameters:        NONE
** output parameters:       NONE
** Returned value:          当前年份
** Created by:              WangDongfang
** Created Date:            2010-07-02
**---------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**---------------------------------------------------------------------------------------------------------
**********************************************************************************************************/
int getYear();

/**********************************************************************************************************
** Function name:           getYear
** Descriptions:            读取当前月份
** input parameters:        NONE
** output parameters:       NONE
** Returned value:          当前月份 - [1, 12]
** Created by:              WangDongfang
** Created Date:            2010-07-02
**---------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**---------------------------------------------------------------------------------------------------------
**********************************************************************************************************/
int getMonth();

/**********************************************************************************************************
** Function name:           getDay
** Descriptions:            读取当前日期
** input parameters:        NONE
** output parameters:       NONE
** Returned value:          当前日期 - [1, 31]
** Created by:              WangDongfang
** Created Date:            2010-07-02
**---------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**---------------------------------------------------------------------------------------------------------
**********************************************************************************************************/
int getDay();

/**********************************************************************************************************
** Function name:           getHour
** Descriptions:            读取当前时
** input parameters:        NONE
** output parameters:       NONE
** Returned value:          当前时 - [0, 23]
** Created by:              WangDongfang
** Created Date:            2010-07-02
**---------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**---------------------------------------------------------------------------------------------------------
**********************************************************************************************************/
int getHour();

/**********************************************************************************************************
** Function name:           getMinute
** Descriptions:            读取当前分
** input parameters:        NONE
** output parameters:       NONE
** Returned value:          当前分 - [0, 59]
** Created by:              WangDongfang
** Created Date:            2010-07-02
**---------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**---------------------------------------------------------------------------------------------------------
**********************************************************************************************************/
int getMinute();

/**********************************************************************************************************
** Function name:           getSecond
** Descriptions:            读取当前秒
** input parameters:        NONE
** output parameters:       NONE
** Returned value:          当前秒 - [0, 59]
** Created by:              WangDongfang
** Created Date:            2010-07-02
**---------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**---------------------------------------------------------------------------------------------------------
**********************************************************************************************************/
int getSecond();

/**********************************************************************************************************
** Function name:           timeGet
** Descriptions:            读取当前时间: 年,月,日,时,分,秒,星期,本年度日期
** input parameters:        NONE
** output parameters:       NONE
** Returned value:          当前时间, 结构体中各成员变量所代表的含义如下:
                            iYear:  年 [1000, 9999]
                            iMon :  月 [1, 12]
                            iDay :  日 [1, 31]
                            iHour:  时 [0, 23]
                            iMin :  分 [0, 59]
                            iSec :  秒 [0, 59]
                            iWday:  星期 [0, 6] 星期日为 0
                            iYay :  本年度日期 [0, 365] 1月1日为 0
** Created by:              WangDongfang
** Created Date:            2010-07-02
**---------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**---------------------------------------------------------------------------------------------------------
**********************************************************************************************************/
TIME_SOCKET timeGet();
#endif                                                                  /*  __timeLib_H                  */

/**********************************************************************************************************
  FILE END
**********************************************************************************************************/
