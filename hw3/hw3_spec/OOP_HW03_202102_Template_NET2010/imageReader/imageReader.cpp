//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// Date: 2014/10/14
//
#include "imageReader.h"
#include <windows.h>
#include <iostream>
#include <math.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>


using namespace std;
namespace {
	//-----------------------------------------------------------------------------
	// Name: DXUtil_ConvertAnsiStringToWide()
	// Desc: This is a UNICODE conversion utility to convert a CHAR string into a
	//       WCHAR string. cchDestChar defaults -1 which means it 
	//       assumes strDest is large enough to store strSource
	//-----------------------------------------------------------------------------
	VOID ConvertAnsiStringToWide( WCHAR* wstrDestination, const CHAR* strSource, 
		int cchDestChar )
	{
		if( wstrDestination==NULL || strSource==NULL )
			return;


		if( cchDestChar == -1 )
			cchDestChar = (int) strlen(strSource)+1;


		MultiByteToWideChar( 0, 0, strSource, -1, 
			wstrDestination, cchDestChar-1 );


		wstrDestination[cchDestChar-1] = 0;

	}
};

namespace {
	bool flg_setup_IL = false;
	unsigned int m_imgId;
	void setup_IL() 
	{
		if (flg_setup_IL) return;
		flg_setup_IL = true;
		ilInit();
		iluInit();
		ilutInit();
		ilutRenderer( ILUT_OPENGL );
		ilGenImages( 1, &m_imgId );
		ilBindImage( m_imgId );
	}
};
namespace ns_opengl
{
	bool Image::readFile( const char *a_File )
	{

		if ( a_File == 0 ) return false;
		cout << "Bgn Image:: " << a_File << endl;
		setup_IL();
		ILboolean success;
		ILenum error;

		//setup_IL();
#ifdef _UNICODE
		wchar_t ILFileName[256];
		ConvertAnsiStringToWide(ILFileName, a_File, -1);
		success = ilLoadImage( ILFileName );

#else
		success = ilLoadImage( (char*)a_File );
#endif


		if( !success ){

			while ((error = ilGetError()) !=IL_NO_ERROR) {
				printf("Error %d: %s\n", error, iluErrorString( error ));

			}
			system("pause");
			exit(1);
			//return false;
		}

		cout << "Opened file:" << a_File << endl;
		m_ImageWidth = ilGetInteger( IL_IMAGE_WIDTH );
		m_ImageHeight = ilGetInteger( IL_IMAGE_HEIGHT );
		//int sw = 512, sh;
		int sw = 256, sh;
		//sh = mImageHeight[imageIndex]*sw/mImageWidth[imageIndex];
		sw = sh = 256;
		iluScale(sw, sh, 24);
		m_ImageWidth = ilGetInteger( IL_IMAGE_WIDTH );
		m_ImageHeight = ilGetInteger( IL_IMAGE_HEIGHT );



		int format = ilGetInteger( IL_IMAGE_FORMAT );

		/*
#define dIMAGE_COLOR_BW 0
#define dIMAGE_COLOR_GRAY 1
#define dIMAGE_COLOR_RGB 2
#define dIMAGE_COLOR_RGBA 3
*/
		m_Colorformat = dIMAGE_COLOR_RGB;
		switch(format) {
	 case IL_RGBA:
	 case IL_BGRA:
		 m_Colorformat = dIMAGE_COLOR_RGBA;
		 m_BytePerPixel = 4;
		 break;
	 case IL_RGB:
		 m_Colorformat = dIMAGE_COLOR_RGB;
		 m_BytePerPixel = 3;
		 break;
		}

		m_TotalBytes = m_ImageWidth * m_ImageHeight*m_BytePerPixel;
		m_ImagePtr = (unsigned char*) new unsigned char[m_TotalBytes];

		cout << "mImageWidth:" << m_ImageWidth << endl;
		cout << "mImageHeight:" << m_ImageHeight << endl;
		cout << "mBytePerPixel:" << m_BytePerPixel << endl;
		cout << "mTotalBytes:" << m_TotalBytes << endl;

		ILubyte *p = ilGetData();

		unsigned char *dp = (unsigned char *)m_ImagePtr;
		unsigned char *sp = (unsigned char *)p;

		switch(format) {
		case  IL_RGBA:
		case IL_BGRA:
			for (int i = 0; i < m_TotalBytes; i++) {
				dp[i] = sp[i];
			}
			break;

		case  IL_RGB:
			for (int i = 0, j = 0; i <  m_TotalBytes; i++) {
				dp[i] = sp[i];

			}
			break;
		}

		cout << "End Image::Read_JPG" << endl;

		return true;
	}

	void Image::createCheckBoxImage( int w, int h )
	{

		m_ImageWidth = w;
		m_ImageHeight = h;
		m_BytePerPixel = 3;
		m_TotalBytes = m_ImageWidth * m_ImageHeight*m_BytePerPixel;
		m_ImagePtr = new unsigned char[m_TotalBytes];

		m_Colorformat = dIMAGE_COLOR_RGB;
		m_BytePerPixel = 3;

		int i;
		for (  i = 0; i < m_ImageWidth * m_ImageHeight; ++i ) {
			m_ImagePtr[i*3+0] = 0x0;
			m_ImagePtr[i*3+1] = 0x0;
			m_ImagePtr[i*3+2] = 255;

		}

		i = 0;
		while ( i < m_ImageHeight ) {
		//for ( i = 0; i < m_ImageHeight; ++i ) {
			for ( int j = 0; j < m_ImageWidth; ++j ) {
				int index;
				index = i*m_ImageWidth+j;
				index *= 3;
				m_ImagePtr[index] = 255;
				m_ImagePtr[index+1] = 255;
				m_ImagePtr[index+2] = 0;
			}
			++i;
			if ( (i%10) == 0) {
				//cout << ".........." << endl;
				i += 10;
			}
			//cout << "i:" << i << endl;
		}

	}

	void Image::getInfo( int &w, int &h ) const
	{
		w = m_ImageWidth;
		h = m_ImageHeight;

	}

	void Image::decrease_Brightness( )
	{
		--m_Intensity_Offset;
		if ( m_Intensity_Offset < -255 ) m_Intensity_Offset = -255;
	}
		void Image::increase_Brightness( )
		{
			++m_Intensity_Offset;
			if ( m_Intensity_Offset > 255 ) m_Intensity_Offset = 255;
		}

    //
    // get (red,green,blue) components at pixel (x,y)
    //
    void Image::getPixelColor(int x, int y, float &r, float &g, float &b) const
    {

        if (m_ImagePtr == 0) return;

        int i = x;
        if (i<0) i = 0;
        else if (i >= m_ImageWidth) i = m_ImageWidth-1;

        int j = y;
        if (j<0) j = 0;
        else if (j >= m_ImageHeight) j = m_ImageHeight-1;

				int offset = 0;
				offset = j*m_ImageWidth*m_BytePerPixel +i*m_BytePerPixel;

				//cout << "offset:" << offset << endl;
				r = (float) m_ImagePtr[offset+0];
				g = (float) m_ImagePtr[offset+1];
				b = (float) m_ImagePtr[offset+2];

				//cout << "r:" << r << endl;

				r /= 255.0;
				g /= 255.0;
				b /= 255.0;

				if (r < 0.0 ) r = 0.0;
				else if (r > 1.0) r = 1.0;

				if (g < 0.0 ) g = 0.0;
				else if (g > 1.0) g = 1.0;

				if (b < 0.0 ) b = 0.0;
				else if (b > 1.0) b = 1.0;

    }


	//sx, sz are scaling factors
	void Image::drawXY(float x0, float y0, float sx, float sy, float point_size, float z, bool xDir, bool yDir ) const
	{
		if (m_ImagePtr == 0) return;

		glPointSize(point_size);
		glBegin(GL_POINTS);
		for (int j = 0; j < m_ImageHeight; ++j) {
			float y;
			if ( yDir == 1 ) {
				y = y0 + ( m_ImageHeight - j - 1 )*sy;
			} else {
				y = y0 + j*sy;
			}
			for (int i = 0; i < m_ImageWidth; ++i) {
				float x;
				if ( xDir == 1 ) {
					x = x0 + ( m_ImageWidth - i - 1 )*sx;
				} else {
					x = x0 + i*sx;
				}
				float r = 1.0, g = 1.0, b = 1.0; //red, green, blue
				int offset = 0;
				offset = j*m_ImageWidth*m_BytePerPixel +i*m_BytePerPixel;

				//cout << "offset:" << offset << endl;
				r = (float) m_ImagePtr[offset+0];
				g = (float) m_ImagePtr[offset+1];
				b = (float) m_ImagePtr[offset+2];

				//cout << "r:" << r << endl;

				r += m_Intensity_Offset;
				g += m_Intensity_Offset;
				b += m_Intensity_Offset;
				r /= 255.0;
				g /= 255.0;
				b /= 255.0;

				if (r < 0.0 ) r = 0.0;
				else if (r > 1.0) r = 1.0;

				if (g < 0.0 ) g = 0.0;
				else if (g > 1.0) g = 1.0;

				if (b < 0.0 ) b = 0.0;
				else if (b > 1.0) b = 1.0;

				glColor3f(r, g, b); //set colour
				glVertex3f( x, y, z ); //define vertex position
			}
		}
		glEnd();
	}
	//sx, sz are scaling factors
	void Image::drawXZ(float x0, float y0, float sx, float sy, float point_size, float z, bool xDir, bool yDir ) const
	{
		if (m_ImagePtr == 0) return;

		glPointSize(point_size);
		glBegin(GL_POINTS);
		for (int j = 0; j < m_ImageHeight; ++j) {
			float y;
			if ( yDir == 1 ) {
				y = y0 + ( m_ImageHeight - j - 1 )*sy;
			} else {
				y = y0 + j*sy;
			}
			for (int i = 0; i < m_ImageWidth; ++i) {
				float x;
				if ( xDir == 1 ) {
					x = x0 + ( m_ImageWidth - i - 1 )*sx;
				} else {
					x = x0 + i*sx;
				}
				float r = 1.0, g = 1.0, b = 1.0; //red, green, blue
				int offset = 0;
				offset = j*m_ImageWidth*m_BytePerPixel +i*m_BytePerPixel;

				//cout << "offset:" << offset << endl;
				r = (float) m_ImagePtr[offset+0];
				g = (float) m_ImagePtr[offset+1];
				b = (float) m_ImagePtr[offset+2];

				//cout << "r:" << r << endl;

				r += m_Intensity_Offset;
				g += m_Intensity_Offset;
				b += m_Intensity_Offset;
				r /= 255.0;
				g /= 255.0;
				b /= 255.0;

				if (r < 0.0 ) r = 0.0;
				else if (r > 1.0) r = 1.0;

				if (g < 0.0 ) g = 0.0;
				else if (g > 1.0) g = 1.0;

				if (b < 0.0 ) b = 0.0;
				else if (b > 1.0) b = 1.0;

				glColor3f(r, g, b); //set colour
				//glVertex3f( x, y, z ); //define vertex position
				glVertex3f( x, z, y ); //define vertex position
			}
		}
		glEnd();
	}
	void Image::draw_VerticalFlip(float x0, float y0, float sx, float sy, float point_size, float z ) const
	{
		
		drawXY( x0, y0, sx, sy, point_size, z, 0, 1 );
		
	}

    void Image::draw_VerticalFlip_XZ(float x0, float y0, float sx, float sy, float point_size, float z ) const
	{
		
		drawXZ( x0, y0, sx, sy, point_size, z, 0, 1 );
		
	}

	void Image::draw_HorizontalFlip(float x0, float y0, float sx, float sy, float point_size, float z ) const
	{
		
		drawXY( x0, y0, sx, sy, point_size, z, 1, 0 );
		
	}



};