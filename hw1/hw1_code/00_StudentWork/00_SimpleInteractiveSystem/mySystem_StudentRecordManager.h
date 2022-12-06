//
//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/03/01
//
#ifndef __MY_STUDENT_RECORD_MANAGER_H_
#define __MY_STUDENT_RECORD_MANAGER_H_
#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
#include <vector>
using std::vector;
class STUDENT_RECORD_MANAGER
{
protected:
	int mNumStudents;
	vector<int> mScore;
	vector<int> mSortedScore;

	double mAverageScore;
	double mStandardDeviation;
	void showSortedScores( ) const;
public:
	STUDENT_RECORD_MANAGER( );
	void askForInput( );
	double computeAverage( );
	double computeStandardDeviation( );
	void sortScores( );
	int getNumOfStudentsInScoreInterval(int s0, int s1) const;
};
#endif
// CODE: 2019/02/25. Do not delete this line.