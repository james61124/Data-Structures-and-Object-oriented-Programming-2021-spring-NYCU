//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// Date: 2014/10/09
//
#include <iostream>
#include "openGLapp.h"
#include "../primitives/vector3d.h"

using namespace std;
namespace ns_opengl {

	OpenGL_APP::OpenGL_APP( ): Basic_OpenGLApp( )
	{
		cout << "create OpenGL_APP" << endl;
		init( );
	}

	OpenGL_APP::OpenGL_APP(int argc, char *argv[], std::string p_Title): Basic_OpenGLApp( argc, argv, p_Title )
	{
		init( );
	}

	//void OpenGL_APP::setGridDimension( unsigned int nx, unsigned int ny )
	//{
	//	m_Grid_NX = nx;
	//	m_Grid_NY = ny;
	//	m_GridCellSize_DX = m_WindowWidth/(float) nx;
	//	m_GridCellSize_DY = m_WindowHeight/(float) ny;
	//}

	void OpenGL_APP::reshape( GLsizei w, GLsizei h )
{
	//cout << "OpenGL_APP::reshape" << endl;
	m_WindowWidth = w;
	m_WindowHeight = h;
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, w, 0, h, -30.0, 30.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//
		//m_BoardGameApp.setCanvasDimension( m_WindowWidth, m_WindowHeight );

			for ( int i = 0; i < mNumApplications; ++i ) {
			mApplicationsArr[i]->reshape( m_WindowWidth, m_WindowHeight );
		}
		glutPostRedisplay( );
}

	void OpenGL_APP::display( )
	{
		update( m_TimeStep );
		//clear color buffer and depth buffer.
		glClearColor( 0.5, 0.5, 0.5, 1.0 );
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		draw( );
		
		glutSwapBuffers(); //swap buffers
	}



};