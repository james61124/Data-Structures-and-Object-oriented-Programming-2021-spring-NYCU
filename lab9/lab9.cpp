#include<fstream>
#include<string>
#include"LinkedList.h"

using namespace std;


int main() {
	ifstream File;
	File.open("demo.txt");

	if (!File.is_open()) {
		cout << "Can't open test.txt" << endl;
		system("pause");
		return 0;
	}

	int num_op = 0;
	File >> num_op;
	LinkedList list;
	while (num_op) {

		char op;
		int val;
		int index;

		File >> op;

		switch (op)
		{
		case 'b':
			File >> val;
			cout << "Push_back(" << val << "):\t";
			list.Push_back(val);
			break;
		case 'f':
			File >> val;
			cout << "Push_front(" << val << "):\t";
			list.Push_front(val);
			break;
		case 'i':
			File >> index;
			File >> val;
			cout << "Insert(" << index << "," << val << "):\t";
			list.Insert(index, val);
			break;
		case 'd':
			File >> index;
			cout << "Delete(" << index << "):\t";
			list.Delete(index);
			break;
		case 'r':
			cout << "Reverse():\t";
			list.Reverse();
			break;
		case 'c':
			cout << "Clear():\t";
			list.Clear();
			break;
		default:
			break;
		}
		list.Print();

		num_op--;
	}

	system("pause");
	return 0;
}