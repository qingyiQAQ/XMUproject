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
	cout << "请输入学生个数:";
	cin >> n;
	cout << "请依次输入学生信息(学号 姓名 成绩):" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> S[i].num >> S[i].name >> S[i].score;
	}
}//按学生个数输入学生信息
void Gothrough(Student S[])
{
	cout << "学号\t姓名\t成绩\t\n";
	for (int i = 0; i < n; i++)
	{
		cout << S[i].num <<"\t" << S[i].name <<"\t" << S[i].score<<endl;
	}
}//查看所有学生信息
void Insert(Student S[])
{
	Student x;
	int po;
	n++;
	cout << "请依次输入该学生信息(学号 姓名 成绩):" << endl;
	cin >> x.num >> x.name >> x.score;
	cout << "请输入插入位置(1-" << n << "):";
	cin >> po;
	for (int i = n; i >= po; i--)
	{
		S[i] = S[i - 1];
	}
	S[po - 1].num = x.num;
	for(int i=0;x.name[i]!='\0';i++)
	S[po - 1].name[i] = x.name[i];
	S[po - 1].score = x.score;
}//插入一个学生到任意位置
void Delete(Student S[])
{
	int po;
	cout << "请输入要删除的学生位置(1-" << n << "):";
	cin >> po;
	for (int i = po-1; i < n; i++) 
	{
		S[i] = S[i+1];
	}
	n--;
}//删除一个任意位置的学生
int name_ascii(char name[])
{
	int a=0;
	for (int i = 0; name[i] != '\0'; i++)
	{
		a += toascii(name[i]);
	}
	return a;
}//将姓名转化为ascii码便于比较
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
}//直接插入排序
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
}//快速排序
void QSort(Student L[], int low, int  high)
{
	int pivotloc;
	if (low < high)
	{
		pivotloc = Partition(L, low, high);
		QSort(L, low, pivotloc - 1);
		QSort(L, pivotloc + 1, high);
	}
}//快速排序
void Quick_Sort(Student L[])
{
	QSort(L, 0, n-1);
}//快速排序
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
}//根据姓名折半查找（递归）
void Binary_Search_recursion(Student L[])
{
	char name[100];
	cout << "请输入需要查找的学生姓名:"<<endl;
	cin >> name;
	Straight_Insertion_Sort(student);
	if (B_Search_recursion(L, 0, n - 1, name) == -1)cout << "未找到！"<<endl;
	else
	{
		cout << "其学号为:" << L[B_Search_recursion(L, 0, n - 1, name)].num << endl;
		cout << "其成绩为:" << L[B_Search_recursion(L, 0, n - 1, name)].score << endl;
	}
}//根据姓名折半查找（递归）
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
}//根据学号折半查找（非递归）
void Binary_Search(Student L[])
{
	int num;
	cout << "请输入需要查找的学生学号:" << endl;
	cin >> num;
	Quick_Sort(student);
	if (B_Search(L, 0, n - 1, num) == -1)cout << "未找到！"<<endl;
	else
	{
		cout << "其姓名为:" << L[B_Search(L, 0, n - 1, num)].name << endl;
		cout << "其成绩为:" << L[B_Search(L, 0, n - 1, num)].score << endl;
	}
}//根据学号折半查找（非递归
int main()
{
	cout << "                                   学生管理系统" << endl;
	cout << "--------------------------------------------------------------------------------------------------------------------------"<<endl;
	cout << "1.根据指定学生个数，逐个输入学生信息" << endl;
	cout << "2.逐个显示学生表中所有学生的相关信息" << endl;
	cout << "3.给定一个学生信息，插入到表中指定的位置" << endl;
	cout << "4.删除指定位置的学生记录" << endl;
	cout << "5.统计表中学生个数" << endl;
	cout << "6.利用直接插入排序按照姓名进行排序" << endl;
	cout << "7.利用快速排序按照学号进行排序" << endl;
	cout << "8.根据姓名进行折半查找，要求使用递归算法实现，成功返回此学生的学号和成绩" << endl;
	cout << "9.根据学号进行折半查找，要求使用非递归算法实现，成功返回此学生的姓名和成绩" << endl;
	cout << "10.退出程序" << endl;
	cout << "--------------------------------------------------------------------------------------------------------------------------"<<endl;
	while (1)
	{
		int a;
		cout << "请输入要执行的程序(1-10):";
		cin >> a;
		switch (a)
		{
		case 1:Start(student); break;
		case 2:Gothrough(student); break;
		case 3:Insert(student); break;
		case 4:Delete(student); break;
		case 5:cout << "学生个数为:" << n; break;
		case 6:Straight_Insertion_Sort(student); break;
		case 7:Quick_Sort(student); break;
		case 8:Binary_Search_recursion(student); break;
		case 9:Binary_Search(student); break;
		case 10:return 0; break;
		}
	}
}
