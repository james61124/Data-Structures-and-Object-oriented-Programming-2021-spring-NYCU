//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// Date: 2014/10/14
//
#ifndef __IMAGE_READER_H__
#define __IMAGE_READER_H__
#include "../headers.h"

#define dIMAGE_COLOR_BW 0
#define dIMAGE_COLOR_GRAY 1
#define dIMAGE_COLOR_RGB 2
#define dIMAGE_COLOR_RGBA 3

namespace ns_opengl
{
	class Image {
	protected:
		int m_Colorformat;
		int m_BytePerPixel;
		int m_TotalBytes;
		int m_ImageWidth;
		int m_ImageHeight;
		unsigned char *m_ImagePtr;
		//
		int m_Intensity_Offset;
		//
	public:
		Image() {
			
			m_ImageWidth = 0;
			m_ImageHeight = 0;
			m_ImagePtr = 0;
			m_Intensity_Offset = 0;
			
		}
		bool readFile( const char *fileName);
		void createCheckBoxImage( int w, int h );
		void getInfo( int &w, int &h ) const;
        void getPixelColor(int x, int y, float &r, float &g, float &b) const;
		unsigned char *getImagePtr( ) const { return m_ImagePtr; }

		~Image() {
			
			if (m_ImagePtr) {
				delete [] m_ImagePtr;
			
			m_ImagePtr = 0;
			}
		}
		void drawXY(float x0, float y0, float sx, float sy, float point_size, float z = 0.0, bool xDir = 0, bool yDir = 0 ) const;
		void drawXZ(float x0, float y0, float sx, float sy, float point_size, float z = 0.0, bool xDir = 0, bool yDir = 0 ) const;
		
        void draw_VerticalFlip_XZ(float x0, float y0, float sx, float sy, float point_size, float z = 0.0 ) const;

        void draw_VerticalFlip(float x0, float y0, float sx, float sy, float point_size, float z = 0.0 ) const;
		void draw_HorizontalFlip(float x0, float y0, float sx, float sy, float point_size, float z = 0.0 ) const;

		void decrease_Brightness( );
		void increase_Brightness( );
	};
}; //namespace ns_myProgram

#endif