#include<bits/stdc++.h>
#define MAXINT 32767
using namespace std;
struct Node
{
	char name[100];
	char info[1000];
};
struct MGraph
{ 
Node vexs[100];
int arcs[100][100];
int vexnum,arcnum;
};
int LocateVex(MGraph &G,char v[])//�Ӿ�������ñ��
{
	int i;
	for(i=0;i<G.vexnum;i++)
	{
		if(strcmp(G.vexs[i].name,v)==0)return i;
	}
	if(i==G.vexnum) return -1;
}
void read_in(MGraph &G)//���뾰���ļ� 
{
	cin>>G.vexnum>>G.arcnum;
	for(int i=0;i<G.vexnum;i++)
	cin>>G.vexs[i].name>>G.vexs[i].info;
	for(int i=0;i<G.vexnum;i++)
	{
		for(int j=0;j<G.vexnum;j++)
		{
			G.arcs[i][j] = MAXINT;
		}
	}
	for(int k=0; k<G.arcnum;++k)
	{                 
		char v1[100],v2[100];
		int w,i,j;  
    	cin>>v1>>v2>>w;
    	if(LocateVex(G, v1)!=-1)
    	i=LocateVex(G, v1);
    	if(LocateVex(G, v2)!=-1)
		j=LocateVex(G, v2);
    	G.arcs[i][j]=w;
    	G.arcs[j][i]=G.arcs[i][j];
   }
}
void freshen(MGraph &G)//�ļ�ˢ�� 
{
	freopen("graph.txt","w",stdout);
	cout<<G.vexnum<<" "<<G.arcnum<<endl;
	for(int i=0;i<G.vexnum;i++)
	cout<<G.vexs[i].name<<" "<<G.vexs[i].info<<endl;
	for(int i=0;i<G.vexnum;i++)
	{
		for(int j=i;j<G.vexnum;j++)
		{
			if(G.arcs[i][j]!=MAXINT)
			{
				cout<<G.vexs[i].name<<" "<<G.vexs[j].name<<" "<<G.arcs[i][j]<<endl;
			}
		}
	}
	fclose(stdout);
	freopen("CON", "r", stdin);
	freopen("CON", "w", stdout);
}
void ShortestPath_DIJ(MGraph &G, int v1 ,int v2)//���·���㷨 
{
	v1--;v2--;
    //��Dijkstra�㷨��������G��v0���㵽���ඥ������·�� 
    int n=G.vexnum;//nΪG�ж���ĸ��� 
	int S[100],D[100],Path[100]; 
	int v,w;                   		
    for(v = 0; v<n; ++v)
	{             	//n���������γ�ʼ�� 
    	S[v] = 0;                  	//S��ʼΪ�ռ� 
    	D[v] = G.arcs[v1][v];           	//��v0�������յ�����·�����ȳ�ʼ�� 
    	if(D[v]< MAXINT)  Path [v]=v1; //v0��v֮���л�����v��ǰ����Ϊv0 
    	else Path [v]=-1;               	//���v0��v֮���޻�����v��ǰ����Ϊ-1 
    }//for 
    S[v1]=1;                    	//��v0����S 
    D[v1]=0;
	/*�D��ʼ��ѭ����ÿ�����v0��ĳ������v�����·������v�ӵ�S���D*/ 
    for(int i=1;i<n; ++i)
	{               	//������n?1�����㣬���ν��м��� 
    	int min= MAXINT;
        for(w=0;w<n; ++w)
		{
			if(!S[w]&&D[w]<min)  
            {
				v=w;
				min=D[w];
			}         	//ѡ��һ����ǰ�����·�����յ�Ϊv 
		}
        S[v]=1;                   		//��v����S 
        for(w=0;w<n; ++w)
		{//���´�v0����������V?S�����ж�������·������
        	if(!S[w]&&(D[v]+G.arcs[v][w]<D[w]))
			{ 
        	     D[w]=D[v]+G.arcs[v][w];   	//����D[w] 
        	     Path [w]=v;              		//����w��ǰ��Ϊv 
       		}//if
       }
    }//for
    int l=v2,a[100],i=0;
    while(l!=-1)
    {
    	a[i]=l;
    	i++;
    	l=Path[l];
	}
	if(D[v2]==MAXINT)cout<<"�޷��ִ"<<endl; 
	else
	{
		cout<<"·����:";
		for(int j=i-1;j>=0;j--)
		{
			cout<<G.vexs[a[j]].name;
			if(j)cout<<"->";
			else cout<<endl; 
		}
		cout<<"���·����:"<<D[v2]<<endl;
	}
}//ShortestPath_DIJ
void delete_scene(MGraph &G)//ɾ������ 
{
	int v;
	cout<<"��������Ҫɾ���ľ���(1-"<<G.vexnum<<"):"<<endl;
	cin>>v;
	for(int i=v-1;i<G.vexnum;i++)
	{
		G.vexs[i]=G.vexs[i+1];
	}
	for(int i=0;i<G.vexnum;i++)
	{
		for(int j=0;j<G.vexnum;j++)
		{
			if(i>=v-1) G.arcs[i][j]=G.arcs[i+1][j];
		}
	}
	for(int i=0;i<G.vexnum;i++)
	{
		for(int j=0;j<G.vexnum;j++)
		{
			if(j>=v-1) G.arcs[i][j]=G.arcs[i][j+1];
		}
	}
	for(int i=0;i<G.vexnum;i++)
	{
		G.arcs[i][G.vexnum]=MAXINT;
		G.arcs[G.vexnum][i]=MAXINT;
	}
	G.vexnum--;
	G.arcnum=0;
	for(int i=0;i<G.vexnum;i++)
	{
		for(int j=i;j<G.vexnum;j++)
		{
			if(G.arcs[i][j]!=MAXINT)
			G.arcnum++;
		}
	}
	freshen(G);
	cout<<"�ɹ�ɾ����"<<endl; 
}
void delete_road(MGraph &G)//ɾ��·�� 
{
	int v1,v2; 
	cout<<"��������Ҫɾ����·�����˵ľ���(1-"<<G.vexnum<<"):"<<endl;
	cin>>v1>>v2;
	if(G.arcs[v1-1][v2-1]==MAXINT)cout<<"δ�ҵ���·��!"<<endl;
	else
	{
		G.arcs[v1-1][v2-1]=MAXINT;
		G.arcs[v2-1][v1-1]=MAXINT;
		cout<<"�ɹ�ɾ����"<<endl;
		G.arcnum--;
		freshen(G);
	}
}
void road(MGraph &G)//�鿴����·�� 
{
	for(int i=0;i<G.vexnum;i++)
	{
		for(int j=0;j<G.vexnum;j++)
		{
			if(G.arcs[i][j]==MAXINT) cout<<"0\t";
			else cout<<G.arcs[i][j]<<"\t";
			if(j==G.vexnum-1)cout<<endl;
		}
	}
}
void teaverse(MGraph &G)//��ѯ���о��� 
{
	cout<<"���������Ϣ����:"<<endl;
	for(int i=0;i<G.vexnum;i++)
	cout<<i+1<<"."<<G.vexs[i].name<<":"<<G.vexs[i].info<<endl;
}
void check_scene(MGraph &G)//Ѱ· 
{
	int v1,v2;
	cout<<"��У������:"<<endl;
	for(int i=0;i<G.vexnum;i++)
	cout<<i+1<<"."<<G.vexs[i].name<<endl;
	cout<<"����������λ��(1-"<<G.vexnum<<")"<<endl;
	cin>>v1;
	cout<<"����������Ŀ�ĵ�(1-"<<G.vexnum<<")"<<endl;
	cin>>v2;
	ShortestPath_DIJ(G,v1,v2);
}
void add_scene(MGraph &G)//���Ӿ��� 
{
	G.vexnum++;
	cout<<"�����뾰�������Լ�����Ϣ:"<<endl; 
	cin>>G.vexs[G.vexnum-1].name>>G.vexs[G.vexnum-1].info;
	for(int i=0;i<G.vexnum;i++)
	{
		G.arcs[G.vexnum-1][i] = MAXINT;
		G.arcs[i][G.vexnum-1] = MAXINT;
	}
	freshen(G);
}
void add_road(MGraph &G)//����·�� 
{
	int v1,v2,l;
	cout<<"������·�����˵ľ���(1-"<<G.vexnum<<")�Լ�����:"<<endl;
	cin>>v1>>v2>>l;
	v1--;
	v2--;
	G.arcs[v1][v2]=G.arcs[v2][v1]=l;
	G.arcnum++;
	freshen(G);
}
void correct_scene(MGraph &G)//�޸ľ��㼰��Ϣ 
{
	int v;
	cout<<"��������Ҫ�޸ĵľ���(1-"<<G.vexnum<<"):"<<endl;
	cin>>v;
	cout<<"�����뾰�������Լ�����Ϣ:"<<endl;
	cin>>G.vexs[v-1].name>>G.vexs[v-1].info;
	freshen(G);
}
int main()
{
	MGraph G;
	int operater;
	freopen("graph.txt","r",stdin);
	read_in(G);
	cout<<"****************************��ӭ�������Ŵ�ѧ****************************"<<endl;
	cout<<"                        1.��ѯ������Ϣ"<<endl;
	cout<<"                        2.��·��ѯ"<<endl;
	cout<<"                        3.����һ�����㼰�����Ϣ"<<endl;
	cout<<"                        4.�޸�һ������������Ϣ"<<endl;
	cout<<"                        5.����һ���µ�·��"<<endl;
	cout<<"                        6.ɾ��һ������"<<endl;
	cout<<"                        7.ɾ��һ��·��"<<endl;
	cout<<"                        8.�˳�"<<endl;
	cout<<"****************************���Ŵ�ѧ����ϵͳ****************************"<<endl;
	freopen("CON", "r", stdin);
	while(1)
	{
		cout<<"��ѡ����Ҫ�ķ���(1-8)"<<endl;
		cin>>operater;
		switch(operater)
		{
			case 1:teaverse(G);break;
			case 2:check_scene(G);break;
			case 3:add_scene(G);break;
			case 4:correct_scene(G);break;
			case 5:add_road(G);break;
			case 6:delete_scene(G);break;
			case 7:delete_road(G);break;
			case 8:return 0;break;
		}
	}
}
