#include "tetramino.h"
#include <cstdlib>
#include "klocuchy.h"

Tetramino::Tetramino():
    _screen(Klocuchy::Instance()->Screen()),
    _tiles(0),
    _x(0), _y(0)
{
    _tiles = new Tile*[4];
    for (int i = 0; i < 4; ++i)
        _tiles[i] = new Tile[4];
    Reset();
}

Tetramino::~Tetramino()
{
    for (int i = 0; i < 4; ++i)
        delete [] _tiles[i];
    delete [] _tiles;
}

void Tetramino::Show()
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (_tiles[i][j].GetColor() != Tile::None)
                _tiles[i][j].Show(Tile::Size * i + _x,
                                  Tile::Size * j + _y);
        }
    }
}

void Tetramino::Move(Direction dir)
{
    switch (dir)
    {
    case Down: ++_y; break;
    case Left: --_x; break;
    case Right: ++_x; break;
    }
}

void Tetramino::Reset()
{
    int shape = rand() % static_cast<int>(Shapes);
    CleanTiles();
    SetShape(static_cast<Shape>(shape));
}

void Tetramino::CleanTiles()
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; j++)
            _tiles[i][j].SetColor(Tile::None);
}

void Tetramino::SetShape(Shape shape)
{
    if (shape == I)
    {
        _tiles[1][0].SetColor(Tile::Green);
        _tiles[1][1].SetColor(Tile::Green);
        _tiles[1][2].SetColor(Tile::Green);
        _tiles[1][3].SetColor(Tile::Green);
    }
    else if (shape == J)
    {
        _tiles[2][0].SetColor(Tile::Blue);
        _tiles[2][1].SetColor(Tile::Blue);
        _tiles[2][2].SetColor(Tile::Blue);
        _tiles[1][2].SetColor(Tile::Blue);
    }
    else if (shape == L)
    {
        _tiles[1][0].SetColor(Tile::Orange);
        _tiles[1][1].SetColor(Tile::Orange);
        _tiles[1][2].SetColor(Tile::Orange);
        _tiles[2][2].SetColor(Tile::Orange);
    }
    else if (shape == O)
    {
        _tiles[1][0].SetColor(Tile::Red);
        _tiles[2][0].SetColor(Tile::Red);
        _tiles[1][1].SetColor(Tile::Red);
        _tiles[1][2].SetColor(Tile::Red);
    }
    else if (shape == S)
    {
        _tiles[2][0].SetColor(Tile::Violet);
        _tiles[3][0].SetColor(Tile::Violet);
        _tiles[1][1].SetColor(Tile::Violet);
        _tiles[2][1].SetColor(Tile::Violet);
    }
    else if (shape == T)
    {
        _tiles[1][0].SetColor(Tile::Grey);
        _tiles[2][0].SetColor(Tile::Grey);
        _tiles[3][0].SetColor(Tile::Grey);
        _tiles[2][1].SetColor(Tile::Grey);
    }
    else
    {
        _tiles[1][0].SetColor(Tile::Yellow);
        _tiles[2][0].SetColor(Tile::Yellow);
        _tiles[2][1].SetColor(Tile::Yellow);
        _tiles[3][1].SetColor(Tile::Yellow);
    }
}

void Tetramino::Rotate(Direction dir)
{
    // TODO
}