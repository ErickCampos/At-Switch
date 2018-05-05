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

static volatile sig_atomic_t working;

static void
mouse_signal_handler(int signo) 
{
    working = 0;
}

void
mouse_click(Display *display, int button)
{
	#if MOUSE_X11_DEGUB
		fprintf(stdout, MOUSE_X11_TAG "creating mouse click event\n");
	#endif
	/* create the event */
	XEvent event;
	memset(&event, 0, sizeof(event));

	/* setting the event parameters up */
	event.xbutton.button = button;
	event.xbutton.same_screen = True;
	event.xbutton.subwindow = DefaultRootWindow(display);

	#if MOUSE_X11_DEGUB
		fprintf(stdout, MOUSE_X11_TAG "querying pointer to subwindows\n");
	#endif
	while(event.xbutton.subwindow) {
		event.xbutton.window = event.xbutton.subwindow;
		XQueryPointer(display, event.xbutton.window,
				&event.xbutton.root, &event.xbutton.subwindow,
				&event.xbutton.x_root, &event.xbutton.y_root,
				&event.xbutton.x, &event.xbutton.y,
				&event.xbutton.state);
	}

	#if MOUSE_X11_DEGUB
		fprintf(stdout, MOUSE_X11_TAG "sending the 'press' event\n");
	#endif
	/* press */
	event.type = ButtonPress;
	if(XSendEvent(display, PointerWindow, True, ButtonPressMask, &event) == 0)
		fprintf(stderr, "Error to send the event!\n");
	XFlush(display);
	usleep(1);

	#if MOUSE_X11_DEGUB
		fprintf(stdout, MOUSE_X11_TAG "sending the 'release' event\n");
	#endif
	/* release */
	event.type = ButtonRelease;
	if(XSendEvent(display, PointerWindow, True, ButtonReleaseMask, &event) == 0)
		fprintf(stderr, "Error to send the event!\n");
	XFlush(display);
	usleep(1);
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

static int
mouse_setup_signals() 
{
	struct sigaction act;

	memset(&act, 0, sizeof(act));

	/* Use the sa_sigaction field because the handles has two additional parameters */
	act.sa_handler = mouse_signal_handler;
	act.sa_flags   = 0;
	sigemptyset(&act.sa_mask);

	if (sigaction(SIGTERM, &act, NULL) == -1) {
		perror("hhpc: could not register SIGTERM");
		return 0;
	}

	if (sigaction(SIGHUP, &act, NULL) == -1) {
		perror("hhpc: could not register SIGHUP");
		return 0;
	}

	//if (sigaction(SIGINT, &act, NULL) == -1) {
	//	perror("hhpc: could not register SIGINT");
	//	return 0;
	//}

	if (sigaction(SIGQUIT, &act, NULL) == -1) {
		perror("hhpc: could not register SIGQUIT");
		return 0;
	}

	return 1;
}

static void
delay(time_t sec, long msec) 
{
	struct timespec sleep;

	sleep.tv_sec  = sec;
	sleep.tv_nsec = (msec % 1000) * 1000 * 1000;

	if (nanosleep(&sleep, NULL) == -1) 
		mouse_signal_handler(0);
}

static int
mouse_grab_pointer(Display *disp, Window win, Cursor cursor, unsigned int mask)
{
	int rc;

	/* retry until we actually get the pointer (with a suitable delay)
	 * or we get an error we can't recover from. */
	while (working) {
		rc = XGrabPointer(disp, win, True, mask,
				GrabModeSync, GrabModeAsync, None, cursor, CurrentTime);

		switch (rc) {
			case GrabSuccess:
				#if MOUSE_X11_DEGUB
					fprintf(stdout, "hhpc: succesfully grabbed mouse pointer\n");
				#endif
				return 1;
			case AlreadyGrabbed:
				#if MOUSE_X11_DEGUB
					fprintf(stdout, "hhpc: XGrabPointer: already grabbed ");
					fprintf(stdout, "mouse pointer, retrying with delay\n");
				#endif
				delay(0, 500);
				break;
			case GrabFrozen:
				#if MOUSE_X11_DEGUB
					fprintf(stdout, "hhpc: XGrabPointer: ");
					fprintf(stdout, "grab was frozen, retrying after delay\n");
				#endif
				delay(0, 500);
				break;
			case GrabNotViewable:
				fprintf(stderr, "hhpc: XGrabPointer: grab was not viewable, exiting\n");
				return 0;
			case GrabInvalidTime:
				fprintf(stderr, "hhpc: XGrabPointer: invalid time, exiting\n");
				return 0;
			default:
				fprintf(stderr, "hhpc: XGrabPointer: ");
				fprintf(stderr, "could not grab mouse pointer (%d), exiting\n", rc);
				return 0;
		}
	}

	return 0;
}

void
mouse_color_cursor(Display *display, Window win)
{
	//int xfd   = ConnectionNumber(display);

	const unsigned int mask = PointerMotionMask | ButtonPressMask;

	//fd_set fds;
	XEvent event;

	/* https://tronche.com/gui/x/xlib/color/structures.html */
	XColor fg, bg; 
	fg.red   = 0;     bg.red   = 65535; 
	fg.green = 65535; bg.green = 65535;
	fg.blue  = 0;     bg.blue  = 0;

	/* https://tronche.com/gui/x/xlib/appendix/b/ */
	/* https://tronche.com/gui/x/xlib/pixmap-and-cursor/XCreateFontCursor.html */
	Cursor mcursor  = XCreateFontCursor(display, XC_gobbler);

	/* https://tronche.com/gui/x/xlib/pixmap-and-cursor/XRecolorCursor.html */
	XRecolorCursor(display, mcursor, &fg, &bg);

	working = 1;

	//if (!mouse_setup_signals()) {
	//	fprintf(stderr, "hhpc: could not register signals. ");
	//	fprintf(stderr, "program will not exit cleanly\n");
	//	fflush(stderr);
	//}

	if (working && mouse_grab_pointer(display, win, mcursor, mask)) {
		/* we grab in sync mode, which stops pointer events from processing,
		 * so we explicitly have to re-allow it with XAllowEvents. The old
		 * method was to just grab in async mode so we wouldn't need this,
		 * but that disables replaying the pointer events */
		XAllowEvents(display, SyncPointer, CurrentTime);

		/* syncing is necessary, otherwise the X11 FD will never receive an
		 * event (and thus will never be ready, strangely enough) */
		XSync(display, False);

		///* add the X11 fd to the fdset so we can poll/select on it */
		//FD_ZERO(&fds);
		//FD_SET(xfd, &fds);

		/* we poll on the X11 fd to see if an event has come in, select()
		 * is interruptible by signals, which allows ctrl+c to work. If we
		 * were to just use XNextEvent() (which blocks), ctrl+c would not
		 * work. */
		delay(0, 1250);
		//if (select(xfd + 1, &fds, NULL, NULL, NULL) > 0) {
			#if MOUSE_X11_DEGUB
				fprintf(stdout, "hhpc: event received, ungrabbing and sleeping\n");
				fflush(stdout);
			#endif

			///* event received, replay event, release mouse, drain, sleep */
			XAllowEvents(display, ReplayPointer, CurrentTime);
			XUngrabPointer(display, CurrentTime);

			/* drain events */
			while (XPending(display)) {
				XMaskEvent(display, mask, &event);
				#if MOUSE_X11_DEGUB
					fprintf(stdout, "hhpc: draining event\n");
					fflush(stdout);
				#endif
			}

			delay(0, 1250);
			mouse_signal_handler(0);
		//} else {
		//	if(working)
		//		perror("hhpc: error while select()'ing");
		//}
	}

	#if MOUSE_X11_DEGUB
		fprintf(stdout, MOUSE_X11_TAG "ungrabbing\n");
		fflush(stdout);
	#endif
	XUngrabPointer(display, CurrentTime);
	XFreeCursor(display, mcursor);
}
/* EOF */
