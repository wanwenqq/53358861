/*****============================================
		*	Á´Ê½Õ»
		*
============================================******/

#include <iostream>
using namespace std;

template <typename T> class LinkStack;
template <typename T> class StackNode
{
public:
	friend class LinkStack<T>;
	StackNode(T e,StackNode<T> *next = NULL):m_data(e),m_pnext(next){}
	~StackNode(){}

private:
	T		m_data;
	StackNode<T>*	m_pnext;
};

template <typename T> class LinkStack
{
public:
	LinkStack():m_pTop(NULL){}
	~LinkStack()
	{
		Empty();
	}

public:
	bool IsEmpty(){return m_pTop == NULL;}


public:
	void Empty();
	void Push(const T e);
	T		Pop();
	T		GetTop() ;
	void	Print();


private:
	StackNode<T> *	m_pTop;
};

template <typename T> void LinkStack<T>::Empty()
{
	StackNode<T> *p;
	while (m_pTop != NULL)
	{
		p = m_pTop;
		m_pTop = m_pTop->m_pnext;
		delete p;
	}
}


template <typename T> void LinkStack<T>::Push(const T e)
{
	m_pTop = new StackNode<T>(e,m_pTop);
}


template <typename T> T LinkStack<T>::Pop()
{
	if (IsEmpty())
	{
		cout<<"empty stack!"<<endl;
		exit(1);
	}

	StackNode<T> *pDel = m_pTop;
	m_pTop = m_pTop->m_pnext;
	T e = pDel->m_data;
	delete pDel;
	return e;
}

template <typename T> T LinkStack<T>::GetTop() 
{
	if ( IsEmpty() )
	{
		cout<<"GetPop,empty stack!"<<endl;
		exit(1);
	}
	return m_pTop->m_data;
}

template <typename T> void LinkStack<T>::Print()
{
	StackNode<T>*	p = m_pTop;
	while (p != NULL)
	{
		cout<<p->m_data<<" ";
		p = p->m_pnext;
	}
	cout<<endl;
}