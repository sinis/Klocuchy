#ifndef FRAME_H
#define FRAME_H

#include <SDL/SDL.h>

class Frame
{
public:
    Frame();

    void SetPosition(int x, int y);
    void SetSize(int width, int height);
    void SetColor(Uint32 light, Uint32 shadow);

    void Show();

private:
    SDL_Surface *_screen;
    int _x;
    int _y;
    int _width;
    int _height;
    Uint32 _light;
    Uint32 _shadow;
};

#endif // FRAME_H
