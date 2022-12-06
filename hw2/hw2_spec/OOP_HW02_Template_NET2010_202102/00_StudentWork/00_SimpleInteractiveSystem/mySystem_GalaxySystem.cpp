//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/03/29
//
#include "mySystem_GalaxySystem.h"
#include <iostream>

using namespace std;

namespace {
    double getRandDouble( double L, double U ) {
        return L + (U-L)*rand( )/(double) RAND_MAX;
    }
};

GALAXY_SYSTEM::GALAXY_SYSTEM( )
{
    mTimeStep = 0.0025; 
    mMaxV = 100.0;
    mNumOfObjs = 100;
    mNumLargeObjs = 2;
    mMinR = 0.5;            //minimum radius of objects
    mMaxR = 3.0;            //maximum radius of objects
    mSpaceSize = 300.0;
    mG = 5.0;               //gravitational constant
    generateObjects( );
}

/*
Generate randomly the positions,  
velocities and radii of the objects.

Also, if the objects are large, 
set their masses to be a large number.

The mass of an  object depends on the object's radius.

The position of an object is inside 
[-halfSpaceSize, halfSpaceSize]x[-halfSpaceSize, halfSpaceSize].

The velocity of an object is inside
[-100.0, 100]x[-100.0, 100].

Initialize the alive flag of each object.
the alive flag indicates whether the object is alive or not.
If the object is not alive, ignore it in all the calculations.

If there's only one large object,
set its position to the origin
and set its velocity to zero.

Use 
TAIL_PLANET tail(x,y);
mTails.push_back( tail ); // push a tail to mTails.
to initialize the tail of an object. 
It sets all the points of the tail to the same point, i.e., (x,y).

Each object has one tail.

*/
void GALAXY_SYSTEM::generateObjects( )
{
    mNumFrames = 0;
    mTails.clear();

    //Fill in here
    /* You can remove the following lines.
    mX.resize( mNumOfObjs );
    mY.resize( mNumOfObjs );
    mR.resize( mNumOfObjs );
    mMass.resize( mNumOfObjs );
    mVx.resize( mNumOfObjs );
    mVy.resize( mNumOfObjs );
    mFx.resize( mNumOfObjs );
    mFy.resize( mNumOfObjs );
    */

}

/*
Handle the key events.
*/
bool GALAXY_SYSTEM::handleKeyPressedEvent( int key )
{
    bool flgHandled = false;
    return flgHandled;
}

/*
Generate the objects.
Call generateObjects( ).
*/
void GALAXY_SYSTEM::reset( )
{
    generateObjects( );
}

/*
Show the system title.
Show the key usage.
*/
void GALAXY_SYSTEM::askForInput( )
{
    cout << "GALAXY_SYSTEM::askForInput" << endl;
}

/*
Return the number of objects
return mNumOfObjs
*/
int GALAXY_SYSTEM::getNumOfObjs( ) const
{
    return 5;
}

/*
Get the object information based on the object index.
(x,y) = position
r = radius
Return the alive flag.
*/
bool GALAXY_SYSTEM::getObjInfo( int objIndex, double &x, double &y, double &r ) const
{
    x = 1;
    y = 1;
    r = 10;
    return true;
}

/*
Merge the objects if they overlap with each other.
Modify the velocities of the objects after merging
based on the conservation of momentum.
Set the alive flags of the objects accordingly.

Pseudo-code

For each pair of the objects
  if they do not overlap continue
  If they overlap
    do
      turn off the alive flag of the object with smaller radius
      compute the new velocity of the larger object
*/
void GALAXY_SYSTEM::mergeObjects( )
{

}

/*
Update the position of the objects
Steps:
1. compute the forces exerting on each object
2. compute the velocity of each object
3. compute the position of each object

Constraints:
The component of a velocity must be inside [-mMaxV, mMaxV].

*/
void GALAXY_SYSTEM::update( ) 
{
    int skipFrames = 10;
    /////////////////////////////////////////////////////
    mergeObjects( ); // merge objects first if they overlap with each other
    
    //
    //Fill in here
    //compute forces exerting on objects
    //compute velocities of objects
    //compute positions of objects
    //
    //add a point to the tail of each object
    //each tail has a maximum number of sample points
    //

    /////////////////////////////////////////////////////
    ++mNumFrames;
}

//
// return the number of sample points of the tail
// of an object with index planet_index
int GALAXY_SYSTEM::getTail_NumSamplePoints( int planet_index ) const 
{ 
    //mTails
    return 0;
}

//
// return the coordinates of the sample point of an object
//
COORD_2D GALAXY_SYSTEM::getTail_SamplePointCoords( 
    int planet_index,               
    int sample_point_index ) const 
{ 
    //mTails
    return COORD_2D(0,0);
}