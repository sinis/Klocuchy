// Utility class for Frames drawing.

#ifndef DRAWER_H
#define DRAWER_H

#include <SDL/SDL.h>

class Drawer
{
public:
    static Uint32 GetPixel(SDL_Surface *surface, int x, int y);
    static void PutPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
    static void DrawHorizontalLine(SDL_Surface *surface, int x, int y1, int y2, Uint32 color);
    static void DrawVerticalLine(SDL_Surface *surface, int x1, int x2, int y, Uint32 color);
};

#endif // DRAWER_H
