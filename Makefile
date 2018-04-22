programa = p1SDL.c
compile: 
	gcc -o ejecutable $(programa) `sdl2-config --cflags --libs`

rm: ejecutable
	rm ejecutable

SDL2: 
	sudo apt-get install libsdl2-dev
