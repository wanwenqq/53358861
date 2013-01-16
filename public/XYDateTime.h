/**
 * @file XYDateTime.h
 * @brief 日期时间模块 
 * @author II_And
 * @version 0.0.1
 * @date 2013-01-14
 */


/*
本地时间(locale time)
格林威治时间（Greenwich Mean Time GMT）
时间协调时间 （Universal Time Coordinated UTC）


（1）世界时 
世界时是最早的时间标准。在1884年，国际上将1s确定为全年内每日平均长度的1/8.64×104。以此标准形成的时间系统，称为世界是，即UT1。1972年国际上开始使用国际原子时标，从那以后，经过格林威治老天文台本初子午线的时间便被称为世界时，即UT2，或称格林威治时间（GMT），是对地球转速周期性差异进行校正后的世界时。 
（2）原子时 
1967年，人们利用铯原子振荡周期极为规律的特性，研制出了高精度的原子时钟，将铯原子能级跃迁辐射9192631770周所经历的时间定为1s。现在用的时间就是1971年10月定义的国际原子时，是通过世界上大约200多台原子钟进行对比后，再由国际度量衡局时间所进行数据处理，得出的统一的原子时，简称TAI。 
（3）世界协调时 
世界协调时是以地球自转为基础的时间标准。由于地球自转速度并不均匀，并非每天都是精确的86400原子s，因而导致了自转时间与世界时之间存在18个月有1s的误差。为纠正这种误差，国际地球自转研究所根据地球自转的实际情况对格林威治时间进行增减闰s的调整，与国际度量衡局时间所联合向全世界发布标准时间，这就是所谓的世界协调时（UTC:CoordinatdeUniversalTime）。UTC的表示方式为：年（y）、月（m）、日（d）、时（h）、分（min）、秒（s），均用数字表示

utc时间都是从（1970年01月01日 0:00:00)开始计算秒数的。所看到的UTC时间那就是从1970年这个时间点起到具体时间共有多少秒

linux下存储时间常见的有两种存储方式，一个是从1970年到现在经过了多少秒，一个是用一个结构来分别存储年月日时分秒的。
time_t 这种类型就是用来存储从1970年到现在经过了多少秒

struct timeval，它精确到微妙。
struct timeval
{
    long tv_sec; //秒
    long tv_usec; //微秒
};



而直接存储年月日的是一个结构：
struct tm
{
    int tm_sec;  //秒，正常范围0-59， 但允许至61
    int tm_min;  //分钟，0-59
    int tm_hour; //小时， 0-23
    int tm_mday; //日，即一个月中的第几天，1-31
    int tm_mon;  //月， 从一月算起，0-11  1+p->tm_mon;
    int tm_year;  //年， 从1900至今已经多少年  1900＋ p->tm_year;
    int tm_wday; //星期，一周中的第几天， 从星期日算起，0-6
    int tm_yday; //从今年1月1日到目前的天数，范围0-365
    int tm_isdst; //日光节约时间的旗标
};
需要特别注意的是，年份是从1900年起至今多少年，而不是直接存储如2011年，月份从0开始的，0表示一月，星期也是从0开始的， 0表示星期日，1表示星期一
函数列表:
time_t time(time_t *timer);
double difftime(time_t time1,time_t time2);
struct tm *gmtime(const time_t *timer);
struct tm *localtime(const time_t *timer);
char *asctime(const struct tm *timeptr);
char *ctime(const time_t *timer);
size_t strftime(char *s,size_t maxsize,const char *format,const struct tm *timeptr);
time_t mktime(struct tm *timeptr);
clock_t clock(void);


windows和linux平台在时间处理上有所不同
size_t 在32位和64位表示是一样的
time_t 在32位和64位表示是不一样的
目前相当一部分操作系统使用32位二进制数字表示时间。此类系统的Unix时间戳最多可以使用到格林威治时间2038年01月19日03时14分07秒（二进制：01111111 11111111 11111111 11111111）。其后一秒，二进制数字会变为10000000 00000000 00000000 00000000，发生溢出错误，造成系统将时间误解为1901年12月13日20时45分52秒。这很可能会引起软件故障，甚至是系统瘫痪。使用64位二进制数字表示时间的系统（最多可以使用到格林威治时间292,277,026,596年12月04日15时30分08秒）则基本不会遇到这类溢出问题
windows平台可以用time_t64来避免此问题

*******************************************************************************************************************
* 序號	* 函数				*   类型		*  	精度		*	时间		*
*******************************************************************************************************************
*   1 	* time				*   C系统调用		* 	低		*	<1s		*
*******************************************************************************************************************
*   2 	* clock				*   C系统调用		* 	低		*	<10ms		*
*******************************************************************************************************************
*   3 	* timeGetTime			*   Windows API		* 	中		*	<1ms		*
*******************************************************************************************************************
*   4 	* QueryPerformanceCounter	*   Windows API		* 	高		*	<0.1ms		*
*******************************************************************************************************************
*   5 	* GetTickCount			*   Windows API		* 	中		*	<1ms		*
*******************************************************************************************************************
*   6 	* RDTSC				*   指令		* 	高		*	<0.1ms		*
*******************************************************************************************************************
*   7 	* gettimeofday			*   linux环境下C系统调用	* 	高		*	<0.1ms		*
*******************************************************************************************************************




根据不同的环境调用函数所用时间不同

localtime是非线程安全的
localtime_r 和 localtime_s可以替代


*/


#pragma once
#include <time.h>
#include "XYObject.h"


//=============================================================================================
//=============================================================================================
class XYDateTime : public XYObject
{
public:
	XYDateTime(void);
	XYDateTime( const unsigned short year,const unsigned short month,const unsigned short day );
	XYDateTime( const unsigned short hour,const unsigned short min,const unsigned short second,unsigned short ms );
	XYDateTime( const unsigned short year,const unsigned short month,const unsigned short day,
		 	const unsigned short hour,const unsigned short min,const unsigned short second );
	XYDateTime( time_t tt );
	XYDateTime( const XYDateTime *XYdt );
	~XYDateTime();


public:
	int			GetDateTimeByDateStr( const char * pSzDate,const char * pMsgfmt );
	int			GetDateTimeByTimeStr( const char * pSzTime,const char * pMsgfmt );
	int			GetDateTimeByDateTimeStr( const char * pSzDateTime,const char * pMsgfmt );
	void			SetCurDateTime();
	long			GetCurDateTime();
	XYString		GetCurDateTimeToString();
public:
	XYString		DateTimeToString( const char * pMsgfmt = "%04d-%02d-%02d %02d:%02d:%02d" );
	XYString		DateToString( const char * pMsgfmt = "%04d-%02d-%02d" );
	XYString		TimeToString( const char * pMsgfmt = "%02d:%02d:%02d" );
	time_t			DateTimeToTimet( );
	unsigned long		DateToLong();
	unsigned long		TimeToLong();

public:
	int			GetYear();
	int			GetMon();
	int			GetDay();
	int			GetHour();
	int			GetMin();
	int			Getsec();
	int			GetDayOfWeek();
	int			GetDayOfYear();
	static XYDateTime	Now();

public:
	bool			operator == ( const XYDateTime &XYDT );
	bool			operator != ( const XYDateTime &XYDT );
	bool			operator > ( const XYDateTime &XYDT );
	bool			operator >= ( const XYDateTime &XYDT );
	bool			operator < ( const XYDateTime &XYDT );
	bool			operator <= ( const XYDateTime &XYDT );

public:
	XYDateTime	&	operator = ( const XYDateTime &XYDT );
	XYDateTime	&	operator += ( const int timet );
	XYDateTime	&	operator -= ( const int timet );
	XYDateTime		operator + ( const int timet );
	XYDateTime		operator - ( const int timet );
	

//重载Object函数
public:
	XYString	ToString();
	bool		Equals( const XYObject *obj );
	int		CompareTo( const XYObject *obj );

public:
	bool		Equals( const XYDateTime *pXYDT );
	static bool	Equals( const XYDateTime *pXYDT1 ,const XYDateTime *pXYDT2);
	int		CompareTo ( const XYDateTime *pXYDT );
	static int	CompareTo( const XYDateTime *pXYDT1 ,const XYDateTime *pXYDT2);

	
		


private:
	int		InitDateTime( struct tm * ptm );

private:
	time_t			m_ttData;
	struct	tm	*	m_ptm;


};


//=============================================================================================
//#############################################################################################
//clock() 是1毫秒精度，实际可能达不到，<10ms  实际应用中 sleep会对clock()产生影响
//clock()返回的是clock ticks。是进程从某个特定事件开始，占用CPU的时间的之和（用clock ticks计量）。在GNU系统中，这个特定事件就是指进程的创建。
//在要度量的某个区间的开头和结尾分别计算一次CPU时间，就可以算出这个区间的Processor Time
//=============================================================================================
class XYClockCounter : public XYObject
{
public:
	XYClockCounter();
	virtual ~XYClockCounter();


public:
	void			SetCurTickCounter();
	unsigned long		GetCurTickCounter();
	XYString		GetCurTickCounterToString();
	bool			Equals( const XYClockCounter *pClockCounter );
	int			CompareTo( const XYClockCounter *pClockCounter );

public:
	XYString		ToString();
	bool			Equals( const XYObject *obj );
	int			CompareTo( const XYObject *obj );

protected:
	clock_t			m_ct;
	
	
};

//=============================================================================================
//#############################################################################################
/*==========
QueryPerformanceCounter()这个函数返回高精确度性能计数器的值,它可以微妙为单位计时.但是QueryPerformanceCounter()确切的精确计时的最小单位是与系统有关的,所以,必须要查询系统以得到QueryPerformanceCounter()返回的嘀哒声的频率.QueryPerformanceFrequency()提供了这个频率值,返回每秒嘀哒声的个数.
============*/
//=============================================================================================

class XYMsecCounter 
{
public:
	XYMsecCounter();
	~XYMsecCounter();

public:
	void			SetCurTickCounter();
	unsigned long		GetCurTickCounter();
	XYString		GetCurTickCounterToString();
	XYString		ToString();
private:
	int64			m_msec;
};


//=============================================================================================
//#############################################################################################
/*============
RDTSC指令，在Intel   Pentium以上级别的CPU中，有一个称为“时间戳（Time   Stamp）”的部件，它以64位无符号整型数的格式，记录了自CPU上电以来所经过的时钟周期数。由于目前的CPU主频都非常高，因此这个部件可以达到纳秒级的计时精度。这个精确性是上述几种方法所无法比拟的.在Pentium以上的CPU中，提供了一条机器指令RDTSC（Read   Time   Stamp   Counter）来读取这个时间戳#的数字，并将其保存在EDX:EAX寄存器对中。由于EDX:EAX寄存器对恰好是Win32平台下C++语言保存函数返回值的寄存器，所以我们可以把这条指令看成是一个普通的函数调用，因为RDTSC不被C++的内嵌汇##编器直接支持，所以我们要用_emit伪指令直接嵌入该指令的机器码形式0X0F、0X31
RDTSC 指令的精度可以达到<0.1ms
==============*/
//=============================================================================================
class XYRDTSCCounter
{
public:
	XYRDTSCCounter();
	virtual ~XYRDTSCCounter();


public:
	void			SetCurTickCounter();
	unsigned long		GetCurTickCounter();
	XYString		GetCurTickCounterToString();
	XYString		ToString();

private:
	uint64			CurTickCounter();
	

private:
	uint64			m_msec;

};
//=============================================================================================
//#############################################################################################
//=============================================================================================











