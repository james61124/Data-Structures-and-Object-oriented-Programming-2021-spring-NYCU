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
#include "openGLapp.h"
#include "openGLapp_myStuff.h"

#include "../primitives/vector3d.h"

using namespace std;
namespace ns_opengl {
	//
	// Initialization step
	// This function is called when the object of OpenGL_APP is created.
	//
	void OpenGL_APP::init( )
	{
		cout << "BGN init()" << endl;
		m_TimeStep = 0.03f; 
		glLineWidth( 5.0 );

	
		m_MouseX = 0;
		m_MouseY = 0;

		//m_BoardGameApp.initBGApp( );
		//m_BoardGameApp.reset( );
		//
		//mMesh2D_Designer.initMesh2DDesigner( );
		//

		mMaxNumApplications = 16;
		mNumApplications = 0;
		mApplicationsArr = new BASIC_APP*[mMaxNumApplications];
	
		//addNewApp( new BOARD_GAME_APP );
		//addNewApp( new MESH2D_DESIGNER );
		//addNewApp( new CROWD_SIMULATION_APP );
		//addNewApp( new PAINTING_SYSTEM_APP );
		addNewApp( new MY_SYSTEM_APP );
		//
		initAllApp( );
		cout << "END init()" << endl;

	}

	void OpenGL_APP::addNewApp( BASIC_APP* app )
	{
		if ( mNumApplications >= mMaxNumApplications ) {
			cout << "OpenGL_APP::addNewApp. Too many apps. Cannot add" << endl;
			return;
		}

		mApplicationsArr[mNumApplications] = app;
		++mNumApplications;

	}

	void OpenGL_APP::initAllApp( ) {
		for ( int i = 0; i < mNumApplications; ++i ) {
			mApplicationsArr[i]->initApp( );
		}
	}

};