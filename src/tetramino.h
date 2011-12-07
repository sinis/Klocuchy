#ifndef TETRAMINO_H
#define TETRAMINO_H

#include <SDL/SDL.h>
#include "tile.h"

class Tetramino
{
public:

    enum Shape {
        I, T, J, L, O, S, Z
    };

    enum Direction {
        Down,
        Left,
        Right
    };

    enum {
        Shapes = 7
    };

    Tetramino();
    ~Tetramino();

    void Show();
    void Move(Direction dir);
    void Rotate(Direction dir);
    Tile **GetTiles() { return _tiles; }
    int GetX() const { return _x; }
    int GetY() const { return _y; }
    void Reset();

protected:
    void SetShape(Shape shape);
    void CleanTiles();

private:
    SDL_Surface *_screen;
    Tile **_tiles;
    int _x;
    int _y;
};

#endif // TETRAMINO_H
