#include <string>
#include <nlohmann_json.hpp>
#include "Window.hpp"
#include "Scene.hpp"

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

class LevelRenderer: public Engine::Renderer {
  public:
    std::unique_ptr<Rect> map_to_frame(Entity e) {
      return animations["sprite"];
    }
}


int main(int argc, char* args[])
{
  Engine::Window window;
  window.init();

  auto j = open_json_file("assets/sprites/test1/sprites.json");
    /*
  for (auto sprite : j) {
    std::cout << sprite["height"] << "\n" << std::endl;
  }*/

  std::unique_ptr<Engine::Rect> sprite = make_unique<Engine::Rect>(
    j[0]["x"],
    j[0]["y"],
    j[0]["width"],
    j[0]["height"]
  )

  bool quit = false;
  Engine::Texture t = window.getTexture("assets/square.png");
  Engine::Scene s;
  LevelRenderer lr;
  lr.texture = t;
  lr.animations["sprite"] = std::vector<std::unique_ptr<Rect>> {sprite};

  Engine::Entity square;
  square.size = Size(25, 25);
  square.position = Coordinate(100, 100);

  s.entities.push_back(square);
  s.renderer = sr;
  while(!quit)
  {
    auto [more_events, e] = window.get_event();
    while(more_events)
      {
          if(e.type == SDL_QUIT) {
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
          std::tie(more_events, e) = window.get_event();
      }

    window.clear();
    window.draw(t, r, p);
    window.render();
  }

  return 0;
}
