OBJS = game.o main.o bird.o tex.o obstacle.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c -std=c++11 $(DEBUG)
LFLAGS = -Wall -lglfw -lGL -lSOIL $(DEBUG)

mustache-nemesis : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o mustache-nemesis
game.o : game.h game.cpp bird.o obstacle.o
	$(CC) $(CFLAGS) game.cpp
bird.o : bird.h bird.cpp vec.h tex.o
	$(CC) $(CFLAGS) bird.cpp
obstacle.o : obstacle.h obstacle.cpp
	$(CC) $(CFLAGS) obstacle.cpp
tex.o : tex.h tex.cpp
	$(CC) $(CFLAGS) tex.cpp
main.o : game.o main.cpp 
	$(CC) $(CFLAGS) main.cpp
clean:
	\rm *.o mustache-nemesis

