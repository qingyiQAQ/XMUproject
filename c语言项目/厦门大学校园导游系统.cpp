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
int LocateVex(MGraph &G,char v[])//从景点名获得编号
{
	int i;
	for(i=0;i<G.vexnum;i++)
	{
		if(strcmp(G.vexs[i].name,v)==0)return i;
	}
	if(i==G.vexnum) return -1;
}
void read_in(MGraph &G)//读入景点文件 
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
void freshen(MGraph &G)//文件刷新 
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
void ShortestPath_DIJ(MGraph &G, int v1 ,int v2)//最短路径算法 
{
	v1--;v2--;
    //用Dijkstra算法求有向网G的v0顶点到其余顶点的最短路径 
    int n=G.vexnum;//n为G中顶点的个数 
	int S[100],D[100],Path[100]; 
	int v,w;                   		
    for(v = 0; v<n; ++v)
	{             	//n个顶点依次初始化 
    	S[v] = 0;                  	//S初始为空集 
    	D[v] = G.arcs[v1][v];           	//将v0到各个终点的最短路径长度初始化 
    	if(D[v]< MAXINT)  Path [v]=v1; //v0和v之间有弧，将v的前驱置为v0 
    	else Path [v]=-1;               	//如果v0和v之间无弧，则将v的前驱置为-1 
    }//for 
    S[v1]=1;                    	//将v0加入S 
    D[v1]=0;
	/*―开始主循环，每次求得v0到某个顶点v的最短路径，将v加到S集―*/ 
    for(int i=1;i<n; ++i)
	{               	//对其余n?1个顶点，依次进行计算 
    	int min= MAXINT;
        for(w=0;w<n; ++w)
		{
			if(!S[w]&&D[w]<min)  
            {
				v=w;
				min=D[w];
			}         	//选择一条当前的最短路径，终点为v 
		}
        S[v]=1;                   		//将v加入S 
        for(w=0;w<n; ++w)
		{//更新从v0出发到集合V?S上所有顶点的最短路径长度
        	if(!S[w]&&(D[v]+G.arcs[v][w]<D[w]))
			{ 
        	     D[w]=D[v]+G.arcs[v][w];   	//更新D[w] 
        	     Path [w]=v;              		//更改w的前驱为v 
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
	if(D[v2]==MAXINT)cout<<"无法抵达！"<<endl; 
	else
	{
		cout<<"路径是:";
		for(int j=i-1;j>=0;j--)
		{
			cout<<G.vexs[a[j]].name;
			if(j)cout<<"->";
			else cout<<endl; 
		}
		cout<<"最短路径是:"<<D[v2]<<endl;
	}
}//ShortestPath_DIJ
void delete_scene(MGraph &G)//删除景点 
{
	int v;
	cout<<"请输入需要删除的景点(1-"<<G.vexnum<<"):"<<endl;
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
	cout<<"成功删除！"<<endl; 
}
void delete_road(MGraph &G)//删除路径 
{
	int v1,v2; 
	cout<<"请输入需要删除的路径两端的景点(1-"<<G.vexnum<<"):"<<endl;
	cin>>v1>>v2;
	if(G.arcs[v1-1][v2-1]==MAXINT)cout<<"未找到该路径!"<<endl;
	else
	{
		G.arcs[v1-1][v2-1]=MAXINT;
		G.arcs[v2-1][v1-1]=MAXINT;
		cout<<"成功删除！"<<endl;
		G.arcnum--;
		freshen(G);
	}
}
void road(MGraph &G)//查看所有路径 
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
void teaverse(MGraph &G)//查询所有景点 
{
	cout<<"景点相关信息如下:"<<endl;
	for(int i=0;i<G.vexnum;i++)
	cout<<i+1<<"."<<G.vexs[i].name<<":"<<G.vexs[i].info<<endl;
}
void check_scene(MGraph &G)//寻路 
{
	int v1,v2;
	cout<<"本校景点有:"<<endl;
	for(int i=0;i<G.vexnum;i++)
	cout<<i+1<<"."<<G.vexs[i].name<<endl;
	cout<<"请输入您的位置(1-"<<G.vexnum<<")"<<endl;
	cin>>v1;
	cout<<"请输入您的目的地(1-"<<G.vexnum<<")"<<endl;
	cin>>v2;
	ShortestPath_DIJ(G,v1,v2);
}
void add_scene(MGraph &G)//增加景点 
{
	G.vexnum++;
	cout<<"请输入景点名称以及其信息:"<<endl; 
	cin>>G.vexs[G.vexnum-1].name>>G.vexs[G.vexnum-1].info;
	for(int i=0;i<G.vexnum;i++)
	{
		G.arcs[G.vexnum-1][i] = MAXINT;
		G.arcs[i][G.vexnum-1] = MAXINT;
	}
	freshen(G);
}
void add_road(MGraph &G)//增加路径 
{
	int v1,v2,l;
	cout<<"请输入路径两端的景点(1-"<<G.vexnum<<")以及距离:"<<endl;
	cin>>v1>>v2>>l;
	v1--;
	v2--;
	G.arcs[v1][v2]=G.arcs[v2][v1]=l;
	G.arcnum++;
	freshen(G);
}
void correct_scene(MGraph &G)//修改景点及信息 
{
	int v;
	cout<<"请输入需要修改的景点(1-"<<G.vexnum<<"):"<<endl;
	cin>>v;
	cout<<"请输入景点名称以及其信息:"<<endl;
	cin>>G.vexs[v-1].name>>G.vexs[v-1].info;
	freshen(G);
}
int main()
{
	MGraph G;
	int operater;
	freopen("graph.txt","r",stdin);
	read_in(G);
	cout<<"****************************欢迎来到厦门大学****************************"<<endl;
	cout<<"                        1.查询景点信息"<<endl;
	cout<<"                        2.问路查询"<<endl;
	cout<<"                        3.增加一个景点及相关信息"<<endl;
	cout<<"                        4.修改一个景点的相关信息"<<endl;
	cout<<"                        5.增加一条新的路径"<<endl;
	cout<<"                        6.删除一个景点"<<endl;
	cout<<"                        7.删除一个路径"<<endl;
	cout<<"                        8.退出"<<endl;
	cout<<"****************************厦门大学导游系统****************************"<<endl;
	freopen("CON", "r", stdin);
	while(1)
	{
		cout<<"请选择需要的服务(1-8)"<<endl;
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
