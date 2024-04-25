#include"CommonFunc.h"
#include"BaseObject.h"
#include"GameMap.h"
#include"MainObject.h"
#include"Timer.h"
#include"ThreatObject.h"
#include"Explosion.h"
#include"TextObject.h"
#include"Menu.h"
#include"GameOver.h"
BaseObject g_background;
BaseObject g_gameover;
TTF_Font*font_=NULL;
TTF_Font*font_menu=NULL;
bool init() {
    bool success = true;

    // Khởi tạo SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    } else {
        // Thiết lập chất lượng tỉ lệ vẽ texture thành linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
        }

        // Tạo cửa sổ
        gWindow = SDL_CreateWindow("Ostacle Race",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SCREEN_WIDTH,
                                    SCREEN_HEIGHT,
                                    SDL_WINDOW_SHOWN);
        if (gWindow == nullptr) {
            std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        } else {
            // Tạo renderer với chế độ vsync
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == nullptr) {
                std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
                success = false;
            } else {
                // Thiết lập màu vẽ cho renderer
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Khởi tạo tải ảnh PNG
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError()
                              << std::endl;
                    success = false;
                }
            }
            // Kiểm tra lỗi khi khởi tạo SDL_ttf
            if (TTF_Init() == -1) {
                std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
                success = false;
            }

            // Mở font
            font_ = TTF_OpenFont("font//CastoroTitling-Regular.ttf", 15);
            font_menu= TTF_OpenFont("font//dlxfont_.ttf", 50);
            if (font_ == nullptr||font_menu==nullptr) {
                std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
                success = false;
            }
        }
    }
     if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,4096)==-1)
     {
         return false;
     }

     sound_jump_threat= Mix_LoadWAV("Sound/source_sound_jump_sound.wav");
     sound_menu= Mix_LoadMUS("Sound/source_sound_bkgr_audio.wav");
     sound_lose=Mix_LoadWAV("Sound/source_sound_lose_sound.wav");

     if(sound_jump_threat==NULL||sound_menu==NULL||sound_lose==NULL)
     {
         return false;
     }
    return success;
}
bool loadbkground()
{
    bool ret =g_background.LoadImg("Pics/bkground.PNG",gRenderer);
    if (ret ==false)
    {
    std::cout << "Lỗi tải background!" << std::endl;
    return false;
  }
  else{ return true;}

}

 void close() {
     g_background.Free();
     SDL_DestroyRenderer(gRenderer);
      gRenderer = nullptr;


    SDL_DestroyWindow(gWindow);

    gWindow = nullptr;

    IMG_Quit();
    SDL_Quit();
 }
 std::vector<ThreatObject*>MakeThreatList()
 {
     std::vector<ThreatObject*>list_threat;
     ThreatObject* threatobject= new ThreatObject[42];
     for(int i=0;i<42;i++)
     {
         ThreatObject* p_threat=(threatobject+i);
         if(p_threat!=NULL)
         {
             p_threat->LoadImg("Pics/threatobject.png",gRenderer);
             p_threat->set_clips();
             p_threat->setxpos(2000+i*1200);
             p_threat->setypos(250);

             BulletObject*p_bullet=new BulletObject();
             p_threat->InitBullet(p_bullet,gRenderer);
             list_threat.push_back(p_threat);
         }
     }
     return list_threat;
 }
  std::vector<ThreatObject*>MakeThreatList1()
 {
     std::vector<ThreatObject*>list_threat;
     ThreatObject* threatobject= new ThreatObject[42];
     for(int i=0;i<42;i++)
     {
         ThreatObject* p_threat=(threatobject+i);
         if(p_threat!=NULL)
         {
             p_threat->LoadImg("Pics/cactus.png",gRenderer);
             p_threat->set_clips();
             p_threat->setxpos(1400+i*1200);
             p_threat->setypos(250);
             list_threat.push_back(p_threat);
         }
     }
     return list_threat;
 }

int main(int argc, char* args[])
{
    Timer time;

  if (!init())
    {
    std::cout << "Lỗi khởi tạo SDL!" << std::endl;
    return -1;
  }
   bool quit = false;
   Menu myMenu;
   int ret_menu = myMenu.ShowMenu(gRenderer,font_menu);
   if (ret_menu == 1)
        {quit = true;}
  if(!loadbkground()){
    std::cout<<" lỗi tại background!"<<std::endl;
    return -1;
  }
again_label:
    GameMap game_map;
    game_map.LoadMap("map/map01.txt");    // Sử dụng trực tiếp kiểu const char**/
    game_map.LoadTiles(gRenderer);

    MainObject character_game;
    character_game.LoadImg("Pics/animal.PNG",gRenderer);
    character_game.set_clips();

    std::vector<ThreatObject*>threat_list =MakeThreatList();
    std::vector<ThreatObject*>threat_list1 =MakeThreatList1();
    ExplosionObject exp;
    exp.LoadImg("Pics/explosion.png",gRenderer);
    exp.set_clip();

    //text
    TextObject score_game;
    score_game.SetColor(TextObject::RED_TEXT);



    TextObject number_dead_threat;
    number_dead_threat.SetColor(TextObject:: BLACK_TEXT );
    UINT mark_value =0;

    TextObject money_game;
    money_game.SetColor(TextObject:: WHITE_TEXT);

    GameOver myGameOver;

    Mix_PlayMusic(sound_menu, -1);
   while (!quit)
    {
       time.start();
       while (SDL_PollEvent(&e) != 0)
         {
             if (e.type == SDL_QUIT)
            {
                  quit = true;
                break;
            }
             character_game.HandelInputAction(e,gRenderer,sound_jump_threat);
          }

      SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
      SDL_RenderClear(gRenderer);
      g_background.renderTexture(gRenderer,NULL);

      map map_data=game_map.getMap();


     character_game.HandleBullet(gRenderer);
     character_game.SetMapxy(map_data.start_x_,map_data.start_y_);
     character_game.DoPlayer(map_data);
     character_game.Show(gRenderer);
     game_map.SetMap(map_data);
     game_map.DrawMap(gRenderer);
     bool check =character_game.CheckToWin(character_game.x_pos_);

     int frameexpwidth= exp.get_frame_width();
     int frameexpheight= exp.get_frame_height();
// va chạm giữa con heo và đạn của nhện nếu nhện bắn vào heo thì heo sẽ chết và kết thúc chương trình
     for(int i=0;i<threat_list.size();i++)
     {
         ThreatObject* p_threat= threat_list.at(i);
         if(p_threat!=NULL)
         {
             p_threat->SetMapxy(map_data.start_x_,map_data.start_y_);
             p_threat->DoPlayer(map_data);
             p_threat->MakeBullet(gRenderer,SCREEN_WIDTH,SCREEN_HEIGHT);
             p_threat->Show(gRenderer);

             SDL_Rect rect_player= character_game.GetRectFrame();
             bool bCol1=false;
             std::vector<BulletObject*>tBullet_list=p_threat->get_bullet_list();
             for(int j=0;j<tBullet_list.size();j++)
             {
                 BulletObject* pt_bullet=tBullet_list.at(j);
                 if(pt_bullet)
                 {
                     bCol1=SDLCommonFunc::CheckCollision(pt_bullet->GetRect(),rect_player);
                     if(bCol1)
                     {
                        p_threat->RemoveBullet(j);
                        for(int i=0; i<8;i++)
                       {

                           int x_pos=pt_bullet->GetRect().x -frameexpheight*0.5;
                           int y_pos= pt_bullet->GetRect().y -frameexpheight*0.5;

                           exp.set_frame(i);
                           exp.SetRect(x_pos,y_pos);
                           exp.Show(gRenderer);
                       }
                       character_game.Free();
                        g_gameover.LoadImg("Pics/GameOver.png",gRenderer);
                        g_gameover.renderTextureGameBackGround(gRenderer,NULL);
                        SDL_RenderPresent(gRenderer);
                         Sleep(700);
                       character_game.is_die_=true;
                        break;
                     }

                 }
             }
             SDL_Rect rect_threat=p_threat->GetRectFrame();
             bool bCol2=SDLCommonFunc::CheckCollision(rect_player,rect_threat);
            if(bCol2)
             {
                g_gameover.LoadImg("Pics/GameOver.png",gRenderer);
                g_gameover.renderTextureGameBackGround(gRenderer,NULL);
                SDL_RenderPresent(gRenderer);
                Sleep(700);
                character_game.is_die_=true;
                p_threat->Free();

            }
         }
     }



//va chạm giữa con heo với xương rồng nếu con heo chạm xuong rồng thì sẽ  và kết thúc chương trình
     for(int i = 0; i < threat_list1.size(); i++)
{
    ThreatObject* p_threat1 = threat_list1.at(i);
    if(p_threat1 != NULL)
    {
        p_threat1->SetMapxy(map_data.start_x_, map_data.start_y_);
        p_threat1->DoPlayer(map_data);
        p_threat1->MakeBullet(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
        p_threat1->Show(gRenderer);

        SDL_Rect rect_player = character_game.GetRectFrame();
        SDL_Rect rect_threat1 = p_threat1->GetRectFrame();

        // Kiểm tra va chạm giữa con heo và nhện
        bool bCol3 = SDLCommonFunc::CheckCollision(rect_player, rect_threat1);
        if(bCol3)
        {    Mix_PlayChannel(-1,sound_lose, 0);
            g_gameover.LoadImg("Pics/GameOver.png",gRenderer);
            g_gameover.renderTextureGameBackGround(gRenderer,NULL);
            SDL_RenderPresent(gRenderer);
            Sleep(700);
            character_game.is_die_=true;
            p_threat1->Free();

        }

    }
}

// va chạm đạn bắn của con heo vào nhện thì nhện biến mât và đạn nhện bắn ra cũng biến mất


     std::vector<BulletObject*>bullet_arr= character_game.get_bullet_list();
     for(int b=0;b<bullet_arr.size();b++)
     {
         BulletObject* p_bullet=bullet_arr.at(b);
         if(p_bullet!=NULL)
         {
             for(int t=0;t<threat_list.size();t++ )
             {
                 ThreatObject* threatobj= threat_list.at(t);
                 if(threatobj!=NULL)
                 {
                     SDL_Rect tRect;
                     tRect.x=threatobj->GetRect().x;
                     tRect.y=threatobj->GetRect().y;
                     tRect.w=threatobj->getwidthframe();
                     tRect.h=threatobj->getheightframe();// lay 1 frame thoi

                     SDL_Rect bRect= p_bullet->GetRect();
                     bool bCol=SDLCommonFunc::CheckCollision(bRect,tRect);
                     if(bCol)
                     {
                         mark_value+=1;
                       for(int i=0; i<8;i++)
                       {

                           int x_pos=p_bullet->GetRect().x -frameexpheight*0.3;
                           int y_pos= p_bullet->GetRect().y -frameexpheight*0.3;

                           exp.set_frame(i);
                           exp.SetRect(x_pos,y_pos);
                           exp.Show(gRenderer);
                       }

                       character_game.RemoveBullet(b);
                       threatobj->Free();
                       threat_list.erase(threat_list.begin()+t);

                     }

                }
             }

         }
     }

     if(check)
     {
        g_gameover.LoadImg("Pics/GameWin.png",gRenderer);
        g_gameover.renderTextureGameBackGround(gRenderer,NULL);
        SDL_RenderPresent(gRenderer);
        Sleep(700);
        character_game.is_die_=true;

     }


     int score_value=character_game.GetScoreCount();
     std::string val_score =std:: to_string(score_value);
     std:: string str_score ("Score:");
     str_score+=val_score;
     score_game.SetText(str_score);
     score_game.LoadRenderText(font_,gRenderer);
     score_game.RenderText(gRenderer,SCREEN_WIDTH-200,15);


    std::string val_str_mark =std:: to_string(mark_value);
    std::string strMark("ThreatDeaded:");
    strMark+= val_str_mark;

    number_dead_threat.SetText(strMark);
    number_dead_threat.LoadRenderText(font_,gRenderer);
    number_dead_threat.RenderText(gRenderer,SCREEN_WIDTH*0.5-50,15);

    int money_value=character_game.GetMoneyCount();
    std::string money_str=std::to_string(money_value);
    std::string strmoney("Coin:");
    strmoney+=money_str;
    money_game.SetText(strmoney);
    money_game.LoadRenderText(font_,gRenderer);
    money_game.RenderText(gRenderer,SCREEN_WIDTH*0.5-600,15);

    SDL_RenderPresent(gRenderer);
      bool game_over = character_game.GetIsDie();
        if (game_over == true)
        {
            Sleep(700);
            int ret_menu = myGameOver.ShowGameOver(gRenderer,font_menu);
            if (ret_menu == 1)
            {
                quit = true;
                continue;
            }
            else
            {
                quit = false;

                goto again_label;
            }
        }



    int real_timer= time.get_ticks();// thoi gian thuc su troi qua
    int time_one_frame =1000/*mili giay*//FRAME_PER_SECOND;




    if(real_timer<time_one_frame)
    {
      int delay_time=time_one_frame-real_timer;

      if(delay_time)
      {
        SDL_Delay(delay_time);
      }
    }

  }

  for(int i=0;i<threat_list.size();i++)
  {
      ThreatObject* p_threat=threat_list.at(i);
      if(p_threat!=NULL)
      {
          p_threat->Free();
          p_threat=NULL;
      }
  }
  for(int i=0;i<threat_list1.size();i++)
  {
      ThreatObject* p_threat1=threat_list1.at(i);
      if(p_threat1!=NULL)
      {
          p_threat1->Free();
          p_threat1=NULL;
      }
  }
  threat_list.clear();
  threat_list1.clear();

  Mix_FreeMusic(sound_menu);
  Mix_CloseAudio();
  close();

  return 0;
}
