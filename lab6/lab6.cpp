#include "Student.h"
#include "BigLeaf.h"
#include "Traffic.h"
#include "TaiwanNumber1.h"
#include "PorkBall.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
	Student* bigleaf = new BigLeaf("Bill", 80, 20, 0.8);
	bigleaf->PrintAllInfo();
	bigleaf->ShowSchool();
	cout << endl;

	Student* traffic = new Traffic("Wilson", 10, 50, 0.5);
	traffic->PrintAllInfo();
	traffic->ShowSchool();
	cout << endl;

	Student* taiwan1 = new TaiwanNumber1("Alice", 25, 77, 0.2);
	taiwan1->PrintAllInfo();
	taiwan1->ShowSchool();
	cout << endl;

	PorkBall* porkball = new PorkBall("Max", 20.2);
	cout << "Check whether the student can ride this porkball." << endl;
	porkball->canRide(bigleaf);
	porkball->canRide(traffic);
	porkball->canRide(taiwan1);
	cout << endl;

	system("PAUSE");
	return 0;
}