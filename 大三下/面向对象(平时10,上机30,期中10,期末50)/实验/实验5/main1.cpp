#include<iostream>
using namespace std;
class Point
{
public:
	Point() {
		x = 0;
		y = 0;
	}
	Point(double x,double y) {
		this->x = x;
		this->y = y;
	}
	double getX(){
		return x;
	}
	double getY() {
		return y;
	}
	double r() {
		return sqrt(x * x + y * y);
	}
	double theta() {
		if (x == 0) {
			if (y > 0)return acos(-1.0) / 2;
			else if (y == 0)return 0;
			else return -acos(-1.0) / 2;
		}
		else if(x > 0) {
			return atan(y / x);
		}
		else {
			if (y == 0)return 0;
			else if (y > 0)return atan(y / x) + acos(-1.0);
			else return atan(y / x) - acos(-1.0);
		}
	}
	double distance(const Point& p) {
		return sqrt((p.x - x) * (p.x - x) + (p.y - y) * (p.y - y));
	}
	Point relative(const Point& p) {
		Point r(x - p.x, y - p.y);
		return r;
	}
	bool is_above_left(const Point& p) {
		return (x < p.x) && (y > p.y);
	}
private:
	double x, y;
};
int main() {
	Point p1(1.0, 1.0), p2(4.0, 5.0), p3(1.0, 0);
	cout << p1.r() << endl;
	cout << p1.distance(p2) << endl;
	cout << p3.theta() << endl;
	Point p12 = p2.relative(p1);
	cout << p12.getX() << " " << p12.getY() << endl;
	cout << p1.is_above_left(p2);
}