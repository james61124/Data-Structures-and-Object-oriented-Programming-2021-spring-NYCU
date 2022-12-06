#include <windows.h>
#include <iostream>
#include "texture.h"


using namespace std;

static GLfloat Gray[]= {0.5f,0.5f,0.5f,0.0f};

/*
GLfloat data[]= {
	// FRONT FACE
	0.0f, 0.0f,		-1.0f, -1.0f, .0f,
	1.0f, 0.0f,		+1.0f, -1.0f, .0f,
	1.0f, 1.0f,		+1.0f, +1.0f, .0f,
	0.0f, 1.0f,		-1.0f, +1.0f, .0f
};
*/

namespace {
GLfloat data_cube[]= {
	// FRONT FACE
	0.0f, 0.0f,		0.0f, 0.0f, .0f,
	1.0f, 0.0f,		1.0f, 0.0f, .0f,
	1.0f, 1.0f,		1.0f, 1.0f, .0f,
	0.0f, 1.0f,		0.0f, 1.0f, .0f
};

GLfloat data_ud[]= {
	// FRONT FACE
	0.0f, 1.0f,		0.0f, 0.0f, .0f,
	1.0f, 1.0f,		1.0f, 0.0f, .0f,
	1.0f, 0.0f,		1.0f, 1.0f, .0f,
	0.0f, 0.0f,		0.0f, 1.0f, .0f
};
};

namespace ns_opengl
{
	dTEXTURE::dTEXTURE()
	{
		m_TextureID = 0;
	}

	dTEXTURE::~dTEXTURE()
	{
	}

	GLint dTEXTURE::getInternalFormat( ) const
	{
		GLint internalformat = GL_RGB8;

		switch( m_Colorformat ) {
		case dIMAGE_COLOR_BW:
		break;
		case dIMAGE_COLOR_GRAY:
		internalformat = GL_RGB8;
		break;
		case dIMAGE_COLOR_RGB:
		internalformat = GL_RGB8;
		break;
		case dIMAGE_COLOR_RGBA:
		internalformat = GL_RGBA8;
		break;
		}
		
		return internalformat;
	}

	GLuint dTEXTURE::getGLComponentName(const unsigned int colorformat) const
	{
		GLuint texFormat = GL_RGB;
	
		switch(colorformat) {
		case dIMAGE_COLOR_BW: 
		break;
		case dIMAGE_COLOR_GRAY: 
		texFormat = GL_RGB;
		break;
		case dIMAGE_COLOR_RGB: 
		texFormat = GL_RGB;
		break;
		case dIMAGE_COLOR_RGBA:
		texFormat = GL_RGBA;
		break;
		}
		
		return texFormat;
	}

	void dTEXTURE::setUpTexture(GLuint id, int w, int h, GLuint texComp, GLuint texFormat, const void* image)
	{
		glBindTexture (GL_TEXTURE_2D, id);
		glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		//glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		//cout << "setUpTexture" << endl;
		//cout << "texComp:" << texComp << endl;
		//cout << "texFormat:" << texFormat << endl;
		//cout << "w, h:" << w << "\t" << h << endl;

		gluBuild2DMipmaps(
			GL_TEXTURE_2D,
			texComp, w, h, 
			texFormat, GL_UNSIGNED_BYTE, image);

	}


	// texture id is a positive integer
	GLuint dTEXTURE::create( )
	{
		glGenTextures( 1, &m_TextureID );
		return create( m_TextureID );
	}

	GLuint dTEXTURE::create( GLuint id )
	{
		m_TextureID = id;
		GLuint texComp;
		GLuint texFormat;
		texFormat = getGLComponentName( m_Colorformat );

		//texComp = GL_RGBA8;
		texComp = getInternalFormat( );

		setUpTexture( m_TextureID, m_ImageWidth, m_ImageHeight, texComp, texFormat, m_ImagePtr);
		return m_TextureID;
	}

	void dTEXTURE::use() const
	{
		//cout << "Use Texture..." << endl;
		glBindTexture (GL_TEXTURE_2D, m_TextureID );

		glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );
		glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glEnable(GL_TEXTURE_2D);
	}



	void dTEXTURE::begin() const
	{

	}

	void dTEXTURE::end() const
	{
		glDisable(GL_TEXTURE_2D);
	}


	void dTEXTURE::drawTexture( ) const
	{
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);
		int i;
		for (i=0;i<4; i++) {
			glTexCoord2f(
                data_cube[5*i], 
                data_cube[5*i+1]); 
			glVertex3f(
                data_cube[5*i+2], 
                data_cube[5*i+3], 
                data_cube[5*i+4]);
		}
		glEnd();
	}

	//
	// sx, sy, sz : 
	// scaling factors along x-, y- and z- axis, respectively.
	//
	void dTEXTURE::drawTexture(float x, float y, float z, float sx, float sy, float sz) const
	{
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);
		int i;
		
		for (i=0;i<4; i++) {
			glTexCoord2f( 
                data_cube[5*i], 
                data_cube[5*i+1] ); 
			glVertex3f( 
                data_cube[5*i+2]*sx+x, 
                data_cube[5*i+3]*sy+y, 
                data_cube[5*i+4]*sz+z );
		}
		
		glEnd();
	}

	//
	// sx, sy: 
	// scaling factors along x- and y-axis, respectively.
	//
	void dTEXTURE::drawTextureWithScale(float x, float y, float sx, float sy ) const
	{
		drawTexture( x, y, 0.0, sx, sy, 1.0 );
	}

	void dTEXTURE::drawTextureWithScale_FlipVertical(float x, float y, float sx, float sy ) const
	{
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);
		int i;
		
		for (i=0;i<4; i++) {
			glTexCoord2f( data_ud[5*i], data_ud[5*i+1] ); 
			glVertex3f( 
				data_ud[5*i+2]*sx+x, 
				data_ud[5*i+3]*sy+y, 
				0.0 );
		}
		
		glEnd();
	}

	void dTEXTURE::drawTextureWithScale_FlipVertical_XZ(float x, float z, float sx, float sz ) const
	{
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);
		int i;
		
		for (i=0;i<4; i++) {
			glTexCoord2f( data_ud[5*i], data_ud[5*i+1] ); 
			glVertex3f( 
				data_ud[5*i+2]*sx+x, 
				0.0,
				data_ud[5*i+3]*sz+z
				);
		}
		
		glEnd();
	}

	void dTEXTURE::drawTextureWithScale_XZ(float x, float z, float sx, float sz ) const
	{
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);
		int i;
		
		for (i=0;i<4; i++) {
			glTexCoord2f( data_ud[5*i], 1 - data_ud[5*i+1] ); 
			glVertex3f( 
				data_ud[5*i+2]*sx+x, 
				0.0,
				data_ud[5*i+3]*sz+z
				);
		}
		
		glEnd();
	}

	//
	// (x, y): corner position
	// (w, h): (width, height)
	//
	void dTEXTURE::drawTexture(int x, int y, int w, int h) const
	{

		if ( m_ImagePtr == NULL ) {
			//warning("dTEXTURE::Draw", "image is not loaded");
			return;
		}
		if ( m_TextureID == 0) return;

		glEnable(GL_TEXTURE_2D);

		glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, m_TextureID );
		drawTexture( );
		//----------------------------------------------------------

		glDisable(GL_TEXTURE_2D);
		//glFlush();
	}

};