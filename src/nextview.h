#ifndef NEXTVIEW_H
#define NEXTVIEW_H

#include <SDL/SDL.h>
#include "tetramino.h"
#include "frame.h"

class NextView
{
public:
    NextView();
    ~NextView();

    void SetPosition(int x, int y);
    void SetTetramino(Tetramino *tetramino) { _tetramino = tetramino; }
    void Show();

private:
    SDL_Surface *_screen;
    int _x;
    int _y;
    Frame *_frame;
    Tetramino *_tetramino;
};

#endif // NEXTVIEW_H
