//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// Date: 2014/10/09
//
#ifndef __OPENGL_STUFF
#define __OPENGL_STUFF
#include "../headers.h"

#define pl_glVertex3f(p) glVertex3f( p.x, p.y, p.z )
#define pl_glNormal3f(p) glNormal3f( p.x, p.y, p.z )
#define pl_glColor3f(p) glColor3f( p.x, p.y, p.z )
#define pl_glVertex3f_pos(p) glVertex3f( p.x, p.y, p.z + 0.5 )
#define pl_glDrawLineSegment(p0, p1) ogl_drawSimpleLineSegment( p0.x, p0.y, p0.z, p1.x, p1.y, p1.z )

#include <string>
namespace ns_opengl {

	class Basic_OpenGLApp {
	protected:
		static int _num_Apps;
		static Basic_OpenGLApp **_openGLApp;
		static int _getAppPointerID( int winID );
	protected:
		int m_WinID;
		int m_WindowWidth, m_WindowHeight;
		void initInternalState( );
		void createWindow( int argc, char *argv[], std::string p_Title );
	public:
		Basic_OpenGLApp( );
		Basic_OpenGLApp(int argc, char *argv[], std::string p_Title);

		//
		virtual void showInfo( ) const;
		virtual void display( ) {}
		virtual void idle( ) {}
		virtual void reshape( GLsizei w, GLsizei h ) { }
		virtual void keyboard(unsigned char key, int x, int y) { }
		virtual void mouseFunc(int button, int state, int x, int y) { }
		virtual void mousePassiveMouseFunc( int x, int y) { }
		virtual void motionFunc( int x, int y ) { }
		virtual void specialFunc(int key, int x, int y) { }

	public:
		static void _display_all( );
		static void _reshape( GLsizei w, GLsizei h );
		static void _idle( );
		static void _keyboard(unsigned char key, int x, int y);
		static void _specialFunc(int key, int x, int y);
		static void _mouseFunc(int button, int state, int x, int y);
		static void _mousePassiveMouseFunc( int x, int y);
		static void _motionFunc( int x, int y );
	};

	extern void initGL( int argc, char *argv[] );
	extern void go_openGL( );
};

extern void ogl_drawSimpleLineSegment( float x0, float y0, float z0, float x1, float y1, float z1 );
extern void ogl_drawSimpleCircleXZ( float x, float y, float z, float r, int numSegments );
extern void ogl_drawSimpleSolidCircleXZ( float x, float y, float z, float r, int numSegments );

extern void ogl_drawFilledRectXZ( float minx, float maxx, float minz, float maxz, float y );
extern void ogl_drawFilledRectXZ_withTexture( float minx, float maxx, float minz, float maxz, float y );

#endif