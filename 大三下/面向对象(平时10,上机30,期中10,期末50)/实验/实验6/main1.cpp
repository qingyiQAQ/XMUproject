#include<iostream>
using namespace std;
class Time
{
private:
	int hour, minute, second;

public:
	Time(int hour, int minute, int second) {
		this->hour = hour;
		this->minute = minute;
		this->second = second;
	}
	void display() {
		cout << hour << ":" << minute << ":" << second << endl;
	}
	int toSecond()const{
		return hour * 3600 + minute * 60 + second;
	}
	Time toTime(int s)const {
		s = ((s % 86400) + 86400) % 86400;
		return Time(
			s / 3600,
			s % 3600 / 60,
			s % 60
		);
	}
	bool operator ==(const Time& t)const {
		return (hour == t.hour) && (minute == t.minute) && (second == t.second);
	}
	bool operator !=(const Time& t)const {
		return !(*this == t);
	}
	bool operator >(const Time& t)const {
		return toSecond() > t.toSecond();
	}
	bool operator >=(const Time& t)const {
		return *this > t || *this == t;
	}
	bool operator <(const Time& t)const {
		return !(*this > t) && (*this != t);
	}
	bool operator <=(const Time& t)const {
		return !(*this > t);
	}
	Time operator +=(int s)const {
		return toTime(toSecond() + s);
	}
	Time operator -=(int s)const {
		return toTime(toSecond() - s);
	}
	Time operator ++()const {
		return *this += 1;
	}
	Time operator --()const {
		return *this -= 1;
	}
	int operator -(const Time& t)const {
		return toSecond() - t.toSecond();
	}
};
int main() {
	Time t1 = Time(1, 2, 5);
	Time t2 = Time(2, 1, 4);
	if (t2 > t1)cout << ">" << endl;
	(t1 -= 5999).display();
	(t2 += 3600).display();
	(--t1).display();
	cout << t1 - t2 << endl;
}