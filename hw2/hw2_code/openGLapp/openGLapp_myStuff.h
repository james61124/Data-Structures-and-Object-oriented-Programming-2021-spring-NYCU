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
#ifndef __OPENGL_APP_MY_STUFF_H_
#define __OPENGL_APP_MY_STUFF_H_

//namespace ns_opengl {



//	class OpenGL_APP : public Basic_OpenGLApp {
	protected:
		int m_MouseX, m_MouseY;
		//
		void addNewApp( BASIC_APP* app );
		void initAllApp( );
		//
		//BOARD_GAME_APP m_BoardGameApp;
		//TURTLE_GRAPICS_APP m_TurtleGraphicsApp;
		//MESH2D_DESIGNER mMesh2D_Designer;
		//CROWD_SIMULATION_APP mCrowdSimulationApp;
		//--------------------------------------------
		int mNumApplications;
		int mMaxNumApplications;
		BASIC_APP **mApplicationsArr;
		//--------------------------------------------
//	}
//};

#endif