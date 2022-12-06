#include<iostream>
#include<fstream>
#include "Cqueue.h"
using namespace std;

int main() {
	/* Do not modify the content in "int main ()". */

	fstream file;
	file.open("Q2_input.txt");

	if (!file.is_open()) {
		cout << "Fail to open file" << endl;
		return 0;
	}

	int TestCase;
	file >> TestCase;

	while (TestCase) {

		int Capacity;
		file >> Capacity;
		Cqueue q(Capacity);

		int NumberOfOp;
		file >> NumberOfOp;

		for (int i = 0; i < NumberOfOp; i++) {
			char op;
			file >> op;
			switch (op)
			{
			case 'e':
				int x;
				file >> x;
				q.Enqueue(x);
				break;

			case 'd':
				q.Dequeue();
				break;

			case 'p':
				q.Print();
				break;

			case 'r':
				q.Reverse();
				break;

			case 's':
				cout << "The size of queue is: " << q.GetSize() << endl;
				break;

			case 'a':
				cout << "Start: " << q.GetStart() << endl;
				break;

			case 'b':
				cout << "End: " << q.GetEnd() << endl;
				break;

			default:
				break;
			}
		}
		cout << endl;
		TestCase--;
	}

	return 0;
}