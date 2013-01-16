#include <stdio.h>

#include "MMTrace.h"




bool MMTrace::m_bTraceIsAlive = true;

MMTrace::MMTrace( const char * &name ):m_strFunctionName( 0 )
{
	if( m_bTraceIsAlive )
	{
		printf("enter MMTrace name=%s\n",name);
		m_strFunctionName  = new string( name );
	}
}




MMTrace::~MMTrace()
{
	if( m_bTraceIsAlive )
	{
		printf("leave MMTrace name=%s\n",m_strFunctionName->c_str());
		delete m_strFunctionName;
	}
}



void MMTrace::Debug( const char*  &msg )
{
	if( m_bTraceIsAlive )
	{
		printf("--[%s]--\n",msg);
	}
}
