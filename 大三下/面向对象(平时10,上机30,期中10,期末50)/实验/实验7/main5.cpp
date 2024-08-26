#include <iostream>
#include <string>
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
	void display()const {
		cout << hour << ":" << minute << ":" << second;
	}
	bool equal(const Time& other_time)const {
		return (hour == other_time.hour) && (minute == other_time.minute) && (second == other_time.second);
	}
	bool less_than(const Time& other_time)const {
		return (hour * 3600 + minute * 60 + second + 1 < other_time.hour * 3600 + other_time.minute * 60 + other_time.second);
	}
};
class Date {
private:
	int year, month, day;
public:
	Date(int y, int m, int d) {
		year = y;
		month = m;
		day = d;
	}
	void increment() {
		int d;
		switch (month) {
		case 1:case 3:case 5:case 7:case 8:case 10:case 12:
			d = 31;
			break;
		case 4:case 6:case 9:case 11:
			d = 30;
			break;
		case 2:
			if (year % 400 == 0 || year % 4 == 0 && year % 100 != 0)
				d = 29;
			else
				d = 28;
		}
		if (day < d)day++;
		else if (month != 12) {
			day = 1;
			month++;
		}
		else {
			day = 1;
			month = 1;
			year++;
		}
	}
	bool equal(const Date& date2)const {
		return year == date2.year && month == date2.month && day == date2.day;
	}
	bool less_than(const Date& date2)const {
		return year < date2.year || 
			year == date2.year && month < date2.month || 
			year == date2.year && month == date2.month && day < date2.day;
	}
	void display()const {
		cout << year << '-' << month << '-' << day;
	}
};
class TimeWithDate :public Time, public Date {
public:
	TimeWithDate(int y,int mo,int d,int h,int mi,int s):Date(y,mo,d),Time(h,mi,s){}
	bool less_than(const TimeWithDate& td2)const {
		if (Date::less_than(td2))return true;
		else if (Date::equal(td2) && Time::less_than(td2)) {
			return true;
		}
		else return false;
	}
	void increment() {
		Time::increment();
		if (((Time*)this)->equal(Time(0, 0, 0)))Date::increment();
	}
	int difference(const TimeWithDate& td2)const {
		int days = 0;
		if (less_than(td2))
			for (TimeWithDate td = *this; td.less_than(td2); td.increment())days--;
		else
			for (TimeWithDate td = td2; td.less_than(*this); td.increment())days++;
		return days;
	}
	void display() {
		Date::display();
		cout << " ";
		Time::display();
	}
};
int main() {
	TimeWithDate td1(2012, 2, 3, 7, 0, 0), td2(2012, 3, 1, 8, 0, 0);
	td1.increment();
	td1.display(); cout << endl;
	cout << td2.difference(td1);
}

