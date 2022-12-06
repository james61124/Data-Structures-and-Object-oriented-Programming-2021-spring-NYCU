//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// Date: 2014/10/09
//
#ifndef __OPENGL_BASIC_TOOLS_H__
#define __OPENGL_BASIC_TOOLS_H__
#include "../primitives/vector3d.h"
#include <vector>

using namespace std;

class COLOR_TABLE {
protected:
	vector<vector3> mColorValueArr;
	vector<float> mColorMappedValue;
	//
	mutable float mMinValue;
	mutable float mMaxValue;
	bool mFlgAutoUpdate;
	bool mFlgAutoScale;
	//
public:
	COLOR_TABLE( );
	void clear( );
    void resetMinValue( float v = 0.0 );
	void resetMaxValue( float v = 0.0 );
	void addEntry(float v, const vector3 &c ); //incremental
	vector3 getColor_Linear( float v ) const;
	void updateMaxValue( float v ) const;
	void updateMinValue( float v ) const;
	void enableAutoScale( bool flg );
	void enableAutoUpdate(bool flg);
	void autoScale( );
};

extern vector3 getColorFromColorTable(int index);
#endif