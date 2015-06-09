OBJS = game.o main.o bird.o tex.o pew.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c -std=c++11 $(DEBUG)
LFLAGS = -Wall -lglfw -lGL -lSOIL $(DEBUG)

mustache-nemesis : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o mustache-nemesis
game.o : game.h game.cpp bird.o pew.o col.h
	$(CC) $(CFLAGS) game.cpp
bird.o : bird.h bird.cpp vec.h col.h tex.o pew.o
	$(CC) $(CFLAGS) bird.cpp
pew.o : pew.h pew.cpp tex.o
	$(CC) $(CFLAGS) pew.cpp
tex.o : tex.h tex.cpp
	$(CC) $(CFLAGS) tex.cpp
main.o : game.o main.cpp 
	$(CC) $(CFLAGS) main.cpp
clean:
	\rm *.o mustache-nemesis

