#pragma once
#include <string>
#include <map>
#include "Window.hpp"

namespace Engine {
  class Entity {
    public:
      Coordinate position;
      Size size;

      virtual void tick(std::vector<std::unique_ptr<Entity>>) {};
  };

  using Entities = std::vector<std::unique_ptr<Entity>>;
  using Animations = std::map<std::string, std::vector<std::unique_ptr<Rect>>>;


  class Renderer {
    public:
      void render(Entities entities) {
        for (const auto& entity: entities) {
          auto frame = map_to_frame(entity);
          texture.render(frame, entity->position);
        }
      }

      virtual std::unique_ptr<Rect> map_to_frame(const std::unique_ptr<Entity>&) = 0;
      Texture texture;
      Animations animations;
    private:
  }

  class Scene {
    public:
      void render() {
      }

      virtual void handle_event(SDL_Event) {};
      Renderer renderer;
      Entities entities;
    private:
  };
}
