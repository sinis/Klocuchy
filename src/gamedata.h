#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <map>
#include <string>

class GameData
{
public:
    GameData();
    ~GameData();

    enum {
        FontSize = 20
    };

    SDL_Surface *GetImage(std::string name);
    TTF_Font *GetFont(std::string name);

    static GameData *Instance() { return _instance; }

private:
    static GameData *_instance;
    std::map<std::string, SDL_Surface*> _images;
    std::map<std::string, TTF_Font*> _fonts;
};

#endif // GAMEDATA_H
