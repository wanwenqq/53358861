/*****============================================
		*	À≥–Ú’ª
		*
============================================******/

#include <iostream>
using namespace std;


template <typename T> class sequencestack
{
public:
	sequencestack(int sz):m_nTop(-1),m_nMaxSize(sz){
		m_data = new T[sz];
		if (m_data == NULL)
		{
			exit(1);
		}
	}
	~sequencestack(){
		delete [] m_data;
	}


public:
	bool	IsEmpty(){return m_nTop == -1;}
	bool	IsFull(){return m_nTop==m_nMaxSize-1;}
	void	Empty(){m_nTop = -1;}

public:
	void Push(const T e);
	T		Pop();
	T		GetTop() const;
	void Print();


public:
	int		m_nTop;
	int		m_nMaxSize;
	T			*m_data;
};


template <typename T> void sequencestack<T>::Push(const T e)
{
	if (IsFull())
	{
		return ;
	}
	m_data[++m_nTop] = e;
}


template <typename T> T sequencestack<T>::Pop()
{
	if (IsEmpty())
	{
		cout<<"empty stack!"<<endl;
		exit(1);
	}
	return m_data[m_nTop--];
}


template <typename T> T sequencestack<T>::GetTop() const
{
	if (IsEmpty())
	{
		exit(1);
	}
	return m_data[m_nTop];
}


template <typename T> void sequencestack<T>::Print()
{
	for (int  i=0;i<m_nTop;i++)
	{
		cout<<m_data[i]<<"  ";
	}
	cout<<endl;
}