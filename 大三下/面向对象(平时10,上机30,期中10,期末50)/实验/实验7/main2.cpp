#include<iostream>
#include<vector>
using namespace std;
class Vehicles {
public:
	virtual void run() {
		cout << "Vehicle is running!" << endl;
	}
	virtual void stop() {
		cout << "Vehicle stopped!" << endl;
	}
};
class Bicycle :virtual public Vehicles {
	void run() {
		cout << "Bicycle is running!" << endl;
	}
	void stop() {
		cout << "Bicycle stopped!" << endl;
	}
};
class Car :virtual public Vehicles {
	void run() {
		cout << "Car is running!" << endl;
	}
	void stop() {
		cout << "Car stopped!" << endl;
	}
};
class Motorcycle :public Bicycle, public Car {
	void run() {
		cout << "Motorcycle is running!" << endl;
	}
	void stop() {
		cout << "Motorcycle stopped!" << endl;
	}
};
int main() {
	vector<Vehicles*> arr = { new Vehicles(),new Car(),new Bicycle(),new Bicycle(), new Bicycle(), new Motorcycle(),new Motorcycle };
	for (int i = 0; i < arr.size(); i++) {
		arr[i]->run();
		arr[i]->stop();
	}
}