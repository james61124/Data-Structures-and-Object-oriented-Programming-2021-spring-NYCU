//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
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
class GALAXY_SYSTEM : public BASE_SYSTEM
{
protected:
    int mNumOfObjs;
    int mNumLargeObjs;
    vector<bool> mAlive;
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
    double mMaxV;
    double mG;              // gravitation constant
    double mSpaceSize;      //Space = [-mSpaceSize/2, mSpaceSize/2]x[-mSpaceSize/2, mSpaceSize/2]
    double mMinR, mMaxR;    // radius range of the objects
    double mTimeStep;       // Time step size
    //
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
};
#endif