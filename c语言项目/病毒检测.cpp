#include<bits/stdc++.h>
using namespace std;
char S[100],T[100];
FILE *fp,*fout;
int next[100],len;
void get_len()
{
	char c;
	fscanf(fp,"%d",&len);
	fscanf(fp,"%c",&c);
}//��ȡ���ݳ���len���ٶ�ȡһ���س��ַ� 
void get_T()
{
	fseek(fp,0,SEEK_CUR);
	int i=0;
	while(T[i]!='\t')
	{
		i++;
		T[i]=fgetc(fp);
	}
	T[0]=i-1;
	for(i=1;i<=T[0];i++)fprintf(fout,"%c",T[i]);
	fprintf(fout,"\t");
}//����Ӵ� 
void get_S()
{
	fseek(fp,0,SEEK_CUR);
	int i=0;
	while(S[i]!='\n')
	{
		i++;
		S[i]=fgetc(fp);
	}
	S[0]=i-1;
	for(i=1;i<=S[0];i++)fprintf(fout,"%c",S[i]);
	fprintf(fout,"\t");
	if(S[0]<12)fprintf(fout,"\t");
}//������� 
int  Index(char S[],char T[])
{
    int i=1, j=1;
    while (i<=S[ 0 ] && j <=T[ 0 ])
	{
        if ( S[ i ]==T[ j ]) 
	    {
			i++;  
			j++; 
		}
    	else
		{
			i=i-j+2;
		    j=1;
		}
	}
    if(j>T[0])return i-T[0];
    else return 0;
}//BF�㷨 
int Index_KMP(char S[],char T[])
{      
    int i= 1,j =1;
	while (i<=S[0] && j<=T[0])
	{     
        if (j==0 || S[i]==T[j]) {   i++;j++;  }
        else 
        j=next[j];       
    }
    if (j>T[0]) return i-T[0];
    else return 0;
}//KMP�㷨 
void get_next(char T[])
{
    int i= 1; next[1] = 0;int j = 0; 
    while( i<T[0])
	{
        if(j==0 || T[i] == T[j])
		{
            ++i; ++j; 
            next[i] = j;
        }
        else
        j = next[j];
    }
}//���next�� 
void change(char T[])
{
	int t=T[1];
	for(int i=1;i<T[0];i++)
	{
		T[i]=T[i+1];
	}
	T[T[0]]=t;
}//�任�Ӵ�ģ�ⲡ����װdna 
int main()
{
	fp=fopen("������Ⱦ�����������.txt","r");
	fout=fopen("������Ⱦ���������.txt","w+");
	get_len();
	for(int m=0;m<len;m++)
	{
		int n;
		get_T();
		get_S();
		get_next(T);
		for(n=0;n<T[0];n++)
		{
			if(Index(S,T)!=0)
			{
				fputs("YES\n",fout);
				break;
			}//�����⵽�Ӵ����YES 
			else
			{
				change(T);
				get_next(T);
			}//���ʧ�ܱ任�Ӵ�������µ�next�ٴμ�� 
		}
		if(n==T[0])
		{
			fputs("NO\n",fout);
		}//�任����=�Ӵ�����ʱ���NO 
	}
}
