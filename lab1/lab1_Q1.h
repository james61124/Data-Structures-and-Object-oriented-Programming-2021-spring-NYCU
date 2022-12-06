#ifndef QUADRATIC_H_INCLUDED
#define QUADRATIC_H_INCLUDED

class QUADRATIC
{
public:
	//QUADRATIC() : a(0), b(0), c(0) {}
	QUADRATIC() {
		this->a = 0;
		this->b = 0;
		this->c = 0;
	}
	QUADRATIC(int a, int b, int c) : a(a), b(b), c(c) {}
	void add(QUADRATIC q);
	void discriminant();


	int a;
	int b;
	int c;

	void print();
};

#endif // QUADRATIC_H_INCLUDED
