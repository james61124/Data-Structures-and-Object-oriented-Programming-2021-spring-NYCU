//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
//
#ifndef __MY_SYSTEM_COLOR_PALETTE_H_
#define __MY_SYSTEM_COLOR_PALETTE_H_
#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
#include <vector>

class COLOR_PALETTE {
protected:
    int mNX, mNZ;
    vector3 mPosition;
    float mDX, mDZ;
    GLfloat mColorBuffer[4];
    vector3 mColor;
    //
    vector3 mColorSelectorPosition;
    //
    vector3 mTransparencyBoardPosition;
    vector3 mTransparency;
    vector3 mTransparencySelectorPosition;

    bool clickAtTransparencyPalette( float x, float z, int mx, int mz );
    bool clickAtColorPalette( float x, float y, int mx, int mz );

    void drawTransparencyBoard( bool flgDrawSelector = true ) const;
    void drawColorBoard( bool flgDrawSelector = true ) const;

public:
    COLOR_PALETTE( );
    void draw( ) const;
    bool clickAt( float x, float z, int mx, int mz );
    vector3 getColor( ) const;
    float getTransparency( ) const;

};
#endif