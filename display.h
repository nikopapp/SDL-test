#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define WHEIGHT             700
#define WWIDTH             1100
#define MILLISECONDDELAY     20


// Declare the display structure.  The details are defined inside display.c
struct Display;
typedef struct display Display;

// Create a new display object.
Display *newDisplay();

//Set drawing colour
void setColour(Display *d, int r, int g, int b, int a);


// Update the window on screen, after delaying for the (rest of) the given time.
void drawFrame(Display *d, int milliseconds);
// Return true if the quit button has been pressed.
bool quitEvent(Display *d);

// Draw a filled rectangle at a given position.
void drawBox(Display *d, int x, int y, int h, int w);

//Listens for keyboard events
int getEvent();

//load photo file
void loadPhoto(Display *d, char *s);
void splashPhoto(Display *d);

//drow lights on
void drawLights(Display *d,int lights[8]);

//drow swithces
void drawSwithces(Display *d,int lights[8]);

//Drow swich bttons
void drawDisk(Display *d, int cx, int cy, int r);

//My own delay function
void myDelay(int ms);

void lightsInit(int *l);

//Controls lights and listens for SDL_QUIT;
bool eventHandler(Display *d, int l[8],int swi);

// Kill display/SDL
void closeDisplay(Display *d);
