//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
//
#ifndef __MY_BASIC_TOOLS_H_
#define __MY_BASIC_TOOLS_H_
#include "../primitives/vector3d.h"

extern double getRandDouble(double x0, double x1);
extern double computePointLineSegmentDistance2( const vector3 &p, const vector3 &q0, const vector3 &q1 );
#endif