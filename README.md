App Images:

![3](https://user-images.githubusercontent.com/69147048/89176156-b57c0700-d591-11ea-8148-d0b2574bdc8b.png)
![9](https://user-images.githubusercontent.com/69147048/89176270-e4927880-d591-11ea-9e30-32ea93817120.png)
# GTK-Application for Ubuntu Linux 20.04.01
This is a project I made during my freshman summer. It was funded by Yale under the First-Year Summer Fellowship program. I was working in Professor Michael Mak's Lab
in the Department of Biomedical Engineering, and my mentor was Hugh Xiao. 

This is a simple GUI made using C and styled with the GTK framework. It is meant for basic scientific image editing and data analysis. 

I wrote a plot.sh script to make boxplots using GNUPlot and a playmusic.sh script to stream music from Youtube in the terminal. 
Note: Idk if it runs on windows, it uses Linux calls for some things.

PS. The code isn't clean, I am working on that!

How to Use
1. Clone the repo- git clone https://github.com/MurageKibicho/GTK-Application
2. Open the GTK-Application folder and open the directory called GUI
3. Open a terminal in the GUI folder and write <pre> gcc gui.c splashScreen.c functions.c -o gui.o `pkg-config --cflags --libs gtk+-3.0`
</pre>
4. In the same terminal window, open the app using <pre> ./gui.o</pre>

App Features: 
1. Reads TIFF images
2. Creates drawing canvas
3. YouTube music player 
4. Makes Boxplots using GNUPlot framework

Cheers!
