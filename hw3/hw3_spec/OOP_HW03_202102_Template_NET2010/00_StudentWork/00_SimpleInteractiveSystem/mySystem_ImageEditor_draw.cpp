//
// Prof. Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/04/
//
#include <iostream>
#include "mySystem_ImageEditor.h"

namespace {
    void drawDisk_TriangleFan(double x, double y, double r, int in_numSamples = 120)
    {
        int numSamples = in_numSamples;
        glBegin(GL_TRIANGLE_FAN);
        glVertex3f( x, 0.0, y );
        for ( int i = 0; i < numSamples; ++i ) {
            double da = 1.0/(double) (numSamples-1)*3.141592654*2.0;

            double a = i*da;
            double x0 = x + r*cos(a);
            double y0 = y + r*sin(a);
            double x1 = x + r*cos(a+da);
            double y1 = y + r*sin(a+da);
            //glVertex3f( x, 0.0, y );


            glVertex3f( x0, 0.0, y0 );

            //glVertex3f( x1, 0.0, y1 );


        }
        glEnd( );
    }
};

void IMAGE_NODE::computeDrawPosition(
    int wImage,
    int hImage) {
    draw_x = (start_x+w/2)*sx;
    draw_y = hImage*sy-(start_y+h/2)*sy;
}

void IMAGE_NODE::drawDisk_TriangleFan( 
    int wImage,int hImage
    ) const
{
        glColor3f(r, g, b);
int numSamples = 12;
        numSamples += w*0.5;
        ::drawDisk_TriangleFan(
            draw_x,
            draw_y,
            radius, numSamples);
}

void IMAGE_SYSTEM::draw_Normal() const
{
    if (m_Image) {
        //std::cout << "IMAGE_SYSTEM::draw( )" << std::endl;
        m_Image->draw_VerticalFlip_XZ(0,0, 2, 2, 4);
    }
}

void IMAGE_SYSTEM::computeAverageColor(
    int start_x, int start_y, 
    int w, int h,
    float &r, float &g, float &b
    ) const 
{
    r = g = b = 0.0;
    if (w*h==0) return;

    for (int j = start_y; j < start_y + h; ++j) {
        for (int i = start_x; i < start_x + w; ++i ) {
            //compute the sum of colors of all pixels of the block
            //m_Image->getPixelColor(i, j, pr, pg, pb);
        }
    }
    //compute the average color (r,g,b)
}

//
//
// Draw the hierarchical structure rooted at node
// Check all children if the node is explored.
// Draw a node if it is not explored or at the lowest level of the hierarchy.
//
void IMAGE_SYSTEM::draw_Disks_Dynamic( const IMAGE_NODE *node) const{
    if (node==0) return;
    if (node->flg_explored) {
        //check all children
        return;
    }
    // draw the un-explored node
}


// call draw_Disks_Dynamic( root )
void IMAGE_SYSTEM::draw_Disks_Dynamic( ) const
{
    
}

void IMAGE_SYSTEM::draw( ) const
{
    //draw_Normal();
    //draw_Disks();
    draw_Disks_Dynamic();
}
