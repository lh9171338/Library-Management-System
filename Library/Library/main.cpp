#include"library.h"

int main()
{
	//clear();				//���
	getn();
	int m;
	while(1)
	{
		system("color 09");
		cout<<"��ѡ�����\n1.����Ա\n2.������\n3.�˳�\n";
		cin>>m;
		switch(m)
		{
		case 1:system("color 0B");guanliyuan();
			break;
		case 2:system("color 0A");jieshuzhe();
			break;
		case 3:return 0;
		default:break;
		}
		system("pause");
		system("cls");
	}
    return 0;
}