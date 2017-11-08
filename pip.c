#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Texture* back;
  SDL_Texture* front;
  
  TTF_Font* textFont = NULL;
  SDL_Color textColor = {0, 0, 0, 0};

  int counter = 0;
  char buff[5];
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

  window = SDL_CreateWindow("PIP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 400, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

  
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  while(counter < 10000)
  {
    	  
    SDL_RenderClear(renderer);	  
    sprintf(buff, "%d", counter);
    //buff[5] = '\0'; 
    SDL_Surface *textSurface;
    SDL_DestroyTexture(front);
    front = NULL;
    
    textureWidth = 0;
    textureHeight = 0;
    textSurface = TTF_RenderText_Solid(textFont, buff, textColor);
    front = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    if(textSurface == NULL)
    {
      printf("TEXT SURFACE IS NULL \n SDLERROR %s:\n", SDL_GetError());
    }
    if(front == NULL)
    {
      printf("FRONT IS NULL\n");
    }
    else
    {
      textureWidth = textSurface -> w;
      textureHeight = textSurface -> h;
      SDL_Rect renderQuad;	    
      renderQuad.x = 320 - (textureWidth/2); 
      renderQuad.y = 200 - (textureHeight/2);
      renderQuad.w = textureWidth;
      renderQuad.h = textureHeight;    	    
      
      SDL_RenderCopy(renderer, front, NULL, &renderQuad);
      SDL_RenderPresent(renderer);
      counter++;
    }
  }
  return 0;
}
