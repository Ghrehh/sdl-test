#pragma once
#include <string>
#include <map>
#include "Texture.hpp"

namespace Engine {
  using std::vector<std::unique_ptr<Entity>> = Entities;
  using std::map<std::string, std::array<std::unique_ptr<Rect>>> = Animations;

  class Entity {
  }

  class Renderer {
    public:
      void render(Entities entities) {
        for (auto entity : entities) {
          auto frame = map_to_frame(entity);
          texture.render(frame, entity->position);
        }
      }

      virtual std::unique_ptr<Rect> map_to_frame(Entity) = 0;
    private:
      Texture texture;
      Animations animations;
  }

  class Scene {
    public:
      void render() {
      }
    private:
      Renderer renderer;
      Entities entities;
  };
}
