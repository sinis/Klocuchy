#include "tile.h"
#include <string>
#include <iostream>
#include <SDL/SDL.h>
#include "gamedata.h"
#include "defines.h"
#include "klocuchy.h"

Tile::Tile(Color color):
    _color(None),
    _image(0)
{
    SetColor(color);
}

void Tile::SetColor(Color color)
{
    SDL_Surface *col = 0;
    std::string file;
    switch (color)
    {
    case Blue:
        file = BLUE;
        break;
    case Green:
        file = GREEN;
        break;
    case Orange:
        file = ORANGE;
        break;
    case Red:
        file = RED;
        break;
    case Violet:
        file = VIOLET;
        break;
    case Grey:
        file = GREY;
        break;
    case Yellow:
        file = YELLOW;
        break;
    case White:
        file = WHITE;
        break;
    default:
        file = "";
        break;
    }

    if (!file.empty())
    {
        col = GameData::Instance()->GetImage(file);
        if (!col)
        {
            std::cerr << "Tile::SetColor() - could not load " << file << std::endl;
            _color = None;
        }
        else
        {
            _color = color;
            _image = col;
        }
    }
    else _color = None;
}

void Tile::Show(int x, int y)
{
    if (_color == None)
        return;

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    SDL_BlitSurface(_image, 0, Klocuchy::Instance()->Screen(), &rect);
}
