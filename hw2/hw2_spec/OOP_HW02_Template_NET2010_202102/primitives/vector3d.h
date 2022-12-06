#ifndef _WAGO_VECTOR_3D_H_
#define _WAGO_VECTOR_3D_H_

#include <math.h>

#define v3_float float
//#define v3_float double

class vector3
{
public:
	vector3() : x( 0.0f ), y( 0.0f ), z( 0.0f ) {};
	vector3( v3_float a_X, v3_float a_Y, v3_float a_Z ) : x( a_X ), y( a_Y ), z( a_Z ) {};
	void Set( v3_float a_X, v3_float a_Y, v3_float a_Z ) { x = a_X; y = a_Y; z = a_Z; }
	void zero() { x = y = z = 0.0; }
	float Normalize() { v3_float L = Length( ); v3_float h = 1.0f / L; x *= h; y *= h; z *= h; return L; }
	vector3 Normalized() { v3_float h = 1.0f / Length(); return vector3( x * h, y * h, z * h ); }
	v3_float Length() const { return (v3_float)sqrt( x * x + y * y + z * z ); }

	v3_float SqrLength() const { return x * x + y * y + z * z; }
	vector3 Perp( vector3& a, vector3& axis);
	vector3 Parallel( vector3& a, vector3& axis );
	v3_float dot( const vector3 &a_V ) const { return x * a_V.x + y * a_V.y + z * a_V.z; }
	v3_float distance( const vector3 &a_V ) const { return sqrt((x - a_V.x)*(x - a_V.x) + (y - a_V.y)*(y - a_V.y) + (z - a_V.z)*(z - a_V.z)); }
	v3_float distance2( const vector3 &a_V ) const { return ((x - a_V.x)*(x - a_V.x) + (y - a_V.y)*(y - a_V.y) + (z - a_V.z)*(z - a_V.z)); }
	const vector3 cross( const vector3 &v ) const { return vector3( y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x ); }
	vector3 RotateAround( vector3& a_Axis, v3_float a_Angle );
	vector3 Perpendicular();
	void operator += ( const vector3& a_V ) { x += a_V.x; y += a_V.y; z += a_V.z; }
	void operator += ( vector3* a_V ) { x += a_V->x; y += a_V->y; z += a_V->z; }
	void operator -= ( const vector3& a_V ) { x -= a_V.x; y -= a_V.y; z -= a_V.z; }
	void operator -= ( vector3* a_V ) { x -= a_V->x; y -= a_V->y; z -= a_V->z; }
	void operator *= ( const v3_float f ) { x *= f; y *= f; z *= f; }
	void operator *= ( const vector3& a_V ) { x *= a_V.x; y *= a_V.y; z *= a_V.z; }
	void operator *= ( vector3* a_V ) { x *= a_V->x; y *= a_V->y; z *= a_V->z; }
	v3_float& operator [] ( int a_N ) { return cell[a_N]; }
	vector3 operator- () const { return vector3( -x, -y, -z ); }
	friend vector3 operator + ( const vector3& v1, const vector3& v2 );
	friend vector3 operator + ( const vector3& v1, vector3* v2 );
	friend vector3 operator - ( const vector3& v1, const vector3& v2 );
	friend vector3 operator - ( const vector3& v1, vector3* v2 );
	friend vector3 operator - ( const vector3* v1, vector3& v2 );
	// extern vector3 operator - ( const vector3* v1, vector3* v2 ) { return vector3( v1->x - v2->x, v1->y - v2->y, v1->z - v2->z ); }
	friend vector3 operator ^ ( const vector3& A, const vector3& B );
	friend vector3 operator ^ ( const vector3& A, vector3* B );
	friend vector3 operator * ( const vector3& v, const v3_float f );
	friend vector3 operator * ( const vector3& v1, const vector3& v2 );
	friend vector3 operator * ( const v3_float f, const vector3& v );
	friend vector3 operator / ( const vector3& v, const v3_float f );
	friend vector3 operator / ( const vector3& v1, const vector3& v2 );
	friend vector3 operator / ( const v3_float f, const vector3& v );

	bool operator == ( const vector3& a_V ) { if((x==a_V.x)&&(y==a_V.y)&&(z==a_V.z)) return true; return false; }
	bool operator == ( const vector3* a_V ) { if((x==a_V->x)&&(y==a_V->y)&&(z==a_V->z)) return true; return false; }
	bool operator != ( const vector3& a_V ) { if((x==a_V.x)&&(y==a_V.y)&&(z==a_V.z)) return false; return true; }
	bool operator != ( const vector3* a_V ) { if((x==a_V->x)&&(y==a_V->y)&&(z==a_V->z)) return false; return true; }
private:
	int MinAxis() { return (fabs(x)<=fabs(y)?((fabs(x)<=fabs(z))?0:2):((fabs(y)<=fabs(z))?1:2)); }
public:
	union
	{
		struct { v3_float x, y, z; };
		struct { v3_float nx, ny, nz; };
		struct { v3_float cell[3]; };
		struct { v3_float e[3];};
		struct {  v3_float r, g, b; };
		v3_float xyz[3];
		v3_float ptr[3];
		v3_float p[3];
	};
};

extern void printf_vector3( const char *msg, const vector3 &p );
#endif