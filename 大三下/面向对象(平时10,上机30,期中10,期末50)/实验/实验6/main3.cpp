#include<iostream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;
class Date {
public:
	Date() {
		this->month = 0;
		this->day = 0;
		this->year = 0;
	}
	Date(int day, int month, int year) {
		this->month = month;
		this->day = day;
		this->year = year;
	}
	Date(string s) {
		istringstream iss(s);
		string token;
		getline(iss, token, '/');
		day = stoi(token);
		getline(iss, token, '/');
		month = stoi(token);
		getline(iss, token);
		year = stoi(token);
	}
	string toString() {
		string s;
		s += static_cast<char>(day / 10 + '0');
		s += static_cast<char>(day % 10 + '0');
		s += "/";
		s += static_cast<char>(month / 10 + '0');
		s += static_cast<char>(month % 10 + '0');
		s += "/";
		s += static_cast<char>(year / 1000 + '0');
		s += static_cast<char>(year / 100 % 10 + '0');
		s += static_cast<char>(year / 10 % 10 + '0');
		s += static_cast<char>(year % 10 + '0');
		return s;
	}
	int culDays(Date date) {
		int months[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		int count = 0;
		if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))months[1] = 29;
		else months[1] = 28;
		count += months[month - 1] - day;
		for (int i = month; i < 12; i++) {
			count += months[i];
		}
		for (int i = year + 1; i < date.year; i++) {
			if ((i % 400 == 0) || ((i % 4 == 0) && (i % 100 != 0)))count += 366;
			else count += 365;
		}
		if ((date.year % 400 == 0) || ((date.year % 4 == 0) && (date.year % 100 != 0)))months[1] = 29;
		else months[1] = 28;
		for (int i = 0; i < date.month - 1; i++) {
			count += months[i];
		}
		count += date.day;
		return count;
	}
private:
	int month, day, year;
};
class User
{
public:
	User() {
		this->name = "empty";
		this->date = Date();
	}

	User(string name, Date date) {
		this->name = name;
		this->date = date;
	}

	virtual int culPrice(Date logoffdate) {
		return 0;
	}

protected:
	string name;
	Date date;
	friend class ComputerLab;
};

class Student :public User {
public:

	Student(string name, Date date) {
		this->name = name;
		this->date = date;
	}

	int culPrice(Date logoffdate) override{
		int days = date.culDays(logoffdate);
		if (days <= 14)return 0;
		else return days - 14;
	}

};

class Staff :public User {
public:

	Staff(string name, Date date) {
		this->name = name;
		this->date = date;
	}

	int culPrice(Date logoffdate) override{
		int days = date.culDays(logoffdate);
		if (days <= 30)return 2 * days;
		else return 2 * 30 + 4 * (days - 30);
	}
};

struct StaInReq {
	Staff* userPointer;
	int labNum;
	int stationNum;
	bool flag;
};

struct StuInReq {
	Student* userPointer;
	int labNum;
	int stationNum;
	bool flag;
};

struct StaOffReq {
	Staff* userPointer;
	bool flag;
};

struct StuOffReq {
	Student* userPointer;
	bool flag;
};

class ComputerLab
{
public:
	ComputerLab() {
		computers.resize(4);
		computers[0].resize(3);
		computers[1].resize(4);
		computers[2].resize(5);
		computers[3].resize(6);
	}

	bool is_user_exist(string name) {
		for (int i = 0; i < computers.size(); i++) {
			for (int j = 0; j < computers[i].size(); j++) {
				if (computers[i][j].name == name) {
					return 1;
				}
			}
		}
		return 0;
	}

	bool login(User user, int x, int y) {
		if (x > computers.size() || y > computers[x - 1].size() || is_user_exist(user.name) || computers[x - 1][y - 1].name != "empty") {
			cout << "invalid login" << endl;
			return 0;
		}
		computers[x - 1][y - 1] = user;
		return 1;
	}

	void operator+(StuInReq& r) {
		r.flag = login(*r.userPointer, r.labNum, r.stationNum);
	}

	void operator+(StaInReq& r) {
		r.flag = login(*r.userPointer, r.labNum, r.stationNum);
	}

	bool logout(User user) {
		for (int i = 0; i < computers.size(); i++) {
			for (int j = 0; j < computers[i].size(); j++) {
				if (computers[i][j].name == user.name) {
					if (computers[i][j].name[0] >= '0' && computers[i][j].name[0] <= '9')
						cout << computers[i][j].name << " log off, " <<
						"time: " << computers[i][j].date.culDays(user.date) << "days, " <<
						"price: " << Staff(computers[i][j].name, computers[i][j].date).culPrice(user.date) << endl;
					else
						cout << computers[i][j].name << " log off, " <<
						"time: " << computers[i][j].date.culDays(user.date) << " days, " <<
						"price: " << Student(computers[i][j].name, computers[i][j].date).culPrice(user.date) << endl;
					computers[i][j] = User();
					return 1;
				}
			}
		}
		cout << "invalid logoff" << endl;
		return 0;
	}

	void operator-(StaOffReq& r) {
		r.flag = logout(*r.userPointer);
	}

	void operator-(StuOffReq& r) {
		r.flag = logout(*r.userPointer);
	}

	void print() {
		for (int i = 0; i < computers.size(); i++) {
			cout << i + 1 << " ";
			for (int j = 0; j < computers[i].size(); j++) {
				cout << j + 1 << ": " << computers[i][j].name << " ";
				if (computers[i][j].name != "empty") cout << computers[i][j].date.toString() << " ";
			}
			cout << endl;
		}
	}

private:
	vector<vector<User>> computers;
};


int main() {
	ComputerLab computerLab;
	while (1) {
		string s;
		cin >> s;
		if (s == "+") {
			string name, date;
			int x, y;
			cin >> name >> x >> y >> date;
			if (name[0] >= '0' && name[0] <= '9') {
				StaInReq r = { new Staff(name,Date(date)), x, y };
				computerLab + r;
			}
			else {
				StuInReq r = { new Student(name,Date(date)), x, y };
				computerLab + r;
			}
		}
		else if (s == "-") {
			string name, date;
			cin >> name >> date;
			StaOffReq r = { new Staff(name,Date(date)) };
			computerLab - r;
		}
		else if (s == "=") {
			break;
		}
		computerLab.print();
	}
}