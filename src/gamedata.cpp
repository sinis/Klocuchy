#include "gamedata.h"
#include <SDL/SDL_image.h>
#include "defines.h"

GameData *GameData::_instance = 0;

GameData::GameData()
{
    _instance = this;
}

GameData::~GameData()
{
    std::map<std::string, SDL_Surface*>::iterator ii;
    std::map<std::string, TTF_Font*>::iterator fi;

    while (_images.size())
    {
        ii = _images.begin();
        SDL_FreeSurface((*ii).second);
        _images.erase(ii);
    }

    while (_fonts.size())
    {
        fi = _fonts.begin();
        TTF_CloseFont((*fi).second);
        _fonts.erase(fi);
    }
}

SDL_Surface *GameData::GetImage(std::string name)
{
    SDL_Surface *img = _images[name];
    if (!img)
    {
        img = IMG_Load((std::string(DATADIR) + name).c_str());
        _images[name] = img;
    }
    return img;
}

TTF_Font *GameData::GetFont(std::string name)
{
    TTF_Font *font = _fonts[name];
    if (!font)
    {
        font = TTF_OpenFont((std::string(DATADIR) + name).c_str(), FontSize);
        _fonts[name] = font;
    }
    return font;
}
