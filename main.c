#include "display.h"

//Dark grey
#define R                    30
#define G                    30
#define B                    30

//Lamp Colour / State
struct lights{
  int r;
  int g;
  int b;
  int a;
  int on[];
};
typedef struct lights Lights;

int main(void)
{
  Lights l;
  //Returns a Display structure wich contains textures
  //Mix_chunks Mix_music etc
  Display *d = newDisplay();
  bool ended = false;
  int *p;
  p=l.on;
  lightsInit(p);
  int swi;
  //setting lightbulb colour
  l.r=41;
  l.g=95;
  l.b=140;
  l.a=200;
  //loads photo to a texture and splashes it to the renderer
  loadPhoto( d, "files/room0.bmp");
  while (! ended) {
      //Sets the drawing colour to dark grey
      setColour(d, R, G, B, 255);
      //Draws a dark grey rectangle the size of the window
      drawBox(d, 0 , 0,WWIDTH, WHEIGHT);
      setColour(d, l.r, l.g, l.b, l.a);
      //Draws a light blue rectangle behind each light that is on
      drawLights(d,l.on);
      //Gets the photo on the window (Photo lamps are transparent)
      splashPhoto(d);
      //Sets the drawing colour to light grey for the switch circles
      setColour(d, 150, 150, 150, 0);
      //Draws the switch circles
      drawSwithces(d,l.on);
      //Refreshes window
      drawFrame(d, MILLISECONDDELAY);
      //Listens keyboard for events
      swi=getEvent(d);
      //Handles events and waits for SDL_QUIT
      ended = eventHandler(d,l.on,swi);

  }
  //Terminates everything
  closeDisplay(d);
  return 0;
}
