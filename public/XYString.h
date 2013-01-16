






#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>
//#include "XYPublic.h"


#define			XY_STRING_BUFFERSIZE						256 //MAX_PATH


extern int XY_snprintf( char *pszBuffer,size_t iBufferSize,const char * msgfmt,...);
extern char * XY_strncpy( char * pszDest,const char * pszSource,size_t size );
extern char * XY_strncat( char * pszDest, char * pszSource,size_t size );



class XYString
{
public:
	XYString();
	XYString( char c );
	XYString( short sIn );
	XYString( unsigned short usIn );
	XYString( int iIn );
	XYString( unsigned int uiIn );
	XYString( long lIn );
	XYString( unsigned long ulIn );
	XYString( float fIn );
	XYString( double dIn );
	XYString( bool bIn );

	XYString( const  char * pSz );
	XYString( const char * pSz,int nStart,int nLen );
	XYString( const  XYString &XYIn );

	virtual ~XYString();



public:
	XYString &		operator = ( const XYString &XYIn );
	XYString &		operator = ( const char * pSz );
	XYString &		operator += ( const XYString &XYIn );
	XYString &		operator += ( const char * pSz );
	XYString 		operator + ( const XYString &XYIn );
	XYString 		operator + ( const char * pSz );
	char			operator [] ( unsigned int iPos );


public:
	friend XYString 	operator + ( const char * pSz,const XYString &XYIn );

	friend bool operator == ( const XYString &XYIn,const char * pSz );
	friend bool operator == ( const char * pSz,const XYString &XYIn );
	friend bool operator == ( const XYString &XYIn1,const XYString &XYIn2 );

	friend bool operator != ( const XYString &XYIn,const char * pSz );
	friend bool operator != ( const char * pSz,const XYString &XYIn );
	friend bool operator != ( const XYString &XYIn1,const XYString &XYIn2 );

	friend bool operator > ( const XYString &XYIn,const char * pSz );
	friend bool operator > ( const char * pSz,const XYString &XYIn );
	friend bool operator > ( const XYString &XYIn1,const XYString &XYIn2 );

	friend bool operator >= ( const XYString &XYIn,const char * pSz );
	friend bool operator >= ( const char * pSz,const XYString &XYIn );
	friend bool operator >= ( const XYString &XYIn1,const XYString &XYIn2 );

	friend bool operator < ( const XYString &XYIn,const char * pSz );
	friend bool operator < ( const char * pSz,const XYString &XYIn );
	friend bool operator < ( const XYString &XYIn1,const XYString &XYIn2 );

	friend bool operator <= ( const XYString &XYIn,const char * pSz );
	friend bool operator <= ( const char * pSz,const XYString &XYIn );
	friend bool operator <= ( const XYString &XYIn1,const XYString &XYIn2 );

public:
	const char	*	c_str();
	long			GetLength();
	void			ToUpper();
	void			ToLower();
	long			ToLong();
	unsigned long	ToULong();
	double			ToDouble();
	bool			ToBool();
	bool			IsEmpty();
	void			Empty();
	int				SetAt( unsigned int iPos,const char value );
	char			GetAt( unsigned int iPos );
	void			Format( const char * pMsgfmt,... );
	XYString		GetUpper();
	XYString		GetLower();
	XYString		GetCopy();//获取XYString副本，深拷贝
	XYString		Left( unsigned int nLen );//获取XYString左边nLen个字符
	XYString		Right( unsigned int nLen );//获取XYString右边nLen个字符
	XYString		Mid( unsigned int iFirst,unsigned int nLen );//获取中间从iFirst开始的nLen个字符
	int				Find( XYString XYFind );//在XYString中查找XYFind,并返回第一次找到的位置
	XYString		FindFrontStr( XYString XYFind );//获取第一次找到位置后的所有字符
	XYString		FindTailStr( XYString XYFind );//获取第一次找到的位置前的所有字体
	void			TrimLeft();//过滤左边的 ' ',0x09(\t,tab),0x0a(\n,换行),0x0d(\r,回车)
	void			TrimRight();//过滤右边的
	void			Trim( const char value=' ' );//过滤特殊字符

protected:
	inline void inner_initString();
	inline int	inner_allocString( size_t size );


public:
	static	XYString		GetUpper( const char * pSz );
	static	XYString		GetLower( const char * pSz );
	static	long			ToLong( const char * pSz );
	static unsigned long	ToULong( const char *pSz );
	static double			ToDouble( const char * pSz );
	static bool				ToBoole( const char * pSz );
	static void				TrimLeft( char * pSz );
	static void				TrimRight( char * pSz );

	static XYString			FormatString( const char * pMsgfmt,...);
	static char *			strncpy( char * pszDest,const char * pszSource,size_t size );
	static char *			strncat( char * pszDest, char * pszSource,size_t size );
	static void				snprintf( char * pSz,size_t size,char * pMsgfmt,... );

protected:
	char	*		m_pStringPtr;
	char			m_szDefaultBuf[XY_STRING_BUFFERSIZE];
	unsigned long	m_lMaxSize;

};
