/*****============================================
		*	顺序表
		*
============================================******/

const int DefaultSize=100;

template <typename T>  class SeqList
{

public:
	SeqList( int sz =DefaultSize ):m_nMaxSize(sz),m_CurrentSize(-1)
	{
		if( sz>0 )
		{
			pm_element = new T[m_nMaxSize];
		}
	}

	~SeqList()
	{
		delete [] pm_element;
		pm_element = 0;
	}



public:
	//获取顺序表当前长度
	int Length() const
	{
		return m_CurrentSize+1;
	}

	//获取顺序表实际长度
	int Size() const
	{
		return m_nMaxSize+1;
	}

	//判断当前表是否已满
	bool IsFull(){
		return m_nMaxSize == m_CurrentSize+1;
	}

	//判断是否是空表
	bool IsEmpty(){
		return m_CurrentSize  == -1;
	}


public:
	//插入数值
	int Put(T  e,int i);

	//获取数值
	T Get( int i);

	//删除元素
	int Remove(T e);

	//查找元素
	int Find( T e);

	//清空数据
	void Clear();

	void print();


private:
	T					*pm_element;
	int		m_nMaxSize;
	int				m_CurrentSize;
};


template <typename T>  int SeqList<T>::Put(T  e,int i)
{
	if( IsFull() ){
		return -2;
	}
	if( i<0 || i>m_CurrentSize+1){
		return -1;
	}
	m_CurrentSize++;
	for ( int j=m_CurrentSize;j>i;j--)
	{
		pm_element[j] = pm_element[j-1];
	}
	pm_element[i] = e;

	cout<<"Put element"<<endl;
	return 1;
}


template <typename T> T SeqList<T>::Get(int i)
{
	if( i<0 || i>m_CurrentSize)
	{
		return -1;
	}
	return pm_element[i];
}



template <typename T> int SeqList<T>::Remove(T e)
{

	if( IsEmpty()){
		return -1;
	}

	int nSize = m_CurrentSize;
	for ( int i=0;i<m_CurrentSize;)
	{
		if( pm_element[i] == e )
		{
			for ( int j=i;j<m_CurrentSize;j++)
			{
				pm_element[j] = pm_element[j+1];
			}
			m_CurrentSize--;
			continue;
		}
		i++;
	}
	if(nSize == m_CurrentSize){
		return -2;
	}
	return 1;
}


template <typename T> int SeqList<T>::Find(T e)
{
	for ( int i=0;i<m_CurrentSize;i++)
	{
		if( pm_element[i] == e){
			return i;
		}
	}
	return -1;
		
}


template <typename T> void SeqList<T>::Clear()
{
	m_CurrentSize = -1;
}

template <typename T> void SeqList<T>::print()
{
	for ( int i=0;i<=m_CurrentSize;i++)
	{
		cout<<"i="<<i<<",element="<<pm_element[i]<<endl;
	}
}


