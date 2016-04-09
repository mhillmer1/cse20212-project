all: megaman

megaman: megaman.o
	g++ -lSDL_image megaman.o -o game

megaman.o: megaman.cpp
	g++ -c -lSDL_image megaman.cpp

clean:
	rm megaman *.o
