#include<bits/stdc++.h>
using namespace std;
int n=52,table[52],j=0;
struct node
{
	int poker;
	node *next;
};
node *p,*head,*r,*p1,*head1,*r1,*p2,*head2,*r2,*add1,*add2;
void start()
{
	head=new node;
	r=head;
	for(int j=0;j<4;j++)
	{
		for(int i=1;i<=13;i++)
		{
			p=new node;
			p->poker=i;
			p->next=NULL;
			r->next=p;
			r=p;
		}
	}//��ʼ���ܿ��� 
	head1=new node;
	r1=head1;
	for(int i=1;i<=26;i++)
	{
		p1=new node;
		p1->next=NULL;
		r1->next=p1;
		r1=p1;
	}//��ʼ�����1���� 
	head2=new node;
	r2=head2;
	for(int i=1;i<=26;i++)
	{
		p2=new node;
		p2->next=NULL;
		r2->next=p2;
		r2=p2;
	}//��ʼ�����2���� 
}
void check()
{
	r=head;
	while(r->next!=NULL)
	{
		r=r->next;
		printf("%d ",r->poker);
	}
	printf("\n");
	r=head;
}//�����ܿ��� 
void check1()
{
	p1=head1;
	while(p1->next!=NULL)
	{
		p1=p1->next;
		printf("%d ",p1->poker);
	}
	printf("\n");
}//�������1���� 
void check2()
{
	p2=head2;
	while(p2->next!=NULL)
	{
		p2=p2->next;
		printf("%d ",p2->poker);
	}
	printf("\n");
}//�������2���� 
void fapai()
{
	printf("����������ƣ���ȥ������С��������11����J����12����Q����13����K\n"); 
	int ra;
	p1=head1;
	while(p1->next!=NULL)
	{
		p=head;
		ra=rand()%n+1;
		for(int i=0;i<ra-1;i++)
		p=p->next;
		r=p->next;
		p->next=p->next->next;
		p1=p1->next;
		p1->poker=r->poker;
		n--;
	}//������Ƶ����1 
	p2=head2;
	while(p2->next!=NULL)
	{
		p=head;
		ra=rand()%n+1;
		for(int i=0;i<ra-1;i++)
		p=p->next;
		r=p->next;
		p->next=p->next->next;
		p2=p2->next;
		p2->poker=r->poker;
		n--;
	}//������Ƶ����2 
}
void pai()
{
	for(int i=0;i<=j;i++)
	printf("%d ",table[i]);
	printf("\n");
}//�鿴��ǰ�����ϵ��� 
void chupai()
{
	while(!(head1->next==NULL||head2->next==NULL))
	{
		table[j]=head1->next->poker;
		head1=head1->next;
		printf("���1���ƣ�����Ϊ%d\n",head1->poker);
		for(int k=0;k<j;k++)
		{
			if(table[k]==head1->poker)
			{
				printf("���1���:");
				for(int m=k;m<=j;m++)printf("%d ",table[m]);
				for(int n=0;n<=j-k;n++)
				{
					r1=new node;
					r1->poker=table[k+n];
					r1->next=NULL;
					p1->next=r1;
					p1=r1;
				}
				j=k-1;
				printf("��ʱ���ϵ���:");
				pai();
				printf("���1����:");
				check1();
			}
		}
		j++;//���1���Ʋ��ж��Ƿ�����ͬ���һ�������м������� 
		table[j]=head2->next->poker;
		head2=head2->next;
		printf("���2���ƣ�����Ϊ%d\n",head2->poker);
		for(int k=0;k<j;k++)
		{
			if(table[k]==head2->poker)
			{
				printf("���2���:");
				for(int m=k;m<=j;m++)printf("%d ",table[m]);
				for(int n=0;n<=j-k;n++)
				{
					r2=new node;
					r2->poker=table[k+n];
					r2->next=NULL;
					p2->next=r2;
					p2=r2;
				}
				j=k-1;
				printf("��ʱ���ϵ���:");
				pai();
				printf("���2����:");
				check2();
			}
		}
		j++;//���2���Ʋ��ж��Ƿ�����ͬ���һ�������м������� 
	}
	if(head1->next==NULL)printf("���2ʤ����");
	else printf("���1ʤ����");//�ж�ʤ����� 
}
int main()
{
	srand((unsigned int)time(NULL));
	start();
	fapai();
	printf("���1�ĳ�ʼ��Ϊ:");
	check1();
	printf("���2�ĳ�ʼ��Ϊ:");
	check2();
	chupai();
	return 0; 
}

