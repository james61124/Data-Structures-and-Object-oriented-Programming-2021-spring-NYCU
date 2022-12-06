//********************************************
// Student Name			:邱弘竣
// Student ID			:109550136
// Student Email Address:james61124@gmail.com
//********************************************
//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/04/
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

class Param {
public: 
    static int GRAPH_MAX_NUM_NODES;
    static int GRAPH_MAX_NUM_EDGES;
	static double GRAPH_NODE_RADIUS;//++
};



class GRAPH_SYSTEM : public BASE_SYSTEM {

protected:
    void drawNodes_Indirect( ) const;
    void drawEdges_Indirect( ) const;
    void drawSelectedNode_Indirect( ) const;
    //
    GRAPH_NODE *GRAPH_SYSTEM::findNearestNode( double x, double z, double &cur_distance2 ) const;
    void deleteNode( int nodeID );
    void deleteSelectedNode(  );
    //
    void createDefaultGraph( );
    void createNet_Circular( int n, int num_layers );
    void createNet_Square( int n, int num_layers );
    void createNet_RadialCircular( int n );
    void createRandomGraph_DoubleCircles(int n);
    //
    // Implement your own stuff
    //
public:
    GRAPH_SYSTEM( );
    void update( );
    void stopAutoNodeDeletion();
    void reset( );
    void askForInput( );
    void clickAt(double x, double z);
    void handleKeyPressedEvent( unsigned char key );
    void handlePassiveMouseEvent( double x, double y );
    void draw( ) const;
    
    int addNode( float x, float y, float z, float r = 1.0 );
    int addEdge( int nodeID_0, int nodeID_1 );
    bool isSelectedNode( ) const;
    void getInfoOfSelectedPoint( double &r, vector3 &p ) const;
    //
    int getNumOfEdges( ) const;
    vector3 getNodePositionOfEdge( int edgeIndex, int nodeIndex ) const;

    int getNumOfNodes( ) const;
    void getNodeInfo( int nodeIndex, double &r, vector3 &p ) const;
protected:
    //
    // Implement your own stuff
    //
    //
    GRAPH_NODE *mSelectedNode;
    GRAPH_NODE *mPassiveSelectedNode;
    //
    bool mFlgAutoNodeDeletion;

	int mMaxNumNodes;
	int mMaxNumEdges;
	int mCurNumFreeNodes;//還可以用的node剩多少(因為有max)
	int mCurNumFreeEdges;
	int mCurNumActiveNodes;//node的ID
	int mCurNumActiveEdges;
	int *mFreeNodeArr;//存還沒被人用的node的ID(index和ID同)
    int *mFreeEdgeArr;
	int *mActiveNodeArr;//存有用到的node的index
	int *mActiveEdgeArr;
	GRAPH_NODE *mPool_Nodes;//node串起來的陣列
	GRAPH_EDGE *mPool_Edges;
	GRAPH_NODE* getFreeNode();
	GRAPH_EDGE* getFreeEdge();
	void initMemorySpace();
	void deleteEdge(int edgeID);
};

#endif