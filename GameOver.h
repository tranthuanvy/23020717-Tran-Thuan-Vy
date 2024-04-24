#ifndef GAME_OVER_H
#define GAME_OVER_H
#include"CommonFunc.h"
#include"TextObject.h"
#define kMenuItemNum1 2

class GameOver: public BaseObject
{
public:
    GameOver();
    ~GameOver();

public:

    int ShowGameOver(SDL_Renderer* des,TTF_Font* font);
    bool CheckFocusWithRectGameOver(const int& x,const int& y,const SDL_Rect& rect);

};


#endif // GAME_OVER_H
