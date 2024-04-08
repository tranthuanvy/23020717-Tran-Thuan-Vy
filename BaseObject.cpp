
#include "BaseObject.h"
 BaseObject::BaseObject()
 {

     p_object_=NULL;

     rect_.x=0;
     rect_.y=0;
     rect_.w=0;
     rect_.h=0;

 }
  BaseObject::~BaseObject()
 {
  Free();
 }
 bool BaseObject::LoadImg( const std::string& path,SDL_Renderer* gRenderer)
 {
      SDL_Texture* newTexture = nullptr;
     SDL_Surface* loadedSurface = IMG_Load(path.c_str());
     if (loadedSurface == nullptr)
    {
        std::cout << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    else
    {
            SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 255, 255 )) ;
            newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
              if (newTexture == nullptr)
        {
            std::cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
        }
          else
            {
            rect_.w= loadedSurface-> w;
            rect_.h= loadedSurface->h;
          }
          SDL_FreeSurface(loadedSurface);

 }
     p_object_=newTexture;
     return p_object_!= nullptr;
 }

 void BaseObject::renderTexture(SDL_Renderer* des,  const SDL_Rect* clip /*= NULL*/ ) {
    // Tạo một SDL_Rect để chỉ định vị trí và kích thước của texture trên bề mặt vẽ
    SDL_Rect dstRect = {rect_.x,rect_.y,rect_.w,rect_.h};

    // Vẽ texture lên bộ kết xuất
    SDL_RenderCopy(des, p_object_, clip, &dstRect);
}

void BaseObject::Free(){
    SDL_DestroyTexture(p_object_);
    p_object_ = nullptr;
    rect_.w=0;
    rect_.h=0;
}
