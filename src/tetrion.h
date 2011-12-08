#ifndef TETRION_H
#define TETRION_H

#include <SDL/SDL.h>
#include <vector>
#include "frame.h"
#include "tile.h"
#include "tetramino.h"
#include "background.h"

class Tetrion
{
public:

    enum {
        TilesInRow = 10,
        TilesInCol = 20
    };

    Tetrion();
    ~Tetrion();

    void Show();
    void SetPosition(int x, int y);
    bool Collides(Tetramino *tetramino);
    void Adapt(Tetramino *tetramino);
    int Check();

protected:
    void RemoveRow(int row);

private:
    SDL_Surface *_screen;
    Background *_background;
    Frame *_frame;
    int _x;
    int _y;
    Tile **_tetrion;
};

#endif // TETRION_H
