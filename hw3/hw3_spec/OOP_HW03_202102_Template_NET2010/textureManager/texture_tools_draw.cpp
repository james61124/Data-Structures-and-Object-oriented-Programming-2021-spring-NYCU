#include "texture_tools.h"
#include "image_processing_simple_tools.h"
#include "../obj3d/basic_mem.h"
#include "../mvector.h"

void TEXTURE_GENERATOR::drawImage(const GLfloat *img) const
{
	int x = viewport[0];
	int y = viewport[1];
	int w = viewport[2];
	int h = viewport[3];

	bgnDraw();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20, 20, -20, 20, -20, 20);
	
	glRasterPos2i(-20, -20);
	glDisable(GL_BLEND);
	glDrawPixels(w, h, GL_RGBA, GL_FLOAT, img);
	glFinish();
	endDraw();
}

void TEXTURE_GENERATOR::draw_grayLevel_Disk(pmDATA_TYPE *pos, pmDATA_TYPE r, int flg_direction) const
{
	//GLfloat color0[4] = {0.3, 0.3, 0.3, 0.8};
	//GLfloat color1[4] = {1.0, 1.0, 1.0, 0.0};
	GLfloat color0[4] = {0.0, 0.0, 0.0, 0.3};
	GLfloat color1[4] = {0.0, 0.0, 0.0, 0.0};
	//GLfloat color1[4] = {0.0, 0.0, 0.0, 0.0};
	int nf = 10;
	glBegin(GL_TRIANGLE_FAN);
	glColor4fv(color0);
	wago_glVertex3fv(pos);
	glColor4fv(color1);
	for (int i = 0; i < nf; i++) {
		float a = i*3.14159*2/(nf-1);
		float x = r*cos(a);
		float y = r*sin(a);
		pmDATA_TYPE p[3] = {pos[0]+x, pos[1]+y, 0.0};
		wago_glVertex3fv(p);
	}
	glEnd();
}

void TEXTURE_GENERATOR::draw_grayLeveL_Disk_AtVertices() const
{
	if (region == NULL) return;
	
	
	float txt_x = region->texture_x;
	float txt_y = region->texture_y;
	float txt_sx = region->texture_sx;
	float txt_sy = region->texture_sy;
	//if (texture) {
		//texture->Draw(0, 0, 0, 0);
	//}
	oTriangleList **ptAttachedFaceList = sobj->ptAttachedFaceList;



	using namespace wagoNS_basic_mem;
	const oTriangleList *fl;
	//
	for (fl = region->tri_list; fl!=NULL; fl = fl->next) {
		const oTriangle *f = fl->f;
		tmp_int_array[f->id] = 0;
	}

	pmDATA_TYPE r = 0.01;

	for (fl = region->tri_list; fl!=NULL; fl = fl->next) {
		const oTriangle *f = fl->f;
		for (int i = 0; i < 3; i++) {
			const oPoint *v = f->point[i];
			int flg = FALSE;
			for (const oTriangleList *ffl = ptAttachedFaceList[v->id]; ffl != NULL; ffl = ffl->next) {
				if (tmp_int_array[ffl->f->id] != 0) {
					flg = TRUE;
					break;
				}
			}
			if (flg) {
				if (map_int_array[v->id] == -1) {
					map_int_array[v->id] = 0;
					pmDATA_TYPE r = 0.005;
					pmDATA_TYPE txt_pos0[3];
					txt_pos0[2] = 0.0;
					switch(i) {
						case 0:
						txt_pos0[0] = f->txt_coords0[0];
						txt_pos0[1] = f->txt_coords0[1];
						break;
						case 1:
						txt_pos0[0] = f->txt_coords1[0];
						txt_pos0[1] = f->txt_coords1[1];
						break;
						case 2:
						txt_pos0[0] = f->txt_coords2[0];
						txt_pos0[1] = f->txt_coords2[1];
						break;
					}
					mapToActualTextureCoords_Region(txt_pos0, txt_pos0, region);
					draw_grayLevel_Disk(txt_pos0, r, FALSE);
				}
			}
		}
	}
	
	/*
	for (fl = region->tri_list; fl!=NULL; fl = fl->next) {
		const oTriangle *f = fl->f;
		const oPoint *v0, *v1, *v2;
		v0 = f->point[0];
		v1 = f->point[1];
		v2 = f->point[2];
		pmDATA_TYPE txt_pos0[3];
		pmDATA_TYPE txt_pos1[3];
		pmDATA_TYPE txt_pos2[3];
		txt_pos0[2] = 0.0;
		txt_pos1[2] = 0.0;
		txt_pos2[2] = 0.0;
		txt_pos0[0] = f->txt_coords0[0];
		txt_pos0[1] = f->txt_coords0[1];
		txt_pos1[0] = f->txt_coords1[0];
		txt_pos1[1] = f->txt_coords1[1];
		txt_pos2[0] = f->txt_coords2[0];
		txt_pos2[1] = f->txt_coords2[1];
		

		if (tmp_int_array[v0->id]==-1) {
			mapToActualTextureCoords_Region(txt_pos0, txt_pos0, region);
			draw_grayLevel_Disk(txt_pos0, r, FALSE);
			tmp_int_array[v0->id] = 0;
		}

		if (tmp_int_array[v1->id]==-1) {
			mapToActualTextureCoords_Region(txt_pos1, txt_pos1, region);
			draw_grayLevel_Disk(txt_pos1, r, FALSE);
			tmp_int_array[v1->id] = 0;
		}

		if (tmp_int_array[v2->id]==-1) {
			mapToActualTextureCoords_Region(txt_pos2, txt_pos2, region);
			draw_grayLevel_Disk(txt_pos2, r, FALSE);
			tmp_int_array[v2->id] = 0;
		}
		//break;
	}

	*/
	for (fl = region->tri_list; fl!=NULL; fl = fl->next) {
		const oTriangle *f = fl->f;
		const oPoint *v0, *v1, *v2;
		v0 = f->point[0];
		v1 = f->point[1];
		v2 = f->point[2];
		tmp_int_array[f->id] = -1;
		map_int_array[v0->id] = -1;
		map_int_array[v1->id] = -1;
		map_int_array[v2->id] = -1;
	}
}

void TEXTURE_GENERATOR::draw_LineSegment(pmDATA_TYPE *p0, pmDATA_TYPE *p1, pmDATA_TYPE r0, pmDATA_TYPE r1) const
{
	int n = 2;
	pmDATA_TYPE d = mDISTANCE3D(p0, p1);
	pmDATA_TYPE v[3];
	mSUB(v, p1, p0);
	//
	GLfloat color0[4] = {0.0, 0.0, 0.7, 0.7};
	glLineWidth(4.0);
	glColor4fv(color0);
	pmDATA_TYPE t, dt;
	t = 0.0;
	dt = 1.0/ (n*2);
	glBegin(GL_LINES);
	for (int i = 0; i < n; i++, t += 2*dt) {
		pmDATA_TYPE pp0[3];
		pmDATA_TYPE pp1[3];
		mLINEAR_POINT(pp0, p0, v, t);
		mLINEAR_POINT(pp1, p0, v, (t+dt));
		wago_glVertex3fv(pp0);
		wago_glVertex3fv(pp1);
	}
	glEnd();
	glLineWidth(1.0);
}

void TEXTURE_GENERATOR::draw_LineSegment_AtBoundingEdges() const
{
	if (region == NULL) return;
	
	
	float txt_x = region->texture_x;
	float txt_y = region->texture_y;
	float txt_sx = region->texture_sx;
	float txt_sy = region->texture_sy;
	//if (texture) {
		//texture->Draw(0, 0, 0, 0);
	//}
	oTriangleList **ptAttachedFaceList = sobj->ptAttachedFaceList;



	using namespace wagoNS_basic_mem;
	const oTriangleList *fl;
	//
	for (fl = region->tri_list; fl!=NULL; fl = fl->next) {
		const oTriangle *f = fl->f;
		tmp_int_array[f->id] = 0;
	}

	pmDATA_TYPE r = 0.01;
	int nBoundingPoints;
	const oPoint *boundary_points[3];
	int boundary_points_index[3];

	for (fl = region->tri_list; fl!=NULL; fl = fl->next) {
		const oTriangle *f = fl->f;
		nBoundingPoints = 0;
		for (int i = 0; i < 3; i++) {
			const oPoint *v = f->point[i];
			int flg = FALSE;
			for (const oTriangleList *ffl = ptAttachedFaceList[v->id]; ffl != NULL; ffl = ffl->next) {
				if (tmp_int_array[ffl->f->id] != 0) {
					flg = TRUE;
					boundary_points[nBoundingPoints] = v;
					boundary_points_index[nBoundingPoints]  = i;
					nBoundingPoints++;
					break;
				}
			}
		}
		pmDATA_TYPE txt_pos0[3];
		pmDATA_TYPE txt_pos1[3];
		txt_pos0[2] = 0.0;
		txt_pos1[2] = 0.0;
		pmDATA_TYPE r0 = 0.01;
		pmDATA_TYPE r1 = 0.02;
		if (nBoundingPoints >= 2) {
			for (int j = 0; j < nBoundingPoints-1; j++) {
				computeActualTextureCoords_ForFaceVertex_Region(txt_pos0, region, f, boundary_points_index[j]);
				computeActualTextureCoords_ForFaceVertex_Region(txt_pos1, region, f, boundary_points_index[j+1]);
				draw_LineSegment(txt_pos0, txt_pos1, r0, r1);
			}
		}
	}
	

	for (fl = region->tri_list; fl!=NULL; fl = fl->next) {
		const oTriangle *f = fl->f;
		//const oPoint *v0, *v1, *v2;
		//v0 = f->point[0];
		//v1 = f->point[1];
		//v2 = f->point[2];
		tmp_int_array[f->id] = -1;
		//map_int_array[v0->id] = -1;
		//map_int_array[v1->id] = -1;
		//map_int_array[v2->id] = -1;
	}
}