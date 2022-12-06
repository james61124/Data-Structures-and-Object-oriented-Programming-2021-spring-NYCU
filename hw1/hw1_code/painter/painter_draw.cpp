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

		void OPENGL_PAINTER::drawOneBlock(int ix, int iy, const vector3 &color) const
	{
		
		glColor3f( color.r, color.g, color.b );
		vector3 p, q;
		p.x = ix*m_GridCellSize_DX;
		p.y = iy*m_GridCellSize_DY;
		q = p + vector3( m_GridCellSize_DX, m_GridCellSize_DY, 0.0 );

		glBegin( GL_QUADS );
		glVertex2f( p.x, p.y );
		glVertex2f( q.x, p.y );
		glVertex2f( q.x, q.y );
		glVertex2f( p.x, q.y );
		glEnd( );
	}

		void OPENGL_PAINTER::drawOneBlock_Wire(int ix, int iy, const vector3 &color) const
	{
		
		glColor3f( color.r, color.g, color.b );
		vector3 p, q;
		p.x = ix*m_GridCellSize_DX;
		p.y = iy*m_GridCellSize_DY;
		q = p + vector3( m_GridCellSize_DX, m_GridCellSize_DY, 0.0 );

		glBegin( GL_LINE_LOOP );
		glVertex2f( p.x, p.y );
		glVertex2f( q.x, p.y );
		glVertex2f( q.x, q.y );
		glVertex2f( p.x, q.y );
		glEnd( );
	}

		void OPENGL_PAINTER::drawOneBlock_Frame(int ix, int iy, 
			const vector3 &bcolor, 
			const vector3 &fcolor) const
	{
		
		glColor3f( bcolor.r, bcolor.g, bcolor.b );
		vector3 p, q;
		p.x = ix*m_GridCellSize_DX;
		p.y = iy*m_GridCellSize_DY;
		q = p + vector3( m_GridCellSize_DX, m_GridCellSize_DY, 0.0 );

		glBegin( GL_QUADS );
		glVertex2f( p.x, p.y );
		glVertex2f( q.x, p.y );
		glVertex2f( q.x, q.y );
		glVertex2f( p.x, q.y );
		glEnd( );

		glColor3f( fcolor.r, fcolor.g, fcolor.b );
		glBegin( GL_LINE_LOOP );
		glVertex2f( p.x, p.y );
		glVertex2f( q.x, p.y );
		glVertex2f( q.x, q.y );
		glVertex2f( p.x, q.y );
		glEnd( );

	}

	void OPENGL_PAINTER::drawGrid_Frame( const vector3 &fcolor ) const
	{
		glColor3f( fcolor.r, fcolor.g, fcolor.b );

		float x = 0.0;
		glBegin( GL_LINES );
		for (int i = 0; i <= m_Grid_NX; ++i, x += m_GridCellSize_DX ) {
			glVertex2f( x, 0.0f );
			glVertex2f( x, (float) m_CanvasHeight );
		}

		float y = 0.0;
		for (int j = 0; j <= m_Grid_NY; ++j, y += m_GridCellSize_DY ) {
			glVertex2f( 0.0, y );
			glVertex2f( (float) m_CanvasWidth, y );
		}

		glEnd( );
	}


	void OPENGL_PAINTER::drawBlocks( )
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin( GL_LINES );
		glVertex3f( -100, -100, 0.0 );
		glVertex3f( 100, 100, 0.0 );
		glEnd( );

		drawOneBlock( 1, 1 );
	}


//	void OPENGL_PAINTER::draw( ) const 
//	{
//	}
};