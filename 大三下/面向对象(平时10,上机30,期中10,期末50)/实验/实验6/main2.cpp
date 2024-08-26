#include<iostream>
#include<vector>
#include<string>
using namespace std;
class User
{
public:
	User() {
		this->name = "empty";
	}

	User(string name) {
		this->name = name;
	}

	//string get_name() {
	//	return name;
	//}

private:
	string name;
	friend class ComputerLab;
};
// loginReq 表示登录请求的类型 
struct loginReq {
	User* userPointer; //指向当前请求登录的用户对象 
	int labNum; //用户请求登录的 lab 的 number 
	int stationNum; //用户请求登录的 station 的 number 
	bool flag; //flag=true 表示登录成功，flag=false 登录失败 
};
// logoffReq 表示注销请求的类型 
struct logoffReq {
	User* userPointer; //指向当前请求注销的用户对象 
	bool flag; //flag=true 表示注销成功，flag=false 注销失败 
};
class ComputerLab
{
public:
	ComputerLab() {
		computers.resize(4);
		computers[0].resize(5);
		computers[1].resize(6);
		computers[2].resize(4);
		computers[3].resize(3);
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

	void operator+(loginReq &r) {
		r.flag = login(*r.userPointer, r.labNum, r.stationNum);
	}

	bool logout(User user) {
		for (int i = 0; i < computers.size(); i++) {
			for (int j = 0; j < computers[i].size(); j++) {
				if (computers[i][j].name == user.name) {
					computers[i][j] = User();
					return 1;
				}
			}
		}
		cout << "invalid logoff" << endl;
		return 0;
	}

	void operator-(logoffReq& r) {
		r.flag = logout(*r.userPointer);
	}

	void print() {
		for (int i = 0; i < computers.size(); i++) {
			cout << i + 1 << " ";
			for (int j = 0; j < computers[i].size(); j++) {
				cout << j + 1 << ": " << computers[i][j].name << " ";
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
			string name;
			int x, y;
			cin >> name >> x >> y;
			loginReq r = { new User(name), x, y };
			//computerLab.login(name, x, y);
			computerLab + r;
		}
		else if (s == "-") {
			string name;
			cin >> name;
			logoffReq r = { new User(name) };
			//computerLab.logout(name);
			computerLab - r;
		}
		else if (s == "=") {
			break;
		}
		computerLab.print();
	}
}