#ifndef THREAT_OBJECT_H_
#define THREAT_OBJECT_H_
#include"CommonFunc.h"
#include"BaseObject.h"
#include"BulletObject.h"

#define MAX_FALL_SPEED 10
#define ThreatFrameNum 8
class ThreatObject : public BaseObject
{
public:
    ThreatObject();
    ~ThreatObject();

    void setxval(const float& xval){x_val_=xval;}
    void setyval(const float& yval){y_val_=yval;}
    void setxpos(const float& xpos){x_pos_=xpos;}
    void setypos(const float& ypos){y_pos_=ypos;}
    float getxpos() const{return x_pos_;}
    float getypos() const{return y_pos_;}
    void SetMapxy(const int& mapx, const int& mapy){map_x_=mapx; map_y_=mapy;}

    void set_clips();
    bool LoadImg(std:: string path,SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    int getwidthframe()const{return width_frame_;}
    int getheightframe()const{return height_frame_;}
    void DoPlayer(map& map_data);
    void CheckToMap(map& map_data);

    SDL_Rect  GetRectFrame();
    std:: vector<BulletObject*>get_bullet_list()const{return list_bullet_;}
    void set_bullet_list(const std::vector<BulletObject*>& bl_list){list_bullet_=bl_list;}
    void InitBullet(BulletObject* p_bullet,SDL_Renderer* screen);// truyền đạt thông số bullet
    void MakeBullet(SDL_Renderer* screen ,const int& x_limit,const int& y_limit);
    void RemoveBullet(const int& index);
private:
    SDL_Rect frame_clip_[ThreatFrameNum];
    int width_frame_;
    int height_frame_;
    int frame_;
    bool on_ground_;
    float x_pos_;
    float y_pos_;
    float x_val_;
    float y_val_;
    int map_x_;
    int map_y_;// giới hạn của nhân vật với bản đồ

    std::vector<BulletObject*>list_bullet_;// đạn của threat
};

#endif // THREAT_OBJECT_H_
