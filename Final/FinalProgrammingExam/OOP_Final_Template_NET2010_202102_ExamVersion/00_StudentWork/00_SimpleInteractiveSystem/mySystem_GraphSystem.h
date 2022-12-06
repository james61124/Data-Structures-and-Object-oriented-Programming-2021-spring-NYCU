//********************************************
// Student Name			:
// Student ID			:
// Student Email Address:
//********************************************
//
// Prof. Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/06/17
//
//
// Add your own functions if necessary
//
#ifndef __MY_GRAPH_SYSTEM_H_
#define __MY_GRAPH_SYSTEM_H_
#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
#include <vector>
#include "base_class.h"
#include "graph_basics.h"

using std::vector;
using std::string;

#define GRAPH_MAX_NUM_NODES 10000
#define GRAPH_MAX_NUM_EDGES 10000

//
enum GraphOption {
    GR_None = 0,
    GR_Neighbor,
    GR_BFS,
    GR_End                   // dummy
};

class GRAPH_SYSTEM : public BASE_SYSTEM {

protected:
    void drawNodes( ) const;
    void drawEdges( ) const;
    void drawSelectedNode( ) const;
    //
    void drawNodes_Indirect( ) const;
    void drawEdges_Indirect( ) const;
    void drawSelectedNode_Indirect( ) const;
    //
    void draw_AttachedEdgesOfSelectedNode( ) const;
    void draw_AdjacentNodesOfSelectedNode( ) const;
    void drawResult_BFS( ) const;
    void drawResult_DFS( ) const;
    //
    void initMemoryPool( );
    GRAPH_NODE *getFreeNode( );
    GRAPH_EDGE *getFreeEdge( );
    GRAPH_NODE *findNearestNode( double x, double y, double &cur_distance2 ) const;

    //
    void createNet_Square( int n );
    void createNet_RadialCircular( int n, int num_layers );
    //

public:
    GRAPH_SYSTEM( );

    void update( );
    bool handleKeyPressedEvent( unsigned char key );
    string getOptionName( ) const;

    void reset( );
    void askForInput( );
    void clickAt(double x, double z);
    bool handlePassiveMouseEvent( double x, double y );
    void draw( ) const;
    void createDefaultGraph( );
    int addNode( float x, float y, float z, float r = 1.0 );
    int addEdge( int nodeID_0, int nodeID_1 );
    bool isSelectedNode( ) const;
    void getInfoOfSelectedPoint( double &r, vector3 &p ) const;
    //
    int getNumOfEdges( ) const;
    vector3 getNodePositionOfEdge( int edgeIndex, int nodeIndex ) const;
    int getNumOfNodes( ) const;
    void getNodeInfo( int nodeIndex, double &r, vector3 &p ) const;
    void getNodeInfoOfAttachedEdgeOfSelectedNode( 
        int edgeIndex
        , int nodexIndex
        , double &r
        , vector3 &p
        ) const;
    void getNodeInfoOfAdjacentNodeOfSelectedNode( 
        int nodexIndex
        , double &r
        , vector3 &p
        ) const;
    int getNumOfAttachedEdgesOfSelectedNode( ) const;
    int getNumOfAdjacentNodesOfSelectedNode( ) const;


    void clearVisitFlagAndDepthOfAllNodes( );
    void bfs( int nodeID);
    void bfs( );

protected:
    GRAPH_NODE *mNodeArr_Pool; 
    GRAPH_EDGE *mEdgeArr_Pool;
    //
    int *mActiveNodeArr;
    int mCurNumOfActiveNodes;
    int *mActiveEdgeArr;
    int mCurNumOfActiveEdges;
    //
    int *mFreeNodeArr;
    int *mFreeEdgeArr;
    int mCurNumOfFreeNodes;
    int mCurNumOfFreeEdges;
    //
    GRAPH_NODE *mSelectedNode;
    GRAPH_NODE *mPassiveSelectedNode;
    //
    // Use mOptionIndex to determine mOption
    int mOptionIndex;       
    GraphOption mOption;
    //
    int mResult_BFS_max_depth;
};

#endif