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
	}//初始化总卡牌 
	head1=new node;
	r1=head1;
	for(int i=1;i<=26;i++)
	{
		p1=new node;
		p1->next=NULL;
		r1->next=p1;
		r1=p1;
	}//初始化玩家1卡牌 
	head2=new node;
	r2=head2;
	for(int i=1;i<=26;i++)
	{
		p2=new node;
		p2->next=NULL;
		r2->next=p2;
		r2=p2;
	}//初始化玩家2卡牌 
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
}//遍历总卡牌 
void check1()
{
	p1=head1;
	while(p1->next!=NULL)
	{
		p1=p1->next;
		printf("%d ",p1->poker);
	}
	printf("\n");
}//遍历玩家1卡牌 
void check2()
{
	p2=head2;
	while(p2->next!=NULL)
	{
		p2=p2->next;
		printf("%d ",p2->poker);
	}
	printf("\n");
}//遍历玩家2卡牌 
void fapai()
{
	printf("进行随机发牌（已去除大王小王），以11代表J，以12代表Q，以13代表K\n"); 
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
	}//随机发牌到玩家1 
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
	}//随机发牌到玩家2 
}
void pai()
{
	for(int i=0;i<=j;i++)
	printf("%d ",table[i]);
	printf("\n");
}//查看当前桌面上的牌 
void chupai()
{
	while(!(head1->next==NULL||head2->next==NULL))
	{
		table[j]=head1->next->poker;
		head1=head1->next;
		printf("玩家1出牌，牌数为%d\n",head1->poker);
		for(int k=0;k<j;k++)
		{
			if(table[k]==head1->poker)
			{
				printf("玩家1获得:");
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
				printf("此时桌上的牌:");
				pai();
				printf("玩家1的牌:");
				check1();
			}
		}
		j++;//玩家1出牌并判断是否有相同牌且获得两牌中间所有牌 
		table[j]=head2->next->poker;
		head2=head2->next;
		printf("玩家2出牌，牌数为%d\n",head2->poker);
		for(int k=0;k<j;k++)
		{
			if(table[k]==head2->poker)
			{
				printf("玩家2获得:");
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
				printf("此时桌上的牌:");
				pai();
				printf("玩家2的牌:");
				check2();
			}
		}
		j++;//玩家2出牌并判断是否有相同牌且获得两牌中间所有牌 
	}
	if(head1->next==NULL)printf("玩家2胜利！");
	else printf("玩家1胜利！");//判断胜利玩家 
}
int main()
{
	srand((unsigned int)time(NULL));
	start();
	fapai();
	printf("玩家1的初始牌为:");
	check1();
	printf("玩家2的初始牌为:");
	check2();
	chupai();
	return 0; 
}

