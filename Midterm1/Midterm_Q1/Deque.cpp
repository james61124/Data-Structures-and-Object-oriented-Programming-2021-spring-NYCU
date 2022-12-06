#include "Deque.h"
#include <iostream>

using namespace std;

Deque::Deque(int _capacity) {
	// TODO: Create a dynamic array to implement a Deque 
	this->capacity = _capacity;
	deque = new int[_capacity] {0};
}

Deque::~Deque() {
	// TODO: delete Deque
}

void Deque::PushFront(int element) {
	// TODO: push the element to the front of the Deque
	int times = 0;
	for (int i = 0; i < capacity; i++) {
		if (deque[i] == 0) {
			break;
		}
		times++;
	}
	if (times == 0) {
		deque[0] = element;
	}
	else if (times != capacity) {
		for (int i = capacity-1; i >0; i--) {
			deque[i] = deque[i - 1];
		}
		deque[0] = element;
		
	}
	else{
		int *tmp;
		tmp = new int[capacity] {0};
		for (int i = 0; i < capacity; i++) {
			tmp[i] = deque[i];
		}
		delete[]deque;
		deque = new int[capacity * 2]{ 0 };
		for (int i = 0; i < capacity; i++) {
			deque[i] = tmp[i];
		}
		for (int i = capacity ; i > 0; i--) {
			deque[i] = deque[i - 1];
		}
		deque[0] = element;
		capacity = capacity * 2;
	}
	cout << "Capacity:" << capacity<<", Element:";
	for (int i = 0; i < capacity; i++) {
		if(deque[i]!=0) cout << deque[i] << " ";
	}
	cout << endl;
}

void Deque::PushBack(int element) {
	// TODO: push the element to the back of the Deque
	int times = 0;
	for (int i = 0; i < capacity; i++) {
		if (deque[i] == 0) {
			break;
		}
		times++;
	}
	if (times == 0) {
		deque[0] = element;
	}
	else if (times != capacity) {
		deque[times] = element;
	}
	else {
		int *tmp;
		tmp = new int[capacity] {0};
		for (int i = 0; i < capacity; i++) {
			tmp[i] = deque[i];
		}
		delete[]deque;
		deque = new int[capacity * 2]{ 0 };
		for (int i = 0; i < capacity; i++) {
			deque[i] = tmp[i];
		}
		deque[capacity] = element;
		capacity = capacity * 2;
	}
	cout << "Capacity:" << capacity << ", Element:";
	for (int i = 0; i < capacity; i++) {
		if (deque[i] != 0) cout << deque[i] << " ";
	}
	cout << endl;
}

void Deque::PopFront() {
	// TODO: pop the front element of the Deque
	int times = 0;
	for (int i = 0; i < capacity; i++) {
		if (deque[i] == 0) {
			break;
		}
		times++;
	}
	if (times != 0) {
		deque[0] = 0;
		for (int i = 0; i < capacity-1; i++) {
			deque[i] = deque[i + 1];
		}
		deque[capacity - 1] = 0;
		cout << "Element:";
		for (int i = 0; i < capacity; i++) {
			if (deque[i] != 0) cout << deque[i] << " ";
		}
		cout << endl;
	}
	else {
		cout << "Deque is empty." << endl;
	}
	
}

void Deque::PopBack() {
	// TODO: pop the back element of the Deque
	int times = 0;
	for (int i = 0; i < capacity; i++) {
		if (deque[i] == 0) {
			break;
		}
		times++;
	}
	if (times != 0) {
		deque[times - 1] = 0;
		cout << "Element:";
		for (int i = 0; i < capacity; i++) {
			if (deque[i] != 0) cout << deque[i] << " ";
		}
		cout << endl;
	}
	else {
		cout << "Deque is empty." << endl;
	}
	
}

int  Deque::GetFront() {
	// TODO: get the value of front element in the Deque 
	int times = 0;
	for (int i = 0; i < capacity; i++) {
		if (deque[i] == 0) {
			break;
		}
		times++;
	}
	if (times != 0) {
		return deque[0];
	}
	else {
		cout << "Deque is empty." << endl;
		return -1;
	}
}

int  Deque::GetBack() {
	// TODO: get the value of back element in the Deque
	int times = 0;
	for (int i = 0; i < capacity; i++) {
		if (deque[i] == 0) {
			break;
		}
		times++;
	}
	if (times != 0) {
		return deque[times-1];
	}
	else {
		cout << "Deque is empty." << endl;
		return -1;
	}
}

void Deque::Reverse() {
	// TODO: reverse the Deque
	int times = 0;
	for (int i = 0; i < capacity; i++) {
		if (deque[i] == 0) {
			break;
		}
		times++;
	}

	if (times != 0) {
		int *tmp, index = times - 1;
		tmp = new int[times] {0};
		for (int i = 0; i < times; i++) {
			tmp[i] = deque[index];
			index--;
		}
		for (int i = 0; i < times; i++) {
			deque[i] = tmp[i];
		}
		cout << "Element:";
		for (int i = 0; i < capacity; i++) {
			if (deque[i] != 0) cout << deque[i] << " ";
		}
		cout << endl;
	}
	else {
		cout << "Deque is empty." << endl;
	}


	
}

void Deque::DoubleCapacity() {
	// TODO: double the capacity of the Deque
	int *tmp;
	tmp = new int[capacity] {0};
	for (int i = 0; i < capacity; i++) {
		tmp[i] = deque[i];
	}
	delete[]deque;
	deque = new int[capacity * 2]{ 0 };
	for (int i = 0; i < capacity; i++) {
		deque[i] = tmp[i];
	}
	capacity = capacity * 2;

}

void Deque::Print() {
	cout << "Element: ";
	for (int i = 0; i < currentSize; i++)
	{
		cout << deque[i] << " ";
	}
	cout << "\n";
}

bool Deque::IsEmpty() {
	return currentSize == 0;
}

bool Deque::IsFull() {
	return currentSize == capacity;
}

int  Deque::GetCapacity() {
	return capacity;
}
