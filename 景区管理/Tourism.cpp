#include<iostream>

#include"Tourism.h"

using namespace std;

#define VEX_FILE_NAME "Vex.txt"  //记录顶点信息的文件
#define EDGE_FILE_NAME "Edge.txt"  //记录边信息的文件


void CTourism::CreateGraph()
{
	cout<<"=======创建景区景点图======="<<endl;
	//初始化图
	m_Graph.Init();

	//打开文件
	FILE *pVex = fopen(VEX_FILE_NAME, "r");
	if(!pVex)
	{
		cout<<"打开文件失败！"<<endl;
		return;
	}

	//读取景点数目
	int nSpotCount = 0;
	fscanf(pVex, "%d\n", &nSpotCount);
	cout<<"顶点数目："<<nSpotCount<<endl;

	//读取顶点信息
	cout<<"------顶点------"<<endl;
	Vex sVex;
	while(fscanf(pVex, "%d\n%s\n%s\n", &sVex.num, sVex.name, sVex.desc) != -1)
	{
		//显示顶点信息
		cout<<sVex.num<<"-"<<sVex.name<<endl;

		//新增顶点
		if(!m_Graph.InsertVex(sVex))
		{
			cout<<"新增顶点失败！"<<endl;
			continue;
		}
	}

	//关闭文件
	fclose(pVex);
	pVex = NULL;

	//打开文件
	FILE *pEdge = fopen(EDGE_FILE_NAME, "r");
	if(!pEdge)
	{
		cout<<"打开文件失败！"<<endl;
		return;
	}

	//读取边信息
	cout<<"------边------"<<endl;
	Edge sEdge;
	while(fscanf(pEdge, "%d\t%d\t%d\n", &sEdge.vex1, &sEdge.vex2, &sEdge.weight) != -1)
	{
		//显示道路信息
		cout<<"(v"<<sEdge.vex1<<",v"<<sEdge.vex2<<")"<<sEdge.weight<<endl;

		//新增边
		if(!m_Graph.InsertEdge(sEdge))
		{
			cout<<"新增边失败！"<<endl;
			continue;
		}
	}

	//关闭文件
	fclose(pEdge);
	pEdge = NULL;
}

void CTourism::GetSpotInfo()
{
	cout<<"======查询景点信息======"<<endl;

	//获得景点数
	int nVexNum = m_Graph.GetVexNum();

	//列出所有景点的编号和名称
	for(int i=0;i<nVexNum;i++)
	{
		Vex sVex = m_Graph.GetVex(i);
		cout<<sVex.num<<"-"<<sVex.name<<endl;
	}

	//输入要查询的编号
	int nVex;
	cout<<"请输入要查询的景点编号:";
	cin>>nVex;
	if(nVex<0||nVex>=nVexNum)
	{
		cout<<"请输入正确的数字!\n";
		return;
	}

	Vex sVex = m_Graph.GetVex(nVex);
	cout<<sVex.name<<endl;//输出景点名字
	cout<<sVex.desc<<endl;//输出景点介绍信息

	//查询周边景点信息
	Edge aEdge[MAX_VERTEX_NUM];
	int nEdgeNum = m_Graph.FindEdge(nVex,aEdge);
	cout<<"====周边景点===="<<endl;
	for(int i=0;i<nEdgeNum;i++)
	{
		Vex v1 = m_Graph.GetVex(aEdge[i].vex1);
		Vex v2 = m_Graph.GetVex(aEdge[i].vex2);
		//输出周边景点及距离
		cout<<v1.name<<"-"<<v2.name<<aEdge[i].weight<<"m"<<endl;
	}
}

void CTourism::TravelPath()
{
	int choice;
	int nVexNum = m_Graph.GetVexNum();
	cout<<"请输入起始点编号："<<endl;
	cin>>choice;
	if(choice<0||choice>=m_Graph.GetVexNum())
	{
		cout<<"请输入正确数字！"<<endl;
		return;
	}

	PathList pList = (PathList)malloc(sizeof(Path));
	PathList phead = pList;

	//遍历景区景点图
	m_Graph.DFSTraverse(choice,pList);
	//输出结果
	cout<<"导游路线为："<<endl;
	int i = 1;

	pList = phead;
	while(pList->next)
	{
		//输出一条路线
		Vex sVex = m_Graph.GetVex(pList->vexs[0]);
		cout<<"路线"<<i++<<":"<<sVex.name;
		for(int j=1;j<nVexNum;j++)
		{
			sVex = m_Graph.GetVex(pList->vexs[j]);
			cout<<"->"<<sVex.name;
		}
		cout<<endl;

		//释放空间
		Path *temp=pList;
		pList=pList->next;
		free(temp);
	}

	free(pList);
	pList=NULL;
	phead=NULL;
}

void CTourism::FindShortPath()
{
	cout<<"======搜索最短路径======"<<endl;
	//获得景点数
	int nVexNum=m_Graph.GetVexNum();

	//列出所有景点编号和名称
	for(int i=0;i<nVexNum;i++)
	{
		Vex sVex=m_Graph.GetVex(i);//查询顶点信息
		cout<<sVex.num<<"-"<<sVex.name<<endl;
	}

	int nVexStart,nVexEnd;//定义起始点和终点
	cout<<"请输入起点的编号：";
	cin>>nVexStart;//输入起点编号
	cout<<"请输入终点的编号：";
	cin>>nVexEnd;//输入终点编号
	//判断输入是否正确
	if(nVexStart<0||nVexStart>=nVexNum||nVexEnd<0||nVexEnd>=nVexNum)
	{
		cout<<"输入错误！"<<endl;
		return;
	}
	Edge aPath[MAX_VERTEX_NUM];
	int nNum=m_Graph.FindShortPath(nVexStart,nVexEnd,aPath);
	Vex sVex=m_Graph.GetVex(aPath[0].vex1);
	int nLength=0;
	cout<<"最短路径为："<<sVex.name;
	for(int i=0;i<nNum;i++)
	{
		sVex=m_Graph.GetVex(aPath[i].vex2);
		cout<<"->"<<sVex.name;
		nLength+=aPath[i].weight;
	}
	cout<<endl;
	cout<<"最短距离为："<<nLength<<endl;
}

void CTourism::DesignPath()
{
	cout << "======铺设电路规划======" << endl;
	Edge aPath[MAX_VERTEX_NUM];  //定义边结构体数组用来保存铺设的线路
	m_Graph.FindMinTree(aPath);  //得到规划的线路
	int nVexNum = m_Graph.GetVexNum();
	if (nVexNum == 0)
	{
		cout << "请先创建图！" << endl;
		return;
	}
	int nAllLength = 0;
	cout << "在以下两个景点之间铺设电路：" << endl;
	for (int i = 0; i < nVexNum - 1; i++)
	{
		Vex sVex1 = m_Graph.GetVex(aPath[i].vex1);
		Vex sVex2 = m_Graph.GetVex(aPath[i].vex2);
		//输出铺设的线路
		cout << sVex1.name << "-" << sVex2.name << " " << aPath[i].weight << "m" << endl;
		nAllLength += aPath[i].weight;
	}
	cout << "铺设电路的总长度为：" << nAllLength <<"m"<< endl;
}