//********************************************
// Student Name			:
// Student ID			:
// Student Email Address:
//********************************************
//
// Prof. Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2019/04/09
//
#include "mySystem_2048.h"
#include <iostream>

using namespace std;

MY_2048::MY_2048( )
{
    mNX = 4;
    mNZ = 4;
    reset( );

    mPositionX = 0;
    mPositionZ = 0;
    mFlgFocus = true;
}

MY_2048::MY_2048( int nx, int nz )
{
    mNX = nx;
    mNZ = nz;
    reset( );

    mPositionX = 0;
    mPositionZ = 0;
    mFlgFocus = true;
}

void MY_2048::setDimension(int nx, int nz)
{
    mFlgFocus = true;
    ///////////////////////////////////
    mNX = nx;
    mNZ = nz;
    reset( );

    //mPositionX = 0;
    //mPositionZ = 0;
    
}


void MY_2048::setFocus( bool flg )
{
    mFlgFocus = flg;
}

void MY_2048::setPosition( int x, int z )
{
    mPositionX = x;
    mPositionZ = z;
}

MY_2048 &MY_2048::operator=(const MY_2048 &m)
{
    this->copy(&m);
    return (*this);
}

//
//copy the data of the object pointed by m to this object.
//
void MY_2048::copy( const BASE_SYSTEM *m )
{
    for ( int j = 0; j < mNZ; ++j ) {
        for ( int i = 0; i < mNX; ++i ) {
            mBoard[ j ][ i ] = ((MY_2048*)m)->mBoard[ j ][ i ];
        }
    }
}

//
//reset the game board
//
void MY_2048::reset( )
{
    mEvent = 0;
    ///////////////////////////////////////
    for ( int j = 0; j < mNZ; ++j ) {
        for ( int i = 0; i < mNX; ++i ) {
            mBoard[ j ][ i ] = 0;
        }
    }
    mNumFreeCells = mNX * mNZ;
    
}

//
// show messages and ask for input (if any)
//
void MY_2048::askForInput( )
{
    cout << "MY_2048" << endl;
    cout << "Key usage:" << endl;
    cout << "1: generate randomly the numbers 2 and 4 for all the cells" << endl;
    cout << "2: generate randomly the numbers 2, 4 and 8 for all the cells" << endl;
    cout << "3: generate randomly the numbers for all the cells" << endl;
    cout << "r: clear all the cells" << endl;
    cout << " " << endl;
    cout << "UP, DOWN, LEFT, RIGHT: move the numbers to the respective side" << endl;
}

//
// randomly generate a new number
//
void MY_2048::generateNumber( )
{
    if (  mNumFreeCells == 0 ) return;
    int index = (rand( )%mNumFreeCells);
    int r = rand()%2;
    int v = 2;
    switch( r ) {
    case 0:
        break;
    case 1:
        v = 4;
        break;
    }
    bool flgDone = false;
    for ( int j = 0; j < mNZ; ++j ) {
        for ( int i = 0; i < mNX; ++i ) {
            int z = mNZ - j - 1;
            if ( mBoard[ z ][ i ] == 0 ) {
                flgDone = true;

                mBoard[ z ][ i ] = v;

                break;
            }
        }
        if ( flgDone ) break;
    }
}

int MY_2048::findItem( int startIndexZ, int i ) const {
    int z = startIndexZ;
    while ( z < mNZ ) {
        if ( mBoard[z][i] == 0) {
            ++z;
            continue;
        }
        break;
    }
    return z;
}

void MY_2048::moveItem( int zIndex, int targetIndex, int i )
{
    if ( targetIndex == zIndex ) return;
    mBoard[targetIndex][i] = mBoard[zIndex][i];
    mBoard[zIndex][i] = 0;
}

void MY_2048::moveDown_Column( int i ) {
    int z0 = 0;
    int base = 0;
    int flgMerge = false;
    int startZIndex = 0;
    //

    while ( true ) {
        z0 = findItem( startZIndex, i );
        if ( z0 >= mNZ ) break; // no item found
        moveItem( z0, base, i );

        int z1 = findItem( z0 + 1, i );
        //
        //cout << "i:" << i << "\t" << z0 << "\t" << z1 << endl;
        //cout << "startZIndex:" << startZIndex << endl;
        //cout << "base:" << base << endl;

        if ( z1 >= mNZ ) {
            // no item found
            break;
        }

        //can merge?
        if ( mBoard[z1][i] == mBoard[base][i] ) {
            mBoard[base][i] *= 2;
            mBoard[z1][i] = 0;
            ++base;
            startZIndex = z1 + 1;

        } else {
            ++base;
            startZIndex = z1;
        }
    }

}

void MY_2048::copy( int src[][MAX_2048_NX], int tgt[][MAX_2048_NX])
{
    for (int j = 0; j < mNZ; ++j ) {
        for (int i = 0; i < mNX; ++i ) {
            tgt[j][i] = src[j][i];
        }
    }
}

void MY_2048::rotate_CounterClockwise( )
{
    for (int j = 0; j < mNZ; ++j ) {
        for (int i = 0; i < mNX; ++i ) {
            int jx;
            int ix;
            ix = mNZ - j - 1;
            jx = i;
            mTmpBoard[jx][ix] = mBoard[j][i];
        }
    }
    copy( mTmpBoard, mBoard );
}

void MY_2048::rotate_Clockwise( )
{
    for (int j = 0; j < mNZ; ++j ) {
        for (int i = 0; i < mNX; ++i ) {
            int jx;
            int ix;
            ix = j;
            jx = mNX - i - 1;
            mTmpBoard[jx][ix] = mBoard[j][i];
        }
    }
    copy( mTmpBoard, mBoard );
}

void MY_2048::moveDown( )
{
    int z = 0;
    for ( int i = 0; i < mNX; ++i ) {
        moveDown_Column( i );
    }
}

void MY_2048::moveUp( )
{
    rotate_CounterClockwise( );
    rotate_CounterClockwise( );
    moveDown( );
    rotate_Clockwise( );
    rotate_Clockwise( );

}

void MY_2048::moveLeft( )
{
    rotate_CounterClockwise( );
    moveDown( );
    rotate_Clockwise( );
}

void MY_2048::moveRight( )
{
    rotate_Clockwise( );
    moveDown( );
    rotate_CounterClockwise( );
}

void MY_2048::generateNumbers_All_2to4( )
{
    reset( );


    for ( int j = 0; j < mNZ; ++j ) {
        for ( int i = 0; i < mNX; ++i ) {
            int r = rand()%2;

            int v;
            if ( r == 0 ) v = 2;
            else v = 4;
            mBoard[ j ][ i ] = v;
        }
    }
}

void MY_2048::generateNumbers_All_2to8( )
{
    reset( );
    for ( int j = 0; j < mNZ; ++j ) {
        for ( int i = 0; i < mNX; ++i ) {
            int r = rand()%3;

            int v;
            if ( r == 0 ) v = 2;
            else if ( r == 1 ) v = 4;
            else v = 8;
            mBoard[ j ][ i ] = v;
        }
    }
}

void MY_2048::generateNumbers_All( )
{
    reset( );
    for ( int j = 0; j < mNZ; ++j ) {
        for ( int i = 0; i < mNX; ++i ) {
            int r = rand()%11;

            int v = 2;
            v = v << r;
            mBoard[ j ][ i ] = v;
        }
    }
}

bool MY_2048::handleKeyPressedEvent( unsigned char key )
{
    switch( key ) {
    case 'r':
    case 'R':
        reset( );
        break;
    case '1':
        generateNumbers_All_2to4( );
        break;
    case '2':
        generateNumbers_All_2to8( );
        break;
    case '3':
        generateNumbers_All( );
        break;
    }
    return true;
}

bool MY_2048::handleSpecialKeyPressedEvent( unsigned char key )
{
    cout << "MY_2048::handleSpecialKeyPressedEvent:" << key << endl;
    bool flgDone = false;

    switch( key ) {
    case GLUT_KEY_UP:
        flgDone = true;
        moveUp( );
        mEvent = GLUT_KEY_UP;
        break;
    case GLUT_KEY_DOWN:
        flgDone = true;
        moveDown( );
        mEvent = GLUT_KEY_DOWN;

        break;
    case GLUT_KEY_LEFT:
        flgDone = true;
        moveLeft( );
        mEvent = GLUT_KEY_LEFT;

        break;
    case GLUT_KEY_RIGHT:
        flgDone = true;
        moveRight( );
        mEvent = GLUT_KEY_RIGHT;

        break;

    }

    if ( flgDone ) {
        generateNumber( );
    }

    return true;
}
