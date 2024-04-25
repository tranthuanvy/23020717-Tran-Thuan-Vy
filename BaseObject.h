#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include"CommonFunc.h"

class BaseObject
{
protected :
    SDL_Rect rect_;
    SDL_Texture* p_object_;

public :
    BaseObject();
    ~BaseObject();

    void SetRect(const int& x,const int& y){ rect_.x=x,rect_.y=y;}
    SDL_Rect GetRect()const {return rect_;}

    SDL_Texture* GetObject()const{ return p_object_;}
    bool LoadImg(const std::string path,SDL_Renderer* gRenderer);
    void renderTexture(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void renderTextureGameBackGround(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void Free();

};
#endif // BASE_OBJECT_H_
