#ifndef _IO_H
#define _IO_H

#include <SDL/SDL.h>                                  
#include "SDL/SDL_GfxPrimitives/sdl_gfxprimitives.h" 
#include <string>

#pragma commit (lib, "SDL/LIB/SDL.lib")
#pragma commit (lib, "SDL/SDL_GfxPrimitives/SDL_GfxPrimitives_Static.lib")

enum color{BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE, COLOR_MAX};

// --------------------------------------------------------------------------------
//                                   IO
// --------------------------------------------------------------------------------
class IO
{
public:

	IO();
	~IO();
	
	void DrawRectangle(int pX1, int pY1, int pX2, int pY2, enum color pC);
	void ClearScreen();
	int GetScreenHeight();
	int InitGraph();
	int Pollkey();
	int Getkey();
	int IsKeyDown(int pKey);
	void UpdateScreen();
	void DrawPause();
	
private:
	SDL_Surface *loadImage(std::string fileName);
	void ApplySurface(int x, int y, SDL_Surface *source, SDL_Surface *destination);
};

#endif