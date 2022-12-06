//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/03/01
//
#include "mySystemApp.h"

using namespace std;

void MY_SYSTEM_APP::drawOrigin( ) const
{
	glLineWidth( 3.0 );
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f( -100.0, 0.0, 0.0 );
	glVertex3f( 100.0, 0.0, 0.0 );
	glEnd( );
	//
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f( 0.0, 0.0, -100.0 );
	glVertex3f( 0.0, 0.0, 100.0 );
	glEnd( );
}

void MY_SYSTEM_APP::draw( ) const
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable( GL_LIGHTING );
	FREE_CANVAS_2D::begin_draw( );

	glLineWidth(1.0);
	glColor3f(0.5, 0.5, 0.5);



	if ( mFlgShow_Grid ) {
		FREE_CANVAS_2D::draw_wire_grid( );
	}

	draw_System_Content( );

	drawOrigin( );

	FREE_CANVAS_2D::end_draw( );
	//cout << "END CROWD_SIMULATION_APP::draw( )" << endl;
	glEnable( GL_LIGHTING );
}

void MY_SYSTEM_APP::draw_System_Content( ) const
{
	switch( mSystemType ) {
		case SYSTEM_TYPE_MONTE_CARLO_CIRCLE:
			draw_MonteCarlo_Circle( );
			break;
		case SYSTEM_TYPE_SINECOSINE_FUNCTION:
			draw_SineCosineFunction( );
			break;
		case SYSTEM_TYPE_CUBIC_FUNCTION:
			draw_CubicFunction( );
			break;
		case SYSTEM_TYPE_STUDENT_RECORD_MANAGER:
			draw_StudentRecordManager( );
			break;

	}
}


void MY_SYSTEM_APP::draw_MonteCarlo_Circle( ) const
{
	float r = mMonteCarloSystem.getRadius( );


	int numSamplingPoints = 36;
	glColor3f( 0.5, 0.5, 0.0);
	glLineWidth( 3.0 );
	glBegin( GL_LINE_LOOP );
	for ( int i = 0; i < numSamplingPoints; ++i ) {
		float x, y, z;
		float a = i/(float) numSamplingPoints*2.0*3.1415;
		x = r*cos(a);
		y = 0.0;
		z = r*sin(a);
		glVertex3f(x, y, z);
	}
	glEnd( );


	glPointSize( 2.0 );
	bool flgInside;
	int numSamples = mMonteCarloSystem.getNumSamples( );
	glBegin( GL_POINTS );
	for ( int i = 0; i < numSamples; ++i ) {
		float x, z;
		flgInside = mMonteCarloSystem.getSample(i, x, z );
		if ( flgInside ) {
			glColor3f( 1.0, 0.5, 0.0 );
		} else {
			glColor3f( 0.0, 0.0, 0.7 );
		}
		glVertex3f( x, 0.0, z );
	}
	glEnd( );
}
void MY_SYSTEM_APP::draw_SineCosineFunction( ) const
{
	glLineWidth(2.0);
	glColor3f(0.3, 0.3, 0.8 );

	double x0, x1;
	mSineCosineFunction.getRangeOfX( x0, x1 );
	glBegin(GL_LINE_STRIP );

	int numSamples = mSineCosineFunction.getNumOfSamples( );
	for ( int i = 0; i < numSamples; ++i ) {
		double y;
		double x;
		x = x0 + (i/((double) numSamples -1))*(x1 - x0);
		y = mSineCosineFunction.getValue( x );
		glVertex3f( x, 0.0, y );
	}
	glEnd( );
}

void MY_SYSTEM_APP::draw_CubicFunction( ) const
{
	glLineWidth(6.0);
	glColor3f(0.2, 0.2, 0.2 );

	double x0, x1;
	mCubicFunction.getRangeOfX( x0, x1 );
	glBegin(GL_LINE_STRIP );
	int numSamples = mCubicFunction.getNumOfSamples( );
	for ( int i = 0; i < numSamples; ++i ) {
		float y;
		float x;
		x = x0 + (i/((double) numSamples -1))*(x1 - x0);
		y = mCubicFunction.getValue( x );
		glVertex3f( x, 0.0, y );
	}
	glEnd( );

    glLineWidth(3.0);
	glColor3f(0.9, 0.9, 0.0 );
    glBegin(GL_LINE_STRIP );
	numSamples = mCubicFunction.getNumOfSamples( );
	for ( int i = 0; i < numSamples; ++i ) {
		float y;
		float x;
		x = x0 + (i/((double) numSamples -1))*(x1 - x0);
		y = mCubicFunction.getValue( x );
		glVertex3f( x, 0.0, y );
	}
	glEnd( );

	glLineWidth(2.0);

}

void MY_SYSTEM_APP::draw_StudentRecordManager( ) const
{
	int numPieces = 10;
	glBegin( GL_QUADS );
	for ( int i = 0; i < numPieces; ++i ) {
		float fraction = i/(float) (numPieces);
		glColor3f(0.3, 0.3, 0.5+ 0.5*fraction );
		float x0, y, x1;
		x0 = i*1;
		x1 = x0 + 1;
		int s0, s1;
		s0 = i*10;
		s1 = s0 + 10-1;
		if ( i == 9 ) s1 = 100;
		y = mStudentRecordManager.getNumOfStudentsInScoreInterval( s0, s1 );
		glVertex3f( x0, 0.0, 0.0 );
		glVertex3f( x1, 0.0, 0.0 );
		glVertex3f( x1, 0.0, y );
		glVertex3f( x0, 0.0, y );
	}
	glEnd( );
}
// CODE: 2021/03/01. Do not delete this line.