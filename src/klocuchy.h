#ifndef KLOCUCHY_H
#define KLOCUCHY_H

#include <SDL/SDL.h>

class Klocuchy
{
public:
    Klocuchy();
    ~Klocuchy();

    enum {
        width = 240,
        height = 320
    };

    bool Initialize();
    void Unload();
    int Exec();

    static Klocuchy *Instance();

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
};

#endif // KLOCUCHY_H
