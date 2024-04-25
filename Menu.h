#ifndef MENU_H_
#define MENU_H_

#include"CommonFunc.h"
#include"TextObject.h"
#define kMenuItemNum 2


class Menu: public BaseObject
{
public:
    Menu();
    ~Menu();

public:

    int ShowMenu(SDL_Renderer* des,TTF_Font* font);


};



#endif // MENU_H_
