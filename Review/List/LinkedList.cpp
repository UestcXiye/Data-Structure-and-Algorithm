#include<iostream>
#include<time.h>
#include<stdlib.h>

using namespace std;

#define OK          1
#define ERROR       0
#define OVERFLOW   -1
#define N           5
typedef int ElemType;
typedef int Status;
typedef struct LNode
{
	ElemType data;
	LNode *next;
}LNode, *LinkList;

//InitList(*L) : 初始化操作，建立一个空的线性表L。
Status InitList(LinkList &L)
{
	L= (LNode *)malloc(sizeof(LNode));//生成一个新的头结点，用头指针L指向头结点
	L->next = NULL;  //头结点的指针域指向NULL
	return OK;
}
//CreateListHead(LinkList L, int n)采用头插法建立单链表
void CreateListHead(LinkList &L, int n)
{
	LNode *p;//创建结点
	int i;
	srand(time(0));   // 初始化随机数种子
	for (int i = 0; i < n; i++)
	{
		p =(LinkList)malloc(sizeof(LNode));  //生成新结点
		p->data= rand() % 100 + 1;
		p->next = L->next;
		L->next = p;
	}
}
//void CreateListTail(LinkList L, int n)采用尾插法建立单链表
void CreateListTail(LinkList &L, int n)
{
	LNode *p,*r;
	int i;
	srand(time(0));
	r = L;
	for (int i = 0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(LNode));  //生成新结点
		p->data = rand() % 100 + 1;
		r->next = p;
		r = p;
	}
	r->next = NULL;
}
//按序号查找结点值
Status GetElem(LinkList L, int i, ElemType *e)
{
	int j=1;
	LNode *p;
	p = L->next;
	while (p && j < i)
	{
		p = p->next;
		++j;
	}

	if (!p || j > i)
	{
		return ERROR;
	}

	*e = p->data;

	return OK;
}
//按值查找表结点
int LocateElem(LinkList L, ElemType e)
{
	LNode *p = L->next;
	int i = 1;
	while (p)
	{
		if (p->data == e)
		{
			return i;
		}
		p = p->next;
		i++;
	}
	return 0;
}

//插入结点操作
Status ListInsert(LinkList &L, int i, ElemType e)
{
	LinkList P;
	LNode *s;
	int j = 1;
	P= L;
	while (P&&j < i)
	{
		P = P->next;
		j++;
	}
	if (!P || j > i)
		return ERROR;
	s = (LNode *)malloc(sizeof(LNode));
	s->data = e;
	s->next = P->next;
	P->next = s;
	return OK;
}

//删除结点操作
Status ListDelete(LinkList &L, int i, ElemType *e)
{
	int j = 1;
	LinkList P = L;
	LNode *s;
	while (P->next&&j < i)
	{
		P = P->next;
		j++;
	}
	if (!P->next || j > i)
		return ERROR;
	s = P->next;
	P->next = s->next;
	*e = s->data;
	s->next = NULL;
	return OK;
}
//求表长操作
int GetLength(LinkList L)
{
	int i = 0;
	LinkList P = L;
	while (P->next)
	{
		++i;
		P = P->next;
	}
	return i;
}
//ClearList(*L): 将线性表清空。
Status ClearList(LinkList &L)
{
	LNode *p, *q;
	p = L->next;
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL;
	return OK;
}
//打印单链表
void PrintList(LinkList L)
{
	LinkList p;
	//cout<<
	p = L->next;
	if (p == NULL)
	{
		cout << "该链表为空！" << endl;
	}
	while (p != NULL)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}
int main()
{
	LinkList L=NULL;
	int choose=1;
	InitList(L);
	cout << "请选择以下序号进行操作" << endl;
	cout << "1.采用头插法建立单链表" << endl;
	cout << "2.采用尾插法建立单链表" << endl;
	cout << "3.按序号查找结点值" << endl;
	cout << "4.按值查找表结点" << endl;
	cout << "5.插入结点操作" << endl;
	cout << "6.删除结点操作" << endl;
	cout << "7.求表长操作" << endl;
	cout << "8.将线性表清空。" << endl;
	cout << "0.退出。" << endl;
	while (choose)
	{
		cin >> choose;
		switch (choose)
		{
		case 1:
		{
			int n;
			cout << "请输入要建立单链表的长度" << endl;
			cin >> n;
			CreateListHead(L, n);
			cout << "按头插法创建单链表成功" << endl;
			PrintList(L);
		}
		break;
		case 2:
		{
			int n;
			cout << "请输入要建立单链表的长度" << endl;
			cin >> n;
			CreateListTail(L, n);
			cout << "按尾插法创建单链表成功" << endl;
			PrintList(L);
		}
		break;
		case 3:
		{
			int result,index;
			cout << "请输入要查找的位置" << endl;
			cin >> index;
			if (GetElem(L, index, &result))
			{
				cout << "第"<< index<<"处的元素值为 ："<<result<< endl;
			}
			else
			{
				cout << "查找失败！" << endl;
			}
		}
		break;
		case 4:
		{
			int data;
			cout << "请输入要查找的元素值" << endl;
			cin >> data;
			int re = LocateElem(L, data);
			if (re)
			{
				cout << data << "位于链表中的第" << re << "个位置" << endl;
			}
			else
			{
				cout << "要查找的元素位置不存在" << endl;
			}
		}
		break;
		//插入结点操作
		//Status ListInsert(LinkList &L, int i, ElemType e)
		case 5:
		{
			int i;
			ElemType e;
			cout << "请输入要插入元素的元素值以及位置";
			cin >> e >> i;
			if (ListInsert(L, i, e))
			{
				cout << "插入成功！！" << endl;
				PrintList(L);
			}
			else
			{
				cout << "元素插入失败！！！" << endl;
				cout << "提示：" << "单链表长度为" << GetLength(L) << " 请在有效的位置插入数据" << endl;
			}
		}
		break;
		//删除结点操作
		//Status ListDelete(LinkList &L, int i, ElemType *e)
		case 6:
		{
			int i;
			ElemType e;
			cout << "请输入要删除元素的位置";
			cin >> i;
			if (ListDelete(L,i,&e))
			{
				cout << "删除成功！！" << endl;
				PrintList(L);
			}
			else
			{
				cout << "元素删除失败！！！" << endl;
				cout << "提示：" << "单链表长度为" << GetLength(L) << " 请在有效的位置删除数据" << endl;
			}
		}
		break;
		case 7:
		{
			cout << "表长为 :"<<GetLength(L) << endl;
		}
		break;
		case 8:
		{
			ClearList(L);
			cout << "链表已清除" << endl;
			PrintList(L);
		}
		break;
		case 0: break;
		default:
			break;
		}
	}
	system("pause");
	return 0;

}

