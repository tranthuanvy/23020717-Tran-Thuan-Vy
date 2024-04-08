#include"CommonFunc.h"
#include"BaseObject.h"
#include "GameMap.h"
#include"MainObject.h"
BaseObject g_background;
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
        }
    }

    return success;
}
bool loadbkground()
{
    bool ret =g_background.LoadImg("C:/Users/Admin/Pictures/bkground.PNG",gRenderer);
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
int main(int argc, char* args[])
{
  // Khởi tạo SDL
  if (!init())
    {
    std::cout << "Lỗi khởi tạo SDL!" << std::endl;
    return -1;
  }
  if(!loadbkground()){
    std::cout<<" lỗi tại background!"<<std::endl;
    return -1;
  }
    GameMap game_map;
     game_map.LoadMap("map/map01.txt");    // Sử dụng trực tiếp kiểu const char**/
   game_map.LoadTiles(gRenderer);

   MainObject character_game;
   character_game.LoadImg("C:/Users/Admin/Pictures/animal.PNG",gRenderer);
   character_game.set_clips();
   bool quit = false;
   while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
        break;
      }
      character_game.HandelInputAction(e,gRenderer);
    }

      SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

      SDL_RenderClear(gRenderer);
      g_background.renderTexture(gRenderer,NULL);
     game_map.DrawMap(gRenderer);

     character_game.Show(gRenderer);

      SDL_RenderPresent(gRenderer);

  }

  // Dọn dẹp
  close();

  // Trả về 0
  return 0;
}



