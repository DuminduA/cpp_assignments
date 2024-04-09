/**
 * Copyright 2024 University of Oulu
 * Authors:
 *   Elmeri Uotila <roope.uotila@oulu.fi>
 */

#ifndef CANVASITEM_H
#define CANVASITEM_H

#include "png.h"
#include "vector2.h"
#include "rgbapixel.h"

class CanvasItem : public PNG
{
	public:
		// x and y here represent size in pixels
		CanvasItem(size_t x, size_t y, Vector2 pos, Vector2 scale, RGBAPixel);
		CanvasItem() {}
		Vector2 position();
		Vector2 scale();
		RGBAPixel getBlendedPixel(size_t x, size_t y);
		void SetPosition(Vector2 pos);
	private:
		Vector2 position_;
		Vector2 scale_;
		RGBAPixel color_;
};

#endif

