#include<iostream>

#include"Tourism.h"

using namespace std;

int main()
{
	CTourism tourism;
	int bRunning = 1;
	char key[10]={0};
	while(bRunning)
	{
		//输出界面
		cout<<"==========景区管理系统=========="<<endl;
		cout<<"1.创建景区图"<<endl;
		cout<<"2.查询景点信息"<<endl;
		cout<<"3.旅游景点导航"<<endl;
		cout<<"4.搜索最短路径"<<endl;
		cout<<"5.铺设电路规划"<<endl;
		cout<<"0.退出"<<endl;

		//输入选项
		cout<<"请输入操作编号(0~5):";
		cin>>key;

		//处理用户输入
		switch(key[0])
		{
		case '1'://创建景区景点图
			tourism.CreateGraph();
			break;
		case '2'://查询景点信息
			tourism.GetSpotInfo();
			break;
		case '3'://旅游景点导航
			tourism.TravelPath();
			break;
		case '4'://搜索最短路径
			tourism.FindShortPath();
			break;
		case '5'://铺设电路规划
			tourism.DesignPath();
			break;
		case '0'://退出
			exit(0);
		default:
			cout<<"请输入0~5的数字:"<<endl;
			break;
		}
	}
	return 0;
}