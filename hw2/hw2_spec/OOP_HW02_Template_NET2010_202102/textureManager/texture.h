#ifndef _dTEXTURE_H_
#define _dTEXTURE_H_
#include "../headers.h"
#include "../imageReader/imageReader.h"


namespace ns_opengl
{
	class dTEXTURE: public Image 
	{
	protected:
		GLuint m_TextureID;
		//
		GLint getInternalFormat( ) const;
		GLuint getGLComponentName(const unsigned int colorformat) const;
		void setUpTexture(GLuint id, int w, int h, GLuint texComp, GLuint texFormat, const void* image);
	public:
		dTEXTURE();
		~dTEXTURE();
		GLuint create( );
		GLuint create( GLuint id );
		//
		void drawTexture(float x, float y, float z, float sx, float sy, float sz) const;
		void drawTexture( ) const;
		void drawTexture(int x, int y, int w, int h) const;
		void drawTextureWithScale(float x, float y, float sx, float sy) const;
		void drawTextureWithScale_FlipVertical(float x, float y, float sx, float sy ) const;
		void drawTextureWithScale_FlipVertical_XZ(float x, float z, float sx, float sz ) const;
		void drawTextureWithScale_XZ(float x, float z, float sx, float sz ) const;

		void use() const;
		void begin() const;
		void end() const;
	};

};

#endif
