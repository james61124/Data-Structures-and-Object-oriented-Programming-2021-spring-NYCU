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

#include <iostream>
#include "mySystem_GraphSystem.h"
#include <time.h>

using namespace std;

int Param::GRAPH_MAX_NUM_NODES = 10000;
int Param::GRAPH_MAX_NUM_EDGES = 10000;
double Param::GRAPH_NODE_RADIUS = 1;//++

GRAPH_SYSTEM::GRAPH_SYSTEM( )
{
    mFlgAutoNodeDeletion = false;
    initMemorySpace(); //要先初始化
    //
    // Implement your own stuff
    //
	createDefaultGraph();

	
}

void GRAPH_SYSTEM::initMemorySpace() {
    mMaxNumNodes = Param::GRAPH_MAX_NUM_NODES;
    mMaxNumEdges = Param::GRAPH_MAX_NUM_EDGES;

    mPool_Nodes = new GRAPH_NODE[mMaxNumNodes];
    mPool_Edges = new GRAPH_EDGE[mMaxNumEdges];
    
    for (int i = 0; i < mMaxNumNodes; ++i) {
        mPool_Nodes[i].id = i;
    }
    for (int i = 0; i < mMaxNumEdges; ++i) {
        mPool_Edges[i].id = i;
    }

    mFreeNodeArr = new int[mMaxNumNodes];
    mFreeEdgeArr = new int[mMaxNumEdges];
    mCurNumFreeNodes = 0;
    mCurNumFreeEdges = 0;

    mActiveNodeArr = new int[mMaxNumNodes];
    mActiveEdgeArr = new int[mMaxNumEdges];
    mCurNumActiveNodes = 0;
    mCurNumActiveEdges = 0;
    reset();
}

void GRAPH_SYSTEM::reset( )
{
    stopAutoNodeDeletion();
    mPassiveSelectedNode = 0;
    mSelectedNode = 0;
    //
    // Implement your own stuff
    //
	for (int i = 0; i < mMaxNumNodes; ++i) {
        mFreeNodeArr[i] = i;
    }
    for (int i = 0; i < mMaxNumEdges; ++i) {
        mFreeEdgeArr[i] = i;
    }
    
    mCurNumFreeNodes = mMaxNumNodes; //++
    mCurNumFreeEdges = mMaxNumEdges;

    mCurNumActiveNodes = 0;
    mCurNumActiveEdges = 0;
}

void GRAPH_SYSTEM::createDefaultGraph( )
{
    reset( );
    //
    // Implement your own stuff
    //
	int v0 = addNode(0.0, 0.0, 0.0, Param::GRAPH_NODE_RADIUS);
    int v1 = addNode(10.0, 0.0, 0.0, Param::GRAPH_NODE_RADIUS);
    int v2 = addNode(0, 0.0, 10.0, Param::GRAPH_NODE_RADIUS);

    addEdge(v0, v1);
    addEdge(v1, v2);
}

void GRAPH_SYSTEM::createRandomGraph_DoubleCircles(int n)
{
    reset( );

    float dx = 5.0;
    float dz = 5.0;
    float r = 15; // radius
    float d = 10; // layer distance
    float offset_x = 15.;//圓心座標
    float offset_z = 15.;
    //
    // Implement your own stuff
    //
	vector<vector<int> > v;//用二維陣列存node的ID 第0橫排是內圈 第1橫排是外圈
    double theta = 2 * 3.14159 / n;
    double pi = 3.14159;
    v.resize(2);
    for (int i = 0; i < 2; i++) v[i].resize(n);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < n; j++) v[i][j] = addNode(offset_x + r * cos(theta * j), 0.0, offset_z + r * sin(theta * j), Param::GRAPH_NODE_RADIUS); //極座標 x=a+rcos(k(2拍/n))
			r += d; //外圈圓
    }
    
    for (int i = 0; i < n; i++) {
        if (n >= 9) addEdge(v[1][(i + ((rand() % (n / 4)) - n / 8 + n)) % n], v[0][i]);
        else if( n < 9)
        {
            int ran = ((i - 1) + (rand() % 3)) % n;
            if (ran < 0 ) ran = n -  ran;
            if (ran >= n) ran = ran - n;
				addEdge(v[1][ran], v[0][i]);
        }
    }
}

void GRAPH_SYSTEM::createNet_Circular( int n, int num_layers )
{
    reset( );

    float dx = 5.0;
    float dz = 5.0;
    float r = 5; // radius
    float d = 5; // layer distance 
    float offset_x = 15.;//圓心座標
    float offset_z = 15.;
    //
    // Implement your own stuff
    //
	vector<vector<int> > v; //第n橫排表第n內圈
    double theta = 2*3.14159 / n;
    v.resize(num_layers+1);

    for (int i = 0; i <= num_layers; i++) v[i].resize(n);//num_layers表有幾圈圓
    for (int i = 0; i <= num_layers; i++){
        for (int j = 0; j < n; j++) v[i][j] = addNode(offset_x + r*cos(theta*j), 0.0, offset_z + r*sin(theta*j), Param::GRAPH_NODE_RADIUS);
			r += d;
    }
    for (int i = 0; i < num_layers; i++){
        for (int j = 0; j < n; j++){
            addEdge(v[i][j], v[i][(j + 1) % n]);//內外圈連起來
            addEdge(v[i][j], v[i + 1][j]); //同一圈連起來
        }
    }
}
void GRAPH_SYSTEM::createNet_Square( int n, int num_layers )
{
	//n:中間有n排不見
	//num_layer:邊長是num_layer
    reset( );

    float dx = 5.0;
    float dz = 5.0;
    float r = 5; // radius
    float d = 5; // layer distance 
    float offset_x = 5.;
    float offset_z = 5.;
    //
    // Implement your own stuff
    //
	vector<vector<int> > v;
    v.resize(num_layers);
    for (int i = 0; i < num_layers; i++) v[i].resize(num_layers);
    //node
    for (int i = 0; i < (num_layers - n) / 2 + n; i++){   //左上
        for (int j = 0; j < (num_layers - n) / 2 + n; j++){
            if (j < (num_layers - n) / 2 || i < (num_layers - n) / 2){
                v[i][j] = addNode(offset_x + d*i , 0.0, offset_z + d*j, Param::GRAPH_NODE_RADIUS);
            }
        }
    }
    for (int i = (num_layers - n) / 2 + n; i < num_layers; i++){//下
        for (int j = 0; j < num_layers; j++){
                v[i][j] = addNode(offset_x + d * i, 0.0, offset_z + d * j, Param::GRAPH_NODE_RADIUS);
        }
    }
    for (int i = 0; i < (num_layers - n) / 2 + n; i++){//右
        for (int j = (num_layers - n) / 2 + n; j < num_layers; j++){
            v[i][j] = addNode(offset_x + d * i, 0.0, offset_z + d * j, Param::GRAPH_NODE_RADIUS);
        }
    }

    //edge
    for (int i = 0; i < (num_layers - n) / 2 + n; i++)
    {
        for (int j = 0; j < (num_layers - n) / 2 + n; j++)
        {
            if (j < (num_layers - n) / 2 -1 || i < (num_layers - n) / 2 -1)
            {   
                addEdge(v[i][j], v[i][j + 1]);
                addEdge(v[i + 1][j], v[i][j]);
                if (i == (num_layers - n) / 2 - 2)
                {
                    addEdge(v[i+1][j],v[i+1][j+1]);
                }
                if (j == (num_layers - n) / 2 - 2)
                {
                    addEdge(v[i + 1][j+1], v[i][j + 1]);
                }
            }
        }
    }
    for (int i = (num_layers - n) / 2 + n; i < num_layers-1; i++)
    {
        for (int j = 0; j < num_layers-1; j++)
        {
            addEdge(v[i][j], v[i][j + 1]);
            addEdge(v[i + 1][j], v[i][j]);
            if (i == num_layers  - 2)
            {
                addEdge(v[i + 1][j], v[i + 1][j + 1]);
            }
            if (j == num_layers - 2)
            {
                addEdge(v[i + 1][j + 1], v[i][j + 1]);
            }
        }
    }
    for (int i = 0; i < (num_layers - n) / 2 + n; i++)
    {
        for (int j = (num_layers - n) / 2 + n; j < num_layers-1; j++)
        {
            addEdge(v[i][j], v[i][j + 1]);
            addEdge(v[i + 1][j], v[i][j]);
            if (i == (num_layers - n) / 2 + n -1)
            {
                addEdge(v[i + 1][j], v[i + 1][j + 1]);
            }
            if (j == num_layers - 2)
            {
                addEdge(v[i + 1][j + 1], v[i][j + 1]);

            }
        }
    }
}

void GRAPH_SYSTEM::createNet_RadialCircular( int n ) {

    reset( );

    float offset_x = 15.0;
    float offset_z = 15.0;

    float r = 15; // radius
    //
    // Implement your own stuff
    //    
	vector<int> v;
    double theta = 2 * 3.14159 / n;
    v.resize(n + 1);
    for (int j = 0; j < n; j++){ //一圈的node
        v[j] = addNode(offset_x + r * cos(theta * j), 0.0, offset_z + r * sin(theta * j), Param::GRAPH_NODE_RADIUS);
    }
    v[n] = addNode(offset_x,0.0,offset_z, Param::GRAPH_NODE_RADIUS);//圓心的node
    for (int j = 0; j < n; j++){ //圓心跟外圈的連線
        addEdge(v[j], v[n]);
    }
}

GRAPH_NODE *GRAPH_SYSTEM::getFreeNode() 
{
    GRAPH_NODE* node = 0;

    if (mCurNumFreeNodes <= 0) return node;

    --mCurNumFreeNodes;
    int nodeIndex = mFreeNodeArr[mCurNumFreeNodes];
    node = &mPool_Nodes[nodeIndex];

    node->dynamicID = mCurNumActiveNodes;
    mActiveNodeArr[mCurNumActiveNodes] = nodeIndex;
    ++mCurNumActiveNodes;

    node->edgeID.clear();

    return node;
}

// return node id
int GRAPH_SYSTEM::addNode( float x, float y, float z, float r )
{
    //
    // Implement your own stuff
    //  
    GRAPH_NODE* node = getFreeNode();
    if (!node) return -1; //if node為0(就return)
    node->p.x = x;  //存position,radius進去 把edgeID空出來
    node->p.y = y;
    node->p.z = z;
    node->r = r;
    node->edgeID.clear();

    return node->id;
}

GRAPH_EDGE* GRAPH_SYSTEM::getFreeEdge()
{
    GRAPH_EDGE* edge = 0;
  
    if (mCurNumFreeEdges <= 0) return edge;
    --mCurNumFreeEdges;
    int edgeIndex = mFreeEdgeArr[mCurNumFreeEdges];
    edge = &mPool_Edges[edgeIndex];

    edge->dynamicID = mCurNumActiveEdges;
    mActiveEdgeArr[mCurNumActiveEdges] = edgeIndex;
    ++mCurNumActiveEdges;

    edge->nodeID[0] = -1;
    edge->nodeID[1] = -1;

    return edge;
}

// return edge id
int GRAPH_SYSTEM::addEdge( int nodeID_0, int nodeID_1 )
{
    //
    // Implement your own stuff
    //  
    GRAPH_EDGE* edge = getFreeEdge();
    if (!edge) return -1;
    edge->nodeID[0] = nodeID_0; //存要連接的兩個node的ID
    edge->nodeID[1] = nodeID_1;

    mPool_Nodes[nodeID_0].edgeID.push_back(edge->id);
    mPool_Nodes[nodeID_1].edgeID.push_back(edge->id);

    return edge->id;
}

void GRAPH_SYSTEM::askForInput( )
{
    //
    // Implement your own stuff
    // 
	cout << "GRAPH_SYSTEM" << endl;
    cout << "Key usage:" << endl;
    cout << "1: create a default graph" << endl;
    cout << "2: create a net circular" << endl;
    cout << "3: create a net square" << endl;
    cout << "4: create a net radial circular" << endl;
    cout << "5: create double circles. Create 10 randomly generated edges attached at a random node" << endl;
    cout << "Delete: delete a node and all the edges attached at it" << endl;
    cout << "Spacebar: unselect the selected node" << endl;
    cout << " " << endl;
    cout << "Use the mouse to select nodes and add edges" << endl;
    cout << "Click the left button to select/unselect or create an edge" << endl;
    cout << " " << endl;
    cout << "A selected node is highlighted as red." << endl;
}

GRAPH_NODE *GRAPH_SYSTEM::findNearestNode( double x, double z, double &cur_distance2 ) const
{
    GRAPH_NODE *n = 0;
    //
    // Implement your own stuff
    // 
    if (!mCurNumActiveNodes) return NULL;

    double nx = mPool_Nodes[mActiveNodeArr[0]].p.x;//存node的座標(初始化是用index=0的node)
    double nz = mPool_Nodes[mActiveNodeArr[0]].p.z;
    double nd = (nx-x)*(nx-x)+(nz-z)*(nz-z);//與目標node的距離平方
    int npo = 0;//存index

    for (int i = 1; i < mCurNumActiveNodes; i++)
    {
        nx = mPool_Nodes[mActiveNodeArr[i]].p.x;
        nz = mPool_Nodes[mActiveNodeArr[i]].p.z;
        if ((nx - x) * (nx - x) + (nz - z) * (nz - z) < nd)//若距離比現在存的距離要小 就存起來
        {
            nd = (nx - x) * (nx - x) + (nz - z) * (nz - z);
            npo = i;
        }
    }
    cur_distance2 = nd;
    return &mPool_Nodes[mActiveNodeArr[npo]];//回傳最近的那個node
}

//
// compute mSelectedNode
//
void GRAPH_SYSTEM::clickAt(double x, double z) //點擊時存在passive
{
    //
    // Implement your own stuff
    // 
    // mSelectedNode = n;
	if (!isSelectedNode()) //若selectednode沒有東西
    {
        mSelectedNode = mPassiveSelectedNode;
    }
    else if(mSelectedNode == mPassiveSelectedNode)//若seleced和passive是一樣的,selected就要被取消
    {
        mSelectedNode = NULL;
    }
    else //selected和passive不一樣,連起來
    {
        addEdge(mSelectedNode->id, mPassiveSelectedNode->id);
        mSelectedNode = NULL;
    }
}

void GRAPH_SYSTEM::deleteNode( int nodeID ) {
    //
    // Implement your own stuff
    // 
	int n = mPool_Nodes[nodeID].edgeID.size();
    for (int i = 0; i < n; i++)
    {
        deleteEdge(mPool_Nodes[nodeID].edgeID[0]);
    }
    int dedyid = mPool_Nodes[nodeID].dynamicID;
    mFreeNodeArr[mCurNumFreeNodes] = nodeID;
    mPool_Nodes[nodeID].dynamicID = mCurNumFreeNodes;
    mCurNumFreeNodes++;
    mActiveNodeArr[dedyid] = mActiveNodeArr[mCurNumActiveNodes - 1];
    mPool_Nodes[mActiveNodeArr[dedyid]].dynamicID = dedyid;
    mCurNumActiveNodes--;
}

void GRAPH_SYSTEM::deleteEdge(int edgeID) {
    
    for (int i = 0; i < mCurNumActiveEdges; i++){
        if (mActiveEdgeArr[i] == edgeID){ //找到edge在active陣列裡的位子
            mFreeEdgeArr[mCurNumFreeEdges] = edgeID;
            mPool_Edges[edgeID].dynamicID = mCurNumFreeEdges;
            mCurNumFreeEdges++;
            mActiveEdgeArr[i] = mActiveEdgeArr[mCurNumActiveEdges - 1];
            mPool_Edges[mActiveEdgeArr[i]].dynamicID = i;
            mCurNumActiveEdges--;
            for (int j = 0; j < mPool_Nodes[mPool_Edges[edgeID].nodeID[0]].edgeID.size(); j++)
            {
                if (mPool_Nodes[mPool_Edges[edgeID].nodeID[0]].edgeID[j] == edgeID)
                {
                    mPool_Nodes[mPool_Edges[edgeID].nodeID[0]].edgeID.erase(mPool_Nodes[mPool_Edges[edgeID].nodeID[0]].edgeID.begin() + j);
                    break;
                }
            }
            for (int j = 0; j < mPool_Nodes[mPool_Edges[edgeID].nodeID[1]].edgeID.size(); j++)
            {
                if (mPool_Nodes[mPool_Edges[edgeID].nodeID[1]].edgeID[j] == edgeID)
                {
                    mPool_Nodes[mPool_Edges[edgeID].nodeID[1]].edgeID.erase(mPool_Nodes[mPool_Edges[edgeID].nodeID[1]].edgeID.begin() + j);
                    break;
                }
            }
            break;
        }
    }
}

void GRAPH_SYSTEM::deleteSelectedNode(  ) {
    //
    // Implement your own stuff
    // 
	if (isSelectedNode())
    {
        deleteNode(mSelectedNode->id);
        mSelectedNode = NULL;
        mPassiveSelectedNode = NULL;
    }
}

bool GRAPH_SYSTEM::isSelectedNode( ) const//表有無select到node
{
    //
    // mSelectedNode != 0;
    //
    // Implement your own stuff
    // 
    if (mSelectedNode != NULL) return true;
    return false;
}

void GRAPH_SYSTEM::getInfoOfSelectedPoint( double &r, vector3 &p ) const
{
     r = mSelectedNode->r;
     p = mSelectedNode->p;
    //
    // Implement your own stuff
    // 

}



int num = 24;
void GRAPH_SYSTEM::handleKeyPressedEvent( unsigned char key )
{
    
    switch( key ) {
    case 127: // delete
        mFlgAutoNodeDeletion = false;
        deleteSelectedNode( );
        break;
    case '1':
        mFlgAutoNodeDeletion = false;
        createDefaultGraph( );
        mSelectedNode = 0;
        break;
    case '2':
        mFlgAutoNodeDeletion = false;
        createNet_Circular(12, 3);
        mSelectedNode = 0;

        break;
    case '3':
        mFlgAutoNodeDeletion = false;
        createNet_Square(3, 11); // you can modify this
        mSelectedNode = 0;

        break;
    case '4':
        mFlgAutoNodeDeletion = false;
        createNet_RadialCircular(24);
        mSelectedNode = 0;

        break;
    case '5':
        mFlgAutoNodeDeletion = false;
        num = 24;
        createRandomGraph_DoubleCircles(num);
        mSelectedNode = 0;

        break;

    case ' ':
        mFlgAutoNodeDeletion = false;
        mSelectedNode = 0;
        break;
    case 'd':
        mFlgAutoNodeDeletion = !mFlgAutoNodeDeletion;
        break;
    case '<':
        mFlgAutoNodeDeletion = false;
        if (num-1 < 3) return;
        num--;
        createRandomGraph_DoubleCircles(num);
        break;
    case '>':
        mFlgAutoNodeDeletion = false;
        if (num+1 > 36) return;
        num++;
        createRandomGraph_DoubleCircles(num);
        break;
    }
}


void GRAPH_SYSTEM::handlePassiveMouseEvent( double x, double z )
{
    double cur_d2;
    GRAPH_NODE *n = findNearestNode( x, z, cur_d2 );
    if ( n == 0 ) return;
    if ( cur_d2 > n->r*n->r ) {
        mPassiveSelectedNode = 0;
        return;
    }
    mPassiveSelectedNode = n;
}

//
// get the number of nodes
//
int GRAPH_SYSTEM::getNumOfNodes( ) const
{
    //
    // Implement your own stuff
    // 

    return mCurNumActiveNodes;
}

void GRAPH_SYSTEM::getNodeInfo( int nodeIndex, double &r, vector3 &p ) const
{
    //
    // Implement your own stuff
    // 
	int nodeID = mActiveNodeArr[nodeIndex];

    const GRAPH_NODE* node = &mPool_Nodes[nodeID];

    r = node->r;
    p = node->p;
}

//
// return the number of edges
//
int GRAPH_SYSTEM::getNumOfEdges( ) const
{
    //
    // Implement your own stuff
    // 
    return mCurNumActiveEdges;
}

//
// an edge should have two nodes: index 0 and index 1
// return the position of node with nodeIndex
//
vector3 GRAPH_SYSTEM::getNodePositionOfEdge( int edgeIndex, int nodeIndex ) const
{
    vector3 p;
    //
    // Implement your own stuff
    // 
    int id = mActiveEdgeArr[edgeIndex];
    const GRAPH_EDGE *edge = &mPool_Edges[id];

    int vertexID = edge->nodeID[nodeIndex];
    p = mPool_Nodes[vertexID].p;

    return p;
}

void GRAPH_SYSTEM::stopAutoNodeDeletion()
{
    mFlgAutoNodeDeletion = false;
}

//
// For every frame, update( ) function is called.
// 
//
void GRAPH_SYSTEM::update( )
{
    if (!mFlgAutoNodeDeletion) {
     
        return;
    }
    mSelectedNode = 0;
    mPassiveSelectedNode = 0;

    Sleep(250);
    //
    //
    // Implement your own stuff
    // 
	if (mCurNumActiveNodes == 0)
    {
        stopAutoNodeDeletion();
    }
    else
    {
        deleteNode(mActiveNodeArr[mCurNumActiveNodes - 1]);
    }

}












