//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// Date: 2014/10/09
//
#ifndef __BOARD_GAME_H_
#define __BOARD_GAME_H_

#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
#include "BG_grid2D.h"

class BOARD_GAME
{
protected:
	int m_PlayerIndexArr[16];
		int m_NumPlayers;
		int m_WhoseTurn;
		int m_MaxNumPieces;
		vector3 *m_PiecePos[2];
		int m_NumPieces[2];

		BG_GRID2D m_BG_Grid2D;
		int m_WinState;
public:
	BOARD_GAME( );
	void reset( );
	bool putAt( int x, int y );	// true: ok; false: cannot put
	void setFirstPlayer( int playerIndex );
	void nextPlayer( );
	int getCurPlayerIndex( ) const;
	int getNumOfPieces( int playerIndex ) const;
	void getInfo( int playerIndex, int pieceIndex, vector3 &p ) const;
	void setBoardGridDimension( int nx, int ny );
	int checkWin( );
	int getWinState( ) const;
};

#endif