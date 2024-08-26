#include<bits/stdc++.h>
using namespace std;
int x=0;
struct student
{
	char no[9];
	char name[20];
	int price;
	void scan()
	{
		scanf("%s %s %d",no,name,&price); 
	}
	void print()
	{
		printf("%8s %8s %8d\n",no,name,price);
	}
};//新建结构体 
struct node
{
	student d;
	node *next;
};//新建节点 
node *head,*p,*r;
void check()
{
	int i=0;
	p=head->next;
	printf("请输入想查询的学生姓名：");
	char Name[20];
	scanf("%s",Name);
	if(strcmp(p->d.name,Name)==0)
	printf("学号为：%s 成绩为：%d\n",p->d.no,p->d.price);
	else i++;
	do
	{
		p=p->next;
		if(strcmp(p->d.name,Name)==0)
		printf("%8s %8d\n",p->d.no,p->d.price);
		else i++;
	}while(p->next!=NULL);
	if(i==x)
	printf("该学生不存在！\n");
}//用于根据姓名查找 
void see()
{
	p=head->next;
	printf("     学号     姓名     成绩\n");
	while(p->next!=NULL)
	{
		p->d.print();
		p=p->next;
	}
	p->d.print();
}//输出链表 
void position()
{
	int po,i;
	p=head->next;
	printf("请输入所查找的学生位于第几行：");
	cin>>po;
	for(i=1;i<=x;i++)
	if(po==i)break;
	if(i==x+1)printf("未找到！\n");
	for(int i=0;i<po-1;i++)
	p=p->next;
	p->d.print();
}//根据位置查找 
void start()
{
	printf("请输入需要录入的学生个数："); 
	cin>>x;
	printf("请按照“学号 姓名 成绩”的格式逐个录入学生：\n");
	head=new node;
	r=head;
	for(int i=0;i<x;i++)
	{
		p=new node;
		p->d.scan();
		p->next=NULL;
		r->next=p;
		r=p;
	}
}//根据个数录入学生 
void delet()
{
	int po,i;
	printf("请输入所需删除的学生位于第几行：");
	p=head->next;
	cin>>po;
	for(i=1;i<=x;i++)
	if(po==i)break;
	if(i==x+1)printf("未找到！\n");
	if(po==1)head->next=p->next;
	else
	{
		for(int i=0;i<po-2;i++)
		p=p->next;
		p->next=p->next->next;
	}
	x--;
}//删除指定位置学生 
void insert()
{
	node *s;
	int po,i;
	printf("请输入所需插入的学生位于第几行：");
	p=head;
	cin>>po;
	for(i=1;i<=x+1;i++)
	if(po==i)break;
	if(i==x+2)printf("未找到！\n");
	else
	{
		for(int i=0;i<po-1;i++)
		p=p->next;
		s=new node;
		s->next=p->next;
		p->next=s;
		p=p->next;
		printf("请按照“学号 姓名 成绩”的格式输入该学生数据：\n");
		p->d.scan();
		x++;
	}
}//根据位置插入学生 
void total()
{
	printf("总学生个数为：%d\n",x);
}//输出表长 
bool nothing()
{
	if(x==0)
	{
		printf("请先输入数据！\n");
		return false;
	}
	else return true;
}//检查是否是空表 
void check();
void see();
void position();
void start();
void delet();
void insert();
void total(); 
bool nothing();
int main()
{
	int a;
	while(x>=0)
	{
		printf("--------------------------------------\n");
		printf("(1) 根据指定学生个数，逐个输入学生信息\n");
		printf("(2) 逐个显示学生表中所有学生的相关信息\n");
		printf("(3) 根据姓名进行查找，返回此学生的学号和成绩\n");
		printf("(4) 根据指定的位置可返回相应的学生信息\n");
		printf("(5) 给定一个学生信息，插入到表中指定的位置\n");
		printf("(6) 删除指定位置的学生记录\n");
		printf("(7) 统计表中学生个数\n");
		printf("--------------------------------------\n");
		printf("请输入要执行的指令序号：");
		cin>>a;
		switch(a)
		{
			case 1:start();break;
			case 2:if(nothing()==true)see();break;
			case 3:if(nothing()==true)check();break;
			case 4:if(nothing()==true)position();break;
			case 5:if(nothing()==true)insert();break;
			case 6:if(nothing()==true)delet();break;
			case 7:total();break;
			default:cout<<"input error!\n";
		}
	}//根据指令序号运行相应指令 
}

