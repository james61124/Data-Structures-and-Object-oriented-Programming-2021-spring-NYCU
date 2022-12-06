#pragma once
#ifndef TAIWANNUMBER1_H
#include "student.h"
#include <string>
#include <iostream>
using namespace std; 

class TaiwanNumber1 :public Student {
public:
	TaiwanNumber1(string ID, int score, int money, float background) :Student(ID, score, money, background) {	}
	void ShowSchool() {
		cout << "student " << ID << "is TaiwanNumber1 student" << endl;
	}


private:
	



};

#endif
#pragma once
