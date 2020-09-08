#include<iostream>

#include"Graph.h"

using namespace std;

void CGraph::Init()
{
	//��ʼ��ͼ�Ķ������
	m_nVexNum=0;
	//��ʼ���ڽӾ���
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<20;j++)
		{
			m_aAdjMatrix[i][j]=0;
		}
	}
}

bool CGraph::InsertVex(Vex sVex)
{
	if(m_nVexNum==MAX_VERTEX_NUM)
	{
		//��������
		return false;
	}

	m_aVexs[m_nVexNum++]=sVex;
	return true;
}

bool CGraph::InsertEdge(Edge sEdge)
{
	if(sEdge.vex1<0||sEdge.vex1>=m_nVexNum||sEdge.vex2<0||sEdge.vex2>=m_nVexNum)
	{
		//�±�Խ��
		return false;
	}

	//����ߵ���Ϣ
	m_aAdjMatrix[sEdge.vex1][sEdge.vex2]=sEdge.weight;
	m_aAdjMatrix[sEdge.vex2][sEdge.vex1]=sEdge.weight;
}

int CGraph::GetVexNum()
{
	return m_nVexNum;
}

Vex CGraph::GetVex(int nVex)
{
	return m_aVexs[nVex];
}

int CGraph::FindEdge(int nVex,Edge aEdge[])
{
	int k=0;
	for(int i=0;i<m_nVexNum;i++)
	{
		//�õ��ߵ���Ϣ
		if(m_aAdjMatrix[nVex][i]<100000&&m_aAdjMatrix[nVex][i]>0)
		{
			aEdge[k].vex1=nVex;
			aEdge[k].vex2=i;
			aEdge[k].weight=m_aAdjMatrix[nVex][i];
			k++;
		}
	}
	return k;
}

void CGraph::DFS(int nVex,bool bVisited[],int &nIndex,PathList &pList)
{
	bVisited[nVex] = true;//��Ϊ�ѷ���
	pList->vexs[nIndex++] = nVex;//���ʶ���nVex

	int nVexNum = 0;
	for(int i=0;i<m_nVexNum;i++)
	{
		if(bVisited[i]) 
			nVexNum++;
	}
	if(nVexNum==m_nVexNum)//���ж��㶼�����ʹ�
	{
		//����һ��·��
		pList->next=(PathList)malloc(sizeof(Path));
		for(int i=0;i<m_nVexNum;i++)
		{
			pList->next->vexs[i]=pList->vexs[i];
		}
		pList=pList->next;
		pList->next=NULL;
	}
	else
	{
		for(int i=0;i<m_nVexNum;i++)
		{
			if(m_aAdjMatrix[nVex][i]>0&&m_aAdjMatrix[nVex][i]<10000&&!bVisited[i])
			{
				DFS(i,bVisited,nIndex,pList);
				bVisited[i]=false;
				nIndex--;
			}
		}
	}
}

void CGraph::DFSTraverse(int nVex,PathList &pList)
{
	int nIndex=0;
	bool bVisited[20]={false};
	DFS(nVex,bVisited,nIndex,pList);
}
int CGraph::FindShortPath(int nVexStart,int nVexEnd,Edge aPath[])
{
	int nShortPath[MAX_VERTEX_NUM][MAX_VERTEX_NUM];  //�������·��
	int nShortDistance[MAX_VERTEX_NUM];  //������̾���
	bool aVistited[MAX_VERTEX_NUM];  //�ж�ĳ�����Ƿ��Ѽ������·��
	int v;

	//��ʼ��
	for (v = 0; v < m_nVexNum; v++)
	{
		aVistited[v] = false;
		if (m_aAdjMatrix[nVexStart][v])
		{
			//��ʼ���ö��㵽�����������̾��룬Ĭ��Ϊ�������ľ���
			nShortDistance[v] = m_aAdjMatrix[nVexStart][v];
		}
		else
		{
			//�������v��nVexStart������������̾�����Ϊ���ֵ
			nShortDistance[v] = 0x7FFFFFFF;
		}
		nShortPath[v][0] = nVexStart;  //��ʼ��ΪnVexStart
		for (int w = 1; w < m_nVexNum; w++)
		{
			nShortPath[v][w] = -1;  //��ʼ�����·��
		}
	}

	//��ʼ����nVexStart������뵽������
	aVistited[nVexStart] = true;
	int min;
	for (int i = 1; i < m_nVexNum; i++)
	{
		min = 0x7FFFFFFF;
		bool bAdd = false;  //�ж��Ƿ��ж�����Լ��뵽����
		for (int w = 0; w < m_nVexNum; w++)
		{
			if (!aVistited[w])
			{
				if (nShortDistance[w] < min)
				{
					v = w;  //w������nVexStart�������
					min = nShortDistance[w];  //w��nVexStart����̾���Ϊmin
					bAdd = true;
				}
			}
		}

		//���û�ж�����Լ��뵽���ϣ�������ѭ��
		if (!bAdd)
		{
			break;
		}

		aVistited[v] = true;  //��w������뵽����
		nShortPath[v][i] = v;  //������w���浽nVexStart��w�����·����
		for (int w = 0; w < m_nVexNum; w++)
		{
			//��w��Ϊ���ɶ������nVexStartͨ��w��ÿ������ľ���
			if (!aVistited[w] && (min + m_aAdjMatrix[v][w] < nShortDistance[w]) && (m_aAdjMatrix[v][w] >0))
			{
				//���µ�ǰ���·��������
				nShortDistance[w] = min + m_aAdjMatrix[v][w];
				for (int i = 0; i < m_nVexNum; i++)
				{
					//���ͨ��w���ﶥ��i�ľ���Ƚ϶̣���w�����·�����Ƹ�i
					nShortPath[w][i] = nShortPath[v][i];
				}
			}
		}
	}

	int nIndex = 0;
	int nVex1 = nVexStart;
	//�����·������Ϊ�ߵĽṹ������
	for (int i = 1; i < m_nVexNum; i++)
	{
		if (nShortPath[nVexEnd][i] != -1)
		{
			aPath[nIndex].vex1 = nVex1;
			aPath[nIndex].vex2 = nShortPath[nVexEnd][i];
			aPath[nIndex].weight = m_aAdjMatrix[nVex1][aPath[nIndex].vex2];
			nVex1 = nShortPath[nVexEnd][i];
			nIndex++;
		}
	}
	return nIndex;
}

void CGraph::FindMinTree(Edge aPath[])
{
	bool aVisited[MAX_VERTEX_NUM];//�ж�ĳ�����Ƿ�����С���������㼯����
	for(int i=0;i<MAX_VERTEX_NUM;i++)
	{
		aVisited[i]=false;//��ʼ������
	}
	aVisited[0]=true;//0������뵽������
	int min,k=0;
	int nVex1,nVex2;
	for(int k=0;k<m_nVexNum-1;k++)
	{
		min=0x7FFFFFFF;
		for(int i=0;i<m_nVexNum;i++)
		{
			if(aVisited[i])//�Ӽ�����ȡ��һ������
			{
				for(int j=0;j<m_nVexNum;j++)
				{
					if(!aVisited[j])
					{

					    if((m_aAdjMatrix[i][j]<min)&&(m_aAdjMatrix[i][j]!=0))
					       {
						       nVex1=i;
						       nVex2=j;
						       min=m_aAdjMatrix[i][j];
					       }
					}
				}
			}
		}
	//������̱ߵ���������
	aPath[k].vex1=nVex1;
	aPath[k].vex2=nVex2;
	aPath[k].weight=m_aAdjMatrix[nVex1][nVex2];
	//������������뵽����
	aVisited[nVex1]=true;
	aVisited[nVex2]=true;
	}
}