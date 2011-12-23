#include "game.h"
#include "klocuchy.h"

Game::Game():
    _screen(Klocuchy::Instance()->Screen()),
    _tetrion(new Tetrion),
    _current(new Tetramino),
    _next(new Tetramino),
    _nextView(new NextView),
    _scoreView(new ScoreView),
    _timer(new Timer),
    _score(0),
    _state(NotStarted)
{
    _tetrion->SetPosition(0, 0);
    _nextView->SetPosition(Tile::Size*Tetrion::TilesInRow+10, 0);
    _scoreView->SetPosition(Tile::Size*Tetrion::TilesInRow+10,
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
    _state = InProgress;
    Play();
}

void Game::Pause()
{
    // Pauses the game.
    // TODO:
    // Should show pause screen.
    _timer->Pause();
    _state = Paused;
}

void Game::Resume()
{
    _timer->Resume();
    _state = InProgress;
    Play();
}

void Game::Reset()
{
    _timer->SetInterval(InitialTiming);
    _tetrion->Clear();
    _current->Reset();
    _next->Reset();
    _state = NotStarted;
    _score = 0;
    _scoreView->SetScore(0);
    _nextView->SetTetramino(_next);
}

void Game::Play()
{
    SDL_Event event;
    bool play = true;
    bool inMove = false;
    bool moved;
    Tetramino::Direction dir, undo;
    Timer fps;
    Timer moveTimer(150);
    fps.SetInterval(1000/FPS);

    fps.Start();
    while (play)
    {
        // Process key events.
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    play = false;
                    Pause();
                    break;
                case SDLK_UP:
                    _current->Rotate(Tetramino::Left);
                    if (_tetrion->Collides(_current))
                        _current->Rotate(Tetramino::Right);
                    break;
                case SDLK_DOWN:
                    _current->Rotate(Tetramino::Right);
                    if (_tetrion->Collides(_current))
                        _current->Rotate(Tetramino::Left);
                    break;
                case SDLK_LEFT:
                    inMove = true;
                    moved = false;
                    moveTimer.Start();
                    dir = Tetramino::Left;
                    break;
                case SDLK_RIGHT:
                    inMove = true;
                    moved = false;
                    moveTimer.Start();
                    dir = Tetramino::Right;
                    break;
                case SDLK_SPACE:
                    inMove = true;
                    moved = false;
                    moveTimer.Start();
                    dir = Tetramino::Down;
                case SDLK_p:
                    Pause();
                    break;
                default:
                    break;
                }
            }
            else if (event.type == SDL_KEYUP)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:
                case SDLK_RIGHT:
                case SDLK_SPACE:
                    inMove = false;
                    break;
                default:
                    break;
                }
            }
        }

        // Move tetramino, if user wants it.
        if (inMove && (!moved || moveTimer.GetState() == Timer::Idle || moveTimer.Finished()))
        {
            moved = true;
            _current->Move(dir);
            switch (dir)
            {
            case Tetramino::Down:
                undo = Tetramino::Up;
                break;
            case Tetramino::Left:
                undo = Tetramino::Right;
                break;
            case Tetramino::Right:
                undo = Tetramino::Left;
            default:
                break;
            }

            if (_tetrion->Collides(_current))
            {
                _current->Move(undo);
                inMove = false;
                moveTimer.SetState(Timer::Idle);
            }
        }

        // Move tetramino down, if timer has finished.
        if (_timer->Finished())
        {
            _current->Move(Tetramino::Down);
            // It tetramino collides with the "floor" - try to add it to the rest
            // of the boxes.
            if (_tetrion->Collides(_current))
            {
                _current->Move(Tetramino::Up);
                // There's no room for anoter tetramino. Game over.
                if (!_tetrion->Adapt(_current))
                {
                    play = false;
                    _state = NotStarted;
                }
                else
                {
                    // Update score and generate new tetramino.
                    _score += _tetrion->Check();
                    _scoreView->SetScore(_score);
                    Tetramino *tmp = _current;
                    _current = _next;
                    _next = tmp;
                    _next->Reset();
                    _nextView->SetTetramino(_next);

                    // TODO:
                    // lowering the _timer's interval depending on _score
                }
            }
            _timer->Start();
        }

        // Draw everything.
        if (fps.Finished())
        {
            SDL_FillRect(_screen, 0, 0);
            _tetrion->Show();
            _current->Show();
            _nextView->Show();
            _scoreView->Show();
            SDL_Flip(_screen);
            fps.Start();
        }
        else
        {
            SDL_Delay(1000/FPS - fps.Elapsed());
        }
    }
}
