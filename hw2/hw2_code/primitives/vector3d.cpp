#include <iostream>
#include <math.h>
#include "vector3d.h"	

using namespace std;

#define PI 3.141592654

vector3 operator + ( const vector3& v1, const vector3& v2 ) { return vector3( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z ); }
	vector3 operator + ( const vector3& v1, vector3* v2 ) { return vector3( v1.x + v2->x, v1.y + v2->y, v1.z + v2->z ); }
	vector3 operator - ( const vector3& v1, const vector3& v2 ) { return vector3( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z ); }
	vector3 operator - ( const vector3& v1, vector3* v2 ) { return vector3( v1.x - v2->x, v1.y - v2->y, v1.z - v2->z ); }
	vector3 operator - ( const vector3* v1, vector3& v2 ) { return vector3( v1->x - v2.x, v1->y - v2.y, v1->z - v2.z ); }
	// friend vector3 operator - ( const vector3* v1, vector3* v2 ) { return vector3( v1->x - v2->x, v1->y - v2->y, v1->z - v2->z ); }
	vector3 operator ^ ( const vector3& A, const vector3& B ) { return vector3(A.y*B.z-A.z*B.y,A.z*B.x-A.x*B.z,A.x*B.y-A.y*B.x); }
	vector3 operator ^ ( const vector3& A, vector3* B ) { return vector3(A.y*B->z-A.z*B->y,A.z*B->x-A.x*B->z,A.x*B->y-A.y*B->x); }
	vector3 operator * ( const vector3& v, const v3_float f ) { return vector3( v.x * f, v.y * f, v.z * f ); }
	vector3 operator * ( const vector3& v1, const vector3& v2 ) { return vector3( v1.x * v2.x, v1.y * v2.y, v1.z * v2.z ); }
	vector3 operator * ( const v3_float f, const vector3& v ) { return vector3( v.x * f, v.y * f, v.z * f ); }
	vector3 operator / ( const vector3& v, const v3_float f ) { return vector3( v.x / f, v.y / f, v.z / f ); }
	vector3 operator / ( const vector3& v1, const vector3& v2 ) { return vector3( v1.x / v2.x, v1.y / v2.y, v1.z / v2.z ); }
	vector3 operator / ( const v3_float f, const vector3& v ) { return vector3( v.x / f, v.y / f, v.z / f ); }

	
vector3 vector3::Perpendicular() 
{ 
	int ma = MinAxis(); 
	if (ma == 0) return vector3( 0, z, -y ); 
	else if (ma == 1) return vector3( z, 0, -x );
	else return vector3( y, -x, 0 );
}

vector3 vector3::RotateAround( vector3& a_Axis, v3_float a_Angle )
{
	v3_float a = (float) (a_Angle * PI / 180.0f);
	if (a < 0) a += 360;
	v3_float cosTheta = cosf( a );
	v3_float sinTheta = sinf( a );
	vector3 current( x, y, z );
	current = Perp( current, a_Axis ) * cosTheta + a_Axis.cross( current ) * sinTheta + Parallel( current, a_Axis ); 
	return current;
}

vector3 vector3::Perp( vector3& a, vector3& axis)
{
	vector3	temp = a - Parallel( a, axis );
	return temp;
}

vector3 vector3::Parallel( vector3& a, vector3& axis )
{
	vector3	temp = axis * a.dot( axis );
	return temp;
}

void printf_vector3( const char *msg, const vector3 &p )
{
	cout << msg << "\t" << p.x << "\t" << p.y << "\t" << p.z << endl;
}