#ifndef TOURISM_H
#define TOURISM_H

#include"Graph.h"

class CTourism
{
private:
	//��������ͼ
	CGraph m_Graph;

public:
	//������������ͼ
	void CreateGraph();
	//��ѯ������Ϣ
	void GetSpotInfo();
	//���ξ��㵼��
	void TravelPath();
	//���·��
	void FindShortPath();
	//�����·�滮
	void DesignPath();
};

#endif