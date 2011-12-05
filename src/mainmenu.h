#ifndef MAINMENU_H
#define MAINMENU_H

#include <string>
#include "button.h"

class MainMenu
{
public:
    MainMenu();
    ~MainMenu();

    enum ButtonID {
        None,
        Start,
        Resume,
        Highscore,
        About,
        Quit
    };

    enum {
        ButtonWidth = 120,
        ButtonHeight = 60,
        Second = 1000,
        MenuFPS = 30
    };

    bool Initialize();
    ButtonID Exec();

protected:
    Button *CreateButton(std::string text, int x, int y);
    void Show();
    void OnMouseMotion(int x, int y);
    ButtonID OnMouseClick(int x, int y);

private:
    SDL_Surface *_screen;
    Button *_start;
    Button *_resume;
    Button *_highscore;
    Button *_about;
    Button *_quit;
};

#endif // MAINMENU_H
