//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// Date: 2014/10/12
//
#include <fstream>
#include <iostream>
#include <string>
#include "fileReader.h"
#define DATA_FILE_NAME	"data.txt"

#define MAX_BLOCKS	1024

using namespace std;
std::string FILE_READER::configFileName = "";
int FILE_READER::m_aDimension[2] = {1, 1};
int FILE_READER::m_NumBlocks = 0;
int FILE_READER::m_CurNumBlocks = 0;
vector3 FILE_READER::m_BlockColor01 = vector3( 1.0, 0.0, 0.0 );
vector3 FILE_READER::m_BlockColor02 = vector3( 0.0, 0.0, 1.0 );

vector3 *FILE_READER::m_paBlocks = new vector3[MAX_BLOCKS];

std::string *FILE_READER::image_fileName = new std::string[16];

int FILE_READER::m_NumOfImages = 0;
int FILE_READER::m_NumRules = 0;
RULE *FILE_READER::m_aRule = new RULE[16];
//
FILE_READER::FILE_READER()
{

}

void FILE_READER::readData()
{
	using namespace std;
	std::ifstream *fp;
	fp = new std::ifstream(DATA_FILE_NAME, ios::in | ios::binary);
	if (fp == 0 || fp->fail()) {
		cout << "Cannot open data file:" << DATA_FILE_NAME << endl;
		return;
	}

	std::string key;
	while (!fp->eof()) {
		*fp >> key;

		if (key.compare("DIM") == 0) {
			*fp >> m_aDimension[0] >> m_aDimension[1];

		}

		if (key.compare("NumOfBlocks") == 0) {
			*fp >> m_NumBlocks;

		}

		if (key.compare("BlockColor01") == 0) {
			*fp >> m_BlockColor01.r >> m_BlockColor01.g >> m_BlockColor01.b;

		}
				if (key.compare("BlockColor02") == 0) {
			*fp >> m_BlockColor02.r >> m_BlockColor02.g >> m_BlockColor02.b;

		}

		if (key.compare("Block") == 0) {
			if ( m_CurNumBlocks >= MAX_BLOCKS ) {
				cout << "There are too many blocks:" << m_CurNumBlocks << endl;
				cout << "MAX_BLOCKS:" << MAX_BLOCKS << endl;
			}
			*fp >> m_paBlocks[m_CurNumBlocks].x >> m_paBlocks[m_CurNumBlocks].y;
			++m_CurNumBlocks;

		}

		if ( key.compare("Image") == 0 ) {
			string name;
			int index;
			*fp >> index >> name;
			image_fileName[index] = name;
			++m_NumOfImages;
		}

		if ( key.compare("WinRule") == 0) {
			string name;
			int num;
			*fp >> name >> num;
			//
			m_aRule[m_NumRules].ruleName = name;
			m_aRule[m_NumRules].num = num;
			//
			++m_NumRules;
		}
	}

	if ( m_CurNumBlocks != m_NumBlocks ) 
	{
		cout << "The number of blocks is not correct!" << endl;
		cout << "m_NumBlocks:" << m_NumBlocks << endl;
		cout << "m_CurNumBlocks:" << m_CurNumBlocks << endl;
	}
	fp->close( );
}

void FILE_READER::getDimension( int &nx, int &ny )
{
	nx = m_aDimension[0];
	ny = m_aDimension[0];

}
int FILE_READER::getNumBlocks( )
{
	return m_NumBlocks;
}

//
// float& : pass-by-reference
//
void FILE_READER::getBlockCoordinates(int index, float &x, float &y)
{
	x = y = 0;
	if ( index <0 || index >= m_NumBlocks ) 
	{
		cout << "invalud index. FILE_READER::getBlockCoordinates. Error!" << endl;
		return;
	}
	x = m_paBlocks[index].x;
	y = m_paBlocks[index].y;
}

void FILE_READER::showContent( )
{
	cout << "BGN FILE_READER::showContent-------------" << endl;
	cout << "configFileName:" << configFileName << endl;
	cout << "Dim:" << m_aDimension[0] << "\t" << m_aDimension[1] << endl;
	cout << "m_NumBlocks:" << m_NumBlocks << endl;
	cout << "m_CurNumBlocks:" << m_CurNumBlocks << endl;
	cout << "m_BlockColor01:" << m_BlockColor01.r << "\t" << m_BlockColor01.g << "\t" << m_BlockColor01.b << endl;
	cout << "m_BlockColor02:" << m_BlockColor02.r << "\t" << m_BlockColor02.g << "\t" << m_BlockColor02.b << endl;

	cout << "	Block info" << endl;
	for (int i = 0; i < m_CurNumBlocks; ++i ) {
		cout << "	block (x, y):" << m_paBlocks[i].x << "\t" << m_paBlocks[i].y << endl;
	}

	
		cout << "Win Rules:" << endl;
			for (int i = 0; i < m_NumRules; ++i) {
cout << m_aRule[i].ruleName << "\t" << m_aRule[i].num << endl;
			}

	cout << "END FILE_READER::showContent-------------" << endl;

}

	std::string FILE_READER::getImageFileName( int imageIndex )
	{
		return image_fileName[imageIndex];
	}