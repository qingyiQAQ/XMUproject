#include<cstring>
#include<cstdlib>
#include<iostream>
using namespace std;
class String {
	char* str;
public:
	String() {
		str = NULL;
	}
	String(const char* p) {
		str = new char[strlen(p) + 1];
		strcpy(str, p);
	}
	~String() {
		delete[]str;
		str = NULL;
	}
	int length() {
		return strlen(str);
	}
	char* get_str() {
		return str;
	}
	char& char_at(int i) {
		if (i < 0 || i >= strlen(str)) {
			cerr << "³¬³ö×Ö·û´®·¶Î§!\n";
			exit(-1);
		}
		return str[i];
	}
	bool is_substring(const char* p) {
		for (int i = 0; i <= strlen(str) - strlen(p); i++) {
			if (strncmp(p, str + i, strlen(p)) == 0)return true;
		}
		return false;
	}
	bool is_substring(const String& s) {
		return is_substring(s.str);
	}
	String substring(int start, int length) {
		char* s = new char[length + 1];
		strncpy(s, str + start, length);
		s[length] = '\0';
		String sstr(s);
		delete[] s;
		return sstr;
	}
	int find_replace_str(const char* find_str, const char* replace_str) {
		int count = 0;
		char* p = str;
		while (*p != '\0') {
			if (strncmp(p, find_str, strlen(find_str)) == 0) {
				count++;
				p += strlen(find_str);
			}
			else p++;
		}
		if (count == 0)return 0;
		char* newstr = new char[strlen(str) - count * strlen(find_str) + count * strlen(replace_str) + 1];
		p = str;
		char* q = newstr;
		while (*p != '\0') {
			if (strncmp(p, find_str, strlen(find_str)) == 0) {
				strcpy(q, replace_str);
				q += strlen(replace_str);
				p += strlen(find_str);
			}
			else {
				*q = *p;
				p++;
				q++;
			}
		}
		delete[]str;
		str = newstr;
		return count;
	}
	void remove_spaces() {
		find_replace_str(" ", "");
	}
	int to_int() {
		int count = 0;
		for (int i = 0; i < strlen(str); i++) {
			count *= 10;
			count += str[i] - '0';
		}
		return count;
	}
	void to_lower_case() {
		for (int i = 0; i < strlen(str); i++) {
			if (str[i] >= 'A' && str[i] <= 'Z') {
				str[i] -= 'A' - 'a';
			}
		}
	}
};
int main() {
	String s1("171727"), s2("717"), s3("ASbUVw");
	cout << s1.is_substring("727") << endl;
	cout << s1.is_substring(s2) << endl;
	cout << s1.substring(0, 3).get_str() << endl;
	cout << s1.find_replace_str("7", " ") << endl;
	cout << s1.get_str() << endl;
	s1.remove_spaces();
	cout << s1.get_str() << endl;
	cout << s1.to_int() << endl;
	s3.to_lower_case();
	cout << s3.get_str() << endl;
}