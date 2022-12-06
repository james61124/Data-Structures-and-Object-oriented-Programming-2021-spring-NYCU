#include <iostream>
#include "boardGameApp.h"
#include "../fileReader/fileReader.h"

using namespace ns_opengl;
using namespace std;

BOARD_GAME_APP::BOARD_GAME_APP( )
{
	mFlgShowGrid = true;
}

void BOARD_GAME_APP::initBGApp( )
{
	FILE_READER::readData( );
	FILE_READER::showContent( );

	string name;
	name = FILE_READER::getImageFileName( 0 );
	m_ImageReader[0].readFile((char*)name.data() );

	name = FILE_READER::getImageFileName( 1 );
	m_ImageReader[1].readFile((char*)name.data() );
	//
	//--------------------------------------------
	//Using textures
	name = FILE_READER::getImageFileName( 0 );
	m_Texture[0].readFile((char*)name.data() );
	name = FILE_READER::getImageFileName( 1 );
	m_Texture[1].readFile((char*)name.data() );
	m_Texture[0].create( );
	m_Texture[1].create( );

	//--------------------------------------------
	//

	//
	int nx, ny;
	FILE_READER::getDimension( nx, ny );

	setBoardGridDimension( nx, ny );
	setCanvasGridDimension( nx, ny );

}



void BOARD_GAME_APP::initApp( )
{
	initBGApp( );
	reset( );
}
void BOARD_GAME_APP::reshape( int w, int h )
{
	setCanvasDimension( w, h );
}

void BOARD_GAME_APP::setShowFlg_Grid( bool flg )
{
	mFlgShowGrid = flg;
}
void BOARD_GAME_APP::draw( int mouseX, int mouseY ) const
{

	int numBlocks = FILE_READER::getNumBlocks( );

	vector3 color = vector3( 1.0, 0.5, 0.0 );
	vector3 p;
	for (int i = 0; i < numBlocks; ++i ) {
		FILE_READER::getBlockCoordinates( i, p.x, p.y );
		drawOneBlock( (int)p.x, (int)p.y, color );
	}


	//---------------------------------------------
	float x0, y0, sx, sy;
	x0 = 0.0;
	y0 = 0.0;
	sx = 1.0;
	sy = 1.0;
	float point_size = 1.0;
	int iW, iH;
	m_ImageReader[0].getInfo( iW, iH );
	sx = m_GridCellSize_DX / (float) iW;
	sy = m_GridCellSize_DY / (float) iH;

	point_size = sx;
	if (sy > point_size ) point_size = sy;
	if ( point_size < 1.0 ) point_size = 1;
	point_size += 0.5;

	int numPieces;

	//Using texture. The scaling factors:
	float textSX, textSY;
	textSX = m_GridCellSize_DX;
	textSY = m_GridCellSize_DY;
	//-----------------------------------
	int winState = getWinState( );
	int imageIndex;
	for (int i = 0; i < 2; ++i ) {
		numPieces = getNumOfPieces( i );
		if ( winState != -1 ) {
			imageIndex = winState;
		} else {
			imageIndex = i;
		}
		for ( int j = 0; j < numPieces; ++j) {
			//cout << "." << textSX << "\t" << textSY << endl;
			getInfo( i, j, p );
			p.x = p.x*m_GridCellSize_DX;
			p.y = p.y*m_GridCellSize_DY;

			//m_ImageReader[imageIndex].draw_VerticalFlip( p.x, p.y, sx, sy, point_size );

			m_Texture[imageIndex].use( );
			//m_Texture[imageIndex].drawTextureWithScale( p.x, p.y, textSX, textSY );
			m_Texture[imageIndex].drawTextureWithScale_FlipVertical( p.x, p.y, textSX, textSY );
			m_Texture[imageIndex].end( );
		}
	}
	//---------------------------------------------
	int playerIndex = getCurPlayerIndex( );
	int my;
	my = m_CanvasHeight - mouseY - 1;
	m_ImageReader[playerIndex].draw_VerticalFlip( (float) mouseX, (float)my, sx, sy, point_size );

	if ( mFlgShowGrid ) drawGrid_Frame( );

	color = vector3( 1.0, 0.0, 0.0 );

}

void BOARD_GAME_APP::draw( ) const
{
	draw( mMouseX, mMouseY );
}



bool BOARD_GAME_APP::handleKeyEvent( unsigned char key )
{
	if ( key == 13 )
	{
		if ( getWinState( ) != -1 ) {
			reset( );
		}
	}
	return true;

}
bool BOARD_GAME_APP::mouseMotionFunc( int x, int y )
{
	return true;

}
bool BOARD_GAME_APP::mouseFunc( int button, int state, int x, int y )
{
	//
	int blockX;
	int blockY;
	bool flgSuccess = false;
	switch( button ) {
			case GLUT_LEFT_BUTTON:
				if (state == GLUT_DOWN) {
					if (getWinState( ) != 1) {

						blockX = (int) (x / (float)(m_CanvasHeight)*m_Grid_NX); 
						blockY = (int) ( (m_CanvasHeight - y - 1)/ (float)(m_CanvasHeight))*m_Grid_NY; 
						flgSuccess = putAt( blockX, blockY );

					}
				}

				break;
	}
	if ( flgSuccess ) {
		nextPlayer( );
	}

	/*
	bool flgwin = checkWin( );
	if ( flgwin ) {
		std::cout << "win" << std::endl;
		system("pause");
	}
	*/

	return true;
}

bool BOARD_GAME_APP::passiveMouseFunc( int x, int y )
{
	mMouseX = x;
	mMouseY = y;

	return true;
}

		bool BOARD_GAME_APP::specialFunc(int key, int x, int y)
		{
	
		switch( key ) {
			case GLUT_KEY_LEFT:
				break;
				case GLUT_KEY_RIGHT:
				break;
				case GLUT_KEY_UP:
					setShowFlg_Grid( true );
				break;
				case GLUT_KEY_DOWN:
					setShowFlg_Grid( false );
					
				break;
		}
		
		return true;
		}