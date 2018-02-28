target=main.c
cc=gcc
libs=-lX11 -lasound

all:
	$(cc) -g mouse_x11.c rec_alsa.c $(target) $(libs)

debug:
	valgrind -v ./a.out --leak-check=full

exec:
	./a.out
