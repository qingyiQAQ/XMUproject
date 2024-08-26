#include<iostream>
using namespace std;
class Complex {
private:
	double real = 0, imag = 0;
public:
	Complex(double real,double imag) {
		this->real = real;
		this->imag = imag;
	}
	friend ostream& operator<<(ostream& os, const Complex& c) {
		os << c.real << "+" << c.imag << "i";
		return os;
	}
	Complex operator+(Complex c) {
		return Complex(real + c.real, imag + c.imag);
	}
	Complex operator+(double d) {
		return Complex(real + d, imag);
	}
	Complex operator-(Complex c) {
		return Complex(real - c.real, imag - c.imag);
	}
	Complex operator-(double d) {
		return Complex(real - d, imag);
	}
	Complex operator*(Complex c) {
		return Complex(real * c.real - imag * c.imag, real * c.imag + imag * c.real);
	}
	Complex operator*(double d) {
		return Complex(real * d, imag * d);
	}
	Complex operator/(Complex c) {
		return Complex((real * c.real + imag * c.imag) / (c.real * c.real + c.imag * c.imag),
			(imag * c.real - real * c.imag) / (c.real * c.real + c.imag * c.imag));
	}
	Complex operator/(double d) {
		return Complex(real / d, imag / d);
	}
};
int main() {
	Complex c1(1, 2), c2(3, 4);
	cout << c1 + c2 << endl;
	cout << c1 - c2 << endl;
	cout << c1 * c2 << endl;
	cout << c1 / c2 << endl;
	cout << c1 + 5 << endl;
	cout << c2 - 3 << endl;
	cout << c2 * 0.1 << endl;
	cout << c2 / 5 << endl;
}