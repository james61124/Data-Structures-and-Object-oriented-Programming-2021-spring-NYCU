#pragma once
#ifndef BIGLEAF_H
#include "student.h"
#include <string>
#include <iostream>
using namespace std; 

class BigLeaf :public Student {
public:
	BigLeaf(string ID, int score, int money, float background):Student(ID,score,money,background) {}
	void ShowSchool() {
		cout << "student " << ID << "is Bigleaf student" << endl;
	}
	

private:
	
			
		
	

};

#endif
#pragma once
