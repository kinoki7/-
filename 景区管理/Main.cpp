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
		//�������
		cout<<"==========��������ϵͳ=========="<<endl;
		cout<<"1.��������ͼ"<<endl;
		cout<<"2.��ѯ������Ϣ"<<endl;
		cout<<"3.���ξ��㵼��"<<endl;
		cout<<"4.�������·��"<<endl;
		cout<<"5.�����·�滮"<<endl;
		cout<<"0.�˳�"<<endl;

		//����ѡ��
		cout<<"������������(0~5):";
		cin>>key;

		//�����û�����
		switch(key[0])
		{
		case '1'://������������ͼ
			tourism.CreateGraph();
			break;
		case '2'://��ѯ������Ϣ
			tourism.GetSpotInfo();
			break;
		case '3'://���ξ��㵼��
			tourism.TravelPath();
			break;
		case '4'://�������·��
			tourism.FindShortPath();
			break;
		case '5'://�����·�滮
			tourism.DesignPath();
			break;
		case '0'://�˳�
			exit(0);
		default:
			cout<<"������0~5������:"<<endl;
			break;
		}
	}
	return 0;
}