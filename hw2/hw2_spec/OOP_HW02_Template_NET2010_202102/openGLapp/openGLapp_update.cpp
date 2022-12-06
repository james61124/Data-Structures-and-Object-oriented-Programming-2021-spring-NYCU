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
#include "../fileReader/fileReader.h"

using namespace std;
namespace ns_opengl {
	void OpenGL_APP::update( float time_step )
	{
		/*
		int winState;
		winState = m_BoardGameApp.checkWin( );
		if ( winState != -1) {
			cout << "Win:" << winState << endl;
			
			//system("pause");


		}
		*/
		//mCrowdSimulationApp.update( );

		for ( int i = 0; i < mNumApplications; ++i ) {
			mApplicationsArr[i]->update( );
		}

	}
};