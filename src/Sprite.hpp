#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Texture.hpp"

namespace Engine {
  class Sprite {
    public:
      Sprite(const Texture& texture, const Rect& sprite):
        texture(texture),
        sprite(sprite)
      {};

      void render(const Coordinate& coordinate) const {
        texture.render(sprite, coordinate);
      };
    private:
      const Texture texture;
      const Rect sprite;
  };
}
