#include "tetrion.h"
#include <SDL/SDL.h>
#include <vector>
#include "klocuchy.h"
#include "defines.h"

Tetrion::Tetrion():
    _screen(Klocuchy::Instance()->Screen()),
    _background(new Background),
    _frame(new Frame),
    _x(0), _y(0),
    _tetrion(0)
{
    _tetrion = new Tile*[TilesInRow];
    for (int i = 0; i < TilesInRow; ++i)
        _tetrion[i] = new Tile[TilesInCol];

    _frame->SetColor(SDL_MapRGB(_screen->format, 200, 200, 200),
                     SDL_MapRGB(_screen->format, 100, 100, 100));
    _frame->SetSize(Tile::Size*TilesInRow+2, Tile::Size*TilesInCol+2);

    _background->SetPosition(_x+2, _y+2);
    _background->SetInterval(300);
    _background->SetSprite(BACKGROUND, 3, Tile::Size*TilesInRow, Tile::Size*TilesInCol);
}

Tetrion::~Tetrion()
{
    delete _background;
    delete _frame;
    for (int i = 0; i < TilesInRow; ++i)
        delete [] _tetrion[i];
    delete [] _tetrion;
}

void Tetrion::Show()
{
    _background->Show();
    _frame->Show();
    for (int i = 0; i < TilesInRow; ++i)
    {
        for (int j = 0; j < TilesInCol; ++j)
        {
            _tetrion[i][j].Show(Tile::Size * i + _x,
                                Tile::Size * j + _y);
        }
    }
}

void Tetrion::SetPosition(int x, int y)
{
    _x = x+2;
    _y = y+2;
    _frame->SetPosition(x, y);
    _background->SetPosition(_x, _y);
}

bool Tetrion::Collides(Tetramino *tetramino)
{
    int dx = tetramino->GetX();
    int dy = tetramino->GetY();

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (tetramino->At(i, j)->GetColor() != Tile::None)
            {
                if (i+dx < 0 || i+dy >= TilesInRow ||
                    j+dy < 0 || j+dy >= TilesInCol)
                    return true;
                else if (_tetrion[i+dx][j+dy].GetColor() != Tile::None)
                    return true;
            }
        }
    }

    return false;
}

bool Tetrion::Adapt(Tetramino *tetramino)
{
    // If tetramino is out of tetrion then game is over.
    int dx = tetramino->GetX();
    int dy = tetramino->GetY();

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (tetramino->At(i, j)->GetColor() == Tile::None)
                continue;
            if (j+dy < 0)
                return false; // Game over. No room for new tetramino.
            _tetrion[i+dx][j+dy].SetColor(tetramino->At(i, j)->GetColor());
        }
    }

    return false;
}

int Tetrion::Check()
{
    // This method:
    // 1. Finds filled rows.
    // 2. Marks tiles in these as "white" (to be removed) and Show()s.
    // 3. Removes these tiles (just copies tiles above onto them).
    // 4. Returns score.
    // It should be invoked after Adapt().
    std::vector<int> rows;
    int score;
    bool full;

    // Find filled.
    for (int i = 0; i < TilesInRow; ++i)
    {
        full = true;
        for (int j = 0; j < TilesInCol; ++j)
        {
            if (_tetrion[i][j].GetColor() == Tile::None)
            {
                full = false;
                break;
            }
        }
        if (full)
            rows.push_back(i);
    }

    // Set score.
    score = rows.size()*rows.size();

    if (!score)
        return score;

    // Mark tiles.
    for (unsigned int i = 0; i < rows.size(); ++i)
        for (int j = 0; j < TilesInCol; ++j)
            _tetrion[rows[i]][j].SetColor(Tile::White);

    // Show them.
    Show();
    SDL_Delay(100);

    // And remove.
    for (unsigned int i = 0; i < rows.size(); ++i)
    {
        RemoveRow(rows[i]);
    }

    return score;
}

void Tetrion::RemoveRow(int row)
{
    // If row == 0 then it must be filled with Tile::None color.
    // If not - copy colors from tiles above.
    while (row)
    {
        for (int i = 0; i < TilesInRow; ++i)
            _tetrion[i][row].SetColor(_tetrion[i][row-1].GetColor());
        --row;
    }

    // Set highest row as Tile::None color.
    for (int i = 0; i < TilesInRow; ++i)
        _tetrion[i][0].SetColor(Tile::None);
}

void Tetrion::Clear()
{
    for (int i = 0; i < TilesInRow; ++i)
        for (int j = 0; j < TilesInCol; ++j)
            _tetrion[i][j].SetColor(Tile::None);
}
