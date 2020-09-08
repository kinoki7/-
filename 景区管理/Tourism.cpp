#include<iostream>

#include"Tourism.h"

using namespace std;

#define VEX_FILE_NAME "Vex.txt"  //��¼������Ϣ���ļ�
#define EDGE_FILE_NAME "Edge.txt"  //��¼����Ϣ���ļ�


void CTourism::CreateGraph()
{
	cout<<"=======������������ͼ======="<<endl;
	//��ʼ��ͼ
	m_Graph.Init();

	//���ļ�
	FILE *pVex = fopen(VEX_FILE_NAME, "r");
	if(!pVex)
	{
		cout<<"���ļ�ʧ�ܣ�"<<endl;
		return;
	}

	//��ȡ������Ŀ
	int nSpotCount = 0;
	fscanf(pVex, "%d\n", &nSpotCount);
	cout<<"������Ŀ��"<<nSpotCount<<endl;

	//��ȡ������Ϣ
	cout<<"------����------"<<endl;
	Vex sVex;
	while(fscanf(pVex, "%d\n%s\n%s\n", &sVex.num, sVex.name, sVex.desc) != -1)
	{
		//��ʾ������Ϣ
		cout<<sVex.num<<"-"<<sVex.name<<endl;

		//��������
		if(!m_Graph.InsertVex(sVex))
		{
			cout<<"��������ʧ�ܣ�"<<endl;
			continue;
		}
	}

	//�ر��ļ�
	fclose(pVex);
	pVex = NULL;

	//���ļ�
	FILE *pEdge = fopen(EDGE_FILE_NAME, "r");
	if(!pEdge)
	{
		cout<<"���ļ�ʧ�ܣ�"<<endl;
		return;
	}

	//��ȡ����Ϣ
	cout<<"------��------"<<endl;
	Edge sEdge;
	while(fscanf(pEdge, "%d\t%d\t%d\n", &sEdge.vex1, &sEdge.vex2, &sEdge.weight) != -1)
	{
		//��ʾ��·��Ϣ
		cout<<"(v"<<sEdge.vex1<<",v"<<sEdge.vex2<<")"<<sEdge.weight<<endl;

		//������
		if(!m_Graph.InsertEdge(sEdge))
		{
			cout<<"������ʧ�ܣ�"<<endl;
			continue;
		}
	}

	//�ر��ļ�
	fclose(pEdge);
	pEdge = NULL;
}

void CTourism::GetSpotInfo()
{
	cout<<"======��ѯ������Ϣ======"<<endl;

	//��þ�����
	int nVexNum = m_Graph.GetVexNum();

	//�г����о���ı�ź�����
	for(int i=0;i<nVexNum;i++)
	{
		Vex sVex = m_Graph.GetVex(i);
		cout<<sVex.num<<"-"<<sVex.name<<endl;
	}

	//����Ҫ��ѯ�ı��
	int nVex;
	cout<<"������Ҫ��ѯ�ľ�����:";
	cin>>nVex;
	if(nVex<0||nVex>=nVexNum)
	{
		cout<<"��������ȷ������!\n";
		return;
	}

	Vex sVex = m_Graph.GetVex(nVex);
	cout<<sVex.name<<endl;//�����������
	cout<<sVex.desc<<endl;//������������Ϣ

	//��ѯ�ܱ߾�����Ϣ
	Edge aEdge[MAX_VERTEX_NUM];
	int nEdgeNum = m_Graph.FindEdge(nVex,aEdge);
	cout<<"====�ܱ߾���===="<<endl;
	for(int i=0;i<nEdgeNum;i++)
	{
		Vex v1 = m_Graph.GetVex(aEdge[i].vex1);
		Vex v2 = m_Graph.GetVex(aEdge[i].vex2);
		//����ܱ߾��㼰����
		cout<<v1.name<<"-"<<v2.name<<aEdge[i].weight<<"m"<<endl;
	}
}

void CTourism::TravelPath()
{
	int choice;
	int nVexNum = m_Graph.GetVexNum();
	cout<<"��������ʼ���ţ�"<<endl;
	cin>>choice;
	if(choice<0||choice>=m_Graph.GetVexNum())
	{
		cout<<"��������ȷ���֣�"<<endl;
		return;
	}

	PathList pList = (PathList)malloc(sizeof(Path));
	PathList phead = pList;

	//������������ͼ
	m_Graph.DFSTraverse(choice,pList);
	//������
	cout<<"����·��Ϊ��"<<endl;
	int i = 1;

	pList = phead;
	while(pList->next)
	{
		//���һ��·��
		Vex sVex = m_Graph.GetVex(pList->vexs[0]);
		cout<<"·��"<<i++<<":"<<sVex.name;
		for(int j=1;j<nVexNum;j++)
		{
			sVex = m_Graph.GetVex(pList->vexs[j]);
			cout<<"->"<<sVex.name;
		}
		cout<<endl;

		//�ͷſռ�
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
	cout<<"======�������·��======"<<endl;
	//��þ�����
	int nVexNum=m_Graph.GetVexNum();

	//�г����о����ź�����
	for(int i=0;i<nVexNum;i++)
	{
		Vex sVex=m_Graph.GetVex(i);//��ѯ������Ϣ
		cout<<sVex.num<<"-"<<sVex.name<<endl;
	}

	int nVexStart,nVexEnd;//������ʼ����յ�
	cout<<"���������ı�ţ�";
	cin>>nVexStart;//���������
	cout<<"�������յ�ı�ţ�";
	cin>>nVexEnd;//�����յ���
	//�ж������Ƿ���ȷ
	if(nVexStart<0||nVexStart>=nVexNum||nVexEnd<0||nVexEnd>=nVexNum)
	{
		cout<<"�������"<<endl;
		return;
	}
	Edge aPath[MAX_VERTEX_NUM];
	int nNum=m_Graph.FindShortPath(nVexStart,nVexEnd,aPath);
	Vex sVex=m_Graph.GetVex(aPath[0].vex1);
	int nLength=0;
	cout<<"���·��Ϊ��"<<sVex.name;
	for(int i=0;i<nNum;i++)
	{
		sVex=m_Graph.GetVex(aPath[i].vex2);
		cout<<"->"<<sVex.name;
		nLength+=aPath[i].weight;
	}
	cout<<endl;
	cout<<"��̾���Ϊ��"<<nLength<<endl;
}

void CTourism::DesignPath()
{
	cout << "======�����·�滮======" << endl;
	Edge aPath[MAX_VERTEX_NUM];  //����߽ṹ���������������������·
	m_Graph.FindMinTree(aPath);  //�õ��滮����·
	int nVexNum = m_Graph.GetVexNum();
	if (nVexNum == 0)
	{
		cout << "���ȴ���ͼ��" << endl;
		return;
	}
	int nAllLength = 0;
	cout << "��������������֮�������·��" << endl;
	for (int i = 0; i < nVexNum - 1; i++)
	{
		Vex sVex1 = m_Graph.GetVex(aPath[i].vex1);
		Vex sVex2 = m_Graph.GetVex(aPath[i].vex2);
		//����������·
		cout << sVex1.name << "-" << sVex2.name << " " << aPath[i].weight << "m" << endl;
		nAllLength += aPath[i].weight;
	}
	cout << "�����·���ܳ���Ϊ��" << nAllLength <<"m"<< endl;
}