#include "texture_tools.h"
#include "image_processing_simple_tools.h"

void TEXTURE_GENERATOR::draw_dyn_heat_diffusion_init() const
{
	cout << "draw_dyn_heat_diffusion_init" << endl;
	//draw();
	draw_close();
	int x = viewport[0];
	int y = viewport[1];
	int w = viewport[2];
	int h = viewport[3];
	
	glReadPixels(x, y, w, h, GL_RGBA, GL_FLOAT, src_img);
	glReadPixels(x, y, w, h, GL_RGBA, GL_FLOAT, original_img);
	glFinish();
	
	imgpro_setConnectionType(imgpro_CONNECTION_TYPE_8);
	
	bgnDraw();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20, 20, -20, 20, -20, 20);
	
	glRasterPos2i(-20, -20);
	glDisable(GL_BLEND);
	glDrawPixels(w, h, GL_RGBA, GL_FLOAT, src_img);
	glFinish();
	endDraw();

	imgpro_stools_open(src_img, w, h, GL_RGBA, mask_img);
	imgpro_stools_open(mask_img, w, h, GL_RGBA, dest_img);
	imgpro_stools_open(dest_img, w, h, GL_RGBA, mask_img);
	imgpro_stools_open(mask_img, w, h, GL_RGBA, dest_img);
	imgpro_stools_open(dest_img, w, h, GL_RGBA, mask_img);
	imgpro_stools_open(mask_img, w, h, GL_RGBA, dest_img);
	imgpro_stools_open(dest_img, w, h, GL_RGBA, mask_img);
	imgpro_stools_open(mask_img, w, h, GL_RGBA, dest_img);
	imgpro_stools_open(dest_img, w, h, GL_RGBA, mask_img);
	//imgpro_stools_open(mask_img, w, h, GL_RGBA, mask_img);
}

void TEXTURE_GENERATOR::draw_dyn_heat_diffusion() const
{
	cout << "draw_dyn_heat_diffusion" << endl;
	int x = viewport[0];
	int y = viewport[1];
	int w = viewport[2];
	int h = viewport[3];
	//imgpro_stools_average(src_img, w, h, GL_RGBA, dest_img);
	//imgpro_stools_average(dest_img, w, h, GL_RGBA, src_img);
	//
	imgpro_stools_setMaskImg(mask_img);
	imgpro_stools_attract(src_img, w, h, GL_RGBA, dest_img);
	imgpro_stools_attract(dest_img, w, h, GL_RGBA, src_img);
	//
	bgnDraw();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20, 20, -20, 20, -20, 20);
	
	glRasterPos2i(-20, -20);
	glDisable(GL_BLEND);
	glDrawPixels(w, h, GL_RGBA, GL_FLOAT, src_img);
	glFinish();
	endDraw();
}