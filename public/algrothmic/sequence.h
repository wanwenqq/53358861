/*****============================================
		*	˳���
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
	//��ȡ˳���ǰ����
	int Length() const
	{
		return m_CurrentSize+1;
	}

	//��ȡ˳���ʵ�ʳ���
	int Size() const
	{
		return m_nMaxSize+1;
	}

	//�жϵ�ǰ���Ƿ�����
	bool IsFull(){
		return m_nMaxSize == m_CurrentSize+1;
	}

	//�ж��Ƿ��ǿձ�
	bool IsEmpty(){
		return m_CurrentSize  == -1;
	}


public:
	//������ֵ
	int Put(T  e,int i);

	//��ȡ��ֵ
	T Get( int i);

	//ɾ��Ԫ��
	int Remove(T e);

	//����Ԫ��
	int Find( T e);

	//�������
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


