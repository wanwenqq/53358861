/**
 * @file XYObject.h
 * @brief Object基类
 * @author II_And
 * @version 0.0.1
 * @date 2013-01-14
 */



/*



*/

#pragma once
#include "XYTypedef.h"
#include "XYString.h"


#define		__LINUX__			0x01
//#define 	__WIN__				0X02



#define		XYOBJECT_BUFFERSIZE				256


class XYObject
{
public:
	XYObject(){};
	~ XYObject(){};
public:
	virtual XYString 	ToString() = 0;
	virtual bool 		Equals( const XYObject *obj ) = 0;
	virtual int			CompareTo( const XYObject *obj ) = 0;

	static unsigned long			GetErrorNo(); 
	
	static XYString	GetErrorNoToString();


private:
	static unsigned long					m_errno;
};

