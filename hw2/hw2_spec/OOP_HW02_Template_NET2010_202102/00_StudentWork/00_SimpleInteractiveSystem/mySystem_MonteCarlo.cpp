//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/03/29
//
#include "mySystem_MonteCarlo.h"
#include "myBasicTools.h"
#include <iostream>

using namespace std;

#define MAX_SAMPLES 1000000

MONTE_CARLO_SYSTEM::MONTE_CARLO_SYSTEM( )
{
    //BEGIN DO NOT CHANGE ANYTHING HERE
    mFunctionType = FUNCTION_EXPONENTIAL_CONSINE;
    cout.precision(8);
    //
    mMinX = 0.0;
    mMaxX = 6;
    mMinY = -4.0;
    mMaxY = 4.0;
    mMinNumSamples = 100;
    mMaxNumSamples = MAX_SAMPLES;
    mNumSamples = 5000;
    computeSamples( );
    computeArea( );
    //END DO NOT CHANGE ANYTHING HERE
}

/*
Show the message to the user.
*/
void MONTE_CARLO_SYSTEM::askForInput( )
{
    cout << "MONTE_CARLO_SYSTEM::askForInput( )" << endl;
}

/*
Handle the key events.
*/
bool MONTE_CARLO_SYSTEM::handleKeyPressedEvent( int key )
{
    bool flgHandled = false;
    //
    return flgHandled;
}

/*
Reset the system state.
Steps:
compute the samples
compute the area
*/
void MONTE_CARLO_SYSTEM::reset( )
{
    srand(0);
    computeSamples( );
    computeArea( );
}

/*
Return the range [mMinX, mMaxX] of x to [minX, maxX].

    minX = mMinX;
    maxX = mMaxX;

*/
void MONTE_CARLO_SYSTEM::getRangeOfX( double &minX, double &maxX ) const
{
    minX = 0.0;
    maxX = 10.0;
}

/*
Uniformly generate all the random sample points
inside [mMinX, mMaxX] x [mMinY, mMaxY].

The number of sample points is mNumSamples.
*/
void MONTE_CARLO_SYSTEM::computeSamples( )
{

}

/*
Compute the area based on the Monte Carlo Simulation.
Steps:
1. compute the number of samples inside the area
2. compute the ratio which is equal to

number of samples inside the area 
divided 
by total number of samples

3. Based on the ratio, compute the area

Return the area value
*/
double MONTE_CARLO_SYSTEM::computeArea( ) const
{
    double area = 1.0;
    cout << "Area:" << area << endl;
    return area;

}

/*
Return the number of sample points.
Return mNumSamples.
*/
int MONTE_CARLO_SYSTEM::getNumSamples( ) const
{
    //Return the number of sample points
    return 1;
}

/*
 x = mX[ sampleIndex ];
 y = mY[ sampleIndex ];
*/
void MONTE_CARLO_SYSTEM::getSample(int sampleIndex, double &x, double &y ) const
{
   

}

/*
Based on the function type mFunctionType,
compute the function value for a given value x.
Return the function value.
*/
double MONTE_CARLO_SYSTEM::getValue(double x) const
{
    double y;
    y = rand( )/(float)RAND_MAX;

    switch( mFunctionType ) {
    case FUNCTION_EXPONENTIAL_CONSINE:
        break;
    case FUNCTION_COSINE:
        break;
    case FUNCTION_SINE_COSINE:
        break;
    case FUNCTION_EXPONENTIAL:
        break;
    }
    return y;
}

/*
Given a point (x,y).
Check if the point lies inside the area.
Return true if it lies inside the area.
Return false otherwise.

The area is defined as the region bounded by
the x-axis and the curve of the function f(x).

Assume that (x,y) lies inside area, then
one of the following conditions must be satisfied.

- If f(x) >= 0 and y >=0, then y <= f(x).
- If f(x) <= 0 and y <=0, then y >= f(x).

Otherwise, (x,y) does not lay inside the area.
*/
bool MONTE_CARLO_SYSTEM::isInsideArea( double x, double y ) const
{
    double realY = getValue( x );
 
    return false;
}