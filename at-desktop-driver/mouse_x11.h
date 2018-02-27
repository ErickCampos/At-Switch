#ifndef _MOUSE_X11_
#define _MOUSE_X11_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>

void mouse_click(Display *display, int button);          /* simulate click */
void mouse_get_coords(Display *display, int *x, int *y); /* get coordinates */
void mouse_move(Display *display, int x, int y);         /* move (relat.) */
void mouse_move_to(Display *display, int x, int y);      /* move (abs.) */

#endif /* _MOUSE_X11_ */
