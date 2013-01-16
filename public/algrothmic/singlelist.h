/*****============================================
		*	单链表
		*
============================================******/

#include <iostream>
using namespace std;
//=======================ListNode start==============================
template<typename Type> class SingleList;
template <typename T> class ListNode
{
public:
	ListNode():mp_next(NULL){}
	ListNode(const T e,ListNode<T> *next=NULL):m_data(e),mp_next(next){}
	~ListNode()
	{
		mp_next = NULL; 
	}


public:
	//获取当前节点数值 
	T GetNode();

	//操作符<<重载
	friend ostream & operator << <T>(ostream&,ListNode<T>&);

private:
	T		m_data;
	ListNode	*mp_next;

private:
	friend typename SingleList<T>;
};

template <typename T> T ListNode<T>::GetNode()
{
	return this->m_data;
}

template <typename T> ostream& operator<<(ostream& os,ListNode<T>& out)
{
	os<<out.m_data;
	return os;
}
//=======================ListNode end==============================

//=======================SingleList start==============================

template <typename T> class SingleList
{
public:
	SingleList():head(new ListNode<T>()){}
	~SingleList()
	{
		delete head;
	}


public:
	int Length();

	bool IsEmpty();

	void Empty();

	ListNode <T> *Get( int n);


	int Put(T e,int n);

	int RemoveElement( T e);

	T Remove( int n);



	void print();

private:
	ListNode<T>	*head;
};

template <typename T> int SingleList<T>::Length()
{
	ListNode<T>	*pMove = head->mp_next;
	int nCount = 0;
	while (pMove != NULL )
	{
		pMove = pMove->mp_next;
		nCount++;
	}
	return nCount;
}


template <typename T> bool SingleList<T>::IsEmpty()
{
	return this->head->mp_next == NULL;

}

template <typename T> void SingleList<T>::Empty()
{
	ListNode<T>	*p;
	while (head->mp_next != NULL)
	{
		p = head->mp_next;
		head->mp_next = head->mp_next->mp_next;
		delete p;
	}
}



template <typename T> ListNode<T> *SingleList<T>::Get(int n)
{
	if ( n<0 )
	{
		cout<<" n<0"<<endl;
		return NULL;
	}
	ListNode<T> *p = head->mp_next;
	for ( int i=0;i<n&&p;i++)
	{
		p= p->mp_next;
	}
	if(p == NULL)
	{
		cout<<"find nothing end"<<endl;
		return NULL;
	}
	return p;
}



template <typename T> int SingleList<T>::Put(T e,int n)
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
	for (int i=0;i<n&&p;i++)
	{
		p = p->mp_next;
	}
	//顺序不能反??
	pNew->mp_next = p->mp_next;
	p->mp_next = pNew;
	return 1;
}


template <typename T> int SingleList<T>::RemoveElement(T e)
{
	ListNode<T> *p = head;
	ListNode<T> *pDel = p->mp_next;
	while (pDel != NULL)
	{
		if(pDel->m_data == e )
		{
			p->mp_next = pDel->mp_next;
			delete pDel;
			pDel = p->mp_next;
			continue;
		}
		p = p->mp_next;
		pDel = pDel->mp_next;
	}
	return 1;
}


template <typename T> T SingleList<T>::Remove(int n)
{
	if (n<0 || n>Length())
	{
		exit(1);
	}
	ListNode <T> *p = head;
	ListNode <T> *pDel;
	for (int i=0;i<n&&p->mp_next;i++)
	{
		p = p->mp_next;
	}
	pDel = p->mp_next;
	p->mp_next = pDel->mp_next;
	T e = pDel->m_data;
	delete pDel;
	return e;
}




template <typename T> void SingleList<T>::print()
{
	ListNode<T> *p = head->mp_next;
	while (p)
	{
		cout<<p->m_data<<endl;
		p = p->mp_next;
	}

}