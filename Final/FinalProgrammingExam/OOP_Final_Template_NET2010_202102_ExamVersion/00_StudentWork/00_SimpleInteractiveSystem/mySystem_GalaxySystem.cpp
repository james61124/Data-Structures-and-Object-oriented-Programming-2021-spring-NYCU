//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
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
    mMinR = 0.5;
    mMaxR = 3.0;
    mSpaceSize = 300.0;
    mG = 5.0;
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

*/
void GALAXY_SYSTEM::generateObjects( )
{
    mX.clear( );
    mY.clear( );
    mR.clear( );
    mMass.clear( );
    double halfSpaceSize = mSpaceSize/2.0;
    for ( int i = 0; i < mNumOfObjs; ++i ) {

        double r = getRandDouble( mMinR, mMaxR );
        mR.push_back( r );
        mMass.push_back( r*r );
        double x = getRandDouble( -halfSpaceSize, halfSpaceSize );
        double y = getRandDouble( -halfSpaceSize, halfSpaceSize );
        mX.push_back( x );
        mY.push_back( y );
    }

    mVx.resize( mNumOfObjs );
    mVy.resize( mNumOfObjs );
    mAlive.resize( mNumOfObjs );
    double mv = 100;
    for ( int i = 0; i < mNumOfObjs; ++i ) {
        mVx[i] = getRandDouble(-mv, mv);
        mVy[i] = getRandDouble(-mv, mv);
        mAlive[i] = true;
    }

    for ( int i = 0; i < mNumLargeObjs; ++i ) {
        int objIndex = i;
        mR[objIndex] = mMaxR*2.0;
        mMass[objIndex] = mMaxR*mMaxR*1000;
        mVx[i] = 0.0;
        mVy[i] = 0.0;

    }
    if ( mNumLargeObjs == 1 ) {
        mX[0] = 0.0;
        mY[0] = 0.0;
    }

    mFx.resize( mNumOfObjs );
    mFy.resize( mNumOfObjs );

}

/*
Handle the key events.
*/
bool GALAXY_SYSTEM::handleKeyPressedEvent( int key )
{
    bool flgHandled = false;
    switch( key ) {
    case '1':
        mNumLargeObjs = 1;
        flgHandled = true;
        break;
    case '2':
        mNumLargeObjs = 2;
        flgHandled = true;

        break;
    case '3':
        mNumLargeObjs = 3;
        flgHandled = true;
        break;
    }
    if ( flgHandled ) reset( );
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
    cout << "Key usage:" << endl;
    cout << "1: one large object" << endl;
    cout << "2: two large object" << endl;
    cout << "3: three large object" << endl;
    cout << "r: reset" << endl;
}

/*
Return the number of objects
*/
int GALAXY_SYSTEM::getNumOfObjs( ) const
{
    return mNumOfObjs;
}

/*
Get the object information based on the object index.
(x,y) = position
r = radius
Return the alive flag.
*/
bool GALAXY_SYSTEM::getObjInfo( int objIndex, double &x, double &y, double &r ) const
{
    x = mX[objIndex];
    y = mY[objIndex];
    r = mR[objIndex];
    return mAlive[objIndex];
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
   for ( int i = 0; i < mNumOfObjs; ++i ) {
        double mi = mMass[i];
        if ( !mAlive[i] ) continue;
        double ri = mR[i];
        for ( int j = i+1; j < mNumOfObjs; ++j ) {
            if ( !mAlive[j] ) continue;
            double mj = mMass[j];
            double rj = mR[j];

            double dx = mX[i] - mX[j];
            double dy = mY[i] - mY[j];
            double d2 = dx*dx + dy*dy;

            double d = sqrt(d2);
            if ( ri + rj > d) {
               

                if ( ri > rj ) {
                    mAlive[j] = false;
                   
                 mVx[i] = mVx[i]*mMass[i]+mVx[j]*mMass[j];
                    mVy[i] = mVy[i]*mMass[i]+mVy[j]*mMass[j];


                    mMass[i] += mMass[j];
                    mVx[i] = mVx[i]/mMass[i];
                    mVy[i] = mVy[i]/mMass[i];

                    //
                    

                } else {
                    mVx[j] = mVx[i]*mMass[i]+mVx[j]*mMass[j];
                    mVy[j] = mVy[i]*mMass[i]+mVy[j]*mMass[j];

                    mAlive[i] = false;
                    mMass[j] += mMass[i];
                    //
                    mVx[j] = mVx[j]/mMass[j];
                    mVy[j] = mVy[j]/mMass[j];
                    break;


                }
            }
           
        }
    }

}

/*
Update the position of the objects
Steps:
1. compute the forces exerting on each object
2. compute the velocity of each object
3. compute the position of each object

Constraints:
The component of a velocity must be inside [-mMaxV, mMaxV].

The component of a position must be inside [-halfSpaceSize, halfSpaceSize].
Warp the position if it's outside of the range.
Consider a position (x,y).
If x > halfSpaceSize, set x = -halfSpaceSize;


*/
void GALAXY_SYSTEM::update( ) 
{
    mergeObjects( );
    for ( int i = 0; i < mNumOfObjs; ++i ) {
        mFx[i] = 0.0;
        mFy[i] = 0.0;

    }
    for ( int i = 0; i < mNumOfObjs; ++i ) {
        double mi = mMass[i];
        if ( !mAlive[i] ) continue;
        double ri = mR[i];
        for ( int j = i+1; j < mNumOfObjs; ++j ) {
            if ( !mAlive[j] ) continue;
            double mj = mMass[j];
            double rj = mR[j];

            double dx = mX[i] - mX[j];
            double dy = mY[i] - mY[j];
            double d2 = dx*dx + dy*dy;

            double d = sqrt(d2);
           
            double nx = dx/d;
            double ny = dy/d;

            double mij = mi*mj;
            if ( d2 != 0.0 ) {
                mFx[i] -= mij*mG*nx/d2;
                mFy[i] -= mij*mG*ny/d2;

                mFx[j] += mij*mG*nx/d2;
                mFy[j] += mij*mG*ny/d2;
            } else {
            }

        }
    }
    for ( int i = 0; i < mNumOfObjs; ++i ) {
        double m = mMass[i];

        mVx[i] = mVx[i] + mFx[i]/m*mTimeStep;
        mVy[i] = mVy[i] + mFy[i]/m*mTimeStep;

        if ( mVx[i] > mMaxV ) mVx[i] = mMaxV;
        if ( mVx[i] < -mMaxV ) mVx[i] = -mMaxV;

        if ( mVy[i] > mMaxV ) mVy[i] = mMaxV;
        if ( mVy[i] < -mMaxV ) mVy[i] = -mMaxV;

    }

    double halfSpaceSize = mSpaceSize/2.0;
    for ( int i = 0; i < mNumOfObjs; ++i ) {
        mX[i] = mX[i] + mVx[i]*mTimeStep;
        mY[i] = mY[i] + mVy[i]*mTimeStep;

        if ( mX[i] < -halfSpaceSize ) {
            mX[i]= halfSpaceSize;
        }
        if ( mX[i] > halfSpaceSize ) {
            mX[i]= -halfSpaceSize;
        }

        if ( mY[i] < -halfSpaceSize ) {
            mY[i]= halfSpaceSize;
        }
        if ( mY[i] > halfSpaceSize ) {
            mY[i]=  -halfSpaceSize;
        }
    }
}