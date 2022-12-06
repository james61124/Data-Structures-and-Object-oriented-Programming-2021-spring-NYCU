//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// Date: 2014/10/09
//
#ifndef __OPENGL_APP_H_
#define __OPENGL_APP_H_

#include "openGLapp_headers.h"

#define RUN_WHICH_APP_None				0
#define RUN_WHICH_APP_2DMeshDesigner	1
#define RUN_WHICH_APP_BOARDGAME			2

namespace ns_opengl {

	class OpenGL_APP : public Basic_OpenGLApp {
	public:
		OpenGL_APP( );

		OpenGL_APP(int argc, char *argv[], std::string p_Title);
		//
		// display function
		void display( );
		//
		// idle function
		void idle( );
		//
		// reshape function
		void reshape( GLsizei w, GLsizei h );
		//
		// keyboard function
		void keyboard(unsigned char key, int x, int y);
		//
		// mouse function
		void mouseFunc(int button, int state, int x, int y);
		//
		// passive mouse function
		void mousePassiveMouseFunc( int x, int y);
		//
		// mouse motion function
		void motionFunc( int x, int y );
		//
		// special key function
		void specialFunc(int key, int x, int y);

	protected:
		float m_TimeStep;	// simulation time step size
//
//
//================================================================
#include "openGLapp_myStuff.h"
//================================================================
	protected:
		//
		// initialize the application
		void init( );
		//
		// update the internal state of the application object
		void update( float time_step );	
		//
		// draw something to the screen
		void draw( ) const;	

	};
};

#endif