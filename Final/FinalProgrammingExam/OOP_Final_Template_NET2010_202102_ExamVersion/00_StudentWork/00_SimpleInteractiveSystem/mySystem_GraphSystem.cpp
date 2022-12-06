//********************************************
// Student Name			:
// Student ID			:
// Student Email Address:
//********************************************
//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/04/09
//
#include <iostream>
#include "mySystem_GraphSystem.h"
#include <time.h>
#include <queue>
#include <list>

using namespace std;

GRAPH_SYSTEM::GRAPH_SYSTEM( )
{
    ///////////////////////////////////////
    // DO NOT change these three lines
    mResult_BFS_max_depth = -1; 
    mOptionIndex = 1;
    mOption = (GraphOption) mOptionIndex;
    ///////////////////////////////////////
    //
    initMemoryPool();
    createDefaultGraph();
}

//
// DO NOT change getOptionName( )
//
string GRAPH_SYSTEM::getOptionName( ) const
{
    string name;
    char *names[] = {
        "GR_None",
        "GR_Neighbor",
        "GR_BFS",
        "GR_End" 
    };
    int index = mOptionIndex;
    return names[index];
}

bool GRAPH_SYSTEM::handleKeyPressedEvent( unsigned char key )
{

    switch( key ) {
    case '1':
        createDefaultGraph( );
        mSelectedNode = 0;
        break;
    case '2':
        createNet_Square(8);
        mSelectedNode = 0;
        break;
    case '3':
        createNet_RadialCircular(12,3);
        mSelectedNode = 0;
    case 'r':
        mOptionIndex = (mOptionIndex+1)%GR_End;
        mOption = (GraphOption)mOptionIndex;
        break;
    }
    clearVisitFlagAndDepthOfAllNodes( );
    return true;
}
//
// For every frame, update( ) function is called.
//
// 
void GRAPH_SYSTEM::update( )
{
    return;
}

void GRAPH_SYSTEM::initMemoryPool( )
{
    mNodeArr_Pool = new GRAPH_NODE[GRAPH_MAX_NUM_NODES];
    mEdgeArr_Pool = new GRAPH_EDGE[GRAPH_MAX_NUM_EDGES];

    mCurNumOfActiveNodes = 0;
    mCurNumOfActiveEdges = 0;
    mActiveNodeArr = new int[GRAPH_MAX_NUM_NODES];
    mActiveEdgeArr = new int[GRAPH_MAX_NUM_EDGES];

    mFreeNodeArr = new int[GRAPH_MAX_NUM_NODES];
    mFreeEdgeArr = new int[GRAPH_MAX_NUM_EDGES];
    //
    for ( int i = 0; i < GRAPH_MAX_NUM_NODES; ++i ) {
        mNodeArr_Pool[ i ].id = i;
    }
    for ( int i = 0; i < GRAPH_MAX_NUM_EDGES; ++i ) {
        mEdgeArr_Pool[ i ].id = i;
    }
    //
    reset( );
}

void GRAPH_SYSTEM::reset( )
{
    //mNumPoints_DoubleCircles = 0;

    mCurNumOfActiveNodes = 0;
    mCurNumOfActiveEdges = 0;

    mCurNumOfFreeNodes = GRAPH_MAX_NUM_NODES;
    mCurNumOfFreeEdges = GRAPH_MAX_NUM_EDGES;

    for ( int i = 0; i < mCurNumOfFreeNodes; ++i ) {
        mFreeNodeArr[ i ] = i;
    }
    for ( int i = 0; i < mCurNumOfFreeEdges; ++i ) {
        mFreeEdgeArr[ i ] = i;
    }

    mPassiveSelectedNode = 0;
    mSelectedNode = 0;

    mResult_BFS_max_depth = -1;
    ///////////////////////////////////
    //mOptionIndex = 1;
    //mOption = (GraphOption) mOptionIndex;

}

GRAPH_NODE *GRAPH_SYSTEM::getFreeNode( ) 
{
    if ( mCurNumOfFreeNodes == 0 ) return 0;
    --mCurNumOfFreeNodes;
    int id = mFreeNodeArr[ mCurNumOfFreeNodes ];
    GRAPH_NODE *n = &mNodeArr_Pool[ id ];
    mActiveNodeArr[ mCurNumOfActiveNodes ] = id;
    n->dynamicID = mCurNumOfActiveNodes;
    ++mCurNumOfActiveNodes;
    return n;
}

GRAPH_EDGE *GRAPH_SYSTEM::getFreeEdge( )
{
    if ( mCurNumOfFreeEdges == 0 ) return 0;
    --mCurNumOfFreeEdges;
    int id = mFreeEdgeArr[ mCurNumOfFreeEdges ];
    GRAPH_EDGE *e = &mEdgeArr_Pool[ id ];
    mActiveEdgeArr[ mCurNumOfActiveEdges ] = id;
    e->dynamicID = mCurNumOfActiveEdges;

    ++mCurNumOfActiveEdges;
    return e;
}

void GRAPH_SYSTEM::createDefaultGraph( )
{
    cout << "createDefaultGraph"<< endl;
    reset( );

    int n_0 = addNode( 0.0, 0.0, 0.0 );
    cout << "n_0:"<< n_0 << endl;
    //
    // Fill your or modify own stuff
    //
	int v0 = addNode(0.0, 0.0, 0.0, 1);
    int v1 = addNode(10.0, 0.0, 0.0, 1);
    int v2 = addNode(20.0, 0.0, 0.0, 1);

    addEdge(v0, v1);
    addEdge(v1, v2);
}

void GRAPH_SYSTEM::createNet_Square( int n )
{
    reset( );

    float dx = 5.0;
    float dz = 5.0;
    float r = 5; // radius
    float d = 5; // layer distance 
    float offset_x = 5.;
    float offset_z = 5.;
    vector<int> id;
    int num = n;
    int total = num*num;
    //id.resize( total );
	int number=0;
    for ( int j = 0; j < num; ++j ) {
        for ( int i = 0; i < num; ++i ) {
            float x, z;
            x = i*dx;
            z = j*dz;
            int index = i + j*num;
            //
            // Fill your or modify own stuff
            //
			number=addNode(5.0*i,0.0, 5.0*j, 1);
			id.push_back(number);
			//number++;
        }
    }
	for(int i=0;i<num*num-1;i++){
		if(i%8!=7){
			addEdge(id[i], id[i+1]);
		}
	}
	for(int i=0;i<num*num-8;i++){
		
			addEdge(id[i], id[i+8]);
		
	}

    //
    // Fill your or modify own stuff
    //
}
void GRAPH_SYSTEM::createNet_RadialCircular( int n, int num_layers ) {

    reset( );

    float offset_x = 15.0;
    float offset_z = 15.0;

    float r = 5; // radius
    vector<int> id;
    id.resize( n*num_layers + 1);
    id[ 0 ] = addNode( offset_x, 0.0, offset_z);

    //
    // Fill your or modify own stuff
    //
    /*for ( int j = 0; j < num_layers; ++j ) {
        for ( int i = 0; i < n; ++i ) {
        }
    }
    for ( int j = 0; j < num_layers; ++j ) {
        int index = n*j+1;
        for ( int i = 0; i < n; ++i ) {
            int k0, k1;
        }
    }*/
	vector<vector<int> > v; //第n橫排表第n內圈
    double theta = 2*3.14159 / n;
    v.resize(num_layers+1);

    for (int i = 0; i <= num_layers-1; i++) v[i].resize(n);//num_layers表有幾圈圓
    for (int i = 0; i <= num_layers-1; i++){
        for (int j = 0; j < n; j++) v[i][j] = addNode(offset_x + r*cos(theta*j), 0.0, offset_z + r*sin(theta*j), 1);
			r += 5;
    }
    for (int i = 0; i < num_layers-1; i++){
        for (int j = 0; j < n; j++){
            //addEdge(v[i][j], v[i][(j + 1) % n]);//內外圈連起來
            addEdge(v[i][j], v[i + 1][j]);
			//addEdge(v[0][1], v[1][j]);//同一圈連起來
        }

	}
	
}

int GRAPH_SYSTEM::addNode( float x, float y, float z, float r )
{
    GRAPH_NODE *g;
    g = getFreeNode( );
    if ( g == 0 ) return -1;
    g->p = vector3( x, y, z );
    g->r = r;
    g->edgeID.clear( );
    return g->id;
}

int GRAPH_SYSTEM::addEdge( int nodeID_0, int nodeID_1 )
{
    GRAPH_EDGE *e;
    e = getFreeEdge( );
    if ( e == 0 ) return -1;
    e->nodeID[ 0 ] = nodeID_0;
    e->nodeID[ 1 ] = nodeID_1;
    mNodeArr_Pool[ nodeID_0 ].edgeID.push_back( e->id );
    mNodeArr_Pool[ nodeID_1 ].edgeID.push_back( e->id );

    return e->id;
}

void GRAPH_SYSTEM::askForInput( )
{
}


GRAPH_NODE *GRAPH_SYSTEM::findNearestNode( 
    double x, 
    double z, 
    double &cur_distance2 
    ) const
{
    GRAPH_NODE *n = 0;
    cur_distance2 = -1.0;
    for ( int i = 0; i < mCurNumOfActiveNodes; ++i ) {
        int id = mActiveNodeArr[ i ];
        const GRAPH_NODE *cn = &mNodeArr_Pool[ id ];
        double dx = cn->p.x - x;
        double dz = cn->p.z - z;
        double d2 = dx*dx + dz*dz;
        if ( cur_distance2 < 0.0 || d2 < cur_distance2 ) {
            //
            // Update n
            //
            //
            // Fill your or modify own stuff
            //
        }

    }
    return n;
}

void GRAPH_SYSTEM::clickAt(double x, double z)
{
    clearVisitFlagAndDepthOfAllNodes( );

    double cur_d2;
    GRAPH_NODE *n = findNearestNode( x, z, cur_d2 );
    if ( n == 0 ) {
        mSelectedNode = 0;
        return;
    }
    if ( cur_d2 > n->r*n->r ) {
        mSelectedNode = 0;
        return;

    }
    if ( mSelectedNode == n ) {
        mSelectedNode = 0;
        return;
    }
    mSelectedNode = n;

    if ( mOption == GR_BFS ) {
        bfs( );
    }
}

bool GRAPH_SYSTEM::isSelectedNode( ) const
{
    return mSelectedNode != 0;
}

void GRAPH_SYSTEM::getInfoOfSelectedPoint( double &r, vector3 &p ) const
{
    if ( isSelectedNode( ) == false ) return;
    //r = mSelectedNode->r;
    //p = mSelectedNode->p;
    r = 0.5;
    p = vector3(1.0, 0.0, 0.0);
    //
    // Fill your or modify own stuff
    //
}



bool GRAPH_SYSTEM::handlePassiveMouseEvent( double x, double z )
{
    double cur_d2;
    GRAPH_NODE *n = findNearestNode( x, z, cur_d2 );
    if ( n == 0 ) return true;
    if ( cur_d2 > n->r*n->r ) {
        mPassiveSelectedNode = 0;
        return true;
    }
    mPassiveSelectedNode = n;

    return true;

}

int GRAPH_SYSTEM::getNumOfNodes( ) const
{
    return mCurNumOfActiveNodes;
}

void GRAPH_SYSTEM::getNodeInfo( int nodeIndex, double &r, vector3 &p ) const
{
    int nodeID = mActiveNodeArr[ nodeIndex ];
    GRAPH_NODE *n = &mNodeArr_Pool[ nodeID ];
    r = n->r;
    p = n->p;
}

int GRAPH_SYSTEM::getNumOfEdges( ) const
{
    return mCurNumOfActiveEdges;
}

vector3 GRAPH_SYSTEM::getNodePositionOfEdge( int edgeIndex, int nodeIndex ) const
{
    int edgeID = mActiveEdgeArr[ edgeIndex ];
    GRAPH_EDGE *e = &mEdgeArr_Pool[ edgeID ];
    return mNodeArr_Pool[ e->nodeID[ nodeIndex ] ].p;
}



//
// Return the number of attached edges of the selected node
//
int GRAPH_SYSTEM::getNumOfAttachedEdgesOfSelectedNode( ) const
{
    int numAttachedEdges = 0;
    if (!mSelectedNode) return numAttachedEdges;

    //
    // Fill your or modify own stuff
    //
    //
    // Set numAttachedEdges as the number of attached edges
    // of the selected node
    //
    return numAttachedEdges;
}

//
// edgeIndex is inside [0, numAttachedEdges-1]
// An edge has two nodes. 
// Use nodeIndex 0 or 1 to obtain (p,r) of the node of the edge
//
void GRAPH_SYSTEM::getNodeInfoOfAttachedEdgeOfSelectedNode( 
    int edgeIndex
    , int nodexIndex
    , double &r
    , vector3 &p
    ) const
{
    if (!mSelectedNode) return;

    int edgeID = mSelectedNode->edgeID[edgeIndex];
    GRAPH_EDGE *e = &mEdgeArr_Pool[ edgeID ];

    int nodeID = e->nodeID[nodexIndex];
    //
    // Fill your or modify own stuff
    //
    //
    // Set p and r as the position and ratius of the node, respectively.
    //
    p = vector3(0,0,0);
    r = 1.0;
}



//
// Return the number of adjacent nodes of the selected node
//
int GRAPH_SYSTEM::getNumOfAdjacentNodesOfSelectedNode( ) const
{
    int numAdjacentNodes = 0;
    if (!mSelectedNode) return numAdjacentNodes;
    //
    // Fill your or modify own stuff
    //
    //
    // Set numAdjacentNodes as the number of adjacent nodes
    // of the selected node
    //
    return numAdjacentNodes;

}

//
// nodeIndex is inside [0,numAdjacentNodes-1] 
//
void GRAPH_SYSTEM::getNodeInfoOfAdjacentNodeOfSelectedNode( 
    int nodexIndex
    , double &r
    , vector3 &p
    ) const
{
    if (!mSelectedNode) return;

    int edgeID = mSelectedNode->edgeID[nodexIndex];
    GRAPH_EDGE *e = &mEdgeArr_Pool[ edgeID ];

    int nodeID = e->nodeID[0];
    if (mSelectedNode->id == nodeID) {
        nodeID = e->nodeID[1];
    }
    //
    // Fill your or modify own stuff
    //
    //
    // Set p and r as the position and ratius of the node, respectively.
    //
}


//
// Clear the visit flags of all nodes.
// Set the depths of all nodes to -1.
// Set mResult_BFS_max_depth to -1 
// which indicates the bfs is not invoked yet.
//
// 
void GRAPH_SYSTEM::clearVisitFlagAndDepthOfAllNodes( )
{
    mResult_BFS_max_depth = -1;
    int num = getNumOfNodes( );
    for ( int i = 0; i < num; ++i ) {
        int nodeID = mActiveNodeArr[ i ];
        GRAPH_NODE *n = &mNodeArr_Pool[ nodeID ];
        n->visited = false;
        n->depth = -1;
    }
}

//
// Breadth first traveral method
// nodeID is the real node ID
//
// Purpose: Compute the depths of all the nodes which are reachable
// from node whose ID is nodeID
//
void GRAPH_SYSTEM::bfs( int nodeID)
{
    int depth = 0;
    queue<int, list<int> > q;
    GRAPH_NODE *node = &mNodeArr_Pool[ nodeID ];
    node->depth = depth;    
    node->visited = true;

    mResult_BFS_max_depth = depth;

    q.push(nodeID);

    while (!q.empty( )) {
        nodeID = q.front( );
        q.pop( );
        // breadth first traversal
        // set n as the node with nodeID
        // update the maximum depth, i.e., mResult_BFS_max_depth
        // for each adjacent node, n0, of the current node
        //     if n0 is visited, continue;
        //     otherwise set the depth correctly to n0
        //               n0.depth <- n.depth + 1
        //               add n0 to the queue q
        //     ...
        //     ...
        //
        // Fill your or modify own stuff
        //
    }
}



//
// breadth first traversal
//
// Clear the visit flags of all nodes
// If mSelectedNode is null, return
// Otherwise invoke bfs( mSelectedNode->id)
//
void GRAPH_SYSTEM::bfs( )
{
    cout << "clear_VisitFlag_DepthOfNodes" << endl;
    clearVisitFlagAndDepthOfAllNodes( );
    if ( !mSelectedNode ) return;
    cout << "Begin bfs" << endl;

    bfs( mSelectedNode->id);
    cout << "End bfs" << endl;

}


