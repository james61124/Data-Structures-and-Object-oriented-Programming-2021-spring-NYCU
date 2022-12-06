//
// Prof. Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2019/04/09
//
#include "mySystem_SortingVisualization.h"
#include "../headers.h"
#include <string>
#include "../../openGLbasic/opengl_stuff.h"
#include "../../openGLbasic/ogl_basic_tools.h"
#include <iostream>
using namespace std;

void SORTING_VISUALIZATION::draw( ) const
{
int numElements = getNumOfElements();
	glBegin( GL_QUADS );
	for ( int i = 0; i < numElements; ++i ) {
		float fraction = i/(float) (numElements);
		glColor3f(0.3+ 0.5*fraction, 0.3, 0.5+ 0.5*fraction );
		float x0, y, x1;
		x0 = i*1;
		x1 = x0 + 1;
        y = getElement(i);
		glVertex3f( x0, 0.0, 0.0 );
		glVertex3f( x1, 0.0, 0.0 );
		glVertex3f( x1, 0.0, y );
		glVertex3f( x0, 0.0, y );
	}
	glEnd( );

    if ( numElements <= 1 ) return;

    int cur_index = getCurrentElementIndex( );
    int max_non_handled_element_index = getMaxNonHandledElementIndex( );
    int i = cur_index;
    int y;
    int x0, x1;
    x0 = cur_index;
    x1 = x0+1;

    if ( x1 > max_non_handled_element_index ) return;
    glLineWidth(5.0);
    glColor3f(1.0, 0.9, 0.0);
    glBegin( GL_LINE_LOOP );
    y = getElement(i);
		glVertex3f( x0, 0.0, 0.0 );
		glVertex3f( x1, 0.0, 0.0 );
		glVertex3f( x1, 0.0, y );
		glVertex3f( x0, 0.0, y );
    glEnd( );
    //

    x0 = getPreviousElementIndex( );
    if (x0 < 0 ) return;
    
   x1 = x0+1;
//    if ( x1 > max_non_handled_element_index ) return;
    glLineWidth(3.0);
    glBegin( GL_LINE_LOOP );
    glColor3f(0.0, 0.9, 0.0);
    y = getElement(x0);
		glVertex3f( x0, 0.0, 0.0 );
		glVertex3f( x1, 0.0, 0.0 );
		glVertex3f( x1, 0.0, y );
		glVertex3f( x0, 0.0, y );
    glEnd( );
    glLineWidth(1.0);

}