#include "texture_tools.h"
#include "image_processing_simple_tools.h"

TEXTURE_GENERATOR::TEXTURE_GENERATOR()
{
	initVariables();
}

void TEXTURE_GENERATOR::initVariables()
{
	flg_first_time = TRUE;
	sobj = NULL;
	region = NULL;
	npixel_offset_height = 5;
	npixel_offset_width = 5;
	viewport[0] = 28;
	viewport[1] = 88;
	viewport[2] = 400;
	viewport[3] = 400;
	//viewport[2] = 512;
	//viewport[3] = 512;
	ortho_frustum[0] = -100.0;
	ortho_frustum[1] = 100.0;
	ortho_frustum[2] = -100.0;
	ortho_frustum[3] = 100.0;
	ortho_frustum[4] = -100.0;
	ortho_frustum[5] = 100.0;
	//
	int w = viewport[2];
	int h = viewport[3];
	//
	original_img = new GLfloat[w*h*4];
	src_img = new GLfloat[w*h*4];
	dest_img = new GLfloat[w*h*4];
	rgb_img = new GLubyte[w*h*3];
	mask_img = new GLfloat[w*h*4];
}

void TEXTURE_GENERATOR::computeOrthoFrustumForRegion()
{
	double he, we;
	double w0 = region_bounding_box[1] - region_bounding_box[0];
	double h0 = region_bounding_box[3] - region_bounding_box[2];
	we = (w0*npixel_offset_width) / (viewport[2] - 2*npixel_offset_width);
	he = (h0*npixel_offset_height) / (viewport[3] - 2*npixel_offset_height);
	
	//we = 0;
	//he = 0;

	double d = (region_bounding_box[5] - region_bounding_box[4])*0.05;
	d += 0.05;
	//cout << "D:" << d << endl;
	ortho_frustum[0] = region_bounding_box[0] - we;
	ortho_frustum[1] = region_bounding_box[1] + we;
	ortho_frustum[2] = region_bounding_box[2] - he;
	ortho_frustum[3] = region_bounding_box[3] + he;
	ortho_frustum[4] = region_bounding_box[4] - d;
	ortho_frustum[5] = region_bounding_box[5] + d;

//cout << "ortho_frustum Box" << ortho_frustum[0] << "\t" << ortho_frustum[1] << "\t" << ortho_frustum[2] << "\t" << ortho_frustum[3] << "\t" << ortho_frustum[4] << "\t" << ortho_frustum[5] << endl;
}

void TEXTURE_GENERATOR::computeRegionBoundingBox_ObjectSpace(bObjRegion *region)
{
	if (region == NULL) return;
	if (region->tri_list == NULL) return;

	bSetAABB(region_bounding_box, region->tri_list->f->point[0]->pos);

	for (const oTriangleList *fl = region->tri_list; fl!=NULL; fl = fl->next) {
		const oTriangle *f = fl->f;
		const oPoint *v0, *v1, *v2;
		v0 = f->point[0];
		v1 = f->point[1];
		v2 = f->point[2];
		bUpdateAABB(region_bounding_box, v0->pos);
		bUpdateAABB(region_bounding_box, v1->pos);
		bUpdateAABB(region_bounding_box, v2->pos);
	}

	//cout << "Bounding Box" << region_bounding_box[0] << "\t" << region_bounding_box[1] << "\t" << region_bounding_box[2] << "\t" << region_bounding_box[3] << "\t" << region_bounding_box[4] << "\t" << region_bounding_box[5] << endl;
}

void TEXTURE_GENERATOR::computeRegionBoundingBox_TextureSpace(bObjRegion *region)
{
	if (region == NULL) return;
	if (region->tri_list == NULL) return;

	const float *txt_ptr = region->tri_list->f->txt_coords0;
	pmDATA_TYPE txt_pos[3];
	txt_pos[0] = txt_ptr[0];
	txt_pos[1] = txt_ptr[1];
	txt_pos[2] = 0.0;
	mapToActualTextureCoords_Region(txt_pos, txt_pos, region);
	bSetAABB(region_bounding_box, txt_pos);

	for (const oTriangleList *fl = region->tri_list; fl!=NULL; fl = fl->next) {
		const oTriangle *f = fl->f;
		txt_ptr = f->txt_coords0;
		txt_pos[0] = txt_ptr[0]; txt_pos[1] = txt_ptr[1];
		mapToActualTextureCoords_Region(txt_pos, txt_pos, region);
		bUpdateAABB(region_bounding_box, txt_pos);
		txt_ptr = f->txt_coords1;
		txt_pos[0] = txt_ptr[0]; txt_pos[1] = txt_ptr[1];
		mapToActualTextureCoords_Region(txt_pos, txt_pos, region);
		bUpdateAABB(region_bounding_box, txt_pos);
		txt_ptr = f->txt_coords2;
		txt_pos[0] = txt_ptr[0]; txt_pos[1] = txt_ptr[1];
		mapToActualTextureCoords_Region(txt_pos, txt_pos, region);
		bUpdateAABB(region_bounding_box, txt_pos);
	}

	cout << "Bounding Box (txt)" << region_bounding_box[0] << "\t" << region_bounding_box[1] << "\t" << region_bounding_box[2] << "\t" << region_bounding_box[3] << "\t" << region_bounding_box[4] << "\t" << region_bounding_box[5] << endl;
}

void TEXTURE_GENERATOR::setObjRegion(SCENE_OBJ *sobj, bObjRegion *region)
{
	this->sobj = sobj;
	this->region = region;
	flg_first_time = TRUE;
	//computeRegionBoundingBox_ObjectSpace(region);
	computeRegionBoundingBox_TextureSpace(region);
	computeOrthoFrustumForRegion();
}

void TEXTURE_GENERATOR::setViewport(int x, int y, int w, int h)
{
	viewport[0] = x;
	viewport[1] = y;
	viewport[2] = w;
	viewport[3] = h;
	computeOrthoFrustumForRegion();
}
//
void TEXTURE_GENERATOR::pushViewport() const
{
	glGetIntegerv(GL_VIEWPORT, viewport_old);
}

void TEXTURE_GENERATOR::popViewport() const
{
	glViewport(viewport_old[0], viewport_old[1], viewport_old[2], viewport_old[3]);
}


void TEXTURE_GENERATOR::drawSphereAtVertices(bObjRegion *region) const
{
	if (region == NULL) return;
	if (region->tri_list == NULL) return;

	for (oTriangleList *fl = region->tri_list; fl!=NULL; fl = fl->next) {
		oTriangle *f = fl->f;
		const oPoint *v0, *v1, *v2;
		
		v0 = f->point[0];
		v1 = f->point[1];
		v2 = f->point[2];
		const pmDATA_TYPE *p = v0->pos;
		glPushMatrix();
		glTranslatef(p[0], p[1], p[2]);
		glutSolidSphere(0.3, 15, 15);
		glPopMatrix();
	}
}

void TEXTURE_GENERATOR::draw_PlanarRegion(bObjRegion *region) const
{
	if (!(sobj && region)) return;
	//cout << "TEXTURE_GENERATOR::draw_PlanarRegion" << endl;
	//sobj->obj->drawUsingFaceNormal_Texture(region, 0x0);
	sobj->obj->draw_Region(region, 0x0);


}

void TEXTURE_GENERATOR::draw_PlanarRegion_ObjectInTextureSpace(bObjRegion *region) const
{
	if (!(sobj && region)) return;
	//cout << "TEXTURE_GENERATOR::draw_PlanarRegion" << endl;
	//sobj->obj->drawUsingFaceNormal_Texture(region, 0x0);
	sobj->obj->draw_Region_ObjectInTextureSpace(region, 0x0);
	//
	glEnable(GL_BLEND);
	draw_grayLeveL_Disk_AtVertices();
	//draw_LineSegment_AtBoundingEdges();
	glDisable(GL_BLEND);
}

void TEXTURE_GENERATOR::bgnDraw() const
{
	pushViewport();
	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	//glClearColor(0.0, 0.0, 0.0, 0.0);
	//glClear(GL_COLOR_BUFFER_BIT);
	//
	
	glOrtho(ortho_frustum[0], ortho_frustum[1], ortho_frustum[2], ortho_frustum[3], -ortho_frustum[5], -ortho_frustum[4]);
	//
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor4f(0.0, 0.0, 0.0, 0.0);
	
	glBegin(GL_QUADS);
	glVertex3f(ortho_frustum[0], ortho_frustum[2], -ortho_frustum[5]);
	glVertex3f(ortho_frustum[1], ortho_frustum[2], -ortho_frustum[5]);
	glVertex3f(ortho_frustum[1], ortho_frustum[3], -ortho_frustum[5]);
	glVertex3f(ortho_frustum[0], ortho_frustum[3], -ortho_frustum[5]);
	glEnd();
	
}

void TEXTURE_GENERATOR::endDraw() const
{
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	popViewport();
}


void TEXTURE_GENERATOR::draw() const
{
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	
	bgnDraw();
	glColor4f(1.0, 1.0, 1.0, 0.8);
	//draw_PlanarRegion(region);
	
	draw_PlanarRegion_ObjectInTextureSpace(region);
	//drawSphereAtVertices(region);
	endDraw();
}

void TEXTURE_GENERATOR::draw_close() const
{
	draw();
	int x = viewport[0];
	int y = viewport[1];
	int w = viewport[2];
	int h = viewport[3];
	
	glReadPixels(x, y, w, h, GL_RGBA, GL_FLOAT, src_img);
	glFinish();
	
	//imgpro_setConnectionType(imgpro_CONNECTION_TYPE_4);
	imgpro_setConnectionType(imgpro_CONNECTION_TYPE_8);
	
	
//	imgpro_stools_open(src_img, w, h, GL_RGBA, dest_img);
//	imgpro_stools_open(dest_img, w, h, GL_RGBA, src_img);
	imgpro_stools_open(src_img, w, h, GL_RGBA, dest_img);
	imgpro_stools_open(dest_img, w, h, GL_RGBA, src_img);
	
	
	imgpro_stools_close(src_img, w, h, GL_RGBA, dest_img);
	imgpro_stools_close(dest_img, w, h, GL_RGBA, src_img);
	imgpro_stools_close(src_img, w, h, GL_RGBA, dest_img);
	imgpro_stools_close(dest_img, w, h, GL_RGBA, src_img);
//	imgpro_stools_close(src_img, w, h, GL_RGBA, dest_img);
//	imgpro_stools_close(dest_img, w, h, GL_RGBA, src_img);
	
	bgnDraw();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20, 20, -20, 20, -20, 20);
	
	glRasterPos2i(-20, -20);
	glDisable(GL_BLEND);
	glDrawPixels(w, h, GL_RGBA, GL_FLOAT, src_img);
	glFinish();
	endDraw();
	//delete [] src_img;
	//delete [] dest_img;
}

void TEXTURE_GENERATOR::draw_heat_diffusion() const
{
	if (flg_first_time) {
		//cout << "draw_dyn_heat_diffusion_init()..." << endl;
		draw_dyn_heat_diffusion_init();
		flg_first_time = FALSE;
	} else {
		draw_dyn_heat_diffusion();	
	}
}

void TEXTURE_GENERATOR::computeTextureCoords(float *txt, const pmDATA_TYPE *p) const
{
	txt[0] = (p[0] - ortho_frustum[0]) / (ortho_frustum[1] - ortho_frustum[0]);
	txt[1] = (p[1] - ortho_frustum[2]) / (ortho_frustum[3] - ortho_frustum[2]);
	if (txt[0] < 0.0 ) {
		txt[0] = 0.0;
	} else if (txt[0] > 1.0) {
		txt[0] = 1.0;
	}

	if (txt[1] < 0.0 ) {
		txt[1] = 0.0;
	} else if (txt[1] > 1.0) {
		txt[1] = 1.0;
	}
}

// p is 2D.
void TEXTURE_GENERATOR::computeTextureCoords2D(float *txt, const pmDATA_TYPE *p) const
{
	txt[0] = (p[0] - ortho_frustum[0]) / (ortho_frustum[1] - ortho_frustum[0]);
	txt[1] = (p[1] - ortho_frustum[2]) / (ortho_frustum[3] - ortho_frustum[2]);
	if (txt[0] < 0.0 ) {
		txt[0] = 0.0;
	} else if (txt[0] > 1.0) {
		txt[0] = 1.0;
	}

	if (txt[1] < 0.0 ) {
		txt[1] = 0.0;
	} else if (txt[1] > 1.0) {
		txt[1] = 1.0;
	}
}

void TEXTURE_GENERATOR::computeTextureCoordsForRegion(bObjRegion *region)
{
	if (region == NULL) return;
	if (region->tri_list == NULL) return;

	for (oTriangleList *fl = region->tri_list; fl!=NULL; fl = fl->next) {
		oTriangle *f = fl->f;
		const oPoint *v0, *v1, *v2;
		float txt0[2];
		float txt1[2];
		float txt2[2];
		v0 = f->point[0];
		v1 = f->point[1];
		v2 = f->point[2];
		computeTextureCoords(txt0, v0->pos);
		computeTextureCoords(txt1, v1->pos);
		computeTextureCoords(txt2, v2->pos);
		f->setTextureCoords(txt0, txt1, txt2);
	}
}

void TEXTURE_GENERATOR::computeTextureCoordsForRegion_TextureSpace(bObjRegion *region)
{
	if (region == NULL) return;
	if (region->tri_list == NULL) return;

	/*
	float txt_x = region->texture_x;
	float txt_y = region->texture_y;
	float txt_sx = region->texture_sx;
	float txt_sy = region->texture_sy;
	*/

	for (oTriangleList *fl = region->tri_list; fl!=NULL; fl = fl->next) {
		oTriangle *f = fl->f;
		pmDATA_TYPE *v0, *v1, *v2;
		float txt0[2];
		float txt1[2];
		float txt2[2];
		v0 = f->txt_coords0;
		v1 = f->txt_coords1;
		v2 = f->txt_coords2;
		pmDATA_TYPE v00[2], v01[2], v02[2];
		mapToActualTextureCoords_Region(v00, v0, region);
		mapToActualTextureCoords_Region(v01, v1, region);
		mapToActualTextureCoords_Region(v02, v2, region);
		computeTextureCoords2D(txt0, v00);
		computeTextureCoords2D(txt1, v01);
		computeTextureCoords2D(txt2, v02);
		f->setTextureCoords(txt0, txt1, txt2);
	}
	region->texture_x = 0.0;
	region->texture_y = 0.0;
	region->texture_sx = 1.0;
	region->texture_sy = 1.0;
}

void TEXTURE_GENERATOR::computeTextureCoordsForRegion()
{
	//computeTextureCoordsForRegion(region);
	computeTextureCoordsForRegion_TextureSpace(region);
}

 
GLuint TEXTURE_GENERATOR::EmptyTexture() const
{
	// Create An Empty Texture
	GLuint txtnumber;											// Texture ID
	unsigned int* data;											// Stored Data
	int w = viewport[2];
	int h = viewport[3];
	// Create Storage Space For Texture Data (w x h x 4)
	data = (unsigned int*)new GLuint[((w * h)* 4 * sizeof(unsigned int))];
	ZeroMemory(data,((w * h)* 4 * sizeof(unsigned int)));	// Clear Storage Memory

	glGenTextures(1, &txtnumber);								// Create 1 Texture
	glBindTexture(GL_TEXTURE_2D, txtnumber);					// Bind The Texture
	glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, data);						// Build Texture Using Information In data
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	delete [] data;												// Release data

	return txtnumber;											// Return The Texture ID
}

dTEXTURE_DB_ENTRY *TEXTURE_GENERATOR::createSimpleTexture() const
{
	if (region == NULL) return NULL;
	dTEXTURE_DB_ENTRY *db = NULL;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//draw();
	draw_close();
	
	glFinish();
	GLuint txt_id = EmptyTexture();
	glBindTexture(GL_TEXTURE_2D,txt_id);
	// Bind To The Blur Texture

	// Copy Our ViewPort To The Blur Texture (From 0,0 To 128,128... No Border)
	//glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, viewport[0], viewport[1], viewport[2], viewport[3], 0);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, viewport[0], viewport[1], viewport[2], viewport[3], 0);
	glFinish();
	db = new dTEXTURE_DB_ENTRY;
	dTEXTURE *texture = new dTEXTURE;
	texture->CreateFromExistingTexture(txt_id);
	db->setTexture(texture);
	return db;
}

dTEXTURE_DB_ENTRY *TEXTURE_GENERATOR::createSimpleTexture_WithBumpMap() const
{
	if (region == NULL) return NULL;
	dTEXTURE_DB_ENTRY *db = NULL;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//draw();
	draw_close();
	int w = viewport[2];
	int h = viewport[3];
	glReadPixels(viewport[0], viewport[1], w, h, GL_RGB, GL_UNSIGNED_BYTE, rgb_img);
	imgpro_change_to_gray_RGB8(rgb_img, w, h);
	imgpro_scale(rgb_img, w, h, 0x7f, 0x0, 0xff);
	glFinish();
	GLuint txt_id = EmptyTexture();
	glBindTexture(GL_TEXTURE_2D,txt_id);
	// Bind To The Blur Texture

	// Copy Our ViewPort To The Blur Texture (From 0,0 To 128,128... No Border)
	//glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, viewport[0], viewport[1], viewport[2], viewport[3], 0);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, viewport[0], viewport[1], viewport[2], viewport[3], 0);
	//-------------------------------------
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    //glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	//-------------------------------------
	glFinish();
	db = new dTEXTURE_DB_ENTRY;
	dTEXTURE *texture = new dTEXTURE;
	texture->CreateFromExistingTexture(txt_id);
	texture->LoadBumpMap_RGB8(rgb_img, viewport[2], viewport[3]);
	db->setTexture(texture);
	return db;
}



dTEXTURE_DB_ENTRY *TEXTURE_GENERATOR::createSimpleTexture_WithBumpMap_UsingHeat() const
{
	if (region == NULL) return NULL;
	dTEXTURE_DB_ENTRY *db = NULL;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//draw();
	//draw_heat_diffusion();
	drawImage(src_img);
	int w = viewport[2];
	int h = viewport[3];
	glReadPixels(viewport[0], viewport[1], w, h, GL_RGB, GL_UNSIGNED_BYTE, rgb_img);
	//imgpro_stools_average(dest_img, w, h, GL_RGBA, rgb_img);
	//
	imgpro_change_to_gray_RGB8(rgb_img, w, h);
	imgpro_scale(rgb_img, w, h, 0x7f, 0x0, 0xff);

	glFinish();
	GLuint txt_id = EmptyTexture();
	glBindTexture(GL_TEXTURE_2D,txt_id);
	drawImage(original_img);
	// Bind To The Blur Texture

	// Copy Our ViewPort To The Blur Texture (From 0,0 To 128,128... No Border)
	//glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, viewport[0], viewport[1], viewport[2], viewport[3], 0);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, viewport[0], viewport[1], viewport[2], viewport[3], 0);
	//-------------------------------------
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    //glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	//-------------------------------------
	glFinish();
	db = new dTEXTURE_DB_ENTRY;
	dTEXTURE *texture = new dTEXTURE;
	texture->CreateFromExistingTexture(txt_id);
	texture->LoadBumpMap_RGB8(rgb_img, viewport[2], viewport[3]);
	db->setTexture(texture);
	return db;
}