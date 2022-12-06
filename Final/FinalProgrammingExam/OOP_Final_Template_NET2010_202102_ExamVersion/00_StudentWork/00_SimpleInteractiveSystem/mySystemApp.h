//********************************************
// Student Name			:ªô¥°µ¤
// Student ID			:109550136
// Student Email Address:james61124@gmail.com
//********************************************
//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/06/17
//
#ifndef __MY_SYSTEM_APP_APP_H_
#define __MY_SYSTEM_APP_APP_H_
/////////////////////////////////////////////
#include "../headers.h"
#include <string>
#include "../openGLbasic/opengl_stuff.h"
#include "../freeCanvas2D/freeCanvas2D.h"
#include "../textureManager/texture.h"
/////////////////////////////////////////////
#include "mySystem_MonteCarlo.h"
#include "mySystem_SortingVisualization.h"
#include "mySystem_GraphSystem.h"

#define SYSTEM_TYPE_MONTE_CARLO_SIMULATION		1
#define SYSTEM_TYPE_GALAXY_SYSTEM           2
#define SYSTEM_TYPE_SIMPLE_PAINTER      3
#define SYSTEM_TYPE_SORTING_VISUALIZATION	4
#define SYSTEM_TYPE_SIMPLE_FILE_EDITOR	    5

#define cn_StudentInfo "Student Name:xyz. ID:012345678"

/////////////////////////////////////////////

using namespace ns_opengl;
class MY_SYSTEM_APP : public FREE_CANVAS_2D
{
protected:
	bool mFlgShow_Grid;
	int mMouseButton;
    int mMouseX, mMouseY;
    float mMouseX_2DSpace, mMouseY_2DSpace;
    //
    //COLOR_PALETTE *mColorPalette;
	//
	void drawOrigin( ) const;
    void draw_System_Content( ) const;
    //

	void draw_MonteCarlo_Simulation( ) const;
	void draw_GalaxySystem( ) const;
	void draw_SimplePainter( ) const;
	void draw_SortingVisualization( ) const;
    void draw_SimpleFileEditor( ) const;
    void askForInput( );
    void reset( );
	//
	void showStudentInfo_2021( ) const;
    void showMenu( ) const;
    //
    void updateMonteCarloTitle( );
    void update_GraphSystemTitle( );
    void update_2048SystemTitle( const char *msg );
    void update_MonteCarloSystemTitle(const char *msg );
    void update_VisualizationSystemTitle();
    void update_ImageSystemTitle( );

public:
	MY_SYSTEM_APP( );
	virtual void update( );
	virtual void draw( ) const;
	virtual void initApp( );
	//
    void clickAt(float x, float y );
	bool specialFunc(int key, int x, int y);
	bool handleKeyEvent( unsigned char key );
	bool passiveMouseFunc( int mx, int my );
	bool mouseMotionFunc( int x, int y );
	bool mouseFunc( int button, int state, int x, int y );
	//////////////////////////////////////////////////
    
protected:
    BASE_SYSTEM *mCurSystem;

    //MY_2048 *mPrev_2048;
    //MY_2048 *mMy2048;
    //
    MONTE_CARLO_SYSTEM *mMonteCarloSystem;
    //
    GRAPH_SYSTEM *mGraphSystem;
    //
    SORTING_VISUALIZATION *mSortingVisualization;

    //TRAFFIC_SYSTEM *mTrafficSystem;

    //IMAGE_SYSTEM *mImageSystem;
    //IMAGE_SYSTEM_RECTANGLES *mImageSystem_Rectangles;
    //
	int mSystemType;
    //GALAXY_SYSTEM mGalaxySystem;
	
	//SIMPLE_FILE_EDITOR mSimpleFileEditor;
	//SIMPLE_PAINTER mSimplePainter;
	//SORTING_VISUALIZATION mSortingVisualization;
};

#endif