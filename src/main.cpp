#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;


class Texture {
  public:
    Texture(SDL_Renderer*, std::string);
    ~Texture();
    void render();
  private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    int width;
    int height;
};

Texture::Texture(SDL_Renderer* renderer, std::string path)
{
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

void Texture::render() {
  SDL_Rect renderQuad = {10, 10, width, height};

  SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
}

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


int main( int argc, char* args[] )
{
  init();

  bool quit = false;
  SDL_Event e;
  Texture t = Texture(renderer, "assets/square.png");
  while(!quit)
  {
    //Handle events on queue
    while(SDL_PollEvent(&e) != 0)
    {
      //User requests quit
      if( e.type == SDL_QUIT )
      {
        quit = true;
      }
    }

    SDL_RenderClear(renderer);
    t.render();
    SDL_RenderPresent(renderer);
  }

  return 0;
}
