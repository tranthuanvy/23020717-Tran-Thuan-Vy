#include"GameOver.h"
GameOver::GameOver()
{

}
GameOver::~GameOver()
{

}

bool GameOver:: CheckFocusWithRectGameOver(const int& x,const int& y,const SDL_Rect& rect)
{
    if(y>=350&& y<=400&&x>=SCREEN_WIDTH*0.5-210&&x<= SCREEN_WIDTH*0.5+150)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int GameOver::ShowGameOver(SDL_Renderer* des,TTF_Font* font)
{
    bool ret= LoadImg("C:/Users/Admin/Pictures/MenuImg.png", des);
    if(!ret){std::cout<<"loooic"<<std::endl;}


    SDL_Rect pos_arr[kMenuItemNum1];
    pos_arr[0].x=SCREEN_WIDTH*0.5-210;
    pos_arr[0].y=350;

    pos_arr[1].x=SCREEN_WIDTH*0.5-270;
    pos_arr[1].y=200;



   TextObject text_menu[kMenuItemNum1];

    text_menu[0].SetText("PLAY AGAIN");
    text_menu[0].SetColor(TextObject::BLACK_TEXT);
    text_menu[0].SetRect( pos_arr[0].x, pos_arr[0].y);

    text_menu[1].SetText("YOU LOSE");
    text_menu[1].SetColor(TextObject::RED_TEXT);
    text_menu[1].SetRect( pos_arr[1].x, pos_arr[1].y);




    bool selected[kMenuItemNum1]={0,0};
    int xm=0;
    int ym=0;
    SDL_Event m_event;
    while(true)
    {
        BaseObject::renderTexture(des);
        for(int i=0;i<kMenuItemNum1;i++)
        {
            text_menu[i].LoadRenderText(font ,des);
             text_menu[i].RenderText(des,pos_arr[i].x, pos_arr[i].y);

        }

    while(SDL_PollEvent(&m_event))
    {
        switch(m_event.type)
        {
          case SDL_QUIT:
            return 1;
          case SDL_MOUSEMOTION:
            {
              xm=m_event.motion.x;
              ym=m_event.motion.y;

              for(int i=0;i<kMenuItemNum1;i++)
              {
                if(CheckFocusWithRectGameOver(xm,ym,text_menu[i].GetRect()))
                {
                    if(selected[i]==false)
                    {
                        selected[i]=1;
                        text_menu[i].SetColor(TextObject::RED_TEXT);

                    }
                }
                else
                {
                    if(selected[i]==true)
                    {
                        selected[i]=0;
                        text_menu[i].SetColor(TextObject::BLACK_TEXT);

                    }
                }
              }
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
                {
                  xm=m_event.button.x;
                  ym=m_event.button.y;

              for(int i=0;i<kMenuItemNum1;i++)
              {
                if(CheckFocusWithRectGameOver(xm,ym,text_menu[i].GetRect()))
                {
                    return i;
                }

              }
            }
                break;
          case SDL_KEYDOWN:
            if(m_event.key.keysym.sym==SDLK_ESCAPE)
            {
                return 1;
            }
          default:
            break;
        }
   }

     SDL_RenderPresent(des);
 }

     return 1;
}
