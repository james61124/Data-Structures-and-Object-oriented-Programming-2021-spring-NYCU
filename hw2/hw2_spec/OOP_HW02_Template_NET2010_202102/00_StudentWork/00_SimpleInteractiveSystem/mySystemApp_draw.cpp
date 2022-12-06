//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/03/29
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

    if ( mColorPalette ) {
        mColorPalette->draw( );
    }

	FREE_CANVAS_2D::end_draw( );
	//cout << "END CROWD_SIMULATION_APP::draw( )" << endl;
	glEnable( GL_LIGHTING );
}

void MY_SYSTEM_APP::draw_System_Content( ) const
{
	switch( mSystemType ) {
		case SYSTEM_TYPE_MONTE_CARLO_SIMULATION:
			draw_MonteCarlo_Simulation( );
			break;
		case SYSTEM_TYPE_GALAXY_SYSTEM:
			draw_GalaxySystem( );
			break;
		case SYSTEM_TYPE_SIMPLE_PAINTER:
			draw_SimplePainter( );
			break;
		case SYSTEM_TYPE_SORTING_VISUALIZATION:
			draw_SortingVisualization( );
			break;
        case SYSTEM_TYPE_SIMPLE_FILE_EDITOR:
			draw_SimpleFileEditor( );
            
            break;

	}
}


void MY_SYSTEM_APP::draw_MonteCarlo_Simulation( ) const
{

/*
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
*/

    double minX, maxX;
    mMonteCarloSystem.getRangeOfX( minX, maxX );
    
	glPointSize( 2.0 );
    int numSamples = mMonteCarloSystem.getNumSamples();
	
    glBegin( GL_POINTS );
	for ( int i = 0; i < numSamples; ++i ) {
        double x, y;
        mMonteCarloSystem.getSample( i, x, y );
        bool flgInside = mMonteCarloSystem.isInsideArea( x, y );

        if ( flgInside ) {
            glColor3f( 1.0, 0.0, 0.0);
        } else {
            glColor3f( 0.25, 0.75, 0.25);
        }
        glVertex3f( x, 0.0, y );
    }
    glEnd( );
	glPointSize( 1.0 );

    glLineWidth(3.0);
    
    int numSegments = 100;
    double f = 1.0/(double)(numSegments);
    glColor3f(0.0, 0.0, 0.0);
    glBegin( GL_LINE_STRIP );
	for ( int i = 0; i < numSegments+1; ++i ) {
		double r0 = i*f;
        double x0 = minX + r0*(maxX - minX);
		double y0 = mMonteCarloSystem.getValue( x0 );
        
        glVertex3f( x0, -1.0, y0 );
	}
	glEnd( );
    
    glLineWidth(3.0);

	//int numSamples = mMonteCarloSystem.getNumSamples( );

    static double ani_x = 0.0;

    ani_x += (maxX - minX)/2000.0;
    if ( ani_x > maxX ) ani_x =  minX;

    double ani_y = mMonteCarloSystem.getValue( ani_x );
    glColor3f(0.0, 0.0, 1.0);
    
    glBegin(GL_LINES);
    glVertex3f( ani_x, -0.5, ani_y );
    glVertex3f( ani_x, -0.5, 0.0 );

    glEnd( );
    glLineWidth(1.0);

    glPointSize(16.0);
    glColor3f(1.0, 0.5, 0.0);
    
    glBegin(GL_POINTS);
    glVertex3f( ani_x, -1.5, ani_y );
    glEnd( );
    glPointSize(1.0);


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
    /*
	glLineWidth(2.0);
	glColor3f(0.3, 0.3, 0.8 );
    glPointSize(5);
	glBegin(GL_POINTS );
    int numObjs = mGalaxySystem.getNumOfObjs( );
	for ( int i = 0; i < numObjs; ++i ) {
		double y;
		double x;
        double r = mGalaxySystem.getObjInfo(i, x, y);
		glVertex3f( x, 0.0, y );
	}
	glEnd( );
    */

    int numObjs = mGalaxySystem.getNumOfObjs( );

        glLineWidth(3.0);
    //glShadeModel(GL_SMOOTH);

    for ( int i = 0; i < numObjs; ++i ) {
		double y;
		double x;
        double r;
        double flgAlive= mGalaxySystem.getObjInfo(i, x, y, r);
        if ( !flgAlive ) continue;
        int numPoints = mGalaxySystem.getTail_NumSamplePoints(i);
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < numPoints; ++j) {
            COORD_2D c = mGalaxySystem.getTail_SamplePointCoords(i, j);
            float f = j/(float)numPoints;
            //f *= f;
            //f *= 10;
            //glColor3f(0.9*f, 0.4*f, 0.1*f);
            float r = cos(f*3.14/2.0);
            float g = sin(f*2.0*3.14);
            float b = 1 - cos(f*3.14/2.0);
            //glColor3f(1-f*(f+0.5), f, 0);

            float cut = 0.75;
            if (f > cut) {
                r = (f - cut)*(f-cut)*16;
                g = 0.0 + (f - cut)*4;
                b = 0.0 + (f - cut)*4;
            }
                        if (r<0.0) r = 0.0; else if (r>1.0) r = 1.0;
            if (g<0.0) g = 0.0; else if (g>1.0) g = 1.0;
            if (b<0.0) b = 0.0; else if (b>1.0) b = 1.0;
            glColor3f(r, g, b);
            glVertex3f(c.x, 0.0, c.y);
        }
        glEnd( );

    }

    //
    glColor3f(0.3, 0.3, 0.8 );
    
    double maxR = mGalaxySystem.getMaxRadius( );
	for ( int i = 0; i < numObjs; ++i ) {
		double y;
		double x;
        double r;
        double flgAlive= mGalaxySystem.getObjInfo(i, x, y, r);
        if ( !flgAlive ) continue;
        if ( r < maxR*0.5 ) {
            glColor3f(0.3, 0.3, 0.8*(r+maxR*0.5)/maxR );
        } else {
            glColor3f(0.8*r/maxR, 0.3, 0.3 );
        }
        drawDisk(x, y, r);
    }
}

void MY_SYSTEM_APP::draw_SimplePainter( ) const
{
    //mSimpleIntegration
    //int numPoints = mSimpleIntegration.getNumPoints( );
    
    int NX, NY;
    mSimplePainter.getCanvasDimension( NX, NY );
    int gridSize = 1.0;
    glBegin(GL_QUADS);
    for ( int j = 0; j < NY-1; ++j ) {
        int y0, y1;
        y0 = j;
        y1 = j + 1;
        for ( int i = 0; i < NX-1; ++i ) {
            int x0, x1;
            
            x0 = i;
            x1 = x0 + 1;
            double r, g, b;
            vector3 color00, color01, color10, color11;
            mSimplePainter.getColorAtPixel( x0, y0, color00 );
            mSimplePainter.getColorAtPixel( x1, y0, color10 );
            mSimplePainter.getColorAtPixel( x0, y1, color01 );
            mSimplePainter.getColorAtPixel( x1, y1, color11 );

            glColor3fv(color00.e);
            glVertex3f( x0, 0.0, y0 );

            glColor3fv(color10.e);
            glVertex3f( x1, 0.0, y0 );

            glColor3fv(color11.e);
            glVertex3f( x1, 0.0, y1 );

            glColor3fv(color01.e);
            glVertex3f( x0, 0.0, y1 );

        }
    }
    glEnd( );

    float r = mSimplePainter.getBrushSize( );
    glColor3f(1.0, 1.0, 1.0);
    drawCircle( mMouseX_2DSpace, mMouseY_2DSpace, r );
    glColor3f(0.0, 0.0, 0.0);
    drawCircle( mMouseX_2DSpace, mMouseY_2DSpace, r*1.08 );

    /*
    glBegin(GL_POINTS);
    for ( int i = 0; i < numPoints; ++i ) {
        double r, g, b;
        double x, y;
        mSimpleIntegration.getPoint(i, x, y, r, g, b);
        x = x/10.0;
        y = y/10.0;
        glColor3d(r, g, b);
        glVertex3f(x, 0.0, y);

    }
    glEnd();
    */

}

void MY_SYSTEM_APP::draw_SortingVisualization( ) const
{
    //mSortingVisualization
    int numElements = mSortingVisualization.getNumOfElements();
	glBegin( GL_QUADS );
	for ( int i = 0; i < numElements; ++i ) {
		float fraction = i/(float) (numElements);
        float c = 0.15+ 0.85*fraction;
		
		float x0, y, x1;
		x0 = i*1;
		x1 = x0 + 1;
        y = mSortingVisualization.getElement(i);
        glColor3f(0.3, c, c );
		glVertex3f( x0, 0.0, 0.0 );
		glVertex3f( x1, 0.0, 0.0 );
        glColor3f(c, c, 0.3 );
		glVertex3f( x1, 0.0, y );
		glVertex3f( x0, 0.0, y );

	}
	glEnd( );

    if ( numElements <= 1 ) return;

    int cur_index = mSortingVisualization.getCurrentElementIndex( );
    int max_non_handled_element_index = mSortingVisualization.getMaxNonHandledElementIndex( );
    int i = cur_index;
    int y;
    int x0, x1;
    x0 = cur_index;
    x1 = x0+1;

    if ( x1 > max_non_handled_element_index -1 ) return;
    glLineWidth(5.0);
    glColor3f(1.0, 0.8, 0.0);
    glBegin( GL_LINE_LOOP );
    y = mSortingVisualization.getElement(i);
		glVertex3f( x0, 0.0, 0.0 );
		glVertex3f( x1, 0.0, 0.0 );
		glVertex3f( x1, 0.0, y );
		glVertex3f( x0, 0.0, y );
    glEnd( );
    //

        x0 = cur_index+1;
    x1 = x0+1;

    if ( x1 > max_non_handled_element_index ) return;
    glBegin( GL_LINE_LOOP );
    glColor3f(0.8, 0.6, 0.0);
    y = mSortingVisualization.getElement(i+1);
		glVertex3f( x0, 0.0, 0.0 );
		glVertex3f( x1, 0.0, 0.0 );
		glVertex3f( x1, 0.0, y );
		glVertex3f( x0, 0.0, y );
    glEnd( );
    glLineWidth(1.0);

}

void MY_SYSTEM_APP::draw_SimpleFileEditor( ) const
{
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
    
    
}