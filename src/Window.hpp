#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <nlohmann_json.hpp>

#include <iostream>
#include <fstream>

namespace Engine {
  struct Rect {
    int x;
    int y;
    int width;
    int height;
  };

  struct Coordinate {
    int x;
    int y;
  };

  class Texture {
    public:
      int width;
      int height;
      SDL_Texture* texture;

      ~Texture() {
        SDL_DestroyTexture(texture);
      }
  };

  class Window {
    public:
      const int SCREEN_WIDTH = 640;
      const int SCREEN_HEIGHT = 480;
      SDL_Window* window = NULL;
      SDL_Renderer* renderer = NULL;
      void init() {
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


      Texture getTexture(std::string path) const {
        SDL_Surface* surface = IMG_Load(path.c_str());
        if(surface == NULL)
        {
          printf(
            "Unable to load image %s! SDL_image Error: %s\n",
            path.c_str(),
            IMG_GetError()
          );
          throw "";
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, surface);
        if(texture == NULL)
        {
          printf(
            "Unable to create texture from %s! SDL Error: %s\n",
            path.c_str(),
            SDL_GetError()
          );
          throw "";
        }

        Texture t;
        t.width = surface->w;
        t.height = surface->h;
        t.texture = texture;

        SDL_FreeSurface(surface);

        return t;
      }

      void clear() {
        SDL_RenderClear(renderer);
      }

      void draw(
        const Texture& texture,
        const Rect& sprite,
        const Coordinate& position
      ) const {
        // Is this leaking memory?
        SDL_Rect src_rect;
        src_rect.x = sprite.x;
        src_rect.y = sprite.y;
        src_rect.w = sprite.width;
        src_rect.h = sprite.height;

        SDL_Rect destination_rect;
        destination_rect.x = position.x;
        destination_rect.y = position.y;
        destination_rect.w = sprite.width;
        destination_rect.h = sprite.height;

        SDL_RenderCopy(renderer, texture.texture, &src_rect, &destination_rect);
      }

      void render() {
        SDL_RenderPresent(renderer);
      }

    private:
  };
}
