//
// Computer Graphics
// National Chiao Tung University
//
// Instructor: Sai-Keung Wong
// Email: cswingo@cs.nctu.edu.tw
//

#ifndef __CAMERA_H__
#define __CAMERA_H__
#include <iostream>
#include "../primitives/mat.h"
#include "../primitives/vec.h"

#define CAMERA_TYPE_PERSPECTIVE		1
#define CAMERA_TYPE_ORTHOGONAL		2

using namespace Angel;

class CAMERA 
{
protected:
	int mType;
	;
	float mZoomFactor;
	float mZoomChangeUnit;
	float mOrthoMarginX;
	float mOrthoMarginZ;
	;
	float mOrthoMinX;
	float mOrthoMaxX;
	float mOrthoMinZ;
	float mOrthoMaxZ;

	;
	mat4 mProjectMatrix;
	mat4 mModelViewMatrix;
	int mWindowWidth, mWindowHeight;
	vec3 mTranslationXYZ;
	float mZnear, mZfar;
	bool mFlgDragging;
	int mCurX, mCurY;
public:
	CAMERA( );
	void init( );
	void updateCamera( );
	void setViewport( int w, int h );
	void getProjectionMatrix( mat4 &m ) const;
	void getModelViewMatrix( mat4 &m ) const;
	void translate(const vec3 &v);
	//
	void dragging( int x, int y );
	void setDragging( int x, int y );
	void endDragging( int x, int y );
	void getCoordinates(float &x, float &y, float &z, float mx, float my);
	void getOrthoActualMargins( float &xmin, float &xmax, float &zmin, float &zmax );
};

#endif