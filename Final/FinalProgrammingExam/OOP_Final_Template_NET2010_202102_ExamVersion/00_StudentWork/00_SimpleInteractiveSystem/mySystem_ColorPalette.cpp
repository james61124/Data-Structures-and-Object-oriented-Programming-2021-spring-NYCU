#include <iostream>
#include "mySystem_ColorPalette.h"

using namespace std;

COLOR_PALETTE::COLOR_PALETTE( )
{
    mPosition = vector3(260.0, -1.0, 200.0);
    mDX = 30;
    mDZ = 30;
    mColor = vector3(1.0, 0.0, 0.0);
    mColorSelectorPosition = vector3(0.0, -1.0, 0.0);
    //
    mTransparencyBoardPosition = vector3(260.0, -1.0, 160.0);
    mTransparency = vector3(1.0, 1.0, 1.0);
    mTransparencySelectorPosition = vector3(0.0, -1.0, 0.0);
}

vector3 COLOR_PALETTE::getColor( ) const
{
    return mColor;
}

//
// (mx, mz) : viewport space in pixels
// (x,z) 2D space
//
bool COLOR_PALETTE::clickAtColorPalette( float x, float y, int mx, int mz )
{
        if ( x <= mPosition.x ) return false;
    if ( x >= mPosition.x + mDX*3 ) return false;
    if ( y <= mPosition.z ) return false;
    if ( y >= mPosition.z +mDZ ) return false;
   // glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glReadBuffer(GL_FRONT);
    //
    //drawColorBoard( false );
    //
    glReadPixels(mx, mz, 1, 1, GL_RGBA, GL_FLOAT, (void*)mColorBuffer );
    glFlush( );
    //glReadBuffer(GL_FRONT);
    
    mColor.r = mColorBuffer[0];
    mColor.g = mColorBuffer[1];
    mColor.b = mColorBuffer[2];
    //
       vector3 rp = vector3(x, 0.0, y) - mPosition;
    mColorSelectorPosition.x = rp.x;
    mColorSelectorPosition.y = -1.0;
    mColorSelectorPosition.z = rp.z;
    return true;
}

bool COLOR_PALETTE::clickAtTransparencyPalette( float x, float y, int mx, int mz )
{
    vector3 &p = mTransparencyBoardPosition;
        if ( x <= p.x ) return false;
    if ( x >= p.x + mDX*3 ) return false;
    if ( y <= p.z ) return false;
    if ( y >= p.z +mDZ ) return false;
    glReadBuffer(GL_FRONT);
    //glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glReadPixels(mx, mz, 1, 1, GL_RGBA, GL_FLOAT, (void*)mColorBuffer );
   
    glFlush( );
   
    //glReadBuffer(GL_FRONT);
    
    mTransparency.r = 1.0 - mColorBuffer[0];
    mTransparency.g = 1.0 - mColorBuffer[1];
    mTransparency.b = 1.0 - mColorBuffer[2];

    vector3 rp = vector3(x, 0.0, y) - mTransparencyBoardPosition;
    mTransparencySelectorPosition.x = rp.x;
    mTransparencySelectorPosition.y = -1.0;
    mTransparencySelectorPosition.z = rp.z;

   // cout << "mTransparency.r:" << mTransparency.r << endl;
    return true;
}

float COLOR_PALETTE::getTransparency( ) const
{
    return mTransparency.r;
}


bool COLOR_PALETTE::clickAt( float x, float y, int mx, int mz )
{
    //cout << "COLOR_PALETTE::clickAt:" << x << "\t" << y << endl;

    bool flgHandled = false;

    if ( clickAtColorPalette( x, y, mx, mz ) ) return true;
    if ( clickAtTransparencyPalette( x, y, mx, mz ) ) return true;

    //cout << "here:" << mColor.r << "\t" << mColor.g << "\t" << mColor.b << endl;
    return flgHandled;
}

void COLOR_PALETTE::drawColorBoard( bool flgDrawSelector ) const
{
    const vector3 &p = mPosition;
    
    glTranslatef(p.x, p.y, p.z);

    vector3 p4, p5, p6, p7; // positions
    vector3 p0, p1, p2, p3;
    vector3 c4, c5, c6, c7; // colors
    vector3 c0, c1, c2, c3;
    vector3 u = vector3(mDX, 0.0, 0.0);
    vector3 v = vector3(0.0, 0.0, mDZ);

    p0 = vector3( 0.0, 0.0, 0.0);
    p1 = p0 + u;
    p2 = p1 + u;
    p3 = p2 + u;

    p4 = p0 + v;
    p5 = p1 + v;
    p6 = p2 + v;
    p7 = p3 + v;

    c0 = vector3(0.0, 1.0, 0.0);
    c1 = vector3(0.0, 0.0, 0.0);
    c2 = vector3(0.0, 0.0, 1.0);
    c3 = vector3(1.0, 0.0, 0.0);
    c4 = vector3(1.0, 1.0, 0.0);
    c5 = vector3(1.0, 1.0, 1.0);
    c6 = vector3(0.0, 1.0, 0.0);
    c7 = vector3(1.0, 1.0, 1.0);


    glBegin(GL_QUADS);
    glColor3fv(c0.e);
    glVertex3fv(p0.e);
    glColor3fv(c1.e);

    glVertex3fv(p1.e);
    glColor3fv(c5.e);

    glVertex3fv(p5.e);
    glColor3fv(c4.e);

    glVertex3fv(p4.e);
    //
    glColor3fv(c1.e);

    glVertex3fv(p1.e);
    glColor3fv(c2.e);

    glVertex3fv(p2.e);
    glColor3fv(c6.e);

    glVertex3fv(p6.e);
    glColor3fv(c5.e);

    glVertex3fv(p5.e);
    //
    glColor3fv(c2.e);

    glVertex3fv(p2.e);
    glColor3fv(c3.e);

    glVertex3fv(p3.e);
    glColor3fv(c7.e);

    glVertex3fv(p7.e);
    glColor3fv(c6.e);

    glVertex3fv(p6.e);
    glEnd( );

    //
    if ( flgDrawSelector ) {
        const vector3 &q = mColorSelectorPosition;
float w = 3.0;
    glLineWidth( 1.0 );
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f( q.x-w, q.y, q.z-w );
    glVertex3f( q.x+w, q.y, q.z-w );
    glVertex3f( q.x+w, q.y, q.z+w );
    glVertex3f( q.x-w, q.y, q.z+w );

    glEnd( );
    //
    w = 2.0;
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
     glVertex3f( q.x-w, q.y, q.z-w );
    glVertex3f( q.x+w, q.y, q.z-w );
    glVertex3f( q.x+w, q.y, q.z+w );
    glVertex3f( q.x-w, q.y, q.z+w );
    glEnd( );
    }
    
}

void COLOR_PALETTE::drawTransparencyBoard( bool flgDrawSelector  ) const
{
    const vector3 &p = mTransparencyBoardPosition;

    glTranslatef(p.x, p.y, p.z);

    vector3 p4, p5, p6, p7; // positions
    vector3 p0, p1, p2, p3;
    vector3 c4, c5, c6, c7; // colors
    vector3 c0, c1, c2, c3;
    vector3 u = vector3(mDX, 0.0, 0.0);
    vector3 v = vector3(0.0, 0.0, mDZ);

    p0 = vector3( 0.0, 0.0, 0.0);
    p1 = p0 + u;
    p2 = p1 + u;
    p3 = p2 + u;

    p4 = p0 + v;
    p5 = p1 + v;
    p6 = p2 + v;
    p7 = p3 + v;

    c0 = vector3(1.0, 1.0, 1.0);
    c1 = vector3(0.0, 0.0, 0.0);
    c2 = vector3(0.0, 0.0, 1.0);
    c3 = vector3(0.0, 0.0, 0.0);
    c4 = vector3(1.0, 1.0, 1.0);
    c5 = vector3(1.0, 1.0, 1.0);
    c6 = vector3(0.0, 1.0, 0.0);
    c7 = vector3(0.0, 0.0, 0.0);


    glBegin(GL_QUADS);
    glColor3fv(c0.e);
    glVertex3fv(p0.e);
    glColor3fv(c3.e);
    glVertex3fv(p3.e);
    glColor3fv(c7.e);
    glVertex3fv(p7.e);
    glColor3fv(c4.e);
    glVertex3fv(p4.e);
    /*
    glColor3fv(c1.e);
    glVertex3fv(p1.e);
    glColor3fv(c5.e);

    glVertex3fv(p5.e);
    glColor3fv(c4.e);

    glVertex3fv(p4.e);
    //
    glColor3fv(c1.e);

    glVertex3fv(p1.e);
    glColor3fv(c2.e);

    glVertex3fv(p2.e);
    glColor3fv(c6.e);

    glVertex3fv(p6.e);
    glColor3fv(c5.e);

    glVertex3fv(p5.e);
    //
    glColor3fv(c2.e);

    glVertex3fv(p2.e);
    glColor3fv(c3.e);

    glVertex3fv(p3.e);
    glColor3fv(c7.e);

    glVertex3fv(p7.e);
    glColor3fv(c6.e);

    glVertex3fv(p6.e);
    */



    glEnd( );

    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
        glColor3f(0.0, 0.0, 0.0);
    glVertex3fv(p0.e);
    glVertex3fv(p3.e);
    glVertex3fv(p7.e);
    glVertex3fv(p4.e);
    glEnd();

    if ( flgDrawSelector ) {
    const vector3 &q = mTransparencySelectorPosition;
float w = 3.0;
    glLineWidth( 1.0 );
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
      glVertex3f( q.x-w, q.y, q.z-w );
    glVertex3f( q.x+w, q.y, q.z-w );
    glVertex3f( q.x+w, q.y, q.z+w );
    glVertex3f( q.x-w, q.y, q.z+w );

    glEnd( );
    //
    w = 2.0;
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
        glVertex3f( q.x-w, q.y, q.z-w );
    glVertex3f( q.x+w, q.y, q.z-w );
    glVertex3f( q.x+w, q.y, q.z+w );
    glVertex3f( q.x-w, q.y, q.z+w );
    glEnd( );
 
    }
    
}

void COLOR_PALETTE::draw( ) const
{
    glPushMatrix( );
    drawColorBoard( );
    glPopMatrix( );

    glPushMatrix( );
    drawTransparencyBoard( );
    glPopMatrix( );

}