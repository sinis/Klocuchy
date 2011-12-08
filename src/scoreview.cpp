#include "scoreview.h"
#include <SDL/SDL_ttf.h>
#include <sstream>
#include "klocuchy.h"
#include "defines.h"
#include "gamedata.h"

ScoreView::ScoreView():
    _screen(Klocuchy::Instance()->Screen()),
    _label(0),
    _scoreSurface(0),
    _score(0),
    _x(0),
    _y(0)
{
    _color.r = _color.g = _color.b = 128;
    SetScore(0); // To generate _screenSurface
    _label = TTF_RenderText_Blended(GameData::Instance()->GetFont(FONT),
        "Score:", _color);
}

ScoreView::~ScoreView()
{
    if (_label)
        SDL_FreeSurface(_label);
    if (_scoreSurface)
        SDL_FreeSurface(_scoreSurface);
}

void ScoreView::SetScore(int score)
{
    std::stringstream ss;

    if (_scoreSurface)
        SDL_FreeSurface(_scoreSurface);
    _score = score;

    ss << score;
    _scoreSurface = TTF_RenderText_Blended(GameData::Instance()->GetFont(FONT),
        ss.str().c_str(), _color);
}

void ScoreView::SetPosition(int x, int y)
{
    _x = x;
    _y = y;
}

void ScoreView::Show()
{
    SDL_Rect rect;
    rect.x = _x;
    rect.y = _y;
    SDL_BlitSurface(_label, 0, _screen, &rect);
    rect.y += _label->h;
    SDL_BlitSurface(_scoreSurface, 0, _screen, &rect);
}