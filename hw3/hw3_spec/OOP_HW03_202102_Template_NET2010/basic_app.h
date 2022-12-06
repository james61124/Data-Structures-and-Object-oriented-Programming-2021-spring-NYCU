//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// Date: 2014/12/10
//
#ifndef __BASIC_APP_H_
#define __BASIC_APP_H_

#include "../headers.h"
#include <string>

class BASIC_APP {
protected:
	bool mEnabledApp;
public:
	BASIC_APP( ) { mEnabledApp = true; }
	virtual void enableApp( bool flg ) { mEnabledApp = flg; }
	virtual void draw( ) const { }
	virtual void update( ) { }
	virtual void initApp( ) = 0;
	virtual void reshape( int w, int h ) { }
	virtual bool handleKeyEvent( unsigned char key ) { return false; }
	virtual bool mouseMotionFunc( int x, int y ) { return false; }
	virtual bool mouseFunc( int button, int state, int x, int y ) { return false; }
	virtual bool passiveMouseFunc( int x, int y ) { return false; }
	virtual bool specialFunc(int key, int x, int y) { return false; }
};

#endif