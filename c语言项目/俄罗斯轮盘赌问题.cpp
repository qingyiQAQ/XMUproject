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
	printf("�����ͽ��������");
	cin>>x;
	printf("����ͽ���α��Ϊ1-%d\n",x);
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
		printf("��%d�ֿ�ʼ,",a);
		printf("�ӱ��Ϊ%d���˿�ʼ,",p->next->num);
		gun[rand()%6]=1;
		for(int i=0;i<6;i++)
		{
			if(gun[i]==1)
			j=i+1;
		}
		printf("ǹ�ڵ�%d�ο۶����ʱ����,",j);
		for(int i=0;i<j-1;i++)
		{
			p=p->next;
		}
		printf("���Ϊ%d�Ķ�ͽ�˳��Ĳ�,",p->next->num);
		if(p->next==head->next)
		head=head->next;
		r=head;
		p->next=p->next->next;
		x--;
		printf("ʣ���ͽ�������Ϊ:");
		for(int i=0;i<x;i++)
		{
			r=r->next;
			printf("%d ",r->num);
		}
		printf("\n");
		for(int i=0;i<6;i++)
		gun[i]=0;
	}
	printf("����ʤ���Ķ�ͽ�����:%d",p->num);
}
