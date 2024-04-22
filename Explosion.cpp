#include"Explosion.h"

ExplosionObject::ExplosionObject()
{
   width_frame_=0;
   height_frame_=0;
   frame_=0;
}

ExplosionObject::~ExplosionObject()
{

}

bool ExplosionObject:: LoadImg(std::string path,SDL_Renderer* screen)
{
    bool ret =BaseObject::LoadImg(path,screen);
    if(ret!=NULL)
    {
        width_frame_=rect_.w/4;
        height_frame_=rect_.h/2;
    }
    return ret ;
}

void ExplosionObject::set_clip()
{

    if(width_frame_>0&& height_frame_>0)
    {
        frame_clip_[0].x=0;
        frame_clip_[0].y=0;
        frame_clip_[0].w=width_frame_;
        frame_clip_[0].h=height_frame_;

        frame_clip_[1].x=width_frame_;
        frame_clip_[1].y=0;
        frame_clip_[1].w=width_frame_;
        frame_clip_[1].h=height_frame_;

        frame_clip_[2].x=2*width_frame_;
        frame_clip_[2].y=0;
        frame_clip_[2].w=width_frame_;
        frame_clip_[2].h=height_frame_;

        frame_clip_[3].x=3*width_frame_;
        frame_clip_[3].y=0;
        frame_clip_[3].w=width_frame_;
        frame_clip_[3].h=height_frame_;

        frame_clip_[4].x=0;
        frame_clip_[4].y=height_frame_;
        frame_clip_[4].w=width_frame_;
        frame_clip_[4].h=height_frame_;

        frame_clip_[5].x=width_frame_;
        frame_clip_[5].y=height_frame_;
        frame_clip_[5].w=width_frame_;
        frame_clip_[5].h=height_frame_;

        frame_clip_[6].x=2*width_frame_;
        frame_clip_[6].y=height_frame_;
        frame_clip_[6].w=width_frame_;
        frame_clip_[6].h=height_frame_;

        frame_clip_[7].x=3*width_frame_;
        frame_clip_[7].y=height_frame_;
        frame_clip_[7].w=width_frame_;
        frame_clip_[7].h=height_frame_;


    }
}

void ExplosionObject:: Show(SDL_Renderer* des)
{

    SDL_Rect* currect_clip=&frame_clip_[frame_];
    SDL_Rect renderQuad ={ rect_.x,rect_.y,width_frame_,height_frame_};
    if(currect_clip!=NULL)
    {
        renderQuad.w= currect_clip->w;
        renderQuad.h= currect_clip->h;
    }
    SDL_RenderCopy(des,p_object_,currect_clip,&renderQuad);
}

