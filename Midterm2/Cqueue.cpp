#include "Cqueue.h"
#include<iostream>
using namespace std;

Cqueue::Cqueue(int Capacity)
{
	// TODO: Constructor
	queue = new int[Capacity];
	capacity = Capacity;
	start = 0;
	end = -1;
	start1 = 0;

	size = Capacity;
	a = new int[0];
	cursize = 0;
	
}

void Cqueue::Enqueue(int x)
{
	if (IsFull()) {
		cout << "Queue is full, cannot add more elements." << endl;
	}
	else {
		//TODO: Add the element to the back of the queue
		/*end = (end + 1) % capacity;
		queue[end] = x;*/
		int* temp = new int[cursize + 1]{ 0 };
		for (int i = 0; i < cursize; i++) {
			temp[i] = a[i];
		}
		temp[cursize] = x;
		a = temp;
		cursize++;
		end = (end + 1) % capacity;
	}
}

void Cqueue::Dequeue()
{
	if (IsEmpty()) {
		cout << "Queue is empty" << endl;
	}
	else {
		//TODO: Remove the first element of the queue
		/*start = (start + 1) % capacity;
		start1 = (start1 + 1) % (capacity - 1);*/
		int* temp = new int[cursize - 1];
		for (int i = 1; i < cursize; i++) {
			temp[i - 1] = a[i];
		}
		a = temp;
		cursize--;
		start = (start + 1) % capacity;
	}
}

bool Cqueue::IsEmpty()
{
	//TODO: Determine if queue is empty
	if (cursize == 0) return true;
	else return false;
	//return ((start == end) || (end == -1));
}

bool Cqueue::IsFull()
{
	//TODO: Determine if queue is full
	//return (((end + 1) % (capacity)) == (start % capacity));
	if (cursize == size) return true;
	else return false;
}

void Cqueue::Print()
{
	cout << "The current content of queue is: ";

	//TODO: Print out the elements of queue from front to back
	/*int i, flag = 1;
	if (IsEmpty()) {
		cout << "Queue is empty" << endl;
	}
	else {
		for (i = start + 1; i < capacity; i++) {
			if ((i - 1) == end) {
				
				flag == 0;
				break;
			}
			cout << queue[i] << " ";
		}
		if (i == capacity && flag == 1) {
			for (int j = 0; j <= end; j++) {
				cout << queue[j] << " ";
			}
		}
	}
	cout << endl;*/
	for (int i = 0; i < cursize; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

void Cqueue::Reverse() {
	//TODO: Reverse the queue
	/*int* a = new int[GetSize()]{ 0 };
	int index = 0;
	int flag = 1, k;
	for (k = start + 1; k < capacity; k++) {
		if ((k - 1) == end) {
			flag == 0;
			break;
		}
		a[index] = queue[k];
		index++;
	}
	if (k == capacity && flag == 1) {
		for (int j = 0; j <= end; j++) {
			a[index] = queue[k];
			index++;
		}
	}

	for (int i = GetSize() - 1; i > 0; i--){
		for (int j = 0; j <= i - 1; j++){
			if (a[j] > a[j + 1]){
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}

	index = 0;
	flag = 1;
	k = 0;
	for (k = start + 1; k < capacity; k++) {
		if ((k - 1) == end) {
			flag == 0;
			break;
		}
		queue[k]=a[index];
		index++;
	}
	if (k == capacity && flag == 1) {
		for (int j = 0; j <= end; j++) {
			queue[k] = a[index];
			index++;
		}
	}*/
	/*for (int i = cursize - 1; i > 0; i--) {
		for (int j = 0; j <= i - 1; j++) {
			if (a[j] > a[j + 1]) {
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}*/
	int* b = new int[cursize] {0};
	int j = cursize - 1;
	for (int i = 0; i < cursize; i++) {
		b[i] = a[j];
		j--;
	}
	for (int i = 0; i < cursize; i++) {
		a[i] = b[i];
		
	}

}

int Cqueue::GetSize() {
	//Return the size of queue
	/*int size = 0;
	int i, flag = 1;
	if (IsEmpty()) {
		return 0;
	}
	else {
		for (i = start + 1; i < capacity; i++) {
			if ((i - 1) == end) {
				flag == 0;
				break;
			}
			size++;
		}
		if (i == capacity && flag == 1) {
			for (int j = 0; j <= end; j++) {
				size++;
			}
		}
	}*/
	return cursize;

}

int Cqueue::GetStart() {
	//return start;
	//int index = (start+1) % capacity;
	if (IsEmpty() == true) {
		return 0;
	}
	else return start;
	
}

int Cqueue::GetEnd() {
	//return end;
	if (IsEmpty() == true) {
		return -1;
	}
	else return end;
}
