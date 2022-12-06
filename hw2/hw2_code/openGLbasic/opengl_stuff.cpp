//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// Date: 2014/10/09
//
#include <iostream>

#include "opengl_stuff.h"

using std::cout;
using std::endl;

namespace {
	const char *default_title = "I enjoy programming very much.";
	char *default_argv[] = {"a1", "a2"};
};
namespace ns_opengl {

const int maxOpenGLApps = 16;
int Basic_OpenGLApp::_num_Apps = 0;
Basic_OpenGLApp **Basic_OpenGLApp::_openGLApp = new Basic_OpenGLApp*[maxOpenGLApps];


	//gb_ : global
	//Begin forward declaration
	void gb_display();
	void gb_reshape(GLsizei w, GLsizei h);
	void gb_keyboard(unsigned char key, int x, int y);
	void gb_mouseFunc(int button, int state, int x, int y);
	void gb_mousePassiveMouseFunc( int x, int y);
	void gb_motionFunc( int x, int y);
	void gb_SpecialFunc( int key, int x, int y );
	void gb_idle();
	//
	//End Forward Declaration

	Basic_OpenGLApp::Basic_OpenGLApp( ) {
		cout << "create Basic_OpenGLApp( )" << endl;
		initInternalState( );

		int argc = 1;
		createWindow( argc, default_argv, default_title );
	}
	
		Basic_OpenGLApp::Basic_OpenGLApp(int argc, char *argv[], std::string p_Title)
	{
		cout << "create Basic_OpenGLApp(int argc, char *argv[], std::string p_Title)" << endl;
		initInternalState( );
		//
		createWindow( argc, argv, p_Title );
	}
		
	void Basic_OpenGLApp::initInternalState( )
	{
				cout << "Basic_OpenGLApp::Basic_OpenGLApp" << endl;
		_openGLApp[_num_Apps] = this;
		++_num_Apps;
		cout << "Basic_OpenGLApp::Basic_OpenGLApp:" << _num_Apps << endl;
		//
		m_WinID = 0;
	}

	void Basic_OpenGLApp::showInfo( ) const
	{
		cout << "void Basic_OpenGLApp::showInfo( ) const" << endl;
		cout << "m_WinID:" << m_WinID << endl;
	}

	void Basic_OpenGLApp::createWindow( int argc, char *argv[], std::string p_Title )
	{
		/*
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
		glutInitWindowSize(800,800);
		glutInitWindowPosition(100,100);
*/

		//Begin glew
		    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
    glutInitWindowSize( 512, 512 );
    // If you are using freeglut, the next two lines will check if 
    // the code is truly 3.2. Otherwise, comment them out
    //glutInitContextVersion( 3, 2 ); 
	//
	// If context is not supported, glGetFloatv does not work correctly.
	// MAKE SURE the context is supported!
	//
	glutInitContextVersion( 2, 0 );
    glutInitContextProfile( GLUT_CORE_PROFILE );
	m_WinID = glutCreateWindow( "Enjoy OOP" );
    glewExperimental = GL_TRUE;
	glewInit( );
		//End glew
		//m_WinID = glutCreateWindow( p_Title.data());
		
		glutSetWindow(m_WinID);
		glDepthFunc( GL_LEQUAL );
		glEnable(GL_DEPTH_TEST);

		GLint param[1] = {1};
		glLightModeliv( GL_LIGHT_MODEL_TWO_SIDE, param );
		glEnable( GL_COLOR_MATERIAL );
		glEnable( GL_LIGHTING );
		glEnable( GL_LIGHT0 );
		glEnable( GL_LIGHT1 );

		//
glutDisplayFunc( gb_display );
		glutReshapeFunc( gb_reshape );
		glutKeyboardFunc( gb_keyboard );
		glutMouseFunc( gb_mouseFunc );
		glutMotionFunc( gb_motionFunc );
		glutPassiveMotionFunc( gb_mousePassiveMouseFunc );
		glutSpecialFunc( gb_SpecialFunc );
		glutIdleFunc( gb_idle );
	}
	int Basic_OpenGLApp::_getAppPointerID( int winID )
	{
		int id = 0;
		//cout << "Basic_OpenGLApp::_getAppPointerID" << endl;
		//cout << "_num_Apps:" << _num_Apps << endl;
		for (int i = 0; i < _num_Apps; ++i ) {
			if ( winID == _openGLApp[i]->m_WinID ) {
				id = i;
				break;
			}
		}
		return id;
	}

	void Basic_OpenGLApp::_reshape( GLsizei w, GLsizei h )
	{
		int winID = 0;

		winID = glutGetWindow( );
//		cout << "_reshape:winID:" << winID << endl;

		int id = _getAppPointerID( winID );
		_openGLApp[ id ]->reshape( w, h );	
	}
	void Basic_OpenGLApp::_display_all( )
	{
		int id = _getAppPointerID( glutGetWindow( ) );
		_openGLApp[ id ]->display( );
	}

		void Basic_OpenGLApp::_idle( )
		{

			int id = _getAppPointerID( glutGetWindow( ) );
		_openGLApp[ id ]->idle( );
		}

		 void Basic_OpenGLApp::_keyboard( unsigned char key, int x, int y )
			 {
	int id = _getAppPointerID( glutGetWindow( ) );
		_openGLApp[ id ]->keyboard( key, x, y );
		}

		 		 void Basic_OpenGLApp::_specialFunc( int key, int x, int y )
			 {
	int id = _getAppPointerID( glutGetWindow( ) );
		_openGLApp[ id ]->specialFunc( key, x, y );
		}

		 void Basic_OpenGLApp::_mouseFunc( int button, int state, int x, int y )
			 {
int id = _getAppPointerID( glutGetWindow( ) );
		_openGLApp[ id ]->mouseFunc( button, state, x, y );
		}

		 void Basic_OpenGLApp::_mousePassiveMouseFunc( int x, int y )
			 {
				 int id = _getAppPointerID( glutGetWindow( ) );
		_openGLApp[ id ]->mousePassiveMouseFunc( x, y );
		}

		 void Basic_OpenGLApp::_motionFunc( int x, int y )
		 {
			  int id = _getAppPointerID( glutGetWindow( ) );
		_openGLApp[ id ]->motionFunc( x, y );
		 }


	void initGL(int argc, char *argv[])
	{
		//glutInit( &argc, argv );
		//-----------------------

	}

	//===================================================
	void gb_display()
	{
		int winID = glutGetWindow( );	
		Basic_OpenGLApp::_display_all( );
		glutSetWindow( winID );
		
	}

	void gb_reshape(GLsizei w, GLsizei h) 
	{
		//cout << "void gb_reshape(GLsizei w, GLsizei h)" << endl;
		Basic_OpenGLApp::_reshape( w, h );
	}

	void gb_SpecialFunc( int key, int x, int y )
	{
		Basic_OpenGLApp::_specialFunc( key, x, y );
	}

	void gb_keyboard(unsigned char key, int x, int y) 
	{
		Basic_OpenGLApp::_keyboard( key, x, y );
		if (key == 27) {	// ESC key ASCII code
			std::cout << "ESC key is pressed!!!" << std::endl;
			//system("pause");
			exit(1);
		}
		/*
		if (key == '1') {
		objects[0]->setPositionY(10*windowHeight/2);
		}
		if (key == '2') {
		objects[1]->setPositionY(10*windowHeight/2);
		}
		*/
	}

	void gb_motionFunc( int x, int y)
	{
		Basic_OpenGLApp::_motionFunc( x, y );
	}


	void gb_mousePassiveMouseFunc( int x, int y)
	{
		Basic_OpenGLApp::_mousePassiveMouseFunc( x, y );
	}

	void gb_mouseFunc(int button, int state, int x, int y)
	{
		Basic_OpenGLApp::_mouseFunc( button, state, x, y );
	}


	void gb_idle()
	{
		//cout << "idle" << endl;
		Basic_OpenGLApp::_idle( );
		glutPostRedisplay(); //ask for drawing the content in the next cycle.
	}



	void go_openGL( ) {

		
		glutMainLoop();
	}


};

void ogl_drawSimpleCircleXZ( float x, float y, float z, float r, int numSegments )
{
		int numPoints = numSegments;
	glPushMatrix( );
	glTranslatef( x, y, z );
	glBegin( GL_LINE_LOOP );
	for ( int i = 0; i < numPoints; ++i ) {
		float a = i/(float)numPoints*3.14f*2.0f;
		
		float xx = r*cos(a);
		float zz = r*sin(a);
		glVertex3f( xx, y, zz );
	}
	glEnd( );
	glPopMatrix( );
}

void ogl_drawSimpleSolidCircleXZ( float x, float y, float z, float r, int numSegments )
{
		int numPoints = numSegments;
	glPushMatrix( );
	glTranslatef( x, y, z );
	glBegin( GL_TRIANGLE_FAN );
	glVertex3f( 0.0, 0.0, 0.0 );
	for ( int i = 0; i < numPoints+1; ++i ) {
		float a = i/(float)numPoints*3.14f*2.0f;
		
		float xx = r*cos(a);
		float zz = r*sin(a);
		glVertex3f( xx, y, zz );
	}
	glEnd( );
	glPopMatrix( );
}
void ogl_drawFilledRectXZ( float minx, float maxx, float minz, float maxz, float y )
{
	glBegin( GL_QUADS );
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f( minx, y, minz );
	glVertex3f( maxx, y, minz );
	glVertex3f( maxx, y, maxz );
	glVertex3f( minx, y, maxz );
	glEnd( );
}

void ogl_drawFilledRectXZ_withTexture( float minx, float maxx, float minz, float maxz, float y )
{
	//cout << "ogl_drawFilledRectXZ_withTexture........" << endl;
	glBegin( GL_QUADS );
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f( 0.0, 0.0 );
	glVertex3f( minx, y, minz );
	glTexCoord2f( 1.0, 0.0 );

	glVertex3f( maxx, y, minz );
	glTexCoord2f( 1.0, 1.0 );

	glVertex3f( maxx, y, maxz );
	glTexCoord2f( 0.0, 1.0 );

	glVertex3f( minx, y, maxz );
	glEnd( );
}

void ogl_drawSimpleLineSegment( float x0, float y0, float z0, float x1, float y1, float z1 )
{
	glBegin( GL_LINES );
	glVertex3f( x0, y0, z0 );
	glVertex3f( x1, y1, z1 );
	glEnd( );
}