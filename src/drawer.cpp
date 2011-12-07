#include "drawer.h"

Uint32 Drawer::GetPixel(SDL_Surface *surface, int x, int y)
{
    return static_cast<Uint32*>(surface->pixels) [x + x*y];
}

void Drawer::PutPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    static_cast<Uint32*>(surface->pixels) [x + x*y] = pixel;
}

void Drawer::DrawHorizontalLine(SDL_Surface *surface, int x, int y1, int y2, Uint32 color)
{
    for (int i = y1; i < y2; ++i)
    {
        PutPixel(surface, x, i, color);
    }
}

void Drawer::DrawVerticalLine(SDL_Surface *surface, int x1, int x2, int y, Uint32 color)
{
    for (int i = x1; i < x2; ++i)
    {
        PutPixel(surface, i, y, color);
    }
}
