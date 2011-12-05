#ifndef TILE_H
#define TILE_H

#include <SDL/SDL.h>

class Tile
{
public:
    enum Color {
        None,
        Blue,
        Green,
        Orange,
        Red,
        Violet,
        Grey,
        Yellow
    };

    Tile(Color color = None);

    void SetColor(Color color);
    Color GetColor() const { return _color; }
    void Show(int x, int y);

private:
    Color _color;
    SDL_Surface *_image;
};

#endif // TILE_H
