//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/03/29
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
       r = g = b = 0.0;
        mCanvas[i] = vector3(r, g, b);
    }
}

/*
Get the canvas dimension.
nx : number of columns
ny : number of rows

nx = mNX;
ny = mNY;
*/
void SIMPLE_PAINTER::getCanvasDimension( int &nx, int &ny ) const
{
 nx = 25;
 ny = 25;
}

//Return x + y*nx
int SIMPLE_PAINTER::computeCanvasIndex( int x, int y, int nx, int ny )
{
    return 10;
}

/*
Get the color at pixel (x,y).
Store it to color.
*/
void SIMPLE_PAINTER::getColorAtPixel( int x, int y, vector3 &color ) const
{
    color = vector3( 0.0, 1.0, 0.0 );
}

/*
Show system title.
Show key usage.
*/
void SIMPLE_PAINTER::askForInput( )
{
    cout << "SIMPLE_PAINTER::askForInput( )" << endl;

}

/*
Return true if the key event is handled.
Return false otherwise.

Make sure that the brush size is not larger than mMaxBrushSize.
*/
bool SIMPLE_PAINTER::handleKeyPressedEvent( int key )
{
    bool flgHandled = false;

    return flgHandled;
}

/*
Return the brush size:
Return mBrushSize
*/
int SIMPLE_PAINTER::getBrushSize( ) const
{
    return 12;
}

/*
Set color:
mColor = color
*/
void SIMPLE_PAINTER::setColor( const vector3 &color )
{
    mColor = vector3(1.0, 0.0, 0.0);
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

}

/*
Draw one pxiel at (x,y) with color and weight w.
If (x,y) is not inside the canvas return.

Make sure that the color component is inside [0,1].

new color = current_color*(1.0-w*w) + w*w*color;
*/
void SIMPLE_PAINTER::drawAt(int x, int y, const vector3 &color, double w )
{

}
