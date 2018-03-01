cc=gcc
target=jack-at-linux
cflags=-o $(target) -g
libs=-lX11 -lasound -I$(shell pwd)/include -O3 -Wall
deps=source/mouse_x11.c source/rec_alsa.c

all: $(target).c
	$(cc) $(cflags) $(deps) $^ $(libs)

debug:
	valgrind -v ./$(target) --leak-check=full

exec:
	./$(target)

clean:
	rm -f $(target)
