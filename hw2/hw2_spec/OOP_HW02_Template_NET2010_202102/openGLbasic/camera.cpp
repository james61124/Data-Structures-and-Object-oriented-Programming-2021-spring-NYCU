#include "../headers.h"

#include "camera.h"

using namespace std;

CAMERA::CAMERA( )
{
	mWindowWidth = 512;
	mWindowHeight = 512;
	mZnear = 0.1f;
	mZfar = 200.0f;
	//
	mOrthoMarginX = 100.0;
	mOrthoMarginZ = 100.0;

	mFlgDragging = false;
	mCurX = 0;
	mCurY = 0;

	//mType = CAMERA_TYPE_PERSPECTIVE;
	mType = CAMERA_TYPE_ORTHOGONAL;

	mZoomFactor = 80.0f;
	mZoomChangeUnit = 1.0f;

	mTranslationXYZ = vec3( 0.0, 0.0, 0.0 );
	if ( mType == CAMERA_TYPE_PERSPECTIVE ) {
		//mTranslationXYZ = vec3(0, 0, -10.0);
		mTranslationXYZ = vec3(-5.0, 5.0, -15.0);
	//mTranslationXYZ = vec3(-5.0, -5.0, -15.0);
	} else if ( mType ==  CAMERA_TYPE_ORTHOGONAL ) {
		mTranslationXYZ = vec3( 0.0, 0.0, 0.0 );
	}
}

void CAMERA::setViewport( int w, int h )
{
	mWindowWidth = w;
	mWindowHeight = h;

}

void CAMERA::init( )
{
	updateCamera( );

}

void CAMERA::set(const vec3 &v)
{
    mTranslationXYZ = v;
    
}
void CAMERA::setZoom(double v)
{
    mZoomFactor = v;
}
void CAMERA::translate(const vec3 &v)
{
	switch( mType ) {
		case CAMERA_TYPE_ORTHOGONAL:
		mZoomFactor += v.z*0.05f;
		break;
		case CAMERA_TYPE_PERSPECTIVE:
		mTranslationXYZ += v;
		break;
	}
	updateCamera( );
/////////////////////////////
    cout << "mZoomFactor:" << mZoomFactor << endl;

}

void CAMERA::dragging( int x, int y )
{
	if ( mFlgDragging == false ) return;
	float dx = (float) (x - mCurX);
	float dy = (float) (y - mCurY);
	float sensitivity_factor = 0.005f;
	switch( mType ) {
		case CAMERA_TYPE_ORTHOGONAL:
			mTranslationXYZ += sensitivity_factor*vec3(dx, -dy, 0)*5.0;
		break;
		case CAMERA_TYPE_PERSPECTIVE:
		mTranslationXYZ += sensitivity_factor*vec3(dx, -dy, 0);
		break;
	}
	updateCamera( );
	mCurX = x;
	mCurY = y;
    /////////////////////////////
    cout << "mTranslationXYZ:" << mTranslationXYZ.x << "\t" << mTranslationXYZ.y << "\t" << mTranslationXYZ.z << endl;
}

void CAMERA::setDragging( int x, int y )
{
	mCurX = x;
	mCurY = y;

	mFlgDragging = true;

}

void CAMERA::endDragging( int x, int y )
{
	updateCamera( );
	mFlgDragging = false;

}

void CAMERA::getCoordinates(float &x, float &y, float &z, float mx, float my)
{
	if ( mType != CAMERA_TYPE_ORTHOGONAL) {
		cout << "CAMERA::getCoordinates: wrong type" << endl;
		return;
	}
	// mx, my : mouse x, mouse y
	x = y = z = 0.0;

	float aspect_ratio;

	aspect_ratio = mWindowWidth/(GLfloat) mWindowHeight;

	float xmin, xmax, ymin, ymax, zmin, zmax;
	float xw, zw;
	//xw = 10.0;
	//zw = 10.0;
	
	xw = mOrthoMarginX; // margin
	zw = mOrthoMarginZ;
	
	xmin = 	(- xw + mZoomFactor*mZoomChangeUnit);
	xmax = 	(+ xw - mZoomFactor*mZoomChangeUnit);
	float xWidth = xmax - xmin;
	zmin = -10.0;
	zmax = 10.0;

	ymin = 	(- zw + mZoomFactor*mZoomChangeUnit)/aspect_ratio;
	ymax = 	(+ zw - mZoomFactor*mZoomChangeUnit)/aspect_ratio;

	float yWidth = ymax - ymin;
	
	//mTranslationXYZ[0], mTranslationXYZ[1], mTranslationXYZ[2]

	float ix = mx / (float) mWindowWidth;


	float iy = ( mWindowHeight - my ) / (float)mWindowHeight;

	ix = ix*xWidth-xWidth*0.5f;
	iy = iy*yWidth-yWidth*0.5f;

	//ix = (ix - xmin)/(xmax - xmin)*xWidth;
	//iy = (iy - ymin)/(ymax - ymin)*yWidth;

	ix -= mTranslationXYZ[0];
	iy -= mTranslationXYZ[1];

	x = ix;
	z = iy;
}

void CAMERA::getOrthoActualMargins( float &xmin, float &xmax, float &zmin, float &zmax )
{
	xmin = mOrthoMinX-mTranslationXYZ[0];
	xmax = mOrthoMaxX-mTranslationXYZ[0];
	zmin = mOrthoMinZ-mTranslationXYZ[1];
	zmax = mOrthoMaxZ-mTranslationXYZ[1];
}

void CAMERA::updateCamera( )
{

	float aspect_ratio;

	float xmin, xmax, ymin, ymax, zmin, zmax;
	float xw, zw;
	xw = mOrthoMarginX; // margin
	zw = mOrthoMarginZ;
	switch( mType ) {
		case CAMERA_TYPE_ORTHOGONAL:
			aspect_ratio = mWindowWidth/(GLfloat) mWindowHeight; // BUG FREE
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity( );
			xmin = 	(- xw + mZoomFactor*mZoomChangeUnit);
			xmax = 	(+ xw - mZoomFactor*mZoomChangeUnit);
			zmin = -10.0;
			zmax = 10.0;
			ymin = 	(- zw + mZoomFactor*mZoomChangeUnit)/aspect_ratio;
			ymax = 	(+ zw - mZoomFactor*mZoomChangeUnit)/aspect_ratio;
			glOrtho( xmin, xmax, ymin, ymax, zmin, zmax );
			mOrthoMinX = xmin;
			mOrthoMaxX = xmax;
			mOrthoMinZ = ymin;
			mOrthoMaxZ = ymax;
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity( );
			glTranslatef(mTranslationXYZ[0], mTranslationXYZ[1], mTranslationXYZ[2]);
			glRotatef(-90.0, 1.0, 0, 0); // rotate 90 degrees about the x-axis
			break;
		case CAMERA_TYPE_PERSPECTIVE:
			aspect_ratio = mWindowWidth/(GLfloat) mWindowHeight; // BUG FREE
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity( );
			gluPerspective(45.0, aspect_ratio, mZnear,mZfar);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity( );
			glTranslatef(mTranslationXYZ[0], mTranslationXYZ[1], mTranslationXYZ[2]);
			//static float angle = 0.0;
			//angle += 0.1;
			//glRotatef(-90, 1, 0, 0);
			glRotatef(90, 1.0, 0, 0);
			//
			break;
	}
	glGetFloatv(GL_MODELVIEW_MATRIX, mModelViewMatrix);
	glGetFloatv(GL_PROJECTION_MATRIX, mProjectMatrix);
}


void CAMERA::getProjectionMatrix( mat4 &m ) const
{
	m = mProjectMatrix;
}

void CAMERA::getModelViewMatrix( mat4 &m ) const
{
	m = mModelViewMatrix;
}