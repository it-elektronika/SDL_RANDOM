#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Texture* back;
  SDL_Texture* front;
  

  SDL_Rect renderQuad;
  TTF_Font* textFont = NULL;
  SDL_Color textColor = {255, 255, 255, 255};

  int counter = 0;
  char buff[100];
  const char* counterText;
  int textureWidth = 0;
  int textureHeight = 0;

int main(int argc, char *argv[])
{
  SDL_Init(SDL_INIT_VIDEO);
  if(TTF_Init() == -1)
  {
    printf("ERROR:  SDL TTF: %s\n", TTF_GetError());
  }

  textFont = TTF_OpenFont("BebasNeue Bold.ttf", 30);
  window = SDL_CreateWindow("PIP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 800, 0);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  renderQuad.x = 320; 
  renderQuad.y = 400;
  renderQuad.w = textureWidth;
  renderQuad.h = textureHeight;

  while(counter < 100)
  {
    SDL_DestroyTexture(front);
    sprintf(buff, "%d\n", counter);
    SDL_Surface* textSurface;
    textSurface = TTF_RenderText_Solid(textFont, counterText, textColor);
    //front = SDL_CreateTextureFromSurface(renderer, textSurface);
    
    if(textSurface == NULL)
    {
      printf("TEXT SURFACE IS NULL SDLERROR %s:\n", SDL_GetError());
    }


    if(front == NULL)
    {
      printf("FRONT IS NULL\n");
    }
    else
    {
      textureWidth = textSurface -> w;
      textureHeight = textSurface -> h;
    SDL_FreeSurface(textSurface);
    //  SDL_RenderCopyEx(renderer, front, NULL, &renderQuad, 0, NULL, SDL_FLIP_NONE); 
    //  SDL_RenderPresent(renderer);
    //  counter++;
    }
    
  }
}
