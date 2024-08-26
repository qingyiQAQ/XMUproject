#include<bits/stdc++.h>
using namespace std;
int park_max,Carnum,Outtime,po_park=0,po_road=0,Time,where,j;
char command;
struct cardata
{
	int carnum;
	int intime;
	int outtime;
};//���Ļ������� 
struct Stack
{
	cardata parkcar[10000];
	cardata *base;
	cardata *top;
};//�����Լ��ȴ���
Stack park,wait;
struct road
{
	cardata car;
	road *next;
};//��� 
road *p,*head,*r;
void startroad()
{
	head=new road;
	head->next=NULL;
	r=head;
}//��ʼ�����
void inroad()
{
	p=new road;
	cin>>p->car.carnum>>p->car.intime;
	p->next=NULL;
	r->next=p;
	r=p;
	po_road++;
	printf("�ó�ͣ�ڱ���ĵ�%d��λ����\n",po_road);
}//��������
void gothroughroad()
{
	int a=1;
	if(head->next==NULL)printf("������޳���\n");
	else
	{
		printf("λ��		����\n"); 
		p=head;
		while(p->next!=NULL)
		{
			printf("%d		",a++);
			p=p->next;
			cout<<p->car.carnum<<endl;
		}
	}
}//�鿴��������г�
bool is_road_space()
{
	if(head->next==NULL)return true;
	else return false;
}//����Ƿ�Ϊ�� 
void startpark()
{
	park.base=park.parkcar;
	park.top=park.parkcar;
}//��ʼ������
void inpark()
{
	cin>>park.top->carnum>>park.top->intime;
	park.top++;
	po_park++;
	printf("�ó�ͣ��ͣ�����ĵ�%d��λ����\n",po_park);
}//�����복��
void gothroughpark()
{
	int c=1;
	if(park.base==park.top)printf("�������޳���\n");
	else
	{
		printf("λ��		����		����ʱ��\n"); 
		cardata *s;
		s=park.base;
		while(park.base!=park.top)
		{
			printf("%d		",c++); 
			cout<<park.base->carnum<<"		"<<park.base->intime<<endl;
			park.base++;
		}
		park.base=s;
	}
}//�鿴���������г�
bool is_park_space()
{
	if(park.top==park.base)return true;
	else return false;
}//�����Ƿ�Ϊ�� 
bool is_park_full()
{
	if(park.top-park.base>=park_max)
	return true;
	else return false;
}//�����Ƿ�����
void startwait()
{
	wait.base=wait.parkcar;
	wait.top=wait.parkcar;
}//��ʼ���ȴ���
void outpark_inwait()
{
	park.top--;
	wait.top->carnum=park.top->carnum;
	wait.top->intime=park.top->intime;
	wait.top->outtime=park.top->outtime;
	wait.top++;
}//����ͣ��������ȴ���
void outroad_inpark()
{
	park.top->carnum=head->next->car.carnum;
	park.top->intime=Time;
	park.top->outtime=head->next->car.outtime;
	head=head->next;
	printf("���ƺ�Ϊ%d�ĳ�����ͣ������ʱ��Ϊ:%d\n",park.top->carnum,Time); 
	park.top++;
	po_road--;
}//���ӱ�����복��
void outpark()
{
	park.top--;
	printf("�ó�ͣ����ʱ��Ϊ%dСʱ��Ӧ�ɷ���Ϊ%fԪ\n",park.top->outtime-park.top->intime,(park.top->outtime-park.top->intime)*1.5);
	Time=park.top->outtime;
	po_park--;
}//���뿪ͣ����
void outwait_inpark()
{
	wait.top--;
	park.top->carnum=wait.top->carnum;
	park.top->intime=wait.top->intime;
	park.top->outtime=wait.top->outtime;
	park.top++;
}//���ӵȴ�������ͣ����
bool find_park()
{
	where=1;
	cardata *t;
	t=park.base;
	while(park.base!=park.top)
	{
		if(park.base->carnum==Carnum)
		{
			park.base->outtime=Outtime;
			break;
		}
		else
		{
			where++;
			park.base++;
		}
	}
	if(park.base==park.top)
	{
		park.base=t;
		return false;
	}
	else
	{
		park.base=t;
		return true;
	}
}
int main()
{
	startroad();
	startpark();
	startwait();
	printf("������ͣ��������ͣ�ų���:");
	cin>>park_max;
	while(1)
	{
		printf("�г�������ͣ����(A);�鿴ͣ�����ڳ���(B);�鿴����ڳ���(C);�г�����ͣ����(D);����ֹͣ(#):");
		cin>>command;
		if(command!='A'&&command!='B'&&command!='C'&&command!='D'&&command!='#')printf("�������\n"); 
		else
		{
			if(command=='A')
			{
				printf("�Ǽǳ��ƺż���������ʱ�䣨��СʱΪ׼��:");
				if(is_park_full()==true)inroad();
				else inpark();
			}
			if(command=='B')
			{
				gothroughpark();
			}
			if(command=='C')
			{
				gothroughroad();
			}
			if(command=='D')
			{
				printf("��ͣ�����ĳ��ĳ��ƺ��Լ��뿪��ʱ��:");
				cin>>Carnum>>Outtime;
				if(find_park()==true)
				{
					int a=park.top-park.base-where;
					for(j=0;j<a;j++)
					{
						outpark_inwait();
					}
					outpark();
					int b=wait.top-wait.base;
					for(j=0;j<b;j++)
					{
						outwait_inpark();
					}
					if(is_road_space()==false)outroad_inpark();
				}
				else printf("δ�ҵ���\n");
			}
			if(command=='#')break;
		}
	}
}
