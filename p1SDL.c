#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include "logica.h"

//Constants of the program
#define XSIZE 1200
#define YSIZE 700
#define MS 10

//Methods of the interface
void drawMap(SDL_Renderer *renderer,SDL_Texture*  map_texture);
void drawCars(SDL_Renderer *renderer,SDL_Texture*  car_texture,SDL_Surface*  car_surface,Cars *listCars);
void selectAutomobile(int tipo,SDL_Renderer *renderer,SDL_Texture*  car_texture,SDL_Surface*  car_surface);
void logMessage(char *message);

//Main function
int main(int argc, char *argv[]) {
  //Start the library
  if(SDL_Init(SDL_INIT_VIDEO)<0){
    printf("SDL library error \n \n");
    return -1;
  }else{
    printf("SDL library started succesfully \n \n");
  }

  const Uint8 *keys;
  int typeEvent;              //Variable to control the events.
  int gameOver = 0;          //Variable to close the aplication.
  SDL_Window   *window;     //Window of the game
  SDL_Renderer *renderer; //Renderer of the game.
  SDL_Surface  *map_surface = NULL;
  SDL_Texture  *map_texture = NULL;
  SDL_Surface  *car_surface = NULL;
  SDL_Texture  *car_texture = NULL;
  SDL_Event event;
  Cars *listCars;

  //Initialice the window, the renderer and the controler of the keyboard.
  window = SDL_CreateWindow("Threadville",SDL_WINDOWPOS_UNDEFINED
                            ,SDL_WINDOWPOS_UNDEFINED,XSIZE,YSIZE,
                            SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
  keys = SDL_GetKeyboardState(NULL);

  //Definitions to the map.
  map_surface = SDL_LoadBMP("mapa.bmp");
  map_texture = SDL_CreateTextureFromSurface(renderer, map_surface);

  while(!gameOver){
///////////////////////////////////////Start the event control//////////////
    //Retorn 1 if there events pendents, 0 if there is nothing.
    if(SDL_PollEvent(&event)){
      typeEvent = event.type;    //EVENTS.
      if (typeEvent==SDL_QUIT){gameOver=1;}
      else if(typeEvent==SDL_KEYDOWN){
        if(keys[SDL_SCANCODE_F1]){
          //Create random cars
          logMessage("Creating a random car \n");
        }else if(keys[SDL_SCANCODE_F2]){
          //Car with user params
          principal();
          logMessage("Creating a car with params \n");
        }else if(keys[SDL_SCANCODE_F3]){
          //Ambulance with random params
          logMessage("Creating an ambulance with params \n");
        }else if(keys[SDL_SCANCODE_F4]){
          //radioactive cars with random params
          logMessage("Creating a radioactive car with params \n");
        }else if(keys[SDL_SCANCODE_F5]){
          logMessage("Exit \n");
          //Exit
          gameOver = 1;
        }
      }
    }
///////////////////////////////////////Finish the event control///////////////

///////////////////////////////////////Start the window control/////////////////
    SDL_SetRenderDrawColor(renderer,0,0,0,0);        //Define the renderer color
    SDL_RenderClear(renderer);                       //Clean the screen
    drawMap(renderer,map_texture);                   //Draw the map on the window.
    drawCars(renderer,car_texture,car_surface,NULL); //Method to draw the automobiles
    SDL_RenderPresent(renderer);                    //Update the window.
    SDL_Delay(MS);                                  //Delay to refresh the window again.
///////////////////////////////////////Finish the window control///////////////
  }

  //Destroy the renderer and the window (close of the app).
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}

//Method to print the map on the main window (SDL_Window)
void drawMap(SDL_Renderer *renderer,SDL_Texture*  map_texture){
  SDL_Rect rect;
  rect.h = YSIZE;
  rect.w = XSIZE;
  rect.x = 0;
  rect.y = 0;//Copy the map_texture to the renderer
  SDL_RenderCopy(renderer, map_texture, NULL, &rect);
}

//Method to print the cars on the window. It most select the kind of
//image according to the id of the automobile
void drawCars(SDL_Renderer *renderer,SDL_Texture*  car_texture,
  SDL_Surface*  car_surface,Cars *listCars){
    listCars = getCars();
    int tipo;
    if(listCars != NULL){
      SDL_Rect rect;
      rect.h = YSIZE;
      rect.w = XSIZE;
      rect.x = 0;
      rect.y = 0;
      SDL_RenderCopy(renderer, car_texture, NULL, &rect);
      while(listCars->siguiente != NULL){//Run over the list to print each automobile
        listCars = listCars->siguiente;  //on the map.
        tipo = 1;//extraer tipo////////////////////////////////////////FALTA
        selectAutomobile(tipo,renderer,car_texture,car_surface);//Select image
        SDL_Rect rect;
        rect.h = YSIZE;
        rect.w = XSIZE;
        rect.x = 0;
        rect.y = 0;//Copy the image on the renderer.
        SDL_RenderCopy(renderer, car_texture, NULL, &rect);
      }
    }
}

//Method that load the image according to the kind of automobile.
void selectAutomobile(int tipo,SDL_Renderer *renderer,SDL_Texture*  car_texture,SDL_Surface*  car_surface){
  switch (tipo) {
    case 1:
      car_surface = SDL_LoadBMP("carro.bmp");
      car_texture = SDL_CreateTextureFromSurface(renderer, car_surface);
      break;
    case 2:
      car_surface = SDL_LoadBMP("ambulancia.bmp");
      car_texture = SDL_CreateTextureFromSurface(renderer, car_surface);
      break;
    case 3:
      car_surface = SDL_LoadBMP("radioactivo.bmp");
      car_texture = SDL_CreateTextureFromSurface(renderer, car_surface);
      break;
    case 4:
      car_surface = SDL_LoadBMP("busAm.bmp");
      car_texture = SDL_CreateTextureFromSurface(renderer, car_surface);
      break;
    case 5:
      car_surface = SDL_LoadBMP("busAz.bmp");
      car_texture = SDL_CreateTextureFromSurface(renderer, car_surface);
      break;
    case 6:
      car_surface = SDL_LoadBMP("busNa.bmp");
      car_texture = SDL_CreateTextureFromSurface(renderer, car_surface);
      break;
    case 7:
      car_surface = SDL_LoadBMP("busRo.bmp");
      car_texture = SDL_CreateTextureFromSurface(renderer, car_surface);
      break;
    case 8:
      car_surface = SDL_LoadBMP("busVe.bmp");
      car_texture = SDL_CreateTextureFromSurface(renderer, car_surface);
      break;
  }
}

//Method that print on the file the message of
//an predeterminated action on the city.
void logMessage(char *message){
  FILE *archivo = fopen("ThreadVilleLogFile.txt", "a+");
  fprintf(archivo, "%s", message);
  fclose(archivo);
}

//https://www.youtube.com/watch?v=IGiBHfDR6Ws
