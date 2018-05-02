cc=gcc
target=jatsd
cflags=-o $(target) -g -Wall -O2
libs=-lX11 -lportaudio -I$(shell pwd)/include -lm
deps=source/mouse_x11.c source/rec_pa.c

all: $(target).c
	$(cc) $(cflags) $(deps) $^ $(libs)

debug:
	gdb ./$(target)

exec:
	./$(target)

clean:
	rm -f $(target)
