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
};//�½��ṹ�� 
struct node
{
	student d;
	node *next;
};//�½��ڵ� 
node *head,*p,*r;
void check()
{
	int i=0;
	p=head->next;
	printf("���������ѯ��ѧ��������");
	char Name[20];
	scanf("%s",Name);
	if(strcmp(p->d.name,Name)==0)
	printf("ѧ��Ϊ��%s �ɼ�Ϊ��%d\n",p->d.no,p->d.price);
	else i++;
	do
	{
		p=p->next;
		if(strcmp(p->d.name,Name)==0)
		printf("%8s %8d\n",p->d.no,p->d.price);
		else i++;
	}while(p->next!=NULL);
	if(i==x)
	printf("��ѧ�������ڣ�\n");
}//���ڸ����������� 
void see()
{
	p=head->next;
	printf("     ѧ��     ����     �ɼ�\n");
	while(p->next!=NULL)
	{
		p->d.print();
		p=p->next;
	}
	p->d.print();
}//������� 
void position()
{
	int po,i;
	p=head->next;
	printf("�����������ҵ�ѧ��λ�ڵڼ��У�");
	cin>>po;
	for(i=1;i<=x;i++)
	if(po==i)break;
	if(i==x+1)printf("δ�ҵ���\n");
	for(int i=0;i<po-1;i++)
	p=p->next;
	p->d.print();
}//����λ�ò��� 
void start()
{
	printf("��������Ҫ¼���ѧ��������"); 
	cin>>x;
	printf("�밴�ա�ѧ�� ���� �ɼ����ĸ�ʽ���¼��ѧ����\n");
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
}//���ݸ���¼��ѧ�� 
void delet()
{
	int po,i;
	printf("����������ɾ����ѧ��λ�ڵڼ��У�");
	p=head->next;
	cin>>po;
	for(i=1;i<=x;i++)
	if(po==i)break;
	if(i==x+1)printf("δ�ҵ���\n");
	if(po==1)head->next=p->next;
	else
	{
		for(int i=0;i<po-2;i++)
		p=p->next;
		p->next=p->next->next;
	}
	x--;
}//ɾ��ָ��λ��ѧ�� 
void insert()
{
	node *s;
	int po,i;
	printf("��������������ѧ��λ�ڵڼ��У�");
	p=head;
	cin>>po;
	for(i=1;i<=x+1;i++)
	if(po==i)break;
	if(i==x+2)printf("δ�ҵ���\n");
	else
	{
		for(int i=0;i<po-1;i++)
		p=p->next;
		s=new node;
		s->next=p->next;
		p->next=s;
		p=p->next;
		printf("�밴�ա�ѧ�� ���� �ɼ����ĸ�ʽ�����ѧ�����ݣ�\n");
		p->d.scan();
		x++;
	}
}//����λ�ò���ѧ�� 
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

