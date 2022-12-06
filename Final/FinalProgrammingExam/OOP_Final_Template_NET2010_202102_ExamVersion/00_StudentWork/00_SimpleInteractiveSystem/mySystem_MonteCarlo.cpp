//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
//
#include "mySystem_MonteCarlo.h"
#include "myBasicTools.h"
#include <iostream>

using namespace std;

#define MAX_SAMPLES 20000

#define center_X  3.141592654*2
#define center_Y  0.0

MONTE_CARLO_SYSTEM::MONTE_CARLO_SYSTEM( )
{
    //BEGIN DO NOT CHANGE ANYTHING HERE
    mSR_Index = 0;
    mSR_Option = (SamplingRegion) mSR_Index;


    mFunctionType = FUNCTION_EXPONENTIAL_SINE;
    cout.precision(8);
    //
    mMinX = 0.0;
    mMaxX = 3.141592654*4.0;
    mMinY = -3.141592654*2.0;
    mMaxY = 3.141592654*2.0;
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
	cout<<"1, 2, 3, 4: curve pairs"<<endl;
	cout<<"c:sort the sample points about the reference point (L,0)"<<endl;
	cout<<"r:cycle the regions. And use the current region for generating the sample points"<<endl;
	cout<<"s:show student information"<<endl;
}

/*
Handle the key events.
*/
bool MONTE_CARLO_SYSTEM::handleKeyPressedEvent( unsigned char key )
{
    cout << "bool MONTE_CARLO_SYSTEM::handleKeyPressedEvent" << endl;

    bool flgHandled = false;
    switch( key ) {
    case 'm':
        mNumSamples = 1000;
        flgHandled = true;
        break;
    case '/':
        mNumSamples = mMaxNumSamples;
        flgHandled = true;
        break;
    case ',':
        mNumSamples -= 1000;
        flgHandled = true;

        break;
    case '.':
        mNumSamples += 1000;
        flgHandled = true;

        break;
    case '1':
        mFunctionType = FUNCTION_EXPONENTIAL_SINE;
        flgHandled = true;
        break;
    case '2':
        mFunctionType = FUNCTION_SINE;
        flgHandled = true;
        break;
    case '3':
        mFunctionType = FUNCTION_SINE_COSINE;
        flgHandled = true;
        break;
    case '4':
        mFunctionType = FUNCTION_EXPONENTIAL;
        flgHandled = true;
        break;
    case 'c':
        sortAboutCenter();
        break;
    case 'r':
    case 'R':
        mSR_Index = (mSR_Index+1)%((int)SR_End);
        mSR_Option = (SamplingRegion) mSR_Index;
        flgHandled = true;
        break;
    }
    if ( flgHandled ) {
        if ( mNumSamples < mMinNumSamples ) mNumSamples = mMinNumSamples;
        if ( mNumSamples > mMaxNumSamples ) mNumSamples = mMaxNumSamples;

        computeSamples( );
        computeArea( );
    }
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
*/
void MONTE_CARLO_SYSTEM::getRangeOfX( double &minX, double &maxX ) const
{
    minX = mMinX;
    maxX = mMaxX;
}

bool MONTE_CARLO_SYSTEM::isInsideSamplingRegion( double x, double y ) const
{
    bool flg_ok = false;
    double L = 3.14159*2.0;
    double r2;
    double r2_inner;
    switch(mSR_Option) {
    case SR_Double_Circles:

        r2 = (x-center_X)*(x-center_X)+y*y;
        r2_inner = (x-center_X/2)*(x-center_X/2)+y*y;
        //
        // Fill your or modify own stuff
        //

        flg_ok = true;

        break;
    case SR_Double_Diamonds:

        if (x>=center_X) {
            if ((-(L-x + center_X)<=y) && (y <= L-x + center_X) ) {
                //
                // Fill or modify your own stuff
                //
                    flg_ok = true;
            }
        } else {
            //
            // Fill or modify your own stuff
            //
        }

        break;
    case SR_Double_Squares:
        if ( !(x <= L )) {
            //
            // Fill or modify your own stuff
            //
            flg_ok = true;
        }
        break;
    }

    return flg_ok;
}

/*
Uniformly generate all the random sample points
inside [mMinX, mMaxX] x [mMinY, mMaxY].

The number of sample points is mNumSamples.
*/
void MONTE_CARLO_SYSTEM::computeSamples( )
{
    //
    mX.clear( );
    mY.clear( );
    mX.resize( mNumSamples );
    mY.resize( mNumSamples );
    mPointIndices.resize( mNumSamples );



    for ( int i = 0; i < mNumSamples; ++i ) {
        mPointIndices[i] = i;
        double x, y;
        while (true) {
            //x = getRandDouble( mMinX, mMaxX );
            //y = getRandDouble( mMinY, mMaxY  );
            x = getRandDouble(-10, 10);
            y = getRandDouble(-10, 10);
            //
            // Fill or modify your own stuff
            //
            bool flg_ok = false;
            flg_ok = isInsideSamplingRegion( x, y );
            if (!flg_ok) continue;
            mX[ i ] = x;
            mY[ i ] = y;
            break;

        }
    }
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
    int counter = 0;
    for ( int i = 0; i < mNumSamples; ++i ) {
        double x = mX[ i ];
        double y = mY[ i ];
        if ( isInsideArea_FuncPair( x, y ) ) {
            ++counter;
        }
    }
    double len = 2*3.14159;
    double area = 0.0;
    double sr_area = 0.0; // sampling region area;
    if (mNumSamples<=0) return area;
    double ratio = (counter/(double)mNumSamples);

    switch(mSR_Option) {
    case SR_Double_Circles:
        sr_area = 3.14159;
        //
        // Fill or modify your own stuff
        //
        break;
    case SR_Double_Diamonds:
        sr_area = len*2*len;
        //
        // Fill or modify your own stuff
        //
        break;
    case SR_Double_Squares:
        sr_area = (mMaxX - mMinX)*(mMaxY - mMinY);
        //
        // Fill or modify your own stuff
        //
        break;
    }

    area = ratio*sr_area;

    cout << "Area:" << area << endl;
    return area;

}

/*
Return the number of sample points.
*/
int MONTE_CARLO_SYSTEM::getNumSamples( ) const
{
    //Return the number of sample points
    //
    // Fill or modify your own stuff
    //
    return mNumSamples;
}
inline void MONTE_CARLO_SYSTEM::getSample(int sampleIndex, double &x, double &y ) const
{
    int index = mPointIndices[sampleIndex];
    x = mX[ index ];
    y = mY[ index ];

}

/*
Based on the function type mFunctionType,
compute the function value for a given value x.

func_index = 0 or 1
1f
0g
Return the function value.
*/
double MONTE_CARLO_SYSTEM::getValue(double x, int func_index) const
{
    double y;
	double a1,a2,a3,a4,a5;
    switch( mFunctionType ) {
    case FUNCTION_EXPONENTIAL_SINE:
		//f(x) = -5 sin( x ) + 2.5 cos( x ) e-x/4 
	//g(x) =3 cos( 2x ) sin ( x )

        a1 = 2.5*pow(2.718281828, -x/4.0);
        if (func_index==1) {
            y = (-5)*sin(x)+2.5*cos(x)*a1;
        }else if(func_index==0){
			y=3*cos(2*x)*sin(x);
		}
        //
        // Fill or modify your own stuff
        //
        break;
    case FUNCTION_SINE:
		//f(x) = 3 sin (4 sin( |x| ))
	//g(x) = 5 cos (2 cos ( |x| ) ) sin ( |x| )

        if (x<0) x = -x;
        //y = 3*sin(x);
        if (func_index==1) {
            y = 3*sin(4*sin(x));
        }else if(func_index==0){
			y=5*cos(2*cos(x))*sin(x);
		}
        //
        // Fill or modify your own stuff
        //
        break;
    case FUNCTION_SINE_COSINE:
		//f(x) = - 4 cos ( -2x ) e-x*x/8
	//g(x) = 7 sin( -x ) cos ( -x ) e-x*x/16

        //x = -x;
        a2 = pow(2.718281828,-(x*x)/8.);
		a3=pow(2.718281828,-(x*x)/16.);
		//double a4=pow(2.718281828,1/16.);
        if (func_index==1) {
            y = -4*cos(-2*x)*a2;
        }else if(func_index==0){
			y=7*sin(-x)*cos(-x)*a3;
		}
        //
        // Fill or modify your own stuff
        //
        break;
    case FUNCTION_EXPONENTIAL:
		//f(x) = -4 + 3 e-sin(x)
	//g(x) = -5 + 2 e¡Vcos( x ) sin( x/2 )

        a4 = pow(2.718281828, -cos(x)*sin(x/2.));
		a5=pow(2.718281828, -sin(x));
		//double a6=pow(2.718281828, -sin(x/2.));
        if (func_index==1) {
            y = -4+3*a5;
        }else if(func_index==0){
			y=-5+2*a4;
		}
        //
        // Fill or modify your own stuff
        //
        break;
    }
    return y;
}

//
// Return true if the sampline point (x,y)is bounded between two curves
//
// 
bool MONTE_CARLO_SYSTEM::isInsideArea_FuncPair( double x, double y) const
{
    double realY0 = getValue( x, 0 );
    double realY1 = getValue( x, 1 );
    return true;
    if (realY0<=y && y<=realY1) return true;
    //
    // Fill or modify your own stuff
    //
    return false;
}

void MONTE_CARLO_SYSTEM::sortAboutCenter()
{
    int numSamples = getNumSamples();
    //
    // Fill or modify your own stuff
    //
    for ( int i = 0; i < numSamples; ++i ) {
        double x0, y0;
        getSample( i, x0, y0 );
        for ( int j = i+1; j < numSamples; ++j ) {
            double x1, y1;
            getSample( j, x1, y1 );
            double r0 = (x0-center_X)*(x0-center_X) + y0*y0;
            double r1 = (x1-center_X)*(x1-center_X) + y1*y1;
        }
    }
}

