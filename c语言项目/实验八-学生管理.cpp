#include<bits/stdc++.h>
using namespace std;
struct Student
{
	int num;
	char name[100];
	int score;
};
int n;
Student student[1000];
void Start(Student S[])
{
	cout << "������ѧ������:";
	cin >> n;
	cout << "����������ѧ����Ϣ(ѧ�� ���� �ɼ�):" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> S[i].num >> S[i].name >> S[i].score;
	}
}//��ѧ����������ѧ����Ϣ
void Gothrough(Student S[])
{
	cout << "ѧ��\t����\t�ɼ�\t\n";
	for (int i = 0; i < n; i++)
	{
		cout << S[i].num <<"\t" << S[i].name <<"\t" << S[i].score<<endl;
	}
}//�鿴����ѧ����Ϣ
void Insert(Student S[])
{
	Student x;
	int po;
	n++;
	cout << "�����������ѧ����Ϣ(ѧ�� ���� �ɼ�):" << endl;
	cin >> x.num >> x.name >> x.score;
	cout << "���������λ��(1-" << n << "):";
	cin >> po;
	for (int i = n; i >= po; i--)
	{
		S[i] = S[i - 1];
	}
	S[po - 1].num = x.num;
	for(int i=0;x.name[i]!='\0';i++)
	S[po - 1].name[i] = x.name[i];
	S[po - 1].score = x.score;
}//����һ��ѧ��������λ��
void Delete(Student S[])
{
	int po;
	cout << "������Ҫɾ����ѧ��λ��(1-" << n << "):";
	cin >> po;
	for (int i = po-1; i < n; i++) 
	{
		S[i] = S[i+1];
	}
	n--;
}//ɾ��һ������λ�õ�ѧ��
int name_ascii(char name[])
{
	int a=0;
	for (int i = 0; name[i] != '\0'; i++)
	{
		a += toascii(name[i]);
	}
	return a;
}//������ת��Ϊascii����ڱȽ�
void Straight_Insertion_Sort(Student S[])
{
	Student x;
	int i, j;
	for (i = 1; i < n; i++)
	{
		if (name_ascii(S[i].name) < name_ascii(S[i-1].name))
		{
			x = S[i];
			for (j = i-1; j >= 0; j--)
			{
				if (name_ascii(S[j].name) > name_ascii(x.name))
				{
					S[j+1] = S[j];
				}
				else break;
			}
			S[j+1] = x;
		}
	}
}//ֱ�Ӳ�������
int Partition(Student L[],int low, int  high)
{
	Student x;
	int pivotkey;
	x = L[low];   pivotkey = L[low].num;
	while (low < high)
	{
		while (low < high && L[high].num >= pivotkey)  --high;
		L[low] = L[high];
		while (low < high && L[low].num <= pivotkey)  ++low;
		L[high] = L[low];
	}
	L[low] = x;
	return low;
}//��������
void QSort(Student L[], int low, int  high)
{
	int pivotloc;
	if (low < high)
	{
		pivotloc = Partition(L, low, high);
		QSort(L, low, pivotloc - 1);
		QSort(L, pivotloc + 1, high);
	}
}//��������
void Quick_Sort(Student L[])
{
	QSort(L, 0, n-1);
}//��������
int B_Search_recursion(Student L[], int low, int high,char name[])
{
	if (low > high)return -1;
	int mid = (low + high) / 2;
	if (strcmp(L[mid].name, name) == 0)return mid;
	else
	{
		if (name_ascii(name) < name_ascii(L[mid].name))B_Search_recursion(L, low, mid - 1, name);
		else B_Search_recursion(L, mid+1 ,high, name);
	}
}//���������۰���ң��ݹ飩
void Binary_Search_recursion(Student L[])
{
	char name[100];
	cout << "��������Ҫ���ҵ�ѧ������:"<<endl;
	cin >> name;
	Straight_Insertion_Sort(student);
	if (B_Search_recursion(L, 0, n - 1, name) == -1)cout << "δ�ҵ���"<<endl;
	else
	{
		cout << "��ѧ��Ϊ:" << L[B_Search_recursion(L, 0, n - 1, name)].num << endl;
		cout << "��ɼ�Ϊ:" << L[B_Search_recursion(L, 0, n - 1, name)].score << endl;
	}
}//���������۰���ң��ݹ飩
int B_Search(Student L[], int low, int high, int num)
{
	int mid;
	while (low <= high)     
	{
		mid = (low + high) / 2;    
		if (L[mid].num == num)
			return mid;         
		else if (num < L[mid].num)
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}
	return -1;
}//����ѧ���۰���ң��ǵݹ飩
void Binary_Search(Student L[])
{
	int num;
	cout << "��������Ҫ���ҵ�ѧ��ѧ��:" << endl;
	cin >> num;
	Quick_Sort(student);
	if (B_Search(L, 0, n - 1, num) == -1)cout << "δ�ҵ���"<<endl;
	else
	{
		cout << "������Ϊ:" << L[B_Search(L, 0, n - 1, num)].name << endl;
		cout << "��ɼ�Ϊ:" << L[B_Search(L, 0, n - 1, num)].score << endl;
	}
}//����ѧ���۰���ң��ǵݹ�
int main()
{
	cout << "                                   ѧ������ϵͳ" << endl;
	cout << "--------------------------------------------------------------------------------------------------------------------------"<<endl;
	cout << "1.����ָ��ѧ���������������ѧ����Ϣ" << endl;
	cout << "2.�����ʾѧ����������ѧ���������Ϣ" << endl;
	cout << "3.����һ��ѧ����Ϣ�����뵽����ָ����λ��" << endl;
	cout << "4.ɾ��ָ��λ�õ�ѧ����¼" << endl;
	cout << "5.ͳ�Ʊ���ѧ������" << endl;
	cout << "6.����ֱ�Ӳ���������������������" << endl;
	cout << "7.���ÿ���������ѧ�Ž�������" << endl;
	cout << "8.�������������۰���ң�Ҫ��ʹ�õݹ��㷨ʵ�֣��ɹ����ش�ѧ����ѧ�źͳɼ�" << endl;
	cout << "9.����ѧ�Ž����۰���ң�Ҫ��ʹ�÷ǵݹ��㷨ʵ�֣��ɹ����ش�ѧ���������ͳɼ�" << endl;
	cout << "10.�˳�����" << endl;
	cout << "--------------------------------------------------------------------------------------------------------------------------"<<endl;
	while (1)
	{
		int a;
		cout << "������Ҫִ�еĳ���(1-10):";
		cin >> a;
		switch (a)
		{
		case 1:Start(student); break;
		case 2:Gothrough(student); break;
		case 3:Insert(student); break;
		case 4:Delete(student); break;
		case 5:cout << "ѧ������Ϊ:" << n; break;
		case 6:Straight_Insertion_Sort(student); break;
		case 7:Quick_Sort(student); break;
		case 8:Binary_Search_recursion(student); break;
		case 9:Binary_Search(student); break;
		case 10:return 0; break;
		}
	}
}
