
#include <iostream>
#include "lab1_Q1.h"

using namespace std;

int main()
{
	int n;
	cin >> n;

	while (n--)
	{
		char command;
		cin >> command;
		QUADRATIC q1, q2;
		switch (command) {
		case '+':
			cin >> q1.a >> q1.b >> q1.c;
			q2.add(q1);
			break;
		case 'p':
			q1.print();
			break;
		case 'd':
			q1.discriminant();
			break;
			

		default:
			cout << "wrong input!";
			break;
		}
	}

	system("pause");
}
