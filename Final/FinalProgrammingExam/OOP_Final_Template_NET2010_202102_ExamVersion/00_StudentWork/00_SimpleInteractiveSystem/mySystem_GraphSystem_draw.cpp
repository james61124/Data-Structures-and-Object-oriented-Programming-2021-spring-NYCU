//
// Prof. Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2019/04/09
//
#include "mySystem_GraphSystem.h"
#include "../headers.h"
#include <string>
#include "../../openGLbasic/opengl_stuff.h"
#include "../../openGLbasic/ogl_basic_tools.h"
#include <iostream>
using namespace std;

namespace {
static COLOR_TABLE _colorTable;

static void initColorTable()
{
    static bool flg = false;
    if (flg) return;
    flg = true;
    _colorTable.addEntry(0.0, vector3(1.0, 0.0, 0.0));
    _colorTable.addEntry(1.0, vector3(1.0, 0.5, 0.0));
    _colorTable.addEntry(2.0, vector3(1.0, 1.0, 0.0));
    _colorTable.addEntry(3.0, vector3(0.0, 1.0, 0.0));
    _colorTable.addEntry(4.0, vector3(0.0, 1.0, 1.0));
    _colorTable.addEntry(5.0, vector3(0.0, 0.0, 1.0));
    _colorTable.addEntry(6.0, vector3(1.0, 0.0, 1.0));

}
};

void GRAPH_SYSTEM::drawEdges( ) const
{
    glColor3f(0.0, 0.0, 1.0);
    glLineWidth(3.0);
    glBegin(GL_LINES);
    for ( int i = 0; i < mCurNumOfActiveEdges; ++i ) {
        int id = mActiveEdgeArr[ i ];
        const GRAPH_EDGE *edge = &mEdgeArr_Pool[id];
        int n_0 = edge->nodeID[ 0 ];
        int n_1 = edge->nodeID[ 1 ];

        const vector3 &p0 = mNodeArr_Pool[n_0].p;
        const vector3 &p1 = mNodeArr_Pool[n_1].p;
        glVertex3f( p0.x, p0.y, p0.z );
        glVertex3f( p1.x, p1.y, p1.z );

    }
    glEnd();
    glLineWidth(1.0);
}


void GRAPH_SYSTEM::drawNodes( ) const
{
    glColor3f(1.0, 0.75, 0.0);
    glLineWidth(2.0);
    for ( int i = 0; i < mCurNumOfActiveNodes; ++i ) {
        int id = mActiveNodeArr[ i ];

        const GRAPH_NODE *node = &mNodeArr_Pool[id];
        const vector3 &p = node->p;
        double r = node->r;
        ogl_drawSimpleSolidCircleXZ(p.x, p.y, p.z, r, 12);
    }
    glLineWidth(1.0);
}

void GRAPH_SYSTEM::drawSelectedNode( ) const
{
    if ( mPassiveSelectedNode ) {
        

        vector3 p = mPassiveSelectedNode->p;
        double r = mPassiveSelectedNode->r;

        
        glColor3f(0.0, 0.5, 1.0);
        ogl_drawSimpleSolidCircleXZ(
            p.x, 
            p.y -1.0, 
            p.z, 
            r, 
            12);
        //
        glLineWidth(3);
        glColor3f(0.2, 0.2, 0.2);
        ogl_drawSimpleCircleXZ(
            p.x, 
            p.y -0.5, 
            p.z, 
            r, 
            12
            );
        glLineWidth(1);

    }

    if ( mSelectedNode == 0 ) return;
    glColor3f(1.0, 0.0, 0.0);

    ogl_drawSimpleSolidCircleXZ(
        mSelectedNode->p.x, 
        mSelectedNode->p.y -1.0, 
        mSelectedNode->p.z, 
        mSelectedNode->r, 
        12);
}

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
    int num = getNumOfNodes( );
    glColor3f(0.5, 0.5, 0.5);
    glLineWidth(2.0);
    for ( int i = 0; i < num; ++i ) {
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
        

        vector3 p = mPassiveSelectedNode->p;
        double r = mPassiveSelectedNode->r;

        glColor3f(0.0, 0.5, 1.0);
        ogl_drawSimpleSolidCircleXZ(
            p.x, 
            p.y -1.0, 
            p.z, 
            r, 
            12);
        //
         glLineWidth(3);
        glColor3f(0.2, 0.2, 0.2);
        ogl_drawSimpleCircleXZ(
            p.x, 
            p.y -1.0, 
            p.z, 
            r, 
            12
            );
        glLineWidth(1);

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

void GRAPH_SYSTEM::draw_AttachedEdgesOfSelectedNode( ) const
{
    int num = getNumOfAttachedEdgesOfSelectedNode( );

    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(5.0);
    glBegin(GL_LINES);

    for (int i =0; i < num;++i) {
        vector3 p0,p1;
        double r0,r1;
        getNodeInfoOfAttachedEdgeOfSelectedNode(
            i, 0, r0, p0
            );
        getNodeInfoOfAttachedEdgeOfSelectedNode(
            i, 1, r1, p1
            );
        glVertex3f( p0.x, p0.y, p0.z );
        glVertex3f( p1.x, p1.y, p1.z );
    }
     glEnd();
    glLineWidth(1.0);

}

void GRAPH_SYSTEM::draw_AdjacentNodesOfSelectedNode( ) const
{
    int num = getNumOfAdjacentNodesOfSelectedNode( );
    glColor3f(0.2, 0.9, 0.2);
    for (int i =0; i < num;++i) {
        

        vector3 p;
        double r;
        getNodeInfoOfAdjacentNodeOfSelectedNode(
            i, r, p
            );
        ogl_drawSimpleSolidCircleXZ(
            p.x, 
            p.y -1.0, 
            p.z, 
            r, 
            12);
    }

}

void GRAPH_SYSTEM::drawResult_BFS( ) const
{
    initColorTable();
    if ( mResult_BFS_max_depth < 0) return;
    _colorTable.resetMinValue( 0 );
    int maxv = mResult_BFS_max_depth;
   // maxv--;
    if (maxv<0) maxv = 0;
    _colorTable.resetMaxValue(  maxv );
    _colorTable.autoScale( );
    //
    int num = getNumOfNodes( );
    glLineWidth(2.0);
    for ( int i = 0; i < num; ++i ) {
        double r;
        vector3 p;
        getNodeInfo( i, r, p );
        int nodeID = mActiveNodeArr[ i ];
        GRAPH_NODE *n = &mNodeArr_Pool[ nodeID ];
        vector3 c = _colorTable.getColor_Linear(n->depth);
        glColor3f(c.x, c.y, c.z);

        //cout << "n->depth:" << n->depth << endl;

        ogl_drawSimpleSolidCircleXZ(p.x, p.y, p.z, r, 12);
    }
    glLineWidth(1.0);
}

void GRAPH_SYSTEM::draw( ) const
{
    drawEdges_Indirect( );
    drawNodes_Indirect( );
    switch( mOption ) {
    case GR_Neighbor:
    draw_AttachedEdgesOfSelectedNode( );
    draw_AdjacentNodesOfSelectedNode( );
    break;
    case GR_BFS:
    drawResult_BFS( );
    break;
    }
    drawSelectedNode_Indirect( );
    //

}
