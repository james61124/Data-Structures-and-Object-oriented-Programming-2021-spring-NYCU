#include "basic_tools.h"

using namespace std;

float bt_random_value_interval( float minv, float maxv )
{
	float f = (rand()%RAND_MAX)/(float)RAND_MAX;
	float v = minv + f*( maxv - minv );
	return v;
}

vector3 bt_random_sample_on_circle_boundary_XZPlane( const vector3 &p, float r )
{
	vector3 q;
	float a = bt_random_value_interval(0.0f, 3.14f*2.0f);
	q.x = p.x + r*cos(a);
	q.z = p.z + r*sin(a);
	
	return q;
}

vector3 bt_random_sample_circle_XZPlane( const vector3 &p, float r )
{
	vector3 q;
	

	while ( true ) {
		float f0 = bt_random_value_interval(-1.0, 1.0 );
		float f1 = bt_random_value_interval(-1.0, 1.0 );
		if ( 1.0 >= f0*f0 + f1*f1 ) {
			q = p + r*f0*vector3(1.0, 0.0, 0.0 );
			q += r*f1*vector3(0.0, 0.0, 1.0 );
			break;
		} else {

		}
	}
	return q;
}

//
// d2 is the shortest distance from the point
// q to the closest path point.
//
// return -1: number of points <=0
//
int bt_computeClosestPathPointIndex( const vector3 &q, const vector3 *p, int numPathPoints, float &d2 )
{
	int vert_index = -1;
	d2 = -1.0;
	if ( numPathPoints <= 0 ) return vert_index;
	vert_index = 0;
	d2 = p[0].distance2(q);
	for ( int i = 1; i < numPathPoints; ++i ) 
	{
		float tmp_d2 = p[i].distance2(q);

		if ( d2 > tmp_d2 ) {
			d2 = tmp_d2;
			vert_index = i;
			
		}
	}
	return vert_index;
}

//
// d2 is the shortest distance from the point q
// to the closest path edge.
// The first edge index is 0, i.e. (p[0], p[1]).
//
// return -1: number of points <=1
// 
int bt_computeClosestPathEdgeIndex( const vector3 &q, const vector3 *p, int numPathPoints, float &d2 )
{
	int edge_index = -1;
	d2 = -1.0;
	if ( numPathPoints <= 1 ) return edge_index;
	d2 = bt_computeDistance2_LineSegment( q, p[0], p[1] );
	edge_index = 0;
	for ( int i = 1; i < numPathPoints - 1; ++i ) {
		float tmp_d2;
		tmp_d2 = bt_computeDistance2_LineSegment( q, p[i], p[i+1] );
		if ( d2 > tmp_d2 ) {
			d2 = tmp_d2;
			edge_index = i;
		}
	}	
	return edge_index;
}


// v is a unit vector
vector3 bt_eliminateNegativeVectorComponent(const vector3 &u, const vector3 &v )
{
	vector3 n;
	float d = u.dot(v);
	if ( d >= 0.0 ) return u;
	n = u - d*v;
	return n;
}

vector3 bt_computeNearestPoint( const vector3 &p, const vector3 &q0, const vector3 &q1 )
{
	vector3 q;
	float d2 = -1.0;
	vector3 qq = q1 - q0;
	float Lqq = qq.Normalize( );
	if ( Lqq == 0.0 ) {
		return q0;
	}
	vector3 pq0 = p - q0;

	float projection_length = pq0.dot( qq );
	if ( projection_length <= 0.0 ) {
		q = q0;
	} else if ( projection_length >= Lqq ) {
		q = q1;
	} else {
		q = q0 + projection_length*qq;
	}
	return q;
}

bool bt_collidePointLineSegment( const vector3 &p, float d2, const vector3 &p0, const vector3 &p1 )
{
	bool flg = false;
	vector3 q = bt_computeNearestPoint( p, p0, p1 );
	if ( d2 > q.distance2(p) ) return true;
	return flg;
}

bool bt_collidePointLineSegment( const vector3 &p, float d2, const vector3 &p0, const vector3 &p1, vector3 &collision_point )
{
	bool flg = false;
	collision_point = bt_computeNearestPoint( p, p0, p1 );
	if ( d2 > collision_point.distance2(p) ) return true;
	return flg;
}

float bt_computeDistance2_LineSegment( const vector3 &p, const vector3 &q0, const vector3 &q1 )
{
	float d2 = -1.0;
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

void bt_computeUnitOrthoVector( const vector3 &source_dir, vector3 &target_dir )
	{
		target_dir.zero( );
		if ( source_dir.z != 0.0 ) 
		{
			target_dir.x = 1.0;
			target_dir.y = 0.0;
			target_dir.z = -(source_dir.x * target_dir.x)/source_dir.z;
		} else if ( source_dir.y != 0.0 ) {
			target_dir.x = 1.0;
			target_dir.z = 0.0;
			target_dir.y = -(source_dir.x * target_dir.x)/source_dir.y;
		}
		else {
			target_dir.y = 1.0;
			target_dir.z = 0.0;
			target_dir.x = -(source_dir.y * target_dir.y)/source_dir.x;
		}
		target_dir.Normalize( );

		//cout << "dot(u, v):" << v.dot(u) << endl;
		//bt_printf_vec3("u", u);
		//bt_printf_vec3("computeUnitOrthoVector:", v); 
	}

//
// rotate p about the axis with respect to the point q.
// angle is in radian
//
vector3 bt_rotatePointAboutAxis
( 
	 const vector3 &p, const vector3 &q, 
	 float angle, const vector3 &axis 
)
{
	//printf_vec3("axis", axis);
	vector3 p_new;
	vector3 pq = p - q;
	float d_n = pq.dot( axis );
	vector3 pqn = d_n*axis;
	vector3 ppqn = pq - pqn;
	float r = ppqn.Length( );
	if (  r <= 0.0001 ) return p;
	ppqn.Normalize( );
	vector3 v = axis.cross( ppqn );
	v.Normalize( );
	p_new = r*ppqn*cos( angle ) + r*v*sin( angle );
	p_new += q+pqn;
	return p_new;
}

// angle is in radian
vector3 bt_rotateVectorAboutAxis
( 
	 const vector3 &v, 
	 float angle, const vector3 &axis 
)
{
	return bt_rotatePointAboutAxis( v, vector3(0.0, 0.0, 0.0), angle, axis );
}


//
// n = u x v
//
// The vectors u, v and n form a right hand coordinate system.
// the vectors prev_u, prev_v and prev_n form a right hand coordinate system.
// The goal is to compute a new set of u, v and n
// so that the twisted angle between the new set of u, v and n is minimum.
// Note: vector n is fixed. 
// Thus, the vectors u and v are rotated about n.
//
void bt_alignUVAxes( vector3 &n, vector3 &u, vector3 &v, const vector3 &prev_n, const vector3 &prev_u, const vector3 &prev_v )
{
	float prev_u_d = n.dot( prev_u );
	vector3 prev_u_n = prev_u - prev_u_d*n;
	//
	float prev_v_d = n.dot( prev_v );
	vector3 prev_v_n = prev_v - prev_v_d*n;
	//
	float L0 = prev_u_n.Normalize( );
	float L1 = prev_v_n.Normalize( );

	float u_angle, v_angle;
	float du = prev_u_n.dot( u );
	float dv = prev_v_n.dot( v );
	if ( du >= 1.0) u_angle = 0.0;
	else if ( du <= -1.0) u_angle = -3.14159f;
	else u_angle = acos( du );
	if ( dv >= 1.0) v_angle = 0.0;
	else if ( dv <= -1.0) v_angle = -3.14159f;
	else v_angle = acos( dv );

	float dir = n.dot((u.cross(prev_u_n)));

	if ( dir >= 0.0 ) {
		dir = u_angle;
	} else {
		dir = -u_angle;
	}

	//u = prev_u_n;
	//v = prev_v_n;
	u = prev_u_n;
	v = n.cross( u );

	/*
	bt_enforce_printf_num("alignUVAxes-----------------", 0);
	bt_enforce_printf_float("u angle", u_angle);
	bt_enforce_printf_float("v angle", v_angle);
	bt_enforce_printf_float("dot", u.dot(v));
	bt_enforce_printf_float("L0", L0);
	bt_enforce_printf_float("L1", L1);
	*/
}

//
// Input: cone_axis and up_dir are unit vectors.
// Compute a vector which is inside the cone( cone_axis, angle );
// The vector is orthogonal to up_dir. 
//
vector3 bt_computeRandomUnitDirectionInsideCone
( 
 const vector3 &cone_axis, 
 float angle_degree, 
 const vector3 &up_dir
 )
{
	vector3 u;
	float a = bt_random_value_interval( -angle_degree, angle_degree );
	a = a/180.0f*3.141592654f;
	vector3 v = up_dir.cross( cone_axis );
	u = cone_axis*cos(a) + v*sin(a);
	u.Normalize( );
	return u;
}

//
// Input n is a unit vector.
// Return the orthogonal component of v with respect to n.
//
//
vector3 bt_computeOrthogonalComponentVector
( 
 const vector3 &v,
 const vector3 &n
)
{
	vector3 u;
	float d = v.dot( n );
	u = v - n*d;
	return u;
}

//
// Compute a random vector which is u*cos(a) + v*sin(a)
// The vector lies on the plane formed by u and v.
//
vector3 bt_computeRandomUnitDirection( const vector3 &u, const vector3 &v )
{
	float a = bt_random_value_interval(0.0f, 3.14159f*2.0f);
	return u*cos(a) + v*sin(a);
}


#ifndef PL_DEBUG
void bt_printf_vec3(const char *msg, const vector3 &u) { }
void bt_printf_num( const char *msg, int num ) { }
#endif // not PL_DEBUG

void bt_enforce_printf_vec3(const char *msg, const vector3 &u)
{
	cout << msg << "\tvec3:" << u.x << "\t" << u.y << "\t" << u.z << endl;
}

void bt_enforce_printf_num( const char *msg, int num )
{
	cout << msg << "\tnum:" << num << endl;
}

void bt_enforce_printf_float( const char *msg, float v )
{
	cout << msg << "\tvalue:" << v << endl;
}

#ifdef PL_DEBUG

void bt_printf_vec3(const char *msg, const vector3 &u)
{
	cout << msg << "\tvec3:" << u.x << "\t" << u.y << "\t" << u.z << endl;
}

void bt_printf_num( const char *msg, int num )
{
	cout << msg << "\tnum:" << num << endl;
}

#endif // PL_DEBUG