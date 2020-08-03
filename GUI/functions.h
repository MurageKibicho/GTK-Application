#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>	
#include <cairo.h>
#include <errno.h>

/* Global variables for storing mouse coordinates,
* count is index of arrays, coordx and coordy are x and y coordinates of the mouse
*/

struct counter{
	int count;				
	double coordx[100];
	double coordy[100];
};


//function prototypes
void do_drawing(cairo_t *);
gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data);
void do_drawing(cairo_t *cr);
gboolean clicked(GtkWidget *widget, GdkEventButton *event, gpointer user_data);
gboolean on_window_draw (GtkWidget *widget, GdkEventExpose *event, gpointer data);
void on_open_image(GtkButton *button, gpointer user_data);
gint delete_event(GtkWidget *widget, GdkEvent *event, gpointer data);
//end of function prototypes

#endif