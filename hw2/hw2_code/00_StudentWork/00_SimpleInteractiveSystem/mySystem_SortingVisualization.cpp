//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/03/29
//
#include "mySystem_SortingVisualization.h"
#include <iostream>

using namespace std;

SORTING_VISUALIZATION::SORTING_VISUALIZATION( )
{
    mNumElements = 20;
    mMinValue = 1;
    mMaxValue = 30;
	mCurrentIndex=0;
	
    reset( );
}

/*
Generate randomly the elements between mMinValue and mMaxValue.
The total number of elements is mNumElements.
*/
void SORTING_VISUALIZATION::reset( )
{
	int a;
    mNumbers.clear();
    for (int i = 0; i < mNumElements; i++)
    {
        a = rand()%(mMaxValue-mMinValue+1)+mMinValue;
        mNumbers.push_back(a);
    }
    mCurrentIndex = 0;
    mMaxNonHandledElementIndex = mNumElements;
}

/*
Show the system title.
Ask to input the range [mMinValue, mMaxValue] of the elements.
Ask to input the number of elements.
Generate the elements.
*/
void SORTING_VISUALIZATION::askForInput( )
{
    cout << "//////////////////////////////" << endl;
    cout << "SORTING_VISUALIZATION" << endl;
  
    cout << "//////////////////////////////" << endl;
    cout << "Press SPACEBAR to visualize the process..." << endl;
    cout << "//////////////////////////////" << endl;
	while(true){
		cout << "input the range [1,30] of the elements:"<<endl;
		cin >> mMinValue >> mMaxValue;
		if( mMinValue>=1 && mMinValue<=30 && mMaxValue>=1 && mMaxValue<=30 )break;
	}
	cout << "input the number of elements"<<endl;
	cin>> mNumElements;
	mMaxNonHandledElementIndex=mNumElements-1;
   
}

/*
Two elements whose
indices are (index) and (index+1).

Swap these two elements if their order is incorrect.
*/
void SORTING_VISUALIZATION::checkAndSwapTwoElements( int index )
{
	/*if(mNumbers[index]>mNumbers[index+1]){
		int tmp=mNumbers[index];
		mNumbers[index]=mNumbers[index+1];
		mNumbers[index+1]=tmp;

	}*/
	int a = mNumbers[index], b = mNumbers[index + 1];
    if (a > b)
    {
        mNumbers[index] = b;
        mNumbers[index + 1] = a;
    }
    else
    {
        return;
    }
}

/*
Perform one swap step for two elements.
The first element is indicated by mCurrentIndex.
*/
void SORTING_VISUALIZATION::processOneSwapStep( )
{
	
	checkAndSwapTwoElements(mCurrentIndex);
    mCurrentIndex++;

    if (mCurrentIndex == mMaxNonHandledElementIndex - 1) {
        mCurrentIndex = 0;
        mMaxNonHandledElementIndex--;
    }
}

/*
Return the current element that will be processed.
*/
int SORTING_VISUALIZATION::getCurrentElementIndex( ) const
{
    return mCurrentIndex;
}

/*
Return the index of the last non-handled element.

mMaxNonHandledElementIndex
*/
int SORTING_VISUALIZATION::getMaxNonHandledElementIndex( ) const
{

    return mMaxNonHandledElementIndex;
}

/*
Return the number of elements.
*/
int SORTING_VISUALIZATION::getNumOfElements( ) const
{
    //Return the number of elements
    return mNumElements;
}

/*
Return the element whose index is elementIndex.
*/
int SORTING_VISUALIZATION::getElement( int elementIndex ) const
{
    return mNumbers[elementIndex];
}