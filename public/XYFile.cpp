

/*
*

*
*/


#include "XYFile.h"



//=============================================================================================
//#############################################################################################
//=============================================================================================
XYFile::XYFile()
{
	m_FileHand = -1;
	m_strFileName = "";
}

XYFile::~XYFile()
{
	Close();
}

XYString XYFile::ToString()
{
	char sBuf[XY_STRING_BUFFERSIZE] = {0};
	XY_snprintf( sBuf,XY_STRING_BUFFERSIZE,"[%d]:[%s]",m_FileHand,m_strFileName.c_str() );
	return (sBuf);
}


bool XYFile::Equals( const XYObject *obj )
{
	XYFile	*pFile = (XYFile*)obj;
	return ( pFile->m_FileHand == m_FileHand );

}


int XYFile::CompareTo( const XYObject *obj )
{
	XYFile	*pFile = (XYFile*)obj;
	return ( m_FileHand > pFile->m_FileHand );

}

//=============================================================================================
XYString XYFile::ToString(  XYFile * obj )
{
	char sBuf[XY_STRING_BUFFERSIZE] = {0};
	XY_snprintf( sBuf,XY_STRING_BUFFERSIZE,"[%d]:[%s]",(obj->m_FileHand),(obj->m_strFileName).c_str() );
	return (sBuf);
}

bool XYFile::Equals( const XYFile * obj )
{
	return ( obj->m_FileHand == m_FileHand );
}

bool XYFile::Equals( const XYFile * obj1,const XYFile * obj2 )
{
	return ( obj1->m_FileHand == obj2->m_FileHand );
}

int XYFile::CompareTo( const XYFile *obj )
{
	return ( m_FileHand > obj->m_FileHand );

}

int XYFile::CompareTo( const XYFile *obj1,const XYFile *obj2 )
{
	return ( obj1->m_FileHand > obj2->m_FileHand );

}
//=============================================================================================

XYString XYFile::GetCurrentPath( )
{
	char	buf[XY_PATH_MAX] = {0};


	return ( getcwd(buf,XY_PATH_MAX)==NULL?NULL:buf);
	
}

int XYFile::CreatDir( XYString strPath,mode_t mode )
{

    char	sBuf[XY_PATH_MAX+1] = {0};
	XY_strncpy( sBuf,strPath.c_str(),XY_PATH_MAX );
	int nLen = strlen( sBuf );
	sBuf[nLen] = '/';

	
	register unsigned long			lmode = S_IRWXU ;
	if( mode & ENUM_XYFILE_SHARE_READ != 0)
	{
		lmode |=  S_IROTH;
	}
	else if( mode & ENUM_XYFILE_SHARE_WRITE != 0)
	{
		lmode |=  S_IWOTH;
	}
	
	for( int i=0;i<=nLen;i++ )
	{
		if(sBuf[i] == '/')
		{
			sBuf[i] = 0;
			if( access(sBuf,NULL) !=0 )
			{
				if( mkdir(sBuf, lmode)== -1 )
				{
					return GetErrorNo();	
				}
			}
			sBuf[i] = '/';
		}
	}

	return NULL;
	
}



bool XYFile::IsDir( XYString strPath )
{
	struct stat st;
	register int ret = 0;
 
	ret = stat(strPath.c_str(), &st);
	if(ret >= 0)
	{
		if (!S_ISDIR(st.st_mode))
		{
			errno = ENOTDIR;
			ret = -1;
		}
	}
 	return (ret!=-1 );
}


bool XYFile::IsFile( XYString strPath )
{
	struct stat st;
    if(stat(strPath.c_str() , &st) ==0)
        return (S_ISREG(st.st_mode) != 0);//判断文件是否为常规文件
    return false;
}


bool XYFile::IsSpecailFile( XYString strPath )
{
	return ( strcmp(strPath.c_str(), ".") == 0 || strcmp(strPath.c_str(), "..") == 0 );
}


void XYFile::GetFullPath( XYString strPath,XYString strName,char * pFullPath )
{
	strcpy( pFullPath, strPath.c_str() );
    if(pFullPath[strPath.GetLength() - 1] != '/')
        strcat(pFullPath, "/");
    strcat( pFullPath, strName.c_str() );
}


void XYFile::DeleteDir( XYString strPath )
{

	DIR *pDir;
    dirent *pDirent;
    char FullPath[XY_PATH_MAX] = {0};

	if( IsFile(strPath) )
	{
		remove( strPath.c_str() );
		return;
	}
	if( IsDir( strPath ))
	{
		if( (pDir=opendir(strPath.c_str())) == NULL)
		{
			return;
		}
		while( (pDirent=readdir(pDir)) != NULL)
		{
			GetFullPath( strPath,pDirent->d_name,FullPath );
			if(IsSpecailFile( pDirent->d_name ))continue;
			DeleteDir( FullPath );
			rmdir( FullPath );
		}
		rmdir( strPath.c_str() );
	}
	
}

//=============================================================================================

int XYFile::Open( XYString strName,unsigned long mode )
{
	register int				ReturnCOde = -1;
	register long				lmode = S_IRWXU;//用户读写操作
	register long				lFlag = 0;
	
	if( NULL == strName )
	{
		return -1;
	}

	if( mode & ENUM_XYFILE_SHARE_READ != 0)
	{
		lmode |=  S_IROTH;
	}
	else if( mode & ENUM_XYFILE_SHARE_WRITE != 0)
	{
		lmode |=  S_IWOTH;
	}
	else if( mode & ENUM_XYFILE_FLAG_READ != 0)
	{
		lFlag |=  O_RDONLY;
	}
	else if( mode & ENUM_XYFILE_FLAG_WRITE != 0)
	{
		lFlag |= O_WRONLY ;
	}
	else if( (mode & ENUM_XYFILE_FLAG_WRITE != 0) &&  (mode & ENUM_XYFILE_FLAG_READ != 0))
	{
		lFlag |= O_RDWR  ;
	}

	m_FileHand = open( strName.c_str(),lFlag,lmode);
	if( m_FileHand == -1)
	{
		return GetErrorNo();	
	}
	m_strFileName = strName;

	return (1);

	
}


XYString XYFile::GetFileName() const
{
	return (m_strFileName);
}

bool XYFile::IsOpen()
{
	return (m_FileHand >= 0 );
}



bool XYFile::IsExist( XYString strFileName )
{
	return ( access(strFileName.c_str(),NULL) == -1 );
}


void XYFile::Close()
{
	if( m_FileHand >=0 )
	{
		close(m_FileHand);
		m_FileHand = -1;
	}
	m_strFileName = "";
}


int	XYFile::DeleteFile( XYString filename )
{
	if( remove(filename.c_str()) < 0 )
	{
		return GetErrorNo();	
	}
	return (1);
}


int XYFile::RenameFile( XYString oldFileName,XYString newFileName )
{
	if( rename(oldFileName.c_str(),newFileName.c_str()) < 0)
	{
		return GetErrorNo();	
	}
	return (0);
}

//=============================================================================================

int	XYFile::GetFileLength(  XYString strPath )
{

	struct stat st;

	if( stat(strPath.c_str(),&st) < 0)
	{
		return (-1);
	}else{
		return st.st_size;
	}
	
}

int XYFile::GetFileLength()
{
	register int nOldSize = 0;
	register int nSize = 0;
	
	nOldSize = Seek(0,1);
	nSize = Seek(0,2);
	Seek(nOldSize,1);

	return (nSize);
}

int	XYFile::SetFileLength( unsigned long size )
{
	register int			ReturnCode = 0;
	if( ReturnCode=ftruncate(m_FileHand,size) < 0)
	{
		return GetErrorNo();
	}
	return (0);
}

int	XYFile::Seek( int offset,int ltype )
{
	if( lseek( m_FileHand,offset,ltype) < 0)
	{
		return GetErrorNo();
	}
	return (0);
}




int	XYFile::Read( char * sBuf,unsigned long size )
{
	register unsigned long		ReturnCode = 0;

	if( (ReturnCode=read(m_FileHand,sBuf,size)) < 0 )
	{
		return GetErrorNo();
	}
	return (ReturnCode);
}


int XYFile::Write( const char * sBuf,unsigned long size )
{
	register unsigned long		ReturnCode = 0;

	if( (ReturnCode=write(m_FileHand,sBuf,size)) < 0 )
	{
		return GetErrorNo();
	}
	return (ReturnCode);
}


int	XYFile::ReadAll( char * sBuf,unsigned long size )
{
	register unsigned long		ReturnCode = 0;
	if( (ReturnCode=Read(sBuf,size)) != size )
	{
		return (XYERROR_FILE_READALL);
	}
	return (ReturnCode);
}


int	XYFile::WriteAll( const char * sBuf,unsigned long size )
{
	register unsigned long		ReturnCode = 0;
	if( (ReturnCode=Write(sBuf,size)) != size )
	{
		return (XYERROR_FILE_WRITEALL);
	}
	return (ReturnCode);
}

void XYFile::Flush()
{
	fsync(m_FileHand);
}

int	XYFile::ReadString( char * sBuf,unsigned long size )
{
	assert( sBuf != NULL);
	register int				ReturnCode = 0;
	int							iPos;
	
	iPos = Seek( 0,1 );
	if( (ReturnCode = Read(sBuf,size))<=0 )
	{
		Seek(iPos,0);
		return (ReturnCode);
	}
	for ( int i=0;i<ReturnCode;i++ )
	{
		if (	(sBuf[i] == 0x0D || sBuf[i] == 0x0A)
			&& (sBuf[i+1] != 0x0D && sBuf[i+1] != 0x0A)	)
		{
			sBuf[i+1] = 0;
			
			Seek(iPos + i + 1,0);
			
			return i + 1;
		}
	}
	sBuf[ ReturnCode ] = 0;
	Seek( iPos+ReturnCode,0);
	return (ReturnCode);
}

int	XYFile::ReadString( XYString * pOut,unsigned long size )
{
	char 				sTempBuf[XY_STRING_BUFFERSIZE] = {0};
	char	*			pTempString;
	register int		ReturnCode = 0;


	if(size>XY_STRING_BUFFERSIZE)
	{
		pTempString = new char[size];
		if(pTempString == NULL)
		{
			return (XYERROR_FILE_EMPTYSTRING);
		}
	}
	else{
		pTempString = sTempBuf;
	}

	ReturnCode = ReadString( pTempString,size );
	*pOut = pTempString;
	if( pTempString != sTempBuf )
	{
		if(ReturnCode>0)
		{
			pTempString[ReturnCode-1] = 0;
		}
		*pOut = pTempString;
		delete [] pTempString;
	}
	
	return (ReturnCode);

}



XYString XYFile::ReadString( unsigned long size )
{
	XYString			strTempString;
	if( ReadString( &strTempString,size)<=0)
	{
		return "";
	}	
	if(strTempString.GetLength()>2)
	{
		strTempString.TrimRight();
	}
	return (strTempString);
}

int	XYFile::WriteString( const char * sBuf,unsigned long size )
{
	assert(sBuf != NULL );
	register int					ReturnCode = 0 ;

	if( (ReturnCode = Write( sBuf,size ))<0 )
	{
		return (ReturnCode);
	}
	
	return (Write("\r\n",2));	
}

int	XYFile::WriteString( XYString  pIn )
{
	pIn += "\r\n";
	return ( Write(pIn.c_str(),pIn.GetLength() ));
}

int	XYFile::LockFile( unsigned short offset,unsigned int size )
{
	register int				ReturnCode = 0;
	struct flock lock;
	lock.l_whence=SEEK_SET;
	lock.l_start=offset;
	lock.l_len=size;
	lock.l_type = F_WRLCK;
	if( (ReturnCode =fcntl(m_FileHand,F_SETLK,&lock))<0 )
	{
		return GetErrorNo();
	}
	return (ReturnCode);
}

int	XYFile::UnLockFile( unsigned short offset,unsigned int size )
{
	register int				ReturnCode = 0;
	struct flock lock;
	lock.l_whence=SEEK_SET;
	lock.l_start=offset;
	lock.l_len=size;
	lock.l_type = F_UNLCK;
	if( (ReturnCode =fcntl(m_FileHand,F_SETLK,&lock))<0 )
	{
		return GetErrorNo();
	}
	return (ReturnCode);
}

//=============================================================================================
XYDateTime	XYFile::GetCreatDateTime()
{
	struct stat st;
	if(fstat(m_FileHand,&st) <0)
	{
		return (XYDateTime((time_t)0));
	}
	return ( XYDateTime(st.st_ctime));
}

XYDateTime	XYFile::GetModifyDateTime()
{
	struct stat st;
	if(fstat(m_FileHand,&st) <0)
	{
		return (XYDateTime((time_t)0));
	}
	return ( XYDateTime(st.st_mtime));
}

XYDateTime	XYFile::GetAccessDateTime()
{
	struct stat st;
	if(fstat(m_FileHand,&st) <0)
	{
		return (XYDateTime((time_t)0));
	}
	return ( XYDateTime(st.st_atime));
}

XYDateTime	XYFile::GetCreatDateTime( XYString strPath )
{
	struct stat st;
	if(stat(strPath.c_str(),&st) <0)
	{
		return (XYDateTime((time_t)0));
	}
	return ( XYDateTime(st.st_ctime));
}

XYDateTime	XYFile::GetModifyDateTime( XYString strPath )
{
	struct stat st;
	if(stat(strPath.c_str(),&st) <0)
	{
		return (XYDateTime((time_t)0));
	}
	return ( XYDateTime(st.st_mtime));
}

XYDateTime	XYFile::GetAccessDateTime( XYString strPath )
{
	struct stat st;
	if(stat(strPath.c_str(),&st) <0)
	{
		return (XYDateTime((time_t)0));
	}
	return ( XYDateTime(st.st_atime));
}

int	XYFile::SetCreatDateTime( XYDateTime dt )
{
	return (0);
}

int	XYFile::SetModifyDateTime( XYDateTime dt )
{
	struct utimbuf utb;
	utb.modtime = dt.DateTimeToTimet();
	if( (utime(m_strFileName.c_str(),&utb))<0 )
	{
		return GetErrorNo();
	}
	return (0);
}

int	XYFile::SetAccessDateTime( XYDateTime dt )
{
	struct utimbuf utb;
	utb.actime = dt.DateTimeToTimet();
	if( (utime(m_strFileName.c_str(),&utb))<0 )
	{
		return GetErrorNo();
	}
	return (0);
}

int	XYFile::SetCreatDateTime( XYString strFileName,XYDateTime dt )
{
	return (0);
}

int	XYFile::SetModifyDateTime( XYString strFileName,XYDateTime dt )
{
	struct utimbuf utb;
	utb.modtime = dt.DateTimeToTimet();
	if( (utime(strFileName.c_str(),&utb))<0 )
	{
		return GetErrorNo();
	}
	return (0);
}

int	XYFile::SetAccessDateTime( XYString strFileName,XYDateTime dt )
{
	struct utimbuf utb;
	utb.actime = dt.DateTimeToTimet();
	if( (utime(strFileName.c_str(),&utb))<0 )
	{
		return GetErrorNo();
	}
	return (0);
}
//=============================================================================================
//=============================================================================================
//=============================================================================================
//=============================================================================================
//=============================================================================================
//=============================================================================================
//=============================================================================================
//=============================================================================================
