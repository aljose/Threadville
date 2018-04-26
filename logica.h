#ifndef _LOGICA_H_
#define _LOGICA_H_

#include <gtk/gtk.h>

char entry_text1[25];
char entry_text2[25];
char entry_text3[25];
char entry_text4[25];
char entry_text5[25];

typedef struct Cars Cars;
struct Cars{
  int id;
  int tipo;
  int x,y;
  Cars *siguiente;
};

Cars* getCars();
static void callback1( GtkWidget *widget,GtkWidget *entry );
static void callback2( GtkWidget *widget,GtkWidget *entry );
static void callback3( GtkWidget *widget,GtkWidget *entry );
static void callback4( GtkWidget *widget,GtkWidget *entry );
static void callback5( GtkWidget *widget,GtkWidget *entry );
static void printing( GtkWidget *widget,GtkWidget *entry );
void principal ();

#endif
