#include<bits/stdc++.h>
using namespace std;
int gun[6];
struct people
{
	int num;
	people *next;
};
people *head,*p,*r;
int main()
{
	int x;
	srand((unsigned)time(NULL));
	printf("输入赌徒的人数：");
	cin>>x;
	printf("将赌徒依次编号为1-%d\n",x);
	head=new people;
	r=head;
	for(int i=0;i<x;i++)
	{
		p=new people;
		p->num=i+1;
		p->next=NULL;
		r->next=p;
		r=p;
	}
	p->next=head->next;
	p=head;
	int j=0,a=0;
	while(x>1)
	{
		a++;
		printf("第%d轮开始,",a);
		printf("从编号为%d的人开始,",p->next->num);
		gun[rand()%6]=1;
		for(int i=0;i<6;i++)
		{
			if(gun[i]==1)
			j=i+1;
		}
		printf("枪在第%d次扣动扳机时会响,",j);
		for(int i=0;i<j-1;i++)
		{
			p=p->next;
		}
		printf("编号为%d的赌徒退出赌博,",p->next->num);
		if(p->next==head->next)
		head=head->next;
		r=head;
		p->next=p->next->next;
		x--;
		printf("剩余赌徒编号依次为:");
		for(int i=0;i<x;i++)
		{
			r=r->next;
			printf("%d ",r->num);
		}
		printf("\n");
		for(int i=0;i<6;i++)
		gun[i]=0;
	}
	printf("最终胜利的赌徒编号是:%d",p->num);
}
