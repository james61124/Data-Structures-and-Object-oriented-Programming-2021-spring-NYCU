#include "paintingSystemApp.h"

using namespace std;

PAINTING_SYSTEM_APP::PAINTING_SYSTEM_APP( )
{
	mPictureTexture = 0;
}

void PAINTING_SYSTEM_APP::initApp( )
{
	mFlgShow_Grid = true;

	//mImageWidth = 1024;
	//mImageHeight = 1024;
	mImageWidth = mImageHeight = 256;
	mPictureTexture = new dTEXTURE;
	//mPictureTexture->readFile( "./pic/piece01.jpg");
	mPictureTexture->createCheckBoxImage( mImageWidth, mImageHeight );
	mPictureTextureID = mPictureTexture->create( );
	setImagePtr( mPictureTexture->getImagePtr( ), mImageWidth, mImageHeight );
	cout << "PAINTING_SYSTEM_APP::initApp( )" << endl;
}

void PAINTING_SYSTEM_APP::update( )
{
	PAINTING_SYSTEM::update( );
	mPictureTexture->create( mPictureTextureID );
}




