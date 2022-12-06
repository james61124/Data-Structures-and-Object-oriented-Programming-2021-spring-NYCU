//********************************************
// Student Name			:
// Student ID			:
// Student Email Address:
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
#include "mySystem_2048.h"
#include <iostream>

using namespace std;

static unsigned char specialKeys[] = {
    GLUT_KEY_UP,
    GLUT_KEY_DOWN,
    GLUT_KEY_LEFT,
    GLUT_KEY_RIGHT
};

int numSpecialKeys = sizeof(specialKeys)/sizeof(unsigned char);

MY_2048::MY_2048( )
{
    mNX = 4;
    mNZ = 4;
    reset( );

    mPositionX = 0;
    mPositionZ = 0;
    mFlgFocus = true;
    //
    flg_AutoPlay = false;
}

MY_2048::MY_2048( int nx, int nz )
{
    mPositionX = 0;
    mPositionZ = 0;
    mFlgFocus = true;
    //
    // Implement your own stuff
    //
}

void MY_2048::setDimension(int nx, int nz)
{
    mFlgFocus = true;
    
    //
    // Implement your own stuff
    //
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

//
// Copy the m's previous board 
// to the object's mBoard.
//
void MY_2048::copyPrevious( const BASE_SYSTEM *m )
{
    for ( int j = 0; j < mNZ; ++j ) {
        for ( int i = 0; i < mNX; ++i ) {
            //mBoard = ((MY_2048*)m)->mPreviousBoard[ j ][ i ];
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
    //
    // Implement your own stuff
    //
}

//
// show messages and ask for input (if any)
//
void MY_2048::askForInput( )
{
    //
    // Implement your own stuff
    //
}

//
// randomly generate a new number
//
void MY_2048::generateNumber( )
{
    //
    // Implement your own stuff
    //
}

void MY_2048::moveDown( )
{
    //
    // Implement your own stuff
    //    

}

void MY_2048::moveUp( )
{
    //
    // Implement your own stuff
    //
}

void MY_2048::moveLeft( )
{
    //
    // Implement your own stuff
    //
}

void MY_2048::moveRight( )
{
    //
    // Implement your own stuff
    //
}

void MY_2048::generateNumbers_All_2to4( )
{
    //
    // Implement your own stuff
    //
}

void MY_2048::generateNumbers_All_2to8( )
{
    //
    // Implement your own stuff
    //
}

void MY_2048::generateNumbers_All( )
{
    //
    // Implement your own stuff
    //
}

void MY_2048::handleKeyPressedEvent( unsigned char key )
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

    case 'a':
    case 'A':
        //flg_AutoPlay
        break;
    }
}

void MY_2048::performAction( unsigned char key ) {
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
}

void MY_2048::handleSpecialKeyPressedEvent( unsigned char key )
{
    //
    // It takes a long time to show a message!
    //
    cout << "MY_2048::handleSpecialKeyPressedEvent:" << key << endl;
    performAction( key );
}

bool MY_2048::isAutoPlay() const
{
    return flg_AutoPlay;
}

//
// The update( ) function is called every frame.
//
// Design an algorithm to automatically perform
// one step.
//
void MY_2048::update( )
{
    //
    // It takes a long time to show a message!
    //
    cout << "MY_2048::update( )" << endl;
    cout << "MY_2048::flg_AutoPlay:\t" << flg_AutoPlay << endl;

    if (!flg_AutoPlay) return;

    //
    // Implement your own stuff
    //
}
