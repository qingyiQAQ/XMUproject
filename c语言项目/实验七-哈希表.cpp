#include<bits/stdc++.h>
using namespace std;
#define HASHSIZE 50//��ϣ����󳤶�
#define NAMELISTSIZE 30//���ϱ���󳤶�
struct Name
{
	char name[100];
	int ascii;//���϶�Ӧ��ascii���
};//���ϱ�ڵ�
struct hashtable
{
	char name[100] = "0";
	int s = 0;//���ҳ���
};//��ϣ��ڵ�
Name NameList[NAMELISTSIZE];//���ϱ�
hashtable Hash[HASHSIZE];//��ϣ��
float ASL = 0.0;//ƽ�����ҳ���
void InsertNamelist(Name NameList[])
{
	cout << "����������30������:"<<endl;
	for (int i = 0; i < NAMELISTSIZE; i++)
		cin >> NameList[i].name;
}//��������
void Hash_name(Name NameList[])
{
	int i, j;
	for (i = 0; i < NAMELISTSIZE; i++)
	{
		for (j = 0; NameList[i].name[j] != '\0'; j++)
			NameList[i].ascii += toascii(NameList[i].name[j]);
	}//�������϶�Ӧascii��
	for (i = 0; i < NAMELISTSIZE; i++)
	{
		int key, s=1;
		key = NameList[i].ascii % (HASHSIZE - 1);//��������������
		while (Hash[key].s != 0)
		{
			key++; s++;
			key = key % (HASHSIZE - 1);
		}//����̽����ɢ�з������ͻ
		for (int j = 0; NameList[i].name[j] != '\0'; j++)
			Hash[key].name[j] = NameList[i].name[j];//�ҵ�λ�ô���
		Hash[key].s = s;
	}
}//��ϣ����
void search()
{
	int c=0;
	char name[100];
	cout << "����������:" << endl;
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
			cout << "δ�ҵ���" << endl;
			return;
		}
		key=key% (HASHSIZE - 1);
	}
	cout << "����λ��Ϊ:" << key+1<<endl;
}//���Ҳ���ô���λ��
void printnamelist()
{
	for (int i = 0; i < NAMELISTSIZE; i++)
		cout << NameList[i].name<<endl;
}//�鿴���ϱ�
void printhash()
{
	cout << "λ��:";
	for (int i = 0; i < HASHSIZE; i++)cout << i<<" ";
	cout << endl;
	cout << "����(0����δ����):";
	for (int i = 0; i < HASHSIZE; i++)
	{
		cout << Hash[i].name << " ";
	}
	cout << endl;
}//�鿴��ϣ��
void asl()
{
	for (int i = 0; i < HASHSIZE; i++)
	{
		if (Hash[i].s != 0)ASL += Hash[i].s;
	}
	ASL = ASL / NAMELISTSIZE;
	cout << "ƽ�����ҳ���ASL=" << ASL<<endl;
}
int main()
{
	int a;
	InsertNamelist(NameList); 
	Hash_name (NameList);
	cout << "1.�鿴���ϱ�" << endl;
	cout << "2.�鿴��ϣ��" << endl;
	cout << "3.�������ϲ�ѯ����λ��" << endl;
	cout << "4.��ʾƽ�����ҳ���" << endl;
	cout << "5.�˳�" << endl;
	while (1)
	{
		cout << "��������Ҫִ�е�ָ��:"<<endl;
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
