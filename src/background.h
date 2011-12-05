#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <string>
#include <SDL/SDL.h>
#include "timer.h"

class Background
{
public:
    enum {
        Second = 1000
    };

    Background();

    void SetSprite(std::string fileName, int frames, int width, int height);
    void SetPosition(int x, int y);
    void SetInterval(int interval);

    void Show();

private:
    Timer _timer;
    SDL_Surface *_sprite;
    SDL_Surface *_screen;
    int _frame;
    int _frames;
    int _width;
    int _height;
    int _x;
    int _y;
    int _interval;
};

#endif // BACKGROUND_H
