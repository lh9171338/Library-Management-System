#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>
#include<cstdlib>
#include<string.h>
#include<time.h>
#include<iomanip> 
using namespace std;

class date{
public:
	int m_year,m_month,m_day;
	date(int,int,int);
	date();
	date gettime();												//获取当前时间
	date addaday();												//加一天
	date addday(unsigned int n);								//加n天
	int countday();												//计算超了多少天
	friend ostream &operator<<(ostream &cout, date &d);
};
class CTitle{
private:
	string m_author;											//作者
	int m_type;													//书还是杂志
public:
	int m_titleID;												//标题编号
	string m_name;												//书名
	int* m_itemList;											//动态创建的书目编号数组
	int m_itemNum;												//标题的书目数量
	int m_itemMax;												//书目编号数组的元素个数
	int* m_reservationList;										//动态预约编号数组
	int m_reservationNum;										//预约数量
	int m_reservationMax;										//预约编号数组的元素个数
	CTitle* m_nextTitle;										//指向下一个CTitle对象的指针
 	static CTitle* m_titleListHead;								//链表的头结点指针
	static CTitle* m_titleListTail;								//链表的尾结点指针

	CTitle(string,string,int);									//构造函数1
	CTitle();
	int AddTitle();												//增加标题
	int DeleteTitle();											//删除标题
	static void LookTitle();									//查看所有标题
	void FindTitle();											//查看某标题并显示所含书目
	void GetTitle();
	void ShowTitle();											//显示该标题信息
	void LookaTitle();											//查看某标题借阅信息
	
	void AddItem(int itemID);									//增加该标题下的书目
    void DeleteItem(int itemID);								//删除该标题下的指定书目

    void AddReservation(int reservationID);						//增加对该标题的一次预订
    void DeleteReservation(int reservationID);					//删除该标题的指定预订

	static void AddCTitle(CTitle title);						//增加结点
	static void DeleteCTitle(string name);						//删除结点
	static CTitle* FindCTitle(string name);						//查找节点
	static CTitle* FindCTitle(int titleID);						//查找节点
	
};
class CItem{
public:
	int m_titleID;												//标题编号
	int m_itemID;												//书目编号
	int m_loanID;												//借书状态
	CItem* m_nextItem;											//指向下一个CItem对象的指针
	static CItem* m_itemListHead;								//链表的头结点指针
	static CItem* m_itemListTail;								//链表的尾结点指针

	CItem(int titleID,int itemID);
	CItem();
	int AddItem();												//添加书目
	int DeleteItem();											//删除书目
	static void LookItem();
	void FindItem();											//查找书目
	void SetLoan(int loanID);									//表示该书目被出借
	void GetItem();
	void ShowItem();											//显示书目信息
    void IsBorrowed();											//返回该书目是否被出借的信息
	static void AddCItem(CItem item);							//增加结点
	static void DeleteCItem(int itemID);						//删除结点
	static CItem* FindCItem(int itemID);						//查找节点
};

class CBorrower{
private:
	string m_sex;
	string m_address;
	string m_city;
public:
	string m_name;
	int m_borrowerID;											//借书者编号
	string m_key;												//密码
	int* m_loanList;											//动态借书编号数组
	int m_loanNum;												//所借的书目数量
	float m_fine;												//未还书罚金
	float m_fine1;												//已还书罚金
	int* m_reservationList;										//动态预约编号数组
	int m_reservationNum;										//预约数量
	CBorrower* m_nextborrower;									//指向下一个CBorrower对象的指针
 	static CBorrower* m_borrowerListHead;						//链表的头结点指针
	static CBorrower* m_borrowerListTail;						//链表的尾结点指针

	CBorrower(string,string,string,string,string);
	CBorrower();
	int AddBorrower();
	int DeleteBorrower();
	static void LookBorrower();
	void ShowBorrower();										//显示该借书者信息
	void FindBorrower();
	int Show();													//显示自己的信息
	int changekey();											//修改密码
	float countfine();											//计算罚金
	void givefine();											//缴纳罚金
	int Givefine();												//缴纳罚金
	void AddLoan(int loanID);									//增加所借书目
    void DeleteLoan(int loanID);								//删除所借书目
	void AddReservation(int reservationID);						//增加预订
    void DeleteReservation(int reservationID);					//删除预订
	
	static void AddCBorrower(CBorrower borrower);				//增加结点
	static void DeleteCBorrower(string m_name);					//删除结点
	static CBorrower* FindCBorrower(int borrowerID);			//查找节点
	static CBorrower* FindCBorrower(string name);				//查找节点
};

class CLoan{
public:
	date m_timeLoan;											//出借日期
	date m_timeExpire;											//到期时间
	int m_itemID;												//所借书目编号
	int m_loanID;												//借书序号
	int m_borrowerID;											//借书者编号
	CLoan* m_nextLoan;											//指向下一个CLoan对象的指针
 	static CLoan* m_loanListHead;								//链表的头结点指针
	static CLoan* m_loanListTail;								//链表的尾结点指针

	CLoan(int itemID,int borrowerID);
	CLoan();
	int AddLoan();												//增加借书行为
    void DeleteLoan();											//删除借书行为
	static void LookLoan();
	void ShowLoan();											//显示某次借书信息
	void GetLoan();

	static void AddCLoan(CLoan Loan);							//增加结点
	static void DeleteCLoan(int loanID);						//删除结点
	static CLoan* FindCLoan(int loanID);						//查找节点
};

class CReservation{
public:
	int m_reservationID;
	int m_titleID;												//所预定标题编号
	int m_borrowerID;											//借书者编号
	CReservation* m_nextReservation;							//指向下一个CReservation对象的指针
 	static CReservation* m_reservationListHead;					//链表的头结点指针
	static CReservation* m_reservationListTail;					//链表的尾结点指针

	CReservation(int titleID,int borrowerID);
	CReservation();
	int AddReservation();										//增加预订
    int DeleteReservation();									//主动删除预订
	void DeleteReservation(int reservationID);					//自动删除预订
	static void LookReservation();
	void ShowReservation();										//显示某次预定信息
	void GetReservation();

	static void AddCReservation(CReservation Reservation);		//增加结点
	static void DeleteCReservation(int reservationID);			//删除结点
	static CReservation* FindCReservation(int reservationID);	//查找节点
};

int guanliyuan();
int jieshuzhe();
void read1();
void read2();
void read3();		
void read4();
void read5();
void read6();
void write1();
void write2();
void write3();
void write4();
void write5();
void write6();
void getn1();
void getn2();
void getn3();
void getn4();
void getn5();
void getn6();
void getn();
void clear();

#endif