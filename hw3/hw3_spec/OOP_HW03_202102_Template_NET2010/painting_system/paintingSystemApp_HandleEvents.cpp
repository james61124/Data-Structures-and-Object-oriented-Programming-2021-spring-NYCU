#include "paintingSystemApp.h"

using namespace std;

bool PAINTING_SYSTEM_APP::handleKeyEvent( unsigned char key )
{
	bool flgHandled = false;
	switch ( key ) {
		case 'g':
		case 'G':
			mFlgShow_Grid = !mFlgShow_Grid;
			break;
	}
	return flgHandled;
}

bool PAINTING_SYSTEM_APP::mouseMotionFunc( int mx, int my )
{
	static vector3 color( 1.0f, 0.0f, 0.0f );
	if ( mMouseButton == GLUT_LEFT_BUTTON ) {
		float x, y, z;
		cout << "here 1" << endl;
		mCamera->getCoordinates( x, y, z, (float)mx, (float)my );
		cout << "here 2" << endl;

		float rf = (rand()%1000)/1000.0f*0.5f;
		color += vector3(0.1f, 0.07f, 0.11f*rf);
		clickAt( (int)x, (int)z, color );
		cout << "here 3" << endl;

		mPictureTexture->create( mPictureTextureID );
		cout << "here 4" << endl;

	} else {
	//if ( mPickedObj == 0 ) {
		return FREE_CANVAS_2D::mouseMotionFunc( mx, my );
	//}
	}

		cout << "here 5" << endl;

	//float x, y, z;
	//mCamera->getCoordinates( x, y, z, mx, my );
	//cout << "Set Position XZ:" << x << "\t" << z << endl;
	return true;
}

bool PAINTING_SYSTEM_APP::mouseFunc( int button, int state, int mx, int my )
{
	cout << "button:" << button << endl;
	//if ( mPickedObj == 0 || button == GLUT_MIDDLE_BUTTON ) {
	//if ( button == 3 || button == 4 ) {

	float x, y, z;
	mCamera->getCoordinates( x, y, z, (float) mx, (float) my );

	vector3 color( 1.0, 0.0, 0.0 );
	mMouseButton = button;
	if ( button == GLUT_LEFT_BUTTON ) {
		cout << "x,z:" <<x << "\t" << z << endl;
		clickAt( (int)x, (int)z, color );
		cout << "222 x,z:" <<x << "\t" << z << endl;
		//
		mPictureTexture->create( mPictureTextureID );
		cout << "333 x,z:" <<x << "\t" << z << endl;

		//
	} else {
		return FREE_CANVAS_2D::mouseFunc( button, state, mx, my );
	}
		cout << "444 x,z:" <<x << "\t" << z << endl;

	//}
	return true;
}


bool PAINTING_SYSTEM_APP::passiveMouseFunc( int mx, int my )
{
		float x, y, z;
		mCamera->getCoordinates( x, y, z, (float)mx, (float)my );
		return true;
}