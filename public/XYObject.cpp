




#include "XYObject.h"


unsigned long 	XYObject::m_errno = 0;

unsigned long XYObject::GetErrorNo()
{
#ifdef __LINUX__
	XYObject::m_errno = errno;
	return XYObject::m_errno;
#else
	XYObject::m_errno = ::GetLastError();
#endif
}

XYString XYObject::GetErrorNoToString()
{
	//TODO
	return XYString(XYObject::m_errno);
}
