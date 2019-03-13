#include"library.h"

int N1=0;
int N3=0;
int N4=0;
int N5=0;
fstream file1,file2,file3,file4,file5,file6;

CTitle Title;
CItem Item;
CBorrower Borrower;
CLoan Loan;
CReservation Reservation;
string key="123456";
int changekey();

int g1();
int g2();

int j1();
int j2();


/*******************************                   TIME               *********************************/

date::date(int year,int month,int day)
{
	m_year=year;
	m_month=month;
	m_day=day;
}
date::date(){}
date date::gettime()												//获取当前时间
{
	time_t t;
	struct tm *local = NULL;
	t=time(NULL);
	localtime_s(local, &t);
	date p(local->tm_year+1900,local->tm_mon+1,local->tm_mday);
	return p;
}
date date::addday(unsigned int n)
{
	int i;
	date p(*this);
	for(i=0;i<n;i++)
		p=p.addaday();
	return p;
}
date date::addaday()
{
	date d(*this);
	d.m_day++;
	switch(d.m_month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:if(d.m_day>31)
			{
				d.m_day=1;
				d.m_month++;
				if(d.m_month>12)
				{
					d.m_month=1;
					d.m_year++;
				}
			}
			break;
	case 4:
	case 6:
	case 9:
	case 11:if(d.m_day>30)
			{
				d.m_day=1;
				d.m_month++;
				if(d.m_month>12)
				{
					d.m_month=1;
					d.m_year++;
				}
			}
			break;
	case 2:if(d.m_year%4)										//平年
		   {
			   if(d.m_day>28)
			   {
					d.m_day=1;
					d.m_month++;
					if(d.m_month>12)
					{
						d.m_month=1;
						d.m_year++;
					}
				}
		   }
		   else
		   {
			   if(d.m_day>29)
			   {
					d.m_day=1;
					d.m_month++;
					if(d.m_month>12)
					{
						d.m_month=1;
						d.m_year++;
					}
				}
		   }
		   break;
		   default:break;
	}
	return d;
}
int date::countday()											//计算超了多少天
{
	int i=0;
	date d1,d2;
	d1=d1.gettime();
	d2=*this;
	if(d1.m_month<d2.m_month||(d1.m_month==d2.m_month&&d1.m_day<=d2.m_day))
		return 0;
	else
	{
		while(1)
		{
			i++;
			d2=d2.addaday();
			if(d1.m_year==d2.m_year&&d1.m_month==d2.m_month&&d1.m_day==d2.m_day)
				break;
		}
		return i;
	}
}


ostream &operator<<(ostream &cout, date &d)
{
	cout<<setw(4)<<d.m_year<<setw(3)<<d.m_month<<setw(3)<<d.m_day;
	return cout;
}




/******************                CTitle                       ***************************/
CTitle* CTitle::m_titleListHead=NULL;
CTitle* CTitle::m_titleListTail=NULL;


CTitle::CTitle(string name,string author,int type)
{
	N1++;
	m_titleID=1000000+N1*100;
	m_name=name;							
	m_author=author;						
	m_type=type;
	m_itemNum=m_itemMax=0;
	m_reservationNum=m_reservationMax=0;
	m_nextTitle=NULL;
}
CTitle::CTitle(){}
int CTitle::AddTitle()											//增加标题				
{
	string name,author;
	int type;
	cout<<"请输入书名,作者,书还是杂志(1代表书,2代表杂志)(输入#退出)"<<endl;
	cin>>name;
	if(name=="#")
		return 0;
	cin>>author>>type;
	if(FindCTitle(name)!=NULL)
	{
		cout<<"该标题已存在"<<endl;
		return 0;
	}
	CTitle p(name,author,type);
	AddCTitle(p);
	cout<<"添加成功"<<endl<<endl;;
	p.GetTitle();
	return 1;
}
int CTitle::DeleteTitle()										//删除标题(无外借书)
{
	int i;
	CTitle *p=NULL;
	CItem *p3=NULL;
	CReservation *p1=NULL;
	CBorrower *p2=NULL;
	string name;
	cout<<"请输入要删除的标题名字(输入#退出)"<<endl;
	cin>>name;
	system("cls");
	if(name=="#")
		return 0;
	p=p->FindCTitle(name);
	while(p==NULL)
	{
		cout<<"无该标题编号，请重新输入(输入#退出)"<<endl;
		cin>>name;
		p=p->FindCTitle(name);
		system("cls");
		if(name=="#")
				return 0;
	}
	p->GetTitle();
	for(i=0;i<p->m_itemNum;i++)
	{
		p3=p3->FindCItem(p->m_itemList[i]);
		p3->DeleteCItem(p->m_itemList[i]);
		p->DeleteItem(p->m_itemList[i]);
	}
	for(i=0;i<p->m_reservationNum;i++)
	{
		p1=p1->FindCReservation(p->m_reservationList[i]);
		p2=p2->FindCBorrower(p1->m_borrowerID);
		p1->DeleteCReservation(p->m_reservationList[i]);
		p2->DeleteReservation(p->m_reservationList[i]);
		p->DeleteReservation(p->m_reservationList[i]);
	}
	DeleteCTitle(name);
	cout<<"删除成功"<<endl;
	return 1;
}
void CTitle::LookTitle()										//查看所有标题
{
	CTitle* pTitle=m_titleListHead;
	if(pTitle!=NULL)
	{
		cout<<"标题编号"<<'\t'<<"书名"<<'\t'<<"作者"<<'\t'<<"类型(1.书，2.杂志)"<<'\t'<<"所含书目数量"<<endl;
		while(pTitle!=NULL)
		{
			pTitle->ShowTitle();
			pTitle=pTitle->m_nextTitle;
		}
	}
	else
		cout<<"没有信息"<<endl;
}
void CTitle::GetTitle()
{
	cout<<"标题编号"<<'\t'<<"书名"<<'\t'<<"作者"<<'\t'<<"类型(1.书，2.杂志)"<<'\t'<<"所含书目数量"<<endl;
	ShowTitle();
}
void CTitle::ShowTitle()										//显示该标题信息
{
	cout<<m_titleID<<"\t\t"<<m_name<<'\t'<<m_author<<'\t'<<m_type<<"\t\t\t"<<m_itemNum<<endl;
}
void CTitle::FindTitle()										//查看某标题
{
	string name;
	int i;
	cout<<"请输入书名"<<endl;
	cin>>name;
	CTitle *p=NULL;
	p=p->FindCTitle(name);
	if(p==NULL)
		cout<<"没找到该书"<<endl;
	else
	{
		cout<<"标题编号"<<'\t'<<"书名"<<'\t'<<"作者"<<'\t'<<"类型(1.书，2.杂志)"<<'\t'<<"所含书目数量"<<endl;
		p->ShowTitle();
		CItem *q=NULL;
		for(i=0;i<p->m_itemNum;i++)
		{
			cout<<endl;
			q=q->FindCItem(p->m_itemList[i]);
			q->GetItem();
		}
		cout<<endl<<"已有"<<p->m_reservationNum<<"人预定"<<endl;
	}
}
void CTitle::LookaTitle()										//查看某标题借阅信息
{
	string name;
	cout<<"请输入书名"<<endl;
	cin>>name;
	CTitle *p=NULL;
	p=p->FindCTitle(name);
	system("cls");
	if(p==NULL)
		cout<<"没找到该书"<<endl;
	else
	{
		cout<<"标题编号"<<'\t'<<"书名"<<'\t'<<"作者"<<'\t'<<"类型(1.书，2.杂志)"<<'\t'<<"所含书目数量"<<endl;
		p->ShowTitle();
		int i,m=0;
		CItem *q1=NULL;
		CReservation *q2=NULL;
		for(i=0;i<p->m_itemNum;i++)
		{
			q1=q1->FindCItem(p->m_itemList[i]);
			if(q1->m_loanID!=0)									//表示已借出
				m++;
		}
		cout<<endl<<"已有"<<m<<"本借出"<<endl;
		if(m!=0)
			cout<<endl<<"借书编号"<<'\t'<<"标题编号"<<'\t'<<"书名"<<'\t'<<"书目编号"<<'\t'<<"借书者编号"<<'\t'<<"借书者姓名"<<"\t"<<"借书日期"<<"\t"<<"应还日期"<<endl;
		for(i=0;i<p->m_itemNum;i++)
		{
			q1=q1->FindCItem(p->m_itemList[i]);
			if(q1->m_loanID!=0)									//表示已借出
			{
				CLoan *q3=NULL;
				q3=q3->FindCLoan(q1->m_loanID);
				q3->ShowLoan();
			}
		}
		cout<<endl<<"已有"<<p->m_reservationNum<<"人预定"<<endl;
		if(p->m_reservationNum!=0)
			cout<<"预定编号"<<'\t'<<"标题编号"<<'\t'<<"书名"<<'\t'<<"借书者编号"<<'\t'<<"借书者姓名"<<endl;
		for(i=0;i<p->m_reservationNum;i++)
		{
			q2=q2->FindCReservation(p->m_reservationList[i]);
			q2->ShowReservation();
		}
	}
}
void CTitle::AddItem(int itemID)								//增加该标题下的书目
{
	m_itemNum++;
	int* tempBuff=m_itemList;
	m_itemList=new int[m_itemNum];
	memcpy(m_itemList,tempBuff,(m_itemNum-1)*sizeof(int));
	m_itemList[m_itemNum-1]=itemID;
}
void CTitle::DeleteItem(int itemID)								//删除该标题下的指定书目
{
	int finded=0,i;
	for(i=0;i<m_itemNum;i++)
	{
		if(m_itemList[i]==itemID)
		finded=1;
		if((finded)&&(i<(m_itemNum-1)))
		{
	        int* tempBuff=m_itemList+i;
			int count=m_itemNum-1-i;
			memcpy(tempBuff,tempBuff+1,count*sizeof(int));
		}
	}
	m_itemNum--;
}
void CTitle::AddReservation(int reservationID)					//增加对该标题的一次预订
{
	m_reservationNum++;
	int* tempBuff=m_reservationList;
	m_reservationList=new int[m_reservationNum];
	memcpy(m_reservationList,tempBuff,(m_reservationNum-1)*sizeof(int));
	m_reservationList[m_reservationNum-1]=reservationID;
}
void CTitle::DeleteReservation(int reservationID)				//删除该标题的指定预订
{
	int finded=0,i;
	for(i=0;i<m_reservationNum;i++)
	{
		if(m_reservationList[i]==reservationID)
			finded=1;
		if((finded)&&(i<(m_reservationNum-1)))
		{
	        int* tempBuff=m_reservationList+i;
			int count=m_reservationNum-1-i;
			memcpy(tempBuff,tempBuff+1,count*sizeof(int));
		}
	}
	m_reservationNum--;
}
void CTitle::AddCTitle(CTitle title)							//增加结点
{
	CTitle *p=new CTitle(title);
	if(m_titleListTail==NULL)
	{	
		m_titleListTail=p;
		if(m_titleListHead==NULL)
			m_titleListHead=p;
	}
	else
	{	
		m_titleListTail->m_nextTitle=p;
		m_titleListTail=p;
	}
}
void CTitle::DeleteCTitle(string name)							//删除结点		
{
	CTitle* pTitle=m_titleListHead;
	CTitle* proTitle=NULL;
	while(pTitle!=NULL)
	{    
		if(pTitle->m_name==name)
    		{
        		if(pTitle==m_titleListHead)
       			{   	
					m_titleListHead=pTitle->m_nextTitle;
           			if(pTitle==m_titleListTail)
               			m_titleListTail=NULL;
       			 }
				else if(pTitle==m_titleListTail)
    			{   	
					m_titleListTail=proTitle;
        			proTitle->m_nextTitle=NULL;
   				}
    			else
   				{	
					proTitle->m_nextTitle=pTitle->m_nextTitle;
				}
   				delete pTitle;
    			break;
		}
		proTitle=pTitle;
		pTitle=pTitle->m_nextTitle;
	}
}
CTitle* CTitle::FindCTitle(int titleID)							//查找节点	
{
	CTitle* pTitle=m_titleListHead;
	while(pTitle!=NULL)
	{
		if(pTitle->m_titleID==titleID)
			return pTitle;
		pTitle=pTitle->m_nextTitle;
	}
	return NULL;
}
CTitle* CTitle::FindCTitle(string name)							//查找节点	
{
	CTitle* pTitle=m_titleListHead;
	while(pTitle!=NULL)
	{
		if(pTitle->m_name==name)
			return pTitle;
		pTitle=pTitle->m_nextTitle;
	}
	return NULL;
}


/********************************     CItem            *******************************/
CItem* CItem::m_itemListHead=NULL;
CItem* CItem::m_itemListTail=NULL;


CItem::CItem(int titleID,int itemID)
{
	m_titleID=titleID;
	m_itemID=itemID;
	m_loanID=0;													//未被借出
	m_nextItem=NULL;
}
CItem::CItem(){}

int CItem::AddItem()											//创建该标题下的书目
{
	string name;
	cout<<"请输入书名"<<endl;
	cin>>name;
	CTitle *p=NULL;
	p=p->FindCTitle(name);
	system("cls");
	if(p==NULL)
	{
		int m;
		cout<<"没有该标题，请先添加\n您选择:\n1.添加标题\n2.退出"<<endl;
		cin>>m;
		system("cls");
		if(m==1)
			p->AddTitle();
		else
			return 0;
	}
	p->GetTitle();
	CItem q(p->m_titleID,p->m_titleID+p->m_itemNum+1);
	AddCItem(q);
	p->AddItem(q.m_itemID);
	q.GetItem();
	cout<<"添加成功"<<endl;
	return 1;
}
int CItem::DeleteItem()											//删除该标题下的指定书目(书未借出)
{
	int itemID;
	CItem *p=NULL;
	CTitle *p1=NULL;
	cout<<"请输入书目编号(输入0退出)"<<endl;
	cin>>itemID;
	system("cls");
	if(itemID==0)
		return 0;
	p=p->FindCItem(itemID);
	while(p==NULL)
	{
		cout<<"无该书目编号，请重新输入(输入0退出)"<<endl;
		cin>>itemID;
		system("cls");
		p=p->FindCItem(itemID);
		if(itemID==0)
			return 0;
	}
	p->GetItem();
	p1=p1->FindCTitle(p->m_titleID);
	p1->DeleteItem(itemID);
	p->DeleteCItem(itemID);
	cout<<"删除成功"<<endl;
	return 1;
}
void CItem::LookItem()
{
	CItem* pItem=m_itemListHead;
	CTitle *p2=NULL;
	if(pItem!=NULL)
	{
		cout<<"标题编号"<<'\t'<<"书名"<<'\t'<<"书目编号"<<'\t'<<"借出状态"<<endl;
		while(pItem!=NULL)
		{
			p2=p2->FindCTitle(pItem->m_titleID);
			cout<<pItem->m_titleID<<"\t\t"<<p2->m_name<<'\t'<<pItem->m_itemID<<"\t\t";
		pItem->IsBorrowed();
			pItem=pItem->m_nextItem;
		}
	}
	else
		cout<<"没有信息"<<endl;
}
void CItem::FindItem()											//查找书目
{
	int itemID;
	CItem *p1=NULL;
	CTitle *p2=NULL;
	cout<<"请输入书目编号"<<endl;
	cin>>itemID;
	system("cls");
	p1=p1->FindCItem(itemID);
	if(p1==NULL)
		cout<<"没有找到"<<endl;
	else
	{
		p2=p2->FindCTitle(p1->m_titleID);
		cout<<"标题编号"<<'\t'<<"书名"<<'\t'<<"书目编号"<<'\t'<<"借出状态"<<endl;
		cout<<p2->m_titleID<<"\t\t"<<p2->m_name<<'\t'<<p1->m_itemID<<"\t\t";
		p1->IsBorrowed();
		if(p1->m_loanID!=0)											//已被借出
		{
			CLoan *p3=NULL;
			p3=p3->FindCLoan(p1->m_loanID);
			p3->GetLoan();
		}
	}
}
void CItem::SetLoan(int loanID)									//表示该书目被出借
{		
	m_loanID=loanID;											//已被借出
}
void CItem::ShowItem()											//显示书目信息
{
	cout<<m_titleID<<"\t\t"<<m_itemID<<"\t\t";
	IsBorrowed();
}
void CItem::GetItem()
{
	cout<<"标题编号"<<'\t'<<"书目编号"<<'\t'<<"借出状态"<<endl;
	ShowItem();
}
void CItem::IsBorrowed()										//返回该书目是否被出借的信息
{
	if(m_loanID==0)
		cout<<"未借出"<<endl;
	else
		cout<<"已借出"<<endl;
}
void CItem::AddCItem(CItem item)								//增加结点
{
	CItem *p=new CItem(item);
	if(m_itemListTail==NULL)
	{	
		m_itemListTail=p;
		if(m_itemListHead==NULL)
			m_itemListHead=p;
	}
	else
	{	
		m_itemListTail->m_nextItem=p;
		m_itemListTail=p;
	}
}			
void CItem::DeleteCItem(int itemID)								//删除结点		
{
	CItem* pItem=m_itemListHead;
	CItem* proItem=NULL;
	while(pItem!=NULL)
	{    
		if(pItem->m_itemID==itemID)
    	{
        		if(pItem==m_itemListHead)
       			{   	
					m_itemListHead=pItem->m_nextItem;
           			if(pItem==m_itemListTail)
               			m_itemListTail=NULL;
       			 }
				else if(pItem==m_itemListTail)
    			{   	
					m_itemListTail=proItem;
        			proItem->m_nextItem=NULL;
   				}
    			else
   				{	
					proItem->m_nextItem=pItem->m_nextItem;
				}
   				delete pItem;
    			break;
		}
		proItem=pItem;
		pItem=pItem->m_nextItem;
	}
}
CItem* CItem::FindCItem(int itemID)								//查找节点	
{
	CItem* pItem=m_itemListHead;
	while(pItem!=NULL)
	{
		if(pItem->m_itemID==itemID)
			return pItem;
		pItem=pItem->m_nextItem;
	}
	return NULL;
}

/*******************************        CBorrower           *************************/
CBorrower* CBorrower::m_borrowerListHead=NULL;
CBorrower* CBorrower::m_borrowerListTail=NULL;


CBorrower::CBorrower(string name,string key,string sex,string address,string city)
{
	N3++;
	m_borrowerID=N3;
	m_name=name;
	m_key=key;
	m_sex=sex;
	m_address=address;
	m_city=city;
	m_loanNum=0;
	m_reservationNum=0;
	m_nextborrower=NULL;
	m_fine=m_fine1=0;
}
CBorrower::CBorrower(){}

int CBorrower::AddBorrower()									//注册
{
	string name,key1,key2,sex,address,city;
	cout<<"/***********************欢迎注册图书馆系统******************/\n请输入您的姓名，性别，住址，城市(输入#退出)"<<endl;
	cin>>name;
	if(name=="#")
		return 0;
	cin>>sex>>address>>city;
	cout<<"请设置密码"<<endl;
	cin>>key1;
	system("cls");
	cout<<"请再次输入密码"<<endl;
	cin>>key2;
	system("cls");
	while(key1!=key2)
	{
		cout<<"两次输入的密码不一致，请重新输入"<<endl;
		cin>>key1>>key2;
		system("cls");
	}
    CBorrower p(name,key1,sex,address,city);
	AddCBorrower(p);
	cout<<"注册成功"<<endl;
	return 0;
}
int CBorrower::DeleteBorrower()								  //注销
{
	string name,key;
	int m=0;
	cout<<"请输入您的姓名,密码(只有3次输入机会,输入#退出)"<<endl;
	cin>>name;
	if(name=="#")
		return 0;
	cin>>key;
	system("cls");
	CBorrower *p=NULL;
	p=p->FindCBorrower(name);
	while(1)
	{
		if(p==NULL||(p!=NULL&&p->m_key!=key))
		{
			m++;
			if(m==3)
				return 0;
			cout<<"信息有误,请重新输入(还有"<<3-m<<"次机会,输入#退出)"<<endl;
			cin>>name;
			if(name=="#")
				return 0;
			else
			{
				cin>>key;
				p=p->FindCBorrower(name);
				m++;
			}
			system("cls");
		}
		else
			break;
	}
	if(p->countfine()>0)
		cout<<"您有罚金未缴纳,请先缴纳"<<endl;
	else if(p->m_loanNum!=0)
		cout<<"您有借书行为，请先归还"<<endl;
	else
	{
		if(p->m_reservationNum!=0)
		{
			int i;
			for(i=0;i<p->m_reservationNum;i++)
			{
				CReservation *q1=NULL;
				CTitle *q2=NULL;
				 q1=q1->FindCReservation(p->m_reservationList[i]);
				 q2=q2->FindCTitle(q1->m_titleID);
				 q1->DeleteCReservation(p->m_reservationList[i]);
				 q2->DeleteReservation(p->m_reservationList[i]);
			}
		}
		DeleteCBorrower(name);
		cout<<"注销成功，欢迎您的使用"<<endl;
	}
	return 1;
}
void CBorrower::LookBorrower()
{
	CBorrower* pBorrower=m_borrowerListHead;
	if(pBorrower!=NULL)
	{
		cout<<"借书者编号"<<'\t'<<"借书者姓名"<<'\t'<<"性别"<<'\t'<<"住址"<<'\t'<<"城市"<<'\t'<<"罚金"<<endl;
		while(pBorrower!=NULL)
		{
			pBorrower->ShowBorrower();
			pBorrower=pBorrower->m_nextborrower;
		}
	}
	else
		cout<<"没有信息"<<endl;
}
void CBorrower::ShowBorrower()											//显示该借书者信息
{
	countfine();
	cout<<m_borrowerID<<"\t\t"<<m_name<<"\t\t"<<m_sex<<'\t'<<m_address<<'\t'<<m_city<<'\t'<<m_fine<<endl;
}
void CBorrower::FindBorrower()
{
	int borrowerID,i;
	CBorrower *p=NULL;
	cout<<"请输入借书者编号"<<endl;
	cin>>borrowerID;
	p=FindCBorrower(borrowerID);
	if(p==NULL)
		cout<<"未找到该借书者"<<endl;
	else
	{
		CLoan *p1=NULL;
		CReservation *p2=NULL;
		cout<<"借书者编号"<<'\t'<<"借书者姓名"<<'\t'<<"性别"<<'\t'<<"住址"<<'\t'<<"城市"<<'\t'<<"罚金"<<endl;
		p->ShowBorrower();
		if(p->m_loanNum==0)
			cout<<"无借书信息"<<endl;
		else
		{
			cout<<endl<<"借书编号"<<'\t'<<"标题编号"<<'\t'<<"书名"<<'\t'<<"书目编号"<<'\t'<<"借书者编号"<<'\t'<<"借书者姓名"<<"\t"<<"借书日期"<<"\t"<<"应还日期"<<endl;
			for(i=0;i<p->m_loanNum;i++)
			{
				p1=p1->FindCLoan(p->m_loanList[i]);
				p1->ShowLoan();
			}
		}
		if(p->m_reservationNum==0)
			cout<<"无预定信息"<<endl;
		else
		{
			cout<<endl<<"预定编号"<<'\t'<<"标题编号"<<'\t'<<"书名"<<'\t'<<"借书者编号"<<'\t'<<"借书者姓名"<<endl;
			for(i=0;i<p->m_reservationNum;i++)
			{
				p2=p2->FindCReservation(p->m_reservationList[i]);
				p2->ShowReservation();
			}
		}
	}
}
int CBorrower::Show()													//显示自己的信息
{
	string name,key;
	int m=0;
	cout<<"请输入您的姓名,密码(只有3次输入机会,输入#退出)"<<endl;
	cin>>name;
	if(name=="#")
		return 0;
	cin>>key;
	system("cls");
	CBorrower *p=NULL;
	p=p->FindCBorrower(name);
	while(1)
	{
		if(p==NULL||(p!=NULL&&p->m_key!=key))
		{
			m++;
			if(m==3)
				return 0;
			cout<<"信息有误,请重新输入(还有"<<3-m<<"次机会,输入#退出)"<<endl;
			cin>>name;
			if(name=="#")
				return 0;
			else
			{
				cin>>key;
				p=p->FindCBorrower(name);
			}
			system("cls");
		}
		else
			break;
	}
	if(p->countfine()>0)
	{
		cout<<"您有罚金需缴纳\n1.现在缴纳\n2.等下缴纳\n";
		cin>>m;
		if(m==1)
		{
			system("cls");
			p->givefine();
		}
	}
	system("cls");
	int i;
	CLoan *p1=NULL;
	CReservation *p2=NULL;
	cout<<"借书者编号"<<'\t'<<"借书者姓名"<<'\t'<<"性别"<<'\t'<<"住址"<<'\t'<<"城市"<<'\t'<<"罚金"<<endl;
	p->ShowBorrower();
	if(p->m_loanNum==0)
		cout<<"无借书信息"<<endl;
	else
	{
		cout<<endl<<"借书编号"<<'\t'<<"标题编号"<<'\t'<<"书名"<<'\t'<<"书目编号"<<'\t'<<"借书者编号"<<'\t'<<"借书者姓名"<<"\t"<<"借书日期"<<"\t"<<"应还日期"<<endl;
		for(i=0;i<p->m_loanNum;i++)
		{
			p1=p1->FindCLoan(p->m_loanList[i]);
			p1->ShowLoan();
		}
	}
	if(p->m_reservationNum==0)
		cout<<"无预定信息"<<endl;
	else
	{
		cout<<endl<<"预定编号"<<'\t'<<"标题编号"<<'\t'<<"书名"<<'\t'<<"借书者编号"<<'\t'<<"借书者姓名"<<endl;
		for(i=0;i<p->m_reservationNum;i++)
		{
			p2=p2->FindCReservation(p->m_reservationList[i]);
			p2->ShowReservation();
		}
	}
	return 1;
}
int CBorrower::changekey()												//修改密码
{
	string name,key1,key2;
	int m=0;
	cout<<"请输入您的姓名,密码(只有3次输入机会,输入#退出)"<<endl;
	cin>>name;
	if(name=="#")
		return 0;
	cin>>key1;
	system("cls");
	CBorrower *p=NULL;
	p=p->FindCBorrower(name);
	while(1)
	{
		if(p==NULL||(p!=NULL&&p->m_key!=key1))
		{
			m++;
			if(m==3)
				return 0;
			cout<<"信息有误,请重新输入(还有"<<3-m<<"次机会,输入#退出)"<<endl;
			cin>>name;
			if(name=="#")
				return 0;
			else
			{
				cin>>key1;
				p=p->FindCBorrower(name);
			}
			system("cls");
		}
		else
			break;
	}
	if(p->countfine()>0)
	{
		cout<<"您有罚金需缴纳\n1.现在缴纳\n2.等下缴纳\n";
		cin>>m;
		if(m==1)
		{
			system("cls");
			p->givefine();
		}
	}
	system("cls");
	cout<<"请输入新密码"<<endl;
	cin>>key1;
	system("cls");
	cout<<"请再次输入密码"<<endl;
	cin>>key2;
	system("cls");
	while(key1!=key2)
	{
		cout<<"两次输入的密码不一致，请重新输入"<<endl;
		cin>>key1>>key2;
		system("cls");
	}
	p->m_key=key1;
	cout<<"修改成功,请记好您的密码"<<endl;
	return 1;
}
void CBorrower::AddReservation(int reservationID)						//增加预订
{
	m_reservationNum++;
	int* tempBuff=m_reservationList;
	m_reservationList=new int[m_reservationNum];
	memcpy(m_reservationList,tempBuff,(m_reservationNum-1)*sizeof(int));
	m_reservationList[m_reservationNum-1]=reservationID;
}
void CBorrower::DeleteReservation(int reservationID)					//删除预订
{
	int finded=0,i;
	for(i=0;i<m_reservationNum;i++)
	{
		if(m_reservationList[i]==reservationID)
		finded=1;
		if((finded)&&(i<(m_loanNum-1)))
		{
	        int* tempBuff=m_reservationList+i;
			int count=m_reservationNum-1-i;
			memcpy(tempBuff,tempBuff+1,count*sizeof(int));
		}
	}
	m_reservationNum--;
}
void CBorrower::AddLoan(int loanID)										//借书
{
	m_loanNum++;
	int* tempBuff=m_loanList;
	m_loanList=new int[m_loanNum];
	memcpy(m_loanList,tempBuff,(m_loanNum-1)*sizeof(int));
	m_loanList[m_loanNum-1]=loanID;
}
void CBorrower::DeleteLoan(int loanID)									//删除所借书目
{
	int finded=0,i;
	for(i=0;i<m_loanNum;i++)
	{
		if(m_loanList[i]==loanID)
		finded=1;
		if((finded)&&(i<(m_loanNum-1)))
		{
	        int* tempBuff=m_loanList+i;
			int count=m_loanNum-1-i;
			memcpy(tempBuff,tempBuff+1,count*sizeof(int));
		}
	}
	m_loanNum--;
}
float CBorrower::countfine()											//计算罚金
{
	int i,m=0;
	CLoan *p=NULL;
	//date q(2016,4,15);												//测试功能用
	for(i=0;i<m_loanNum;i++)
	{
		p=p->FindCLoan(m_loanList[i]);
		m+=p->m_timeExpire.countday();
		//m+=q.countday();
	}
	m_fine=m*0.5+m_fine1;														//超一天5毛
	return m_fine;
}
void CBorrower::givefine()												//缴纳罚金
{
	float m=countfine();
	if(m==0)
		cout<<"您不需要缴纳罚金"<<endl;
	else
	{
		cout<<"您共需缴纳"<<m<<"元罚金"<<endl;
	/**************************		
	                        机器自动收取罚金
							********************************/
		Sleep(5000);
		m_fine1=0;
		system("cls");
		cout<<"缴纳成功,抱歉给您带来了不便,您的权限已恢复"<<endl;
	}
}
int CBorrower::Givefine()												//缴纳罚金
{
	string name,key;
	int m=0;
	cout<<"请输入您的姓名,密码(只有3次输入机会,输入#退出)"<<endl;
	cin>>name;
	if(name=="#")
		return 0;
	cin>>key;
	system("cls");
	CBorrower *p=NULL;
	p=p->FindCBorrower(name);
	while(1)
	{
		if(p==NULL||(p!=NULL&&p->m_key!=key))
		{
			m++;
			if(m==3)
				return 0;
			cout<<"信息有误,请重新输入(还有"<<3-m<<"次机会,输入#退出)"<<endl;
			cin>>name;
			system("cls");
			if(name=="#")
				return 0;
			else
			{
				cin>>key;
				p=p->FindCBorrower(name);
			}
		}
		else
			break;
	}
	if(p->m_loanNum>0)
	{
		cout<<"请先还书"<<endl;
		return 0;
	}
	p->givefine();
	return 1;
}
void CBorrower::AddCBorrower(CBorrower borrower)						//增加结点
{
	CBorrower *p=new CBorrower(borrower);
	if(m_borrowerListTail==NULL)
	{	
		m_borrowerListTail=p;
		if(m_borrowerListHead==NULL)
			m_borrowerListHead=p;
	}
	else
	{	
		m_borrowerListTail->m_nextborrower=p;
		m_borrowerListTail=p;
	}
}
void CBorrower::DeleteCBorrower(string name)							//删除结点		
{
	CBorrower* pBorrower=m_borrowerListHead;
	CBorrower* proBorrower=NULL;
	while(pBorrower!=NULL)
	{    
		if(pBorrower->m_name==name)
    		{
        		if(pBorrower==m_borrowerListHead)
       			{   	
					m_borrowerListHead=pBorrower->m_nextborrower;
           			if(pBorrower==m_borrowerListTail)
               			m_borrowerListTail=NULL;
       			 }
				else if(pBorrower==m_borrowerListTail)
    			{   	
					m_borrowerListTail=proBorrower;
        			proBorrower->m_nextborrower=NULL;
   				}
    			else
   				{	
					proBorrower->m_nextborrower=pBorrower->m_nextborrower;
				}
   				delete pBorrower;
    			break;
		}
		proBorrower=pBorrower;
		pBorrower=pBorrower->m_nextborrower;
	}
}
CBorrower* CBorrower::FindCBorrower(string name)						//查找节点	
{
	CBorrower* pBorrower=m_borrowerListHead;
	while(pBorrower!=NULL)
	{
		if(pBorrower->m_name==name)
			return pBorrower;
		pBorrower=pBorrower->m_nextborrower;
	}
	return NULL;
}		
CBorrower* CBorrower::FindCBorrower(int borrowerID)						//查找节点	
{
	CBorrower* pBorrower=m_borrowerListHead;
	while(pBorrower!=NULL)
	{
		if(pBorrower->m_borrowerID==borrowerID)
			return pBorrower;
		pBorrower=pBorrower->m_nextborrower;
	}
	return NULL;
}
/*******************************            CLoan           **************************/
CLoan* CLoan::m_loanListHead=NULL;
CLoan* CLoan::m_loanListTail=NULL;


CLoan::CLoan(int itemID,int borrowerID)
{
	N4++;
	m_loanID=N4;
	m_itemID=itemID;
	m_borrowerID=borrowerID;
	m_nextLoan=NULL;
	m_timeLoan=m_timeLoan.gettime();
	m_timeExpire=m_timeLoan.addday(30);
}
CLoan::CLoan(){}
int CLoan::AddLoan()											//增加借书行为
{
	int itemID;
	string name,key;
	int m=0;
	cout<<"请输入书目编号(输入0退出)"<<endl;
	CItem *p1=NULL;
	CBorrower *p2=NULL;
	cin>>itemID;
	system("cls");
	if(itemID==0)
		return 0;
	p1=p1->FindCItem(itemID);
	while(p1==NULL)
	{
		cout<<"无该书目编号，请重新输入(输入0退出)"<<endl;
		cin>>itemID;
		system("cls");
		if(itemID==0)
			return 0;
		p1=p1->FindCItem(itemID);
	}
	if(p1->m_loanID!=0)
	{
		cout<<"该书已借出"<<endl;
		return 0;
	}
	cout<<"请输入您的姓名,密码(只有3次输入机会)"<<endl;
	cin>>name>>key;
	system("cls");
	p2=p2->FindCBorrower(name);
	while(1)
	{
		if(p2==NULL||(p2!=NULL&&p2->m_key!=key))
		{
			m++;
			if(m==3)
				return 0;
			cout<<"信息有误,请重新输入(还有"<<3-m<<"次机会,输入#退出)"<<endl;
			cin>>name;
			if(name=="#")
				return 0;
			else
			{
				cin>>key;
				p2=p2->FindCBorrower(name);
			}
			system("cls");
		}
		else
			break;
	}
	if(p2->countfine()>0)
	{
		cout<<"您有罚金需缴纳,暂时失去借书权限\n1.现在缴纳\n2.等下缴纳(退出)\n";
		cin>>m;
		if(m==1)
		{
			system("cls");
			p2->givefine();
		}
		else
			return 0;
	}
	system("cls");
	CLoan q(itemID,p2->m_borrowerID);
	AddCLoan(q);
	p1->SetLoan(q.m_loanID);
	p2->AddLoan(q.m_loanID);
	q.GetLoan();
	cout<<"添加成功"<<endl;
	return 1;
}
void CLoan::DeleteLoan()										//还书
{
	int itemID;
	cout<<"请输入书目编号"<<endl;
	CItem *p1=NULL;
	CBorrower *p2=NULL;
	CLoan *q=NULL;
	cin>>itemID;
	system("cls");
	p1=p1->FindCItem(itemID);
	while(1)
	{
		if(p1==NULL||p1->m_loanID==0)
		{
			cout<<"书目编号输入有误，请重新输入"<<endl;
			cin>>itemID;
			system("cls");
			p1=p1->FindCItem(itemID);
		}
		else
			break;
	}
	q=q->FindCLoan(p1->m_loanID);
	p1->SetLoan(0);
	p2=p2->FindCBorrower(q->m_borrowerID);
	p2->DeleteLoan(q->m_loanID);
	cout<<"还书成功"<<endl;
	int m=q->m_timeExpire.countday();
	if(m>0)
	{
		p2->m_fine1+=m*0.5;
		cout<<"您超时还书,需缴纳一定罚金(超时一天0.5元),否则将失去部分权限"<<endl;
	}
	DeleteCLoan(q->m_loanID);
}

void CLoan::LookLoan()
{
	CLoan* pLoan=m_loanListHead;
	if(pLoan!=NULL)
	{
		cout<<"借书编号"<<'\t'<<"标题编号"<<'\t'<<"书名"<<'\t'<<"书目编号"<<'\t'<<"借书者编号"<<'\t'<<"借书者姓名"<<'\t'<<"借书日期"<<"\t"<<"应还日期"<<endl;
		while(pLoan!=NULL)
		{
			pLoan->ShowLoan();
			pLoan=pLoan->m_nextLoan;
		}
	}
	else
		cout<<"没有信息"<<endl;
}
void CLoan::ShowLoan()										//显示某次借书信息
{
	CTitle *p1=NULL;
	CItem *p2=NULL;
	CBorrower *p3=NULL;
	p2=p2->FindCItem(m_itemID);
	p1=p1->FindCTitle(p2->m_titleID);
	p3=p3->FindCBorrower(m_borrowerID);
	cout<<m_loanID<<"\t\t"<<p2->m_titleID<<"\t\t"<<p1->m_name<<"\t"<<m_itemID<<"\t\t"<<m_borrowerID<<"\t\t"<<p3->m_name<<"\t\t"<<m_timeLoan<<"\t"<<m_timeExpire<<endl;
}
void CLoan::GetLoan()
{
	cout<<"借书编号"<<'\t'<<"标题编号"<<'\t'<<"书名"<<'\t'<<"书目编号"<<'\t'<<"借书者编号"<<'\t'<<"借书者姓名"<<'\t'<<"借书日期"<<"\t"<<"应还日期"<<endl;
	ShowLoan();
}
void CLoan::AddCLoan(CLoan Loan)							//增加结点
{
	CLoan *p=new CLoan(Loan);
	if(m_loanListTail==NULL)
	{	
		m_loanListTail=p;
		if(m_loanListHead==NULL)
			m_loanListHead=p;
	}
	else
	{	
		m_loanListTail->m_nextLoan=p;
		m_loanListTail=p;
	}
}
void CLoan::DeleteCLoan(int loanID)							//删除结点		
{
	CLoan* pLoan=m_loanListHead;
	CLoan* proLoan=NULL;
	while(pLoan!=NULL)
	{    
		if(pLoan->m_loanID==loanID)
    		{
        		if(pLoan==m_loanListHead)
       			{   	
					m_loanListHead=pLoan->m_nextLoan;
           			if(pLoan==m_loanListTail)
               			m_loanListTail=NULL;
       			 }
				else if(pLoan==m_loanListTail)
    			{   	
					m_loanListTail=proLoan;
        			proLoan->m_nextLoan=NULL;
   				}
    			else
   				{	
					proLoan->m_nextLoan=pLoan->m_nextLoan;
				}
   				delete pLoan;
    			break;
		}
		proLoan=pLoan;
		pLoan=pLoan->m_nextLoan;
	}
}
CLoan* CLoan::FindCLoan(int loanID)							//查找节点	
{
	CLoan* pLoan=m_loanListHead;
	while(pLoan!=NULL)
	{
		if(pLoan->m_loanID==loanID)
			return pLoan;
		pLoan=pLoan->m_nextLoan;
	}
	return NULL;
}

/*******************************         CReservation       **************************/
CReservation* CReservation::m_reservationListHead=NULL;
CReservation* CReservation::m_reservationListTail=NULL;


CReservation::CReservation(int titleID,int borrowerID)
{
	N5++;
	m_reservationID=N5;
	m_titleID=titleID;
	m_borrowerID=borrowerID;
	m_nextReservation=NULL;
}
CReservation::CReservation(){}
int CReservation::AddReservation()									//增加预订
{
	int m=0;
	string name1,name2,key;
	cout<<"请输入书名(输入#退出)"<<endl;
	cin>>name1;
	system("cls");
	if(name1=="#")
		return 0;
	CTitle *p1=NULL;
	CBorrower *p2=NULL;
	p1=p1->FindCTitle(name1);
	while(p1==NULL)
	{
		cout<<"无该书，请重新输入"<<endl;
		cin>>name1;
		system("cls");
		p1=p1->FindCTitle(name1);
		if(name1=="#")
			return 0;
	}
	cout<<"请输入您的姓名,密码(只有3次输入机会)"<<endl;
	cin>>name2;
	if(name1=="#")
		return 0;
	cin>>key;
	system("cls");
	p2=p2->FindCBorrower(name2);
	while(1)
	{
		if(p2==NULL||(p2!=NULL&&p2->m_key!=key))
		{
			m++;
			if(m==3)
			return 0;
			cout<<"信息有误,请重新输入(还有"<<3-m<<"次机会,输入#退出)"<<endl;
			cin>>name2;
			if(name2=="#")
				return 0;
			else
			{
				cin>>key;
				p2=p2->FindCBorrower(name2);
			}
			system("cls");
		}
		else
			break;
	}
	if(p2->countfine()>0)
	{
		cout<<"您有罚金需缴纳,暂时失去预定权限\n1.现在缴纳\n2.等下缴纳(退出)\n";
		cin>>m;
		if(m==1)
		{
			system("cls");
			p2->givefine();
		}
		else
			return 0;
	}
	system("cls");
	CReservation q(p1->m_titleID,p2->m_borrowerID);
	AddCReservation(q);
	q.GetReservation();
	p1->AddReservation(q.m_reservationID);
	p2->AddReservation(q.m_reservationID);
	cout<<"添加成功"<<endl;
	return 1;
}
int CReservation::DeleteReservation()  								//主动删除预订
{
	int reservationID;
	cout<<"请输入预定编号(输入0退出)"<<endl;
	CReservation *p=NULL;
	CTitle *p1=NULL;
	CBorrower *p2=NULL;
	cin>>reservationID;
	system("cls");
	if(reservationID==0)
			return 0;
	p=p->FindCReservation(reservationID);
	while(p==NULL)
	{
		cout<<"无该预定编号，请重新输入"<<endl;
		cin>>reservationID;
		system("cls");
		p=p->FindCReservation(reservationID);
		if(reservationID==0)
				return 0;
	}
	p1=p1->FindCTitle(p->m_titleID);
	p2=p2->FindCBorrower(p->m_borrowerID);
	p1->DeleteReservation(reservationID);
	p2->DeleteReservation(reservationID);
	p->DeleteCReservation(reservationID);
	cout<<"删除成功"<<endl;
	return 1;
}
void CReservation::DeleteReservation(int reservationID)  			//自动删除预订
{
	CReservation *p=NULL;
	CBorrower *p2=NULL;
	p=p->FindCReservation(reservationID);
	p2=p2->FindCBorrower(p->m_borrowerID);
	p2->DeleteReservation(reservationID);
	p->DeleteCReservation(reservationID);
}
void CReservation::LookReservation()
{
	CReservation* pReservation=m_reservationListHead;
	if(pReservation!=NULL)
	{
		cout<<"预定编号"<<'\t'<<"标题编号"<<'\t'<<"书名"<<'\t'<<"借书者编号"<<'\t'<<"借书者姓名"<<endl;
		while(pReservation!=NULL)
		{
			pReservation->ShowReservation();
			pReservation=pReservation->m_nextReservation;
		}
	}
	else
		cout<<"没有信息"<<endl;
}
void CReservation::ShowReservation()								//显示某次预定信息
{
	CTitle *p1=NULL;
	CBorrower *p2=NULL;
	p1=p1->FindCTitle(m_titleID);
	p2=p2->FindCBorrower(m_borrowerID);
	cout<<m_reservationID<<"\t\t"<<m_titleID<<"\t\t"<<p1->m_name<<"\t"<<m_borrowerID<<"\t\t"<<p2->m_name<<endl;
}
void CReservation::GetReservation()
{
	cout<<"预定编号"<<'\t'<<"标题编号"<<'\t'<<"书名"<<'\t'<<"借书者编号"<<'\t'<<"借书者姓名"<<endl;
	ShowReservation();
}
void CReservation::AddCReservation(CReservation Reservation)		 //增加结点
{
	CReservation *p=new CReservation(Reservation);
	if(m_reservationListTail==NULL)
	{	
		m_reservationListTail=p;
		if(m_reservationListHead==NULL)
			m_reservationListHead=p;
	}
	else
	{	
		m_reservationListTail->m_nextReservation=p;
		m_reservationListTail=p;
	}
}
void CReservation::DeleteCReservation(int reservationID)			//删除结点		
{
	CReservation* pReservation=m_reservationListHead;
	CReservation* proReservation=NULL;
	while(pReservation!=NULL)
	{    
		if(pReservation->m_reservationID==reservationID)
    		{
        		if(pReservation==m_reservationListHead)
       			{   	
					m_reservationListHead=pReservation->m_nextReservation;
           			if(pReservation==m_reservationListTail)
               			m_reservationListTail=NULL;
       			 }
				else if(pReservation==m_reservationListTail)
    			{   	
					m_reservationListTail=proReservation;
        			proReservation->m_nextReservation=NULL;
   				}
    			else
   				{	
					proReservation->m_nextReservation=pReservation->m_nextReservation;
				}
   				delete pReservation;
    			break;
		}
		proReservation=pReservation;
		pReservation=pReservation->m_nextReservation;
	}
}
CReservation* CReservation::FindCReservation(int reservationID)			//查找节点	
{
	CReservation* pReservation=m_reservationListHead;
	while(pReservation!=NULL)
	{
		if(pReservation->m_reservationID==reservationID)
			return pReservation;
		pReservation=pReservation->m_nextReservation;
	}
	return NULL;
}
/****************************************外部函数*************************************/


int changekey()
{
	string key1,key2;
	int m=0;
	cout<<"请输入原密码(有3次输入机会,输入#退出)"<<endl;
	cin>>key1;
	system("cls");
	if(key1=="#")
			return 0;
	while(key!=key1)
	{
		m++;
		if(m==3)
			return 0;
		cout<<"密码不正确,请重新输入(还有"<<3-m<<"次机会)"<<endl;
		cin>>key1;
		system("cls");
		if(key1=="#")
			return 0;
	}
	cout<<"请输入新密码"<<endl;
	cin>>key1;
	system("cls");
	cout<<"请再次输入密码"<<endl;
	cin>>key2;
	system("cls");
	while(key1!=key2)
	{
		cout<<"两次输入的密码不一致，请重新输入"<<endl;
		cin>>key1>>key2;
		system("cls");
	}
	key=key1;
	cout<<"修改成功,请记好您的密码"<<endl;
	return 1;
}
int guanliyuan()
{
	system("cls");
	string key1;
	int m=0;
	cout<<"请输入密码(有3次输入机会,输入#退出)"<<endl;
	cin>>key1;
	system("cls");
	if(key1=="#")
			return 0;
	while(key!=key1)
	{
		m++;
		if(m==3)
			return 0;
		cout<<"密码不正确,请重新输入(还有"<<3-m<<"次机会,输入#退出)"<<endl;
		cin>>key1;
		system("cls");
		if(key1=="#")
			return 0;
	}
	while(1)
	{
		cout<<"请选择功能:\n1.书籍管理\n2.信息查询\n3.修改密码\n4.返回首页\n";
		cin>>m;
		system("cls");
		switch(m)
		{
		case 1:system("color 09");g1();
			break;
		case 2:system("color 0A");g2();
			break;
		case 3:read6();
			system("color 0B");
			changekey();
			write6();
			break;
		case 4:return 0;
		default:break;
		}
		system("pause");
		system("cls");
	}
}
int g1()
{
	system("cls");
	int m;
	while(1)
	{
		system("cls");
		read1();
		read2();
		read3();
		read4();
		read5();
		cout<<"1.添加标题\n2.删除标题\n3.添加书目\n4.删除书目\n5.返回\n";
		cin>>m;
		system("cls");
		switch(m)
		{
		case 1:system("color 09");Title.AddTitle();
			break;
		case 2:system("color 0A");Title.DeleteTitle();
			break;
		case 3:system("color 0B");Item.AddItem(); 
			break;
		case 4:system("color 0C");Item.DeleteItem(); 
			break;
		case 5:return 0;
		default:break;
		}
		write1();
		write2();
		write3();
		write4();
		write5();
		system("pause");
		system("cls");
	}
}
int g2()
{
	read1();
	read2();
	read3();
	read4();
	read5();
	system("cls");
	int m;
	while(1)
	{
		cout<<"1.查看全部书籍\n2.查看全部书目\n3.查看全部借书人\n4.查看全部借书信息\n5.查看全部预定信息\n6.查看某书籍书目信息\n7.查看某书籍借阅信息\n8.查看某借书人信息\n9.查看某书目信息\n0.返回\n";
		cin>>m;
		system("cls");
		switch(m)
		{
		case 1:system("color 09");Title.LookTitle();
			break;
		case 2:system("color 0A");Item.LookItem(); 
			break;
		case 3:system("color 0E");Borrower.LookBorrower();
			break;
		case 4:system("color 0B");Loan.LookLoan(); 
			break;
		case 5:system("color 0C");Reservation.LookReservation(); 
			break;
		case 6:system("color 0D");Title.FindTitle(); 
			break;
		case 7:system("color 0E");Title.LookaTitle(); 
			break;
		case 8:system("color 0A");Borrower.FindBorrower(); 
			break;
		case 9:system("color 0B");Item.FindItem(); 
			break;
		case 0:return 0;
		default:break;
		}
		system("pause");
		system("cls");
	}
}
int jieshuzhe()
{
	system("cls");
	int m;
	while(1)
	{
		cout<<"1.账号管理\n2.图书借阅\n3.返回首页\n";
		cin>>m;
		system("cls");
		switch(m)
		{
		case 1:system("color 0B");j1();
			break;
		case 2:system("color 0C");j2();
			break;
		case 3:return 0;
		default:break;
		}
		system("pause");
		system("cls");
	}
}
int j1()
{
	system("cls");
	int m;
	while(1)
	{
		read1();
		read2();
		read3();
		read4();
		read5();
		cout<<"1.注册账号\n2.注销账号\n3.账号信息\n4.修改密码\n5.缴纳罚金\n6.返回\n";
		cin>>m;
		system("cls");
		switch(m)
		{
		case 1:system("color 09");Borrower.AddBorrower();
			break;
		case 2:system("color 0A");Borrower.DeleteBorrower();
			break;
		case 3:system("color 0B");Borrower.Show(); 
			break;
		case 4:system("color 0C");Borrower.changekey(); 
			break;
		case 5:system("color 0D");Borrower.Givefine(); 
			break;
		case 6:return 0;
		default:break;
		}
		write1();
		write2();
		write3();
		write4();
		write5();
		system("pause");
		system("cls");
	}
}
int j2()
{
	system("cls");
	int m;
	while(1)
	{
		read1();
		read2();
		read3();
		read4();
		read5();
		cout<<"1.查看全部书籍\n2.查找书籍\n3.借书\n4.还书\n5.预定书籍\n6.取消预定\n7.返回\n";
		cin>>m;
		system("cls");
		switch(m)
		{
		case 1:system("color 09");Title.LookTitle();
			break;
		case 2:system("color 0A");Title.FindTitle();
			break;
		case 3:system("color 0B");Loan.AddLoan(); 
			break;
		case 4:system("color 0C");Loan.DeleteLoan(); 
			break;
		case 5:system("color 0D");Reservation.AddReservation(); 
			break;
		case 6:system("color 0E");Reservation.DeleteReservation(); 
			break;
		case 7:return 0;
		default:break;
		}
		write1();
		write2();
		write3();
		write4();
		write5();
		system("pause");
		system("cls");
	}
}
void read1()
{
	file1.open("f1.txt",ios::in);
	if(!file1)
	{
		cout<<"f1.txt can't open. "<<endl;
		abort();
	}
	CTitle *p=Title.m_titleListHead;
	file1.seekg(0);
	while(1)
	{
		file1.read((char *)&Title,sizeof(CTitle));
		if(Title.m_itemNum>0)
			file1.read((char *)Title.m_itemList,sizeof(int)*Title.m_itemNum);
		if(Title.m_reservationNum>0)
			file1.read((char *)Title.m_reservationList,sizeof(int)*Title.m_reservationNum);
		 if(file1.eof())
	       break;
		*p=Title;
		p=p->m_nextTitle;
	}
	file1.close();
}
void read2()
{
	file2.open("f2.txt",ios::in);
	if(!file2)
	{
		cout<<"f2.txt can't open. "<<endl;
		abort();
	}
	CItem *p=Item.m_itemListHead;
	file2.seekg(0);
	while(1)
	{
		file2.read((char *)&Item,sizeof(CItem));
		if(file2.eof())
	       break;
		*p=Item;
		p=p->m_nextItem;
	}
	file2.close();
}
void read3()
{
	file3.open("f3.txt",ios::in);
	if(!file3)
	{
		cout<<"f3.txt can't open. "<<endl;
		abort();
	}
	CBorrower *p=Borrower.m_borrowerListHead;
	file3.seekg(0);
	while(1)
	{
		file3.read((char *)&Borrower,sizeof(CBorrower));
		if(Borrower.m_loanNum>0)
			file3.read((char *)Borrower.m_loanList,sizeof(int)*Borrower.m_loanNum);
		if(Borrower.m_reservationNum>0)
			file3.read((char *)Borrower.m_reservationList,sizeof(int)*Borrower.m_reservationNum);
		if(file3.eof())
	       break;
		*p=Borrower;
		p=p->m_nextborrower;
	}
	file3.close();
}
void read4()
{
	file4.open("f4.txt",ios::in);
	if(!file4)
	{
		cout<<"f4.txt can't open. "<<endl;
		abort();
	}
	CLoan *p=Loan.m_loanListHead;
	file4.seekg(0);
	while(1)
	{
		file4.read((char *)&Loan,sizeof(CLoan));
		if(file4.eof())
	       break;
		*p=Loan;
		p=p->m_nextLoan;
	}
	file4.close();
}
void read5()
{
	file5.open("f5.txt",ios::in);
	if(!file5)
	{
		cout<<"f5.txt can't open. "<<endl;
		abort();
	}
	CReservation *p=Reservation.m_reservationListHead;
	file5.seekg(0);
	while(1)
	{
		file5.read((char *)&Reservation,sizeof(CReservation));
		if(file5.eof())
	       break;
		*p=Reservation;
		p=p->m_nextReservation;
	}
	file5.close();
}
void read6()
{
	file6.open("f6.txt",ios::in);
	if(!file6)
	{
		cout<<"f6.txt can't open. "<<endl;
		abort();
	}
	file6.seekg(0);
	file6.read((char *)&key,sizeof(string));
	file6.close();
}
void write1()
{
	file1.open("f1.txt",ios::out|ios::in);
	if(!file1)
	{
		cout<<"f1.txt can't open. "<<endl;
		abort();
	}
	CTitle *p=Title.m_titleListHead;
	while(p!=NULL)
	{
		file1.write((char *)p,sizeof(CTitle));
		if(p->m_itemNum>0)
			file1.write((char *)p->m_itemList,sizeof(int)*p->m_itemNum);
		if(p->m_reservationNum>0)
			file1.write((char *)p->m_reservationList,sizeof(int)*p->m_reservationNum);
		p=p->m_nextTitle;
	}
	file1.close();
}
void write2()
{
	file2.open("f2.txt",ios::out);
	if(!file2)
	{
		cout<<"f2.txt can't open. "<<endl;
		abort();
	}
	CItem *p=Item.m_itemListHead;
	while(p!=NULL)
	{
		file2.write((char *)p,sizeof(CItem));
		p=p->m_nextItem;
	}
	file2.close();
}
void write3()
{
	file3.open("f3.txt",ios::out);
	if(!file3)
	{
		cout<<"f3.txt can't open. "<<endl;
		abort();
	}
	CBorrower *p=Borrower.m_borrowerListHead;
	while(p!=NULL)
	{
		file3.write((char *)p,sizeof(CBorrower));
		if(p->m_loanNum>0)
			file3.write((char *)p->m_loanList,sizeof(int)*p->m_loanNum);
		if(p->m_reservationNum>0)
			file3.write((char *)p->m_reservationList,sizeof(int)*p->m_reservationNum);
		p=p->m_nextborrower;
	}
	file3.close();
}
void write4()
{
	file4.open("f4.txt",ios::out);
	if(!file4)
	{
		cout<<"f4.txt can't open. "<<endl;
		abort();
	}
	CLoan *p=Loan.m_loanListHead;
	while(p!=NULL)
	{
		file4.write((char *)p,sizeof(CLoan));
		p=p->m_nextLoan;
	}
	file4.close();
}
void write5()
{
	file5.open("f5.txt",ios::out);
	if(!file5)
	{
		cout<<"f5.txt can't open. "<<endl;
		abort();
	}
	CReservation *p=Reservation.m_reservationListHead;
	while(p!=NULL)
	{
		file5.write((char *)p,sizeof(CReservation));
		p=p->m_nextReservation;
	}
	file5.close();
}
void write6()
{
	file6.open("f6.txt",ios::out);
	if(!file6)
	{
		cout<<"f6.txt can't open. "<<endl;
		abort();
	}
	file6.write((char *)&key,sizeof(string));
	file6.close();
}
void getn1()					//获得初始值
{
	file1.open("f1.txt",ios::out|ios::in|ios::app);
	if(!file1)
	{
		cout<<"f1.txt can't open. "<<endl;
		abort();
	}
	file1.seekg(0);
	while(1)
	{
		file1.read((char *)&Title,sizeof(CTitle));
		Title.m_itemList=new int[Title.m_itemNum];
		Title.m_reservationList=new int[Title.m_reservationNum];
		if(Title.m_itemNum>0)
			file1.read((char *)Title.m_itemList,sizeof(int)*Title.m_itemNum);
		if(Title.m_reservationNum>0)
			file1.read((char *)Title.m_reservationList,sizeof(int)*Title.m_reservationNum);
	    if(file1.eof())
	       break;
		CTitle *p=new CTitle(Title);
		if(CTitle::m_titleListHead==NULL)
			CTitle::m_titleListHead=p;
		if(CTitle::m_titleListTail!=NULL)
			CTitle::m_titleListTail->m_nextTitle=p;
		CTitle::m_titleListTail=p;
	}
	file1.close();
}
void getn2()
{
	file2.open("f2.txt",ios::out|ios::in|ios::app);
	if(!file2)
	{
		cout<<"f2.txt can't open. "<<endl;
		abort();
	}
	file2.seekg(0);
	while(1)
	{
		file2.read((char *)&Item,sizeof(CItem));
	    if(file2.eof())
	       break;
		CItem *p=new CItem(Item);
		if(CItem::m_itemListHead==NULL)
			CItem::m_itemListHead=p;
		if(CItem::m_itemListTail!=NULL)
			CItem::m_itemListTail->m_nextItem=p;
		CItem::m_itemListTail=p;
	}
	file2.close();
}
void getn3()
{
	file3.open("f3.txt",ios::out|ios::in|ios::app);
	if(!file3)
	{
		cout<<"f3.txt can't open. "<<endl;
		abort();
	}
	file3.seekg(0);
	while(1)
	{
		file3.read((char *)&Borrower,sizeof(CBorrower));
		Borrower.m_loanList=new int[Borrower.m_loanNum];
		Borrower.m_reservationList=new int[Borrower.m_reservationNum];
		if(Borrower.m_loanNum>0)
			file3.read((char *)Borrower.m_loanList,sizeof(int)*Borrower.m_loanNum);
		if(Borrower.m_reservationNum>0)
			file3.read((char *)Borrower.m_reservationList,sizeof(int)*Borrower.m_reservationNum);
		if(file3.eof())
	       break;
		CBorrower *p=new CBorrower(Borrower);
		if(CBorrower::m_borrowerListHead==NULL)
			CBorrower::m_borrowerListHead=p;
		if(CBorrower::m_borrowerListTail!=NULL)
			CBorrower::m_borrowerListTail->m_nextborrower=p;
		CBorrower::m_borrowerListTail=p;
	}
	file3.close();
}
void getn4()
{
	file4.open("f4.txt",ios::out|ios::in|ios::app);
	if(!file4)
	{
		cout<<"f4.txt can't open. "<<endl;
		abort();
	}
	file4.seekg(0);
	while(1)
	{
		file4.read((char *)&Loan,sizeof(CLoan));
	    if(file4.eof())
	       break;
		CLoan *p=new CLoan(Loan);
		if(CLoan::m_loanListHead==NULL)
			CLoan::m_loanListHead=p;
		if(CLoan::m_loanListTail!=NULL)
			CLoan::m_loanListTail->m_nextLoan=p;
		CLoan::m_loanListTail=p;
	}
	file4.close();
}
void getn5()
{
	file5.open("f5.txt",ios::out|ios::in|ios::app);
	if(!file5)
	{
		cout<<"f5.txt can't open. "<<endl;
		abort();
	}
	file5.seekg(0);
	while(1)
	{
		file5.read((char *)&Reservation,sizeof(CReservation));
	    if(file5.eof())
	       break;
		CReservation *p=new CReservation(Reservation);
		if(CReservation::m_reservationListHead==NULL)
			CReservation::m_reservationListHead=p;
		if(CReservation::m_reservationListTail!=NULL)
			CReservation::m_reservationListTail->m_nextReservation=p;
		CReservation::m_reservationListTail=p;
	}
	file5.close();
}
void getn6()
{
	file6.open("f6.txt",ios::out|ios::in|ios::app);
	if(!file6)
	{
		cout<<"f6.txt can't open. "<<endl;
		abort();
	}
	file6.seekg(0);
	file6.read((char *)&key,sizeof(string));
	file6.close();
}
void getn()
{
	getn1();
	getn2();
	getn3();
	getn4();
	getn5();
	getn6();
	write1();
	write2();
	write3();
	write4();
	write5();
}
void clear()
{
	file1.open("f1.txt",ios::out);
	file1.close();
	file2.open("f2.txt",ios::out);
	file2.close();
	file3.open("f3.txt",ios::out);
	file3.close();
	file4.open("f4.txt",ios::out);
	file4.close();
	file5.open("f5.txt",ios::out);
	file5.close();
	file6.open("f6.txt",ios::out);
	file6.close();
}