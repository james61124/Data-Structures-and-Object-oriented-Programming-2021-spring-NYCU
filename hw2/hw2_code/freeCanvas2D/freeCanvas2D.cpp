#include "freeCanvas2D.h"

FREE_CANVAS_2D::FREE_CANVAS_2D( )
{
	mGridCellSizeDX = 1.0;
	mGridCellSizeDZ = 1.0;
	mProjRangeMin = vector3( -100.0, -100.0, -30.0 );
	mProjRangeMax = vector3(  100.0,  100.0,  30.0 );

	mCanvasWidth = 0;
	mCanvasHeight = 0;
	mCamera = new CAMERA;
}

void FREE_CANVAS_2D::setGridCellDimension( int gw, int gh )
{
	mGridCellSizeDX = (float) gw;
	mGridCellSizeDZ = (float) gh;
}

void FREE_CANVAS_2D::setCanvasDimension( int w, int h )
{
	mCanvasWidth = w;
	mCanvasHeight = h;
}

void FREE_CANVAS_2D::getCanvasDimension( int &w, int &h ) const
{
	w = mCanvasWidth;
	h = mCanvasHeight;
}

void FREE_CANVAS_2D::reshape( int w, int h)
{

	mCanvasWidth = w;
	mCanvasHeight = h;
	/////////////////////////////////////
	//glViewport(0, 0, w, h);
	if ( mCamera ) mCamera->setViewport( w, h );
	//glutPostRedisplay();
}

bool FREE_CANVAS_2D::passiveMouseFunc( int mx, int my )
{
	float fx, fy, fz;
		fx = (float)mx;
		fy = 0.0;
		fz = (float)my;

		float x, y, z;
		mCamera->getCoordinates( x, y, z, (float)mx, (float)my );
		//cout << "x y z:" << x << "\t" << y << "\t" << z << endl;
		//mCrowdSimulation->pickAgent( x, 0.0, z, true );

		return true;
}

bool FREE_CANVAS_2D::mouseMotionFunc( int x, int y )
{
	if ( mCamera ) 
	{
		mCamera->dragging( x, y );
	}
		return true;

}

bool FREE_CANVAS_2D::mouseFunc( int button, int state, int mx, int my )
{
    
	switch ( button ) {
		case GLUT_RIGHT_BUTTON:
			if (state == GLUT_DOWN) {
				if (mCamera) {
					mCamera->setDragging( mx, my );
				}
			} else if (state == GLUT_UP) {
				if (mCamera) {
					mCamera->endDragging( mx, my );
				}
			}
			break;
			case GLUT_LEFT_BUTTON:
				
				//mCamera->getCoordinates( x, y, z, mx, my );
				//mCrowdSimulation->handleMouseEvents( button, state, x, y, z );
			break;
			case 3:
				if (mCamera) {
					mCamera->translate(vec3(0, 0, 10.0));
				}
				break;
			case 4:
				if (mCamera) {
					mCamera->translate(vec3(0, 0, -10.0));
				}
				break;
	}
		return true;

}

bool FREE_CANVAS_2D::handleKeyEvent( unsigned char key )
{
	return true;
}

void FREE_CANVAS_2D::begin_draw( ) const
{
	mCamera->updateCamera( );
}

void FREE_CANVAS_2D::end_draw( ) const
{
}

void FREE_CANVAS_2D::draw_wire_grid( ) const
{
	float xmin, xmax;
	float zmin, zmax;
	mCamera->getOrthoActualMargins( xmin, xmax, zmin, zmax );
	//
	int xmin_i = (int) (xmin/mGridCellSizeDX - 1);
	int xmax_i = (int) (xmax/mGridCellSizeDX + 1);
	int zmin_i = (int) (zmin/mGridCellSizeDZ - 1);
	int zmax_i = (int) (zmax/mGridCellSizeDZ + 1);

	glBegin(GL_LINES);
	for ( int i = xmin_i; i <= xmax_i; ++i ) {
		float x;
		x = i*mGridCellSizeDX;
		glVertex3f( x, -0.1f, zmin );
		glVertex3f( x, -0.1f, zmax );
	}

	for ( int i = zmin_i; i <= zmax_i; ++i ) {
		float z;
		z = i*mGridCellSizeDZ;
		glVertex3f( xmin, -0.1f, z );
		glVertex3f( xmax, -0.1f, z );
	}
	glEnd( );

	/*
	int xmin_i = xmin - 1;
	int xmax_i = xmax + 1;

	int zmin_i = zmin - 1;
	int zmax_i = zmax + 1;

	//
	// mGridCellSizeDX
	//
	glBegin(GL_LINES);
	for ( int i = xmin_i; i <= xmax_i; ++i ) {
		glVertex3f( i, -0.1, zmin_i );
		glVertex3f( i, -0.1, zmax_i );
	}

	for ( int i = zmin_i; i <= zmax_i; ++i ) {
		glVertex3f( xmin_i, -0.1, i );
		glVertex3f( xmax_i, -0.1, i );
	}
	glEnd( );
	*/
}
