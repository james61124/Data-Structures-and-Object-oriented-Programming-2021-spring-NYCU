//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
//
#ifndef __MY_SIMPLE_FILE_EDITOR_H_
#define __MY_SIMPLE_FILE_EDITOR_H_
#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
#include <vector>
#include "base_class.h"
using std::vector;

class SIMPLE_FILE_EDITOR : public BASE_SYSTEM
{
protected:
    int mNX, mNY;
    int mCurX, mCurY;
    int *mBitmap;
    void readFile( );
    void storeOneRowToBitmap( const std::string &inputString );
public:
    SIMPLE_FILE_EDITOR( );
    void askForInput( );
    void getBitmapDimension(int &nx, int &ny) const;
    int getBitmapValue(int x, int y) const;
};
#endif