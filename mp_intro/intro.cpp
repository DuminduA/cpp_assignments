#include "RGB/png.h"
#include "RGB/rgbapixel.h"

#include <string>
#include <cmath>

void rotate(std::string inputFile, std::string outputFile) {
	PNG pic(inputFile);
	// Your code here
	pic.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
	PNG png(width, height);
	// Your code here
	return png;
}
