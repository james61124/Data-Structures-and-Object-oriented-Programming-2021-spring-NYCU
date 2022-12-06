//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/06/17
//
/*
Visualizing the process of sorting some integers.
*/
#ifndef __MY_SORTING_VISUALIZATION_H_
#define __MY_SORTING_VISUALIZATION_H_
#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
#include <vector>
#include "base_class.h"
using std::vector;

#define SORTING_ORDER_INCREASING 1
#define SORTING_ORDER_DECREASING 2

class SORTING_VISUALIZATION : public BASE_SYSTEM
{
protected:
    vector<int> mNumbers;
    int mNumElements;
    int mMinValue, mMaxValue;
    int mCurrentIndex;
    int mMaxNonHandledElementIndex;
    int mPrevElementIndex;
    int mSortingOrder;
//
    void shiftToRight( 
    int start_index
    , int end_index 
    );

    int getNumOfElements( ) const;
    int getElement( int elementIndex ) const;
    int getMaxNonHandledElementIndex( ) const;

    int getPreviousElementIndex( ) const;
    int getCurrentElementIndex( ) const;
    void insertElement(int index);
    void processOneStep( );
	void processOneStep2();
    void resetSorting( );
public:
    SORTING_VISUALIZATION( );
    bool handleKeyPressedEvent( unsigned char key );
    void reset( );
    void draw( ) const;
    void askForInput( ) { }
};
#endif