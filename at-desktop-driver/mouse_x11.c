/* Written by Pioz.
 * Compile with: gcc -o autoclick autoclick.c -lX11
 * source: https://gist.github.com/pioz/726474 
 *
 * Cassio Batista - casio.batista.13@gmail.com
 * Federal University of Pará (UFPA). Belém, Brazil.
 */

#include "mouse_x11.h"

/* simulate mouse click */
void
mouse_click(Display *display, int button)
{
	// create and setting up the event
	XEvent event;
	memset(&event, 0, sizeof(event));

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
}

/* get mouse coordinates */
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

/* move mouse pointer(relative) */
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

/* move mouse pointer(absolute) */
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
