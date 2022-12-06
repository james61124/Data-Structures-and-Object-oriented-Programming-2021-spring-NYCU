#ifndef DEQUE_H
#define DEQUE_H

class Deque
{
public:
	Deque(int _capacity);
	~Deque();

	void PushFront(int element); //1
	void PushBack(int element);  //2
	void PopFront();			 //3
	void PopBack();				 //4
	int  GetFront();			 //F
	int  GetBack();				 //B
	void Reverse();				 //R
	void DoubleCapacity();
	void Print();
	bool IsEmpty();
	bool IsFull();
	int  GetCapacity();


private:
	int capacity;
	int currentSize;
	int* deque;
};



#endif // ! Deque_H
