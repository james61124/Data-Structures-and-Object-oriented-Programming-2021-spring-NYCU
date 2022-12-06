#pragma once
#ifndef TRAFFIC_H
#include "student.h"
#include <string>
#include <iostream>
using namespace std; 

class Traffic :public Student {
public:
	Traffic(string ID, int score, int money, float background) :Student(ID, score, money, background) {}
	void ShowSchool() {
		cout << "student " << ID << "is Traffic student" << endl;
	}


private:
	




};

#endif
#pragma once
