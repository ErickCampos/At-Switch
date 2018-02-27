/* Erick 
 * 
 *  
 *  
 *  
 *  
 */

#include "mouse_x11.h"
/include "rec_alsa.h"

int
main(int argc, char *argv[])
{
	int x = 0;
	int y = 0;

	// open X display
	Display *display = XOpenDisplay(NULL);
	if(display == NULL) {
		fprintf(stderr, "Can't open display!\n");
		return -1;
	}

	mouse_click(display, Button1);

	/* close X display and exit */
	XCloseDisplay(display);
	return 0;

	return EXIT_SUCCESS;
}
