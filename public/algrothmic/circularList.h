/*****============================================
		*	Ñ­»·Á´±í
		*
============================================******/

#include <iostream>
using namespace std;

//=======================ListNode start==============================
template <typename T> class CircularList;
template <typename T> class ListNode
{
private:
	friend class CircularList<T>;
	ListNode():m_pnext(NULL){}
	ListNode(const T item,ListNode<T> *next=NULL):m_data(item),m_pnext(next){}

	~ListNode(){
		m_pnext = NULL;
	}

public:
	T Get();

private:
	T		m_data;
	ListNode	* m_pnext;
};

template <typename T> T ListNode<T>::Get()
{
	return m_data;
}
//=======================ListNode end==============================

template <typename T> class CircularList
{
public:
	CircularList():head(new ListNode<T>()){
		head->m_pnext=head;
	}

	~CircularList(){
		Empty();
		delete head;
	}

public:
	void Empty();
	int Length();

	ListNode<T> * Find(int n);
	ListNode<T> * Find(T e,int n);

	bool Insert(T e,int n);

	bool RemoveAll( T e);
	T Remove(int n);

	T Get(int n);


public:
	void Print();

private:
	ListNode<T>	* head;
};


template <typename T> void CircularList<T>::Empty()
{
	ListNode<T> *p = head;
	ListNode<T> *pDel;
	while(p->m_pnext !=head){
		pDel = p->m_pnext;
		p->m_pnext = pDel->m_pnext;
		delete pDel;
	}
}

template<typename T> int CircularList<T>::Length()
{
	ListNode<T> *p = head;
	int nCount = 0;
	while (p->m_pnext != head)
	{
		p = p->m_pnext;
		nCount++;
	}
	return nCount;
}

template <typename T> ListNode<T>* CircularList<T>::Find(int n)
{
	if (n<0)
	{
		return NULL;
	}
	ListNode<T> *p = head->m_pnext;
	for (int i=0;i<n&&p != head;i++)
	{
		p = p->m_pnext;
	}
	if (p == head)
	{
		return NULL;
	}
	return p;
}

template<typename T> ListNode<T> * CircularList<T>::Find(T e,int n)
{
	if (n<1)
	{
		return NULL;
	}
	ListNode<T> *p = head;
	int nCount = 0;
	while (nCount != n)
	{
		p = p->m_pnext;
		if (p->m_data == e)
		{
			nCount++;
		}
		if (p == head)
		{
			return NULL;
		}
	}
	return p;
}


template <typename T> bool CircularList<T>::Insert(T e,int n)
{
	if (n<0)
	{
		return false;
	}
	ListNode<T> *p = head	;
	ListNode<T> *pNode = new ListNode<T>(e);
	if( pNode == NULL){
		return false;
	}
	for (int i=0;i<n;i++)
	{
		p = p->m_pnext;
		if (p == head)
		{
			return false;
		}
	}
	pNode->m_pnext = p->m_pnext;
	p->m_pnext = pNode;

	return true	;
}


template <typename T> bool CircularList<T>::RemoveAll(T e)
{
	ListNode<T> *p = head	;
	ListNode<T> *pDel = head->m_pnext;
	while (pDel != head)
	{
		if (pDel->m_data == e)
		{
			p->m_pnext = pDel->m_pnext;
			delete pDel;
			pDel = p->m_pnext;
			continue;
		}
		p = p->m_pnext;
		pDel = pDel->m_pnext;
	}
	return true;
}

template <typename T> T CircularList<T>::Remove(int n)
{
	if (n<0)
	{
		exit(1);
	}
	ListNode<T> *p = head;
	ListNode<T> *pDel;
	for (int i=0;i<n&&p->m_pnext != head;i++)
	{
		p = p->m_pnext;
	}
	if (p->m_pnext  == head)
	{
		exit(2);
	}
	pDel = p->m_pnext;
	p->m_pnext = pDel->m_pnext;
	T e = pDel->m_data;
	delete pDel;
	return e;
}


template <typename T> T CircularList<T>::Get(int n)
{
	if (n<0)
	{
		exit(1);
	}
	ListNode<T> *p = head->m_pnext;
	for (int i=0;i<n;i++)
	{
		p = p->m_pnext;
	}
	if (p == head)
	{
		exit(2);
	}
	return p->m_data;
}

template<typename T> void CircularList<T>::Print()
{
	ListNode<T>* p = head->m_pnext;
	while (p != head)
	{
		cout<<p->m_data<<" ";
		p = p->m_pnext;
	}
	cout<<endl;
}