#ifndef GRAPH_H
#define GRAPH_H

#define MAX_VERTEX_NUM 20//��󶥵���
#define MAX_NAME_LEN 20  //�������Ƴ���
#define MAX_DESC_LEN 1024 //������������


//������Ϣ
struct Vex
{
	int num;//���
	char name[MAX_NAME_LEN];//��������
	char desc[MAX_DESC_LEN];//�������
};

//�ߵ���Ϣ
struct Edge
{
	int vex1;//��һ������ı��
	int vex2;//�ڶ�������ı��
	int weight;//�ߵ�Ȩֵ
};

typedef struct Path
{
	int vexs[20];//������һ��·��
	Path *next;//��һ��·��
}*PathList;

class CGraph
{
private:
	int m_aAdjMatrix[20][20];//�ڽӾ���
	Vex m_aVexs[20];//������Ϣ����
	int m_nVexNum;//��ǰͼ�Ķ������

public:
	//��ʼ��ͼ
	void Init();
	//���붥��
	bool InsertVex(Vex sVex);
	//�����
	bool InsertEdge(Edge sEdge);
	//�õ��������
	int GetVexNum();
	//�õ��������Ϣ
	Vex GetVex(int nVex);
	//���ұߵ���Ϣ
	int FindEdge(int nVex,Edge aEdge[]);
	//������������ͼ
	void DFS(int nVex,bool bVisited[],int &nIndex,PathList &pList);
	//������ȱ���
	void DFSTraverse(int nVex,PathList &pList);
	//�������·��
	int FindShortPath(int nVexStart,int nVexEnd,Edge aPath[]);
	//������С������
	void FindMinTree(Edge aPath[]);
};

#endif