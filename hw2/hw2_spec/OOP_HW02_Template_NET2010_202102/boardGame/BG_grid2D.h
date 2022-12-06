#ifndef _BG_GRID_2D_H_
#define _BG_GRID_2D_H_

#include <math.h>
#include "../primitives/grid2D.h"
#include "../primitives/vector3d.h"

class BG_GRID2D: public GRID_2D
{
public:
	BG_GRID2D( );
	BG_GRID2D( int nx, int ny );

	int checkWin( ) const;
	bool getWinningSequence( int &n, vector3 *p );
	void initGameCondition( int numofStones );

protected:
	int m_NumOfStones;
	bool checkWinCondition( int playerIndex ) const;
	bool check_horizontal( int playerIndex ) const;
	bool check_vertical( int playerIndex ) const;
	bool check_diagonal( int playerIndex ) const;
	bool check_diagonal_up( int playerIndex ) const;
	bool check_diagonal_down( int playerIndex ) const;
};

#endif