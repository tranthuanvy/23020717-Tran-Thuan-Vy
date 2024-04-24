#ifndef COMMON_FUNC_H_
#define COMMON_FUNC_H_

#include <Windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<vector>
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP =32;
const int FRAME_PER_SECOND =35;

static SDL_Window * gWindow =nullptr;
static SDL_Renderer* gRenderer = nullptr;
static SDL_Event e;

//static Mix_Chunk *sound_jump_threat;
//static Mix_Chunk *sound_exp}

static SDL_Renderer* gMenu=NULL;

#define BLANK_TILE 0
#define TILE_SIZE 64
#define MAX_MAP_X 500
#define MAX_MAP_Y 10
#define COIN_TILE 5
#define OSTACLE1 4
#define OSTACLE2 3


typedef struct Input
{
    int jump_;
    int right_;

};

typedef struct map
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name_;
} ;
namespace SDLCommonFunc
{
    bool CheckCollision(const SDL_Rect& object1,const SDL_Rect& object2);

}

#endif // COMMON_FUNC_H_
