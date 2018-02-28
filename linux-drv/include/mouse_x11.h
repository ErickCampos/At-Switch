/*
 * A minimal "driver" to make all sort of AT switches work on a desktop computer
 * via audio jack's P2, 3.5mm connector as a simple 'mouse click'. No USB or
 * additional mouse device is needed, just the switch :)
 *  
 * Authors: Feb, 2018. Federal University of Pará (UFPA). Belém, Brazil.
 * Cassio Batista - cassio.batista.13@gmail.com
 * Erick Campos - erick.c.modesto@gmail.com
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

#define MOUSE_X11_DEGUB 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>

void mouse_click(Display *display, int button);          /* simulate click */
void mouse_get_coords(Display *display, int *x, int *y); /* get coordinates */
void mouse_move(Display *display, int x, int y);         /* move (relat.) */
void mouse_move_to(Display *display, int x, int y);      /* move (abs.) */

#endif /* _MOUSE_X11_ */
