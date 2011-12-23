#include "nextview.h"
#include <SDL/SDL.h>
#include "klocuchy.h"
#include "tile.h"

NextView::NextView():
    _screen(Klocuchy::Instance()->Screen()),
    _x(0), _y(0),
    _frame(new Frame),
    _tetramino(0)
{
    _frame->SetSize(Tile::Size*4+4, Tile::Size*4+4);
    _frame->SetColor(SDL_MapRGB(_screen->format, 200, 200, 200),
                     SDL_MapRGB(_screen->format, 100, 100, 100));
}

NextView::~NextView()
{
    delete _frame;
}

void NextView::SetPosition(int x, int y)
{
    _x = x+2;
    _y = y+2;
    _frame->SetPosition(x, y);
}

void NextView::Show()
{
    _frame->Show();
    _tetramino->Show(0, 0, _x, _y);
}
