
#pragma once

#include "XYTypedef.h"
#include "XYString.h"

#define			XYERROR_SYSTEM				0X80000000
#define			XYERROR_BASE				0XA0000000		

#define			XYERROR_STRING_NULL			0

#define			XYERROR_DATETIME_MKTIME				(XYERROR_BASE+1)	//mktime错误
#define			XYERROR_DATETIME_LOCALTIME			(XYERROR_BASE+2)	//localtime错误



#pragma pack(1)

typedef struct
{
	unsigned long 					ulErrorNo;
	const char		*				strModelName;
	const char 		*				strErrorString;
}tagErrorDecs;

#pragma pack()



class XYError
{
public:
	XYError();
	~XYError();

public:
	static unsigned long					GetErrorNo();
	static unsigned long					GetErrorNo( unsigned long lerr );
	static XYString							GetErrorString( unsigned long ulErrorNo );

private:
	static tagErrorDecs						m_tagErrorDecs[];
};



