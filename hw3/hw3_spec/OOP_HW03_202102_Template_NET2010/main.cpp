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
#include <math.h>
#include "openGLbasic/opengl_stuff.h"
#include "openGLapp/openGLapp.h"

using namespace std;
int main(int argc, char *argv[])
{
	using ns_opengl::initGL;
	using ns_opengl::go_openGL;
	using ns_opengl::Basic_OpenGLApp;
	using ns_opengl::OpenGL_APP;

	cout << "Step 1: initGL( argc, argv )" << endl;
	initGL( argc, argv );	// initialize openGL

	//---------------------------------------------------------------
	cout << "Step 2: Create an app" << endl;
	OpenGL_APP app(argc, argv, "Enjoy Programming. Press ENTER to reset. Can you find the bug?");
	app.showInfo( );
	cout << "Step 3" << endl;
	//---------------------------------------------------------------

	//---------------------------------------------------------------
	//const char *win_title = "This the second window.";//Try me!!!
	//OpenGL_APP advancedApp( argc, argv, win_title );	//Try me!!!
	//---------------------------------------------------------------
	cout << "Step 4: go_openGL" << endl;

	go_openGL( );

	return 0;
}

//===================================================

//


