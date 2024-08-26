#include<bits/stdc++.h>
using namespace std;
int park_max,Carnum,Outtime,po_park=0,po_road=0,Time,where,j;
char command;
struct cardata
{
	int carnum;
	int intime;
	int outtime;
};//车的基本数据 
struct Stack
{
	cardata parkcar[10000];
	cardata *base;
	cardata *top;
};//车库以及等待区
Stack park,wait;
struct road
{
	cardata car;
	road *next;
};//便道 
road *p,*head,*r;
void startroad()
{
	head=new road;
	head->next=NULL;
	r=head;
}//初始化便道
void inroad()
{
	p=new road;
	cin>>p->car.carnum>>p->car.intime;
	p->next=NULL;
	r->next=p;
	r=p;
	po_road++;
	printf("该车停在便道的第%d的位置上\n",po_road);
}//车进入便道
void gothroughroad()
{
	int a=1;
	if(head->next==NULL)printf("便道上无车辆\n");
	else
	{
		printf("位置		车牌\n"); 
		p=head;
		while(p->next!=NULL)
		{
			printf("%d		",a++);
			p=p->next;
			cout<<p->car.carnum<<endl;
		}
	}
}//查看便道上所有车
bool is_road_space()
{
	if(head->next==NULL)return true;
	else return false;
}//便道是否为空 
void startpark()
{
	park.base=park.parkcar;
	park.top=park.parkcar;
}//初始化车库
void inpark()
{
	cin>>park.top->carnum>>park.top->intime;
	park.top++;
	po_park++;
	printf("该车停在停车场的第%d的位置上\n",po_park);
}//车进入车库
void gothroughpark()
{
	int c=1;
	if(park.base==park.top)printf("车库内无车辆\n");
	else
	{
		printf("位置		车牌		进入时间\n"); 
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
}//查看车库内所有车
bool is_park_space()
{
	if(park.top==park.base)return true;
	else return false;
}//车库是否为空 
bool is_park_full()
{
	if(park.top-park.base>=park_max)
	return true;
	else return false;
}//车库是否已满
void startwait()
{
	wait.base=wait.parkcar;
	wait.top=wait.parkcar;
}//初始化等待区
void outpark_inwait()
{
	park.top--;
	wait.top->carnum=park.top->carnum;
	wait.top->intime=park.top->intime;
	wait.top->outtime=park.top->outtime;
	wait.top++;
}//车从停车场进入等待区
void outroad_inpark()
{
	park.top->carnum=head->next->car.carnum;
	park.top->intime=Time;
	park.top->outtime=head->next->car.outtime;
	head=head->next;
	printf("车牌号为%d的车进入停车场的时间为:%d\n",park.top->carnum,Time); 
	park.top++;
	po_road--;
}//车从便道进入车库
void outpark()
{
	park.top--;
	printf("该车停留的时间为%d小时，应缴费用为%f元\n",park.top->outtime-park.top->intime,(park.top->outtime-park.top->intime)*1.5);
	Time=park.top->outtime;
	po_park--;
}//车离开停车场
void outwait_inpark()
{
	wait.top--;
	park.top->carnum=wait.top->carnum;
	park.top->intime=wait.top->intime;
	park.top->outtime=wait.top->outtime;
	park.top++;
}//车从等待区进入停车场
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
	printf("请输入停车场最多可停放车数:");
	cin>>park_max;
	while(1)
	{
		printf("有车辆进入停车场(A);查看停车场内车辆(B);查看便道内车辆(C);有车辆出停车场(D);程序停止(#):");
		cin>>command;
		if(command!='A'&&command!='B'&&command!='C'&&command!='D'&&command!='#')printf("输入错误！\n"); 
		else
		{
			if(command=='A')
			{
				printf("登记车牌号及车辆到达时间（按小时为准）:");
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
				printf("出停车场的车的车牌号以及离开的时间:");
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
				else printf("未找到！\n");
			}
			if(command=='#')break;
		}
	}
}
