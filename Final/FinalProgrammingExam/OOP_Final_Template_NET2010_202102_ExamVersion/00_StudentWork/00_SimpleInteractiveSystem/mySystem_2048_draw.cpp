//
// Prof. Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2019/04/09
//
#include "mySystem_2048.h"
#include "../headers.h"
#include <string>
#include "../../openGLbasic/opengl_stuff.h"
#include <iostream>
using namespace std;

#define GRID_CELL_X 5
#define GRID_CELL_Z 5
#define GRID_CELL_OFFSET    0.5

void drawArrow( )
{
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f( 0.0, 0.0, -0.5);
    glVertex3f( 1.0, 0.0, -0.5); 
    glVertex3f( 1.0, 0.0, -1.0); 
    glVertex3f( 1.5, 0.0, -0.0); 
    glVertex3f( 1.0, 0.0, 1.0); 
    glVertex3f( 1.0, 0.0, 0.5);
    glVertex3f( 0.0, 0.0, 0.5);
    glEnd( );
    glLineWidth(1.0);

}

void MY_2048::draw_Board( ) const
{
    if ( mFlgFocus ) { 
        glColor3f( 0.0, 0.0, 0.0 );
    } else {
        glColor3f( 0.5, 0.5, 0.5 );
    }
    vector3 p0, p1, p2, p3;

    p0 = vector3(0.0, 0.0, 0.0);
    p0.x += mPositionX;
    p0.z += mPositionZ;

    p1 = p0;
    p1.x += mNX*GRID_CELL_X;
    p2 = p1;
    p2.z += mNZ*GRID_CELL_Z;
    p3 = p2;
    p3.x = p0.x;
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex3f(p0.x, p0.y, p0.z);
    glVertex3f(p1.x, p1.y, p1.z);
    glVertex3f(p2.x, p2.y, p2.z);
    glVertex3f(p3.x, p3.y, p3.z);

    glEnd( );
    glLineWidth(1);
}

vector3 getColor( int v ) {
    vector3 color;
    color = vector3( 0.8, 0.8, 0.8);

    switch( v ) {
    case 2:
        color = vector3( 1.0, 0.5, 0.5 );
        break;
case 4:
        color = vector3( 1.0, 0.75, 0.0 );
        break;
case 8:
        color = vector3( 1.0, 1.0, 0.0 );
        break;
case 16:
        color = vector3( 0.75, 1.0, 0.0 );
        break;
case 32:
        color = vector3( 0.5, 1.0, 0.0 );
        break;
case 64:
        color = vector3( 0.25, 1.0, 0.25 );
        break;
case 128:
        color = vector3( 0.0, 1.0, 0.5 );
        break;
case 256:
        color = vector3( 0.15, 0.75, 0.15 );
        break;
case 512:
        color = vector3( 0.25, 0.25, 1.0 );
        break;
case 1024:
        color = vector3( 1.0, 0.0, 1.0 );
        break;
case 2048:
        color = vector3( 0.75, 0.0, 0.75 );
        break;
    }
    return color;
}

/*
vector3 getColor( int v ) {
    vector3 color;
    color = vector3( 0.8, 0.8, 0.8);

    switch( v ) {
    case 2:
        color = vector3( 0.0, 1.0, 0.0 );
        break;
case 4:
        color = vector3( 0.0, 0.5, 0.0 );
        break;
case 8:
        color = vector3( 0.5, 0.5, 0.0 );
        break;
case 16:
        color = vector3( 0.5, 1.0, 0.0 );
        break;
case 32:
        color = vector3( 1.0, 1.0, 0.0 );
        break;
case 64:
        color = vector3( 1.0, 0.5, 0.0 );
        break;
case 128:
        color = vector3( 1.0, 0.0, 0.0 );
        break;
case 256:
        color = vector3( 1.0, 0.0, 0.5 );
        break;
case 512:
        color = vector3( 1.0, 0.0, 1.0 );
        break;
case 1024:
        color = vector3( 0.5, 0.0, 1.0 );
        break;
case 2048:
        color = vector3( 0.0, 0.0, 1.0 );
        break;
    }
    return color;
}
*/

string getNumberString( int v ) {
    string str;
    //color = vector3( 0.8, 0.8, 0.8);

    switch( v ) {
    case 2:
       str = "2";
        break;
case 4:
               str = "4";

        break;
case 8:
        str = "8";
        break;
case 16:
        str = "16";
        break;
case 32:
        str = "32";
        break;
case 64:
        str = "64";
        break;
case 128:
        str = "128";
        break;
case 256:
        str = "256";
        break;
case 512:
        str = "512";
        break;
case 1024:
        str = "1024";
        break;
case 2048:
        str = "2048";
        break;
    }
    return str;
}

void MY_2048::draw_GridCell( int ix, int iz ) const
{
    int v = mBoard[iz][ix];
    vector3 color = getColor( v );
    string str = getNumberString( v );
    //
    vector3 p0, p1, p2, p3;

    p0 = vector3(ix*GRID_CELL_X + GRID_CELL_OFFSET, 0.0, iz*GRID_CELL_Z + GRID_CELL_OFFSET);
    p0.x += mPositionX;
    p0.z += mPositionZ;

    p1 = p0;
    p1.x += GRID_CELL_X - GRID_CELL_OFFSET*2;
    p2 = p1;
    p2.z += GRID_CELL_Z - GRID_CELL_OFFSET*2;
    p3 = p2;
    p3.x = p0.x;

    glColor3f( color.r, color.g, color.b );
    glBegin(GL_QUADS);
    glVertex3f(p0.x, p0.y, p0.z);
    glVertex3f(p1.x, p1.y, p1.z);
    glVertex3f(p2.x, p2.y, p2.z);
    glVertex3f(p3.x, p3.y, p3.z);
    glEnd( );

    //
    if ( v != 0 ) {
    glColor3f( 0.0, 0.0, 0.0 );
    glRasterPos3i( p0.x + 1, p0.y-1, p0.z +1 );
    
    //glutBitmapString( GLUT_BITMAP_9_BY_15, (const unsigned char *)str.data( ) );
    //
    glutBitmapString( GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char *)str.data( ) );
    }
    }


void MY_2048::draw_GridCells(  ) const
{
    for ( int j = 0; j < mNZ; ++j ) {
        for ( int i = 0; i < mNX; ++i ) {
         draw_GridCell( i, j );
        }
     }
}

void MY_2048::draw_Event( ) const
 {
     if ( mEvent == 0 ) return;
     if ( mFlgFocus == false ) return;

     glPushMatrix( );
     glTranslatef( mPositionX - 3, 0.0, 0.0 );
     switch( mEvent ) {
     case GLUT_KEY_UP:
         glRotatef(-90, 0.0, 1.0, 0.0);
         break;
       case GLUT_KEY_DOWN:
         glRotatef(90, 0.0, 1.0, 0.0);

         break;
         case GLUT_KEY_LEFT:
             glRotatef(180, 0.0, 1.0, 0.0);
         break;
         case GLUT_KEY_RIGHT:
         

         break;
     }
     drawArrow( );
     glPopMatrix( );
 }



void MY_2048::draw( ) const
{
    draw_Board( );
    draw_GridCells( );

    draw_Event( );
}
