//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/03/29
//
/*
This system simulates the motion of n-body in a two-dimensional space.
Steps:
1. compute the forces exerting on the objects
2. compute the velocities of the objects
3. update the positions of the objects
*/
#ifndef __MY_GALAXY_SYSTEM_H_
#define __MY_GALAXY_SYSTEM_H_
#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
#include <vector>
#include "base_class.h"
using std::vector;

#define DFT_MAXNUM_POINTS_TAIL 100

class COORD_2D {
public:
    COORD_2D( ) {
        this->x = 0;
        this->y = 0;
    }
    COORD_2D(double x, double y) {
        this->x = x;
        this->y = y;
    }
    double x, y;
};

//
//Each tail has a maximum number of sample points.
//
class TAIL_PLANET {
private:
    int maxNumPoints;
public:
    vector<COORD_2D> points;
public:

    TAIL_PLANET( ) {
        this->maxNumPoints = DFT_MAXNUM_POINTS_TAIL;
        points.resize(maxNumPoints);
        reset(0, 0);
    }
    
    TAIL_PLANET( int maxNumPoints ) {
        this->maxNumPoints = maxNumPoints;
        points.resize(maxNumPoints);
        reset(0, 0);

    }

    TAIL_PLANET( double x, double y ) {
        this->maxNumPoints = DFT_MAXNUM_POINTS_TAIL;
        points.resize(maxNumPoints);
        reset(x, y);
    }
    
    void reset( double x, double y ) {
        for (int i =0; i <points.size();++i) {
            points[i].x = x;
            points[i].y = y;
        }
    }

    void add_to_back(double x, double y) {
        
    }

    void add_to_front(double x, double y) {
        //
    }
};

class GALAXY_SYSTEM : public BASE_SYSTEM
{
protected:
    int mNumFrames;
    int mNumOfObjs;     // number of all the objects (including large objects)
    int mNumLargeObjs;  // number of large objects
    vector<bool> mAlive; // alive flag
    vector<double> mX; // x-coordinate
    vector<double> mY; // y-coordinate
    vector<double> mR; // radius
    vector<double> mMass; // mass
    //
    vector<double> mVx; // object velocity, x-component
    vector<double> mVy; // object velocity, y-component
    //
    vector<double> mFx; // force exerted on object, x-component
    vector<double> mFy; // force exerted on object, y-component
    //
    double mMaxV;       // (absolute) maximum speed component
    double mG;              // gravitation constant
    double mSpaceSize;      // Space = [-mSpaceSize/2, mSpaceSize/2]x[-mSpaceSize/2, mSpaceSize/2]
    double mMinR, mMaxR;    // radius range of the objects
    double mTimeStep;       // Time step size
    //
    vector<TAIL_PLANET> mTails;

    ///////////////////////////////////////////////
    ///////////////////////////////////////////////
    void mergeObjects( );
    void generateObjects( );
public:
    GALAXY_SYSTEM( );
    void askForInput( );
    int getNumOfObjs( ) const;
    bool handleKeyPressedEvent( int key );
    bool getObjInfo( int objInbdex, double &x, double &y, double &r ) const;
    void update( );
    void reset( );
    double getMaxRadius( ) const { return mMaxR; }

    int getTail_NumSamplePoints( int planet_index ) const;
    COORD_2D getTail_SamplePointCoords( 
        int planet_index, 
        int sample_point_index ) const;
};
#endif