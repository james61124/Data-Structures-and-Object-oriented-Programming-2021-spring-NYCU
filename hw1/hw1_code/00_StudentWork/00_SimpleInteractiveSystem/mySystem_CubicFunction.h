//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/03/01
//
#ifndef __MY_CUBIC_FUNCTION_H_
#define __MY_CUBIC_FUNCTION_H_
#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
#include <vector>
using std::vector;
class CUBIC_FUNCTION
{
protected:
	// ax^3 + bx^2 + cx +d 
	double a, b, c, d;
	double x0, x1;
	int mNumSamples;
public:
	CUBIC_FUNCTION( );
	void askForInput( );
	void getRangeOfX( double &x0, double &x1 ) const;
	int getNumOfSamples( ) const;
	double getValue( double x ) const;
    void increase(double dv = 0.1);
    void decrease(double dv = 0.1);
    double getA() const { return a; }
    double getB() const { return b; }
    double getC() const { return c; }
    double getD() const { return d; }
};
#endif
// CODE: 2019/02/25. Do not delete this line.