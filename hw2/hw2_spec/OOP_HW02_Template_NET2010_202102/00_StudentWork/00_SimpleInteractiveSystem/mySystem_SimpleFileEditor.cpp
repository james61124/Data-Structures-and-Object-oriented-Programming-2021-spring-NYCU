//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/03/29
//
#include "mySystem_SimpleFileEditor.h"
#include <iostream>
#include <fstream>
using namespace std;

#define FILE_NAME "oop.txt"

SIMPLE_FILE_EDITOR::SIMPLE_FILE_EDITOR( )
{
    //BEGIN: DO NOT CHANGE
    mNX = 100; // number of columns
    mNY = 100; // number of rows
    mBitmap = new int[mNX*mNY];
    for ( int i = 0; i < mNX*mNY; ++i ) {
        mBitmap[ i ] = 0;
    }
    readFile( );
    //END: DO NOT CHANGE

}

/*
Set up the bitmap based on the data stored in a file.

Each line in the file is mapped to one row
of the bitmap in a consecutive manner.

Steps:
Open the file.
Read a file.
 Repeat until EOF
   read a line from the file each time
   set the bitmap based on the current line
Close the file.
*/
void SIMPLE_FILE_EDITOR::readFile( )
{

}

/*
Set one row of the bitmap based on the input string inputString.
The elements of the row are mapped one to one to the input string.

The element of a bitmap is set as follows.

If inputString[i] is the space character, 
the value of the element is set as 0.
Otherwise, the value of the element is set to (int) inputString[i].
*/
void SIMPLE_FILE_EDITOR::storeOneRowToBitmap( const string &inputString )
{
}

/*
Show the system title.
Show "No input is required!".
*/
void SIMPLE_FILE_EDITOR::askForInput( )
{
    //Show the system title
    //
    cout << "SIMPLE_FILE_EDITOR" << endl;
    cout << "No input is required!" << endl;
}

/*
Get the dimension of the bitmap to (nx, ny).
nx : number of columns
ny : number of rows
*/
void SIMPLE_FILE_EDITOR::getBitmapDimension(int &nx, int &ny) const
{
    nx = 1;
    ny = 1;
}

/*
Return the bitmap value at (x, y).
x : column index
y : row index
*/
int SIMPLE_FILE_EDITOR::getBitmapValue(int x, int y) const
{
    return 10;
}


bool SIMPLE_FILE_EDITOR::handleKeyPressedEvent( int key )
{
    bool flg =false;
    switch(key) {
    case '<':
        //rotateToLeft( );
        flg = true;
        break;
        case '>':
        //rotateToRight( );
        flg = true;
        break;
    }

    return flg;
}