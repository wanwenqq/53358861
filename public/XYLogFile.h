#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>


#define				LOGFILE_NULL					1
#define				LOGFILE_INFO					2
#define				LOGFILE_WARNING					3
#define				LOGFILE_ERROR					4
#define				LOGFILE_FATAL					5


const int			LOGFILE_BUFFERSIZE		=		1024;


#pragma pack( 1 )
typedef struct
{
	int		level;
	char  	sDes[16];
}XYLogFileDes;

#pragma pack()


class XYLogFile
{
public:
	XYLogFile();
	~XYLogFile();

public:
	static	XYLogFile * GetInstance();


private:
	static XYLogFile * g_XYLogFile;



public:
	void			XYNull( bool bWrited,const char * msgfmt,... );
	void			XYWarning( bool bWrited,const char * msgfmt,... );
	void			XYInfo( bool bWrited,const char * msgfmt,... );
	void			XYError( bool bWrited,const char * msgfmt,... );
	void			XYFatal( bool bWrited,const char * msgfmt,... );


	void			XYLog( int level,bool bWrited,const char * msgfmt,... );


private:
	static	XYLogFileDes		m_LogFileDesList[];



};
