TARGET   = dots
CFLAGS   = -pedantic -Wall -Wextra -std=c99 -lm
SDLFLAGS = `sdl2-config --cflags` -lSDL2_image -lSDL2_mixer
SOURCES  = display.c main.c
INCS     = display.h
OUTPUT   = -o dots
LIBS     = `sdl2-config --libs`
OPTIM    = -O3
CC       = gcc

compile: $(TARGET)

$(TARGET): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) $(OUTPUT) $(CFLAGS) $(LIBS) $(SDLFLAGS) $(LINKERS) $(OPTIM)

run: compile
	./dots

hcomp:
	gcc main.c display.c -o dots -pedantic -Wall -Wextra -std=c99 -g -lm `sdl2-config --libs` `sdl2-config --cflags` -lSDL2_mixer -lSDL2_image
