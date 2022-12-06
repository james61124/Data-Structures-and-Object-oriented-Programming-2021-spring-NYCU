//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// Date: 2014/10/12
//
#ifndef __FILE_READER_H__
#define __FILE_READER_H__

#include <string>
#include "../primitives/vector3d.h"

struct RULE
{
	std::string ruleName;
	int num;
};

class FILE_READER {
protected:
	static std::string configFileName;
	static std::string *image_fileName;
	static int m_NumOfImages;
	static int m_aDimension[2];
	static int m_NumBlocks;		// expected number of blocks
	static int m_CurNumBlocks;	// current number of blocks
	static vector3 *m_paBlocks;
	static vector3 m_BlockColor01;
	static vector3 m_BlockColor02;
	static RULE *m_aRule;
	static int m_NumRules;
public:
	FILE_READER();
	static void readData();
	static void getDimension( int &nx, int &ny );
	static int getNumBlocks( );
	static void getBlockCoordinates(int index, float &x, float &y);
	static void showContent( );
	static std::string getImageFileName( int imageIndex );

};

#endif