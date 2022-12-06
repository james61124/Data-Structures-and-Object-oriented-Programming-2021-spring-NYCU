//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// Date: 2014/10/09
//
//------------------------------
// Student Name:
// Student ID:
// Student Email:
// Program description:
//
//------------------------------
#include <iostream>
#include "openGLapp_headers.h"
#include "openGLapp.h"
#include "openGLapp_myStuff.h"
#include "../primitives/vector3d.h"
#include "../fileReader/fileReader.h"

using namespace std;
namespace ns_opengl {
	//
	// Draw something to the screen
	//
	// const: cannot change the content of the application
	//
	void OpenGL_APP::draw( ) const	
	{
		//m_BoardGameApp.draw( m_MouseX, m_MouseY );

		//m_TurtleGraphicsApp.draw( );

		//mMesh2D_Designer.draw( );
		
		//mCrowdSimulationApp.draw( );

		for ( int i = 0; i < mNumApplications; ++i ) {
			mApplicationsArr[i]->draw( );
		}
	}
};
