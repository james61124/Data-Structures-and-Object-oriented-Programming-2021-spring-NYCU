//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/03/29
//
/*
This system employs the Monte Carlo Simulation
to perform the calculation.
*/
#ifndef __MY_SYSTEM_MONTE_CARLO_H_
#define __MY_SYSTEM_MONTE_CARLO_H_
#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
#include <vector>
#include "base_class.h"
using std::vector;

#define FUNCTION_EXPONENTIAL_CONSINE    1
#define FUNCTION_COSINE           2
#define FUNCTION_SINE_COSINE    3
#define FUNCTION_EXPONENTIAL    4

class MONTE_CARLO_SYSTEM : public BASE_SYSTEM
{
protected:
    int mMinNumSamples; // the minimum number of samples
    int mMaxNumSamples; // the maximum number of samples

    int mFunctionType;  // the function type
    vector<double> mX;  // x value
    vector<double> mY;  // the function value 

    double mMinX, mMaxX;    // the range along the x-axis
    double mMinY, mMaxY;    // the range along the y-axis

    int mNumSamples;        // the number of samples
    void computeSamples( );

public:
    MONTE_CARLO_SYSTEM( );
    void askForInput( );
    int getNumSamples( ) const;
    void getSample(int sampleIndex, double &x, double &y ) const;
    void getRangeOfX( double &minX, double &maxX ) const;
    double getValue(double x) const;
    bool isInsideArea( double x, double y ) const;
    double computeArea( ) const;
    bool handleKeyPressedEvent( int key );
    void reset( );
    ////////////////////////////////////////////////////
public:
    void update(  bool flg_timer = false ) { }
    void clickAt( int x, int y, const vector3 &color ) { }
};
#endif