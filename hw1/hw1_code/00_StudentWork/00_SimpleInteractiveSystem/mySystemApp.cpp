//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/03/01
//
#include "mySystemApp.h"

using namespace std;

#define STUDENT_INFO "Name:ªô¥°µ¤   ID:109550136"

void MY_SYSTEM_APP::showMyStudentInfo( ) const
{
	
	cout << "*******************************" << endl;
    cout << "Date:" << "2020/03/14" << endl;
	cout << "Student ID:109550136\t" << endl;
	cout << "Student Name:ªô¥°µ¤\t" << endl;
	cout << "Student Email:james61124@gmail.com\t" << endl;
	cout << "*******************************" << endl;
}

MY_SYSTEM_APP::MY_SYSTEM_APP( )
{
	mSystemType = SYSTEM_TYPE_MONTE_CARLO_CIRCLE;
    string title = STUDENT_INFO;
        glutSetWindowTitle(title.data( ));
}

void MY_SYSTEM_APP::initApp( )
{
	mFlgShow_Grid = true;
}

void MY_SYSTEM_APP::update( )
{

}
// CODE: 2021/03/01. Do not delete this line.



