//gcc gui.c splashScreen.c functions.c-o gui.o `pkg-config --cflags --libs gtk+-3.0`

#include "splashScreen.h"
#include "functions.h"
#include <math.h>

typedef struct {
	double x, y;
}point;

char saveCalculate();
void plotGraph(GtkWidget *widget, GdkEventButton *event, gpointer user_data); 
void playMusicYouTube(GtkWidget *widget, GdkEventButton *event, gpointer user_data);
double shoeLace(GtkWidget *widget, GdkEventButton *event, gpointer user_data);
void openNewNotebookWindow(GtkButton *button, GtkNotebook *notebook);

struct counter count2;

int main (int argc, char *argv[] ) 
{

	//VAriable  declarations for ui features
	GtkWidget *window;
	GtkWidget *open, *plot, *save, *playMusic; //Buttons seen on screeen
	GtkWidget *grid;
	GtkWidget *imagecont;
	GtkWidget *box;
	GtkWidget *canvas;
	GtkWidget *notebook, *label, *frame, *notebookGrid;
	GtkDrawingArea *drawing_area;
	GtkStyleContext *openContext, *plotContext, *saveContext, *windowContext, *musicContext;//attach css to buttons
	GtkCssProvider *openProvider, *plotProvider, *saveProvider, *windowProvider, *musicProvider;//link to Css file

	char ch;
	int i;
	char bufferf[32];
	char bufferl[32];
	


	//Initalize GTK window
	count2.count = 0;
	gtk_init(&argc, &argv);
	

	if(showSplash("ear1.png", 10000, 680, 445) != 0) {
		fprintf(stderr, "%d\n", errno);
	}

	//create new ui features
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
	imagecont = gtk_image_new();
	drawing_area =(GtkDrawingArea*) gtk_drawing_area_new();
	gtk_box_pack_start(GTK_BOX(box),imagecont,TRUE,TRUE,0);

	//Initialize buttons
	open = gtk_button_new_with_label("open\n");
	plot = gtk_button_new_with_label("plot\n");
	save = gtk_button_new_with_label("save\n");
	playMusic = gtk_button_new_with_label("Youtube Playlist\n");

	//Initialize buttons

	//Initialize contexts
	openContext = gtk_widget_get_style_context(open);
	plotContext = gtk_widget_get_style_context(plot);
	saveContext = gtk_widget_get_style_context(save);
	windowContext = gtk_widget_get_style_context(window);
	musicContext = gtk_widget_get_style_context(playMusic);


	//Initialize contexts

	//Initialize providers
	openProvider = gtk_css_provider_new();
	plotProvider = gtk_css_provider_new();
	saveProvider = gtk_css_provider_new();
	windowProvider = gtk_css_provider_new();
	musicProvider = gtk_css_provider_new();


	//Initialize providers

	//load css files from different files
	gtk_css_provider_load_from_path(openProvider, "openStyles.css", NULL);
	gtk_css_provider_load_from_path(plotProvider, "plotStyles.css", NULL);
	gtk_css_provider_load_from_path(saveProvider, "saveStyles.css", NULL);
	gtk_css_provider_load_from_path(windowProvider, "windowStyles.css", NULL);
	gtk_css_provider_load_from_path(musicProvider, "musicStyles.css", NULL);


	//load css files from different files

	//Add context providers and attach CSS
	gtk_style_context_add_provider(openContext, GTK_STYLE_PROVIDER(openProvider),
									GTK_STYLE_PROVIDER_PRIORITY_USER);
	gtk_style_context_add_provider(plotContext, GTK_STYLE_PROVIDER(plotProvider),
									GTK_STYLE_PROVIDER_PRIORITY_USER);
	gtk_style_context_add_provider(saveContext, GTK_STYLE_PROVIDER(saveProvider),
									GTK_STYLE_PROVIDER_PRIORITY_USER);
	gtk_style_context_add_provider(windowContext, GTK_STYLE_PROVIDER(windowProvider),
									GTK_STYLE_PROVIDER_PRIORITY_USER);
	gtk_style_context_add_provider(musicContext, GTK_STYLE_PROVIDER(musicProvider),
									GTK_STYLE_PROVIDER_PRIORITY_USER);
	

	gtk_style_context_add_class(openContext, "open");
	gtk_style_context_add_class(plotContext, "plot");
	gtk_style_context_add_class(saveContext, "save");
	gtk_style_context_add_class(windowContext, "window");
	gtk_style_context_add_class(musicContext, "music");

	//Add context providers and attach CSS


	notebook = gtk_notebook_new();
	gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_TOP);

	grid = gtk_grid_new();
	//box

	gtk_grid_attach(GTK_GRID(grid), open, 0,0,1,1);
	gtk_grid_attach(GTK_GRID(grid), save, 1,0,1,1);
	gtk_grid_attach(GTK_GRID(grid), plot, 2,0,1,1);


	//gtk_grid_attach(GTK_GRID(grid), box, 1,2,1,1);
	//gtk_grid_attach(GTK_GRID(grid), (GtkWidget*)drawing_area, 1,2,1,1);
	gtk_grid_attach(GTK_GRID(grid), notebook , 1,1,2,1);
	gtk_grid_attach(GTK_GRID(grid), playMusic , 0,2,2,1);

	
	
	//box
	gtk_widget_add_events(window, GDK_BUTTON_PRESS_MASK);

	//set window title
	gtk_window_set_title(GTK_WINDOW(window), "Mak's Lab");
	//set window size
	gtk_window_set_default_size(GTK_WINDOW(window), 200,200);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	//Set window width
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	//add grid to window container
	gtk_container_add(GTK_CONTAINER(window), grid);

	//Main signal to handle delete_event for window
	g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(delete_event), NULL);
//show open dialog when open clicked
	g_signal_connect(open, "clicked", G_CALLBACK(on_open_image), imagecont);
	//create drawing area
	g_signal_connect(drawing_area, "draw", G_CALLBACK(on_window_draw), NULL);
	g_signal_connect(window, "button-press-event", G_CALLBACK(clicked), NULL);
	g_signal_connect(plot, "clicked", G_CALLBACK(plotGraph), NULL);

	g_signal_connect(save, "clicked", G_CALLBACK(shoeLace), NULL);
	g_signal_connect(playMusic, "clicked", G_CALLBACK(playMusicYouTube), NULL);


	
	// frame = gtk_frame_new("New Page");
	// gtk_container_set_border_width(GTK_CONTAINER(frame), 10);
	// gtk_widget_set_size_request(frame, 700, 700);
	// gtk_widget_show(frame);
	
	
	notebookGrid = gtk_grid_new();
	//gtk_container_set_border_width(GTK_CONTAINER(notebookGrid), 10);
	gtk_widget_set_size_request(notebookGrid, 800, 800); //800
	//gtk_container_add(GTK_CONTAINER(frame), notebookGrid);
	gtk_widget_show(notebookGrid);
	label = gtk_label_new("Image 1");
	gtk_notebook_prepend_page(GTK_NOTEBOOK(notebook), notebookGrid, label);

	//gtk_container_add(GTK_CONTAINER(notebookGrid), (GtkWidget*)drawing_area);
	gtk_grid_attach(GTK_GRID(notebookGrid), box, 0,1,1,1);

	gtk_grid_attach(GTK_GRID(notebookGrid), (GtkWidget*)drawing_area, 0,1,1,1);



	
	//Append pages to notebook
	//for (i = 0; i < 5; i++) {
	//	sprintf(bufferf, "Append frame %d", i + 1);
	//	sprintf(bufferl, "Page %d", i +1);
		// frame = gtk_frame_new(bufferf);
		// gtk_container_set_border_width(GTK_CONTAINER(frame), 10);
		// gtk_widget_set_size_request(frame, 700, 700);
		// gtk_widget_show(frame);

		// label = gtk_label_new(bufferf);
		// gtk_container_add(GTK_CONTAINER(frame), label);
		// gtk_widget_show(label);

		// label = gtk_label_new(bufferl);
		// gtk_notebook_prepend_page(GTK_NOTEBOOK(notebook), frame, label);
	//}

	//Append pages to notebook
	//
		//signal to handle destroy event
	//signal to handle button click
	//g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(hello), NULL);
	//signal to destroy window when button clicked
	//useful when trying to hide other widget in button
	//g_signal_connect_swapped(G_OBJECT(button), "clicked", G_CALLBACK(gtk_widget_destroy), G_OBJECT(window));

	//show widgets
	gtk_widget_show_all(window);

	gtk_main();
	return 0;
}
//opens inital save file then adds data to screen
char saveCalculate(GtkWidget *widget, GdkEventButton *event, gpointer user_data){
	char ch;
	gchar *text;
	FILE *fp;
	//open database
	fp = fopen("jass.txt", "r");

	if (fp == NULL) {
		perror("File is empty\n");
		exit(0);
	}
	ch = fgetc(fp);
	while( ch != EOF) {
		printf("%c",ch);
		 ch = fgetc(fp);
	}
	fclose(fp);
   return ch;
}
double shoeLace(GtkWidget *widget, GdkEventButton *event, gpointer user_data) {
	char *inputFile = "jass.txt";
	int i, numPoints;
	double leftSum = 0, rightSum = 0, result = 0;
	point *pointSet;
	FILE* fp = fopen(inputFile, "r");
	fscanf(fp, "%d", &numPoints);
	printf("%d\n",numPoints);

	pointSet = (point*)malloc((numPoints + 1)*sizeof(point));
	for(i = 0; i < numPoints; i++) {
		fscanf(fp, "%lf %lf", &pointSet[i].x, &pointSet[i].y);
	}
	fclose(fp);

	pointSet[numPoints] = pointSet[0];
	for(i = 0; i < numPoints; i++) {
		leftSum  +=pointSet[i].x*pointSet[i+1].y;
		rightSum +=pointSet[i+1].x*pointSet[i].y;
	}
	free(pointSet);
	result = 0.5*fabs(leftSum - rightSum);
	printf("%f\n", result);

	return result;
}
void plotGraph(GtkWidget *widget, GdkEventButton *event, gpointer user_data){
	system("gnuplot -p plot.sh");
}
void playMusicYouTube(GtkWidget *widget, GdkEventButton *event, gpointer user_data){
	system("youtube-dl -f 251 https://www.youtube.com/watch?v=5iAAZ_dWjjI -o - | ffplay -nodisp -autoexit -i -");
}


