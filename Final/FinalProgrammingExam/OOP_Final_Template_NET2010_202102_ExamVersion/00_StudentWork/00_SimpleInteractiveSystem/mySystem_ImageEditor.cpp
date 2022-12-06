//
// Prof. Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2019/04/09
//
#include <iostream>
#include "mySystem_ImageEditor.h"

using namespace std;

#define IMAGE_FILE_NAME "3d-flower-desktop.jpg"

#define IMAGE_MAX_HIERARCHY_DEPTH 8

#define W_MAX_IMAGE_BLOCKS 64   // number of blocks along the x-axis
#define H_MAX_IMAGE_BLOCKS 64   // number of blocks along the y-axis

IMAGE_SYSTEM::IMAGE_SYSTEM()
{
    mFlgDrawnInRainbow = false;

    //
    m_ImageHierarchy = 0;
    m_Depth = 0;
    m_Image = new ns_opengl::Image;
    m_Image->readFile(IMAGE_FILE_NAME);

    int wImage, hImage;
        m_Image->getInfo(wImage, hImage);

    int cur_depth = 0;
        int start_x = 0;
    int start_y = 0;

        int w = wImage;
        int h = hImage;
        float sx = 2; 
        float sy = 2;

        float radius = wImage/2.0*(sx+sy)*0.5;

    m_ImageHierarchy = new IMAGE_NODE(
        cur_depth, 
        start_x,
        start_y,
        w,
        h,
        sx,
        sy,
        radius
        ); 
    float r, g, b;
    computeAverageColor(start_x, start_y, w, h, r, g, b);

    m_ImageHierarchy->setColor(r,g,b);
    m_ImageHierarchy->computeDrawPosition(
        wImage, hImage
        );
    //
    m_CurrentNode_Replay = 0;
    m_Replay_Head = 0;
    m_Replay_Tail = 0;
    //
    m_Width_ImageBlocks = 0;
    m_Height_ImageBlocks = 0;
    m_ImageBlockHead = 0;
    m_ImageBlockTail = 0;
    m_ImageBlockPool = new IMAGE_NODE[W_MAX_IMAGE_BLOCKS*H_MAX_IMAGE_BLOCKS];
//
    m_CurrentData = m_ImageHierarchy;
}

void IMAGE_SYSTEM::reset(IMAGE_NODE *node)
{
    node->flg_explored = false;
    for (int i = 0; i < 4; ++i ) {
        if (node->children[i]) {
            reset(node->children[i]);
        }
    }
}

void IMAGE_SYSTEM::reset()
{
    m_CurrentNode_Replay = 0;
    m_Replay_Head = 0;
    m_Replay_Tail = 0;
    reset(m_ImageHierarchy);
}

void IMAGE_SYSTEM::replay_backward()
{
    if ( m_Replay_Head == 0) return;

    if (  m_CurrentNode_Replay == 0) {
        collapseImageNode(m_Replay_Head);
        m_CurrentNode_Replay = m_Replay_Tail;
    } else {
        m_CurrentNode_Replay->flg_explored = false;
        m_CurrentNode_Replay = m_CurrentNode_Replay->prev;
        if ( m_CurrentNode_Replay == 0) {
            m_CurrentNode_Replay = m_Replay_Head;
        }
    }
}

void IMAGE_SYSTEM::replay_forward()
{
    if ( m_Replay_Head == 0) return;

    if (  m_CurrentNode_Replay == 0) {
        collapseImageNode(m_Replay_Head);
        m_CurrentNode_Replay = m_Replay_Head;
    } else {
        m_CurrentNode_Replay->flg_explored = true;
        m_CurrentNode_Replay = m_CurrentNode_Replay->next;
        if (m_CurrentNode_Replay==0) {
            m_CurrentNode_Replay = m_Replay_Tail;
        }
    }
}

bool IMAGE_SYSTEM::handleKeyPressedEvent( unsigned char key )
{
    switch(key) {
      
    //case ' ':
    //       m_CurrentNode_Replay = 0;
    //    break;
    case '.':
    case '<':
        replay_forward();
        break;
    case ',':
    case '>': 
        replay_backward();
        break;
    case 'r':
        reset();
        m_CurrentData = m_ImageHierarchy;

        break;
    
    case 'k':
    case 'K':
        m_Depth--;
        if (m_Depth < 0 ) m_Depth = 0;
        break;
    case 'l':
    case 'L':
        m_Depth++;
        if (m_Depth > IMAGE_MAX_HIERARCHY_DEPTH ) m_Depth = IMAGE_MAX_HIERARCHY_DEPTH;
        break;
    case '1':
        exploreImageDownwards(0, 0, true);
        m_CurrentData = m_ImageHierarchy;
        break;
        case '2':
        exploreImageUpwards(0, 0, true);
        m_CurrentData = m_ImageHierarchy;

        break;
        case '3':
        exploreImageLeftToRight(0, 0, true);
        m_CurrentData = m_ImageHierarchy;

        break;
        case '4':
        exploreImageRightToLeft(0, 0, true);
        m_CurrentData = m_ImageHierarchy;

        break;
        case '5':
            createSnakeBlocks_BottomUp();
            m_CurrentData = m_ImageBlockHead;
            break;
            case '6':
            createSnakeBlocks_TopDown();
            m_CurrentData = m_ImageBlockHead;
            break;
            case '7':
                createSpiralBlocksIn_Clockwise();
            m_CurrentData = m_ImageBlockHead;
                break;
                case '8':
                createSpiralBlocksOut_CounterClockwise();
            m_CurrentData = m_ImageBlockHead;
                break;
        case ' ':
            mFlgDrawnInRainbow = !mFlgDrawnInRainbow;
            break;
    }

    return true;
}

void IMAGE_SYSTEM::createSpiralBlocksIn_Clockwise()
{
     m_Width_ImageBlocks = 32;
    m_Height_ImageBlocks = 32;

    int wImage, hImage;
    m_Image->getInfo(wImage, hImage);

    m_ImageBlockHead = 0;
    m_ImageBlockTail = 0;
    int minx = 0;
    int maxx = wImage;
    int miny = 0;
    int maxy = hImage;
    int start_x = 0;
    int start_y = 0;
    int x = 0;
    int y = 0;
    int wBlock = wImage/ m_Width_ImageBlocks;
    int hBlock = hImage/ m_Height_ImageBlocks;

    int cur_depth = 0;
    int sx = 2, sy = 2;
    int blockIndex = 0;
    int dir = 0;
    while (true) {
        IMAGE_NODE *node = &m_ImageBlockPool[blockIndex++];
        node->resetChildren();
        
        float radius = wBlock;
        node->set( 
            cur_depth, 
        x,
        y,
        wBlock,
        hBlock,
        sx,
        sy,
        radius);
        //
        if (m_ImageBlockHead) {
            m_ImageBlockTail->flg_explored = true;
            m_ImageBlockTail->children[0] = node;
           m_ImageBlockTail =  node;
        } else {
            m_ImageBlockHead = m_ImageBlockTail = node;
        }
        //
        node->computeDrawPosition( wImage, hImage );
        computeNodeColor( node);

           switch(dir) {
           case 0:
               x += wBlock;
               if (x>=maxx) {
                   x -= wBlock;
                   y += hBlock;
                   miny += hBlock;
                   dir = 1;
               }

               break;
           case 1:
               y += hBlock;
               if (y>=maxy) {
                   y -= hBlock;
                   x -= wBlock;
                   maxx -= wBlock;
                   dir = 2;
               }
               break;
           case 2:
               x -= wBlock;
               if (x<minx) {
                   x += wBlock;
                   y -= hBlock;
                   maxy -= hBlock;
                   dir = 3;
               }
               break;
           case 3:
               y -= hBlock;
               if (y<miny) {
                   y += hBlock;
                   x += wBlock;
                   minx += wBlock;
                   dir = 0;
               }
               break;
           }
    
        //cout << "blockIndex:" << blockIndex << "\t" << x << "\t" << y << endl;
        if (minx >= maxx || miny>=maxy) break;
    }
}

void IMAGE_SYSTEM::createSpiralBlocksOut_CounterClockwise()
{
    createSpiralBlocksIn_Clockwise();
    vector<IMAGE_NODE*> ptrArr;
    for ( IMAGE_NODE* p = m_ImageBlockHead; p; p = p->children[0]) {
        p->flg_explored = false;
        ptrArr.push_back(p);
    }
    int n = ptrArr.size();
    for (int i = 0; i < n;++i) {
        ptrArr[i]->children[0] = 0;
    }
    for (int i = 0; i < n-1;++i) {
        int j = n-i-1;
        IMAGE_NODE* p = ptrArr[j];
        p->flg_explored = true;
        p->children[0] = ptrArr[j-1];

    }
    m_ImageBlockHead = ptrArr[n-1];
    m_ImageBlockTail = ptrArr[0];
}

void IMAGE_SYSTEM::createSnakeBlocks_BottomUp( ) {
    m_Width_ImageBlocks = 32;
    m_Height_ImageBlocks = 32;

    int wImage, hImage;
    m_Image->getInfo(wImage, hImage);

    m_ImageBlockHead = 0;
    m_ImageBlockTail = 0;
    int start_x = 0;
    int start_y = 0;
    int x = 0;
    int y = 0;
    int wBlock = wImage/ m_Width_ImageBlocks;
    int hBlock = hImage/ m_Height_ImageBlocks;

    int cur_depth = 0;
    int sx = 2, sy = 2;
    int blockIndex = 0;
    bool flg_dir = true;
    while (true) {
        IMAGE_NODE *node = &m_ImageBlockPool[blockIndex++];
        node->resetChildren();
        
        float radius = wBlock;
        node->set( 
            cur_depth, 
        x,
        y,
        wBlock,
        hBlock,
        sx,
        sy,
        radius);
        //
        if (m_ImageBlockHead) {
            m_ImageBlockTail->flg_explored = true;
            m_ImageBlockTail->children[0] = node;
           m_ImageBlockTail =  node;
        } else {
            m_ImageBlockHead = m_ImageBlockTail = node;
        }
        //
        node->computeDrawPosition( wImage, hImage );
        computeNodeColor( node);
        if (flg_dir) {
            x += wBlock;
            if ( x>= wImage) {
                y += hBlock;
                flg_dir = false;
                x -= wBlock;
            }
        } else {
            x -= wBlock;
            if ( x< 0 ) {
                y += hBlock;
                flg_dir = true;
                x += wBlock;
            }
        }
        //cout << "blockIndex:" << blockIndex << "\t" << x << "\t" << y << endl;
        if (y>= hImage)break;
    }
}

void IMAGE_SYSTEM::createSnakeBlocks_TopDown( ) {
    createSnakeBlocks_BottomUp( );
    vector<IMAGE_NODE*> ptrArr;
    for ( IMAGE_NODE* p = m_ImageBlockHead; p; p = p->children[0]) {
        p->flg_explored = false;
        ptrArr.push_back(p);
    }
    int n = ptrArr.size();
    for (int i = 0; i < n;++i) {
        ptrArr[i]->children[0] = 0;
    }
    for (int i = 0; i < n-1;++i) {
        int j = n-i-1;
        IMAGE_NODE* p = ptrArr[j];
        p->flg_explored = true;
        p->children[0] = ptrArr[j-1];

    }
    m_ImageBlockHead = ptrArr[n-1];
    m_ImageBlockTail = ptrArr[0];

}

void IMAGE_SYSTEM::computeNodeColor(IMAGE_NODE *node)
{
    float r, g, b;
    computeAverageColor(
        node->start_x,
        node->start_y,
        node->w,
        node->h,
        r,
        g,
        b);
    node->setColor(r,g,b);
}

void IMAGE_SYSTEM::exploreImageNode(IMAGE_NODE *node, double x, double y)
{

    if (node->flg_explored) {
        for (int i =0; i <4; ++i) {
            exploreImageNode(node->children[i], x, y);
        }
    } else {
        if (node->w/2 ==0 || node->h/2 == 0) return;
        float dx = x - node->draw_x;
        float dy = y - node->draw_y;
        float d2 = dx*dx + dy*dy;
        float r2 = node->radius*node->radius;
        //if (d2 > r2) return;
        if ( dx < -node->w) return;
        if ( dx >  node->w) return;
        if ( dy < -node->h) return;
        if ( dy >  node->h) return;

        //
        if (m_Replay_Head) {
            m_Replay_Tail->next = node;
            node->prev = m_Replay_Tail;
            m_Replay_Tail = node;
        } else {
            m_Replay_Head = m_Replay_Tail = node;
        }
        //
        node->flg_explored = true;
        if (node->children[0]) return;

        int wImage, hImage;
        m_Image->getInfo(wImage, hImage);
        IMAGE_NODE *children[4];
        float radius = node->w/2.0;
        children[0] = new IMAGE_NODE(
            node->cur_depth+1, 
            node->start_x, 
            node->start_y,
            node->w/2, node->h/2, 
            node->sx, node->sy,
            radius
            );
        
        
        children[1] = new IMAGE_NODE(
            node->cur_depth+1, 
            node->start_x+node->w/2, 
            node->start_y,
            node->w/2, node->h/2, 
            node->sx, node->sy,
            radius
            );
        children[2] = new IMAGE_NODE(
            node->cur_depth+1, 
            node->start_x, 
            node->start_y+node->h/2,
            node->w/2, node->h/2, 
            node->sx, node->sy,
            radius
            );
        children[3] = new IMAGE_NODE(
            node->cur_depth+1, 
            node->start_x +node->w/2, 
            node->start_y+node->h/2,
            node->w/2, node->h/2, 
            node->sx, node->sy,
            radius
            );
        for (int i =0; i <4; ++i) {
            computeNodeColor(children[i]);
            children[i]->computeDrawPosition(
            wImage, hImage
            );
            node->children[i] = children[i];
        }
    }
}

bool IMAGE_SYSTEM::handlePassiveMouseEvent( double x, double y )
{
    //std::cout << "IMAGE_SYSTEM Mouse:" << x << "\t" << y << std::endl;
    
    exploreImageNode(m_ImageHierarchy,x, y);
        m_CurrentData = m_ImageHierarchy;

    return true;
}

void IMAGE_SYSTEM::collapseImageNode(IMAGE_NODE *node)
{
    if (node ==0) return;
    node->flg_explored = false;
    for (int i =0; i <4; ++i) {
            if (node->children[i]) {
                collapseImageNode(node->children[i]);
            }
    }

}

void IMAGE_SYSTEM::collapseImageNode(IMAGE_NODE *parent_node, IMAGE_NODE *node, double x, double y)
{

    if (node->flg_explored) {
        bool flg_collapsed = false;
        for (int i =0; i <4; ++i) {
            if (node->children[i] == 0) {
                flg_collapsed = true;
                break;
            } else {
                collapseImageNode(node, node->children[i], x, y);
        
            }
        }
        std::cout << "flg_collapsed:" << flg_collapsed << std::endl;

        if ( flg_collapsed ) {
              collapseImageNode(parent_node);
        }
    } else {
        if (parent_node) {
        float dx = x - parent_node->draw_x;
        float dy = y - parent_node->draw_y;
        float d2 = dx*dx + dy*dy;
        float r2 = parent_node->radius*parent_node->radius;
        if (d2 > r2) return;
        collapseImageNode(parent_node);
        }
    }
}

bool IMAGE_SYSTEM::exploreImageDownwards( 
    IMAGE_NODE *node, double x, double y, bool flg_auto, int code )
{
    if (node->flg_explored) {
        int ccode = 1;
        for (int i =0; i <4; ++i, ccode = ccode << 1) {
            if (!(ccode&code)) continue;
            exploreImageDownwards(node->children[i], x, y, flg_auto, code);
        }
    } else {
        if (node->w/2 ==0 || node->h/2 == 0) return true;
        float dx = x - node->draw_x;
        float dy = y - node->draw_y;
        float d2 = dx*dx + dy*dy;
        float r2 = node->radius*node->radius;
        if (!flg_auto && (d2 > r2)) return true;
        //
        if (m_Replay_Head) {
            m_Replay_Tail->next = node;
            node->prev = m_Replay_Tail;
            m_Replay_Tail = node;
        } else {
            m_Replay_Head = m_Replay_Tail = node;
        }
        //
        node->flg_explored = true;
        if (node->children[0]) return true;

        int wImage, hImage;
        m_Image->getInfo(wImage, hImage);
        IMAGE_NODE *children[4];
        float radius = node->w/2.0;
        children[0] = new IMAGE_NODE(
            node->cur_depth+1, 
            node->start_x, 
            node->start_y,
            node->w/2, node->h/2, 
            node->sx, node->sy,
            radius
            );
        
        
        children[1] = new IMAGE_NODE(
            node->cur_depth+1, 
            node->start_x+node->w/2, 
            node->start_y,
            node->w/2, node->h/2, 
            node->sx, node->sy,
            radius
            );
        children[2] = new IMAGE_NODE(
            node->cur_depth+1, 
            node->start_x, 
            node->start_y+node->h/2,
            node->w/2, node->h/2, 
            node->sx, node->sy,
            radius
            );
        children[3] = new IMAGE_NODE(
            node->cur_depth+1, 
            node->start_x +node->w/2, 
            node->start_y+node->h/2,
            node->w/2, node->h/2, 
            node->sx, node->sy,
            radius
            );
        for (int i =0; i <4; ++i) {
            computeNodeColor(children[i]);
            children[i]->computeDrawPosition(
            wImage, hImage
            );
            node->children[i] = children[i];
        }
    }

    return true;
}

bool IMAGE_SYSTEM::exploreImageDownwards( double x, double y, bool flg_auto )
{

    exploreImageDownwards(m_ImageHierarchy, x, y, flg_auto, 0x0c);
    return true;
}

bool IMAGE_SYSTEM::exploreImageUpwards( double x, double y, bool flg_auto )
{

    exploreImageDownwards(m_ImageHierarchy, x, y, flg_auto, 0x03);
    return true;
}

bool IMAGE_SYSTEM::exploreImageLeftToRight( double x, double y, bool flg_auto )
{
    exploreImageDownwards(m_ImageHierarchy, x, y, flg_auto, 0x0a);
    return true;
}

    bool IMAGE_SYSTEM::exploreImageRightToLeft( double x, double y, bool flg_auto )
    {
        exploreImageDownwards(m_ImageHierarchy, x, y, flg_auto, 0x05);
    return true;
    }

bool IMAGE_SYSTEM::handleMotionMouseEvent( double x, double y )
{
    std::cout << "IMAGE_SYSTEM::handleMotionMouseEvent:" << x << "\t" << y << std::endl;
    collapseImageNode(0, m_ImageHierarchy,x, y);
    return true;
}

int IMAGE_SYSTEM::computeNumOfNodes(IMAGE_NODE *node, int &numNodes) const
{
    if (node ==0) return numNodes;
    ++numNodes;
    if (node->flg_explored) {
    for (int i =0; i <4; ++i) {
        if (node->children[i]) computeNumOfNodes(node->children[i], numNodes);
    }
    }
    return numNodes;
}

int IMAGE_SYSTEM::computeNumOfNodes() const {
    int numNodes = 0;
    //m_CurrentData = m_ImageHierarchy;
    computeNumOfNodes(m_CurrentData, numNodes);
    return numNodes;
}
