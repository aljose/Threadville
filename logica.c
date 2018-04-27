#include "logica.h"
Cars* getCars(){
  return 0;
}

#include <gtk/gtk.h>

static void printing( GtkWidget *widget,GtkWidget *entry ){
  // printf ("Entry contents_1 : %s\n", entry_text1);
  // printf ("Entry contents_2 : %s\n", entry_text2);
  // printf ("Entry contents_3 : %s\n", entry_text3);
  // printf ("Entry contents_4 : %s\n", entry_text4);
  // printf ("Entry contents_5 : %s\n", entry_text5);
}

/* Our callback.
 * The data passed to this function is printed to stdout */
static void callback1( GtkWidget *widget,GtkWidget *entry ){
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  //entry_text1 = (char*)entry_text;
  printf ("Entry contents: %s\n", entry_text);
}

static void callback2( GtkWidget *widget,GtkWidget *entry ){
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  char *temp = entry_text;
  printf ("Entry contents: %s\n", temp);
}

static void callback3( GtkWidget *widget,GtkWidget *entry ){
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  printf ("Entry contents: %s\n", entry_text);
}

static void callback4( GtkWidget *widget,GtkWidget *entry ){
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  printf ("Entry contents: %s\n", entry_text);
}

static void callback5( GtkWidget *widget,GtkWidget *entry ){
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  printf ("Entry contents: %s\n", entry_text);
}



void principal(){
printf("Voy por aca1");
    GtkWidget *window;
    GtkWidget *label1;
    GtkWidget *entry1;
    GtkWidget *button1;
    GtkWidget *label2;
    GtkWidget *entry2;
    GtkWidget *button2;
    GtkWidget *label3;
    GtkWidget *entry3;
    GtkWidget *button3;
    GtkWidget *label4;
    GtkWidget *entry4;
    GtkWidget *button4;
    GtkWidget *label5;
    GtkWidget *entry5;
    GtkWidget *button5;
    GtkWidget *buttonQuit;

    GtkWidget *table;
    gtk_init (NULL,NULL);
    /* Create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    /* Set the window title */
    gtk_window_set_title (GTK_WINDOW (window), "Properties");
    /* Set a handler for delete_event that immediately
     * exits GTK. */
    g_signal_connect (window, "delete-event",G_CALLBACK (gtk_main_quit), NULL);
    /* Sets the border width of the window. */
    gtk_container_set_border_width (GTK_CONTAINER (window), 20);
    /* Create a 2x2 table */
    table = gtk_grid_new ();

    /* Create first button */
printf("Voy por aca");
    label1  = gtk_label_new ("Label:");
    entry1  = gtk_entry_new ();
    button1 = gtk_button_new_with_label ("Save");
    label2  = gtk_label_new ("Viajes:");
    entry2  = gtk_entry_new ();
    button2 = gtk_button_new_with_label ("Save");
    label3  = gtk_label_new ("Velocidad:");
    entry3  = gtk_entry_new ();
    button3 = gtk_button_new_with_label ("Save");
    label4  = gtk_label_new ("Color:");
    entry4  = gtk_entry_new ();
    button4 = gtk_button_new_with_label ("Save");
    label5  = gtk_label_new ("Modelo:");
    entry5  = gtk_entry_new ();
    button5 = gtk_button_new_with_label ("Save");
    buttonQuit = gtk_button_new_with_label ("Quit");

    gtk_grid_attach(GTK_GRID(table), label1, 0, 1, 1, 1);
    gtk_widget_show (label1);
    gtk_grid_attach (GTK_GRID(table), entry1, 0, 2, 1, 1);
    gtk_widget_show (entry1);
    gtk_grid_attach(GTK_GRID(table), button1, 1, 2, 1, 1);
    gtk_widget_show (button1);
    g_signal_connect (button1, "clicked",G_CALLBACK (callback1),entry1);
    //
    gtk_grid_attach(GTK_GRID(table), label2, 0, 3, 1, 1);
    gtk_widget_show (label2);
    gtk_grid_attach(GTK_GRID(table), entry2, 0, 4, 1, 1);
    gtk_widget_show (entry2);
    gtk_grid_attach(GTK_GRID(table), button2,1, 4, 1, 1);
    gtk_widget_show (button2);
    g_signal_connect (button2, "clicked",G_CALLBACK (callback2),entry2);
    //
    gtk_grid_attach(GTK_GRID(table), label3, 0, 5, 1, 1);
    gtk_widget_show (label3);
    gtk_grid_attach(GTK_GRID(table), entry3, 0, 6, 1, 1);
    gtk_widget_show (entry3);
    gtk_grid_attach(GTK_GRID(table), button3,1, 6, 1, 1);
    gtk_widget_show (button3);
    g_signal_connect (button3, "clicked",G_CALLBACK (callback3),entry3);
    //
    gtk_grid_attach(GTK_GRID(table), label4, 0, 7, 1, 1);
    gtk_widget_show (label4);
    gtk_grid_attach(GTK_GRID(table), entry4, 0, 8, 1, 1);
    gtk_widget_show (entry4);
    gtk_grid_attach(GTK_GRID(table), button4, 1, 8, 1, 1);
    gtk_widget_show (button4);
    g_signal_connect (button4, "clicked",G_CALLBACK (callback4),entry4);
    //
    gtk_grid_attach(GTK_GRID(table), label5, 0, 9, 1, 1);
    gtk_widget_show (label5);
    gtk_grid_attach(GTK_GRID(table), entry5, 0, 10, 1, 1);
    gtk_widget_show (entry5);
    gtk_grid_attach(GTK_GRID(table), button5,1, 10, 1, 1);
    gtk_widget_show (button5);
    g_signal_connect (button5, "clicked",G_CALLBACK (callback5),entry5);
    //
    gtk_grid_attach(GTK_GRID(table), buttonQuit, 0, 11, 2, 1);
    gtk_widget_show (buttonQuit);
    g_signal_connect (buttonQuit, "clicked",G_CALLBACK (printing), NULL);
    //
    /* Put the table in the main window */
    gtk_container_add (GTK_CONTAINER (window), table);

    gtk_widget_show (table);
    gtk_widget_show (window);
    gtk_main ();
}
