//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
//
#include "mySystem_SortingVisualization_bubble.h"
#include <iostream>

using namespace std;

SORTING_VISUALIZATION_BUBBLE::SORTING_VISUALIZATION_BUBBLE( )
{
    mNumElements = 20;
    mMinValue = 1;
    mMaxValue = 30;
    reset( );
}

/*
Generate randomly the elements between mMinValue and mMaxValue.
The total number of elements is mNumElements.
*/
void SORTING_VISUALIZATION_BUBBLE::reset( )
{
    mNumbers.resize( mNumElements );
    for ( int i = 0; i < mNumElements; ++i ) {
        int dv = rand( )%(mMaxValue - mMinValue + 1);
        int v = mMinValue + dv;
        mNumbers[ i ] = v;
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
void SORTING_VISUALIZATION_BUBBLE::askForInput( )
{
    cout << "//////////////////////////////" << endl;
    cout << "SORTING_VISUALIZATION" << endl;
   
    while ( true) {
        cout << "The range of elements is [1, 30]:" << endl;
        cout << "Input minValue and maxValue:" << endl;
        cin >> mMinValue >> mMaxValue;
        if ( mMinValue == 0 && mMaxValue == 0 ) {
            mMinValue = 1;
            mMaxValue = 30;
            break;
        }
        if ( (mMinValue >= 1 && mMinValue <= 30 )
            && 
            (mMaxValue >= 1 && mMaxValue <= 30 )
            ) break;
    }

    while (true) {
        cout << "Input the number of elements [1, 50]:" << endl;
        cin >> mNumElements;
        if ( (mNumElements >= 1 && mNumElements <= 50 ) ) break;
    }
    cout << "//////////////////////////////" << endl;
    cout << "Press SPACEBAR to visualize the process..." << endl;
    cout << "//////////////////////////////" << endl;

    reset( );
}

/*
Two elements whose
indices are (index) and (index+1).

Swap these two elements if their order is incorrect.
*/
void SORTING_VISUALIZATION_BUBBLE::checkAndSwapTwoElements( int index )
{
    int v0 = mNumbers[ index ];
    int v1 = mNumbers[ index + 1];

    if ( v1 > v0 ) return;

    mNumbers[ index ] = v1;
    mNumbers[ index + 1 ] = v0;
}

/*
Perform one swap step for two elements.
The first element is indicated by mCurrentIndex.
*/
void SORTING_VISUALIZATION_BUBBLE::processOneSwapStep( )
{
    if ( mNumElements <= 1) return;
    if ( mMaxNonHandledElementIndex <= 1 ) return;
    if (mCurrentIndex >= mMaxNonHandledElementIndex - 1 ) { 
        mCurrentIndex = 0;
        --mMaxNonHandledElementIndex;
    }
    if ( mMaxNonHandledElementIndex <= 1 ) return;
    checkAndSwapTwoElements( mCurrentIndex );


    ++mCurrentIndex;
}

/*
Return the current element that will be processed.
*/
int SORTING_VISUALIZATION_BUBBLE::getCurrentElementIndex( ) const
{
    return mCurrentIndex;
}

/*
Return the index of the last non-handled element.
*/
int SORTING_VISUALIZATION_BUBBLE::getMaxNonHandledElementIndex( ) const
{
    return mMaxNonHandledElementIndex;
}

/*
Return the number of elements.
*/
int SORTING_VISUALIZATION_BUBBLE::getNumOfElements( ) const
{
    //Return the number of elements
    return mNumElements;
}

/*
Return the element whose index is elementIndex.
*/
int SORTING_VISUALIZATION_BUBBLE::getElement( int elementIndex ) const
{
    return mNumbers[ elementIndex ];
}

