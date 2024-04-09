/**
 * Copyright 2024 University of Oulu
 * Authors:
 *   Elmeri Uotila <roope.uotila@oulu.fi>
 */

#ifndef CANVAS_H
#define CANVAS_H

#include "png.h"
#include "vector2.h"
#include "canvasitem.h"

class Canvas
{
	public:
		Canvas();
		~Canvas();
		void Add(CanvasItem* item);
		void Remove(CanvasItem* item);
		void Swap(CanvasItem* item1, CanvasItem* item2);
		void draw(PNG* canvas) const;
		
	private:
		CanvasItem* items;
		size_t itemcount = 0;
};

#endif

