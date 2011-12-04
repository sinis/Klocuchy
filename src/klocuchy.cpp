#include "src/klocuchy.h"
#include <iostream>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

Klocuchy *Klocuchy::_instance = 0;

Klocuchy::Klocuchy():
    _screen(0)
{
    _instance = this;
}

Klocuchy::~Klocuchy()
{}

bool Klocuchy::InitSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "SDL_Init() failed.\n";
        return false;
    }

    _screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE);
    if (!_screen)
    {
        std::cerr << "SDL_SetVideoMode() failed.\n";
        SDL_Quit();
        return false;
    }

    return true;
}

bool Klocuchy::InitIMG()
{
    if (!IMG_Init(IMG_INIT_PNG))
    {
        std::cerr << "IMG_Init() failed.\n";
        return false;
    }
    return true;
}

bool Klocuchy::InitTTF()
{
    if (TTF_Init())
    {
        std::cerr << "TTF_Init() failed.\n";
        return false;
    }
    return true;
}

bool Klocuchy::Initialize()
{
    if (!InitSDL())
        return false;

    if (!InitIMG())
    {
        SDL_Quit();
        return false;
    }

    if (!InitTTF())
    {
        IMG_Quit();
        SDL_Quit();
        return false;
    }

    if (!InitGame())
    {
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return false;
    }

    return true;
}

bool Klocuchy::InitGame()
{
    // TODO
    return true;
}

void Klocuchy::UnloadGame()
{
    // TODO
}

void Klocuchy::Unload()
{
    UnloadGame();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int Klocuchy::Exec()
{
    return 0;
}
