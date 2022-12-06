//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/06/17
//
#include "mySystemApp.h"

using namespace std;

void MY_SYSTEM_APP::showStudentInfo_2021( ) const
{
	cout << "*******************************" << endl;
    cout << "2021 Spring. 2021/06/17" << endl;
	cout << "Student ID:109550136\t" << endl;
	cout << "Student Name:ªô¥°µ¤\t" << endl;
	cout << "Student Email:james61124@gmail.com\t" << endl;
	cout << "*******************************" << endl;
}

void MY_SYSTEM_APP::showMenu( ) const
{
    cout << "Welcome to our mini-galaxy!" << endl;
    cout << "Menu----------------------" << endl;
    cout << "Key usage:" << endl;
    cout << "F1: Graph System" << endl;
    cout << "F2: Monte Carlo Simulation" << endl;
    cout << "F3: Visualization of Sorting Process" << endl;
    cout << endl;
    cout << " s: Show Student Information on Console window" << endl;
    cout << "F5: show Student Information" << endl;
    cout << endl;
    cout << "--------------------------" << endl;

}

MY_SYSTEM_APP::MY_SYSTEM_APP( )
{
	mSystemType = SYSTEM_TYPE_GALAXY_SYSTEM;
    //
    mCurSystem = 0;
}

void MY_SYSTEM_APP::initApp( )
{
	mFlgShow_Grid = false;
    showMenu( );
    //
    mGraphSystem = new GRAPH_SYSTEM;
    //

    mMonteCarloSystem = new MONTE_CARLO_SYSTEM;

    mSortingVisualization = new SORTING_VISUALIZATION;
    //

    mCurSystem = mGraphSystem;

    ////////////////////////////////////////////
    //
    specialFunc(GLUT_KEY_F1, 0, 0);
}

void MY_SYSTEM_APP::update( )
{
    mCurSystem->update( );
    return;
}




