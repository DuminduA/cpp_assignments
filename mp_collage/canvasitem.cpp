/**
 * Copyright 2024 University of Oulu
 * Authors:
 *   Elmeri Uotila <roope.uotila@oulu.fi>
 */

#include "canvasitem.h"

CanvasItem::CanvasItem(size_t x, size_t y, Vector2 position, Vector2 scale, RGBAPixel color) {
	resize(x, y);
	// TODO Initialize the pixels transparent so when drawing shapes, the background is transparent
	// Your code here
	for (size_t i = 0; i < x; i++) {
		for(size_t j=0; j < y; j++){
			RGBAPixel* pixel = (*this)(i,j);
			pixel->alpha = 0;
		}
	}

	position_ = position;
	color_ = color;
	scale_ = scale;
}

RGBAPixel CanvasItem::getBlendedPixel(size_t x, size_t y){
	RGBAPixel* p = (*this)(x,y);
	RGBAPixel copy = *p;
	// TODO Blend the pixel with color_
	// Multiply the colors per channel and divide by 255
	// Result should be stored in a copy so we don't modify the original PNG
	// This way the color can be easily changed later
	
	// Your code here
	copy.red = (copy.red * color_.red) / 255;
    copy.green = (copy.green * color_.green) / 255;
    copy.blue = (copy.blue * color_.blue) / 255;
    copy.alpha = (copy.alpha * color_.alpha) / 255;
	
	return copy;
}

Vector2 CanvasItem::position(){
	return position_;
}

Vector2 CanvasItem::scale(){
	return scale_;
}

void CanvasItem::SetPosition(Vector2 pos){
	position_ = pos;
}