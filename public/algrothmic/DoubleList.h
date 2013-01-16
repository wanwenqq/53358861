/*****============================================
		*	Ë«ÏòÁ´±í
		*
============================================******/

#include <iostream>
using namespace std;


//=======================ListNode start==============================
template <typename T> class DoubleList;
template <typename T> class ListNode
{
public:
	ListNode():m_prior(NULL),m_pnext(NULL){}
	ListNode(const T e,ListNode<T> *prior=NULL,ListNode<T> *next=NULL):m_data(e),m_pnext(next),m_prior(prior){}
	~ListNode()
	{
		m_pnext = NULL;
		m_prior = NULL;
	}

	friend class DoubleList<T>;

public:
	T Get();


private:
	T		m_data;
	ListNode	*m_prior;
	ListNode	*m_pnext;
};


template <typename T> T ListNode<T>::Get()
{
	return this->m_data;
}

//=======================ListNode end==============================

template <typename T> class DoubleList
{
public:
	DoubleList():head(new ListNode<T>())
		{
			head->m_prior = head;
			head->m_pnext = head;
	}
	~DoubleList(){
		Empty();
		delete head;
	}

public:
	void Empty();

	int Length();

	int Put(T e,int i);

	ListNode<T> * Get(int n);

	T Remove( int n);

	ListNode<T>  * Find(T e);
	

	void print();

private:
	ListNode<T> *head;
};


template <typename T> void DoubleList<T>::Empty()
{
	ListNode<T> *p = head->m_pnext;
	ListNode<T> *pDel;
	while (p != head)
	{
		pDel = p	;
		p = pDel->m_pnext;
		delete	pDel;
	}
	p->m_pnext = head;
	p->m_prior = head;

}


template <typename T> int DoubleList<T>::Length()
{
	ListNode<T>	*pproir = head->m_prior;
	ListNode<T>	*pnext = head->m_pnext;
	int nCount = 0;

	while (1)
	{
		if(pproir->m_pnext == pnext)
		{
			break;
		}
		if (pproir == pnext && pproir != head)
		{
			nCount++;
			break;
		}
		nCount += 2;
		pproir = pproir->m_prior;
		pnext = pnext->m_pnext;
	}
	return nCount;
}



template <typename T> int DoubleList<T>::Put(T e,int n)
{
	if (n<0 || n>Length())
	{
		return -1;
	}
	ListNode<T> *p = head;
	ListNode<T> *pNew = new ListNode<T>(e);
	if(pNew == NULL){
		return -2;
	}
	for (int i=0;i<n;i++)
	{
		p = p->m_pnext;
		if (p == head)
		{
			return -3;
		}
	}
	pNew->m_pnext = p->m_pnext;
	pNew->m_prior = p;
	p->m_pnext = pNew;
	pNew->m_pnext->m_prior = pNew;

	return 1;

}


template <typename T> ListNode<T>* DoubleList<T>::Get(int n)
{
	if( n<0 || n> Length()){
		return NULL;
	}
	ListNode<T> *p = head->m_pnext;
	for (int i=0;i<n;i++)
	{
		p = p->m_pnext;
		if( p == head){
			return NULL;
		}
	}
	return p;
}


template <typename T> T DoubleList<T>::Remove(int n)
{
	if( n<0 || n>Length()){
		exit(0);
	}
	ListNode<T> *p = head	;
	ListNode<T> *pDel;
	for ( int i=0;i<n;i++)
	{
		p = p->m_pnext;
		if( p == head){
			exit(0);
		}
	}
	pDel = p;
	p->m_prior->m_pnext = pDel->m_pnext;
	p->m_pnext->m_prior = pDel->m_prior;
	T e = pDel->m_data;
	delete pDel;

	return e;
}


template <typename T> ListNode<T>* DoubleList<T>::Find(T e)
{
	ListNode<T> *pproir = head->m_prior;
	ListNode<T> *pnext = head	->m_pnext;

	while ( pproir->m_pnext != pnext && pproir != pnext)
	{
		if ( pproir->m_data == e)
		{
			return pproir;
		}
		if (pnext->m_data == e)
		{
			return pnext;
		}
		pproir = pproir->m_prior;
		pnext = pnext->m_pnext;
	}
	return NULL;
}


template <typename T> void DoubleList<T>::print()
{
	ListNode<T>	*p = head->m_pnext;
	while (p != head)
	{
		cout<<p->m_data<<endl;
		p = p->m_pnext;
	}
}