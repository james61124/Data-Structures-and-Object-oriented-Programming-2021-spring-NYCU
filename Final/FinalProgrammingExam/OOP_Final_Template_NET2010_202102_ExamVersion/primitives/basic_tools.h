//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// Date: 2014/12/30
//
#ifndef __BASIC_TOOLS_H__
#define __BASIC_TOOLS_H__
#include <math.h>
#include <iostream>
#include "vector3d.h"
extern float bt_random_value_interval( float minv, float maxv );
//
// bt_random_sample_circle_XZPlane: within the circle disk
extern vector3 bt_random_sample_circle_XZPlane( const vector3 &p, float r );
//
// bt_random_sample_on_circle_boundary_XZPlane: on boundary of the circle
extern vector3 bt_random_sample_on_circle_boundary_XZPlane( const vector3 &p, float r );
extern int bt_computeClosestPathPointIndex( const vector3 &q, const vector3 *p, int numPathPoints, float &d2 );
extern int bt_computeClosestPathEdgeIndex( const vector3 &q, const vector3 *p, int numPathPoints, float &d2 );

extern vector3 bt_eliminateNegativeVectorComponent(const vector3 &u, const vector3 &v );
extern bool bt_collidePointLineSegment( const vector3 &p, float d2, const vector3 &p0, const vector3 &p1 );
extern bool bt_collidePointLineSegment( const vector3 &p, float d2, const vector3 &p0, const vector3 &p1, vector3 &collision_point );
extern vector3 bt_computeNearestPoint( const vector3 &p, const vector3 &q0, const vector3 &q1 );
extern float bt_computeDistance2_LineSegment( const vector3 &p, const vector3 &q0, const vector3 &q1 );
extern void bt_computeUnitOrthoVector( const vector3 &source_dir, vector3 &target_dir );
extern vector3 bt_rotatePointAboutAxis
( 
	 const vector3 &p, const vector3 &q, 
	 float angle, const vector3 &axis 
);
extern vector3 bt_rotateVectorAboutAxis
( 
	 const vector3 &v, 
	 float angle, const vector3 &axis 
);

vector3 bt_computeRandomUnitDirectionInsideCone
( 
 const vector3 &cone_axis, 
 float angle_degree, 
 const vector3 &up_dir
);

vector3 bt_computeRandomUnitDirection( const vector3 &u, const vector3 &v );

extern vector3 bt_computeOrthogonalComponentVector
( 
 const vector3 &v,
 const vector3 &n
);

extern void bt_alignUVAxes( vector3 &n, vector3 &u, vector3 &v, const vector3 &prev_n, const vector3 &prev_u, const vector3 &prev_v );
extern float bt_get_random_float( float min_value, float max_value );
extern void bt_printf_vec3(const char *msg, const vector3 &u);
extern void bt_printf_num( const char *msg, int num );
template <class DB> void bt_enforce_printf_Array( const char *msg, const DB *arr, int num )
{
		std::cout << msg << std::endl;
	for ( int i = 0; i < num; ++i ) {
		std::cout << arr[i] << "\t";
	}
	std::cout << std::endl;
}


extern void bt_enforce_printf_vec3(const char *msg, const vector3 &u);
extern void bt_enforce_printf_num( const char *msg, int num );
extern void bt_enforce_printf_float( const char *msg, float v );


#endif