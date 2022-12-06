#include <fstream>
#include <iostream>
#include <string>
#include "textureManager.h"

using namespace std;

namespace ns_opengl
{
void TEXTURE_MANAGER::readConfig( const char *fileName )
{
	int textureID;
	ifstream *fp;
	fp = new ifstream(fileName, ios::in | ios::binary);
	if (fp == 0 || fp->fail( ) ) {
		cout << "CS_ENVIRONMENT::read. Cannot open data file:" << fileName << endl;
		return;
	}

	bool flg_valid = false;
	std::string key;
	std::string imageFileName;
	while (!fp->eof()) {
		*fp >> key;
		
		if (key.compare("TEXTURES") == 0) {
			flg_valid = true;
		}
		if ( flg_valid == false ) {
			cout << "The data file is not for defining textures." << endl;
			break;
		}

		if (key.compare("BEGIN") == 0) {
			*fp >> textureID;
		}
		if (key.compare("IMAGE") == 0) {
			*fp >> imageFileName;
		}

		if (key.compare("END") == 0) {
			addTexture( textureID, imageFileName );
		}


		key.empty( );
	}

	fp->close( );
	
}

void TEXTURE_MANAGER::addTexture( int textureID, const std::string &imageFileName )
{
	mTextureImageFileNameArr[ textureID ] = imageFileName;
}

void TEXTURE_MANAGER::loadAllTexturesFromFiles( )
{
	for ( int i = 0; i < mMaxNumOfTextures; ++i ) {
		cout << "Texture image file name:" <<  mTextureImageFileNameArr[i] << endl;
		if ( mTextureImageFileNameArr[i].size( ) > 0 ) {
			bool flg = mTextureArr[i].readFile( mTextureImageFileNameArr[i].data( ) );
			if ( flg ) mTextureArr[i].create( );
		}
	}
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

};