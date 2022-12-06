//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// Date: 2014/12/10
//
#ifndef __PAINTING_SYSTEM_H_
#define __PAINTING_SYSTEM_H_
#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
class PAINTING_SYSTEM
{
protected:
	float mTimeStep;
	int mImageWidth, mImageHeight;
	unsigned char *mImagePtr;
	//
	int mVelocityMode;
	vector3 *mCur_VelocityField;
	vector3 *mPre_VelocityField;

	vector3 *mVelocityField1;
	vector3 *mVelocityField0;


	void updateVelocityMode( );
	void initInternalVariables( );
	void boundaryConstraint( int &x, int &z );
	void setImagePtr( unsigned char *image_ptr, int w, int h );
	void setVelocityField( int x, int z, const vector3 &v );
	void setColor( int x, int z, const vector3 &color );
public:
	PAINTING_SYSTEM( );
	void update(  bool flg_timer = false );
	void clickAt( int x, int y, const vector3 &color );
};
#endif