#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Texture.hpp"

namespace Engine {
  Texture::Texture(SDL_Renderer* renderer, std::string path)
  {
    if (renderer == nullptr) {
      throw std::runtime_error("texture given bad renderer pointer");
    }
    this->renderer = renderer;

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

    texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    if(texture == NULL)
    {
      printf(
        "Unable to create texture from %s! SDL Error: %s\n",
        path.c_str(),
        SDL_GetError()
      );
      throw "";
    }

    width = surface->w;
    height = surface->h;

    SDL_FreeSurface(surface);
  }

  Texture::~Texture()
  {
    SDL_DestroyTexture(texture);
  }

  void Texture::render(const Rect& sprite, const Coordinate& position) const {
    if (renderer == nullptr) {
      throw std::runtime_error("texture given bad renderer pointer");
    }

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

    SDL_RenderCopy(renderer, texture, &src_rect, &destination_rect);
  }
}
