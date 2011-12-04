#ifndef KLOCUCHY_H
#define KLOCUCHY_H

#include <SDL/SDL.h>
#include "gamedata.h"

class Klocuchy
{
public:
    Klocuchy();
    ~Klocuchy();

    enum {
        Width = 240,
        Height = 320
    };

    bool Initialize();
    void Unload();
    int Exec();
    SDL_Surface *Screen() { return _screen; }

    static Klocuchy *Instance() { return _instance; }

private:
    bool InitSDL();
    bool InitIMG();
    bool InitTTF();
    bool InitGame();
    void UnloadGame();

private:
    static Klocuchy *_instance;
    SDL_Surface *_screen;
    // TODO:
    // GameData, MainMenu, Game.
    GameData *_gameData;
};

#endif // KLOCUCHY_H
