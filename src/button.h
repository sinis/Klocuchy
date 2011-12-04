#ifndef BUTTON_H
#define BUTTON_H

#include <SDL/SDL.h>
#include <string>

class Button
{
public:
    Button();
    ~Button();

    enum State {
        MouseOut,
        MouseOver,
        Pressed
    };

    bool SetText(std::string text);
    bool SetImage(std::string fileName, int width, int height);
    void SetPosition(int x, int y) { _x = x; _y = y; }
    void SetEnabled(bool enabled);

    State GetState() const { return _state; }
    bool IsEnabled() const { return _enabled; }
    bool IsMouseOver(int x, int y);
    void OnMouseOver();
    void OnMouseOut();
    void OnPress();

    void Show();

private:
    std::string _text;
    int _x;
    int _y;
    bool _enabled;
    int _width;
    int _height;
    State _state;
    SDL_Surface *_screen;
    SDL_Surface *_image;
    SDL_Surface *_label;
};

#endif // BUTTON_H
