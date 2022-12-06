//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// Date: 2014/10/09
//
#ifndef __BOARD_GAME_APP_H_
#define __BOARD_GAME_APP_H_
#include "../headers.h"
#include <string>
#include "../imageReader/imageReader.h"
#include "../openGLbasic/opengl_stuff.h"
#include "../boardGame/boardGame.h"
#include "../textureManager/textureManager.h"
#include "../painter/painter.h"
#include "../basic_app.h"
using namespace ns_opengl;

class BOARD_GAME_APP : public BOARD_GAME, public OPENGL_PAINTER, public BASIC_APP {
protected:
	int mMouseX;
	int mMouseY;


	bool mFlgShowGrid;
	Image m_ImageReader[8];
	dTEXTURE m_Texture[2];
	void initBGApp( );
	virtual void draw( int mouseX, int mouseY ) const;
public:
	BOARD_GAME_APP( );
	
	void setShowFlg_Grid( bool flg );
	bool clickAtPosition( int x, int y );

	void draw( ) const;
	//
	void initApp( );
	void reshape( int w, int h );
	bool handleKeyEvent( unsigned char key );
	bool mouseMotionFunc( int x, int y );
	bool mouseFunc( int button, int state, int x, int y );
	bool passiveMouseFunc( int x, int y );
	bool specialFunc(int key, int x, int y);
};

#endif