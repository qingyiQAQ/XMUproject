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

	string get_name() {
		return name;
	}

private:
	string name;
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
				if (computers[i][j].get_name() == name) {
					return 1;
				}
			}
		}
		return 0;
	}

	bool login(string name, int x, int y) {
		if (x > computers.size() || y > computers[x-1].size() || is_user_exist(name) || computers[x - 1][y - 1].get_name() != "empty") {
			cout << "invalid login" << endl;
			return 0;
		}
		User user(name);
		computers[x - 1][y - 1] = user;
		return 1;
	}

	bool logout(string name) {
		for (int i = 0; i < computers.size(); i++) {
			for (int j = 0; j < computers[i].size(); j++) {
				if (computers[i][j].get_name() == name) {
					User emptyuser;
					computers[i][j] = emptyuser;
					return 1;
				}
			}
		}
		cout << "invalid logoff" << endl;
		return 0;
	}

	void print() {
	for (int i = 0; i < computers.size(); i++) {
		cout << i + 1 << " ";
		for (int j = 0; j < computers[i].size(); j++) {
			cout << j + 1 << ": " << computers[i][j].get_name() << " ";
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
			computerLab.login(name, x, y);
		}
		else if (s == "-") {
			string name;
			cin >> name;
			computerLab.logout(name);
		}
		else if (s == "=") {
			break;
		}
		computerLab.print();
	}
}