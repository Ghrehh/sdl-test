#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <nlohmann_json.hpp>
#include "Texture.hpp"
#include "Sprite.hpp"

#include <iostream>
#include <fstream>

using json = nlohmann::json;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int x = 0;
int y = 0;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void init()
{
  //Initialization flag
  bool success = true;

  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
    printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    throw "";
  }
  else
  {
    //Set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
      printf( "Warning: Linear texture filtering not enabled!" );
    }

    //Create window
    window = SDL_CreateWindow( "Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
      printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
      throw "";
    }
    else
    {
      //Create vsynced renderer for window
      renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
      if( renderer == NULL )
      {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        throw "";
      }
      else
      {
        //Initialize renderer color
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {
          printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
          throw "";
        }
      }
    }
  }
}

json open_json_file(std::string path) {
  std::string all_lines;
  std::string line;
  std::ifstream file(path);

  if (file.is_open()) {
    while(file) {
      std::getline(file, line);
      all_lines += line;
    }

    file.close();
  }

  return json::parse(all_lines);
}


int main( int argc, char* args[] )
{
  init();

  auto j = open_json_file("assets/test1.json");

  for (auto sprite : j) {
    std::cout << sprite["height"] << "\n" << std::endl;
  }

  bool quit = false;
  SDL_Event e;
  Engine::Texture t = {renderer, "assets/square.png"};
  Engine::Rect r = {0, 0, 25, 25};
  Engine::Sprite s = {t, r};
  Engine::Coordinate p = {100, 100};
  while(!quit)
  {
    while( SDL_PollEvent( &e ) != 0 )
      {
          if( e.type == SDL_QUIT )
          {
            // justbreak
              quit = true;
          }
          /*
          else if( e.type == SDL_KEYDOWN )
          {
              switch( e.key.keysym.sym )
              {
                  case SDLK_w:

                  case SDLK_DOWN:
                  gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                  break;

                  case SDLK_LEFT:
                  gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
                  break;

                  case SDLK_RIGHT:
                  gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                  break;

                  default:
                  gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
                  break;
              }
          }*/
      }

    SDL_RenderClear(renderer);
    s.render(p);
    SDL_RenderPresent(renderer);
  }

  return 0;
}
