/**
 * Copyright 2024 University of Oulu
 * Authors:
 *   Elmeri Uotila <roope.uotila@oulu.fi>
 */

#include "png.h"
#include "color.h"
#include "line.h"
#include "triangle.h"
#include "rectangle.h"
#include "shape.h"
#include "vector2.h"
#include "canvas.h"
#include "canvasitem.h"

void Layers()
{
	const char OUTPUT_FILE[] = "out.png";
	const int WIDTH = 128;
	const int HEIGHT = 128;
	
	// Let's define drawables, canvas items and the output canvas
	const size_t num_drawables = 3;
	const size_t num_items = 7;
	Drawable** drawables = new Drawable*[num_drawables];
	CanvasItem** canvasItems = new CanvasItem*[num_items];
	Canvas outputCanvas;
	
	// Define a white + shape in quarter of the size of the output canvas
	// We want to draw them white so we can define the color with canvas item color
	drawables[0] = new Line(Vector2(0.5*WIDTH/4, 0.0), Vector2(0.5*WIDTH/4, 1.0*HEIGHT/4), RGBAPixel(255,255,255));
	drawables[1] = new Line(Vector2(0.0, 0.5*HEIGHT/4), Vector2(1.0*WIDTH/4, 0.5*HEIGHT/4), RGBAPixel(255,255,255));
	
	// Define a white triangle
	drawables[2] = new Triangle(RGBAPixel(255,255,255), Vector2(0.0, 0.0), Vector2(WIDTH, HEIGHT/2), Vector2(0.0, HEIGHT));

	// Some text in the background, should be partly obscured by the + shapes
	// Since this is added to the canvas first, it will be drawn first
	canvasItems[5] = new CanvasItem(WIDTH, HEIGHT, Vector2(0.0, 0.0), Vector2(1.0, 1.0), RGBAPixel(0,0,255));
	canvasItems[5]->readFromFile("Images/background.png");
	outputCanvas.Add(canvasItems[5]);

	// These canvas items should match the size of the drawables
	// They are then scaled up which should make them look thicker
	// We also position them in the corners and give them distinct color
	// Draw the + shapes to their intended canvas items
	for (size_t i=0; i<2; i++) {
		canvasItems[i] = new CanvasItem(WIDTH/4, HEIGHT/4, Vector2(i*WIDTH/2, 0), Vector2(2.0, 2.0), 
						RGBAPixel(i == 0 ? 255 : 0, i == 1 ? 255 : 0, 0, 127));
		drawables[0]->draw(canvasItems[i]);
		drawables[1]->draw(canvasItems[i]);
		outputCanvas.Add(canvasItems[i]);
	}
	
	// Define the canvas items for the triangles then draw them
	// Draw the triangles to their intended canvas items
	for (size_t i=3; i<5; i++) {
		canvasItems[i] = new CanvasItem(WIDTH, HEIGHT, Vector2(WIDTH/2, HEIGHT/2), 
				Vector2(i==3 ? -0.5 : 0.5, 0.5), RGBAPixel(0, i == 3 ? 255 : 0, i == 4 ? 255 : 0));
		drawables[2]->draw(canvasItems[i]);
		outputCanvas.Add(canvasItems[i]);
	}
	
	// Big + in the middle
	canvasItems[2] = new CanvasItem(WIDTH, HEIGHT, Vector2(-3.0, -3.0), Vector2(4.1, 4.1), RGBAPixel(0,0,0,255));
	
	drawables[0]->draw(canvasItems[2]);
	drawables[1]->draw(canvasItems[2]);
	outputCanvas.Add(canvasItems[2]);
	
	// Some text in the foreground, should partly obscure the + shapes
	canvasItems[6] = new CanvasItem(WIDTH, HEIGHT, Vector2(0.0, 0.0), Vector2(1.0, 1.0), RGBAPixel(255,0,0,127));
	canvasItems[6]->readFromFile("Images/foreground.png");
	outputCanvas.Add(canvasItems[6]);

	// The order of items on the canvas is important!
	
	// This is our final output. The output canvas draws all its items in order, blending based on alpha channel
	PNG out(WIDTH, HEIGHT);
	outputCanvas.draw(&out);
	out.writeToFile(OUTPUT_FILE);

	// Clean up
	for (size_t i = 0; i < num_drawables; i++)
	{
		delete drawables[i];
		drawables[i] = NULL;
	}
	
	for(size_t i=0; i < num_items; i++)
	{
		delete canvasItems[i];
		canvasItems[i] = NULL;
	}
	
	delete[] canvasItems;
	delete[] drawables;
	drawables = NULL;
	canvasItems = NULL;
}

void Collage(){
	const char OUTPUT_FILE[] = "collage.png";
	char INPUT_FILE[] = "Images/1.png";
	// Line thickness
	const int th = 8;
	
	// Let's define canvas items and the output canvas
	const size_t num_items = 8;
	CanvasItem** canvasItems = new CanvasItem*[num_items];
	Canvas outputCanvas;

	PNG out("Images/5.png");
	int WIDTH = out.width();
	int HEIGHT = out.height();
	
	// Load our images for the collage
	for (size_t i=0; i<4; i++){
		// Converting number to ASCII number characters
		INPUT_FILE[7] = (char)(i+49);
		canvasItems[i] = new CanvasItem(WIDTH, HEIGHT, Vector2(0.0, 0.0), Vector2(1.0, 1.0), i==0 ? RGBAPixel(255,0,196) : RGBAPixel(255,255,255,255));
		canvasItems[i]->readFromFile(INPUT_FILE);
		outputCanvas.Add(canvasItems[i]);
	}
	
	// Define canvas items for frames, matching the size of the respective images
	for (size_t i=4; i<num_items; i++) {
		canvasItems[i] = new CanvasItem(canvasItems[i-4]->width()+th*2, canvasItems[i-4]->height()+th*2, Vector2(0.0, 0.0), Vector2(1.0, 1.0), RGBAPixel(50,0,200));
		
		Rectangle rec(Vector2(canvasItems[i]->width()/2, canvasItems[i]->height()/2), RGBAPixel(255,255,255), canvasItems[i]->width(), canvasItems[i]->height());
		
		rec.draw(canvasItems[i]);
		outputCanvas.Add(canvasItems[i]);
	}
	
	// Arrange them somehow
	// 0-3 are images, 4-7 are frames
	canvasItems[0]->SetPosition(Vector2(1800.0, 50.0));
	canvasItems[4]->SetPosition(Vector2(1800.0-th, 50.0-th));
	canvasItems[1]->SetPosition(Vector2(200.0, 700.0));
	canvasItems[5]->SetPosition(Vector2(200.0-th, 700.0-th));
	canvasItems[2]->SetPosition(Vector2(1300.0, 700.0));
	canvasItems[6]->SetPosition(Vector2(1300.0-th, 700.0-th));
	canvasItems[3]->SetPosition(Vector2(650.0, 50.0));
	canvasItems[7]->SetPosition(Vector2(650.0-th, 50.0-th));
	
	// We should put the frames under the images so it only shows up on the sides
	for(size_t i=0; i<num_items/2; i++){
		outputCanvas.Swap(canvasItems[i], canvasItems[i+4]);
	}
	
	// Actually we don't want the frame around the logo so let's delete it
	outputCanvas.Remove(canvasItems[4]);
	
	// This tests that swap won't do anything with invalid pointers...
	outputCanvas.Swap(canvasItems[1], nullptr);
	
	// This tests that it won't remove anything in the case of an invalid pointer
	outputCanvas.Remove(nullptr);
	
	// This is our final output. The output canvas draws all its items in order, blending based on alpha channel
	outputCanvas.draw(&out);
	out.writeToFile(OUTPUT_FILE);

	// Clean up
	for(size_t i=0; i < num_items; i++)
	{
		delete canvasItems[i];
		canvasItems[i] = NULL;
	}
	
	delete[] canvasItems;
	canvasItems = NULL;
}

int main(){
	Layers();
	Collage();
	return 0;
}
