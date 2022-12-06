#ifndef _dTEXTURE_TOOLS_H_
#define _dTEXTURE_TOOLS_H_
#include "../basic.h"
#include <GL/gl.h>
#include "image.h"
#include <GL/glext.h>
#include "../stdutil.h"
#include "../prmatools.h"
#include "../gltools.h"
#include "../obj3d/scene_obj_type.h"
#include "../obj3d/obj3d_tools.h"

class TEXTURE_GENERATOR {
private:
	pmDATA_TYPE obj_bounding_box[6];
	pmDATA_TYPE region_bounding_box[6];
	double ortho_frustum[6];
	//pmDATA_TYPE obj_texture_bounding_box[6];
	//pmDATA_TYPE region_texture_bounding_box[6];
	SCENE_OBJ *sobj;
	bObjRegion *region;
	int npixel_offset_height;
	int npixel_offset_width;
	//
	mutable GLfloat *original_img;
	mutable GLfloat *src_img, *dest_img;
	mutable GLfloat *mask_img;
	GLubyte *rgb_img;
	//
	GLint viewport[4];
	mutable GLint viewport_old[4];
	//
	mutable int flg_first_time;
	//
	void pushViewport() const;
	void popViewport() const;
	//
	void initVariables();
	void bgnDraw() const;
	void endDraw() const;
	//
	//
	void computeTextureCoords(float *txt, const pmDATA_TYPE *pos) const;
	void computeTextureCoords2D(float *txt, const pmDATA_TYPE *pos) const;
	//
	void computeOrthoFrustumForRegion();
	void computeRegionBoundingBox_ObjectSpace(bObjRegion *region);
	//
	void computeRegionBoundingBox_TextureSpace(bObjRegion *region);
	//
	void drawImage(const GLfloat *img) const;
	void drawSphereAtVertices(bObjRegion *region) const;
	void draw_PlanarRegion(bObjRegion *region) const;
	void draw_PlanarRegion_ObjectInTextureSpace(bObjRegion *region) const;
	//
	void draw_grayLevel_Disk(pmDATA_TYPE *pos, pmDATA_TYPE r, int flg_direction) const;
	void draw_grayLeveL_Disk_AtVertices() const;
	//
	void draw_LineSegment(pmDATA_TYPE *p0, pmDATA_TYPE *p1, pmDATA_TYPE r0, pmDATA_TYPE r1) const;
	void draw_LineSegment_AtBoundingEdges() const;
	//
	void computeTextureCoordsForRegion(bObjRegion *region);
	void computeTextureCoordsForRegion_TextureSpace(bObjRegion *region);
	//void compute_RegionTextureBoundingBox(bObjRegion *region);
	//
	GLuint EmptyTexture() const;
	//
	void draw_dyn_heat_diffusion_init() const;
	void draw_dyn_heat_diffusion() const;
public:
	TEXTURE_GENERATOR();
	void setObjRegion(SCENE_OBJ *sobj, bObjRegion *region);
	void setViewport(int x, int y, int w, int h);
	void draw() const;
	void draw_close() const;
	void draw_heat_diffusion() const;
	//
	void computeTextureCoordsForRegion();
	dTEXTURE_DB_ENTRY *createSimpleTexture() const;
	dTEXTURE_DB_ENTRY *createSimpleTexture_WithBumpMap() const;
	dTEXTURE_DB_ENTRY *createSimpleTexture_WithBumpMap_UsingHeat() const;
};

#endif