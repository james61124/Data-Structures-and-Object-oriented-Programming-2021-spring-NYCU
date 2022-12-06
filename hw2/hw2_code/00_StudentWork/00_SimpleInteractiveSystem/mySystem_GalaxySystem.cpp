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
#include <stdlib.h>
#include <time.h>
#include <cmath>

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

Alarso, if the objects are large, 
set their masses to be a lge number.

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
    mX.clear();
    mY.clear();
    mR.clear();
    mMass.clear();
    mTails.clear();
    mVx.clear();
    mVy.clear();
    mAlive.clear();
    //Fill in here
    for (int i = 0; i < mNumOfObjs; i++)
    {
        mX.push_back(getRandDouble(-150.0, 150.0));
        mY.push_back(getRandDouble(-150.0, 150.0));
        mR.push_back(getRandDouble(mMinR, mMaxR));
        mMass.push_back(mR[i]* mR[i]);

        TAIL_PLANET tail(mX[i], mY[i]);
        mTails.push_back(tail);
        mVx.push_back(getRandDouble(-mMaxV, mMaxV));
        mVy.push_back(getRandDouble(-mMaxV, mMaxV));
        mAlive.push_back(true);
    }
    for (int i = 0; i < mNumLargeObjs; i++)
    {
        mR[i] = mMaxR * 2.0;
        mMass[i] = mMaxR * mMaxR * 1000;
        mVx[i] = 0.0;
        mVy[i] = 0.0;
    }
    if (mNumLargeObjs == 1)
    {
        mX[0] = 0.0;
        mY[0] = 0.0;
    }
    mFx.resize(mNumOfObjs);
    mFy.resize(mNumOfObjs);
}

/*
Handle the key events.
*/
bool GALAXY_SYSTEM::handleKeyPressedEvent( int key )
{
   bool flgHandled = false;
    switch (key)
    {
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
    if (flgHandled)
    {
        reset();
    }
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
    cout << "1: one large object" << endl; // generate the objects. Only one large object
    cout << "2: two large object" << endl; // generate the objects. Only two large objects
    cout << "3: three large object" << endl; // generate the objects. Only three large objects
    cout << "r: reset" << endl; 		// reset the positions of the objects


}

/*
Return the number of objects
return mNumOfObjs
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
    x = this->mX[objIndex];
    y = this->mY[objIndex];
    r = this->mR[objIndex];
	if(mAlive[objIndex]==true){
		return true;
	}
	else{
		return false;
	}
    
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
        if ( !mAlive[i] ) continue;
        for ( int j = i+1; j < mNumOfObjs; ++j ) {
            if ( !mAlive[j] ) continue;
			if(sqrt((mX[i]-mX[j])*(mX[i]-mX[j])+(mY[i]-mY[j])*(mY[i]-mY[j]))<(mR[i]+mR[j])){
				int big=0,little=0;
				if(mR[i]>mR[j]){
					big=i;
					little=j;
				}
				else{
					big=j;
					little=i;
				}
				mAlive[little]=false;
				int mivi_mjvj_X = mVx[big]*mMass[big]+mVx[little]*mMass[little];
				int mivi_mjvj_Y = mVy[big]*mMass[big]+mVy[little]*mMass[little];
       			mMass[big] += mMass[little]; // total mass
         		mVx[big] = mivi_mjvj_X / mMass[big];
				mVy[big] = mivi_mjvj_Y / mMass[big];

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
	//compute forces exerting on objects
    for (int i = 0; i < mNumOfObjs; i++)
    {
        mFx[i] = 0.0;
        mFy[i] = 0.0;
    }

	for ( int i = 0; i < mNumOfObjs; ++i ) {
        if ( !mAlive[i] ) continue;
        for ( int j = i+1; j < mNumOfObjs; ++j ) {
            if ( !mAlive[j] ) continue;
			double d=sqrt((mX[i]-mX[j])*(mX[i]-mX[j])+(mY[i]-mY[j])*(mY[i]-mY[j]));
			double nx = (mX[i]-mX[j])/d; //normalize along the x-axis
			double ny = (mY[i]-mY[j])/d;
			double mij = mMass[i]*mMass[j];
			mFx[i] -= mij*mG*nx/(d*d); 	//notice the negative sign	
			mFy[i] -= mij*mG*ny/(d*d);	//notice the negative sign
			mFx[j] += mij*mG*nx/(d*d);	//notice the positive sign
			mFy[j] += mij*mG*ny/(d*d);  //notice the positive sign


		}
	 }


    for (int i = 0; i < mNumOfObjs; i++)
    {
		if ( !mAlive[i] ) continue;
        mVx[i] += mFx[i] / mMass[i] * mTimeStep;
        mVy[i] += mFy[i] / mMass[i] * mTimeStep;
        if (mVx[i] > mMaxV){
			mVx[i] = mMaxV;
		}
        if (mVx[i] < -mMaxV){
			mVx[i] = -mMaxV;;
		}
        if (mVy[i] > mMaxV){
			mVy[i] = mMaxV;
		}
        if (mVy[i] < -mMaxV){
			 mVy[i] = -mMaxV;
		}
    }

    for (int i = 0; i < mNumOfObjs; i++)
    {
		if ( !mAlive[i] ) continue;
        mX[i] += mVx[i] * mTimeStep;
        mY[i] += mVy[i] * mTimeStep;
        if (skipFrames == 0 || mNumFrames % skipFrames == 0){
			mTails[i].add_to_front(mX[i], mY[i]);
		}
        
    }
    /////////////////////////////////////////////////////
    ++mNumFrames;
}

//
// return the number of sample points of the tail
// of an object with index planet_index
int GALAXY_SYSTEM::getTail_NumSamplePoints( int planet_index ) const 
{ 
    //mTails
    return mTails[planet_index].points.size();
}

//
// return the coordinates of the sample point of an object
//
COORD_2D GALAXY_SYSTEM::getTail_SamplePointCoords( 
    int planet_index,               
    int sample_point_index ) const 
{ 
    //mTails
   // return COORD_2D(0,0);
	 return mTails[planet_index].points[sample_point_index];

}