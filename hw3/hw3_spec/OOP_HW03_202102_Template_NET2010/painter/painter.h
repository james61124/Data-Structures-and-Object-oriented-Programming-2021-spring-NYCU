//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// Date: 2014/10/09
//
#ifndef __OPENGL_PAINTER_H_
#define __OPENGL_PAINTER_H_
#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
#include "../imageReader/imageReader.h"

namespace ns_opengl {

	class OPENGL_PAINTER
	{
	protected:

	public:
		OPENGL_PAINTER( );
		void setCanvasGridDimension( unsigned int nx, unsigned int ny );
		void setCanvasDimension( int w, int h );
		void getCanvasDimension( int &w, int &h ) const;
		void drawBlocks( );
		//
		// draw one block at position (ix, iy)
		void drawOneBlock(int ix, int iy, const vector3 &color = vector3(1.0, 1.0, 1.0) ) const;
		//
		// draw an empty block at position (ix, iy)
		void drawOneBlock_Wire(int ix, int iy, const vector3 &color = vector3(1.0, 1.0, 1.0) ) const;
		//
		// draw one block with a frame at position (ix, iy)
		void drawOneBlock_Frame(int ix, int iy, 
			const vector3 &bcolor = vector3(1.0f, 1.0f, 1.0f),  
			const vector3 &fcolor = vector3(0.9f, 0.6f, 0.0f)) const;
		//
		// draw a wireframe for the grid
		void drawGrid_Frame( const vector3 &fcolor = vector3(0.9f, 0.9f, 0.5f) ) const;

		//----------------------------
		//Virtual methods here
		//virtual void draw( ) const;
		//----------------------------
	protected:
		int m_CanvasWidth, m_CanvasHeight;
		int m_Grid_NX, m_Grid_NY;	// the grid dimension along the x-axis and the y-axis
		float m_GridCellSize_DX, m_GridCellSize_DY; // the grid cell size along the x-axis and the y-axis


	};
};

#endif