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
//
// Add your own functions if necessary
//
#ifndef __MY_2048_SYSTEM_H_
#define __MY_2048_SYSTEM_H_
#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
#include <vector>
#include "base_class.h"
#include "graph_basics.h"

using std::vector;

#define MAX_2048_NX 10
#define MAX_2048_NZ 10

class MY_2048 : public BASE_SYSTEM {
protected:
    void draw_GridCell( int ix, int iz ) const;
    void draw_GridCells( ) const;
    void draw_Board( ) const;
    void draw_Event( ) const;

    void reset( );
    void generateNumber( );
    void moveDown( );
    void moveUp( );
    void moveLeft( );
    void moveRight( );
    //
    void rotate_CounterClockwise( );
    void rotate_Clockwise( );
    void copy( int src[][MAX_2048_NX], int tgt[][MAX_2048_NX]);
    //
    void moveItem( int zIndex, int targetIndex, int i );
    int findItem( int startIndexZ, int i ) const;
    void moveDown_Column( int i );
    //
    void generateNumbers_All_2to4( );
    void generateNumbers_All_2to8( );
    void generateNumbers_All( );


public:
    MY_2048( );
    MY_2048( int nx, int nz );
    void setDimension(int nx, int nz);
    void draw( ) const;
    void askForInput( );
    bool handleKeyPressedEvent( unsigned char key );
    bool handleSpecialKeyPressedEvent( unsigned char key );
    void setPosition( int x, int z );
    void copy( const BASE_SYSTEM *m );
    MY_2048 &operator=(const MY_2048 &m);
    void setFocus( bool flg );
protected:
    ///////////////////////////////////////////
    bool mFlgFocus;
    int mPositionX, mPositionZ;
    unsigned char mEvent;
    ///////////////////////////////////////////
    int mNX, mNZ;
    int mNumFreeCells;
    int mBoard[MAX_2048_NZ][MAX_2048_NX];
    int mTmpBoard[MAX_2048_NZ][MAX_2048_NX];
    //
    
};

#endif