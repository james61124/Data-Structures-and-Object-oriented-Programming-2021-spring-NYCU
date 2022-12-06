//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// Date: 2014/12/10
//
#ifndef __FREE_CANVAS_2D_H_
#define __FREE_CANVAS_2D_H_
#include "../headers.h"
#include <string>
#include "../basic_app.h"
#include "../primitives/vector3d.h"
#include "../openGLbasic/camera.h"

class FREE_CANVAS_2D : public BASIC_APP
{
protected:
	int mCanvasWidth, mCanvasHeight;
	float mGridCellSizeDX, mGridCellSizeDZ;
	vector3 mProjRangeMin;
	vector3 mProjRangeMax;
	//
	CAMERA *mCamera;
public:
	FREE_CANVAS_2D( );
	void setCanvasDimension( int w, int h );
	void getCanvasDimension( int &w, int &h ) const;
	void setGridCellDimension( int gw, int gh );
	virtual void begin_draw( ) const;
	virtual void end_draw( ) const;
	virtual void draw_wire_grid( ) const;
	//
	virtual void reshape( int w, int h);
	virtual bool mouseMotionFunc( int x, int y );
	virtual bool mouseFunc( int button, int state, int x, int y );
	virtual bool passiveMouseFunc( int x, int y );
	virtual bool handleKeyEvent( unsigned char key );
};

#endif