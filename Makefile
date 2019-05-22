CC = g++

all: main.o Map.o View.o Actor.o Raycaster.o
	$(CC) main.o Map.o View.o Actor.o Raycaster.o -lsfml-graphics -lsfml-window -lsfml-system -g -o raycasting

main.o: main.cpp Map.hpp Actor.hpp View.hpp Raycaster.hpp
	$(CC) main.cpp -c -o main.o

Map.o: Map.cpp Map.hpp
	$(CC) Map.cpp -c -o Map.o

View.o: View.cpp View.hpp
	$(CC) View.cpp -c -o View.o

Actor.o: Actor.cpp Actor.hpp
	$(CC) Actor.cpp -c -o Actor.o

Raycaster.o: Raycaster.cpp Raycaster.hpp Map.hpp Actor.hpp View.hpp
	$(CC) Raycaster.cpp -c -o Raycaster.o


clean: 
	rm -f *.o raycasting
