#pragma once
#ifndef STUDENT_H
#include <string>
#include <iostream>
using namespace std;

class Student {
	public:
		string ID;
		int score;
		int money;
		float background;
		Student(string ID, int score, int money, float background) {
			this->ID = ID;
			this->score = score;
			this->money = money;
			this->background = background;
		}
		void PrintAllInfo() {
			cout << "ID : " << ID << endl;
			cout << "score : " << score << endl;
			cout << "money : " << money << endl;
			cout << "background : " << background << endl;
		}
		virtual void ShowSchool() {

		}
		string getID() {
			return ID;
		}

	private:
		

};

#endif
#pragma once
