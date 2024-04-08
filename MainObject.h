#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H
#include "CommonFunc.h"
#include "BaseObject.h"
class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject();
   enum WalkType
   {
    WALK_RIGHT=0,
    WALK_LEFT=1,
   };
    virtual bool LoadImg( const std::string& path,SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandelInputAction(SDL_Event events, SDL_Renderer* screen);
    void set_clips();
private:
    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int width_frame_;
    int height_frame_;

    SDL_Rect frame_clip_[8];
    Input input_type_;
    int frame_;
    int status_;


};


#endif // MAIN_OBJECT_H
