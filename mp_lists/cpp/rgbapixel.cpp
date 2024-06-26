#include "rgbapixel.h"

RGBAPixel:: RGBAPixel(){
	red =  255;
	green = 255;
	blue = 255;
	alpha = 255;
}

RGBAPixel::RGBAPixel( uint8_t red,
					uint8_t green,
					uint8_t blue){
	this->red = red;
	this->green = green;
	this->blue = blue;
	alpha = 255;
}

bool RGBAPixel::operator<(RGBAPixel const & other) const {
	return red+green+blue < other.red+other.green+other.blue;
}

bool RGBAPixel::operator>(RGBAPixel const & other) const {
	return red+green+blue > other.red+other.green+other.blue;
}
