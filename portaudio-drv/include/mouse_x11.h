/*
 * A minimal "driver" to make all sort of AT switches work on a desktop computer
 * via audio jack's P2, 3.5mm connector as a simple 'mouse click'. No USB or
 * additional mouse device is needed, just the switch :)
 *  
 * Authors: Feb, 2018
 * Cassio Batista - cassio.batista.13@gmail.com
 * Erick Campos - erick.c.modesto@gmail.com
 * Federal University of Pará (UFPA). Belém, Brazil.
 * 
 * Credits:
 * ALSA Capture Program: Paul David (http://equalarea.com/paul/alsa-audio.html)
 * Mouse with X11/Xlib: Enrico "Pioz" (https://gist.github.com/pioz/726474)
 *
 * Source: Enrico "Pioz"'s gist (https://gist.github.com/pioz/726474)
 *
 */

#ifndef _MOUSE_X11_
#define _MOUSE_X11_

#define X11_TAG   "[X11] "
#define HHPC_TAG  "[HHPC] "
#define X11_DEGUB 0

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/cursorfont.h>

#include <sys/select.h>
#include <sys/time.h>

#include <signal.h>
#include <time.h>

void x11_click(Display *display, int button);             /* simulate click */
void x11_get_coords(Display *display, int *x, int *y);    /* get coordinates */
void x11_move(Display *display, int x, int y);            /* move (relat.) */
void x11_move_to(Display *display, int x, int y);         /* move (abs.) */
void x11_delay(time_t sec, long msec);
int  x11_grab_pointer(Display *disp, Window win, Cursor cursor, unsigned int mask);
void x11_color_cursor(Display *disp, Window win);  /* modify cursor icon */

#endif /* _MOUSE_X11_ */
