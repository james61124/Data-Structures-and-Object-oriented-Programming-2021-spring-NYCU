#include "paintingSystem.h"

PAINTING_SYSTEM::PAINTING_SYSTEM( )
{
	mImagePtr = 0;
	mImageWidth =0;
	mImageHeight = 0;
	mVelocityField0 = 0;
	mVelocityField1 = 0;

	mTimeStep = 0.03f;
}

void PAINTING_SYSTEM::initInternalVariables( )
{
}

void PAINTING_SYSTEM::setImagePtr( unsigned char *image_ptr, int w, int h )
{
	mImagePtr = image_ptr;
	mImageWidth = w;
	mImageHeight = h;
	mVelocityField0 = new vector3[mImageWidth*mImageHeight];
	mVelocityField1 = new vector3[mImageWidth*mImageHeight];

	mVelocityMode = 0;
	mCur_VelocityField = mVelocityField0;
	mPre_VelocityField = mVelocityField1;
}

void PAINTING_SYSTEM::updateVelocityMode( ) 
{
	mVelocityMode = (mVelocityMode+1)%2;
	if ( mVelocityMode == 0 ) {
		mCur_VelocityField = mVelocityField0;
		mPre_VelocityField = mVelocityField1;
	} else {
		mCur_VelocityField = mVelocityField1;
		mPre_VelocityField = mVelocityField0;
	}
}
void PAINTING_SYSTEM::boundaryConstraint( int &x, int &z )
{
	if ( x <= 0) {
		x = 0;
	}
	if ( z <= 0) {
		z = 0;
	}
	if ( x >= mImageWidth ) {
		x = mImageWidth - 1;
	}

	if ( z >= mImageHeight ) {
		z = mImageHeight - 1;
	}
}

void PAINTING_SYSTEM::setColor( int x, int z, const vector3 &color )
{
	boundaryConstraint( x, z );
	int index = x + z*mImageWidth;
	int index3 = index*3;
	//
	mImagePtr[index3+0] = (unsigned char) color.r*255;
	mImagePtr[index3+1] = (unsigned char) color.g*255;
	mImagePtr[index3+2] = (unsigned char) color.b*255;
}


void PAINTING_SYSTEM::clickAt( int x, int z, const vector3 &color )
{
	boundaryConstraint( x, z );
	int index = x + z*mImageWidth;
	int index3 = index*3;
	//
	mImagePtr[index3+0] = (unsigned char) color.r*255;
	mImagePtr[index3+1] = (unsigned char) color.g*255;
	mImagePtr[index3+2] = (unsigned char) color.b*255;

	setVelocityField( x, z, vector3( 1.0, 0.0, 0.0) );
	setVelocityField( x+1, z, vector3( 1.0, 0.0, 0.0) );
	setVelocityField( x-1, z, vector3( -1.0, 0.0, 0.0) );
	setVelocityField( x, z-1, vector3( 0.0, 0.0, -1.0) );
	setVelocityField( x, z+1, vector3( 0.0, 0.0, 1.0) );
}

void PAINTING_SYSTEM::setVelocityField( int x, int z, const vector3 &v )
{
	int index;
	boundaryConstraint( x, z );
	index = z*mImageWidth + x;
	mCur_VelocityField[index] = v;
}


void PAINTING_SYSTEM::update(  bool flg_timer )
{
	return;
	vector3 c;
	vector3 v;
	for (int z = 0; z < mImageHeight; ++z )	{
		for (int x = 0; x < mImageWidth; ++x )	{
			int index = z*mImageWidth + x;
			float f = 0.2f;
			float r, g, b;
			v = mCur_VelocityField[ index ];
			r = (float) (mImagePtr[ index + 0 ])/255.0f;
			g = (float) (mImagePtr[ index + 1 ])/255.0f;
			b = (float) (mImagePtr[ index + 2 ])/255.0f;
			int fx, fz;
			fx = (int) (x + v.x);
			fz = (int) (z + v.z);
			c.r = r*f;
			c.g = g*f;
			c.b = b*f;


			setColor( fx, fz, c );
			
		}
	}

	updateVelocityMode( );
}
