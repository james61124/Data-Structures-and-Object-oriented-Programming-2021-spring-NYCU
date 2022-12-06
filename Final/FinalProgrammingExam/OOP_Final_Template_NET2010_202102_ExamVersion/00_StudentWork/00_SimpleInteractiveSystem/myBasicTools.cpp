#include <iostream>
#include "myBasicTools.h"

/*
Generate a random numbe 
between x0 and x1 (inclusive).
*/
double getRandDouble(double x0, double x1)
{
    int r = rand()%RAND_MAX;
    double f = r/(double)RAND_MAX;
    return x0 + f*(x1-x0);
}

double computePointLineSegmentDistance2( const vector3 &p, const vector3 &q0, const vector3 &q1 )
{
    double d2 = -1.0;
	vector3 qq = q1 - q0;
	float Lqq = qq.Normalize( );
	if ( Lqq == 0.0 ) {
		return p.distance2( q0 );
	}
	vector3 pq0 = p - q0;

	float projection_length = pq0.dot( qq );
	if ( projection_length <= 0.0 ) {
		return p.distance2( q0 );
	} else if ( projection_length >= Lqq ) {
		return p.distance2( q1 );
	} else {
		vector3 p_on_qq = projection_length*qq;
		vector3 npq = pq0 - p_on_qq;

		return npq.SqrLength( );
	}
	return d2;
}