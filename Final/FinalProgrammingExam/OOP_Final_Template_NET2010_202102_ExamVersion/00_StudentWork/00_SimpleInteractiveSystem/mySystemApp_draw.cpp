//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
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


	FREE_CANVAS_2D::end_draw( );
	//cout << "END CROWD_SIMULATION_APP::draw( )" << endl;
	glEnable( GL_LIGHTING );
}

void MY_SYSTEM_APP::draw_System_Content( ) const
{
    mCurSystem->draw( );

    return;
}


void MY_SYSTEM_APP::draw_MonteCarlo_Simulation( ) const
{

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
void MY_SYSTEM_APP::draw_GalaxySystem( ) const
{
}

void MY_SYSTEM_APP::draw_SimplePainter( ) const
{


}

void MY_SYSTEM_APP::draw_SortingVisualization( ) const
{

}

void MY_SYSTEM_APP::draw_SimpleFileEditor( ) const
{
    /*
    int nx, ny;
    mSimpleFileEditor.getBitmapDimension( nx, ny );
    
    glPointSize( 5.0 );
    glBegin( GL_POINTS );
    for ( int j = 0; j < ny; ++j ) {
        for ( int i = 0; i < nx; ++i ) {
            int x = i;
            int z = ny - j - 1; 
            int v = mSimpleFileEditor.getBitmapValue( i, j );
            float c = v/255.0;
            if ( c > 1.0 ) c = 1.0;
            else if ( c < 0.0 ) c = 0.0;
            
            float r = 0.0, g = 0.0, b = 0.0;
            r = g = b = c;

            if ( c < 0.2 && c > 0.0 ) g = 1.0;
            if ( c > 0.2 ) r = 1.0;
            if ( c > 0.5 ) { r = b = 0.0; g = 1.0; }
            if ( c > 0.7 ) { r = 0.5; b = 1.0; }

           // if ( c > 0.0 ) g = 1.0;
            glColor3f(r, g, b);
        glVertex3f( x, 0.0, z );
    }
    }
    glEnd( );
    */
    
}