programa = logica.c p1SDL.c
compile:
	gcc -o ejecutable $(programa) `sdl2-config --cflags --libs` `pkg-config --cflags --libs gtk+-3.0`

rm: ejecutable
	rm ejecutable

SDL2:
	sudo apt-get install libsdl2-dev
