


#include "XYLock.h"



XYLock::XYLock()
{
	m_strLockName = "XYLock";
}

XYLock::XYLock( const XYString LockName ):m_strLockName(LockName)
{
	
}

XYLock::~XYLock()
{
	m_strLockName  = "";
}


XYString XYLock::GetLockNameString() const
{
	return m_strLockName;
}
XYString XYLock::ToString()
{
	return m_strLockName;
}


bool XYLock::Equals( const XYObject * obj )
{
	XYLock	*pLock = (XYLock*)obj;
	return (m_strLockName == pLock->m_strLockName);
}


int XYLock::CompareTo( const XYObject * obj )
{
	//TODO do nothing
	return (0);
}


//=============================================================================================
//#############################################################################################
//=============================================================================================

XYMutex::XYMutex()
{
	pthread_mutex_init( &m_mutex,NULL );
}

XYMutex::~XYMutex()
{
	pthread_mutex_destroy ( &m_mutex );
}


void XYMutex::Lock()
{
	pthread_mutex_lock( &m_mutex );
}


void XYMutex::UnLock()
{
	pthread_mutex_unlock( &m_mutex );
} 



//=============================================================================================
//#############################################################################################
//=============================================================================================

XYCond::XYCond()
{
	pthread_cond_init( &m_cond,NULL );
}

XYCond::~XYCond()
{
	pthread_cond_destroy( &m_cond );
}


void XYCond::Active()
{
	pthread_cond_signal( &m_cond );
}

void XYCond::Wait( unsigned long ulmsec )
{
	struct timespec				abstime;

	abstime.tv_nsec = ulmsec;
	pthread_cond_timedwait(&m_cond,NULL,&abstime);
}



//=============================================================================================
//#############################################################################################
//=============================================================================================

XYSem::XYSem()
{
	sem_init( &m_semt,0,1 );
}

XYSem::~XYSem()
{
	sem_destroy( &m_semt );
}


void XYSem::Active()
{
	sem_post( &m_semt );
}

void XYSem::Wait( unsigned long ulmsec  )
{
	struct timespec				abstime;

	abstime.tv_nsec = ulmsec;
	sem_timedwait( &m_semt,&abstime );
}

//=============================================================================================
//#############################################################################################
//=============================================================================================
XYSemPV::XYSemPV()
{
	m_keyt = -1;
}

XYSemPV::~XYSemPV()
{
	m_keyt = -1;
}


int XYSemPV::Creat( const unsigned long lkey )
{	
	if ( (m_keyt = semget(lkey,1,0666|IPC_CREAT)) == -1 )
	{
		return GetErrorNo();
	}

	return(1);
}

int XYSemPV::Open( const unsigned long lkey )
{	
	if ( (m_keyt = semget(lkey,1,0666)) == -1 )
	{
		return GetErrorNo();
	}

	return(1);
}


void XYSemPV::Lock()
{
	struct sembuf					sb;
		
	sb.sem_num = 0;
	sb.sem_op = -1;
	sb.sem_flg = ~(IPC_NOWAIT | SEM_UNDO);
	semop(m_keyt,&sb,1);
}


void XYSemPV::UnLock()
{
	struct sembuf					sb;
		
	sb.sem_num = 0;
	sb.sem_op = 1;
	sb.sem_flg = ~(IPC_NOWAIT | SEM_UNDO);
	semop(m_keyt,&sb,1);
}

void XYSemPV::Close()
{
	if ( m_keyt != -1 )
	{
		semctl(m_keyt,0,IPC_RMID,0);
		m_keyt = -1;
	}
}



//=============================================================================================
//#############################################################################################
//=============================================================================================

XYMutexLock::XYMutexLock( XYMutex *pMutex ):m_pMutex(pMutex)
{
	
}

XYMutexLock::~XYMutexLock( )
{
	UnAttch();
}

void XYMutexLock::Attch()
{
	if(m_pMutex != NULL)
	{
		m_pMutex->Lock();
	}
}

void XYMutexLock::UnAttch()
{
	if(m_pMutex != NULL)
	{
		m_pMutex->UnLock();
		m_pMutex = NULL;
	}
}


//=============================================================================================
//#############################################################################################
//=============================================================================================
XYReadWrite::XYReadWrite()
{
	pthread_rwlock_init( &m_rwlock,NULL );
}


XYReadWrite::~XYReadWrite()
{
	pthread_rwlock_destroy( &m_rwlock );
}

void XYReadWrite::ReadLock()
{
	pthread_rwlock_rdlock( &m_rwlock  );
}

void XYReadWrite::WriteLock()
{
	pthread_rwlock_wrlock( &m_rwlock  );
} 

void XYReadWrite::UnLock()
{
	pthread_rwlock_unlock( &m_rwlock  );
}  
//=============================================================================================
//#############################################################################################
//=============================================================================================
XYReadWriteLock::XYReadWriteLock( XYReadWrite * pReadWrite ) :m_pReadWrite(pReadWrite)
{
	
}

XYReadWriteLock::~XYReadWriteLock()
{
	
}

void XYReadWriteLock::ReadLock()
{
	if(m_pReadWrite != NULL)
	{
		m_pReadWrite->ReadLock();
	}
	
}


void XYReadWriteLock::WriteLock()
{
	if(m_pReadWrite != NULL)
	{
		m_pReadWrite->WriteLock();
	}
	
} 

void XYReadWriteLock::UnLock()
{
	if(m_pReadWrite != NULL)
	{
		m_pReadWrite->UnLock();
		m_pReadWrite = NULL;
	}

}  
//=============================================================================================
//#############################################################################################
//=============================================================================================



//=============================================================================================
//#############################################################################################
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
//=============================================================================================
