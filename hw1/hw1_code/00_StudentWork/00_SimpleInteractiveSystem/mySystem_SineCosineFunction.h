//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/03/01
//
#ifndef __MY_SINECOSINE_FUNCTION_H_
#define __MY_SINECOSINE_FUNCTION_H_
#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
#include <vector>
using std::vector;
class SINECOSINE_FUNCTION
{
protected:
	double a, b;
	double x0, x1;
	int mNumSamples;
protected:
public:
	SINECOSINE_FUNCTION( );
    void reset();
    void increaseA(double increasedAmount = 0.05);
    void decreaseA(double decreasedAmount = 0.05);
    void increaseB(double increasedAmount = 0.05);
    void decreaseB(double decreasedAmount = 0.05);
    void increaseSampleNum(int increasedAmount = 5);
    void decreaseSampleNum(int decreasedAmount = 5);
    double getA() const { return a;}
    double getB() const { return b;}

    void askForInput( );
	void getRangeOfX( double &x0, double &x1 ) const;
	int getNumOfSamples( ) const;
	double getValue( double x ) const;

};
#endif
// CODE: 2019/02/25. Do not delete this line.


