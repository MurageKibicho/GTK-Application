//run gcc gui.c splashScreen.c -o gui.o
#include <gtk/gtk.h>
#include "splashScreen.h"

gboolean closeScreen(gpointer data) {
	gtk_widget_destroy((GtkWidget*)data);
	gtk_main_quit();
	return FALSE;
}

int showSplash(char *imageName, int time, int width, int height) {
	GtkWidget *window, *image, *text;
	GdkPixbuf *pix;

	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	pix =  gdk_pixbuf_new_from_file(imageName, NULL);
	pix = gdk_pixbuf_scale_simple(pix,680,445,GDK_INTERP_BILINEAR);
	image = gtk_image_new_from_pixbuf(pix);

	text = gtk_label_new("Never have I ever");

	gtk_label_set_text((GtkLabel*)text, "Trying this shit");

	gtk_widget_set_size_request(window, width, height);
	gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

	gtk_container_add(GTK_CONTAINER(window),image);
	gtk_widget_show_all(window);
	g_timeout_add(time, closeScreen, window);
	gtk_main();
	return 0;
}