//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
//
/*
Visualizing the process of sorting some integers.
*/
#ifndef __MY_SORTING_VISUALIZATION_BUBBLE_H_
#define __MY_SORTING_VISUALIZATION_BUBBLE_H_
#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
#include <vector>
#include "base_class.h"
using std::vector;
class SORTING_VISUALIZATION_BUBBLE : public BASE_SYSTEM
{
protected:
    vector<int> mNumbers;
    int mNumElements;
    int mMinValue, mMaxValue;
    int mCurrentIndex;
    int mMaxNonHandledElementIndex;
//
    void checkAndSwapTwoElements( int index );
public:
    SORTING_VISUALIZATION_BUBBLE( );
    void reset( );
    void askForInput( );
    int getNumOfElements( ) const;
    int getElement( int elementIndex ) const;
    int getMaxNonHandledElementIndex( ) const;
    void processOneSwapStep( );
    int getCurrentElementIndex( ) const;
};
#endif