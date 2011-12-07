#include "nextview.h"
#include "klocuchy.h"
#include "tile.h"

NextView::NextView():
    _screen(Klocuchy::Instance()->Screen()),
    _x(0), _y(0),
    _frame(new Frame),
    _tetramino(0)
{
    _frame->SetSize(Tile::Size*4+4, Tile::Size*4+4);
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
    _tetramino->Show(_x, _y);
}
