//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
//

#ifndef __MY_TRAFFIC_SYSTEM_H_
#define __MY_TRAFFIC_SYSTEM_H_
#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
#include <vector>
#include "base_class.h"
#include "graph_basics.h"

using std::vector;

class AGENT {
public:
    AGENT( );
    //
    double cur_speed;
    vector3 cur_direction;
    //
    vector3 p; // position
    //vector3 v; // velocity
    double v_speed;
    vector3 v_direction;
    //
    double r; // radius
    vector3 dv; // desired velocity
    double sf; // speed factor
    int agentID;
    //
    double df_desired_speed; //default
    double df_safe_time_headway; // default
    double df_max_acc; // max acceleration
    double df_breaking_acc; // comfortable breaking deceleration
    double df_acc_exp; // acceleration exponent
    double df_min_distance; // minimum distance 2m
    double df_vehicle_length; // vehicle length
    //
    double len_on_lane; // travel length on the lane
    //
    int laneID;
    //
    void stop( );
    void computeVelocity( double time_step, const vector3 &desired_direction );
    void updatePosition( double time_step );
    //
    void computeVelocity( const AGENT *gj, double time_step );
};

class NODE : public AGENT {
public:
    NODE( );
    int nodeID;
    vector<int> in_laneID;
    vector<int> out_laneID;
};

class LANE {
public:

    int roadID;
    int laneID;
    int p0ID, p1ID; // from node p0 to node p1
};



class TRAFFIC_LIGHT {
public:
    int numStages;              // number of stages
    vector<double> stageDuration;   
    //
    int currentStage;           // the current stage
    double currentDuration;
};



class ROAD {
public:

    int roadID;
    vector<LANE *> lanes;
    void addLane( LANE *L );
};


class TRAFFIC_SYSTEM : public BASE_SYSTEM {
protected:
    NODE *addNode( const vector3 &p );
    ROAD *addRoad( );
    LANE *addLane( ROAD *r, int nodeID_0, int nodeID_1 );
AGENT *addAgent( const vector3 &p );
    //
LANE *getNearestLane( const vector3 &p );

    void reset( );
    void createSimpleRoadNetwork( );
    //
    void generateAgentRandomly( );

    void generateAgentsRandomly( int num );
    //
    void draw_Lane( const LANE *L ) const;
    void draw_Lanes( ) const;
    void draw_Agent( const AGENT *g ) const;
    void draw_Agents(  ) const;
    //
    void resolveAgentCollision( AGENT *g0, AGENT *g1 );
    void resolveAgentCollision( );
    void update( double time_step );
    //
    void computeVelocity_Agent( AGENT *g, double  time_step );
    bool isLeader( const AGENT *g, const AGENT *gi, double &d2 ) const;
    AGENT *getLeader( const AGENT *g );
    //
    void transiteAgentToAdjacentLane( AGENT *g );
    void transiteAgentsToAdjacentLane(  );

public:
    TRAFFIC_SYSTEM( );
    void draw( ) const;
    void askForInput( );
    void update( );
    bool handleKeyPressedEvent( unsigned char key );
    bool handleSpecialKeyPressedEvent( unsigned char key );

protected:
    vector<AGENT *> mAgents;
    vector<ROAD *> mRoads;
    vector<LANE *> mLanes; 
    vector<NODE *> mNodes;
};

#endif