#include<bits/stdc++.h>
using namespace std;
struct word 
{
	char a;
	word *next;
};
word *head1,*p1,*r1,*head2,*p2,*r2,*head,*p,*r;
int main()
{
	int len1,len2,len;
	char b1,b2,t;
	head1=new word;
	r1=head1;
	printf("set1=");
	while((b1=getchar())!='\n')
	{
		p1=new word;
		p1->a=b1;
		p1->next=NULL;
		r1->next=p1;
		r1=p1;
		len1++;
	}
	head2=new word;
	r2=head2;
	printf("set2=");
	while((b2=getchar())!='\n')
	{
		p2=new word;
		p2->a=b2;
		p2->next=NULL;
		r2->next=p2;
		r2=p2;
		len2++;
	}
	for(int i=0;i<len1;i++)
	{
		p1=head1;
		while(p1->next->next!=NULL)
		{
			p1=p1->next;
			if(p1->a > p1->next->a)
			{
				t=p1->a;
				p1->a=p1->next->a;
				p1->next->a=t;
			}
		}
	}
	for(int i=0;i<len2;i++)
	{
		p2=head2;
		while(p2->next->next!=NULL)
		{
			p2=p2->next;
			if(p2->a > p2->next->a)
			{
				t=p2->a;
				p2->a=p2->next->a;
				p2->next->a=t;
			}
		}
	}
	p1=head1;
	while(p1->next!=NULL)
	{
		if(p1->a==p1->next->a)
		{
			p1->next=p1->next->next;
			len1--;
		}
		else p1=p1->next;
	}
	p2=head2;
	while(p2->next!=NULL)
	{
		if(p2->a==p2->next->a)
		{
			p2->next=p2->next->next;
			len2--;
		}
		else p2=p2->next;
	}
	p1=head1;
	p2=head2;
	head=new word;
	r=head;
	while(!(p1->next==NULL&&p2->next==NULL))
	{
		if(p1->next!=NULL)
		{
			if(p2->next==NULL||p1->next->a <= p2->next->a)
			{
				if(p2->next==NULL||p1->next->a < p2->next->a)
				{
					p=new word;
					p->a=p1->next->a;
					p->next=NULL;
					r->next=p;
					r=p;
					len++;
				}
				p1=p1->next;
			}
		}
		if(p2->next!=NULL)
		{
			if(p1->next==NULL||p1->next->a > p2->next->a)
			{
				p=new word;
				p->a=p2->next->a;
				p->next=NULL;
				r->next=p;
				r=p;
				len++;
				p2=p2->next;
			}
		}
	}
	printf("并集为:");
	p=head;
	while(p->next!=NULL)
	{
		p=p->next;
		printf("%c",p->a);
	}
	printf("\n");
	p1=head1;
	head=new word;
	r=head;
	while(p1->next!=NULL)
	{
		p1=p1->next;
		p2=head2;
		while(p2->next!=NULL)
		{
			p2=p2->next;
			if(p1->a == p2->a)
			{
				p=new word;
				p->a=p1->a;
				p->next=NULL;
				r->next=p;
				r=p;
				len++;
			}
		}
	}
	p=head;
	printf("交集为:");
	while(p->next!=NULL)
	{
		p=p->next;
		printf("%c",p->a);
	}
	printf("\n");
	p1=head1;
	p2=head2;
	head=new word;
	r=head;
	while(!(p1->next==NULL&&p2->next==NULL))
	{
		if(p1->next!=NULL)
		{
			if(p2->next==NULL||p1->next->a <= p2->next->a)
			{
				if(p2->next==NULL||p1->next->a != p2->next->a)
				{
					p=new word;
					p->a=p1->next->a;
					p->next=NULL;
					r->next=p;
					r=p;
					len++;
				}
				p1=p1->next;
			}
		}
		if(p2->next!=NULL)
		{
			if(p1->next==NULL||p1->next->a > p2->next->a)
			{
				p2=p2->next;
			}
		}
	}
	p=head;
	printf("差集为:");
	while(p->next!=NULL)
	{
		p=p->next;
		printf("%c",p->a);
	}
}
