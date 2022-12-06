#include "BG_grid2D.h"

BG_GRID2D::BG_GRID2D( )
{
	initGameCondition( 5 );
}

BG_GRID2D::BG_GRID2D( int nx, int ny ): GRID_2D(nx, ny)
{
	initGameCondition( 5 );
}

void BG_GRID2D::initGameCondition( int numofStones )
{
	m_NumOfStones = numofStones;
}

bool BG_GRID2D::checkWinCondition( int playerIndex ) const
{
	bool state = false;
	state = check_horizontal( playerIndex ) 
		|| check_vertical( playerIndex )
		|| check_diagonal( playerIndex );
	return state;
}

bool BG_GRID2D::check_horizontal( int playerIndex ) const
{
	bool state = false;
	int num;
	for (int j =0 ;j < ny; ++j ) {

		for (int i =0 ;i < nx - m_NumOfStones+1; ++i ) {
			if ( grid[i][j] != playerIndex ) continue;
			int ux = i + m_NumOfStones;
			num = 0;
			for ( int k = i; k < ux; ++k) {  
				if ( grid[k][j] == playerIndex ) {
					++num;
				}
			}
			if ( num == m_NumOfStones ) {
				state = true;
				break;
			}
		}
	}
	return state;
}

bool BG_GRID2D::check_vertical( int playerIndex ) const
{
	bool state = false;
	int num;
	for (int i =0 ;i < nx; ++i ) {

		for (int j =0 ;j < ny - m_NumOfStones+1; ++j ) {
			if ( grid[i][j] != playerIndex ) continue;
			int ux = j + m_NumOfStones;
			num = 0;
			for ( int k = j; k < ux; ++k) {  
				if ( grid[i][k] == playerIndex ) {
					++num;
				}
			}
			if ( num == m_NumOfStones ) {
				state = true;
				break;
			}
		}
	}
	return state;
}

bool BG_GRID2D::check_diagonal_up( int playerIndex ) const
{
	bool state = false;
	int num;
	for (int i =0 ;i < nx- m_NumOfStones+1; ++i ) {
		for (int j =0 ;j < ny - m_NumOfStones+1; ++j ) {
			if ( grid[i][j] != playerIndex ) continue;
			num = 0;
			for ( int k = 0; k < m_NumOfStones; ++k) {  
				if ( grid[i+k][j+k] == playerIndex ) {
					++num;
				}
			}
			if ( num == m_NumOfStones ) {
				state = true;
				break;
			}
		}
	}
	return state;
}

bool BG_GRID2D::check_diagonal_down( int playerIndex ) const
{
	bool state = false;
	int num;
	for (int i =0 ;i < nx- m_NumOfStones+1; ++i ) {
		for (int j =0 ;j < ny - m_NumOfStones+1; ++j ) {
			if ( grid[i][j+m_NumOfStones-1] != playerIndex ) continue;
			num = 0;
			for ( int k = 0; k < m_NumOfStones; ++k) {  
				if ( grid[i+k][j+m_NumOfStones-1-k] == playerIndex ) {
					++num;
				}
			}
			if ( num == m_NumOfStones ) {
				state = true;
				break;
			}
		}
	}
	return state;
}


bool BG_GRID2D::check_diagonal( int playerIndex ) const
{
	bool state = false;
	state = check_diagonal_up( playerIndex ) 
		|| check_diagonal_down( playerIndex );
	return state;
}

// return:
// -1 : no
// 0, 1: first player, second player
int BG_GRID2D::checkWin( ) const
{
	int winState = -1;

	bool state;
	state = checkWinCondition( 0 );
	if ( state ) {
		winState = 0;
	} else {
		state = checkWinCondition( 1 );
		if ( state ) {
			winState = 1;
		}
	}
	return winState;
}
