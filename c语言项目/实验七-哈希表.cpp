#include<bits/stdc++.h>
using namespace std;
#define HASHSIZE 50//哈希表最大长度
#define NAMELISTSIZE 30//姓氏表最大长度
struct Name
{
	char name[100];
	int ascii;//姓氏对应的ascii码和
};//姓氏表节点
struct hashtable
{
	char name[100] = "0";
	int s = 0;//查找长度
};//哈希表节点
Name NameList[NAMELISTSIZE];//姓氏表
hashtable Hash[HASHSIZE];//哈希表
float ASL = 0.0;//平均查找长度
void InsertNamelist(Name NameList[])
{
	cout << "请依次输入30个姓氏:"<<endl;
	for (int i = 0; i < NAMELISTSIZE; i++)
		cin >> NameList[i].name;
}//输入姓氏
void Hash_name(Name NameList[])
{
	int i, j;
	for (i = 0; i < NAMELISTSIZE; i++)
	{
		for (j = 0; NameList[i].name[j] != '\0'; j++)
			NameList[i].ascii += toascii(NameList[i].name[j]);
	}//计算姓氏对应ascii码
	for (i = 0; i < NAMELISTSIZE; i++)
	{
		int key, s=1;
		key = NameList[i].ascii % (HASHSIZE - 1);//除留余数法建表
		while (Hash[key].s != 0)
		{
			key++; s++;
			key = key % (HASHSIZE - 1);
		}//线性探测再散列法处理冲突
		for (int j = 0; NameList[i].name[j] != '\0'; j++)
			Hash[key].name[j] = NameList[i].name[j];//找到位置存入
		Hash[key].s = s;
	}
}//哈希函数
void search()
{
	int c=0;
	char name[100];
	cout << "请输入姓氏:" << endl;
	cin >> name;
	int key, ascii=0;
	for (int i = 0; name[i] != '\0'; i++)
	{
		ascii += toascii(name[i]);
	}
	key=ascii% (HASHSIZE - 1);
	while (strcmp(Hash[key].name , name)!=0)
	{
		key++;
		c++;
		if (c > HASHSIZE)
		{
			cout << "未找到！" << endl;
			return;
		}
		key=key% (HASHSIZE - 1);
	}
	cout << "储存位置为:" << key+1<<endl;
}//查找并获得储存位置
void printnamelist()
{
	for (int i = 0; i < NAMELISTSIZE; i++)
		cout << NameList[i].name<<endl;
}//查看姓氏表
void printhash()
{
	cout << "位置:";
	for (int i = 0; i < HASHSIZE; i++)cout << i<<" ";
	cout << endl;
	cout << "姓氏(0代表未储存):";
	for (int i = 0; i < HASHSIZE; i++)
	{
		cout << Hash[i].name << " ";
	}
	cout << endl;
}//查看哈希表
void asl()
{
	for (int i = 0; i < HASHSIZE; i++)
	{
		if (Hash[i].s != 0)ASL += Hash[i].s;
	}
	ASL = ASL / NAMELISTSIZE;
	cout << "平均查找长度ASL=" << ASL<<endl;
}
int main()
{
	int a;
	InsertNamelist(NameList); 
	Hash_name (NameList);
	cout << "1.查看姓氏表" << endl;
	cout << "2.查看哈希表" << endl;
	cout << "3.根据姓氏查询储存位置" << endl;
	cout << "4.显示平均查找长度" << endl;
	cout << "5.退出" << endl;
	while (1)
	{
		cout << "请输入需要执行的指令:"<<endl;
		cin >> a;
		switch (a)
		{
		case 1:printnamelist(); break;
		case 2:printhash(); break;
		case 3:search(); break;
		case 4:asl(); break;
		case 5:return 0; break;
		}
	}
}
