/**
 * @file XYLock.h
 * @brief :
 * @author II_And
 * @version 0.0.1
 * @date 2013-01-17
 */



/*
*


Solaris 库（lib 线程）	Linux POSIX 库（libp 线程）	操作
sema_destroy()			sem_destroy()	销毁信号状态。
sema_init()				sem_init()	初始化信号。
sema_post()				sem_post()	增加信号。
sema_wait()				sem_wait()	阻止信号计数。
sema_trywait()			sem_trywait()	减少信号计数。
mutex_destroy()			pthread_mutex_destroy()	销毁或禁用与互斥对象相关的状态。
mutex_init()			pthread_mutex_init()	初始化互斥变量。
mutex_lock()			pthread_mutex_lock()	锁定互斥对象和块，直到互斥对象被释放。
mutex_unlock()			pthread_mutex_unlock()	释放互斥对象。
cond_broadcast()		pthread_cond_broadcast()	解除对等待条件变量的所有线程的阻塞。
cond_destroy()			pthread_cond_destroy()	销毁与条件变量相关的任何状态。
cond_init()				pthread_cond_init()	初始化条件变量。
cond_signal()			pthread_cond_signal()	解除等待条件变量的下一个线程的阻塞。
cond_wait()				pthread_cond_wait()	阻止条件变量，并在最后释放它。
rwlock_init()			pthread_rwlock_init()	初始化读／写锁。
rwlock_destroy()		pthread_rwlock_destroy()	锁定读／写锁。
rw_rdlock()				pthread_rwlock_rdlock()	读取读／写锁上的锁。
rw_wrlock()				pthread_rwlock_wrlock()	写读／写锁上的锁。
rw_unlock()				pthread_rwlock_unlock()	解除读／写锁。
rw_tryrdlock()			pthread_rwlock_tryrdlock()	读取非阻塞读／写锁上的锁。
rw_trywrlock()		pthread_rwlock_trywrlock()	写非阻塞读／写锁上的锁。


1.信号量
	int sem_init (sem_t* sem, int pshared, unsigned int value);
	int sem_wait (sem_t* sem);
	int sem_trywait(sem_t* sem);
	int sem_post       (sem_t* sem);
	int sem_getvalue (sem_t* sem);
	int sem_destroy   (sem_t* sem);

2.条件变量
	int pthread_cond_init(pthread_cond_t *cond,pthread_condattr_t *cond_attr);
	int pthread_cond_wait(pthread_cond_t *cond,pthread_mutex_t *mutex);
　　	int pthread_cond_timewait(pthread_cond_t *cond,pthread_mutex *mutex,const timespec *abstime);
　　	int pthread_cond_destroy(pthread_cond_t *cond);
　　	int pthread_cond_signal(pthread_cond_t *cond);
　　	int pthread_cond_broadcast(pthread_cond_t *cond); //解除所有线程的阻塞


3.互斥
	int pthread_mutex_init(pthread_mutex_t *mutex,const pthread_mutex_attr_t *mutexattr);
　　	int pthread_mutex_lock(pthread_mutex *mutex);
　　	int pthread_mutex_destroy(pthread_mutex *mutex);
　　	int pthread_mutex_unlock(pthread_mutex *mutex);


4.信号量 system p/v
	int semget(key_t key,int nsems,int semflg);
	int semop(int semid,struct sembuf*sops,unsign ednsops);
	int semctl(int semid,int semnum,int cmd,union semunarg);
	structsembuf{
	ushortsem_num;//semaphore index in array
	shortsem_op;//semaphore operation
	shortsem_flg;//operation flags
	sem_num将要处理的信号量的个数。
	sem_op要执行的操作。
	sem_flg操作标志。
*
*/


#include "XYObject.h"
#include <semaphore.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/sem.h>





class XYLock : public XYObject
{
public:
	XYLock();
	XYLock( const XYString LockName );
	~XYLock();

public:
	XYString						GetLockNameString() const;


//重载Object函数:
public:	
	XYString						ToString();
	bool							Equals( const XYObject *obj );
	int								CompareTo( const XYObject *obj );

protected:
	XYString						m_strLockName;

};

//=============================================================================================
//#############################################################################################
//=============================================================================================

class XYMutex
{
	XYMutex( );
	~XYMutex();

public:
	void							Lock();
	void							UnLock();
	
private:
	pthread_mutex_t					m_mutex;
	
};

//=============================================================================================
//#############################################################################################
//=============================================================================================

class XYCond
{
	XYCond( );
	~XYCond();

public:
	void							Active();
	void							Wait( unsigned long ulmsec );
	
private:
	pthread_cond_t					m_cond;
	
};

//=============================================================================================
//#############################################################################################
//=============================================================================================

class XYSem
{
	XYSem( );
	~XYSem();

public:
	void							Active();
	void							Wait( unsigned long ulmsec );
	
private:
	sem_t							m_semt;
	
};

//=============================================================================================
//#############################################################################################
//=============================================================================================

class XYSemPV : public XYLock
{
	XYSemPV( );
	~XYSemPV();

public:
	int								Creat( const unsigned long lkey );
	int								Open( const unsigned long lkey );
	void							Close();
	void							Lock();
	void							UnLock();
	
	
private:
	int								m_keyt;
	
};

//=============================================================================================
//#############################################################################################
//=============================================================================================


class XYMutexLock : public XYLock
{
public:
	XYMutexLock(  XYMutex 	*pMutex );
	~XYMutexLock();

public:
	void							Attch();
	void							UnAttch();
private:
	XYMutex			*				m_pMutex;
	

};

//=============================================================================================
//#############################################################################################
//=============================================================================================

class XYReadWrite
{
public:
	XYReadWrite( );
	~XYReadWrite();

public:
	void							ReadLock();
	void							WriteLock();
	void							UnLock();
private:
	pthread_rwlock_t				m_rwlock;
	

};

//=============================================================================================
//#############################################################################################
//=============================================================================================



class XYReadWriteLock : public  XYLock
{
public:
	XYReadWriteLock( XYReadWrite * pReadWrite );
	~XYReadWriteLock();

public:
	void							ReadLock();
	void							WriteLock();
	void							UnLock();
private:
	
	XYReadWrite			*			m_pReadWrite;

};

//=============================================================================================
//#############################################################################################
//=============================================================================================


