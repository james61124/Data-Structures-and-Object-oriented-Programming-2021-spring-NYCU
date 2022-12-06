//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/03/01
//
#include <sstream>
#include "mySystemApp.h"

using namespace std;

void MY_SYSTEM_APP::increase()
{
    switch( mSystemType ) {
		case SYSTEM_TYPE_MONTE_CARLO_CIRCLE:
			mMonteCarloSystem.increase( );
            updateMonteCarloTitle();
			break;
		case SYSTEM_TYPE_SINECOSINE_FUNCTION:
            mSineCosineFunction.increaseA();
            updateSineConsineTitle();

			break;
		case SYSTEM_TYPE_CUBIC_FUNCTION:
            mCubicFunction.increase();
            updateCubicFunctionTitle();

			break;
		case SYSTEM_TYPE_STUDENT_RECORD_MANAGER:
			break;
	}
}

void MY_SYSTEM_APP::decrease()
{
    switch( mSystemType ) {
		case SYSTEM_TYPE_MONTE_CARLO_CIRCLE:
			mMonteCarloSystem.decrease();
            updateMonteCarloTitle();
			break;
		case SYSTEM_TYPE_SINECOSINE_FUNCTION:
            mSineCosineFunction.decreaseA();
            updateSineConsineTitle();
			break;
		case SYSTEM_TYPE_CUBIC_FUNCTION:
            mCubicFunction.decrease();
            updateCubicFunctionTitle();
			break;
		case SYSTEM_TYPE_STUDENT_RECORD_MANAGER:
			break;
	}
}

void MY_SYSTEM_APP::increaseRadius()
{
    switch( mSystemType ) {
		case SYSTEM_TYPE_MONTE_CARLO_CIRCLE:
			mMonteCarloSystem.increaseRadius( );
            updateMonteCarloTitle();
			break;
		case SYSTEM_TYPE_SINECOSINE_FUNCTION:
			break;
		case SYSTEM_TYPE_CUBIC_FUNCTION:
			break;
		case SYSTEM_TYPE_STUDENT_RECORD_MANAGER:
			break;
	}
}

void MY_SYSTEM_APP::decreaseRadius()
{
    switch( mSystemType ) {
		case SYSTEM_TYPE_MONTE_CARLO_CIRCLE:
			mMonteCarloSystem.decreaseRadius( );
            updateMonteCarloTitle();
			break;
		case SYSTEM_TYPE_SINECOSINE_FUNCTION:
			break;
		case SYSTEM_TYPE_CUBIC_FUNCTION:
			break;
		case SYSTEM_TYPE_STUDENT_RECORD_MANAGER:
			break;
	}
}

void MY_SYSTEM_APP::handle_key01()
{
        switch( mSystemType ) {
		case SYSTEM_TYPE_MONTE_CARLO_CIRCLE:
			break;
		case SYSTEM_TYPE_SINECOSINE_FUNCTION:
            mSineCosineFunction.increaseB();
            updateSineConsineTitle();

			break;
		case SYSTEM_TYPE_CUBIC_FUNCTION:
			break;
		case SYSTEM_TYPE_STUDENT_RECORD_MANAGER:
			break;
	}
}

void MY_SYSTEM_APP::handle_key02()
{
        switch( mSystemType ) {
		case SYSTEM_TYPE_MONTE_CARLO_CIRCLE:
			break;
		case SYSTEM_TYPE_SINECOSINE_FUNCTION:
            mSineCosineFunction.decreaseB();
            updateSineConsineTitle();

			break;
		case SYSTEM_TYPE_CUBIC_FUNCTION:
			break;
		case SYSTEM_TYPE_STUDENT_RECORD_MANAGER:
			break;
	}

}

void MY_SYSTEM_APP::handle_key03()
{
        switch( mSystemType ) {
		case SYSTEM_TYPE_MONTE_CARLO_CIRCLE:
			break;
		case SYSTEM_TYPE_SINECOSINE_FUNCTION:
            mSineCosineFunction.decreaseSampleNum();
            updateSineConsineTitle();
			break;
		case SYSTEM_TYPE_CUBIC_FUNCTION:
			break;
		case SYSTEM_TYPE_STUDENT_RECORD_MANAGER:
			break;
	}
}

void MY_SYSTEM_APP::handle_key04()
{
        switch( mSystemType ) {
		case SYSTEM_TYPE_MONTE_CARLO_CIRCLE:
			break;
		case SYSTEM_TYPE_SINECOSINE_FUNCTION:
            mSineCosineFunction.increaseSampleNum();
            updateSineConsineTitle();

			break;
		case SYSTEM_TYPE_CUBIC_FUNCTION:
			break;
		case SYSTEM_TYPE_STUDENT_RECORD_MANAGER:
			break;
	}

}

void MY_SYSTEM_APP::askForInput( )
{
	switch( mSystemType ) {
		case SYSTEM_TYPE_MONTE_CARLO_CIRCLE:
			mMonteCarloSystem.askForInput( );
			break;
		case SYSTEM_TYPE_SINECOSINE_FUNCTION:
			mSineCosineFunction.askForInput( );
			break;
		case SYSTEM_TYPE_CUBIC_FUNCTION:
			mCubicFunction.askForInput( );
            updateCubicFunctionTitle();
			break;
		case SYSTEM_TYPE_STUDENT_RECORD_MANAGER:
			mStudentRecordManager.askForInput( );
			break;
	}
}

void MY_SYSTEM_APP::updateMonteCarloTitle( )
{
    string title;
    string result;
    ostringstream strs;
    ostringstream strs_int;

    double pi;
    int numSamples;
    title = "SYSTEM_TYPE_MONTE_CARLO_SIMULATION";

    mMonteCarloSystem.reset( );
    pi = mMonteCarloSystem.computePI( );
    strs << pi;
    title = title + "  pi:";
    title = title + strs.str();
    numSamples = mMonteCarloSystem.getNumSamples();
    strs_int << numSamples;
    title = title + "  #Samples:";
    title = title + strs_int.str();
    glutSetWindowTitle(title.data());
}

void MY_SYSTEM_APP::updateSineConsineTitle( )
{
    string title;
    string result;
    ostringstream strs;
    ostringstream strs_d;

    title = "SYSTEM_TYPE_SINECOSINE_FUNCTION (a*cos(b*x)) ";

    //mSineCosineFunction.reset( );

    {
    int numSamples = mSineCosineFunction.getNumOfSamples();
    strs_d.str("");
    strs_d.clear();
    
    strs_d << numSamples;
    title = title + "  #Samples:";
    title = title + strs_d.str();
    }

    {
    double a = mSineCosineFunction.getA();
    strs_d.str("");
    strs_d.clear();
    strs_d.precision(5);
    strs_d << a;
    title = title + "  a:";
    title = title + strs_d.str();
    }

    {
    double b = mSineCosineFunction.getB();
    strs_d.str("");
    strs_d.clear();
    strs_d.precision(5);
    strs_d << b;
    title = title + "  b:";
    title = title + strs_d.str();
    }

    //
    glutSetWindowTitle(title.data());
}

void MY_SYSTEM_APP::updateCubicFunctionTitle()
{
    string title;
    string result;
    ostringstream strs;
    ostringstream strs_d;

    title = "SYSTEM_TYPE_CUBIC_FUNCTION  ";

   

    {
    double a = mCubicFunction.getA();
    strs_d.str("");
    strs_d.clear();
    strs_d.precision(5);
    strs_d << a;
    title = title + "  a:";
    title = title + strs_d.str();
    }

    {
    double b = mCubicFunction.getB();
    strs_d.str("");
    strs_d.clear();
    strs_d.precision(5);
    strs_d << b;
    title = title + "  b:";
    title = title + strs_d.str();
    }

    {
    double c = mCubicFunction.getC();
    strs_d.str("");
    strs_d.clear();
    strs_d.precision(5);
    strs_d << c;
    title = title + "  c:";
    title = title + strs_d.str();
    }

    {
    double d = mCubicFunction.getD();
    strs_d.str("");
    strs_d.clear();
    strs_d.precision(5);
    strs_d << d;
    title = title + "  d:";
    title = title + strs_d.str();
    }
    //
    glutSetWindowTitle(title.data());
}

bool MY_SYSTEM_APP::specialFunc(int key, int x, int y)
{
    string title;
	//cout << "special key:" << key << endl;

	switch( key ) {
	case GLUT_KEY_F1:
		mSystemType = SYSTEM_TYPE_MONTE_CARLO_CIRCLE;
		updateMonteCarloTitle();
        cout << "mSystemType = SYSTEM_TYPE_MONTE_CARLO_CIRCLE" << endl;
		break;
	case GLUT_KEY_F2:
		mSystemType = SYSTEM_TYPE_SINECOSINE_FUNCTION;
		updateSineConsineTitle();
        cout << "mSystemType = SYSTEM_TYPE_SINECOSINE_FUNCTION" << endl;
		break;
	case GLUT_KEY_F3:
		mSystemType = SYSTEM_TYPE_CUBIC_FUNCTION;
        //title = "SYSTEM_TYPE_CUBIC_FUNCTION";
        //glutSetWindowTitle(title.data( ));
		cout << "mSystemType = SYSTEM_TYPE_CUBIC_FUNCTION" << endl;
        updateCubicFunctionTitle();
		break;
    case GLUT_KEY_F4:
		mSystemType = SYSTEM_TYPE_STUDENT_RECORD_MANAGER;
		title = "SYSTEM_TYPE_STUDENT_RECORD_MANAGER";
        glutSetWindowTitle(title.data( ));
        cout << "mSystemType = SYSTEM_TYPE_STUDENT_RECORD_MANAGER" << endl;

		break;
	}
	return true;
}

bool MY_SYSTEM_APP::handleKeyEvent( unsigned char key )
{
	bool flgHandled = false;
	switch ( key ) {
		case 's':
		case 'S': //fall through
			showMyStudentInfo( );
			break;
		case 'i':
		case 'I':
			askForInput( );
			break;
		case 'g':
		case 'G':
			mFlgShow_Grid = !mFlgShow_Grid;
			break;
        case 'n':
            decreaseRadius();
            break;
        case 'm':
            increaseRadius();
            break;
        case '>':
            increase();
            break;
        case '<':
            decrease();
            break;
		case 'v':
			decreaseRadius( );
			break;
		case 'b':
			increaseRadius( );
			break;
            case '1':
                handle_key01();
                break;
            case '2':
                handle_key02();
                break;
			case '3':
                handle_key03();
                break;
            case '4':
                handle_key04();
                break;
	}
	return flgHandled;
}

bool MY_SYSTEM_APP::mouseMotionFunc( int mx, int my )
{
	static vector3 color( 1.0, 0.0, 0.0 );
	if ( mMouseButton == GLUT_LEFT_BUTTON ) {
		//cout << "mouseMotionFunc GLUT_LEFT_BUTTON" << endl;
		float x, y, z;
		mCamera->getCoordinates( x, y, z, (float) mx, (float) my );

		float rf = (rand()%1000)/1000.0f*0.5f;
		color += vector3(0.1f, 0.07f, 0.11f*rf);
		//clickAt( (int) x, (int) z, color );

	} else {
		//if ( mPickedObj == 0 ) {
		return FREE_CANVAS_2D::mouseMotionFunc( mx, my );
		//}
	}

	//cout << "here 5" << endl;

	//float x, y, z;
	//mCamera->getCoordinates( x, y, z, mx, my );
	//cout << "Set Position XZ:" << x << "\t" << z << endl;
	return true;
}

bool MY_SYSTEM_APP::mouseFunc( int button, int state, int mx, int my )
{
	//cout << "button:" << button << endl;
	//if ( mPickedObj == 0 || button == GLUT_MIDDLE_BUTTON ) {
	//if ( button == 3 || button == 4 ) {

	float x, y, z;
	mCamera->getCoordinates( x, y, z, (float) mx, (float) my );

	vector3 color( 1.0, 0.0, 0.0 );
	mMouseButton = button;
	if ( button == GLUT_LEFT_BUTTON ) {
		//clickAt( (int) x, (int) z, color );
	} else {
		return FREE_CANVAS_2D::mouseFunc( button, state, mx, my );
	}
	return true;
}


bool MY_SYSTEM_APP::passiveMouseFunc( int mx, int my )
{
	float x, y, z;
	mCamera->getCoordinates( x, y, z, (float) mx, (float) my );
	return true;
}
// CODE: 2021/03/01. Do not delete this line.