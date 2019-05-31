#include "Quad.hpp"

void Quad::Render(FrameBuffer & fb) const
{
	// takes around 60% of the time the line
	// version took
	/*
	for (u32 i = rect_.origin.y; i <= (rect_.origin.y +
	rect_.dimensions.y);i++) {
	fb.DrawScanline(i,rect_.origin.x,rect_.origin.x +
	rect_.dimensions.x,PackRGBA(colour_)); } */

	// Triangle Version
	// Seems to perform about the same as the direct scanline version but
	// i'll keep this implementation as it is closer to what i'm used to
	// with OpenGL
	// BUG: now that RenderTriangle does perspective
	// by default therefore i need to figure out
	// how to fix the quad drawing
	// possibly by changing Quad so it just takes
	// 4 Vertices maybe?
	// now FIXED
	fb.RenderTriangle(v1_, v2_, v3_, PackRGBA(colour_));
	fb.RenderTriangle(v2_, v4_, v3_, PackRGBA(colour_));
}