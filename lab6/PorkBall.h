#pragma once
#ifndef PORKBALL_H
#include "Student.h"
#include "Traffic.h"
#include <string>
#include <iostream>
using namespace std;

class PorkBall {
public:
	PorkBall(string name, float speed) {
		this->name = name;
		this->speed = speed;
	}

	bool canRide(Student* student) {
		// use isTraffic to check whether the student can ride the porkball.
		if (isTraffic(student)) {
			cout << student->getID()<< " can ride porkball "<<name<<", the speed is "<<speed<< endl;
			return true;
		}
		else {
			cout << "error bad_cast" << endl;
			return false;
		}
	}

private:
	string name;
	float speed;
	bool isTraffic(Student* student) {
		// use dynamic casting to check whether the student is a Traffic student. 
		Traffic* tra = dynamic_cast<Traffic*>(student);
		if (tra == NULL) {
			return false;
		}
		else {
			return true;
		}
		
	}
};
#endif
#pragma once
