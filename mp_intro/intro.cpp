#include "RGB/png.h"
#include "RGB/rgbapixel.h"

#include <string>
#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;

void rotate(std::string inputFile, std::string outputFile) {
	PNG * pic = new PNG();
	pic->readFromFile(inputFile);
	int width  = pic->width();
	int height = pic->height();

	PNG * output = new PNG(pic->width(), pic->height());	
	
	// Go over the whole image,swap pixels accordingly
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
		RGBAPixel * inPixel = (*pic)(x,y);
		RGBAPixel * outPixel = (*output)((width-1)-x,(height-1)-y);

		outPixel  -> red = inPixel -> red;
		outPixel  -> green = inPixel -> green;
		outPixel  -> blue = inPixel -> blue;
		}
	}

	output->writeToFile(outputFile);
}


double mapToReal(int x, int width, double minR, double maxR)
{
	double range = maxR - minR;
	return x * (range/width) + minR;
}

double mapToImaginary(int x, int height, double minI, double maxI)
{
	double range = maxI - minI;
	return x * (range/height) + minI;
}

int findMandlebrot(double cr, double ci, int max_iter)
{
	int i =0;
	double zr = 0.0, zi = 0.0;
	while(i < max_iter && zr* zr + zi * zi < 4.0)
	{
		double temp = zr * zr - zi * zi + cr;
		zi = 2.0 * zr * zi + ci;
		zr = temp;
		i++;

	}
	return i;
}


PNG myArt(unsigned int width, unsigned int height) {
	PNG png(width, height);
	// Your code here

	int minR = -2;
	int maxR = 2;
	int minI = -1;
	int maxI = 3;
	int maxN = 1000;

	for (unsigned int y=0; y<height; ++y) {
		for (unsigned x=0; x<width; ++x) {
			double cr = mapToReal(x, width, minR, maxR);
			double ci = mapToImaginary(y, height, minI, maxI);

			int n= findMandlebrot(cr, ci, maxN);

			RGBAPixel * px = (png)(x,y);
			px ->red = ( int(n*n % 256));
			px ->green = (n *n %256);
			px ->blue = (int(n/2%256));
		}
	}
	
	return png;
}
