#include "display.h"
// Include the SDL header here, not in display.h, to make sure this is the
// only module wih access to SDL.
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
// Define the display structure here, to make sure this is the only module
// which mentions SDL.
struct display {
    SDL_Window *window;
    SDL_Texture *surface;
    SDL_Surface *temp;
    SDL_Texture *background;
    SDL_Renderer *renderer;
    SDL_Event event;
    Uint32 colour;
    //declare the music file
    Mix_Music *music;
    Mix_Chunk *zap;
};

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREEN_DEPTH 8

enum textquality {solid, shaded, blended};

// Loads a font, nothing fancy.
// Put sensible error handling code in. If you pass the NULL in later on,
// SDL_ttf dies pretty horribly.
TTF_Font* loadfont(char* file, int ptsize)
{
  TTF_Font* tmpfont;
  tmpfont = TTF_OpenFont(file, ptsize);
  if (tmpfont == NULL) {
    printf("Unable to load font: %s %s \n", file, TTF_GetError());
    // Handle the error here.
  }
  return tmpfont;
}

// SDL_ttf has a few modes you can draw with, check its documentation.
SDL_Surface *drawtext(TTF_Font* fonttodraw, char fgR, char fgG, char fgB, char fgA,
	char bgR, char bgG, char bgB, char bgA, char text[], textquality quality)
{
  SDL_Color tmpfontcolor = {fgR,fgG,fgB,fgA};
  SDL_Color tmpfontbgcolor = {bgR, bgG, bgB, bgA};
  SDL_Surface* resulting_text;

  if (quality == solid) {
	  resulting_text = TTF_RenderText_Solid(fonttodraw, text, tmpfontcolor);
  }
  else if (quality == shaded) {
	  resulting_text = TTF_RenderText_Shaded(fonttodraw, text, tmpfontcolor, tmpfontbgcolor);
  }
  else if (quality == blended) {
	  resulting_text = TTF_RenderText_Blended(fonttodraw, text, tmpfontcolor);
  }

  return resulting_text;
}

/*
int main(int argc, char** argv) {
	// Must call initialise first.
  TTF_Init();

	// This loads courier, but any font will do.
  TTF_Font* font = loadfont("C:/windows/fonts/cour.ttf", 10);
	SDL_Surface* surface = drawtext(font, 255, 255, 255, 70, 0, 0, 0, 0, "test", blended);

	// End of SDL_ttf stuff, this is just SDL to display the text we made.
	SDL_Surface* screen;
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, SDL_SWSURFACE);
	SDL_BlitSurface(surface, NULL, screen, NULL);
	SDL_Flip(screen);

	while (1);

  return 0;
}
*/
// Fail, including the SDL error message if any, and stop the program.
void fail(char *s) {
    fprintf(stderr, "%s: %s\n", s, SDL_GetError());
    SDL_Quit();
    exit(1);
}


Display *newDisplay()
{
    Display *d = malloc(sizeof(Display));
    int r = SDL_Init(SDL_INIT_EVERYTHING);
    if (r < 0) fail("Unable to initialize SDL");
    r = TTF_Init();
    TTF_Font* font = loadfont("C:/windows/fonts/cour.ttf", 10);
    if (r < 0) fail("Unable to initialize tff");
     //Initialize SDL_mixer
     r= Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
     if(r < 0 ) {
     printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n",
      Mix_GetError() );
     return(0);
   }    int x = SDL_WINDOWPOS_UNDEFINED, y = SDL_WINDOWPOS_UNDEFINED;
    d->window = SDL_CreateWindow("", x, y, WWIDTH, WHEIGHT, 0);
    if (d->window == NULL) fail("Unable to initialize SDL Window");
    d->renderer = SDL_CreateRenderer(d->window, -1, 0);
    SDL_SetRenderDrawColor(d->renderer, 0, 0, 0, 0);
    d->zap = Mix_LoadWAV("files/click.wav");
    Mix_VolumeChunk(d->zap, 15);
    if (d->zap==NULL){fail("music not good");}
    d->music = Mix_LoadMUS("files/PdPrince-SStrobe.mp3");
    if (d->music==NULL){fail("music not good");}
     //If there is no music playing
     if( Mix_PlayingMusic() == 0 ) {
     //Play the music
     Mix_PlayMusic( d->music, -1.0 ); }
    /*
    d->surface = SDL_GetWindowSurface(d->window);
    Uint32 black = SDL_MapRGBA(d->surface->format, 0, 0, 0, 0);
    if (d->surface == NULL) fail("Unable to get SDL surface");
    r = SDL_FillRect(d->surface, NULL, black);
    if (r < 0) fail("Unable to draw black background");
    r = SDL_UpdateWindowSurface(d->window);
    if (r < 0) fail("Unable to update SDL window");*/
    return d;
}

void setColour(Display *d, int r, int g, int b, int a) {

  SDL_SetRenderDrawColor(d->renderer, r, g, b, a);
}
void drawBox(Display *d, int x, int y, int h, int w) {
SDL_Rect rect={x,y,h,w};
    SDL_SetRenderDrawBlendMode(d->renderer, SDL_BLENDMODE_NONE);
    int r = SDL_RenderFillRect(d->renderer, &rect);
    if (r < 0) fail("Unable to draw SDL box");

}


// Update the window on screen, after delaying for the (rest of) the given time.
void drawFrame(Display *d, int milliseconds) {
    int t = milliseconds - SDL_GetTicks() % milliseconds;
    SDL_Delay(t);
    SDL_RenderPresent(d->renderer);
    SDL_RenderClear(d->renderer);

}

void loadPhoto(Display *d, char *s)
{
  d->temp = IMG_Load(s);
  if (d->temp == NULL){
    fail("bad photo");
  }
  d->background = SDL_CreateTextureFromSurface(d->renderer, d->temp);
  SDL_SetTextureAlphaMod(d->background , 255);
  SDL_SetTextureBlendMode(d->background, SDL_BLENDMODE_BLEND);
    /* we got the texture now -> free surface */
  SDL_RenderCopy(d->renderer, d->background, NULL, NULL);
//  d->surface = IMG_LoadTexture(d->renderer, s);
}

void splashPhoto(Display *d)
{
SDL_RenderCopy(d->renderer, d->background, NULL, NULL);
}

/*My own delay function*/
void myDelay(int ms)
{
  SDL_Delay(ms);
}

int getEvent(Display *d)
{
    int r;
    r=-SDL_PollEvent(&d->event)-1;
    if (d->event.type == SDL_KEYDOWN){
      switch (d->event.key.keysym.sym) {
        case SDLK_0:
        r=0;
        break;
        case SDLK_1:
        r=1;
        break;
        case SDLK_2:
        r=2;
        break;
        case SDLK_3:
        r=3;
        break;
        case SDLK_4:
        r=4;
        break;
        case SDLK_5:
        r=5;
        break;
        case SDLK_6:
        r=6;
        break;
        case SDLK_7:
        r=7;
        break;
        case SDLK_ESCAPE:
        r=10;
        break;
        default:
        r = -1;
        break;

      }
    }
    if(d->event.type != SDL_QUIT){
    return r;
    }
    else{
      return 10;
    }

}
void drawLights(Display *d,int lights[8])
{
  int i=0;
  while(i<8){
    if(lights[i]==1){
      drawBox(d, 95*(i+1),100, WHEIGHT/8,WHEIGHT-280);
    }
  i++;
  }
}
void drawSwithces(Display *d,int lights[8])
{
  int i=0;
  while(i<8){
    if(lights[i]==1){
      drawDisk(d, 95*(i)+150, 580, 10 );
    }
    else{
      drawDisk(d, 95*(i)+150, 605, 10 );
    }
  i++;
  }

}
void lightsInit(int *l)
{
  int i=0;
  while(i<8){
    *l++=0;
    i++;
  }
}
bool eventHandler(Display *d, int l[8],int swi)
{
  bool ended = false;
  if(swi==10){
    ended = true;
  }
  else{
    if(swi>=0){
      Mix_PlayChannel( -1, d->zap, 0 );
      switch (l[swi] ){
        case 0:
          l[swi]=1;
          break;
        case 1:
          l[swi]=0;
          break;
     }
    }
 }
 return ended;
}
void drawDisk(Display *d, int cx, int cy, int r)
{

   double dy;
   for (dy = 1; dy <= r; dy += 1.0) {
        double dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
        SDL_RenderDrawLine(d->renderer, cx-dx, cy+r-dy, cx+dx, cy+r-dy);
        SDL_RenderDrawLine(d->renderer, cx-dx, cy-r+dy, cx+dx, cy-r+dy);
   }

}

void closeDisplay(Display *d)
{
  //Stop the music
  /*Mix_HaltMusic();
  Mix_FreeMusic(d->music);
  Mix_CloseAudio();
  free(d);*/
  SDL_DestroyWindow(d->window);
  SDL_DestroyRenderer(d->renderer);
  SDL_Quit();
}

/* Return true if the quit button has been pressed.
bool quitEvent() {
    SDL_Event event;
    int r = SDL_PollEvent(&event);
    return r > 0 && event.type == SDL_QUIT;
}*/
