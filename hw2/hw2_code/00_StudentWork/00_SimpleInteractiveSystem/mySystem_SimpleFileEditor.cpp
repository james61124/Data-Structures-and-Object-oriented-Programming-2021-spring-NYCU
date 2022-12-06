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
#include <string.h>
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
	/*ifstream fin;
	fin.open("FILE_NAME");
	string a;
	mCurX=0;
	mCurY=0;
	for(int i=0;i<mNX;i++){
		fin>>a;
		storeOneRowToBitmap( a );
	}
	int n=0;
	for(int i=0;i<mNX*mNY;i++){
		
		cout<<mBitmap[i]<<" ";
		n++;
		if(n==100){
			cout<<endl;
			n=0;
		}
		
	}
	fin.close();*/
	
	mCurX = 0;
    mCurY = 0;
    ifstream inputFILE;
    inputFILE.open(FILE_NAME);
    string readtext;
    while (inputFILE)
    {
        getline(inputFILE, readtext);
        if (readtext.size() == 0)
        {
            continue;
        }
        cout << "inputString: " << readtext << endl;
        storeOneRowToBitmap(readtext);
        readtext.clear();
        mCurY++;
    }
    inputFILE.close();

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
	/*const char *a;
	a=new char(mNY);
	a=&inputString[0];
	int j=0;
	for(int i=mCurX;i<mCurX+mNY;i++){
		
			mBitmap[i]=(int)a[j];
			j++;
		
		
	}
	mCurX++;*/
	 if (mCurY > mNY) return;
    
    int index = mCurX + mCurY * mNX;
    for (int i = 0; i < inputString.size(); i++)
    {
        if (i > mNX){
			break;
		}
        if (inputString[i] != ' '){
			mBitmap[index] = inputString[i] ;
		}
        else{
			mBitmap[index] = 0;
		}
        index++;
	}

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
	nx = this->mNX;
    ny = this->mNY;
}

/*
Return the bitmap value at (x, y).
x : column index
y : row index
*/
int SIMPLE_FILE_EDITOR::getBitmapValue(int x, int y) const
{
    return mBitmap[x+y*mNX];
}


bool SIMPLE_FILE_EDITOR::handleKeyPressedEvent( int key )
{
    bool flg =false;
    switch(key) {
    case '<':
        rotateToLeft( );
        flg = true;
        break;
        case '>':
        rotateToRight( );
        flg = true;
        break;
    }

    return flg;
}

void SIMPLE_FILE_EDITOR::rotateToLeft()
{
    
	for (int i = 0; i < mNX; i++)
    {
        int tmp = mBitmap[i * mNY];  
        for (int j = 0; j < mNY - 1; j++)
        {
            int index = mNY * i + j; 
            mBitmap[index] = mBitmap[index + 1];
        }
        mBitmap[mNY * i + (mNY - 1)] = tmp;
    }
}

void SIMPLE_FILE_EDITOR::rotateToRight()
{
    for (int i = 0; i < mNX; i++)
    {
        int tmp = mBitmap[(i + 1) * mNY - 1];  
        for (int j = mNY - 2; j >= 0; j--)
        {
            int index = mNY * i + j; 
            mBitmap[index + 1] = mBitmap[index];
        }
        mBitmap[i * mNY] = tmp;
    }
}