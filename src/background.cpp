#include "background.h"
#include <iostream>
#include "gamedata.h"
#include "klocuchy.h"

Background::Background():
    _sprite(0),
    _screen(Klocuchy::Instance()->Screen()),
    _frame(0),
    _frames(0),
    _width(0),
    _height(0),
    _x(0), _y(0),
    _interval(Second)
{}

void Background::SetSprite(std::string fileName, int frames, int width, int height)
{
    SDL_Surface *sprite = GameData::Instance()->GetImage(fileName);
    if (!sprite)
    {
        std::cerr << "Background::SetSprite() - could not load sprite " << fileName << std::endl;
        return;
    }

    _sprite = sprite;
    _frame = 0;
    _frames = frames;
    _width = width;
    _height = height;

    _timer.SetInterval(_interval/_frames);
}

void Background::SetPosition(int x, int y)
{
    _x = x;
    _y = y;
}

void Background::Show()
{
    SDL_Rect src;
    SDL_Rect dst;

    if (_timer.Finished())
    {
        _timer.Start();
        _frame = (_frame+1) % _frames;
    }

    src.x = _width * _frame;
    src.y = 0;
    src.w = _width;
    src.h = _height;
    dst.x = _x;
    dst.y = _y;

    SDL_BlitSurface(_sprite, &src, _screen, &dst);
}

void Background::SetInterval(int interval)
{
    _interval = interval;
    _timer.SetInterval(_interval/_frames);
}
