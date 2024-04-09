#ifndef GAME_MAP_H
#define GAME_MAP_H
#include "CommonFunc.h"
#include"BaseObject.h"
#include <cstdio>

#define MAX_TILES 20

class TileMap : public BaseObject
{
public:
    TileMap(){;}
    ~TileMap(){;}
};
class GameMap
{
public:
    GameMap(){;}
    ~GameMap(){;}

    void LoadMap(  char* name);
    void LoadTiles(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);
    map getMap()const {return game_map_;};//phan di chuyen nhan vat
    void SetMap(map& map_data){ game_map_=map_data;};// de map chay theo nhan vat
private:
  map game_map_;//chứa toàn bộ thông tin: trạng thái của ô , vị trí của ô,chỉ sô của ô
  TileMap tile_map_[MAX_TILES];


};
#endif // GAME_MAP_H
