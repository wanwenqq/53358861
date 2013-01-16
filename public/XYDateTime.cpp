



#include "XYDateTime.h"



XYDateTime::XYDateTime()
{
	m_ttData = 0;
	struct tm 			s_tm;

	s_tm.tm_year = 1900;
	s_tm.tm_mon = 1;
	s_tm.tm_mday = 1;
	s_tm.tm_hour = 0;
	s_tm.tm_min = 0;
	s_tm.tm_sec = 0;
	InitDateTime( &s_tm );

}


XYDateTime::XYDateTime( const unsigned short year,const unsigned short month,const unsigned short day )
{
	struct tm 			s_tm;

	s_tm.tm_year = year-1900;
	s_tm.tm_mon = month-1;
	s_tm.tm_mday = day;
	s_tm.tm_hour = 0;
	s_tm.tm_min = 0;
	s_tm.tm_sec = 0;
//	m_ttData = mktime( &s_tm );
//	m_ptm = *localtime( &m_ttData );
	InitDateTime( &s_tm );
	
}

XYDateTime::XYDateTime( const unsigned short hour,const unsigned short min,const unsigned short second,unsigned short ms )
{
	struct tm 			s_tm;

	s_tm.tm_year = 90;
	s_tm.tm_mon = 0;
	s_tm.tm_mday = 1;
	s_tm.tm_hour = hour;
	s_tm.tm_min = min;
	s_tm.tm_sec = second;

	InitDateTime( &s_tm );
}

XYDateTime::XYDateTime( const unsigned short year,const unsigned short month,const unsigned short day,
		 	const unsigned short hour,const unsigned short min,const unsigned short second )
{
	struct tm 			s_tm;

	s_tm.tm_year = year-1900;
	s_tm.tm_mon = month-1;
	s_tm.tm_mday = day;
	s_tm.tm_hour = hour;
	s_tm.tm_min = min;
	s_tm.tm_sec = second;

	InitDateTime( &s_tm );
}


XYDateTime::XYDateTime( time_t tt )
{
	m_ttData = tt;
//	m_ptm = gmtime( &m_ttData );//GMT时间
	m_ptm = localtime( &m_ttData );//TODO 此处localtime非线程安全
	assert( m_ptm != NULL);
}

XYDateTime::XYDateTime( const XYDateTime *XYdt )
{
	m_ttData = XYdt->m_ttData;
	m_ptm = XYdt->m_ptm;
}



XYDateTime::~XYDateTime()
{

}
//=============================================================================================
int XYDateTime::GetDateTimeByDateStr( const char * pSzDate,const char * pMsgfmt )
{
	
	int year,month,day,hour;
        sscanf( pSzDate,pMsgfmt,&year,&month,&day );    

 	struct tm s_tm;
	s_tm.tm_year = year-1900;
	s_tm.tm_mon = month-1;
	s_tm.tm_mday = day;
	s_tm.tm_hour = 0;
	s_tm.tm_min = 0;
	s_tm.tm_sec = 0;

	return InitDateTime( &s_tm );
}

/**
 * @brief 
 *
 * @param pSzTime
 * @param pMsgfmt
 *
 * @return 
 */
int XYDateTime::GetDateTimeByTimeStr( const char * pSzTime,const char * pMsgfmt )
{
	
	int hour,minutes,seconds;
        sscanf( pSzTime,pMsgfmt,&hour,&minutes,&seconds );    

 	struct tm s_tm;
	s_tm.tm_year = 1900;
	s_tm.tm_mon = 0;
	s_tm.tm_mday = 1;
	s_tm.tm_hour = hour;
	s_tm.tm_min = minutes;
	s_tm.tm_sec = seconds;

	return InitDateTime( &s_tm );
}


int XYDateTime::GetDateTimeByDateTimeStr( const char * pSzDateTime,const char * pMsgfmt )
{
	
	int year,month,day,hour,minutes,seconds;
        sscanf( pSzDateTime,pMsgfmt,&year,&month,&day,&hour,&minutes,&seconds );    

 	struct tm s_tm;
	s_tm.tm_year = year-1900;
	s_tm.tm_mon = month-1;
	s_tm.tm_mday = day;
	s_tm.tm_hour = hour;
	s_tm.tm_min = minutes;
	s_tm.tm_sec = seconds;

	return InitDateTime( &s_tm );
}

int XYDateTime::InitDateTime( struct tm * ptm )
{
	if( m_ttData = mktime( ptm ) == -1)
	{
		return (XYERROR_DATETIME_MKTIME);
	}

	//m_ptm = *localtime( &m_ttData );//TODO 此处localtime非线程安全
	m_ptm = ptm;
	return (1);
}
//=============================================================================================

void XYDateTime::SetCurDateTime()
{
	m_ttData = time(NULL);
}


long XYDateTime::GetCurDateTime()
{
	return ( time(NULL)-m_ttData );
}

XYString XYDateTime::GetCurDateTimeToString()
{
	register long			ReturnCode;
	char				szTemp[XYOBJECT_BUFFERSIZE] = {0};

	ReturnCode = GetCurDateTime();
	XY_snprintf(szTemp,XYOBJECT_BUFFERSIZE,"%d:%d:%d",ReturnCode / 3600,(ReturnCode % 3600) / 60,ReturnCode % 60);
	return szTemp;	
}

XYString XYDateTime::DateTimeToString( const char * pMsgfmt )
{
	char 		szTemp[XYOBJECT_BUFFERSIZE] = {0};

	XY_snprintf(szTemp,XYOBJECT_BUFFERSIZE,
						pMsgfmt,
						m_ptm->tm_year + 1900,
						m_ptm->tm_mon + 1,
						m_ptm->tm_mday,
						m_ptm->tm_hour,
						m_ptm->tm_min,
						m_ptm->tm_sec	);

	return szTemp;
}


XYString XYDateTime::DateToString( const char * pMsgfmt )
{
	char 		szTemp[XYOBJECT_BUFFERSIZE] = {0};

	XY_snprintf(szTemp,XYOBJECT_BUFFERSIZE,
						pMsgfmt,
						m_ptm->tm_year + 1900,
						m_ptm->tm_mon + 1,
						m_ptm->tm_mday
						);
							

	return szTemp;
}


XYString XYDateTime::TimeToString( const char * pMsgfmt )
{
	char 		szTemp[XYOBJECT_BUFFERSIZE] = {0};

	XY_snprintf(szTemp,XYOBJECT_BUFFERSIZE,
						pMsgfmt,						
						m_ptm->tm_hour,
						m_ptm->tm_min,
						m_ptm->tm_sec	);

	return szTemp;
}


time_t XYDateTime::DateTimeToTimet( )
{
	return ( m_ttData );
}

unsigned long XYDateTime::DateToLong()
{
	return ( (m_ptm->tm_year+1900)*1000 + (m_ptm->tm_mon+1)*100 + m_ptm->tm_mday );
}

unsigned long XYDateTime::TimeToLong()
{
	return ( m_ptm->tm_hour*1000 + m_ptm->tm_min*100 + m_ptm->tm_sec );
}

//=============================================================================================
int XYDateTime::GetYear()
{
	return ( m_ptm->tm_year+1900 );
}

int XYDateTime::GetMon()
{
	return ( m_ptm->tm_mon+1 );
}


int XYDateTime::GetDay()
{
	return ( m_ptm->tm_mday );
}

int XYDateTime::GetHour()
{
	return ( m_ptm->tm_hour );
}

int XYDateTime::GetMin()
{
	return ( m_ptm->tm_min );
}

int XYDateTime::Getsec()
{
	return ( m_ptm->tm_sec );
}

int XYDateTime::GetDayOfWeek()
{
	return ( m_ptm->tm_wday );
}

int XYDateTime::GetDayOfYear()
{
	return ( m_ptm->tm_yday );
}

XYDateTime XYDateTime::Now()
{
	return ( XYDateTime(time(NULL)));
}

//=============================================================================================
bool XYDateTime::operator == ( const XYDateTime &XYDT )
{
	return ( m_ttData == XYDT.m_ttData?true:false);
} 

bool XYDateTime::operator != ( const XYDateTime &XYDT )
{
	return ( m_ttData != XYDT.m_ttData?true:false);
} 

bool XYDateTime::operator > ( const XYDateTime &XYDT )
{
	return ( m_ttData > XYDT.m_ttData?true:false);
} 

bool XYDateTime::operator >= ( const XYDateTime &XYDT )
{
	return ( m_ttData >= XYDT.m_ttData?true:false);
} 

bool XYDateTime::operator < ( const XYDateTime &XYDT )
{
	return ( m_ttData < XYDT.m_ttData?true:false);
} 

bool XYDateTime::operator <= ( const XYDateTime &XYDT )
{
	return ( m_ttData <= XYDT.m_ttData?true:false);
} 
//=============================================================================================
XYDateTime & XYDateTime::operator = ( const XYDateTime &XYDT )
{
	m_ttData = XYDT.m_ttData;
	return (  *this );
}

XYDateTime & XYDateTime::operator += ( const int timet )
{
	m_ttData += timet;
	return (  *this );
}

XYDateTime & XYDateTime::operator -= ( const int timet )
{
	m_ttData -= timet;
	return (  *this );
}

XYDateTime XYDateTime::operator + ( const int timet )
{
	return ( XYDateTime(m_ttData+timet) );
}

XYDateTime XYDateTime::operator - ( const int timet )
{
	return ( XYDateTime(m_ttData-timet) );
}
//=============================================================================================
XYString XYDateTime::ToString()
{
	char 		szTemp[XYOBJECT_BUFFERSIZE] = {0};

	XY_snprintf(szTemp,XYOBJECT_BUFFERSIZE,
						"%04d-%02d-%02d %02d:%02d:%02d",
						m_ptm->tm_year + 1900,
						m_ptm->tm_mon + 1,
						m_ptm->tm_mday,
						m_ptm->tm_hour,
						m_ptm->tm_min,
						m_ptm->tm_sec	);

	return szTemp;	
}

bool XYDateTime::Equals( const XYObject *obj )
{
	XYDateTime *pDateTime = (XYDateTime*)obj;
	return ( pDateTime->m_ttData == m_ttData?true:false );
}

bool XYDateTime::Equals( const 	XYDateTime *pXYDT )
{
	return ( pXYDT->m_ttData == m_ttData?true:false);
}

bool XYDateTime::Equals( const XYDateTime *pXYDT1 ,const XYDateTime *pXYDT2)
{
	return ( pXYDT1->m_ttData == pXYDT2->m_ttData?true:false);
}

int XYDateTime::CompareTo( const XYObject *obj )
{
	XYDateTime *pDateTime = (XYDateTime*)obj;
	return ( m_ttData-pDateTime->m_ttData );
}

int XYDateTime::CompareTo ( const XYDateTime *pXYDT )
{	
	return ( m_ttData-pXYDT->m_ttData );
}

int XYDateTime::CompareTo( const XYDateTime *pXYDT1 ,const XYDateTime *pXYDT2)
{
	return ( pXYDT1->m_ttData-pXYDT2->m_ttData );
}
//=============================================================================================
//#############################################################################################
//=============================================================================================
XYClockCounter::XYClockCounter()
{
	m_ct = 0;
}

XYClockCounter::~XYClockCounter()
{
	
}

void XYClockCounter::SetCurTickCounter()
{
	m_ct = clock();
}

unsigned long XYClockCounter::GetCurTickCounter()
{
	return (unsigned long)(clock() - m_ct);
}


XYString XYClockCounter::GetCurTickCounterToString()
{
	char szTemp[XYOBJECT_BUFFERSIZE] = {0};
	
	unsigned long lTemp = GetCurTickCounter();
	XY_snprintf( szTemp,XYOBJECT_BUFFERSIZE,"%ld[%ld]",lTemp/1000,lTemp%1000 );

	return szTemp;	
}

XYString XYClockCounter::ToString()
{
	char szTemp[XYOBJECT_BUFFERSIZE] = {0};

	XY_snprintf(szTemp,XYOBJECT_BUFFERSIZE,"%ld",m_ct);

	return szTemp;	
}

bool XYClockCounter::Equals( const XYObject *obj )
{
	XYClockCounter *pClockCounter = (XYClockCounter*)obj;
	return ( m_ct == pClockCounter->m_ct?true:false);
}


bool XYClockCounter::Equals( const XYClockCounter *pClockCounter )
{
	return ( m_ct == pClockCounter->m_ct?true:false);
}

int XYClockCounter::CompareTo( const XYObject *obj )
{
	XYClockCounter *pClockCounter = (XYClockCounter*)obj;
	return ( m_ct - pClockCounter->m_ct);
}

int XYClockCounter::CompareTo( const XYClockCounter *pClockCounter )
{
	return ( m_ct - pClockCounter->m_ct);
}




//=============================================================================================
//#############################################################################################
//=============================================================================================

XYMsecCounter::XYMsecCounter()
{
	m_msec = 0;
}

XYMsecCounter::~XYMsecCounter()
{

}

void XYMsecCounter::SetCurTickCounter()
{
#ifdef __LINUX__
	struct timeval			s_tv;
	gettimeofday( &s_tv,NULL );
	m_msec = s_tv.tv_sec * 1000000 + s_tv.tv_usec;
#else
	LARGE_INTEGER					sttemp;
		
	QueryPerformanceCounter(&sttemp);
	m_msec = sttemp.QuadPart;
#endif
}


unsigned long XYMsecCounter::GetCurTickCounter()
{
#ifdef __LINUX__
	struct timeval			s_tv;
	gettimeofday( &s_tv,NULL );
	return (s_tv.tv_sec * 1000000 + s_tv.tv_usec-m_msec)/1000;
#else
	LARGE_INTEGER					sttemp,sttemp1;
		
	QueryPerformanceCounter(&sttemp);
	QueryPerformanceFrequency(&sttemp); 
	return((unsigned long)((1000 * (double)(sttemp.QuadPart - m_msec)) / sttemp1.QuadPart));
#endif
}


XYString XYMsecCounter::GetCurTickCounterToString()
{
	char szTemp[XYOBJECT_BUFFERSIZE] = {0};
	
	unsigned long lTemp = GetCurTickCounter();
	XY_snprintf( szTemp,XYOBJECT_BUFFERSIZE,"%ld[%ld]",lTemp/1000,lTemp%1000 );

	return szTemp;	
}

XYString XYMsecCounter::ToString()
{
	char szTemp[XYOBJECT_BUFFERSIZE] = {0};
#ifdef __LINUX__
	XY_snprintf(szTemp,XYOBJECT_BUFFERSIZE,"%lld",GetCurTickCounter());
#else
	XY_snprintf(szTemp,XYOBJECT_BUFFERSIZE,"%l64d",GetCurTickCounter());
#endif
	return szTemp;		
}
//=============================================================================================
//#############################################################################################
//=============================================================================================
XYRDTSCCounter::XYRDTSCCounter()
{
	m_msec = 0;
}

XYRDTSCCounter::~XYRDTSCCounter()
{
	
}

void XYRDTSCCounter::SetCurTickCounter()
{
	m_msec = CurTickCounter();
}



uint64 XYRDTSCCounter::CurTickCounter()
{
#ifdef __LINUX__
{
#if defined (__i386__) 
	uint64 x; 
	__asm__ volatile("rdtsc":"=A"(x)); 
	return x;
#elif defined (__x86_64__)
	 unsigned hi,lo;  
	__asm__ volatile("rdtsc":"=a"(lo),"=d"(hi));  
	return ((uint64)lo)|(((uint64)hi)<<32);  
#endif
}
#else
{
	__asm  
    {  
        _emit 0x0F;  
        _emit 0x31;  
    }  
}
#endif
}


unsigned long XYRDTSCCounter::GetCurTickCounter()
{
	return ( (unsigned long)((CurTickCounter()-m_msec)/(1600.0*1000)) );//此处是cpu频率
}


XYString XYRDTSCCounter::GetCurTickCounterToString()
{
	char szTemp[XYOBJECT_BUFFERSIZE] = {0};
	
	unsigned long		lTemp = GetCurTickCounter();
	XY_snprintf( szTemp,XYOBJECT_BUFFERSIZE,"%ld[%ld]",lTemp/1000,lTemp%1000 );
	return szTemp;	
}


XYString XYRDTSCCounter::ToString()
{
	char szTemp[XYOBJECT_BUFFERSIZE] = {0};
#ifdef __LINUX__
	XY_snprintf(szTemp,XYOBJECT_BUFFERSIZE,"%llu",GetCurTickCounter());
#else
	XY_snprintf(szTemp,XYOBJECT_BUFFERSIZE,"%l64d",GetCurTickCounter());
#endif
	return szTemp;	
}


//=============================================================================================
//=============================================================================================
//=============================================================================================
//=============================================================================================
//=============================================================================================
//=============================================================================================
//=============================================================================================
//=============================================================================================
//=============================================================================================
//=============================================================================================
//=============================================================================================

