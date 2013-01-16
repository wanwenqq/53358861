

#pragma once

#define		__LINUX__			0x01
//#define 	__WIN__				0X02





#ifdef		__LINUX__			//linux平台
#include <sys/time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <utime.h>
typedef 		long long				int64;
typedef 		unsigned long long		uint64;

#else						//windows平台
#include <WinBase.h>
typedef 		__int64					int64;
typedef 		unsigned __int64		uint64;

#endif


//=============================================================================================
//#############################################################################################
//=============================================================================================

#define			XYERROR_SYSTEM				0X80000000
#define			XYERROR_BASE				0XA0000000		

#define			XYERROR_STRING_NULL			0

#define			XYERROR_DATETIME_MKTIME				(XYERROR_BASE+1)	//mktime错误
#define			XYERROR_DATETIME_LOCALTIME			(XYERROR_BASE+2)	//localtime错误
#define			XYERROR_FILE_READALL				(XYERROR_BASE+3)	//readall 错误
#define			XYERROR_FILE_WRITEALL				(XYERROR_BASE+4)	//writeall 错误
#define			XYERROR_FILE_EMPTYSTRING			(XYERROR_BASE+5)	//分配内存失败

//=============================================================================================
//#############################################################################################
//=============================================================================================


//=============================================================================================
//#############################################################################################
//=============================================================================================


//=============================================================================================
//#############################################################################################
//=============================================================================================


//=============================================================================================
//#############################################################################################
//=============================================================================================



#pragma pack(1)

typedef struct
{
	unsigned long 					ulErrorNo;
	const char		*				strModelName;
	const char 		*				strErrorString;
}tagErrorDecs;



static tagErrorDecs g_tagErrorDecs[] = 
{
	{XYERROR_DATETIME_MKTIME,"DATETIME","mktime错误"},
	{XYERROR_DATETIME_LOCALTIME,"DATETIME","localtime错误"},
	{XYERROR_FILE_READALL,"XYFILE","readall错误"},
	{XYERROR_FILE_WRITEALL,"XYFILE","writeall错误"},
	{XYERROR_FILE_EMPTYSTRING,"XYFILE","分配内存失败"},
};

#pragma pack()



