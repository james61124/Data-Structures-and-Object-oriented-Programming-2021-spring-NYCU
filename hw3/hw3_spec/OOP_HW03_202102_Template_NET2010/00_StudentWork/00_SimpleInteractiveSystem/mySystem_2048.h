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
    void generateNumbers_All_2to4( );
    void generateNumbers_All_2to8( );
    void generateNumbers_All( );

    void performAction( unsigned char key );

    //
    // Implement your own stuff
    //
public:
    MY_2048( );
    MY_2048( int nx, int nz );
    void setDimension(int nx, int nz);
    void draw( ) const;
    void askForInput( );
    void handleKeyPressedEvent( unsigned char key );
    void handleSpecialKeyPressedEvent( unsigned char key );
    void setPosition( int x, int z );
    void setFocus( bool flg );
    //
    void update( );

    bool isAutoPlay() const;
    //
    void copyPrevious( const BASE_SYSTEM *m );
    //
protected:
    ///////////////////////////////////////////
    bool mFlgFocus;
    int mPositionX, mPositionZ;
    unsigned char mEvent;
    ///////////////////////////////////////////
    int mNX, mNZ;
    int mBoard[MAX_2048_NZ][MAX_2048_NX];
    //
    int mPreviousBoard[MAX_2048_NZ][MAX_2048_NX];
    //
    bool flg_AutoPlay;
    //
    //
    // Implement your own stuff
    //
};

#endif