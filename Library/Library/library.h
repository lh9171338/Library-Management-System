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
	date gettime();												//��ȡ��ǰʱ��
	date addaday();												//��һ��
	date addday(unsigned int n);								//��n��
	int countday();												//���㳬�˶�����
	friend ostream &operator<<(ostream &cout, date &d);
};
class CTitle{
private:
	string m_author;											//����
	int m_type;													//�黹����־
public:
	int m_titleID;												//������
	string m_name;												//����
	int* m_itemList;											//��̬��������Ŀ�������
	int m_itemNum;												//�������Ŀ����
	int m_itemMax;												//��Ŀ��������Ԫ�ظ���
	int* m_reservationList;										//��̬ԤԼ�������
	int m_reservationNum;										//ԤԼ����
	int m_reservationMax;										//ԤԼ��������Ԫ�ظ���
	CTitle* m_nextTitle;										//ָ����һ��CTitle�����ָ��
 	static CTitle* m_titleListHead;								//�����ͷ���ָ��
	static CTitle* m_titleListTail;								//�����β���ָ��

	CTitle(string,string,int);									//���캯��1
	CTitle();
	int AddTitle();												//���ӱ���
	int DeleteTitle();											//ɾ������
	static void LookTitle();									//�鿴���б���
	void FindTitle();											//�鿴ĳ���Ⲣ��ʾ������Ŀ
	void GetTitle();
	void ShowTitle();											//��ʾ�ñ�����Ϣ
	void LookaTitle();											//�鿴ĳ���������Ϣ
	
	void AddItem(int itemID);									//���Ӹñ����µ���Ŀ
    void DeleteItem(int itemID);								//ɾ���ñ����µ�ָ����Ŀ

    void AddReservation(int reservationID);						//���ӶԸñ����һ��Ԥ��
    void DeleteReservation(int reservationID);					//ɾ���ñ����ָ��Ԥ��

	static void AddCTitle(CTitle title);						//���ӽ��
	static void DeleteCTitle(string name);						//ɾ�����
	static CTitle* FindCTitle(string name);						//���ҽڵ�
	static CTitle* FindCTitle(int titleID);						//���ҽڵ�
	
};
class CItem{
public:
	int m_titleID;												//������
	int m_itemID;												//��Ŀ���
	int m_loanID;												//����״̬
	CItem* m_nextItem;											//ָ����һ��CItem�����ָ��
	static CItem* m_itemListHead;								//�����ͷ���ָ��
	static CItem* m_itemListTail;								//�����β���ָ��

	CItem(int titleID,int itemID);
	CItem();
	int AddItem();												//�����Ŀ
	int DeleteItem();											//ɾ����Ŀ
	static void LookItem();
	void FindItem();											//������Ŀ
	void SetLoan(int loanID);									//��ʾ����Ŀ������
	void GetItem();
	void ShowItem();											//��ʾ��Ŀ��Ϣ
    void IsBorrowed();											//���ظ���Ŀ�Ƿ񱻳������Ϣ
	static void AddCItem(CItem item);							//���ӽ��
	static void DeleteCItem(int itemID);						//ɾ�����
	static CItem* FindCItem(int itemID);						//���ҽڵ�
};

class CBorrower{
private:
	string m_sex;
	string m_address;
	string m_city;
public:
	string m_name;
	int m_borrowerID;											//�����߱��
	string m_key;												//����
	int* m_loanList;											//��̬����������
	int m_loanNum;												//�������Ŀ����
	float m_fine;												//δ���鷣��
	float m_fine1;												//�ѻ��鷣��
	int* m_reservationList;										//��̬ԤԼ�������
	int m_reservationNum;										//ԤԼ����
	CBorrower* m_nextborrower;									//ָ����һ��CBorrower�����ָ��
 	static CBorrower* m_borrowerListHead;						//�����ͷ���ָ��
	static CBorrower* m_borrowerListTail;						//�����β���ָ��

	CBorrower(string,string,string,string,string);
	CBorrower();
	int AddBorrower();
	int DeleteBorrower();
	static void LookBorrower();
	void ShowBorrower();										//��ʾ�ý�������Ϣ
	void FindBorrower();
	int Show();													//��ʾ�Լ�����Ϣ
	int changekey();											//�޸�����
	float countfine();											//���㷣��
	void givefine();											//���ɷ���
	int Givefine();												//���ɷ���
	void AddLoan(int loanID);									//����������Ŀ
    void DeleteLoan(int loanID);								//ɾ��������Ŀ
	void AddReservation(int reservationID);						//����Ԥ��
    void DeleteReservation(int reservationID);					//ɾ��Ԥ��
	
	static void AddCBorrower(CBorrower borrower);				//���ӽ��
	static void DeleteCBorrower(string m_name);					//ɾ�����
	static CBorrower* FindCBorrower(int borrowerID);			//���ҽڵ�
	static CBorrower* FindCBorrower(string name);				//���ҽڵ�
};

class CLoan{
public:
	date m_timeLoan;											//��������
	date m_timeExpire;											//����ʱ��
	int m_itemID;												//������Ŀ���
	int m_loanID;												//�������
	int m_borrowerID;											//�����߱��
	CLoan* m_nextLoan;											//ָ����һ��CLoan�����ָ��
 	static CLoan* m_loanListHead;								//�����ͷ���ָ��
	static CLoan* m_loanListTail;								//�����β���ָ��

	CLoan(int itemID,int borrowerID);
	CLoan();
	int AddLoan();												//���ӽ�����Ϊ
    void DeleteLoan();											//ɾ��������Ϊ
	static void LookLoan();
	void ShowLoan();											//��ʾĳ�ν�����Ϣ
	void GetLoan();

	static void AddCLoan(CLoan Loan);							//���ӽ��
	static void DeleteCLoan(int loanID);						//ɾ�����
	static CLoan* FindCLoan(int loanID);						//���ҽڵ�
};

class CReservation{
public:
	int m_reservationID;
	int m_titleID;												//��Ԥ��������
	int m_borrowerID;											//�����߱��
	CReservation* m_nextReservation;							//ָ����һ��CReservation�����ָ��
 	static CReservation* m_reservationListHead;					//�����ͷ���ָ��
	static CReservation* m_reservationListTail;					//�����β���ָ��

	CReservation(int titleID,int borrowerID);
	CReservation();
	int AddReservation();										//����Ԥ��
    int DeleteReservation();									//����ɾ��Ԥ��
	void DeleteReservation(int reservationID);					//�Զ�ɾ��Ԥ��
	static void LookReservation();
	void ShowReservation();										//��ʾĳ��Ԥ����Ϣ
	void GetReservation();

	static void AddCReservation(CReservation Reservation);		//���ӽ��
	static void DeleteCReservation(int reservationID);			//ɾ�����
	static CReservation* FindCReservation(int reservationID);	//���ҽڵ�
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