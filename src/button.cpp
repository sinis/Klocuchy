#include "button.h"
#include <SDL/SDL_ttf.h>
#include <iostream>
#include "klocuchy.h"
#include "gamedata.h"
#include "defines.h"

Button::Button():
    _text(""),
    _x(0), _y(0),
    _enabled(true),
    _width(0), _height(0),
    _state(MouseOut),
    _screen(Klocuchy::Instance()->Screen()),
    _label(0)
{}

Button::~Button()
{
    if (_label)
        SDL_FreeSurface(_label);
}

bool Button::SetText(std::string text)
{
    TTF_Font *font = GameData::Instance()->GetFont(FONT);
    SDL_Color color;

    if (!font)
    {
        std::cerr << "Button::SetText() - could not load font.\n";
        return false;
    }

    if (_label)
    {
        SDL_FreeSurface(_label);
        _label = 0;
    }

    if (_enabled)
        color.r = color.g = color.b = 0;
    else
        color.r = color.g = color.b = 128;

    _label = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!_label)
    {
        std::cerr << "Button::SetText() - could not render text.\n";
        return false;
    }

    _text = text;
    return true;
}

bool Button::SetImage(std::string fileName, int width, int height)
{
    SDL_Surface *img = GameData::Instance()->GetImage(fileName);

    if (!img)
    {
        std::cerr << "Button::SetImage() - could not load image " << fileName << std::endl;
        return false;
    }

    _image = img;
    _width = width;
    _height = height;
    return true;
}

void Button::SetEnabled(bool enabled)
{
    _enabled = enabled;
    SetText(_text);
}

bool Button::IsMouseOver(int x, int y)
{
    return (x >= _x && x <= _x+_width && y >= _y && y <= _y+_height);
}

void Button::OnMouseOver()
{
    _state = MouseOver;
}

void Button::OnMouseOut()
{
    _state = MouseOut;
}

void Button::OnPress()
{
    _state = Pressed;
}

void Show()
{
    SDL_Rect src, dst;
    src.x = 0;
    src.y = 0;
    src.h = _height;
    dst.x = _x;
    dst.y = _y;

    switch (_state)
    {
    case MouseOut:
        src.w = 0;
        break;
    case MouseOver:
        src.w = _width;
        break;
    case Pressed:
        src.w = _width*2;
        break;
    }

    SDL_BlitSurface(_image, &src, _screen, &dst);
}
