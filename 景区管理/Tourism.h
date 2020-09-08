#ifndef TOURISM_H
#define TOURISM_H

#include"Graph.h"

class CTourism
{
private:
	//景区景点图
	CGraph m_Graph;

public:
	//创建景区景点图
	void CreateGraph();
	//查询景点信息
	void GetSpotInfo();
	//旅游景点导航
	void TravelPath();
	//最短路径
	void FindShortPath();
	//铺设电路规划
	void DesignPath();
};

#endif