#include "XYLogFile.h"





XYLogFile * XYLogFile::g_XYLogFile = NULL;

XYLogFileDes XYLogFile::m_LogFileDesList[] =
{
	{ LOGFILE_NULL,"NULL"},
	{ LOGFILE_INFO,"INFO"},
	{ LOGFILE_WARNING,"WARNING"},
	{ LOGFILE_ERROR,"ERROR"},
	{ LOGFILE_FATAL,"FATAL"},
	
};


XYLogFile::XYLogFile()
{

}


XYLogFile::~XYLogFile()
{

}


XYLogFile * XYLogFile::GetInstance()
{
	if( g_XYLogFile == NULL )
	{
		g_XYLogFile = new XYLogFile();
	}
	return g_XYLogFile;
}


// 打印空信息
// 使用举例:XYNull( "[file]:%s,%d",__FILE__,__LINE__ );
void XYLogFile::XYNull( bool bWrited,const char * msgfmt,...  )
{
	time_t timer;
	struct tm *tmclock;
	timer = time(NULL);
//		tmclock = localtime(&timer);
//		char *stime = asctime(tmclock);
//		int sz = strlen( stime );
//		stime[sz-1] = 0;

	char *stime = ctime(&timer);
	int sz = strlen(stime);
	stime[sz-1] = 0;


	va_list al;
	char sMsg[LOGFILE_BUFFERSIZE] = {0};
	int size = sprintf( sMsg,"[%s]:[file]=%s,[line]=%d,[NULL]=",stime,__FILE__,__LINE__);
	va_start( al,msgfmt );
	int len = vsnprintf( sMsg+size,LOGFILE_BUFFERSIZE-size,msgfmt,al );
	if( len > LOGFILE_BUFFERSIZE ) sMsg[LOGFILE_BUFFERSIZE-1-size] = 0;
	else sMsg[len+size] = 0;
	printf( "%s\n", sMsg );

	va_end( al );

	if( bWrited )
	{//TODO 写入日志进文件

	}

	
}



void XYLogFile::XYInfo( bool bWrited,const char * msgfmt,... )
{
	time_t timer;
	struct tm *tmclock;
	timer = time(NULL);


	char *stime = ctime(&timer);
	int sz = strlen(stime);
	stime[sz-1] = 0;


	va_list al;
	char sMsg[LOGFILE_BUFFERSIZE] = {0};
	int size = sprintf( sMsg,"[INFO]:[%s]:",stime );
	va_start( al,msgfmt );
	int len = vsnprintf( sMsg+size,LOGFILE_BUFFERSIZE-size,msgfmt,al );
	if( len > LOGFILE_BUFFERSIZE ) sMsg[LOGFILE_BUFFERSIZE-1-size] = 0;
	else sMsg[len+size] = 0;
	printf( "%s\n", sMsg );

	va_end( al );

	if( bWrited )
	{//TODO 写入日志进文件

	}


}



void XYLogFile::XYError( bool bWrited,const char * msgfmt,... )
{
	time_t timer;
	struct tm *tmclock;
	timer = time(NULL);


	char *stime = ctime(&timer);
	int sz = strlen(stime);
	stime[sz-1] = 0;


	va_list al;
	char sMsg[LOGFILE_BUFFERSIZE] = {0};
	int size = sprintf( sMsg,"[ERROR]:[%s]:",stime );
	va_start( al,msgfmt );
	int len = vsnprintf( sMsg+size,LOGFILE_BUFFERSIZE-size,msgfmt,al );
	if( len > LOGFILE_BUFFERSIZE ) sMsg[LOGFILE_BUFFERSIZE-1-size] = 0;
	else sMsg[len+size] = 0;
	printf( "%s\n", sMsg );

	va_end( al );

	if( bWrited )
	{//TODO 写入日志进文件

	}


}



void XYLogFile::XYFatal( bool bWrited,const char * msgfmt,... )
{
	time_t timer;
	struct tm *tmclock;
	timer = time(NULL);


	char *stime = ctime(&timer);
	int sz = strlen(stime);
	stime[sz-1] = 0;


	va_list al;
	char sMsg[LOGFILE_BUFFERSIZE] = {0};
	int size = sprintf( sMsg,"[FATAL]:[%s]:",stime );
	va_start( al,msgfmt );
	int len = vsnprintf( sMsg+size,LOGFILE_BUFFERSIZE-size,msgfmt,al );
	if( len > LOGFILE_BUFFERSIZE ) sMsg[LOGFILE_BUFFERSIZE-1-size] = 0;
	else sMsg[len+size] = 0;
	printf( "%s\n", sMsg );

	va_end( al );

	if( bWrited )
	{//TODO 写入日志进文件

	}


}


void XYLogFile::XYWarning( bool bWrited,const char * msgfmt,... )
{
	time_t timer;
	struct tm *tmclock;
	timer = time(NULL);


	char *stime = ctime(&timer);
	int sz = strlen(stime);
	stime[sz-1] = 0;


	va_list al;
	char sMsg[LOGFILE_BUFFERSIZE] = {0};
	int size = sprintf( sMsg,"[WARNING]:[%s]:",stime );
	va_start( al,msgfmt );
	int len = vsnprintf( sMsg+size,LOGFILE_BUFFERSIZE-size,msgfmt,al );
	if( len > LOGFILE_BUFFERSIZE ) sMsg[LOGFILE_BUFFERSIZE-1-size] = 0;
	else sMsg[len+size] = 0;
	printf( "%s\n", sMsg );

	va_end( al );

	if( bWrited )
	{//TODO 写入日志进文件

	}


}


void XYLogFile::XYLog( int level, bool bWrited,const char * msgfmt,... )
{
	time_t timer;
	struct tm *tmclock;
	timer = time(NULL);


	char *stime = ctime(&timer);
	int sz = strlen(stime);
	stime[sz-1] = 0;

	/*
	char sTitle[16] = {0};
	//方案一
	switch( level )
	{
		case LOGFILE_INFO:
			strcpy( sTitle,"INFO");
			break;
		case LOGFILE_WARNING:
			strcpy( sTitle,"WARNING");
			break;
		case LOGFILE_ERROR:
			strcpy( sTitle,"ERROR");
			break;
		case LOGFILE_FATAL:
			strcpy( sTitle,"FATAL");
			break;
		case LOGFILE_NULL:
		default:
			strcpy( sTitle,"NULL");
			break;

	}
	*/



	va_list al;
	char sMsg[LOGFILE_BUFFERSIZE] = {0};
	int size = sprintf( sMsg,"[%s]:[%s]:",m_LogFileDesList[level].sDes,stime );
	va_start( al,msgfmt );
	int len = vsnprintf( sMsg+size,LOGFILE_BUFFERSIZE-size,msgfmt,al );
	if( len > LOGFILE_BUFFERSIZE ) sMsg[LOGFILE_BUFFERSIZE-1-size] = 0;
	else sMsg[len+size] = 0;
	printf( "%s\n", sMsg );

	 


}





