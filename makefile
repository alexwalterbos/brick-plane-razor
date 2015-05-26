OBJS = Game.o main.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall -lglfw -lGL $(DEBUG)

mustache-nemesis : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o mustache-nemesis
Game.o : Game.h
	$(CC) $(CFLAGS) Game.cpp

main.o : 
	$(CC) $(CFLAGS) main.cpp
clean:
	\rm *.o mustache-nemesis

