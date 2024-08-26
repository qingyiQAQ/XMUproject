#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
vector<vector<string>> lab;
void print() {
	for (int i = 0; i < lab.size(); i++) {
		cout << i + 1 << " ";
		for (int j = 0; j < lab[i].size(); j++) {
			cout << j + 1 << ": ";
			if (lab[i][j] == "")cout << "empty";
			else cout << lab[i][j];
			cout << " ";
		}
		cout << endl;
	}
}
int main() {
	lab = {
		{"","","","",""},
		{"","","","","",""},
		{"","","",""},
		{"","",""}
	};
	string s;
	while (1) {
		cin >> s;
		if (s == "+") {
			string user;
			int a, b;
			cin >> user >> a >> b;
			a--; b--;
			int flag = 0;
			for (int i = 0; i < lab.size(); i++) {
				for (int j = 0; j < lab[i].size(); j++) {
					if (lab[i][j] == user) {
						flag = 1;
					}
				}
			}
			if (a < lab.size() && b < lab[a].size() && lab[a][b] == "" && !flag) {
				lab[a][b] = user;
			}
			else {
				cout << "invalid login" << endl;
			}
		}
		else if (s == "-") {
			string user;
			cin >> user;
			int flag = 0;
			for (int i = 0; i < lab.size(); i++) {
				for (int j = 0; j < lab[i].size(); j++) {
					if (lab[i][j] == user) {
						lab[i][j] = "";
						flag = 1;
					}
				}
			}
			if (flag == 0) {
				cout << "invalid logoff" << endl;
			}
		}
		else if (s == "=") {
			break;
		}
		print();
	}
}