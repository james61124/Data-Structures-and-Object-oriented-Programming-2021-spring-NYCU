#include "mySystem_Traffic.h"
#include "../headers.h"
#include <string>
#include "../../openGLbasic/opengl_stuff.h"
#include <iostream>
using namespace std;

void TRAFFIC_SYSTEM::draw_Lane( const LANE *L ) const
{
    vector3 p0, p1;
    p0 = mNodes[L->p0ID]->p;
    p1 = mNodes[L->p1ID]->p;

    glLineWidth( 5.0 );
    
    glBegin(GL_LINES);
    glColor3f( 0.5, 0.5, 0.5 );
    glVertex3f( p0.x, p0.y, p0.z );
    glColor3f( 0.8, 0.8, 0.8 );
    glVertex3f( p1.x, p1.y, p1.z );

    glEnd( );
}

void TRAFFIC_SYSTEM::draw_Lanes(  ) const
{
    for ( int i = 0; i < mLanes.size( ); ++i ) {
        draw_Lane( mLanes[ i ] );
    }
}

void TRAFFIC_SYSTEM::draw_Agent( const AGENT *g ) const
{
    glColor3f( 0.0, 0.0, 1.0 );
        ogl_drawSimpleSolidCircleXZ(g->p.x, g->p.y, g->p.z, g->r, 12);

}


void TRAFFIC_SYSTEM::draw_Agents(  ) const
{
    for ( int i = 0; i < mAgents.size( ); ++i ) {
        draw_Agent( mAgents[ i ] );
    }
}

void TRAFFIC_SYSTEM::draw( ) const
{
    draw_Lanes( );
    draw_Agents( );
}