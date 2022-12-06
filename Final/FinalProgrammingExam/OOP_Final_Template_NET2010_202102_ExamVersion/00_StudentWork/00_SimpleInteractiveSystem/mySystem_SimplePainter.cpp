//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
//
#include "mySystem_SimplePainter.h"
#include <iostream>
#include "myBasicTools.h"

using namespace std;
namespace {

};

SIMPLE_PAINTER::SIMPLE_PAINTER()
{
    mMaxBrushSize = 21;
    mBrushSize = 3; 

    mNX = 256; // index from 0 to mNX-1 along the x-axis; number of colmns
    mNY = 256; // index from 0 to mNY-1 along the y-axis; number of rows

    mCanvas = new vector3[mNX*mNY]; // a color bitmap
    mColor = vector3(1.0, 0.0, 0.0); // current color
    mTransparency = 0.25;  // current transparency
    reset( );
}

/*
Randomly generate the colors of the bitmap.
*/
void SIMPLE_PAINTER::reset( )
{
    double v0 = 0.75;
    double v1 = 0.9;
    for ( int i = 0; i < mNY*mNX; ++i ) {
        double r, g, b;
        r = getRandDouble(v0, v1);
        g = getRandDouble(v0, v1);
        b = getRandDouble(v0, v1);
        mCanvas[i] = vector3(r, g, b);
    }
}

/*
Get the canvas dimension.
nx : number of columns
ny : number of rows
*/
void SIMPLE_PAINTER::getCanvasDimension( int &nx, int &ny ) const
{
    nx = mNX;
    ny = mNY;

}

inline int computeCanvasIndex( int x, int y, int nx, int ny )
{
    return x + y*nx;
}

/*
Get the color at pixel (x,y).
Store it to color.
*/
void SIMPLE_PAINTER::getColorAtPixel( int x, int y, vector3 &color ) const
{
    int index;
    index = computeCanvasIndex(x, y, mNX, mNY );
    color = mCanvas[ index ];
}

/*
Show system title.
Show key usage.
*/
void SIMPLE_PAINTER::askForInput( )
{
    cout << "SIMPLE_PAINTER::askForInput( )" << endl;
    cout << "Please use keyboard and mouse to control" << endl;
    cout << "1: red color" << endl;
    cout << "2: green color" << endl;
    cout << "3: blue color" << endl;
    cout << ",: decrease brush size" << endl;
    cout << ".: increase brush size" << endl;

}

/*
Return true if the key event is handled.
Return false otherwise.

Make sure that the brush size is not larger than mMaxBrushSize.
*/
bool SIMPLE_PAINTER::handleKeyPressedEvent( int key )
{
    bool flgHandled = false;
    switch( key ) {
    case '.':
        mBrushSize += 2;
        flgHandled = true;
        break;
    case ',':
        mBrushSize -= 2;
        flgHandled = true;
        break;
    case '1':
        mColor = vector3(1.0, 0.0, 0.0);
        flgHandled = true;
        break;
    case '2':
        mColor = vector3(0.0, 1.0, 0.0);
        flgHandled = true;
        break;
    case '3':
        mColor = vector3(0.0, 0.0, 1.0);
        flgHandled = true;
        break;
    }

    if ( mBrushSize > mMaxBrushSize ) mBrushSize = mMaxBrushSize;
    else if ( mBrushSize < 1 ) mBrushSize = 1;

    return flgHandled;
}

/*
Return the brush size:
Return mBrushSize
*/
int SIMPLE_PAINTER::getBrushSize( ) const
{
    return mBrushSize;
}

/*
Set color:
mColor = color
*/
void SIMPLE_PAINTER::setColor( const vector3 &color )
{
    mColor = color;
}

/*
Set transparency:
mTransparency = v
*/
void SIMPLE_PAINTER::setTransparency( float v ) {
    mTransparency = v;
}

/*
Use the brush to draw. The center is at (x,y).
A disk is defined based on position (x,y) and
brush radius.

The radius of  the disk is set to ~2*mBrushSize.
Steps:

For each pixel in the disk centered at (x,y)
   do
     compute color and transparency
     draw at the pixel
*/
void SIMPLE_PAINTER::clickAt(double x, double y)
{
    vector3 color = mColor;

    int ref_s = mBrushSize/2;
    double S2 = ref_s*ref_s;
    int s = ref_s * 4;
    for ( int j = -s; j <= s; ++j ) {
        for ( int i = -s; i <= s; ++i ) {
            double rx = i;
            double ry = j;
            double w = 1.0; // weight
            double R2 = rx*rx + ry*ry;

            if ( R2 > 4.0*S2 ) continue; // this pixel is too far. ignore it
            if ( R2 > S2/2.0 ) {    // pixel is a bit far but not too far
                double k = S2/2.0 - R2;
                double d = 0.003;   // magic number
                w = pow(2.718281828, d*k ); // use the guassian function to compute weight w
            } else {
                w = 1.0; // pixel is near to the center (x,y). Set weight to a high value; here it's one.
            }
            //
            drawAt(x+i, y+j, w*color, w*mTransparency);
        }
    }
}

/*
Draw one pxiel at (x,y) with color and weight w.
If (x,y) is not inside the canvas return.

Make sure that the color component is inside [0,1].

new color = current_color*(1.0-w*w) + w*w*color;
*/
void SIMPLE_PAINTER::drawAt(int x, int y, const vector3 &color, double w )
{
    if ( x < 0 ) return;
    if ( x > mNX ) return;
    if ( y < 0 ) return;
    if ( y > mNY ) return;
    //
    int index = computeCanvasIndex(x, y, mNX, mNY );

    vector3 current_color = mCanvas[index];

    vector3 c = current_color*(1.0-w*w) + w*w*color;
    if ( c.r > 1.0 ) c.r = 1.0;
    if ( c.g > 1.0 ) c.g = 1.0;
    if ( c.b > 1.0 ) c.b = 1.0;

    mCanvas[index] = c;
}
