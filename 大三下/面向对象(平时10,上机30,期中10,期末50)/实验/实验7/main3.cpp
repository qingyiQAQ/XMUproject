#include <iostream>
using namespace std;
class Time
{
private:
	int hour, minute, second;

public:
	Time(int h, int m, int s) {
		hour = h;
		minute = m;
		second = s;
	}
	void set(int h, int m, int s) {
		hour = h;
		minute = m;
		second = s;
	}
	void increment() {
		int s = hour * 3600 + minute * 60 + second + 1;
		hour = s / 3600 % 24;
		minute = s % 3600 / 60;
		second = s % 60;
	}
	void display() {
		cout << hour << ":" << minute << ":" << second << endl;
	}
	bool equal(Time& other_time) {
		return (hour == other_time.hour) && (minute == other_time.minute) && (second == other_time.second);
	}
	bool less_than(Time& other_time) {
		return (hour * 3600 + minute * 60 + second + 1 < other_time.hour * 3600 + other_time.minute * 60 + other_time.second);
	}
};
class ExtTime :public Time {
private:
	string timezone;
public:
	ExtTime(string tz, int h, int m, int s) :Time(h, m, s) {
		timezone = tz;
	}
};
int main() {
	Time t1(23, 59, 59);
	ExtTime t2("GMT+5", 7, 0, 0);
	t1.increment();
	t1.display();
	t2.increment();
	t2.display();
}