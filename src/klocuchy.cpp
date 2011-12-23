#include "klocuchy.h"
#include <iostream>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

Klocuchy *Klocuchy::_instance = 0;

Klocuchy::Klocuchy():
    _screen(0),
    _gameData(0),
    _mainMenu(0),
    _game(0)
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

    _screen = SDL_SetVideoMode(Width, Height, 32, SDL_HWSURFACE);
    if (!_screen)
    {
        std::cerr << "SDL_SetVideoMode() failed.\n";
        SDL_Quit();
        return false;
    }

    SDL_WM_SetCaption("Klocuchy made by Sinis", 0);

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
    _gameData = new GameData;

    _mainMenu = new MainMenu;
    if (!_mainMenu->Initialize())
        return false;

    _game = new Game;

    return true;
}

void Klocuchy::UnloadGame()
{
    delete _mainMenu;
    delete _gameData;
    delete _game;

    _mainMenu = 0;
    _gameData = 0;
    _game = 0;
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
    bool quit = false;
    // TODO

    while (!quit)
    {
        switch (_mainMenu->Exec())
        {
        case MainMenu::Start:
            _game->Start();
            break;
        case MainMenu::Resume:
            _game->Resume();
            break;
        case MainMenu::Highscore:
            break;
        case MainMenu::About:
            break;
        case MainMenu::Quit:
            quit = true;
            break;
        default:
            // Pfrh, warnings.
            break;
        }

        switch (_game->GetState())
        {
        case Game::Paused:
            _mainMenu->EnableResume(true);
            break;
        default:
            _mainMenu->EnableResume(false);
            break;
        }
    }

    return 0;
}
