#include "texture_DB_entry.h"

dTEXTURE_DB_ENTRY::dTEXTURE_DB_ENTRY()
{
	initVariables();
}


dTEXTURE_DB_ENTRY::dTEXTURE_DB_ENTRY(const char *filename)
{
	initVariables();
	this->filename = filename;
	dTEXTURE *texture = new dTEXTURE;
	if (texture->ReadFile(filename)) {
		texture->RemapColors(2,1,0);
		texture->Create();
		this->texture = texture;
	} else {
		texture->CloseFile();
		delete texture;
	}
}

void dTEXTURE_DB_ENTRY::setTexture(dTEXTURE *texture)
{
	this->texture = texture;
}

void dTEXTURE_DB_ENTRY::initVariables()
{
	texture = NULL;
	flg_loaded = FALSE;
	filename = "";
	filename_bump = "";
}