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
}//获取数据长度len并再读取一个回车字符 
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
}//获得子串 
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
}//获得主串 
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
}//BF算法 
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
}//KMP算法 
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
}//获得next组 
void change(char T[])
{
	int t=T[1];
	for(int i=1;i<T[0];i++)
	{
		T[i]=T[i+1];
	}
	T[T[0]]=t;
}//变换子串模拟病毒环装dna 
int main()
{
	fp=fopen("病毒感染检测输入数据.txt","r");
	fout=fopen("病毒感染检测输出结果.txt","w+");
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
			}//如果检测到子串输出YES 
			else
			{
				change(T);
				get_next(T);
			}//检测失败变换子串并获得新的next再次检测 
		}
		if(n==T[0])
		{
			fputs("NO\n",fout);
		}//变换次数=子串长度时输出NO 
	}
}
