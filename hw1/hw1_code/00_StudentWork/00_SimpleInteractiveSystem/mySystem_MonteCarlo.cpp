//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/03/01
//
#include "mySystem_MonteCarlo.h"
#include <iostream>
#include <math.h>

using namespace std;

#define MAX_NUM_SAMPLES 1000000
#define MIN_NUM_SAMPLES 2
#define DFT_NUM_SAMPLES 10000

MONTE_CARLO_SYSTEM::MONTE_CARLO_SYSTEM( )
{
	cout.precision(8);
    mRadius = 5.0f;
	mNumSamples = DFT_NUM_SAMPLES;
	reset();
}

void MONTE_CARLO_SYSTEM::reset()
{
    generateUniformSamples( );
    computePI();
}

//increase the radius of the circle
void MONTE_CARLO_SYSTEM::increaseRadius( )
{
    mRadius += 1;
   
    generateUniformSamples( );
    computePI();
}

//decrease the number of sample points
void MONTE_CARLO_SYSTEM::decreaseRadius( )
{
    mRadius -= 1;
    

    generateUniformSamples( );
    computePI();
}

//increase the number of sample points
void MONTE_CARLO_SYSTEM::increase(int increasedAmount)
{
    mNumSamples =mNumSamples+ increasedAmount;
    if ( mNumSamples > MAX_NUM_SAMPLES)
      mNumSamples = MAX_NUM_SAMPLES;
    //generateUniformSamples( );
    //computePI();
}

//decrease the number of sample points
void MONTE_CARLO_SYSTEM::decrease(int decreasedAmount)
{
     mNumSamples = mNumSamples- decreasedAmount;
    if ( mNumSamples < MIN_NUM_SAMPLES)
      mNumSamples = MIN_NUM_SAMPLES;
    //generateUniformSamples( );
    //computePI();
}

//
//Show the system name
//Ask to input the radius of the circle
//Ask to input the number of sample points
//Call computeSamples( ) to compute the sample points and pi
//
void MONTE_CARLO_SYSTEM::askForInput( )
{
	
	cout << "This is a Monte Carlo Simulation." << endl;

    while (true) {
	    cout << "Please input the radius of the circle [1,10]:" << endl;
	    cin >> mRadius;
        if ( mRadius >1 && mRadius <= 10) break;
    }
    //
	while (true) {
	    cout << "Please input the number of the sample:[1,1000000]" << endl;
	    cin >> mNumSamples;
        if ( mNumSamples >=1 && mNumSamples <= 1000000) break;
    }
	//
	//generateUniformSamples( );
	//computePI( );
}

//
// Compute the coordinates of the sample points uniformly.
// There are mNumSamples samples.
//
void MONTE_CARLO_SYSTEM::generateUniformSamples( )
{
	mX.clear( );
	mY.clear( );

	double pi=0;
	for ( int i = 0; i < mNumSamples; ++i ) {
		float x, y;
		double fx = ( rand( )%RAND_MAX )/(double) (RAND_MAX-1);
		double fy = ( rand( )%RAND_MAX )/(double) (RAND_MAX-1);
		
        x = 2*fx*mRadius - mRadius;
		y = 2*fy*mRadius - mRadius;
		mX.push_back( x );
		mY.push_back( y );
		//cout<<mX[i]<<" "<<mY[i]<<endl;
		
			
		
		
	}
	
}

// 
// Compute PI and output it to the console window.
//   
double MONTE_CARLO_SYSTEM::computePI() const
{
    double pi = 0,answer=0;
	for ( int i = 0; i < mNumSamples; ++i ) {
		
		
		
		if(sqrt(mX[i]*mX[i]+mY[i]*mY[i])<=mRadius){
			answer++;
		}

		
		
	}
	pi=4*answer/mNumSamples;
	

	cout << "PI:" << pi << endl;
    return pi;
}


//
//Return the radius of the circle
//
double MONTE_CARLO_SYSTEM::getRadius( ) const
{
	//return mRadius;
    return mRadius;
}

//Return the number of sample points
int MONTE_CARLO_SYSTEM::getNumSamples( ) const
{
	
	return mNumSamples;
}

//
// Input: sampleIndex is the index of the sample. The index starts from 0.
// Return the sample coordinates in (x, y).
// Return the boolean value indicating whether the sample lying inside the circle.
//
bool MONTE_CARLO_SYSTEM::getSample(int sampleIndex, float &x, float &y) const
{
	bool flgInside = false;
	x=this->mX[sampleIndex];
	y=this->mY[sampleIndex];
	if(sqrt(mX[sampleIndex]*mX[sampleIndex]+mY[sampleIndex]*mY[sampleIndex])<=mRadius){
		flgInside=true;	
	}
    //
    //
    //
    return flgInside;
}
// CODE: 2021/03/01. Do not delete this line.