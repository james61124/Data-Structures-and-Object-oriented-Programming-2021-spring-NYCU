#include <windows.h>
#include <iostream>
#include "textureManager.h"

using namespace std;
namespace ns_opengl
{
	TEXTURE_MANAGER *TEXTURE_MANAGER::_instance = 0;

TEXTURE_MANAGER::TEXTURE_MANAGER( )
{	
	mMaxNumOfTextures = 16;
	mCurNumOfTextures = 0;
	mTextureArr = new dTEXTURE[mMaxNumOfTextures];
	mTextureImageFileNameArr = new string[mMaxNumOfTextures];
}


void TEXTURE_MANAGER::bgn_use( int textureID ) const
{
	mTextureArr[textureID].use( );
}

void TEXTURE_MANAGER::end_use( int textureID ) const
{
	mTextureArr[textureID].end( );
}

void TEXTURE_MANAGER::draw( int textureID ) const
{
	mTextureArr[textureID].use( );
	mTextureArr[textureID].drawTextureWithScale_FlipVertical( 0.0, 0.0, 100.0, 100.0 );
	mTextureArr[textureID].end( );
}

};