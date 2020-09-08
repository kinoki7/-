#ifndef GRAPH_H
#define GRAPH_H

#define MAX_VERTEX_NUM 20//最大顶点数
#define MAX_NAME_LEN 20  //景点名称长度
#define MAX_DESC_LEN 1024 //景点描述长度


//顶点信息
struct Vex
{
	int num;//编号
	char name[MAX_NAME_LEN];//景点名字
	char desc[MAX_DESC_LEN];//景点介绍
};

//边的信息
struct Edge
{
	int vex1;//第一个顶点的编号
	int vex2;//第二个顶点的编号
	int weight;//边的权值
};

typedef struct Path
{
	int vexs[20];//保存下一条路径
	Path *next;//下一条路径
}*PathList;

class CGraph
{
private:
	int m_aAdjMatrix[20][20];//邻接矩阵
	Vex m_aVexs[20];//顶点信息数组
	int m_nVexNum;//当前图的顶点个数

public:
	//初始化图
	void Init();
	//插入顶点
	bool InsertVex(Vex sVex);
	//插入边
	bool InsertEdge(Edge sEdge);
	//得到顶点个数
	int GetVexNum();
	//得到顶点的信息
	Vex GetVex(int nVex);
	//查找边的信息
	int FindEdge(int nVex,Edge aEdge[]);
	//遍历景区景点图
	void DFS(int nVex,bool bVisited[],int &nIndex,PathList &pList);
	//深度优先遍历
	void DFSTraverse(int nVex,PathList &pList);
	//搜索最短路径
	int FindShortPath(int nVexStart,int nVexEnd,Edge aPath[]);
	//构建最小生成树
	void FindMinTree(Edge aPath[]);
};

#endif