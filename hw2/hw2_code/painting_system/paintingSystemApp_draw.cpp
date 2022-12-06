#include "paintingSystemApp.h"

using namespace std;

void PAINTING_SYSTEM_APP::drawOrigin( ) const
{
	glLineWidth( 7.0 );
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f( -5.0, 0.0, 0.0 );
	glVertex3f( 5.0, 0.0, 0.0 );
	glEnd( );
	//
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f( 0.0, 0.0, -5.0 );
	glVertex3f( 0.0, 0.0, 5.0 );
	glEnd( );
}

void PAINTING_SYSTEM_APP::draw( ) const
{
		glClearColor( 1.0, 1.0, 1.0, 1.0 );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable( GL_LIGHTING );
	FREE_CANVAS_2D::begin_draw( );
	

	//cout << "BGN CROWD_SIMULATION_APP::draw( ):" << mCurNumOfAgents << endl;
	glLineWidth(1.0);
	//glColor3f(1.0, 1.0, 1.0);
	glColor3f(0.5, 0.5, 0.5);

	if ( mFlgShow_Grid ) {
		FREE_CANVAS_2D::draw_wire_grid( );
	}

	if ( mPictureTexture ) {
		//cout << "here" << endl;
		mPictureTexture->use( );
		mPictureTexture->drawTextureWithScale_XZ( 0.0f, 0.0f, (float)mImageWidth, (float)mImageHeight );
		mPictureTexture->end( );
	}
	glPointSize(5.0);
	glColor3f(1.0, 1.0, 0.0);

	drawOrigin( );

	
	FREE_CANVAS_2D::end_draw( );
	//cout << "END CROWD_SIMULATION_APP::draw( )" << endl;
	glEnable( GL_LIGHTING );
}