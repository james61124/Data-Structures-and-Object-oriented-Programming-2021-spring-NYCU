//
// Prof. Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2019/04/09
//
#include "mySystem_MonteCarlo.h"
#include "../headers.h"
#include <string>
#include "../../openGLbasic/opengl_stuff.h"
#include "../../openGLbasic/ogl_basic_tools.h"
#include <iostream>
using namespace std;

#define GRID_CELL_X 5
#define GRID_CELL_Z 5
#define GRID_CELL_OFFSET    0.5

namespace ns_SystemParameter {
    int cnPointSize = 5;
    int cnLineWidth = 5;
};

namespace {
COLOR_TABLE _colorTable;

void initColorTable()
{
    static bool flg = false;
    if (flg) return;
    flg = true;
    _colorTable.addEntry(0.0, vector3(1.0, 0.0, 0.0));
    _colorTable.addEntry(0.0, vector3(1.0, 0.5, 0.0));
    _colorTable.addEntry(0.0, vector3(1.0, 1.0, 0.0));
    _colorTable.addEntry(0.0, vector3(0.0, 1.0, 0.0));
    _colorTable.addEntry(0.0, vector3(0.0, 1.0, 1.0));
    _colorTable.addEntry(0.0, vector3(0.0, 0.0, 1.0));
    _colorTable.addEntry(0.0, vector3(1.0, 0.0, 1.0));

}
}
/*

//_colorTable.updateMaxValue(mMaxNodeDepth);
_colorTable.resetMaxValue(mMaxNodeDepth);
_colorTable.autoScale( );
*/

void MONTE_CARLO_SYSTEM::setupColorTable() const {
    int numSamples = getNumSamples();

    _colorTable.enableAutoScale(true);


    for ( int i = 0; i < numSamples; ++i ) {
        double x, y;
        //getSample( i, x, y );
        if (i==0) {

            _colorTable.resetMinValue(i);
            _colorTable.resetMaxValue(i);

        }
        //_colorTable.updateMinValue(i);
        _colorTable.updateMaxValue(i);
    }
    _colorTable.autoScale( );
}

void MONTE_CARLO_SYSTEM::draw( ) const
{
    static bool flg_colorTable = false;
    if (!flg_colorTable) initColorTable();

    setupColorTable();

    double minX, maxX;
    getRangeOfX( minX, maxX );



    glPointSize( ns_SystemParameter::cnPointSize );
    int numSamples = getNumSamples();

    vector3 pcolor;
    glBegin( GL_POINTS );
    for ( int i = 0; i < numSamples; ++i ) {
        double x, y;
        getSample( i, x, y );
        bool flgInside = isInsideArea_FuncPair( x, y );



        if ( flgInside ) {
            pcolor = _colorTable.getColor_Linear(i);
        } else {
            pcolor = 0.8*(vector3(1,1,1)-_colorTable.getColor_Linear(i));

        }
        

        glColor3f( pcolor.x, pcolor.y, pcolor.z);

        glVertex3f( x, 0.0, y );
    }
    glEnd( );
    glPointSize( 1.0 );

    glLineWidth(ns_SystemParameter::cnLineWidth);

    int numSegments = 100;
    double f = 1.0/(double)(numSegments);
    glColor3f(0.0, 0.0, 0.0);
    glBegin( GL_LINE_STRIP );
    for ( int i = 0; i < numSegments+1; ++i ) {
        double r0 = i*f;
        double x0 = minX + r0*(maxX - minX);
        double y0 = getValue( x0,0 );

        glVertex3f( x0, -1.0, y0 );
    }
    glEnd( );

    glBegin( GL_LINE_STRIP );
    for ( int i = 0; i < numSegments+1; ++i ) {
        double r0 = i*f;
        double x0 = minX + r0*(maxX - minX);
        double y0 = getValue( x0,1 );

        glVertex3f( x0, -1.0, y0 );
    }
    glEnd( );
    ///
    glLineWidth(ns_SystemParameter::cnLineWidth/2);
    {
    int numSegments = 100;
    double f = 1.0/(double)(numSegments);
    glColor3f(1.0, 1.0, 0.0);
    glBegin( GL_LINE_STRIP );
    for ( int i = 0; i < numSegments+1; ++i ) {
        double r0 = i*f;
        double x0 = minX + r0*(maxX - minX);
        double y0 = getValue( x0,0 );

        glVertex3f( x0, -1.0, y0 );
    }
    glEnd( );

    glColor3f(0.0, 1.0, 1.0);
    glBegin( GL_LINE_STRIP );
    for ( int i = 0; i < numSegments+1; ++i ) {
        double r0 = i*f;
        double x0 = minX + r0*(maxX - minX);
        double y0 = getValue( x0,1 );

        glVertex3f( x0, -1.0, y0 );
    }
    glEnd( );
    }
}