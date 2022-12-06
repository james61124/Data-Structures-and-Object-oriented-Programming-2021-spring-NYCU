//
// Prof. Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/04/
//
#include "mySystem_GraphSystem.h"
#include "../headers.h"
#include <string>
#include "../../openGLbasic/opengl_stuff.h"
#include <iostream>
using namespace std;

void GRAPH_SYSTEM::drawEdges_Indirect( ) const
{
    int numEdges = getNumOfEdges( );

    glColor3f(0.0, 0.8, 0.0);
    glLineWidth(3.0);
    glBegin(GL_LINES);
    for ( int i = 0; i < numEdges; ++i ){
        vector3 p0 = getNodePositionOfEdge( i, 0 );
        vector3 p1 = getNodePositionOfEdge( i, 1 );
        glVertex3f( p0.x, p0.y, p0.z );
        glVertex3f( p1.x, p1.y, p1.z );
    }
    glEnd();
    glLineWidth(1.0);
}

void GRAPH_SYSTEM::drawNodes_Indirect( ) const
{
    int numEdges = getNumOfNodes( );
    glColor3f(0.5, 0.5, 0.5);
    glLineWidth(2.0);
    for ( int i = 0; i < numEdges; ++i ) {
        double r;
        vector3 p;
        getNodeInfo( i, r, p );

        ogl_drawSimpleSolidCircleXZ(p.x, p.y, p.z, r, 12);
    }
    glLineWidth(1.0);
}

void GRAPH_SYSTEM::drawSelectedNode_Indirect( ) const
{
    if ( mPassiveSelectedNode ) {
        glColor3f(0.0, 0.5, 1.0);

        vector3 p = mPassiveSelectedNode->p;
        double r = mPassiveSelectedNode->r;
        ogl_drawSimpleSolidCircleXZ(
            p.x, 
            p.y -1.0, 
            p.z, 
            r, 
            12);

    }
    if ( isSelectedNode( ) == false ) return;
    glColor3f(1.0, 0.0, 0.0);

    vector3 p;
    double r;
    getInfoOfSelectedPoint( r, p );
    ogl_drawSimpleSolidCircleXZ(
        p.x, 
        p.y -1.0, 
        p.z, 
        r, 
        12);
}

void GRAPH_SYSTEM::draw( ) const
{
    drawEdges_Indirect( );
    drawNodes_Indirect( );
    drawSelectedNode_Indirect( );
}
