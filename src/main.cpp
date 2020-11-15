#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <nlohmann_json.hpp>
#include "Window.hpp"

#include <iostream>
#include <fstream>

using json = nlohmann::json;

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
  Engine::Window window;
  window.init();

  auto j = open_json_file("assets/sprites/test1/sprites.json");

  for (auto sprite : j) {
    std::cout << sprite["height"] << "\n" << std::endl;
  }

  bool quit = false;
  SDL_Event e;
  Engine::Texture t = window.getTexture("assets/square.png");
  Engine::Rect r = {0, 0, 25, 25};
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

    window.clear();
    window.draw(t, r, p);
    window.render();
  }

  return 0;
}
