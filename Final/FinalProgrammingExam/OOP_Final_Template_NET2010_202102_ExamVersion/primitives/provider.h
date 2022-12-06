//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// Date: 2014/10/09
//
//------------------------------

#ifndef __PROVIDER_H_
#define __PROVIDER_H_

/*
Assign each element an ID from 0 to mMaxNumOfElements-1.
*/
template <class T> class PROVIDER {
	protected:
		T *mEleArr;
		int mMaxNumOfElements;
		int *mFreeEleIndexArr;
		int mCurNumOfFreeElements;
		int *mUsedEleIndexArr[2];
		int mCurNumOfUsedElements[2];
		int mUsedEleIndexArrIndex;
		
public:
	PROVIDER( ) {
		mEleArr = 0;
		mMaxNumOfElements = 0;
		mCurNumOfFreeElements = 0;
		mFreeEleIndexArr = 0;
		mUsedEleIndexArr[0] = 0;
		mUsedEleIndexArr[1] = 0;
		mCurNumOfUsedElements[0] = 0;
		mCurNumOfUsedElements[1] = 0;
		mUsedEleIndexArrIndex = 0;

	}
	T* init( int num ) {
		mMaxNumOfElements = num;
		mEleArr = new T[mMaxNumOfElements];
		mFreeEleIndexArr = new int[mMaxNumOfElements];
		mUsedEleIndexArr[0] = new int[mMaxNumOfElements];
		mUsedEleIndexArr[1] = new int[mMaxNumOfElements];

		mCurNumOfFreeElements = mMaxNumOfElements;
		for (int i = 0; i < mMaxNumOfElements; ++i ) {
			mEleArr[i]._index = i;
			mFreeEleIndexArr[i] = i;
		}
		mCurNumOfUsedElements[0] = 0;
		mCurNumOfUsedElements[1] = 0;
		mUsedEleIndexArrIndex = 0;
		return mEleArr;
	}

	void reset( )
	{
		mCurNumOfFreeElements = mMaxNumOfElements;
		for (int i = 0; i < mMaxNumOfElements; ++i ) {
			mEleArr[i]._index = i;
			mFreeEleIndexArr[i] = i;
		}
		mCurNumOfUsedElements[0] = 0;
		mCurNumOfUsedElements[1] = 0;
		mUsedEleIndexArrIndex = 0;
	}

	// -1: invalid
	int getFreeElement( )
	{
		if ( mCurNumOfFreeElements <= 0 ) {
			return -1;
		}
		--mCurNumOfFreeElements;
		int index = mCurNumOfFreeElements;
		
		mUsedEleIndexArr[mUsedEleIndexArrIndex][ mCurNumOfUsedElements[mUsedEleIndexArrIndex] ] = mFreeEleIndexArr[index];
		++mCurNumOfUsedElements[mUsedEleIndexArrIndex];
		return mFreeEleIndexArr[index];
	}

	int *getUsedEleIndexArr( int &num ) const {
		num = mCurNumOfUsedElements[mUsedEleIndexArrIndex];
		return mUsedEleIndexArr[mUsedEleIndexArrIndex];
	}

	void begin_update( )
	{
		int arrIndex = (mUsedEleIndexArrIndex+1)%2; //cyclic 0->1->0-> ...etc
		mCurNumOfUsedElements[ arrIndex ] = 0;
	}

	void updateUsedElement( int index ) 
	{
		int arrIndex = (mUsedEleIndexArrIndex+1)%2;
		if ( mEleArr[index].isEnabled == false ) {
			mFreeEleIndexArr[mCurNumOfFreeElements] = index;
			++mCurNumOfFreeElements;
		} else {
			mUsedEleIndexArr[arrIndex][ mCurNumOfUsedElements[arrIndex] ] = index;
			++mCurNumOfUsedElements[arrIndex];
		}
	}
	void end_update( )
	{
		mUsedEleIndexArrIndex = (mUsedEleIndexArrIndex+1)%2;
	}

};

#endif