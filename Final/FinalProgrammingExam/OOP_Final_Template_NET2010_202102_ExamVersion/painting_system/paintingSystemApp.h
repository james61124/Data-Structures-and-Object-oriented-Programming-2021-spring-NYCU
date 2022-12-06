//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// Date: 2014/12/10
//
#ifndef __PAINTING_SYSTEM_APP_H_
#define __PAINTING_SYSTEM_APP_H_

#include "../headers.h"
#include <string>
#include "../openGLbasic/opengl_stuff.h"
#include "paintingSystem.h"
#include "../freeCanvas2D/freeCanvas2D.h"
#include "../textureManager/texture.h"


using namespace ns_opengl;
class PAINTING_SYSTEM_APP : public FREE_CANVAS_2D, public PAINTING_SYSTEM
{
protected:
	bool mFlgShow_Grid;
	//
	int mMouseButton;
	GLuint mPictureTextureID;
	dTEXTURE *mPictureTexture;
	//
	void drawOrigin( ) const;
public:
	PAINTING_SYSTEM_APP( );
	virtual void update( );
	virtual void draw( ) const;
	virtual void initApp( );
	//
	bool handleKeyEvent( unsigned char key );
	bool passiveMouseFunc( int mx, int my );
	bool mouseMotionFunc( int x, int y );
	bool mouseFunc( int button, int state, int x, int y );
};

#endif