#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* back;
SDL_Texture* front;
SDL_Surface *textSurface;
SDL_Rect renderQuad;	 
TTF_Font* textFont = NULL;
SDL_Color textColor = {0, 0, 0, 0};

int i;
int counter = 0;
char buff[5];
const char* counterText;
int textureWidth = 0;
int textureHeight = 0;
FILE *f1;
char buf[12];
char rez[12];

int main(int argc, char *argv[])
{
  i = 0;
  printf("POINT A\n");

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
    system("vcgencmd measure_temp >> output.txt");
    system("vcgencmd measure_temp >> output_all.txt");
    
    if((f1 = fopen("output.txt", "r")) == NULL)
    {
      printf("ERROR OPENING FILE!");
      exit(2);
    }

    while((buf[i] = fgetc(f1)) != EOF)
    {
      printf("BUF[%d]: %s\n", i, buf);
      rez[i] = buf[i];
      i++;
      if(i+0 > 9)
      {
        break;
      }
    }
 //   rez[i] = '\0';
 //   buf[i] = '\0';
    printf("REZ: %s\n", rez);
    SDL_RenderClear(renderer);	  
    sprintf(buff, "%d", counter);
    SDL_DestroyTexture(front);
    front = NULL;
    printf("POINT B");
    textureWidth = 0;
    textureHeight = 0;
    textSurface = TTF_RenderText_Solid(textFont, rez, textColor);
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
     
      renderQuad.x = 320 - (textureWidth/2); 
      renderQuad.y = 200 - (textureHeight/2);
      renderQuad.w = textureWidth;
      renderQuad.h = textureHeight;    	    
      
      SDL_RenderCopy(renderer, front, NULL, &renderQuad);
      SDL_RenderPresent(renderer);
      counter++;
    }
    printf("POINT C");

    fclose(f1);
    system("rm output.txt");
  }
  return 0;
}
