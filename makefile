all: src/main.o src/glad.o src/window.o
	g++ -lglfw -ldl src/main.o src/window.o src/glad.o -o cool

src/main.o: src/main.c
	g++ -c -Iinclude src/main.c -o src/main.o

src/glad.o: src/glad.c
	g++ -c -Iinclude src/glad.c -o src/glad.o

src/window.o: src/window.c
	g++ -c -Iinclude src/window.c -o src/window.o