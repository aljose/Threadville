#include <SDL2/SDL.h>
#include <stdlib.h>


#define XSIZE 600
#define YSIZE 600
#define MS 10
#define NAVE_LEN 20
#define NAVE_VEL 5
#define MISIL_LEN 5
#define MISIL_VEL 5

typedef struct Nave Nave;
typedef struct Misil Misil;

struct Nave{
  int x1,y1;
  int x2,y2;
  int x3,y3;
  int vx,vy;
  Misil *misiles;
};

struct Misil{
  int x1,y1;
  int x2,y2;
  int vx,vy;
  Misil *siguiente;
};

void NavePinta(Nave *nave,SDL_Renderer *renderer);
void NaveAvanzaIzqDer(Nave *nave);
void NaveAvanzaArrAb(Nave *nave);
void NaveDispara(Nave *nave);
void MisilAvanza(Misil *misil);
void MisilBorraObsoletos(Misil *misiles);

int main(int argc, char *argv[]) {
  //Se inicializan la biblioteca
  if(SDL_Init(SDL_INIT_EVERYTHING)<0){
    printf("SDL library error \n \n");
    return -1;
  }else{
    printf("SDL library started succesfully \n \n");
  }

  const Uint8 *keys;
  int typeEvent;          //Variable que almacena el tipo de evento.
  int gameOver = 0;       //Variable de condicion para el cierre de la aplicacion.
  SDL_Window *window;     //Ventana de juego
  SDL_Renderer *renderer; //Renderizador del juego.
  SDL_Event event;
  //Se inicializa la nave con parametros default
  Nave nave={XSIZE/2,YSIZE/2,XSIZE/2-NAVE_LEN,YSIZE/2+NAVE_LEN,XSIZE/2+NAVE_LEN
             ,YSIZE/2+NAVE_LEN,NAVE_VEL,NAVE_VEL,NULL};

  //Se inicializan tanto la ventana como el renderizador de la app.
  window = SDL_CreateWindow("Threadville",SDL_WINDOWPOS_UNDEFINED
                            ,SDL_WINDOWPOS_UNDEFINED,XSIZE,YSIZE,
                            SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
  keys = SDL_GetKeyboardState(NULL);

  while(!gameOver){
///////////////////////////////////////Inicia el control de los eventos//////////////
    //Retorna 1 si hay eventos pendientes, cero si no hay nada.
    if(SDL_PollEvent(&event)){
      typeEvent = event.type;    //EVENTOS.
      if (typeEvent==SDL_QUIT){gameOver=1;}
      else if(typeEvent==SDL_KEYDOWN){
        if(keys[SDL_SCANCODE_LEFT]){
          nave.vx = -abs(nave.vx);
          NaveAvanzaIzqDer(&nave);
        }else if(keys[SDL_SCANCODE_RIGHT]){
          nave.vx = abs(nave.vx);
          NaveAvanzaIzqDer(&nave);
        }else if(keys[SDL_SCANCODE_UP]){
          nave.vy = -abs(nave.vy);
          NaveAvanzaArrAb(&nave);
        }else if(keys[SDL_SCANCODE_DOWN]){
          nave.vy = abs(nave.vy);
          NaveAvanzaArrAb(&nave);
        }else if(keys[SDL_SCANCODE_SPACE]){
          NaveDispara(&nave);
        }
      }
    }
///////////////////////////////////////Finaliza el control de los eventos///////////////
    MisilBorraObsoletos(nave.misiles);
///////////////////////////////////////Inicia el control de la pantalla/////////////////
    SDL_SetRenderDrawColor(renderer,0,0,0,0); //Se define el color de la pantalla(negro)
    SDL_RenderClear(renderer);                //Se limpia la pantalla
    SDL_SetRenderDrawColor(renderer,255,255,255,0); //Se define el color de la nave(blanco)
    NavePinta(&nave,renderer);                //Metodo para pintar la nave.
    SDL_RenderPresent(renderer);              //Se actualiza la pantalla.
    SDL_Delay(MS);                            //Delay para refrescar la pantalla
///////////////////////////////////////Finaliza el control de la pantalla///////////////
  }

  //Se destruye la ventana y el Renderizador (cierre de la aplicacion).
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}

//Metodo que pinta los misiles y la nave
void NavePinta(Nave *nave,SDL_Renderer *renderer){
  //Pinta los misiles
  Misil *ixMisil = nave->misiles;
  while (ixMisil !=NULL){
    MisilAvanza(ixMisil);
    SDL_RenderDrawLine(renderer,ixMisil->x1,ixMisil->y1,ixMisil->x2,ixMisil->y2);
    ixMisil = ixMisil->siguiente;
  }

  //Pinta la nave
  SDL_Point points[4] = {{nave->x1,nave->y1},{nave->x2,nave->y2},
                         {nave->x3,nave->y3},{nave->x1,nave->y1}};
  SDL_RenderDrawLines(renderer,points,4);
}

//Movimiento horizontal de la nave
void NaveAvanzaIzqDer(Nave *nave){
  nave->x1 += nave->vx;
  nave->x2 += nave->vx;
  nave->x3 += nave->vx;
}

//Movimiento vertical de la nave
void NaveAvanzaArrAb(Nave *nave){
  nave->y1 += nave->vy;
  nave->y2 += nave->vy;
  nave->y3 += nave->vy;
}

//Metodo que agrega un misil a la lista enlazada.
void NaveDispara(Nave *nave){
  if(nave->misiles == NULL){
    nave->misiles = (Misil *) SDL_malloc(sizeof(Misil));
    nave->misiles->x1 = nave->x1;
    nave->misiles->y1 = nave->y1;
    nave->misiles->x2 = nave->x1;
    nave->misiles->y2 = nave->y1 - MISIL_LEN;
    nave->misiles->vx = 0;
    nave->misiles->vy = -MISIL_VEL;
    nave->misiles->siguiente = NULL;
  }else{
    Misil *ixMisil = nave->misiles;
    while(ixMisil->siguiente!=NULL){
      ixMisil = ixMisil->siguiente;
    }
    ixMisil->siguiente = (Misil *) SDL_malloc(sizeof(Misil));
    ixMisil=ixMisil->siguiente;
    ixMisil->x1 = nave->x1;
    ixMisil->y1 = nave->y1;
    ixMisil->x2 = nave->x1;
    ixMisil->y2 = nave->y1-MISIL_LEN;
    ixMisil->vx = 0;
    ixMisil->vy = -MISIL_VEL;
    ixMisil->siguiente = NULL;
  }
}

//Metodo que actualiza la posicion de los misiles.
void MisilAvanza(Misil *misil){
  misil->x1 += misil->vx;
  misil->y1 += misil->vy;
  misil->x2 += misil->vx;
  misil->y2 += misil->vy;
}

//Libera memoria de los misiles usados..!!
void MisilBorraObsoletos(Misil *misiles){
  Misil *ixMisil = misiles;//Puntero de los misiles
  if (ixMisil == NULL){
    return;
  }else{
    Misil *auxMisil;
    while(ixMisil->siguiente !=NULL){//Recorrido de los misiles
      if(ixMisil->siguiente->y1 < 0){
        auxMisil = ixMisil->siguiente->siguiente;
        SDL_free(ixMisil->siguiente);
        ixMisil->siguiente = auxMisil;
      }else{
        ixMisil = ixMisil->siguiente;
      }
    }
  }
}
//https://www.youtube.com/watch?v=IGiBHfDR6Ws
