//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// Date: 2014/10/09
//
//incomplete
#include "painter.h"

namespace ns_opengl {
	OPENGL_PAINTER::OPENGL_PAINTER( )
	{
		setCanvasGridDimension( 10, 10 );
		setCanvasDimension(800, 800);
	}

	void OPENGL_PAINTER::setCanvasDimension( int w, int h )
	{
		m_CanvasWidth = w;
		m_CanvasHeight = h;
		setCanvasGridDimension( m_Grid_NX, m_Grid_NY );
	}

	void OPENGL_PAINTER::getCanvasDimension( int &w, int &h ) const
	{
		w = m_CanvasWidth;
		h = m_CanvasHeight;
	}
	void OPENGL_PAINTER::setCanvasGridDimension( unsigned int nx, unsigned int ny )
	{
		m_Grid_NX = nx;
		m_Grid_NY = ny;
		m_GridCellSize_DX = m_CanvasWidth/(float) nx;
		m_GridCellSize_DY = m_CanvasHeight/(float) ny;
	}
}
