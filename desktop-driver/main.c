/* 
 * Minimal "driver" to make all sort of AT switches work on a desktop computer
 * via audio jack's P2 3.5mm connector as a simple 'mouse click'. No USB or
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
 * Compile: $ make
 * gcc -o jack-at-deskdriver mouse_x11.c rec_alsa.c main.c -lX11 -lasound 
 *
 */

#include <signal.h>
#include "mouse_x11.h"
#include "rec_alsa.h"

#define MAIN_TAG "[MAIN] "

static volatile int keep_running = 1;

void
sigint_handler(int dummy)
{
    keep_running = 0;
}

int
main(int argc, char *argv[])
{
	int x = 0;
	int y = 0;

	/* create alsa rec (capture from mic) structure */
	rec_alsa_t mic_params;
	rec_alsa_create(&mic_params);

	/* open X display */
	Display *disp = XOpenDisplay(NULL);
	if(disp == NULL) {
		fprintf(stderr, "Can't open display!\n");
		return EXIT_FAILURE;
	}

	signal(SIGINT, sigint_handler);

	fprintf(stdout, MAIN_TAG "to gravando\n");
	int count_block_event = 0;
	while(keep_running) {
		if(rec_alsa_get_event_prob(&mic_params) >= 25) {
			count_block_event++;
		} else {
			count_block_event = 0;
		}

		if(count_block_event > 5) {
			mouse_click(disp, Button1);
			count_block_event = 0;
		}
		usleep(10);
	}

	/* close X display and exit */
	XCloseDisplay(disp);

	/* destroy alsa rec (capture from mic) structure */
	rec_alsa_destroy(&mic_params);

	fprintf(stdout, MAIN_TAG "valeu\n");

	return EXIT_SUCCESS;
}
