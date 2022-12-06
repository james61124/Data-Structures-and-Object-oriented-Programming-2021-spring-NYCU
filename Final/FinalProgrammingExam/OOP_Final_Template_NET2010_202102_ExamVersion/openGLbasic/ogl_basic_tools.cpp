#include <iostream>
#include "ogl_basic_tools.h"

using namespace std;

namespace {
	vector3 colorTable[] = {
		vector3(1.0, 0.0, 0.0),
		vector3(1.0, 0.5, 0.0),
		vector3(1.0, 1.0, 0.0),
		vector3(0.5, 1.0, 0.0),
		vector3(1.0, 0.7, 0.5),
		vector3(0.0, 0.0, 1.0),
		vector3(0.5, 0.0, 1.0),
		vector3(1.0, 0.0, 1.0),
		vector3(1.0, 0.5, 1.0),
		vector3(1.0, 0.5, 0.5),
		vector3(0.5, 0.5, 0.5)
	};
};

vector3 getColorFromColorTable(int index)
{
	int num = sizeof(colorTable)/sizeof(vector3);
	//cout << "num:" << num << endl;
	//cout << "index:" << index << endl;
	index = index%num;
	
	return colorTable[index];
}

COLOR_TABLE::COLOR_TABLE( )
{
	mMaxValue = 0.0;
	mFlgAutoUpdate = true;
	mFlgAutoScale = true;
}

void COLOR_TABLE::resetMaxValue( float v )
{
	mMaxValue = v;
}

void COLOR_TABLE::resetMinValue( float v )
{
	mMinValue = v;
}

void COLOR_TABLE::enableAutoScale( bool flg )
{
	mFlgAutoScale = flg;
}

void COLOR_TABLE::enableAutoUpdate(bool flg)
{
	mFlgAutoUpdate = flg;
}

void COLOR_TABLE::clear( )
{
		mColorValueArr.clear( );
	mColorMappedValue.clear( );
}
void COLOR_TABLE::updateMaxValue( float v ) const
{
	if ( v > mMaxValue ) mMaxValue = v;
}

void COLOR_TABLE::updateMinValue( float v ) const
{
    if ( v < mMinValue ) mMinValue = v;
}


void COLOR_TABLE::autoScale( )
{
	if ( mFlgAutoScale == false ) return;
	//float cur_max = mColorMappedValue.back( );
	int num = mColorMappedValue.size( );
	for ( int i = 0; i < num; ++i ) {
		mColorMappedValue[i] = mMinValue + (i/(float)(num - 1))*(mMaxValue-mMinValue);
	}
}


void COLOR_TABLE::addEntry(float v, const vector3 &c ) //incremental
{
    mColorMappedValue.push_back( v );
    mColorValueArr.push_back( c );
}

vector3 COLOR_TABLE::getColor_Linear( float v ) const
{
	if ( mFlgAutoUpdate ) {
		updateMinValue( v );
		updateMaxValue( v );
	}
	vector3 c;

	if ( mColorMappedValue.size( ) > 1 ) {
		if ( v <= mColorMappedValue[0] ) {
			c = mColorValueArr[0];
		} else if ( v >= mColorMappedValue.back( ) ) {
			c = mColorValueArr.back( );
		} else {
			int num = mColorMappedValue.size( ); 
			for ( int i = 1; i < num ; ++i ) {
				int j = num - i - 1;
				if ( v >= mColorMappedValue[j] ) {
					float f;
					f =  ( v - mColorMappedValue[ j ] )/( mColorMappedValue[ j + 1 ] - mColorMappedValue[ j ]);
					c = mColorValueArr[ j ]*(1.0 - f) + mColorValueArr[ j + 1 ]*f;
					break;
				} else {
				}
			}
		}
	} else {
		//only one color
		c = mColorValueArr[0];
	}
	return c;
}
