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


};


#endif // GAME_OVER_H
