#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H
#include<vector>
#include "CommonFunc.h"
#include "BaseObject.h"
#include"BulletObject.h"

#define PLAYERJUMPVALUE 20
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 8
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

    void DoPlayer(map& map_data);
    void CheckToMap(map& map_data);
    void SetMapxy(const int map_x, const int map_y){ map_x_=map_x, map_y_=map_y;};//tinh toan gia tri x, y mep ban do
    void Mapwhenrunner(map& map_data);
    SDL_Rect GetRectFrame();

    void setbulletlist(std::vector<BulletObject*>bullet_list)
    {
        bullet_list_=bullet_list;
    }
    std:: vector<BulletObject*>get_bullet_list()const{return bullet_list_;}
    void RemoveBullet(const int& index);
    void  HandleBullet(SDL_Renderer* des);
    void increasemoney();
private:
    int moneycount ;
    std::vector<BulletObject*>bullet_list_;
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
    bool on_ground_;

    int map_x_;
    int map_y_;

};


#endif // MAIN_OBJECT_H
