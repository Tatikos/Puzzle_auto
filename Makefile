# Makefile for Latin Square Program

CC = gcc
CFLAGS = -Wall
TARGET = latin_square_game

all: $(TARGET)

$(TARGET): main.o data.o checks.o autoplay.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o data.o checks.o autoplay.o

main.o: main.c data.h checks.h autoplay.h
	$(CC) $(CFLAGS) -c main.c

data.o: data.c data.h
	$(CC) $(CFLAGS) -c data.c

checks.o: checks.c checks.h
	$(CC) $(CFLAGS) -c checks.c

autoplay.o: autoplay.c autoplay.h
	$(CC) $(CFLAGS) -c autoplay.c

clean:
	rm -f *.o $(TARGET)