#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* temp;
SDL_Texture* volt;
SDL_Texture* gpu;
SDL_Surface *tempSurface;
SDL_Surface *voltSurface;
SDL_Surface *gpuSurface;

SDL_Rect tempQuad;	 
SDL_Rect voltQuad;	
SDL_Rect gpuQuad;	
TTF_Font* textFont = NULL;
SDL_Color textColor = {0, 0, 0, 0};

int i;
int counter = 0;
char buff[5];
int textureWidth = 0;
int textureHeight = 0;

FILE *f1;
FILE *f2;
FILE *f3;

char temp_buf[12];
char temp_rez[12];

char volt_buf[13];
char volt_rez[13];

char gpu_buf[8];
char gpu_rez[8];


int lastTime = -1001;
int currentTime = 0;


int main(int argc, char *argv[])
{
  printf("POINT START\n");

  SDL_Init(SDL_INIT_VIDEO);
  if(TTF_Init() == -1)
  {
    printf("ERROR:  SDL TTF: %s\n", TTF_GetError());
  }
  
  textFont = TTF_OpenFont("BebasNeue Bold.ttf", 30);

  window = SDL_CreateWindow("PIP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 400, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  while(1)
  {
    printf("POINT A\n");
    i = 0;
    currentTime = SDL_GetTicks();
    printf("CURRENT: %d, LAST: %d, LAST+1000: %d\n", currentTime, lastTime, lastTime+1000);
    if(currentTime > (lastTime + 1000))
    {
      printf("IN IF");
      system("vcgencmd measure_temp >> temp.txt");
      system("vcgencmd measure_temp >> temp_all.txt");
      
      system("vcgencmd measure_volts >> volt.txt");
      system("vcgencmd measure_volts >> volt_all.txt");   
     
      system("vcgencmd get_mem gpu >> gpu.txt");
      system("vcgencmd get mem gpu >> gpu_all.txt");
      
      if((f1 = fopen("temp.txt", "r")) == NULL)
      {
        printf("ERROR OPENING FILE1!");
        exit(2);
      }
      
      while((temp_buf[i] = fgetc(f1)) != EOF)
      {
        temp_rez[i] = temp_buf[i];
        i++;
        if(i == 11)
        {
          break;
        }
      }
      temp_rez[i] = '\0';
      temp_buf[i] = '\0';
      fclose(f1);
      
      if((f2 = fopen("volt.txt", "r")) == NULL)
      {
        printf("ERROR OPENING FILE2!");
        exit(2);
      }
      
      i = 0;
      while((volt_buf[i] = fgetc(f2)) != EOF)
      {
        volt_rez[i] = volt_buf[i];
        i++;
        if(i == 12)
        {
          break;
        }
      }
      volt_rez[i] = '\0';
      volt_buf[i] = '\0'; 
      fclose(f2);
      
      if((f3 = fopen("gpu.txt", "r")) == NULL)
      {
        printf("ERROR OPENING FILE3!");
        exit(2);
      }
      i=0;
      while((gpu_buf[i] = fgetc(f3)) != EOF)
      {
        gpu_rez[i] = gpu_buf[i];
        i++;
        if(i == 7)
        {
          break;
        }
      }
      gpu_rez[i] = '\0';
      gpu_buf[i] = '\0';  
      fclose(f3);
      
      for(i = 0; i < 13; i++)
      {
        printf("VOLT[%d]: %c \n", i, volt_rez[i]);
      }

      for(i = 0; i < 12; i++)
      {
        printf("TEMP[%d]: %c \n", i, temp_rez[i]);
      }

      for(i = 0; i < 12; i++)
      {
        printf("GPU[%d]: %c \n", i, gpu_rez[i]);
      }
    
      system("rm temp.txt");
      system("rm volt.txt");
      system("rm gpu.txt");
      lastTime = currentTime;
    }
    SDL_RenderClear(renderer);	  
    SDL_DestroyTexture(temp);
    SDL_DestroyTexture(volt);
    SDL_DestroyTexture(gpu);

    temp = NULL;
    volt = NULL;
    gpu = NULL;

    printf("POINT B\n");
    textureWidth = 0;
    textureHeight = 0;
    
    tempSurface = TTF_RenderText_Solid(textFont, temp_rez, textColor);
    voltSurface = TTF_RenderText_Solid(textFont, volt_rez, textColor);
    gpuSurface  = TTF_RenderText_Solid(textFont, gpu_rez, textColor);

    temp = SDL_CreateTextureFromSurface(renderer, tempSurface);
    volt = SDL_CreateTextureFromSurface(renderer, voltSurface);
    gpu = SDL_CreateTextureFromSurface(renderer, gpuSurface);
    
    SDL_FreeSurface(tempSurface);
    SDL_FreeSurface(voltSurface);
    SDL_FreeSurface(gpuSurface);

    if(tempSurface == NULL)
    {
      printf("TEMP SURFACE IS NULL \n SDLERROR %s:\n", SDL_GetError());
    }
    
    if(voltSurface == NULL)
    {
      printf("VOLT SURFACE IS NULL \n SDLERROR %s:\n", SDL_GetError());
    }
    
    if(temp == NULL || volt == NULL)
    {
      printf("FRONT IS NULL\n");
    }
    else
    {
      textureWidth = tempSurface -> w;
      textureHeight = tempSurface -> h;
     
      tempQuad.x = 320 - (textureWidth/2); 
      tempQuad.y = 100 - (textureHeight/2);
      tempQuad.w = textureWidth;
      tempQuad.h = textureHeight;    	    
     
      voltQuad.x = 320 - (textureWidth/2); 
      voltQuad.y = 200 - (textureHeight/2);
      voltQuad.w = textureWidth;
      voltQuad.h = textureHeight;    	  

      gpuQuad.x = 320 - (textureWidth/2); 
      gpuQuad.y = 300 - (textureHeight/2);
      gpuQuad.w = textureWidth;
      gpuQuad.h = textureHeight;    	  

      SDL_RenderCopy(renderer, temp, NULL, &tempQuad);
      SDL_RenderCopy(renderer, volt, NULL, &voltQuad);
      SDL_RenderCopy(renderer, gpu, NULL, &gpuQuad);

      SDL_RenderPresent(renderer);
      counter++;
    }
    printf("POINT C\n");
    printf("POINT D\n");
  }
  return 0;
}
