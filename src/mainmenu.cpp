#include "mainmenu.h"
#include "klocuchy.h"
#include "defines.h"
#include "timer.h"

MainMenu::MainMenu():
    _screen(0),
    _start(0),
    _resume(0),
    _highscore(0),
    _about(0),
    _quit(0)
{}

MainMenu::~MainMenu()
{
    if (_start)
        delete _start;
    if (_resume)
        delete _resume;
    if (_highscore)
        delete _highscore;
    if (_about)
        delete _about;
    if (_quit)
        delete _quit;
}

bool MainMenu::Initialize()
{
    int x = (Klocuchy::Width - ButtonWidth)/2;
    int y = 0;
    _screen = Klocuchy::Instance()->Screen();

    _start = CreateButton("Start", x, y);
    if (!_start)
        return false;

    y += 64;
    _resume = CreateButton("Resume", x, y);
    if (!_resume)
        return false;
    _resume->SetEnabled(false);

    y += 64;
    _highscore = CreateButton("Highscore", x, y);
    if (!_highscore)
        return false;

    y += 64;
    _about = CreateButton("About", x, y);
    if (!_about)
        return false;

    y += 64;
    _quit = CreateButton("Quit", x, y);
    if (!_quit)
        return false;

    return true;
}

Button *MainMenu::CreateButton(std::string text, int x, int y)
{
    Button *button = new Button;

    if (!button->SetImage(BUTTON, ButtonWidth, ButtonHeight))
    {
        delete button;
        return 0;
    }

    if (!button->SetText(text))
    {
        delete button;
        return 0;
    }

    button->SetPosition(x, y);
    return button;
}

MainMenu::ButtonID MainMenu::Exec()
{
    ButtonID id = None;
    SDL_Event event;
    Timer timer(Second/MenuFPS);
    bool quit = false;

    Show();
    timer.Start();
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    quit = true;
                break;
            case SDL_MOUSEMOTION:
                OnMouseMotion(event.motion.x, event.motion.y);
                break;
            case SDL_MOUSEBUTTONDOWN:
                id = OnMouseClick(event.motion.x, event.motion.y);
                if (id != None)
                    quit = true;
                break;
            }
        }

        if (timer.Finished())
        {
            Show();
            timer.Start();
        }
        else
        {
            SDL_Delay(Second/MenuFPS - timer.Elapsed());
        }
    }

    Show();
    SDL_Delay(200);

    return id;
}

void MainMenu::Show()
{
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = Klocuchy::Width;
    rect.h = Klocuchy::Height;
    Uint32 color = SDL_MapRGB(_screen->format, 0, 0, 0);
    SDL_FillRect(_screen, &rect, color);

    _start->Show();
    _resume->Show();
    _highscore->Show();
    _about->Show();
    _quit->Show();

    SDL_Flip(_screen);
}

void MainMenu::OnMouseMotion(int x, int y)
{
    if (_start->IsMouseOver(x, y))
        _start->OnMouseOver();
    else _start->OnMouseOut();

    if (_resume->IsMouseOver(x, y))
        _resume->OnMouseOver();
    else _resume->OnMouseOut();

    if (_highscore->IsMouseOver(x, y))
        _highscore->OnMouseOver();
    else _highscore->OnMouseOut();

    if (_about->IsMouseOver(x, y))
        _about->OnMouseOver();
    else _about->OnMouseOut();

    if (_quit->IsMouseOver(x, y))
        _quit->OnMouseOver();
    else _quit->OnMouseOut();
}

MainMenu::ButtonID MainMenu::OnMouseClick(int x, int y)
{
    ButtonID id = None;

    if (_start->IsEnabled() && _start->IsMouseOver(x, y))
    {
        _start->OnPress();
        id = Start;
        _resume->SetEnabled(true);
    }

    if (_resume->IsEnabled() && _resume->IsMouseOver(x, y))
    {
        _resume->OnPress();
        id = Resume;
    }

    if (_highscore->IsEnabled() && _highscore->IsMouseOver(x, y))
    {
        _highscore->OnPress();
        id = Highscore;
    }

    if (_about->IsEnabled() && _about->IsMouseOver(x, y))
    {
        _about->OnPress();
        id = About;
    }

    if (_quit->IsEnabled() && _quit->IsMouseOver(x, y))
    {
        _quit->OnPress();
        id = Quit;
    }

    return id;
}

void MainMenu::EnableResume(bool enable)
{
    _resume->SetEnabled(enable);
}
