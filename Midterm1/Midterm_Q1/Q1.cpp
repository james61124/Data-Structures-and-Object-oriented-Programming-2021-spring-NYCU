#include "Deque.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {

	fstream file;

	file.open("test2_Q1.txt");
	if (!file) {
		cout << "Failed to open!\n";
		system("pause");
		exit(0);
	}

	int executeTime, dequeCapacity;
	file >> executeTime >> dequeCapacity;
	Deque myDeque(dequeCapacity);

	while (executeTime--)
	{
		char cmd;
		file >> cmd;
		int num;

		switch (cmd)
		{
		case '1':
			// TODO: implement function of PushFront
			file >> num;
			cout << "PushFront(" << num << "): \t";
			myDeque.PushFront(num);
			break;

		case '2':
			// TODO: implement function of PushBack
			
			file >> num;
			cout << "PushBack(" << num << "): \t";
			myDeque.PushBack(num);
			break;

		case '3':
			// TODO: implement function of PopFront
			
			cout << "PopFront(): \t";
			myDeque.PopFront();
			break;

		case '4':
			// TODO: implement function of PopBack
			
			cout << "PopBack(): \t";
			myDeque.PopBack();
			break;

		case 'F':
			// TODO: implement function of GetFront
			cout << "GetFront(): \t";
			if(myDeque.GetFront()!=-1)
			cout << myDeque.GetFront()<<endl;
			break;

		case 'B':
			// TODO: implement function of GetBack
			
			cout << "GetBack(): \t";
			if (myDeque.GetBack() != -1)
			cout << myDeque.GetBack() << endl;
			break;

		case 'R':
			// TODO: implement function of Reverse
			
			cout << "Reverse(): \t";
			myDeque.Reverse();
			break;

		default:
			break;
		}
	}

	system("pause");
	return 0;
}

