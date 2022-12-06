#include "mySystem_Traffic.h"
#include "myBasicTools.h"

#include <iostream>

using namespace std;

AGENT::AGENT( )
{
    
    len_on_lane = 0.0;
    
    //
    df_desired_speed = 10; // meter/sec
     //df_safe_time_headway = 1.5; // second
     df_safe_time_headway = 0.5; // second
     
    df_max_acc = 1.0; // meter/second^2
     df_acc_exp = 4; // acceleration exponent
     df_min_distance = 2.0; //meter. minimum distance 2m
     df_vehicle_length = 5.0; // meter
     df_breaking_acc = 2.0; // meter/second^2
     //
     r = df_vehicle_length/2.0;
     sf = getRandDouble(0.5, 1.5);

     df_desired_speed *= sf;
     //
      cur_speed = 0.0;
      cur_direction = vector3( 1.0, 0.0, 0.0 );
}

void AGENT::computeVelocity( const AGENT *gj, double time_step )
{
    double inc_term = pow( cur_speed/df_desired_speed, df_acc_exp);
    double a_free = df_max_acc*(1.0 - inc_term );

    double a_inter = 0.0;
    if ( gj ) {
        double dv = cur_speed - gj->cur_speed;
        double s = df_min_distance 
            + cur_speed*df_safe_time_headway 
            + cur_speed*dv/(2.0*sqrt(df_max_acc*df_breaking_acc));


        //distance
        double d;
        d = p.distance( gj->p ) - r - gj->r; 
        double ss = s/d;

        a_inter = -df_max_acc*ss*ss;
    }
    //
    //v = cur_speed*cur_direction;
    //
    double a = a_free + a_inter;

    v_speed = cur_speed + a*time_step;
    if ( v_speed < 0.0 ) v_speed = 0.0;
    v_direction = cur_direction;

}

void AGENT::stop( )
{
    //dv is used for determining the direction
    //
    v_speed = 0;
    cur_speed = 0.0;
}

// simple 
void AGENT::computeVelocity( double time_step, const vector3 &desired_direction )
{
    double s = df_desired_speed;
    dv = desired_direction*s;
    v_speed = s;
    v_direction = desired_direction;
}

void AGENT::updatePosition( double time_step )
{
    p = p + v_speed*v_direction*time_step;
    //
    cur_direction = v_direction;
    cur_speed = v_speed;
}

NODE::NODE( )
{
    v_speed = 0.0;
    cur_speed = 0.0;
    r = 0.0;
}

void ROAD::addLane( LANE *L )
{
    lanes.push_back( L );
}

TRAFFIC_SYSTEM::TRAFFIC_SYSTEM( )
{
    reset( );
    
}

void TRAFFIC_SYSTEM::reset( )
{
    mNodes.resize( 0 ); //memory not release. BUG
    mLanes.resize( 0 ); //memory not release. BUG
    mRoads.resize( 0 ); //memory not release. BUG
    mAgents.resize( 0 ); //memory not release. BUG
    
    createSimpleRoadNetwork( );
    generateAgentsRandomly( 20 );
    resolveAgentCollision( );
}

void TRAFFIC_SYSTEM::askForInput( )
{
}

void TRAFFIC_SYSTEM::createSimpleRoadNetwork( )
{
    double len = 400.0;
    double lane_gap = 8.0;
    NODE *n[6][2];
    n[0][0] = addNode( vector3( 0.0, 0.0, 0.0 ) );
    n[0][1] = addNode( vector3( len, 0.0, 0.0 ) );
    //
    n[1][0] = addNode( vector3( 0.0, 0.0, lane_gap ) );
    n[1][1] = addNode( vector3( len, 0.0, lane_gap ) );
    //
    n[2][0] = addNode( vector3( len, 0.0, 0.0 ) );
    n[2][1] = addNode( vector3( len*1.5, 0.0, 0.0 ) );
    //
    n[3][0] = addNode( vector3( len, 0.0, lane_gap ) );
    n[3][1] = addNode( vector3( len*1.5, 0.0, lane_gap ) );
    //
    n[4][0] = addNode( vector3( len*1.5, 0.0, 0.0 ) );
    n[4][1] = addNode( vector3( len*3, 0.0, 0.0 ) );
    //
    n[5][0] = addNode( vector3( len*1.5, 0.0, lane_gap ) );
    n[5][1] = addNode( vector3( len*3, 0.0, lane_gap ) );
    //
    ROAD *r[2];
    r[0] = addRoad( );

    LANE *L[6];
    L[0] = addLane( r[0],  n[0][0]->nodeID, n[0][1]->nodeID );
    L[1] = addLane( r[0],  n[2][0]->nodeID, n[2][1]->nodeID );
    L[2] = addLane( r[0],  n[4][0]->nodeID, n[4][1]->nodeID );
    
    L[3] = addLane( r[0],  n[1][0]->nodeID, n[1][1]->nodeID );
    L[4] = addLane( r[0],  n[3][0]->nodeID, n[3][1]->nodeID );
    L[5] = addLane( r[0],  n[5][0]->nodeID, n[5][1]->nodeID );


}

LANE *TRAFFIC_SYSTEM::getNearestLane( const vector3 &p )
{
    LANE *L = 0;
    double cur_d2 = -1.0;
    for ( int i = 0; i < mLanes.size( ); ++i ) {
        LANE *cL = mLanes[ i ];
        vector3 p0 = mNodes[ cL->p0ID ]->p;
        vector3 p1 = mNodes[ cL->p1ID ]->p;
        double d2 = computePointLineSegmentDistance2( p, p0, p1 );
        if ( cur_d2 < 0.0 || cur_d2 > d2 ) {
            cur_d2 = d2;
            L = cL;
        }
    }
    return L;
}

AGENT *TRAFFIC_SYSTEM::addAgent( const vector3 &p )
    {
        AGENT *g = new AGENT;
        g->agentID = mAgents.size( );
        g->p = p;
        g->len_on_lane = 0.0;
        mAgents.push_back( g );
        //
        LANE *L = getNearestLane( p );
        g->laneID = -1;
        if ( L ) {
            g->laneID = L->laneID;
            g->cur_speed = 0.0;
            vector3 dir = mNodes[ L->p1ID ]->p - mNodes[ L->p0ID ]->p;
            dir.Normalize( );
            g->cur_direction = dir;
            g->dv = g->cur_speed*g->cur_direction;
            g->v_speed = g->cur_speed;
            g->v_direction = g->cur_direction;
            g->p.z = mNodes[ L->p1ID ]->p.z;
        }
        //
        return g;
    }

    NODE *TRAFFIC_SYSTEM::addNode( const vector3 &p )
    {
        NODE *n = new NODE;
        n->nodeID = mNodes.size( );
        n->p = p;
        mNodes.push_back( n );
        return n;
    }

    ROAD *TRAFFIC_SYSTEM::addRoad( )
    {
        ROAD *r = new ROAD;
        r->roadID = mRoads.size( );
        mRoads.push_back( r );
        return r;
    }

    //
    // source node (nodeID_0) to target node (nodeID_1)
    //
    LANE *TRAFFIC_SYSTEM::addLane( ROAD *r, int nodeID_0, int nodeID_1 )
    {
        LANE *L = new LANE;
        int id = mLanes.size( );
        mLanes.push_back( L );
        L->p0ID = nodeID_0;
        L->p1ID = nodeID_1;
        L->laneID = id;
        //
        mNodes[ nodeID_0]->out_laneID.push_back( L->laneID );
        mNodes[ nodeID_1]->in_laneID.push_back( L->laneID );

        //
        r->addLane( L );
        return L;
    }

    void TRAFFIC_SYSTEM::generateAgentRandomly(  )
    {
        double minx = 0.0;
        double maxx = 40.0;
        double minz = 0.0;
        double maxz = 10.0;
        vector3 p;
        p.x = getRandDouble( minx, maxx );
        p.z = getRandDouble( minz, maxz );
        addAgent( p );

    }
    void TRAFFIC_SYSTEM::generateAgentsRandomly( int num )
    {
        for ( int i = 0; i < num; ++i ) {
            generateAgentRandomly( );
        }
    }

    void TRAFFIC_SYSTEM::resolveAgentCollision( AGENT *gi, AGENT *gj )
    {
        if ( gi->laneID != gj->laneID ) return;

        double R = gi->r + gj->r;
        double R2 = R*R;
        vector3 pji = gj->p - gi->p;
        double d2 = gj->p.distance2(gi->p);
        //
        double e = 0.001;
        if ( R2 + e > d2 ) {
            double d = sqrt( d2 );
            double h = 0.5*(R + e - d);
            vector3 n = pji.Normalized( );
            gi->p = gi->p - h*n;
            gj->p = gj->p + h*n; 


        }
    }

    void TRAFFIC_SYSTEM::resolveAgentCollision( )
    {
        for ( int i = 0; i < mAgents.size( ); ++i ) {
            AGENT *gi = mAgents[ i ];
            for ( int j = i + 1; j < mAgents.size( ); ++j ) {
                AGENT *gj = mAgents[ j ];
                resolveAgentCollision( gi, gj );
            }
        }
    }

    // is gj the leader of gi?
    bool TRAFFIC_SYSTEM::isLeader( const AGENT *gi, const AGENT *gj, double &d2 ) const
    {
        bool flg = false;
        //
        double R = gi->r + gj->r;
        double R2 = R*R;
        vector3 pji = gj->p - gi->p;
        d2 = gj->p.distance2(gi->p);
        //
        //
        
        double e = 0.001;
       // if ( R2 + e >= d2 ) {
            // check who in the front
            double di = pji.dot( gi->cur_direction );
            double dj = pji.dot( gj->cur_direction );
            if ( dj > 0.0 ) {
                //gj in front
                flg = true;
            } else {
                //gi in front
                

            }
       // }
 
        //
        return flg;
    }

    AGENT *TRAFFIC_SYSTEM::getLeader( const AGENT *g )
    {
        AGENT *cur_L = 0;
        double cur_d2 = -1.0;
        for ( int i = 0 ; i < mAgents.size( ); ++i ) {
                AGENT *gi = mAgents[ i ];
                if ( gi == g ) continue;
                if ( gi->laneID != g->laneID ) continue;
                double d2;
                bool flg = isLeader( g, gi, d2 );
                if ( !flg ) continue;
                if ( cur_d2 < 0.0 || cur_d2 > d2) {
                    cur_d2 = d2;
                    cur_L = gi;
                }
            }

        return cur_L;
    }

    void TRAFFIC_SYSTEM::computeVelocity_Agent( AGENT *g, double  time_step )
    {
        AGENT *gj = getLeader( g );

        if ( gj == 0 ) {
            int laneID = g->laneID;
            int nodeID = mLanes[ laneID ]->p1ID;
            gj = static_cast<AGENT *>(mNodes[ nodeID ]); 
        }
        g->computeVelocity( gj, time_step );
    }

    void TRAFFIC_SYSTEM::transiteAgentToAdjacentLane( AGENT *g )
    {
            int laneID = g->laneID;
            if ( laneID < 0 ) return;
            LANE *L = mLanes [ laneID ];
            NODE *n0 = mNodes[ L->p0ID ];
            NODE *n1 = mNodes[ L->p1ID ];
            //
            vector3 gpp = g->p - n1->p;
            double d = gpp.Length( );
            double r = g->r;
            double e = 0.01;
            double safe_d = g->df_min_distance;

            double de = d - r - safe_d;
            if ( 10.0 > de) cout << "de:" << de << endl;
            if ( e > de ) {
                if ( n1->out_laneID.size( ) == 0 ) return;
                g->laneID = n1->out_laneID[ 0 ];

            }
    }

    void TRAFFIC_SYSTEM::transiteAgentsToAdjacentLane( )
    {
        for ( int i = 0; i < mAgents.size( ); ++i ) {
            AGENT *g = mAgents[ i ];
            transiteAgentToAdjacentLane( g );
        }
    }

    void TRAFFIC_SYSTEM::update( double time_step )
    {
        vector3 desired_direction;
        for ( int i = 0; i < mAgents.size( ); ++i ) {
            AGENT *g = mAgents[ i ];
            int laneID = g->laneID;
            if ( laneID < 0 ) continue;
            LANE *L = mLanes [ laneID ];
            NODE *n0 = mNodes[ L->p0ID ];
            NODE *n1 = mNodes[ L->p1ID ];

            desired_direction = n1->p - g->p;
             
            double len = desired_direction.Normalize( );
            if ( len > 0.0001 ) {
                //g->computeVelocity( time_step, desired_direction );
                computeVelocity_Agent( g, time_step );
            } else {
                g->stop( );
            }
        }

        resolveAgentCollision( );
        for ( int i = 0; i < mAgents.size( ); ++i ) {
            AGENT *g = mAgents[ i ];
            int laneID = g->laneID;
            if ( laneID < 0 ) continue;
            LANE *L = mLanes [ laneID ];
            NODE *n0 = mNodes[ L->p0ID ];
            NODE *n1 = mNodes[ L->p1ID ];
            vector3 np = n1->p - g->p;
            double L_np2 = np.SqrLength( );
            double L_v = g->v_speed*time_step;
            if (  L_np2 > L_v*L_v ) {
                g->updatePosition( time_step );
            } else {
                g->p = n1->p;
            }
        }
    }

    void TRAFFIC_SYSTEM::update(  )
    {
        double dt = 0.005;
        update( dt );
        transiteAgentsToAdjacentLane( );
    }

    bool TRAFFIC_SYSTEM::handleKeyPressedEvent( unsigned char key )
    {
        switch ( key ) {
        case 'r':
        case 'R':
            reset( );
            break;
        }
        return true;
    }

    bool TRAFFIC_SYSTEM::handleSpecialKeyPressedEvent( unsigned char key )
    {
        return true;
    }