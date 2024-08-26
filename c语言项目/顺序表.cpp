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
};
student stu[2000];//新建结构体数组 
void start()
{
	printf("请输入需要录入的学生个数："); 
	cin>>x;
	printf("请按照“学号 姓名 成绩”的格式逐个录入学生：\n");
	for(int i=0;i<x;i++)
	stu[i].scan();
}//根据个数录入学生 
void see()
{
	printf("     学号     姓名     成绩\n");
	for(int i=0;i<x;i++)
	stu[i].print();
}//输出顺序表 
void check()
{
	int i=0;
	printf("请输入想查询的学生姓名：");
	char Name[20];
	scanf("%s",Name);
	for(int j=0;j<x;j++)
	{
		if(strcmp(stu[j].name,Name)==0)
		printf("学号为：%s 成绩为：%d\n",stu[i].no,stu[i].price);
		else i++;
	}
	if(i==x)printf("该学生不存在！\n");
}//用于根据姓名查找 
void position()
{
	int j=0,po;
	printf("请输入所查找的学生位于第几行：");
	cin>>po;
	for(int i=0;i<x;i++)
	if(i!=po-1)j++;
	if(j==x)printf("未找到！\n");
	else stu[po-1].print();
}//根据位置查找 
void insert()
{
	int po,i;
	printf("请输入所需插入的学生位于第几行：");
	cin>>po;
	for(i=1;i<=x;i++)
	if(po==i)break;
	if(i==x+1)printf("未找到！\n");
	else
	{
		x++;
		for(int i=x;i>po-1;i--)
		stu[i]=stu[i-1];
		printf("请按照“学号 姓名 成绩”的格式输入该学生数据：\n");
		stu[po-1].scan();
	}
}//根据位置插入学生 
void delet()
{
	int po,i;
	printf("请输入所需删除的学生位于第几行：");
	cin>>po;
	for(i=1;i<=x;i++)
	if(po==i)break;
	if(i==x+1)printf("未找到！\n");
	else
	{
		for(int i=po-1;i<x;i++)
		stu[i]=stu[i+1];
		x--;
	}
}//删除指定位置学生
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
void start();
void see();
void check();
void position();
void insert();
void delet();
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
