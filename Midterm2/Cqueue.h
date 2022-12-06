#pragma once

class Cqueue {
private:
	int* queue;
	int capacity;
	int start;
	int end;

	/* You can add extra variables or functions here */
	int start1;
	int size;
	int cursize;
	int* a;

public:
	Cqueue(int Capacity);
	void Enqueue(int x);
	void Dequeue();
	bool IsEmpty();
	bool IsFull();
	void Reverse();
	int GetSize();
	int GetStart();
	int GetEnd();
	void Print();

};
