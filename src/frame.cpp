#include "frame.h"
#include "drawer.h"
#include "klocuchy.h"

Frame::Frame():
    _screen(Klocuchy::Instance()->Screen()),
    _x(0), _y(0),
    _width(0),
    _height(0),
    _light(0),
    _shadow(0)
{}

void Frame::SetPosition(int x, int y)
{
    _x = x;
    _y = y;
}

void Frame::SetSize(int width, int height)
{
    _width = width;
    _height = height;
}

void Frame::SetColor(Uint32 light, Uint32 shadow)
{
    _light = light;
    _shadow = shadow;
}

void Frame::Show()
{
    // Bright lines.
    // Top-inside.
    Drawer::DrawHorizontalLine(_screen, _x+1, _x+_width-1, _y+1, _light);
    // Bottom-outside.
    Drawer::DrawHorizontalLine(_screen, _x, _x+_width, _y+_height, _light);
    // Left-inside.
    Drawer::DrawVerticalLine(_screen, _x+1, _y+2, _y+_height-1, _light);
    // Right-outside.
    Drawer::DrawVerticalLine(_screen, _x+_width, _y, _y+_height, _light);

    // Dark lines.
    // Top-outside.
    Drawer::DrawHorizontalLine(_screen, _x, _x+_width, _y, _shadow);
    // Bottom-inside.
    Drawer::DrawHorizontalLine(_screen, _x+1, _x+_width-1, _y+_height-1, _shadow);
    // Left-outside.
    Drawer::DrawVerticalLine(_screen, _x, _y, _y+_height, _shadow);
    // Right-inside.
    Drawer::DrawVerticalLine(_screen, _x+_width-1, _y+1, _y+_height-1, _shadow);
}
