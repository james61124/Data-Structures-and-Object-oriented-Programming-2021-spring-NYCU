#include "grid2D.h"


GRID_2D::GRID_2D( )
{
	nx = 0; ny = 0;
	grid = 0;
	m_initValue = -1;
}
GRID_2D::GRID_2D( int nx, int ny )
{
	nx = 0; ny = 0;
	grid = 0;
	m_initValue = -1;

	setGridDimension( nx, ny );

}

void GRID_2D::reset( )
{
	initializeGridValue( m_initValue );
}

void GRID_2D::setGridDimension( int nx, int ny )
{
	if ( grid != 0) {
		for ( int i = 0; i < this->nx; ++i ) {
			delete [] grid[i];
		}
		delete [] grid;
	}
	this->nx = nx;
	this->ny = ny;
	grid = new int*[nx];
	for (int i = 0; i < nx; ++i ) {
		grid[i] = new int[ny];
	}

}

void GRID_2D::initializeGridValue( int value )
{
	m_initValue = value;
	for (int i = 0; i < nx; ++i ) {
		for (int j = 0; j < ny; ++j ) {
			grid[i][j] = value;
		}
	}
}

int GRID_2D::getValue( int x, int y ) const
{
	return grid[x][y];
}

void GRID_2D::set(int x, int y, int value)
{
	grid[x][y] = value;
}
