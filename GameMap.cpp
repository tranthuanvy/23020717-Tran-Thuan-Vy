#include"GameMap.h"

 void GameMap::LoadMap(  char * name) {
    FILE* fp =nullptr;
    fopen_s (&fp,name,"rb");
    if(fp ==nullptr)
    {
        return ;
    }
    game_map_.max_x_=0;
    game_map_.max_y_=0;
    for(int i=0;i<MAX_MAP_Y;i++)
    {
        for(int j=0;j<MAX_MAP_X;j++)
        {
            std::fscanf(fp, "%d", &game_map_.tile[i][j]);
            int val = game_map_.tile[i][j];
            if(val>0)
            {
                if(j>game_map_.max_x_)
                {
                    game_map_.max_x_=j;
                }
                if(j>game_map_.max_y_)
                {
                   game_map_.max_y_=i;
                }
            }
        }
    }
    game_map_.max_x_=(game_map_.max_x_+1)*TILE_SIZE;
    game_map_.max_y_=(game_map_.max_y_+1)*TILE_SIZE;

    game_map_.start_x_=0;
    game_map_.start_y_=0;

    game_map_.file_name_=name;
    fclose(fp);
}
void GameMap::LoadTiles(SDL_Renderer* screen)
{
    char file_img[30];
    FILE* fp=NULL;
    for (int i=0;i<MAX_TILES;i++)
    {
        sprintf_s(file_img,"map/%d.png",i);
        fopen_s(&fp,file_img,"rb");
        if(fp==NULL)
            {
                continue;
            }
        fclose(fp);
        tile_map_[i].LoadImg(file_img,screen);
    }
}
void GameMap::DrawMap(SDL_Renderer* screen)
{
    // Tính toán vị trí kích thước của bản đồ
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    int map_x=0;
    int map_y=0;

     map_x = game_map_.start_x_ / TILE_SIZE;
    x1 = (game_map_.start_x_ % TILE_SIZE) * -10;
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    map_y = game_map_.start_y_ / TILE_SIZE;
   y1 = (game_map_.start_y_ % TILE_SIZE) * -1;
   y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    // Vòng lặp vẽ tile
    for (int i = y1; i < y2; i += TILE_SIZE)
    {
        map_x = game_map_.start_x_/ TILE_SIZE; // Đảm bảo reset map_x
        for (int j = x1; j < x2; j += TILE_SIZE)
        {
           int val = game_map_.tile[map_y][map_x];
                if (val > 0)
                {
                        tile_map_[val].SetRect(j,i);
                        tile_map_[val].renderTexture(screen);

                }

            map_x++;
        }
        map_y++;
    }
}
