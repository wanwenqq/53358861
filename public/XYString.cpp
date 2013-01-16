#include "XYString.h"




//=============================================================================================
XYString::XYString()
{
	inner_initString();
}


XYString::~XYString()
{
	if( m_pStringPtr != m_szDefaultBuf )
	{
		delete [] m_pStringPtr;
		m_pStringPtr = m_szDefaultBuf;
	}
	m_lMaxSize = XY_STRING_BUFFERSIZE;
}



//=============================================================================================
XYString::XYString( char c)
{
	inner_initString();
	XY_snprintf( m_pStringPtr,m_lMaxSize,"%c",c );
}

XYString::XYString( short sIn )
{
	inner_initString();
	XY_snprintf(m_pStringPtr,m_lMaxSize,"%d",sIn );
}


XYString::XYString( unsigned short usIn )
{
	inner_initString();
	XY_snprintf( m_pStringPtr,m_lMaxSize,"%u",usIn );
}


XYString::XYString( int iIn )
{
	inner_initString();
	XY_snprintf( m_pStringPtr,m_lMaxSize,"%d",iIn );
}


XYString::XYString( unsigned int uiIn )
{
	inner_initString();
	XY_snprintf( m_pStringPtr,m_lMaxSize,"%u",uiIn );

}


XYString::XYString( long lIn )
{
	inner_initString();
	XY_snprintf(m_pStringPtr,m_lMaxSize,"%d",lIn );

}


XYString::XYString( unsigned long ulIn )
{
	inner_initString();
	XY_snprintf(m_pStringPtr,m_lMaxSize,"%u",ulIn );
}


XYString::XYString( float fIn )
{
	inner_initString();
	XY_snprintf(m_pStringPtr,m_lMaxSize,"%f",fIn );
}

XYString::XYString( double dIn )
{
	inner_initString();
	XY_snprintf(m_pStringPtr,m_lMaxSize,"%f",dIn );
}

XYString::XYString( bool bIn )
{
	inner_initString();
	if( bIn )XY_snprintf(m_pStringPtr,m_lMaxSize,"true" );
	else XY_snprintf( m_pStringPtr,m_lMaxSize,"false" );
}


XYString::XYString( const char * pSz )
{
	assert( pSz != NULL);
	inner_initString();
	inner_allocString(strlen(pSz));

	XY_strncpy( m_pStringPtr,pSz,m_lMaxSize );

}


XYString::XYString( const char * pSz,int nStart,int nLen )
{
	assert( pSz != NULL);

	inner_initString();
	int nLeft = strlen( pSz) - nStart;
	int nSize =  nLeft>nLen ? nLeft:nLen;
	inner_allocString( nSize );

	XY_strncpy( m_pStringPtr,pSz+nStart,m_lMaxSize );
	


}


//=============================================================================================

XYString::XYString( const XYString &XYIn )
{
	inner_initString();
	inner_allocString( strlen(XYIn.m_pStringPtr) );

	XY_strncpy( m_pStringPtr,XYIn.m_pStringPtr,m_lMaxSize );
}


void XYString::inner_initString()
{
	m_pStringPtr = m_szDefaultBuf;
	m_lMaxSize = XY_STRING_BUFFERSIZE;
	m_pStringPtr[0] = 0;
}

int XYString::inner_allocString( size_t size )
{
	register size_t		ReturnCode;
	char * pszTemp;

	assert(m_pStringPtr != NULL );

	ReturnCode  = size + 1;
	if( m_lMaxSize>ReturnCode )
	{
		return (1);
	}

	pszTemp = m_pStringPtr;
	ReturnCode = (ReturnCode>>8+1)<<8;
	m_pStringPtr = new char[ReturnCode];
	if( m_pStringPtr == NULL )
	{
		m_pStringPtr = pszTemp;
		return (-1);//需要定义错误码，以便debug及信息查找
	}
	XY_strncpy(m_pStringPtr,pszTemp,m_lMaxSize );
	m_lMaxSize = ReturnCode;

	if( pszTemp != m_szDefaultBuf )
	{
		delete [] pszTemp;
	}

	return (1);



}
//=============================================================================================
XYString & XYString::operator = ( const XYString & XYIn )
{
	inner_allocString( strlen(XYIn.m_pStringPtr) );
	XY_strncpy(m_pStringPtr,XYIn.m_pStringPtr,m_lMaxSize );


	return (*this);

}

XYString & XYString::operator = ( const char * pSz )
{
	inner_allocString( strlen( pSz ) );
	XY_strncpy( m_pStringPtr,pSz,m_lMaxSize );


	return (*this);
}

XYString &	XYString::operator += ( const XYString &XYIn )
{

	inner_allocString( strlen(m_pStringPtr)+strlen(XYIn.m_pStringPtr) );
	XY_strncat( m_pStringPtr,XYIn.m_pStringPtr,m_lMaxSize );


	return (*this);
}

XYString &	XYString::operator += ( const char * pSz )
{
	inner_allocString( strlen(m_pStringPtr)+strlen(pSz));
	XY_strncat( m_pStringPtr,const_cast<char*>(pSz),m_lMaxSize );


	return (*this);


}


XYString 	XYString::operator + ( const XYString &XYIn )
{
	XYString	tempString( m_pStringPtr );
	tempString += XYIn;

	return (tempString);

}


XYString 	XYString::operator + ( const char * pSz )
{
	XYString	tempString (  m_pStringPtr );
	tempString += pSz;


	return (tempString);
}

XYString 	operator + ( const char * pSz,const XYString &XYIn )
{
	
	XYString	tempString ( pSz );
	tempString += XYIn;

	return (tempString);
}

char XYString::operator [] ( unsigned int iPos )
{
	if( iPos >= m_lMaxSize )return (0);
	else return (m_pStringPtr[iPos]);
}





//=============================================================================================
bool operator == ( const char * pSz,const XYString &XYIn )
{
	return ( strcmp(pSz,XYIn.m_pStringPtr)==0?true:false);
}

bool operator == ( const XYString &XYIn,const char * pSz )
{
	return ( strcmp(XYIn.m_pStringPtr,pSz)==0?true:false);
}

bool operator == ( const XYString &XYIn1,const XYString &XYIn2 )
{
	return ( strcmp(XYIn1.m_pStringPtr,XYIn2.m_pStringPtr)==0?true:false);
}

///////////
bool operator != ( const char * pSz,const XYString &XYIn )
{
	return ( strcmp(pSz,XYIn.m_pStringPtr)==0?false:true);
}

bool operator != ( const XYString &XYIn,const char * pSz )
{
	return ( strcmp(XYIn.m_pStringPtr,pSz)==0?false:true);
}

bool operator != ( const XYString &XYIn1,const XYString &XYIn2 )
{
	return ( strcmp(XYIn1.m_pStringPtr,XYIn2.m_pStringPtr)==0?false:true);
}

///////////
bool operator > ( const char * pSz,const XYString &XYIn )
{
	return ( strcmp(pSz,XYIn.m_pStringPtr)>0?true:false);
}

bool operator > ( const XYString &XYIn,const char * pSz )
{
	return ( strcmp(XYIn.m_pStringPtr,pSz)>0?true:false);
}

bool operator > ( const XYString &XYIn1,const XYString &XYIn2 )
{
	return ( strcmp(XYIn1.m_pStringPtr,XYIn2.m_pStringPtr)>0?true:false);
}

///////////
bool operator >= ( const char * pSz,const XYString &XYIn )
{
	return ( strcmp(pSz,XYIn.m_pStringPtr)>=0?true:false);
}

bool operator >= ( const XYString &XYIn,const char * pSz )
{
	return ( strcmp(XYIn.m_pStringPtr,pSz)>=0?true:false);
}

bool operator >= ( const XYString &XYIn1,const XYString &XYIn2 )
{
	return ( strcmp(XYIn1.m_pStringPtr,XYIn2.m_pStringPtr)>=0?true:false);
}

///////////
bool operator < ( const char * pSz,const XYString &XYIn )
{
	return ( strcmp(pSz,XYIn.m_pStringPtr)<0?true:false);
}

bool operator < ( const XYString &XYIn,const char * pSz )
{
	return ( strcmp(XYIn.m_pStringPtr,pSz)<0?true:false);
}

bool operator < ( const XYString &XYIn1,const XYString &XYIn2 )
{
	return ( strcmp(XYIn1.m_pStringPtr,XYIn2.m_pStringPtr)<0?true:false);
}

///////////
bool operator <= ( const char * pSz,const XYString &XYIn )
{
	return ( strcmp(pSz,XYIn.m_pStringPtr)<=0?true:false);
}

bool operator <= ( const XYString &XYIn,const char * pSz )
{
	return ( strcmp(XYIn.m_pStringPtr,pSz)<=0?true:false);
}

bool operator <= ( const XYString &XYIn1,const XYString &XYIn2 )
{
	return ( strcmp(XYIn1.m_pStringPtr,XYIn2.m_pStringPtr)<=0?true:false);
}


//=============================================================================================
const char * XYString::c_str()
{
	return (m_pStringPtr);
}

long XYString::GetLength()
{
	return (strlen(m_pStringPtr));
}

void XYString::ToUpper()
{
	register unsigned int	i;
	for( i=0;i<strlen(m_pStringPtr);i++ )
	{
		if( m_pStringPtr[i]>= 'a' && m_pStringPtr[i]<='z' )
		{
			m_pStringPtr[i] -= 32;
		}
	}
}

void XYString::ToLower()
{
	register unsigned int	i;
	for( i=0;i<strlen(m_pStringPtr);i++ )
	{
		if( m_pStringPtr[i]>= 'A' && m_pStringPtr[i]<='Z' )
		{
			m_pStringPtr[i] += 32;
		}
	}
}



long XYString::ToLong()
{
	return ( strtol(m_pStringPtr,NULL,10) );
}

unsigned long XYString::ToULong()
{
	return ( strtoul(m_pStringPtr,NULL,10) );
}

double XYString::ToDouble()
{
	return ( strtod(m_pStringPtr,NULL) );
}

bool XYString::ToBool()
{
	//TODO 需要区分不同平台windows 下是stricmp linux下是strcasecmp
	return ( strcasecmp(m_pStringPtr,"true")==0?true:false);

}



bool XYString::IsEmpty()
{
	assert( m_pStringPtr != NULL);

	return ( m_pStringPtr[0]==0?true:false );
}

void XYString::Empty()
{
	assert( m_pStringPtr != NULL );
	m_pStringPtr[0] = 0;
}

int XYString::SetAt( unsigned int iPos,const char value )
{
	assert( m_pStringPtr != NULL );
	if( iPos >= m_lMaxSize )
	{
		return (-1);
	}
	m_pStringPtr[iPos] = value;
	return (0);
}


char XYString::GetAt( unsigned int iPos )
{
	assert( m_pStringPtr != NULL );
	if( iPos >= m_lMaxSize )
	{
		return (-1);
	}

	return m_pStringPtr[iPos];

}

void XYString::Format( const char * pMsgfmt,... )
{
	va_list al;
	va_start( al,pMsgfmt );
	vsnprintf( m_pStringPtr,m_lMaxSize,pMsgfmt,al );
	va_end( al );
}


//=============================================================================================
XYString XYString::GetUpper()
{
	XYString	XYTempString(m_pStringPtr);

	XYTempString.ToUpper();
	return XYTempString;

}

XYString XYString::GetLower()
{
	XYString	XYTempString(m_pStringPtr);

	XYTempString.ToLower();
	return XYTempString;
}

XYString XYString::GetCopy()
{
	XYString XYTempString(this);

	return XYTempString;
}

XYString XYString::Left( unsigned int nLen )
{
	XYString	XYTempString;
	register int		ReturnCode;

	ReturnCode = strlen(m_pStringPtr);
	if( nLen > ReturnCode )
	{
		return "";
	}
	if( XYTempString.inner_allocString( nLen+1 )<0 )
	{
		return "";
	}
	memcpy( XYTempString.m_pStringPtr,m_pStringPtr,nLen );
	XYTempString.m_pStringPtr[ nLen ] = 0;
	
	return XYTempString;
}

XYString XYString::Right( unsigned int nLen )
{
	XYString		XYTempString;
	register int	ReturnCode;

	ReturnCode = strlen( m_pStringPtr );
	if( nLen > ReturnCode )
	{
		return "";
	}
	if( XYTempString.inner_allocString( nLen+1 )<0 )
	{
		return "";
	}
	memcpy( XYTempString.m_pStringPtr,m_pStringPtr+ReturnCode-nLen,nLen );
	XYTempString.m_pStringPtr[nLen] = 0;

	return XYTempString;
}

XYString XYString::Mid( unsigned int iFirst,unsigned int nLen )
{
	XYString			XYTempString;
	register int		ReturnCode;

	ReturnCode = strlen( m_pStringPtr );
	if( (iFirst+nLen) > ReturnCode )
	{
		return "";
	}
	if( XYTempString.inner_allocString( nLen+1 )<0 )
	{
		return "";
	}

	memcpy(XYTempString.m_pStringPtr,m_pStringPtr+iFirst,nLen );
	XYTempString.m_pStringPtr[nLen] = 0;
	return XYTempString;

}

int XYString::Find( XYString XYFind )
{
	register char *		pTemp;
	if( (pTemp=strstr(m_pStringPtr,XYFind.c_str())) == NULL )
	{
		return (-1);
	}

	return pTemp-m_pStringPtr;
}


XYString XYString::FindTailStr( XYString XYFind )
{
	register char	*		pTemp;
	register int			ReturnCode;

	if( (pTemp=strstr(m_pStringPtr,XYFind.c_str())) == NULL)
	{
		return "";
	}

	ReturnCode = (unsigned int)(pTemp-m_pStringPtr);
	int nLen = strlen(m_pStringPtr) - ReturnCode;
	XYString	XYTempString;
	if( XYTempString.inner_allocString( nLen+1 ) <0 )
	{
		return "";
	}
	memcpy( XYTempString.m_pStringPtr,m_pStringPtr+ReturnCode,nLen );
	XYTempString.m_pStringPtr[nLen] = 0;
	return XYTempString;

}

XYString XYString::FindFrontStr( XYString XYFind )
{
	register char	*		pTemp;
	register int			ReturnCode;

	if( (pTemp= strstr(m_pStringPtr,XYFind.c_str())) == NULL )
	{
		return "";
	}

	ReturnCode = (unsigned int)(pTemp-m_pStringPtr);
	XYString	XYTempString;
	if( XYTempString.inner_allocString( ReturnCode+1 ) < 0 )
	{
		return "";
	}

	memcpy( XYTempString.m_pStringPtr,m_pStringPtr,ReturnCode );
	XYTempString.m_pStringPtr[ReturnCode] = 0;
	return XYTempString;

}


void XYString::TrimLeft()
{
	register int			ReturnCode;
	register int			ioffset;

	ReturnCode = strlen( m_pStringPtr );
	ioffset = ReturnCode;

	for( int i=0;i<ReturnCode;i++ )
	{
		if(m_pStringPtr[i] != ' ' 
			&& m_pStringPtr[i] != 0x09
			&& m_pStringPtr[i] != 0x0a
			&& m_pStringPtr[i] != 0x0d )
		{
			ioffset = i;			
			break;
		}
	}
	if( ioffset != 0 )
	{
		memmove( m_pStringPtr,m_pStringPtr+ioffset,ReturnCode-ioffset );
		m_pStringPtr[ReturnCode-ioffset] = 0;
	}
}

void XYString::TrimRight()
{
	register int			ReturnCode;
	register int			ioffset;

	ReturnCode = strlen( m_pStringPtr );
	ioffset = ReturnCode;
	for( int i=ReturnCode-1;i>=0;i-- )
	{
		if(m_pStringPtr[i] != ' ' 
			&& m_pStringPtr[i] != 0x09
			&& m_pStringPtr[i] != 0x0a
			&& m_pStringPtr[i] != 0x0d )
		{
			ioffset = i;
			break;
		}
	}
	if( ioffset != ReturnCode-1 )
	{
		m_pStringPtr[ioffset+1] = 0;
	}else
	{
		inner_allocString( ReturnCode+1 );
		m_pStringPtr[ReturnCode] = 0;
	}
}


void XYString::Trim( const char value )
{
	register int			ReturnCode;
	ReturnCode = strlen(m_pStringPtr);
	char	*				pTemp = new char[ReturnCode+1];

	for( pTemp=m_pStringPtr;*m_pStringPtr!=0;++m_pStringPtr)
	{
		if(*m_pStringPtr != value )
		{
			*pTemp++ = *m_pStringPtr;
		}
	}
	*pTemp = 0;
	XY_strncpy( m_pStringPtr,pTemp,strlen(pTemp) );

}

//=============================================================================================
XYString XYString::GetUpper( const char * pSz )
{
	XYString	XYTempString( pSz );

	XYTempString.ToUpper();
	return XYTempString;
}

XYString XYString::GetLower( const char * pSz )
{
	XYString	XYTempString( pSz );

	XYTempString.ToLower();
	return XYTempString;
}

long XYString::ToLong( const char * pSz )
{	
	return ( strtol(pSz,NULL,10) );
}

unsigned long XYString::ToULong( const char * pSz )
{
	return ( strtoul(pSz,NULL,10) );
}

double XYString::ToDouble( const char * pSz )
{
	return ( strtod(pSz,NULL) );
}

bool XYString::ToBoole( const char * pSz )
{	
	//TODO 需要区分不同平台windows 下是stricmp linux下是strcasecmp
	return (strcasecmp(pSz,"true")==0?true:false);
}

void XYString::TrimLeft(  char * pSz )
{
	register int			ReturnCode;
	register int			ioffset;

	ReturnCode = strlen( pSz );
	ioffset = ReturnCode;

	for( int i=0;i<ReturnCode;i++ )
	{
		if(pSz[i] != ' ' 
			&& pSz[i] != 0x09
			&& pSz[i] != 0x0a
			&& pSz[i] != 0x0d )
		{
			ioffset = i;			
			break;
		}
	}
	if( ioffset != 0 )
	{
		memmove( pSz,pSz+ioffset,ReturnCode-ioffset );
		pSz[ReturnCode-ioffset] = 0;
	}

}

void XYString::TrimRight(  char *  pSz)
{
	register int			ReturnCode;
	register int			ioffset;

	ReturnCode = strlen( pSz );
	ioffset = ReturnCode;
	for( int i=ReturnCode-1;i>=0;i-- )
	{
		if(pSz[i] != ' ' 
			&& pSz[i] != 0x09
			&& pSz[i] != 0x0a
			&& pSz[i] != 0x0d )
		{
			ioffset = i;
			break;
		}
	}
	if( ioffset != ReturnCode-1 )
	{
		pSz[ioffset+1] = 0;
	}else
	{//TODO  此处有异议
		pSz[ReturnCode-1] = 0;
	}

}

XYString XYString::FormatString( const char * pMsgfmt,... )
{
	char			szTemp[XY_STRING_BUFFERSIZE*10] = {0};
	va_list			al;

	va_start( al,pMsgfmt );
	vsnprintf( szTemp,XY_STRING_BUFFERSIZE*10,pMsgfmt,al );
	va_end( al );

	return szTemp;
	
}

char * XYString::strncpy( char * pszDest,const char * pszSource,size_t size )
{
	return ( XY_strncpy( pszDest,pszSource,size ));
}

char * XYString::strncat( char * pszDest, char * pszSource,size_t size )
{
	return ( XY_strncat( pszDest,pszSource,size  ) );
}

void XYString::snprintf( char * pSz,size_t size,char * pMsgfmt,... )
{
	assert( pSz != NULL );
	assert( size >0 );

	if( pSz == NULL || size <=0 )
	{
		return;
	}

	va_list al;
	va_start( al,pMsgfmt );
	vsnprintf( pSz,size,pMsgfmt,al );
	va_end( al );

	pSz[ size-1 ]=0;

}


//=============================================================================================

int XY_snprintf( char * pszBuffer,size_t iBufferSize,const char * msgfmt,...)
{
	assert( pszBuffer != NULL );
	assert( iBufferSize > 0 );

	if( pszBuffer == NULL || iBufferSize <= 0 ) return (0);

	va_list al;
	va_start( al,msgfmt );
	int nlen = vsnprintf( pszBuffer,iBufferSize,msgfmt,al );
	va_end( al );
	pszBuffer[iBufferSize -1] = 0;

	return nlen;
}

char * XY_strncpy( char * pszDest,const char * pszSource,size_t size )
{
	assert( pszDest != NULL);
	assert( pszSource != NULL );
	assert( size > 0 );

	if( pszDest == NULL || pszSource == NULL || size <= 0 ) return (NULL);
	char * pszTemp = strncpy( pszDest,pszSource,size );
	pszDest[size-1] = 0;

	return (pszTemp);


}


char * XY_strncat( char * pszDest, char * pszSource,size_t size )
{
	assert( pszDest != NULL );
	assert( pszSource != NULL );
	assert ( size >0 );

	if( pszDest == NULL || pszSource == NULL || size <= 0 ) return (NULL);
	char *pszTemp = strncat( pszDest,pszSource,size );
	pszDest[strlen(pszDest)-1] = 0;

	return pszTemp;

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

