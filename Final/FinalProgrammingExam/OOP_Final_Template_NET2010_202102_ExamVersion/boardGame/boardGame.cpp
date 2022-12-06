#include <iostream>
#include "boardGame.h"

using namespace std;

BOARD_GAME::BOARD_GAME( )
{
	m_NumPlayers = 2;
	m_PlayerIndexArr[0] = 0;
	m_PlayerIndexArr[1] = 1;

	m_WhoseTurn = 0;
	m_MaxNumPieces = 1024;
	m_PiecePos[0] = new vector3[m_MaxNumPieces];
	m_PiecePos[1] = new vector3[m_MaxNumPieces];
	m_NumPieces[0] = 0;
	m_NumPieces[1] = 0;
	//
	m_BG_Grid2D.setGridDimension( 10, 10);	// test
	m_BG_Grid2D.setGridDimension( 10, 20);	// test

	reset( );
}

void BOARD_GAME::reset( )
{
	m_NumPieces[0] = 0;
	m_NumPieces[1] = 0;
	m_WhoseTurn = 0;
	m_WinState = -1;
m_BG_Grid2D.reset( );
}

//return 
// -1: no
// 0: first person
// 1: second person
int BOARD_GAME::checkWin( )
{
	if ( m_WinState != -1 ) return m_WinState;
	m_WinState = m_BG_Grid2D.checkWin( );
	return m_WinState;
}

int BOARD_GAME::getWinState( ) const
{
	return m_WinState;
}
void BOARD_GAME::setBoardGridDimension( int nx, int ny )
{
m_BG_Grid2D.setGridDimension( nx, ny );
m_BG_Grid2D.initializeGridValue( -1 );
}

//
// true: can put; 
// false: cannot put
bool BOARD_GAME::putAt( int x, int y )
	{
		cout << "putAt (x, y):" << x << "\t" << y  << endl;
		int playerIndex = m_PlayerIndexArr[m_WhoseTurn];
		int pieceIndex = m_NumPieces[playerIndex];
		int value = m_BG_Grid2D.getValue( x, y );
		if ( value != -1 ) return false;

		m_PiecePos[playerIndex][pieceIndex].x = (float) x;
		m_PiecePos[playerIndex][pieceIndex].y = (float) y;
		++m_NumPieces[playerIndex];
		//
		m_BG_Grid2D.set( x, y, playerIndex );

		return true;
	}		

	void BOARD_GAME::setFirstPlayer( int playerIndex )
	{
		m_WhoseTurn = 0;
		for (int i = 0; i < m_NumPlayers; ++i ) {
			if ( m_PlayerIndexArr[i] == playerIndex ) { m_WhoseTurn = i; break; }
		}
	}

	void BOARD_GAME::nextPlayer( )
	{
		m_WhoseTurn = ( m_WhoseTurn + 1)%m_NumPlayers;
	}

	int BOARD_GAME::getCurPlayerIndex( ) const
	{
		return m_PlayerIndexArr[ m_WhoseTurn ];
	}

	int BOARD_GAME::getNumOfPieces( int playerIndex ) const
	{
		return m_NumPieces[playerIndex];
	}

	void BOARD_GAME::getInfo( int playerIndex, int pieceIndex, vector3 &p ) const
	{
		p.x = m_PiecePos[playerIndex][pieceIndex].x;
		p.y = m_PiecePos[playerIndex][pieceIndex].y;
	}
