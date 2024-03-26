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

// double getAngle(double angle) {
// 	if (angle < 90) {
// 		angle = 90 - angle;
// 	} else if (angle < 180) {
// 		angle = 180 - angle;
// 	} else if (angle < 270) {
// 		angle = 270 - angle;
// 	} else {
// 		angle = 360 - angle;
// 	}
// 	return angle;
// }

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
	int maxN = 100;

	for (int y=0; y<height; ++y) {
		for (int x=0; x<width; ++x) {
			double cr = mapToReal(x, width, minR, maxR);
			double ci = mapToImaginary(y, height, minI, maxI);

			int n= findMandlebrot(cr, ci, maxN);

			RGBAPixel * px = (png)(x,y);
			px ->red = ( int(n*n % 256));
			px ->green = (n * int(tan(n)) %256);
			px ->blue = (int(n/2%256));
		}
	}
	
	return png;
}

// void clock() {
	    // Get current time
    // time_t now = time(nullptr);
    // tm* currentTime = localtime(&now);
    // int hour = currentTime->tm_hour;
    // int minute = currentTime->tm_min;
    // int second = currentTime->tm_sec;
	// int centerX = width / 2;
	// int centerY = height / 2;

	// cout << " hour " << hour << " minute " << minute << " second " << second << endl;

	// for (int y = 0; y < height; ++y) {
    //     for (int x = 0; x < width; ++x) {
    //         double distance = sqrt(pow(x - centerX, 2) + pow(y - centerY, 2));
    //         if (abs(distance - radius) <= 2) {
	// 			RGBAPixel * px = (png)(x,y);
	// 			px ->red = 0;
	// 			px ->green = 0;
	// 			px ->blue = 0;
    //         }
    //         else if (distance < radius) {
	// 			RGBAPixel * px = (png)(x,y);
	// 			px ->red = 255;
	// 			px ->green = 255;
	// 			px ->blue = 255;
    //         }
    //     }
    // }

	// for (int y = 0; y < height; ++y) {
	// 	RGBAPixel * px = (png)(width/2,y);
	// 	px ->red = 0;
	// 	px ->green = 0;
	// 	px ->blue = 0;
    // }

	// for (int x = 0; x < width; ++x) {
	// 	RGBAPixel * px = (png)(x,height/2);
	// 	px ->red = 0;
	// 	px ->green = 0;
	// 	px ->blue = 0;
    // }

	// // hour = 10;
	// // minute = 0;
	// // second =0;
    // // // Calculate positions of clock hands

    // double hourAngle = getAngle(360.0 * (hour % 12 + minute / 60.0) / 12.0);
    // double minuteAngle = getAngle(360.0 * (minute + second / 60.0) / 60.0);
    // // double secondAngle = getAngle(360.0 * second / 60.0);


    // // // Draw hour hand
    // int hourHandLength = radius * 0.5;
    // int hourHandX = centerX + hourHandLength * sin((hourAngle) * M_PI / 180);
    // int hourHandY = centerY + hourHandLength * cos((hourAngle) * M_PI / 180);

	// int xdrawFrom = centerX;
	// int xdrawTo = hourHandX;
	// // int ydrawFrom = centerY;
	// // int ydrawTo = hourHandY;

	// if (centerY > hourHandX) {
	// 	xdrawFrom = hourHandX;
	// 	xdrawTo = centerX;
	// }

	// cout << hourHandX << " X " << hourHandY << " " << hour << " theta "<< hourAngle << endl;
	// cout << centerX << "X" << centerY << "Y" << hour << endl;

    // for (int x = xdrawFrom; x <= xdrawTo; ++x) {
	// 	// int y = int(tan(hourAngle) * x);
	// 	int y = x;
	// 	RGBAPixel * px = (png)(x,y);
	// 	px ->red = 0;
	// 	px ->green = 0;
	// 	px ->blue = 0;
    // }

    // // Draw minute hand
    // int minuteHandLength = radius * 0.8;
    // int minuteHandX = centerX + minuteHandLength * sin((minuteAngle - 90) * M_PI / 180);
    // int minuteHandY = centerY + minuteHandLength * cos((minuteAngle - 90) * M_PI / 180);

	// if (centerY > minuteHandY) {
	// 	xdrawFrom = minuteHandX;
	// 	xdrawTo = centerX;
	// } else {
	// 	xdrawFrom = centerX;
	// 	xdrawTo = minuteHandX;
	// }

	// cout << minuteHandX << " X " << minuteHandY << " " << minute << " theta "<< minuteAngle << endl;
    // for (int x = xdrawFrom; x <= xdrawTo; ++x) {
	// 	RGBAPixel * px = (png)(x,x);
	// 	px ->red = 0;
	// 	px ->green = 0;
	// 	px ->blue = 255;
    // }

    // // Draw second hand
    // int secondHandLength = radius * 0.9;
    // // int secondHandX = centerX + secondHandLength * sin((secondAngle - 90) * M_PI / 180);
    // int secondHandY = centerY + secondHandLength * cos((secondAngle - 90) * M_PI / 180);


	// if (centerY > secondHandY) {
	// 	ydrawFrom = secondHandY;
	// 	ydrawTo = centerY;
	// } else {
	// 	ydrawFrom = centerY;
	// 	ydrawTo = secondHandY;
	// }

	// cout << ydrawFrom << " ydrawFrom " << ydrawTo << " ydrawTo " << endl;
    // for (int y = ydrawFrom; y <= ydrawTo; ++y) {
	// 	RGBAPixel * px = (png)(y,y);
	// 	px ->red = 0;
	// 	px ->green = 255;
	// 	px ->blue = 0;
    // }
// }


void drawHearts(unsigned int width, unsigned int height) {
	PNG png(width, height);
	int centerX = (width-1) / 4;
	int centerY = (height-1) / 2;
	int size = 1000;
	RGBAPixel color = RGBAPixel(255,0,0);
	for (int y = centerY - size; y <= centerY + size; ++y) {
        for (int x = centerX - size; x <= centerX + size; ++x) {
            // Calculate distance from center of heart shape
            double distance = sqrt(pow(x - centerX, 2) + pow(y - centerY + size * 0.3, 2));
            // If distance is within heart shape equation, set pixel color
            if (distance <= size * 0.5 ||
                (x >= centerX && x <= centerX + size * 0.6 && y >= centerY - size * 0.3 && y <= centerY + size * 0.3) ||
                (x <= centerX && x >= centerX - size * 0.6 && y >= centerY - size * 0.3 && y <= centerY + size * 0.3)) {
				RGBAPixel * px = (png)(x,y);
				px ->red = color.red;
				px ->green = color.green;
				px ->blue = color.blue;
            }
        }
    }

	centerX = 3 * (width-1) / 4;
	centerY = (height-1) / 2;
	size = 1000;
	color = RGBAPixel(0,255,0);
	for (int y = centerY - size; y <= centerY + size; ++y) {
        for (int x = centerX - size; x <= centerX + size; ++x) {
            // Calculate distance from center of heart shape
            double distance = sqrt(pow(x - centerX, 2) + pow(y - centerY + size * 0.3, 2));
            // If distance is within heart shape equation, set pixel color
            if (distance <= size * 0.5 ||
                (x >= centerX && x <= centerX + size * 0.6 && y >= centerY - size * 0.3 && y <= centerY + size * 0.3) ||
                (x <= centerX && x >= centerX - size * 0.6 && y >= centerY - size * 0.3 && y <= centerY + size * 0.3)) {
				RGBAPixel * px = (png)(x,y);
				px ->red = color.red;
				px ->green = color.green;
				px ->blue = color.blue;
            }
        }
    }

	int startX = (width-1) / 4 + 100;
	int startY = (height-1) / 2;
	int endX = 3 * (width-1) / 4 - 100;
	int endY = (height-1) / 2;
	color = RGBAPixel(0,0,255);
	    // Draw the arrow body
    for (int y = startY; y <= endY; ++y) {
        for (int x = startX; x <= endX; ++x) {
			RGBAPixel * px = (png)(x,y);
            px ->red = color.red;
			px ->green = color.green;
			px ->blue = color.blue;
        }
    }
    // Draw the arrowhead
    for (int y = endY - 10; y <= endY + 10; ++y) {
        for (int x = endX - (y - endY + 10); x <= endX + (y - endY + 10); ++x) {
			RGBAPixel * px = (png)(x,y);
            px ->red = color.red;
			px ->green = color.green;
			px ->blue = color.blue;
        }
    }
}
