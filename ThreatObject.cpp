#include"ThreatObject.h"

ThreatObject::ThreatObject()
{
    width_frame_=0;
    height_frame_=0;
    x_val_=0;
    y_val_=0;
    x_pos_=0;
    y_pos_=0;
    on_ground_=0;
    frame_=0;
}
ThreatObject::~ThreatObject()
{

}
bool ThreatObject::LoadImg(std::string path,SDL_Renderer* screen)
{
    bool ret =BaseObject::LoadImg(path,screen);
    if(ret)
    {
        width_frame_=rect_.w/ThreatFrameNum;
        height_frame_=rect_.h;

    }
    return ret;
}

SDL_Rect ThreatObject:: GetRectFrame()
{
    SDL_Rect rect;
    rect.x=rect_.x;
    rect.y=rect_.y;
    rect.w=width_frame_;
    rect.h=height_frame_;

    return rect;

}

void ThreatObject:: set_clips()
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

        frame_clip_[4].x=4*width_frame_;
        frame_clip_[4].y=0;
        frame_clip_[4].w=width_frame_;
        frame_clip_[4].h=height_frame_;

        frame_clip_[5].x=5*width_frame_;
        frame_clip_[5].y=0;
        frame_clip_[5].w=width_frame_;
        frame_clip_[5].h=height_frame_;

        frame_clip_[6].x=6*width_frame_;
        frame_clip_[6].y=0;
        frame_clip_[6].w=width_frame_;
        frame_clip_[6].h=height_frame_;

        frame_clip_[7].x=7*width_frame_;
        frame_clip_[7].y=0;
        frame_clip_[7].w=width_frame_;
        frame_clip_[7].h=height_frame_;


    }
}

void ThreatObject:: Show(SDL_Renderer* des)
{
    rect_.x=x_pos_ - map_x_;//tru di khoang cuon chieu
    rect_.y=y_pos_ - map_y_;


     frame_++;
     if(frame_>=8)
    {
        frame_=0;
    }
    SDL_Rect* currect_clip=&frame_clip_[frame_];
    SDL_Rect renderQuad ={ rect_.x,rect_.y,width_frame_,height_frame_};
    SDL_RenderCopy(des,p_object_,currect_clip,&renderQuad);
}

  void ThreatObject::RemoveBullet(const int& index)
{
    int size =list_bullet_.size();
    if(size>0&&index<size)
    {
        BulletObject* p_bullet =list_bullet_.at(index);
        list_bullet_.erase(list_bullet_.begin()+index);
        if(p_bullet!=NULL)
        {
            delete p_bullet;
            p_bullet=NULL;
        }
    }
}

void ThreatObject::DoPlayer(map& map_data)
{
    x_val_=0;

    y_val_+=0.8; //0.8:GRAVITY_SPEED

    if(y_val_>=MAX_FALL_SPEED)
    {
        y_val_= MAX_FALL_SPEED;
    }

    CheckToMap(map_data);


}

void ThreatObject::CheckToMap(map& map_data)
{
   int x1=0;
   int x2=0;

   int y1=0;
   int y2=0;



   int height_min = height_frame_< TILE_SIZE ? height_frame_:TILE_SIZE;

   x1= (x_pos_ + x_val_)/TILE_SIZE;
   x2=(x_pos_+x_val_+width_frame_ -1 )/TILE_SIZE;

   y1=(y_pos_)/TILE_SIZE;
   y2=(y_pos_+height_min-1)/TILE_SIZE;

   if(x1>=0&& x2<=MAX_MAP_X&&y1>=0&&y2<MAX_MAP_Y)
   {
       if(x_val_>0)// moving to right
       {
          int val1=  map_data.tile[y1][x2];
          int val2=  map_data.tile[y2][x2];

            if((val1!=BLANK_TILE &&val1!=COIN_TILE&&val1!=OSTACLE1&&val1!=OSTACLE2)||( val2!=BLANK_TILE&&val2!=COIN_TILE&&val2!=OSTACLE1&&val2!=OSTACLE2))

           {
               x_pos_ =x2*TILE_SIZE;
               x_pos_-=width_frame_+1;
               x_val_=0;

           }
        }
        else if(x_val_<0)
        {
            int val1=  map_data.tile[y1][x1];
            int val2=  map_data.tile[y2][x1];

            if((val1!=BLANK_TILE &&val1!=COIN_TILE&&val1!=OSTACLE1&&val1!=OSTACLE2)||( val2!=BLANK_TILE&&val2!=COIN_TILE&&val2!=OSTACLE1&&val2!=OSTACLE2))

           {
               x_pos_ =(x1+1)*TILE_SIZE;
               x_val_=0;

           }
        }

   }



//check vertical

   int width_min= width_frame_< TILE_SIZE ? width_frame_: TILE_SIZE;

     x1=(x_pos_)/TILE_SIZE;
     x2=(x_pos_+width_min)/TILE_SIZE;

     y1=(y_pos_+y_val_)/TILE_SIZE;
     y2=(y_pos_+y_val_+height_frame_-1)/TILE_SIZE;

  if(x1>=0&&x2< MAX_MAP_X && y1>=0&&y2< MAX_MAP_Y)
  {
      if(y_val_>0)//roi tu do
      {
          int val1=map_data.tile[y2][x1];
          int val2=  map_data.tile[y2][x2];

               if((val1!=BLANK_TILE&&val1!=COIN_TILE&&val1!=OSTACLE1&&val1!=OSTACLE2)|| (val2!=BLANK_TILE&&val2!=COIN_TILE&&val2!=OSTACLE1&&val2!=OSTACLE2))
          {
              y_pos_=y2*TILE_SIZE;
              y_pos_ -=(height_frame_+1);
              y_val_=0;
            on_ground_=true;//nhân vật chưa chạm đến màn hình do hình ảnh góc thừa khoảng trắng

          }

          }

    else if(y_val_<0)
    {
          int val1=map_data.tile[y1][x1];
          int val2=map_data.tile[y1][x2];


            if((val1!=BLANK_TILE&&val2!=COIN_TILE&&val1!=OSTACLE1&&val1!=OSTACLE2)||( val2!=BLANK_TILE&&val2!=COIN_TILE&&val2!=OSTACLE1&&val2!=OSTACLE2))
            {
                y_pos_=(y1+1)*TILE_SIZE;
                y_val_=0;
            }

          }
  }
  x_pos_+=x_val_;
  y_pos_+=y_val_;

if(x_pos_+width_frame_>map_data.max_x_)
{
    x_pos_=map_data.max_x_-width_frame_-1;// tru sai so
}

}
void ThreatObject::InitBullet(BulletObject* p_bullet,SDL_Renderer* screen)
{
    if(p_bullet!=NULL)
    {
        p_bullet->set_bullet_type(BulletObject::SPHERE_BULLET);
        bool ret = p_bullet->LoadImgBullet(screen);
        if(ret)
       {
        p_bullet->set_is_move(true);
        p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
        p_bullet->SetRect(rect_.x+5,y_pos_ +10);
        p_bullet->set_x_val(15);
        list_bullet_.push_back(p_bullet);
       }

    }
}

void ThreatObject::MakeBullet(SDL_Renderer* screen,const int& x_limit,const int& y_limit)
{
    for(int i=0;i< list_bullet_.size();i++)
    {
        BulletObject*p_bullet=list_bullet_.at(i);
        if(p_bullet!=NULL)
        {
            if(p_bullet->get_is_move())
            {
                int bullet_distance=rect_.x+ width_frame_ - p_bullet->GetRect().x;
                if(bullet_distance<650&& bullet_distance>0)
                {
                   p_bullet->HandleMove(x_limit,y_limit);
                   p_bullet->renderTexture(screen);
                }
                else
                {
                    p_bullet->set_is_move(false);
                }
            }
            else//khi vien dan qua ma hinh
            {
               p_bullet->set_is_move(true) ;
               p_bullet->SetRect(rect_.x+5,y_pos_+10);
            }
        }
    }
}

















