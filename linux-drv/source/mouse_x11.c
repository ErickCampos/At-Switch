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

#include "mouse_x11.h"

void
mouse_click(Display *display, int button)
{
	/* create the event */
	XEvent event;
	memset(&event, 0, sizeof(event));

	/* setting the event parameters up */
	event.xbutton.button = button;
	event.xbutton.same_screen = True;
	event.xbutton.subwindow = DefaultRootWindow(display);

	while(event.xbutton.subwindow) {
		event.xbutton.window = event.xbutton.subwindow;
		XQueryPointer(display, event.xbutton.window,
				&event.xbutton.root, &event.xbutton.subwindow,
				&event.xbutton.x_root, &event.xbutton.y_root,
				&event.xbutton.x, &event.xbutton.y,
				&event.xbutton.state);
	}

	/* press */
	event.type = ButtonPress;
	if(XSendEvent(display, PointerWindow, True, ButtonPressMask, &event) == 0)
		fprintf(stderr, "Error to send the event!\n");
	XFlush(display);
	usleep(1);

	/* release */
	event.type = ButtonRelease;
	if(XSendEvent(display, PointerWindow, True, ButtonReleaseMask, &event) == 0)
		fprintf(stderr, "Error to send the event!\n");
	XFlush(display);
	usleep(1);

	printf("#####################cliquei valeu\n");
}

void
mouse_get_coords(Display *display, int *x, int *y)
{
	XEvent event;
	XQueryPointer(display, DefaultRootWindow(display),
			&event.xbutton.root, &event.xbutton.window,
			&event.xbutton.x_root, &event.xbutton.y_root,
			&event.xbutton.x, &event.xbutton.y,
			&event.xbutton.state);

	*x = event.xbutton.x;
	*y = event.xbutton.y;
}

void
mouse_move(Display *display, int x, int y)
{
	XWarpPointer(display,
				None, None,
				0, 0,
				0, 0,
				x, y);
	XFlush(display);
	usleep(1);
}

void
mouse_move_to(Display *display, int x, int y)
{
	int cur_x, cur_y;
	mouse_get_coords(display, &cur_x, &cur_y);
	XWarpPointer(display,
				None, None,
				0, 0,
				0, 0,
				-cur_x, -cur_y);
	XWarpPointer(display,
				None, None,
				0, 0,
				0, 0,
				x, y);
	usleep(1);
}
/* EOF */
