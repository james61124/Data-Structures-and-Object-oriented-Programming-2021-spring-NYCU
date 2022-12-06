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

#define Mtool_BgnMsg( )	cout << "-----------" << endl;
#define Mtool_EndMsg( )	cout << "-----------" << endl;

#define ENABLE_DEBUG_MSG
#undef ENABLE_DEBUG_MSG

using namespace std;

namespace ns_opengl {
	void OpenGL_APP::keyboard(unsigned char key, int x, int y)
	{
		bool flg_key_handled;
#ifdef ENABLE_DEBUG_MSG
		Mtool_BgnMsg( );
		cout << "OpenGL_APP: WinID:" << m_WinID << endl;
		cout << "OpenGL_APP::keyboard(unsigned char key, int x, int y)" << endl;
		cout << "key:" << key << "\t(x, y):" << x << "\t" << y << endl;
		Mtool_EndMsg( );
#endif

		//cout << "key:" << key << "\t(x, y):" << x << "\t" << y << endl;
		
		//cout << "key:" << (int)key << endl;
		
		for ( int i = 0; i < mNumApplications; ++i ) {
			flg_key_handled = mApplicationsArr[i]->handleKeyEvent( key );
			if ( flg_key_handled ) break;
		}

		/*

		*/
	}
		void OpenGL_APP::mouseFunc(int button, int state, int x, int y)
		{
#ifdef ENABLE_DEBUG_MSG
			Mtool_BgnMsg( );
		cout << "OpenGL_APP: WinID:" << m_WinID << endl;

			cout << "OpenGL_APP::mouseFunc(int button, int state, int x, int y)" << endl;
			cout << "button:" << button << "\tstate:" << state << endl;
			cout << "\t(x, y):" << x << "\t" << y << endl;
		Mtool_EndMsg( );
#endif

		for ( int i = 0; i < mNumApplications; ++i ) {
			bool flg_key_handled = mApplicationsArr[i]->mouseFunc( button, state, x, y );
			if ( flg_key_handled ) break;
		}

		/*
		cout << "bgn Click" << endl;

		*/
		//cout << "end Click" << endl;

		}
		void OpenGL_APP::mousePassiveMouseFunc( int x, int y)
		{
#ifdef ENABLE_DEBUG_MSG

			Mtool_BgnMsg( );
		cout << "OpenGL_APP: WinID:" << m_WinID << endl;
		cout << "OpenGL_APP::mousePassiveMouseFunc( int x, int y)" << endl;
		cout << "(x, y):" << x << "\t" << y << endl;
		Mtool_EndMsg( );
#endif

		m_MouseX = x;
		m_MouseY = y;

			// TRY ME // TRY ME // TRY ME
			//m_BlockY = (y / (float)(m_WindowHeight))*m_Grid_NY; 

		for ( int i = 0; i < mNumApplications; ++i ) {
			bool flg_key_handled = mApplicationsArr[i]->passiveMouseFunc( x, y );
			if ( flg_key_handled ) break;
		}
		}

		void OpenGL_APP::motionFunc( int x, int y )
		{
#ifdef ENABLE_DEBUG_MSG

			Mtool_BgnMsg( );
				cout << "OpenGL_APP: WinID:" << m_WinID << endl;
		cout << "OpenGL_APP::motionFunc( int x, int y)" << endl;
		cout << "(x, y):" << x << "\t" << y << endl;
		Mtool_EndMsg( );
#endif
				for ( int i = 0; i < mNumApplications; ++i ) {
			bool flg_key_handled = mApplicationsArr[i]->mouseMotionFunc( x, y );
			if ( flg_key_handled ) break;
		}
		}

		void OpenGL_APP::specialFunc(int key, int x, int y)
		{
#ifdef ENABLE_DEBUG_MSG

			Mtool_BgnMsg( );
				cout << "OpenGL_APP: WinID:" << m_WinID << endl;
		cout << "OpenGL_APP::specialFunc( int key, int x, int y )" << endl;
		cout << "key:" << key << endl;

		cout << "(x, y):" << x << "\t" << y << endl;
		Mtool_EndMsg( );
#endif
		//cout << "key:" << key << endl;
for ( int i = 0; i < mNumApplications; ++i ) {
			bool flg_key_handled = mApplicationsArr[i]->specialFunc( key, x, y );
			if ( flg_key_handled ) break;
		}
		}

		void OpenGL_APP::idle( )
		{
			static bool firstTime = false;
			if ( firstTime ) return;
			firstTime = true;
			cout << "OpenGL_APP: WinID:" << m_WinID << endl;
			cout << "OpenGL_APP::idle( )" << endl;
		}
}