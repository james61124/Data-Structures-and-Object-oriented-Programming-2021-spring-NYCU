//
// Prof. Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2019/04/09
//

#ifndef __MY_IMAGE_SYSTEM_H_
#define __MY_IMAGE_SYSTEM_H_
#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
#include <vector>
#include "base_class.h"
#include "../../imageReader/imageReader.h"

class IMAGE_NODE {
public:
    IMAGE_NODE(
        ) {
    flg_explored = false;
        children[0] = children[1] = children[2] = children[3] = 0;
        prev = next = 0;
    }
    IMAGE_NODE( 
        int cur_depth,
        int start_x, int start_y, 
        int w, int h,
        float sx, float sy,
        float radius
        ) {
            set( cur_depth,
         start_x,  start_y, 
         w,  h,
         sx,  sy,
         radius);
    }
    void set(int cur_depth,
        int start_x, int start_y, 
        int w, int h,
        float sx, float sy,
        float radius) 
    {
        prev = next = 0;
        flg_explored = false;
        this->cur_depth = cur_depth;
        this->start_x = start_x;
        this->start_y = start_y;
        this->w = w;
        this->h = h;
        this->sx = sx;
        this->sy = sy;
        this->radius = radius;
        children[0] = children[1] = children[2] = children[3] = 0;
    }

    void setColor(float r, float g, float b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }
    void resetChildren() {
        children[0] = children[1] = children[2] = children[3] = 0;
    }

    void computeDrawPosition(
    int wImage,
    int hImage);
    void drawDisk_TriangleFan( 
    int wImage,int hImage 
    ) const;

    void drawRectangle( 
        int wImage,int hImage 
    ) const;
    void drawRectangle( 
        int wImage,int hImage, float fr, float fg, float fb
    ) const;

public:
    bool flg_explored;
    float r, g, b;
    float radius;
    int cur_depth;
        int start_x; int start_y; 
        int w; 
        int h;
        float sx; float sy;
    IMAGE_NODE *children[4];
    float draw_x, draw_y;
    IMAGE_NODE *next;
    IMAGE_NODE *prev;
};

class IMAGE_SYSTEM : public BASE_SYSTEM {
public:
    virtual void askForInput( ) { }
    virtual void update( ) { }
    virtual void reset( );
    virtual void draw( ) const;
    virtual void draw_in_rainbow( ) const;
    virtual void draw_Rectangles_Dynamic_InRainbow() const;
    virtual void draw_Rectangles_Dynamic_InRainbow(
    const IMAGE_NODE *node, 
    int &count, 
    int numNodes,
    bool flg_draw_all
    ) const;
    virtual void copy( const BASE_SYSTEM *m ) { }
    virtual void clickAt(double x, double y ) { }
    virtual bool handleKeyPressedEvent( unsigned char key );
    virtual bool handleSpecialKeyPressedEvent( unsigned char key ) { return true; }
    virtual bool handlePassiveMouseEvent( double x, double y );
    virtual bool handleMotionMouseEvent( double x, double y );
protected:
    int computeNumOfNodes( ) const;
    int computeNumOfNodes(IMAGE_NODE *node, int &numNodes) const;

    void replay_forward();
    void replay_backward();

    void reset(IMAGE_NODE *node);
    void computeNodeColor(IMAGE_NODE *node);
    void collapseImageNode(IMAGE_NODE *node);
    void collapseImageNode(IMAGE_NODE *parent_node, IMAGE_NODE *node, double x, double y);
    void exploreImageNode(IMAGE_NODE *node, double x, double y);
    //
    bool exploreImageDownwards( IMAGE_NODE *node, double x, double y, bool flg_auto, int code );
    bool exploreImageDownwards( double x, double y, bool flg_auto );
    bool exploreImageUpwards( double x, double y, bool flg_auto );
    bool exploreImageLeftToRight( double x, double y, bool flg_auto );
    bool exploreImageRightToLeft( double x, double y, bool flg_auto );

    //
    void computeAverageColor(
    int start_x, int start_y, 
    int w, int h,
    float &r, float &g, float &b
    ) const;
    void draw_Normal() const;
    void draw_Disks_Dynamic( const IMAGE_NODE *node) const;

    void draw_Disks_Dynamic( ) const;

    void draw_Rectangles_Dynamic( const IMAGE_NODE *node, bool flg_draw_all) const;
    void draw_Rectangles_Dynamic( ) const;

    void draw_Disks(
        int cur_depth, 
        int max_depth,
        int start_x, int start_y, 
        int w, int h,
        float sx, float sy
        ) const;
    void draw_Disks(int depth) const;
    void draw_Disks() const;
    void drawDisk_TriangleFan( const IMAGE_NODE *node ) const;

    void createSnakeBlocks_BottomUp( );
    void createSnakeBlocks_TopDown( );
    void createSpiralBlocksIn_Clockwise();
    void createSpiralBlocksOut_CounterClockwise();
public:
    IMAGE_SYSTEM();
protected:
    ns_opengl::Image *m_Image;
    int m_Depth;

    IMAGE_NODE *m_CurrentData;

    IMAGE_NODE *m_ImageHierarchy;

   

    IMAGE_NODE *m_CurrentNode_Replay;
    IMAGE_NODE *m_Replay_Head;
    IMAGE_NODE *m_Replay_Tail;
    //
    bool mFlgDrawnInRainbow;

    int m_Width_ImageBlocks;
    int m_Height_ImageBlocks;
     IMAGE_NODE *m_ImageBlockPool;
     IMAGE_NODE *m_ImageBlockHead;
     IMAGE_NODE *m_ImageBlockTail;
};

#endif