/**
 * @file XYFile.h
 * @brief 文件操作模块
 * @author II_And
 * @version 0.0.1
 * @date 2013-01-14
 */


/*

O_RDONLY                       以只读的方式打开文件
O_WRONLY                      以只写的方式打开文件
O_RDWR                          以读写的方式打开文件
O_CREAT                          创建一个文件
O_EXCL                            仅与O_CREAT连用，如果文件已经存在，则强制open失败
O_NOCTTY                       如果打开的文件是一个终端，就不会成为打开其进程的控制终端
O_TRUNC                         如果文件已经存在，则删除文件的内容，将其长度截为0
O_NOBLOCK                    以非阻塞的方式打开一个文件
O_APPEND                       将文件指针设置到文件的结束处（如果打开来写），以追加的方式打开文件
O_SYNC                            在数据被物理地写入磁盘或其他设备之后操作才返回

S_IRWXU 
00700权限，代表该文件所有者拥有读，写和执行操作的权限
S_IRUSR(S_IREAD)
00400权限，代表该文件所有者拥有可读的权限
S_IWUSR(S_IWRITE)
00200权限，代表该文件所有者拥有可写的权限
S_IXUSR(S_IEXEC)
00100权限，代表该文件所有者拥有执行的权限
S_IRWXG
00070权限，代表该文件用户组拥有读，写和执行操作的权限
S_IRGRP
00040权限，代表该文件用户组拥有可读的权限
S_IWGRP
00020权限，代表该文件用户组拥有可写的权限
S_IXGRP
00010权限，代表该文件用户组拥有执行的权限
S_IRWXO
00007权限，代表其他用户拥有读，写和执行操作的权限
S_IROTH
00004权限，代表其他用户拥有可读的权限
S_IWOTH
00002权限，代表其他用户拥有可写的权限
S_IXOTH
00001权限，代表其他用户拥有执行的权限


*

struct stat {  
        mode_t     st_mode;       //文件对应的模式，文件，目录等  
        ino_t      st_ino;        //inode节点号  
        dev_t      st_dev;        //设备号码  
        dev_t      st_rdev;       //特殊设备号码  
        nlink_t    st_nlink;      //文件的连接数  
        uid_t      st_uid;        //文件所有者  
        gid_t      st_gid;        //文件所有者对应的组  
        off_t      st_size;       //普通文件，对应的文件字节数  
        time_t     st_atime;      //文件最后被访问的时间  
        time_t     st_mtime;      //文件内容最后被修改的时间  
        time_t     st_ctime;      //文件状态改变时间  
        blksize_t st_blksize;     //文件内容对应的块大小  
        blkcnt_t   st_blocks;     //伟建内容对应的块数量  
      };  
* */



#pragma once


#include "XYObject.h"
#include "XYDateTime.h"



#define			XY_PATH_MAX					256



enum
{
	ENUM_XYFILE_FLAG_READ			= 0X01,
	ENUM_XYFILE_FLAG_WRITE			= 0X02,
	ENUM_XYFILE_FLAG_RW				= ENUM_XYFILE_FLAG_READ | ENUM_XYFILE_FLAG_WRITE,
	ENUM_XYFILE_SHARE_READ			= 0X04,
	ENUM_XYFILE_SHARE_WRITE			= 0X08,
	ENUM_XYFILE_SHARE_RW			= ENUM_XYFILE_SHARE_READ | ENUM_XYFILE_SHARE_WRITE,
};



//=============================================================================================
//#############################################################################################
//=============================================================================================

class XYFile : public XYObject
{
public:
	XYFile();
	~XYFile();

public:
	static XYString					GetCurrentPath( );
	static int						CreatDir( XYString strPath,mode_t mode= ENUM_XYFILE_FLAG_RW|ENUM_XYFILE_SHARE_RW);
	static bool						IsDir( XYString strPath );
	static bool						IsFile( XYString strPath );
	static bool						IsSpecailFile( XYString strPath );
	static void						GetFullPath( XYString strPath,XYString stsrName,char * pFullPath );
	static void						DeleteDir( XYString strPath );
	static int						RenameDir( XYString DirName );

public:
	int								Open( XYString strName,unsigned long mode );
	inline XYString					GetFileName() const;
	bool							IsOpen();
	static bool						IsExist( XYString strFileName );
	void							Close();
	static int						DeleteFile( XYString filename );
	static int						RenameFile( XYString oldFileName,XYString newFileName );




public:
	static int						GetFileLength( XYString strPath );
	int								GetFileLength();
	int								SetFileLength( unsigned long size );
	int								Seek( int offset,int ltype );
	int								Read( char * sBuf,unsigned long size );
	int								Write( const char * sBuf,unsigned long size );
	int								ReadAll( char * sBuf,unsigned long size );
	int								WriteAll( const char * sBuf,unsigned long size );
	void							Flush();
	int								ReadString( XYString * pOut,unsigned long size= XY_STRING_BUFFERSIZE );
	int								ReadString( char * sBuf,unsigned long size=XY_STRING_BUFFERSIZE );
	XYString						ReadString( unsigned long size );
	int								WriteString( const char * sBuf,unsigned long size );
	int								WriteString( XYString  pIn );
	int								LockFile( unsigned short offset,unsigned int size );
	int								UnLockFile( unsigned short offset,unsigned int size );


public:
	XYDateTime						GetCreatDateTime();
	XYDateTime						GetModifyDateTime();
	XYDateTime						GetAccessDateTime();
	static XYDateTime				GetCreatDateTime( XYString strPath );
	static XYDateTime				GetModifyDateTime( XYString strPath );
	static XYDateTime				GetAccessDateTime( XYString strPath );
	int								SetCreatDateTime( XYDateTime dt );
	int								SetModifyDateTime( XYDateTime dt );
	int								SetAccessDateTime( XYDateTime dt );	
	static int						SetCreatDateTime( XYString strFileName,XYDateTime dt );
	static int						SetModifyDateTime( XYString strFileName,XYDateTime dt );
	static int						SetAccessDateTime( XYString strFileName,XYDateTime dt );								

//重载Object函数:
public:	
	XYString						ToString();
	bool							Equals( const XYObject *obj );
	int								CompareTo( const XYObject *obj );
public:
	static XYString					ToString( XYFile * obj );
	bool							Equals( const XYFile * obj );
	static bool						Equals( const XYFile * obj1,const XYFile * obj2 );
	int								CompareTo( const XYFile *obj );
	static int						CompareTo( const XYFile *obj1,const XYFile *obj2 );
	


private:
	int								m_FileHand;
	XYString						m_strFileName;

};

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
