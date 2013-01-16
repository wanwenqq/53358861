/*****============================================
		*	À≥–Ú∂”¡–
		*
============================================******/

#include <iostream>
using namespace std;

template <typename T> class sequencestack
{
public:
	sequencestack(int sz):m_nrear(0),m_front(0),m_nMaxSize(sz),m_nCount(0){
		m_data = new T[sz];
		if (m_data == NULL)
		{
			return;
		}
	}

	~sequencestack(){
		delete [] m_data;
	}


public:
	void Empty();
	bool Append(const T e);
	T		Delete();
	T		Get();
	void Print();


public:
	bool IsEmpty();
	bool IsFull();

private:
	int m_nrear;
	int m_front;
	int m_nMaxSize;
	int m_nCount;
	T	*m_data;
};


template <typename T> void sequencestack<T>::Empty()
{
	m_nrear = 0;
	m_front = 0;
	m_nCount = 0;
}

template <typename T> bool sequencestack<T>::IsEmpty()
{
	return m_nCount == 0;
}

template <typename T> bool sequencestack<T>::IsFull()
{
	return m_nCount == m_nMaxSize;
}


template <typename T> bool sequencestack<T>::Append(const T e)
{
	if (IsFull())
	{
		return false;
	}
	m_data[m_nrear] = e;
	m_nrear = (m_nrear+1)%m_nMaxSize;
	m_nCount++;
	return 1;
}

template <typename T> T sequencestack<T>::Delete()
{
	if (IsEmpty())
	{
		cout<<"Delete,Empty stack!"<<endl;
		exit(1);
	}
	T e = m_data[m_front];
	m_front = (m_front+1)%m_nMaxSize;
	m_nCount--;
	return e;
}

template <typename T> T sequencestack<T>::Get()
{
	if (IsEmpty())
	{
		cout<<"Delete,Empty stack!"<<endl;
		exit(1);
	}
	return m_data[m_front];
}

template <typename T> void sequencestack<T>::Print()
{
	for (int i=0;i<m_nCount;i++)
	{
		cout<<m_data[(m_front+i+m_nMaxSize)%m_nMaxSize]<<"  ";
	}

	cout<<endl;
}