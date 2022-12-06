//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/03/01
//
#include "mySystem_StudentRecordManager.h"
#include <iostream>
#include <cmath>

using namespace std;

STUDENT_RECORD_MANAGER::STUDENT_RECORD_MANAGER( )
{
	mNumStudents = 0;
}

void STUDENT_RECORD_MANAGER::askForInput( )
{
	//Show the system title
	//Ask to input the number of students
	//Ask to input the score of each student
	//Show the average
	//Show the standard deviation
	//Show the scores in an ascending order
	//
	cout << "STUDENT_RECORD_MANAGER" << endl;
	while(true){
		cout << "Input the number of students [2, 100]:" << endl;
		cin >> mNumStudents;
		if ( mNumStudents >= 2 && mNumStudents <=100 ) break;
	}
	
		cout<<"input the score of each student[0,100]"<<endl;
		for(int i=0;i<mNumStudents;i++){
			int score;
			while(true){
				cin>>score;
				if(score>=0 && score<=100) break;
			}
			mScore.push_back(score);
		}
	
		
		
		cout<<"average:"<<computeAverage( )<<endl;
		cout<<"StandardDeviation:"<<computeStandardDeviation( )<<endl;
		sortScores( );
		showSortedScores( );


	

	
}

double STUDENT_RECORD_MANAGER::computeAverage( )
{
	//Compute the average
    double totalScore = 0;
	for(int i=0;i<mNumStudents;i++){
		totalScore=totalScore+mScore[i];
	}
	mAverageScore = totalScore/mNumStudents;
	return mAverageScore;
}

double STUDENT_RECORD_MANAGER::computeStandardDeviation( )
{
	//Compute the standard deviation

	double sum = 0.0;
	for(int i=0;i<mNumStudents;i++){
		sum=sum+(mScore[i]-mAverageScore)*(mScore[i]-mAverageScore);
	}
	mStandardDeviation=sqrt(sum/(mNumStudents));
	return mStandardDeviation;
}

void STUDENT_RECORD_MANAGER::sortScores( )
{
	//Sorting in an ascending order
	for(int i=0;i<mNumStudents;i++){
		for(int j=0;j<mNumStudents;j++){
			if(mScore[i]<mScore[j]){
				int temp=mScore[i];
				mScore[i]=mScore[j];
				mScore[j]=temp;
			}
		}
	}
	for(int i=0;i<mNumStudents;i++){
		mSortedScore.push_back(mScore[i]);
	}

}

void STUDENT_RECORD_MANAGER::showSortedScores( ) const
{
	//Show the scores in an ascending order
	for(int i=0;i<mNumStudents;i++){
		cout<<mSortedScore[i]<<endl;
	}
	

}

int STUDENT_RECORD_MANAGER::getNumOfStudentsInScoreInterval(int s0, int s1) const
{
	//
	//Return the number of students whose score is inside the interval [s0, s1]. 
	//s0 and s1 are included.
	//int b=10;
	// int &a=b;
	int num = 0;
	for(int i=0;i<mNumStudents;i++){
		if(mSortedScore[i]>=s0 && mSortedScore[i]<=s1){
			num++;
		}
	}

    return num;
}
// CODE: 2021/03/01. Do not delete this line.