//
// Prof. Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/04/
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

	//drawOrigin( );

//    if ( mColorPalette ) {
       // mColorPalette->draw( );
 //   }

	FREE_CANVAS_2D::end_draw( );
	//cout << "END CROWD_SIMULATION_APP::draw( )" << endl;
	glEnable( GL_LIGHTING );
}

void MY_SYSTEM_APP::draw_System_Content( ) const
{
    mCurSystem->draw( );
    if ( mCurSystem == mMy2048 ) {
       mPrev_2048->copyPrevious( mCurSystem );
        mPrev_2048->draw( );
    }

    return;
	switch( mSystemType ) {
		case SYSTEM_TYPE_MONTE_CARLO_SIMULATION:
//			draw_MonteCarlo_Simulation( );
			break;
		case SYSTEM_TYPE_GALAXY_SYSTEM:
//			draw_GalaxySystem( );
			break;
		case SYSTEM_TYPE_SIMPLE_PAINTER:
//			draw_SimplePainter( );
			break;
		case SYSTEM_TYPE_SORTING_VISUALIZATION:
///			draw_SortingVisualization( );
			break;
        case SYSTEM_TYPE_SIMPLE_FILE_EDITOR:
//			draw_SimpleFileEditor( );
            
            break;

	}
}


void drawDisk(double x, double y, double r)
{
    int numSamples = 12;
    glBegin(GL_TRIANGLES);
    for ( int i = 0; i < numSamples; ++i ) {
        double da = 1.0/(double) (numSamples-1)*3.141592654*2.0;

        double a = i*da;
        double x0 = x + r*cos(a);
        double y0 = y + r*sin(a);
        double x1 = x + r*cos(a+da);
        double y1 = y + r*sin(a+da);
        glVertex3f( x, 0.0, y );
        

        glVertex3f( x0, 0.0, y0 );

        glVertex3f( x1, 0.0, y1 );


    }
    glEnd( );
}

void drawCircle(double x, double y, double r)
{
    int numSamples = 36;
    glBegin(GL_LINE_LOOP);
    for ( int i = 0; i < numSamples; ++i ) {
        double da = 1.0/(double) (numSamples-1)*3.141592654*2.0;

        double a = i*da;
        double x0 = x + r*cos(a);
        double y0 = y + r*sin(a);
        glVertex3f( x0, 0.0, y0 );
    }
    glEnd( );
}
