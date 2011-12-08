#include "game.h"
#include "klocuchy.h"

Game::Game():
    _screen(Klocuchy::Instance()->Screen()),
    _tetrion(new Tetrion),
    _next(new Tetramino),
    _current(new Tetramino),
    _nextView(new NextView),
    _scoreView(new ScoreView),
    _timer(new Timer),
    _score(0)
{
    _tetrion->SetPosition(0, 0);
    _nextView->SetPosition(_screen->w - (Tile::Size*4+4), 0);
    _scoreView->SetPosition(_screen->w - (Tile::Size*4+4),
                            _screen->h - (Tile::Size*4+4));
    _timer->SetInterval(InitialTiming);
}

Game::~Game()
{
    delete _tetrion;
    delete _next;
    delete _current;
    delete _nextView;
    delete _scoreView;
    delete _timer;
}

void Game::Start()
{
    // Resets everything and starts game.
    Reset();
    _timer->Start();
    Play();
}

void Game::Pause()
{
    // Pauses the game.
    // TODO:
    // Should show pause screen.
    _timer->Pause();
}

void Game::Resume()
{
    _timer->Resume();
    Play();
}

void Game::Reset()
{
    _timer->SetInterval(InitialTiming);
    _tetrion->Clear();
    _current->Reset();
    _next->Reset();
}

void Game::Play()
{
    SDL_Event event;
    bool play = true;
    bool inMove = false;
    Tetramino::Direction dir;
    Timer fps;
    fps.SetInterval(1000/FPS);

    fps.Start();
    while (play)
    {
        while (SDL_PollEvent(&event))
        {
            
        }
    }
}