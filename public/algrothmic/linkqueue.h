/*****============================================
		*	а╢й╫╤сап
		*
============================================******/

#include <iostream>
using namespace std;

template <typename T> class LinkQueue;

template <typename T> class QueueNode
{
public:
	friend class LinkQueue<T>;
	QueueNode(const T e,QueueNode<T>* next = NULL):m_data(e),m_pnext(next){}
	~QueueNode(){}
private:
	T		m_data;
	QueueNode<T>	*m_pnext;
};


template <typename T> class LinkQueue
{
public:
	LinkQueue():m_prear(NULL),m_pfront(NULL){}
	~LinkQueue(){
		Empty();
	}

public:
	void Empty();
	void Append(const T e);
	T		Delete();
	T		GetFront();

	void Print();

public:
	bool IsEmpty(){
		return m_pfront == NULL;
	}

private:
	QueueNode<T> *m_prear;
	QueueNode<T> *m_pfront;

};

template <typename T> void LinkQueue<T>::Empty()
{
	QueueNode<T>	*pDel;
	while (m_pfront)
	{
		pDel = m_pfront;
		m_pfront = m_pfront->m_pnext;
		delete pDel;
	}

}


template <typename T> void LinkQueue<T>::Append(const T e)
{
	if (m_pfront == NULL)
	{
		m_pfront = m_prear = new QueueNode<T>(e);
	}
	else{
		m_prear = m_prear->m_pnext=new QueueNode<T>(e);
	}
}


template <typename T> T LinkQueue<T>::Delete()
{
	if (IsEmpty())
	{
		cout<<" Delete,Queue Empty!"<<endl;
		exit(1);
	}
	QueueNode<T> *pDel = m_pfront;
	T	e = m_pfront->m_data;
	m_pfront = m_pfront->m_pnext;
	delete pDel;
	return e;
}


template <typename T> T LinkQueue<T>::GetFront()
{
	if (IsEmpty())
	{
		cout<<" GetFront,Queue Empty!"<<endl;
		exit(1);
	}
	return m_pfront->m_data;
}


template <typename T> void LinkQueue<T>::Print()
{
	QueueNode<T>	*p = m_pfront;
	while (p)
	{
		cout<<p->m_data<<" ";
		p = p->m_pnext;
	}
	cout<<endl;
}