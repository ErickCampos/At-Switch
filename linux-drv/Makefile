target=jack-at-linux.c
cc=gcc
libs=-lX11 -lasound -I$(shell pwd)/include -g -o jack-at-linux

all:
	$(cc) source/mouse_x11.c source/rec_alsa.c $(target) $(libs)

debug:
	valgrind -v ./jack-at-linux --leak-check=full

exec:
	./jack-at-linux
