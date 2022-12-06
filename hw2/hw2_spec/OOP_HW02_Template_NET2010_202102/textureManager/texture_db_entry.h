#ifndef __TEXTURE_DB_ENTRY_H__
#define __TEXTURE_DB_ENTRY_H__
#include "texture.h"

class dTEXTURE_DB_ENTRY {
private:
	int flg_loaded;
	void initVariables();
public:
	std::string filename;
	std::string filename_bump;
	int id;
	dTEXTURE *texture;
	dTEXTURE_DB_ENTRY *prev, *next;
	dTEXTURE_DB_ENTRY();
	dTEXTURE_DB_ENTRY(const char *filename);
	void setTexture(dTEXTURE *texture);
};

#endif