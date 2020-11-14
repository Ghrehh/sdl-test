#pragma once
#include <SDL.h>
#include <string>

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
      Texture(SDL_Renderer*, std::string);
      ~Texture();
      void render(const Rect&, const Coordinate&) const;
    private:
      SDL_Renderer* renderer;
      SDL_Texture* texture;
      int width;
      int height;
  };
}
