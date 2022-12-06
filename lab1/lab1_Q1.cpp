#include "lab1_Q1.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

void QUADRATIC::print()
{
	cin >> a >> b >> c;
	cout << a << "x^2";
	if (b >= 0) {
		cout << "+" << b;
	}
	else if (b < 0) {
		cout << b;
	}
	cout << "x";
	if (c >= 0) {
		cout << "+" << c<<endl;
	}
	else if (c < 0) {
		cout << c<<endl;
	}
	
}

void QUADRATIC::add(QUADRATIC q)
{

	cin >> a >> b >> c;
	a = a + q.a;
	b = b + q.b;
	c = c + q.c;
	cout << a << "x^2";
	if (b >= 0) {
		cout << "+" << b;
	}
	else if (b < 0) {
		cout << b;
	}
	cout << "x";
	if (c >= 0) {
		cout << "+" << c << endl;
	}
	else if (c < 0) {
		cout << c << endl;
	}


}

void QUADRATIC::discriminant()
{
	cin >> a >> b >> c;
	if (b * b - 4 * a * c > 0) {
		cout << "There are two roots:" << (-(double)b + sqrt((double)b * (double)b - 4 * (double)a * (double)c)) / 2 * (double)a << "," 
			<< (-(double)b - sqrt((double)b * (double)b - 4 * (double)a * (double)c)) / 2 * (double)a << endl;
	}
	else if (b * b - 4 * a * c == 0) {
		cout << "There is a double root :" << (-(double)b + sqrt((double)b * (double)b - 4 * (double)a * (double)c)) / 2 * (double)a <<endl; 
	}
	else if (b * b - 4 * a * c < 0) {
		cout << "There are two complex roots:" << -(double)b / 2 * (double)a << "+" << sqrt((4 * (double)a * (double)c - (double)b * (double)b)) / 2 * (double)a << "i"
			<< -(double)b / 2 * (double)a << "-" << sqrt((4 * (double)a * (double)c - (double)b * (double)b)) / 2 * (double)a << "i"<<endl;
	}

}