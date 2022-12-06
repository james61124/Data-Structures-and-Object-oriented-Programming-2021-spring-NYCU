//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/06/17
//
#include "mySystem_SortingVisualization.h"
#include <iostream>

using namespace std;

SORTING_VISUALIZATION::SORTING_VISUALIZATION( )
{
    mNumElements = 50;
    mMinValue = 1;
    mMaxValue = 50;
    mSortingOrder = SORTING_ORDER_INCREASING;
    reset( );
}

/*
Generate randomly the elements between mMinValue and mMaxValue.
The total number of elements is mNumElements.
*/
void SORTING_VISUALIZATION::reset( )
{
    mNumbers.resize( mNumElements );
    for ( int i = 0; i < mNumElements; ++i ) {
        //mNumbers[ i ] = i;
		mNumbers[ i ] =rand()%(mMaxValue-mMinValue+1)+mMinValue;
    }
    mCurrentIndex = 0;
    mMaxNonHandledElementIndex = mNumElements;
    mPrevElementIndex = -1;
}

void SORTING_VISUALIZATION::resetSorting( )
{
    mCurrentIndex = 0;
    mMaxNonHandledElementIndex = mNumElements;
    mPrevElementIndex = -1;
}

bool SORTING_VISUALIZATION::handleKeyPressedEvent( 
    unsigned char key 
    )
{
    bool flg_handled = false;
    
    switch( key ) {
    case '1':
        mSortingOrder = SORTING_ORDER_INCREASING;
        resetSorting( );

        flg_handled = true;
        break;
        case '2':
        mSortingOrder = SORTING_ORDER_DECREASING;
        resetSorting( );

        flg_handled = true;
        break;

		case ' ':
		if(mSortingOrder == SORTING_ORDER_INCREASING)processOneStep( );
		else if(mSortingOrder == SORTING_ORDER_DECREASING) processOneStep2( );
        flg_handled = true;
        break;

        case 'r':
        reset( );
        flg_handled = true;
        break;
    }
    return flg_handled;
}

void SORTING_VISUALIZATION::shiftToRight( 
    int start_index
    , int end_index 
    )
{
    //
    // Fill or modify your own stuff
    //

    for (int i =end_index; i > start_index; i-- ) {
        mNumbers[i]=mNumbers[i-1];
    }
}

int SORTING_VISUALIZATION::getPreviousElementIndex( ) const
{
    return mPrevElementIndex;
}

void SORTING_VISUALIZATION::insertElement( int index )
{
    //
    // Fill or modify your own stuff
    //
	int tmp=mNumbers[mCurrentIndex];
	shiftToRight(index,mCurrentIndex);
	mNumbers[index]=tmp;

}

/*
Perform one swap step for two elements.
The first element is indicated by mCurrentIndex.
*/
void SORTING_VISUALIZATION::processOneStep( )
{
    if ( mNumElements <= 1) return;
    //if ( mMaxNonHandledElementIndex <= 1 ) return;
	if(mCurrentIndex>mNumElements) return;
    //
    // Fill or modify your own stuff
    //
	int i=0;
	while(i<mCurrentIndex){
		if(mNumbers[i]>mNumbers[mCurrentIndex]){
			//mPrevElementIndex=i;
			insertElement(i);
			break;
		}
		i++;
	}
	/*for(int i=mCurrentIndex-1;i>=0;i--){
		if(mNumbers[i]>mNumbers[mCurrentIndex]){
			//mPrevElementIndex=i;
			insertElement(mPrevElementIndex);
			//break;
		}
	}*/
	mPrevElementIndex=i;
	//mMaxNonHandledElementIndex--;
    ++mCurrentIndex;
}

void SORTING_VISUALIZATION::processOneStep2(){
	if ( mNumElements <= 1) return;
    //if ( mMaxNonHandledElementIndex <= 1 ) return;
	if(mCurrentIndex>mNumElements) return;
    //
    // Fill or modify your own stuff
    //
	int i=0;
	while(i<mCurrentIndex){
		if(mNumbers[i]<mNumbers[mCurrentIndex]){
			//mPrevElementIndex=i;
			insertElement(i);
			break;
		}
		i++;
	}
	/*for(int i=mCurrentIndex-1;i>=0;i--){
		if(mNumbers[i]>mNumbers[mCurrentIndex]){
			//mPrevElementIndex=i;
			insertElement(mPrevElementIndex);
			//break;
		}
	}*/
	mPrevElementIndex=i;
	//mMaxNonHandledElementIndex--;
    ++mCurrentIndex;

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
    //
    // Fill or modify your own stuff
    //
    //return 10;
    return mNumbers[ elementIndex ];
}