#include<iostream>

#include"Graph.h"

using namespace std;

void CGraph::Init()
{
	//初始化图的顶点个数
	m_nVexNum=0;
	//初始化邻接矩阵
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
		//顶点已满
		return false;
	}

	m_aVexs[m_nVexNum++]=sVex;
	return true;
}

bool CGraph::InsertEdge(Edge sEdge)
{
	if(sEdge.vex1<0||sEdge.vex1>=m_nVexNum||sEdge.vex2<0||sEdge.vex2>=m_nVexNum)
	{
		//下标越界
		return false;
	}

	//输入边的信息
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
		//得到边的信息
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
	bVisited[nVex] = true;//改为已访问
	pList->vexs[nIndex++] = nVex;//访问顶点nVex

	int nVexNum = 0;
	for(int i=0;i<m_nVexNum;i++)
	{
		if(bVisited[i]) 
			nVexNum++;
	}
	if(nVexNum==m_nVexNum)//所有顶点都被访问过
	{
		//保存一条路径
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
	int nShortPath[MAX_VERTEX_NUM][MAX_VERTEX_NUM];  //保存最短路径
	int nShortDistance[MAX_VERTEX_NUM];  //保存最短距离
	bool aVistited[MAX_VERTEX_NUM];  //判断某顶点是否已加入最短路径
	int v;

	//初始化
	for (v = 0; v < m_nVexNum; v++)
	{
		aVistited[v] = false;
		if (m_aAdjMatrix[nVexStart][v])
		{
			//初始化该顶点到其他顶点的最短距离，默认为两顶点间的距离
			nShortDistance[v] = m_aAdjMatrix[nVexStart][v];
		}
		else
		{
			//如果顶点v和nVexStart不想连，则最短距离设为最大值
			nShortDistance[v] = 0x7FFFFFFF;
		}
		nShortPath[v][0] = nVexStart;  //起始点为nVexStart
		for (int w = 1; w < m_nVexNum; w++)
		{
			nShortPath[v][w] = -1;  //初始化最短路径
		}
	}

	//初始化，nVexStart顶点加入到集合中
	aVistited[nVexStart] = true;
	int min;
	for (int i = 1; i < m_nVexNum; i++)
	{
		min = 0x7FFFFFFF;
		bool bAdd = false;  //判断是否还有顶点可以加入到集合
		for (int w = 0; w < m_nVexNum; w++)
		{
			if (!aVistited[w])
			{
				if (nShortDistance[w] < min)
				{
					v = w;  //w顶点离nVexStart顶点最近
					min = nShortDistance[w];  //w到nVexStart的最短距离为min
					bAdd = true;
				}
			}
		}

		//如果没有顶点可以加入到集合，则跳出循环
		if (!bAdd)
		{
			break;
		}

		aVistited[v] = true;  //将w顶点加入到集合
		nShortPath[v][i] = v;  //将顶点w保存到nVexStart到w的最短路径里
		for (int w = 0; w < m_nVexNum; w++)
		{
			//将w作为过渡顶点计算nVexStart通过w到每个顶点的距离
			if (!aVistited[w] && (min + m_aAdjMatrix[v][w] < nShortDistance[w]) && (m_aAdjMatrix[v][w] >0))
			{
				//更新当前最短路径及距离
				nShortDistance[w] = min + m_aAdjMatrix[v][w];
				for (int i = 0; i < m_nVexNum; i++)
				{
					//如果通过w到达顶点i的距离比较短，则将w的最短路径复制给i
					nShortPath[w][i] = nShortPath[v][i];
				}
			}
		}
	}

	int nIndex = 0;
	int nVex1 = nVexStart;
	//将最短路径保存为边的结构体数组
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
	bool aVisited[MAX_VERTEX_NUM];//判断某顶点是否在最小生成树顶点集合里
	for(int i=0;i<MAX_VERTEX_NUM;i++)
	{
		aVisited[i]=false;//初始化集合
	}
	aVisited[0]=true;//0顶点加入到集合中
	int min,k=0;
	int nVex1,nVex2;
	for(int k=0;k<m_nVexNum-1;k++)
	{
		min=0x7FFFFFFF;
		for(int i=0;i<m_nVexNum;i++)
		{
			if(aVisited[i])//从集合中取出一个顶点
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
	//保存最短边的两个顶点
	aPath[k].vex1=nVex1;
	aPath[k].vex2=nVex2;
	aPath[k].weight=m_aAdjMatrix[nVex1][nVex2];
	//将两个顶点加入到集合
	aVisited[nVex1]=true;
	aVisited[nVex2]=true;
	}
}