//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/06/17
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

#define FUNCTION_EXPONENTIAL_SINE    1
#define FUNCTION_SINE           2
#define FUNCTION_SINE_COSINE    3
#define FUNCTION_EXPONENTIAL    4

enum SamplingRegion {
   SR_Double_Squares=0,
   SR_Double_Circles,
   SR_Double_Diamonds,
   SR_End                   // dummy
};

class MONTE_CARLO_SYSTEM : public BASE_SYSTEM
{
protected:
    int mMinNumSamples; // the minimum number of samples
    int mMaxNumSamples; // the maximum number of samples

    int mFunctionType;  // the function type
    vector<double> mX;  // x value
    vector<double> mY;  // the function value 

    vector<int> mPointIndices;
    double mMinX, mMaxX;    // the range along the x-axis
    double mMinY, mMaxY;    // the range along the y-axis

    int mNumSamples;        // the number of samples
    //
    SamplingRegion mSR_Option;
    int mSR_Index;
    //
    void computeSamples( );
    void sortAboutCenter();
    bool isInsideSamplingRegion( double x, double y ) const;
public:
    MONTE_CARLO_SYSTEM( );
    void draw( ) const;
    void askForInput( );
    double getRadius( ) const;
    int getNumSamples( ) const;
    void getSample(int sampleIndex, double &x, double &y ) const;
    void getRangeOfX( double &minX, double &maxX ) const;
    double getValue(double x, int func_index) const;

    bool isInsideArea( double x, double y ) const;
    bool isInsideArea_FuncPair( double x, double y ) const;
    double computeArea( ) const;
    bool handleKeyPressedEvent( unsigned char key );
    void reset( );

    void setupColorTable() const;
    
    ////////////////////////////////////////////////////
public:
    void update(  bool flg_timer = false ) { }
    void clickAt( int x, int y, const vector3 &color ) { }
};
#endif