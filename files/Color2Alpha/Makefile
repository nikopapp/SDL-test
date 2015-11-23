CFLAGS = `pkg-config --cflags opencv`
TARGET = c2a
SOURCES = openCV.h $(TARGET).cpp
LIBS =  `pkg-config --libs opencv`
CC = g++
NUM = 3
IMG_IN = room0.png
IMG_OUT = room1.png

compile:
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LIBS)
	./$(TARGET) $(IMG_IN) $(IMG_OUT)
compare: compare.cpp
	$(CC) compare.cpp openCV.h -o compare $(CFLAGS) $(LIBS)
runcompare:
	./compare $(IMG_OUT) $(IMG_IN)
