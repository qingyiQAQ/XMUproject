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
student stu[2000];//�½��ṹ������ 
void start()
{
	printf("��������Ҫ¼���ѧ��������"); 
	cin>>x;
	printf("�밴�ա�ѧ�� ���� �ɼ����ĸ�ʽ���¼��ѧ����\n");
	for(int i=0;i<x;i++)
	stu[i].scan();
}//���ݸ���¼��ѧ�� 
void see()
{
	printf("     ѧ��     ����     �ɼ�\n");
	for(int i=0;i<x;i++)
	stu[i].print();
}//���˳��� 
void check()
{
	int i=0;
	printf("���������ѯ��ѧ��������");
	char Name[20];
	scanf("%s",Name);
	for(int j=0;j<x;j++)
	{
		if(strcmp(stu[j].name,Name)==0)
		printf("ѧ��Ϊ��%s �ɼ�Ϊ��%d\n",stu[i].no,stu[i].price);
		else i++;
	}
	if(i==x)printf("��ѧ�������ڣ�\n");
}//���ڸ����������� 
void position()
{
	int j=0,po;
	printf("�����������ҵ�ѧ��λ�ڵڼ��У�");
	cin>>po;
	for(int i=0;i<x;i++)
	if(i!=po-1)j++;
	if(j==x)printf("δ�ҵ���\n");
	else stu[po-1].print();
}//����λ�ò��� 
void insert()
{
	int po,i;
	printf("��������������ѧ��λ�ڵڼ��У�");
	cin>>po;
	for(i=1;i<=x;i++)
	if(po==i)break;
	if(i==x+1)printf("δ�ҵ���\n");
	else
	{
		x++;
		for(int i=x;i>po-1;i--)
		stu[i]=stu[i-1];
		printf("�밴�ա�ѧ�� ���� �ɼ����ĸ�ʽ�����ѧ�����ݣ�\n");
		stu[po-1].scan();
	}
}//����λ�ò���ѧ�� 
void delet()
{
	int po,i;
	printf("����������ɾ����ѧ��λ�ڵڼ��У�");
	cin>>po;
	for(i=1;i<=x;i++)
	if(po==i)break;
	if(i==x+1)printf("δ�ҵ���\n");
	else
	{
		for(int i=po-1;i<x;i++)
		stu[i]=stu[i+1];
		x--;
	}
}//ɾ��ָ��λ��ѧ��
void total()
{
	printf("��ѧ������Ϊ��%d\n",x);
}//����� 
bool nothing()
{
	if(x==0)
	{
		printf("�����������ݣ�\n");
		return false;
	}
	else return true;
}//����Ƿ��ǿձ� 
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
		printf("(1) ����ָ��ѧ���������������ѧ����Ϣ\n");
		printf("(2) �����ʾѧ����������ѧ���������Ϣ\n");
		printf("(3) �����������в��ң����ش�ѧ����ѧ�źͳɼ�\n");
		printf("(4) ����ָ����λ�ÿɷ�����Ӧ��ѧ����Ϣ\n");
		printf("(5) ����һ��ѧ����Ϣ�����뵽����ָ����λ��\n");
		printf("(6) ɾ��ָ��λ�õ�ѧ����¼\n");
		printf("(7) ͳ�Ʊ���ѧ������\n");
		printf("--------------------------------------\n");
		printf("������Ҫִ�е�ָ����ţ�");
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
	}//����ָ�����������Ӧָ�� 
}
