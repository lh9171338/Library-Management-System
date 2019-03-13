#include"library.h"

int main()
{
	//clear();				//清空
	getn();
	int m;
	while(1)
	{
		system("color 09");
		cout<<"请选择身份\n1.管理员\n2.借书者\n3.退出\n";
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