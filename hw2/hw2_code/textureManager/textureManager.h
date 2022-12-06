//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// Date: 2014/10/14
//
#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__
#include "../headers.h"
#include "texture.h"

namespace ns_opengl
{
	class TEXTURE_MANAGER
	{
	private:
		static TEXTURE_MANAGER *_instance;
	protected:
		int mCurNumOfTextures;
		int mMaxNumOfTextures;
		std::string *mTextureImageFileNameArr;
		dTEXTURE *mTextureArr;

		void addTexture( int textureID, const std::string &imageFileName );
		

	public:
		TEXTURE_MANAGER( );
		void readConfig( const char *fileName );
		void loadAllTexturesFromFiles( );
		void bgn_use( int textureID ) const;
		void end_use( int textureID ) const;
		void draw( int textureID ) const;
		//
		static TEXTURE_MANAGER *instance( ) {
			if ( _instance == 0 ) {
				_instance = new TEXTURE_MANAGER;
			}
			return _instance;
		}
	};
};

#endif