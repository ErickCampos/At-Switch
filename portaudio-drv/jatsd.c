/*
 * JATDS - Jack AT Switch Driver
 * A minimal "driver" to make all sort of AT switches work on a desktop computer
 * via audio jack's P2, 3.5mm connector as a simple 'mouse click'. No USB or
 * additional mouse device is needed, just the switch :)
 * 
 * Authors: Apr, 2018.
 * Cassio Batista - cassio.batista.13@gmail.com
 * Erick Campos - erick.c.modesto@gmail.com
 * Federal University of Pará (UFPA). Belém, Brazil.
 *
 */

#include <signal.h>
#include <pthread.h>
#include <math.h>
#include "rec_pa.h"
#include "mouse_x11.h"

#define INIT_WINDOW_STEP 1000
#define POWER_THRESH 1000       /* set 0 for dynamic estimation */

#define DPLOT 0
#define DEGUB 1

#define C_FG_R   "\x1b[31m" /* red */
#define C_RESET  "\x1b[0m"

static volatile int keep_running = 1;

void
sigint_handler(int dummy)
{
	keep_running = 0;
}

int
main(void)
{
	PaStream*  stream;
	paTestData data;
	PaError    err = paNoError;

	long i;              /* a dumb iterator */
	int win_step;        /* step to walk over the window */
	int win_count = 0;
	int click_count = 0;
	long avg_power = 0;  /* average power of the signal */
	pthread_t tid;

	/* simulate a queue of size 3 */
	/*       0     1     2        */
	/*    .-----.-----.-----.     */
	/* ->       |     |       ->  */
	/*    '-----'-----'-----'     */
	/*      last       first      */
	/*       in         in        */
	/* initialize queue with non valid frame index values */
	unsigned long fifo[3]; 
	for(i=0; i<3; i++)
		fifo[i] = -1;

	/* open X display */
	Display *disp = XOpenDisplay(NULL);
	if(disp == NULL) {
		fprintf(stderr, "Can't open display!\n");
		return EXIT_FAILURE;
	}

	Window rootwin = RootWindow(disp, DefaultScreen(disp));

	color_mouse_t disp_win;
	disp_win.d = disp;
	disp_win.w = rootwin;

	/* handling control c */
	signal(SIGINT, sigint_handler);

	/* create the portaudio "object" */
	if((err = Pa_Create(&stream, err, &data)) != paNoError) {
		return Pa_Destroy(err, &data, "create pa structures");
	}

	/* update frame indexes on queue */
	i = 2; /* TODO sizeof(fifo)/sizeof(unsigned long)?  */
	while(keep_running && (err = Pa_IsStreamActive(stream)) == 1 && i > -1) {
		if(data.frameIndex != fifo[i])
			fifo[i--] = data.frameIndex;

		/* the stream needs to breath for some ms */
		Pa_Sleep(150);
	} /* close while */

	#if POWER_THRESH > 0
		/* assign a constant value as average power */
		avg_power = POWER_THRESH;
	#else
		/* analyze a 500-samples window to dynamically estimate
		 * the average power of the signal */
		int lower_interval = 3*(fifo[2]+fifo[1])/4;
		for(i=lower_interval; i<lower_interval+500; i++)
			avg_power += pow(abs(data.recordedSamples[i]), 2);

		/* take the mean and double the power to ensure reliability */
		avg_power /= 500;
		avg_power *= 2;
	#endif

	#if DEGUB
		printf("power: %lu\n", avg_power);
	#endif

	/* main event loop */
	while(keep_running) {
		/* apply main routine here */
		/* TODO: search for pa ring buffer */
		while(keep_running && (err = Pa_IsStreamActive(stream)) == 1) {

			/* wait for the proper time to en/dequeue */
			while(data.frameIndex == fifo[0])
				Pa_Sleep(200);

			/* update queue: enqueue D (at 0), dequeue A (from 2) */
			fifo[2] = fifo[1];
			fifo[1] = fifo[0];
			fifo[0] = data.frameIndex;

			/* delay to skip the inverse signal */
			if(win_count-- > 0) {
				Pa_Sleep(500);
				continue;
			}

			/* looking at every 1k samples from the signal 
			 * instead of one by one can save our precious time */
			win_step = INIT_WINDOW_STEP;
			win_count = 0;
			for(i=fifo[2]; i<fifo[1]; i+=win_step) {
				if(abs(data.recordedSamples[i]) > avg_power) {
					#if DEGUB
						fprintf(stdout, ".");
						fflush(stdout);
					#endif
					win_step /= 2;
					if(++win_count == 5) {
						
						#if DEGUB
							fprintf(stdout, "CLICK!\n");
							fflush(stdout);
						#endif
						pthread_create(&tid, NULL, mouse_color_cursor, &disp_win);
						mouse_click(disp, Button1);
						click_count++;
						pthread_join(tid, NULL);
						break;
					}
				}
			}

			/* debug for plot */
			#if DPLOT
				for(i=fifo[2]; i<fifo[1]; i++)
					fprintf(stdout, "%+04d\n", data.recordedSamples[i]);
				fflush(stdout);
			#endif

			/* gimme a break for some ms */
			Pa_Sleep(250);
		} /* close while */

		/* init PortAudio stream */
		if((err = Pa_Init(&stream, err, &data)) != paNoError) {
			return Pa_Destroy(err, &data, "resetting pa structures");
		}
	}

	#if DEGUB
		fprintf(stdout, "clicks: %d\n", click_count);
		fflush(stdout);
	#endif

	if(err < 0)
		return Pa_Destroy(err, &data, "check whether stream is active");

	/* abort PortAudio stream as fast as possible */
	if(!keep_running) {
		fprintf(stderr, "Aborted\n");
		fflush(stderr);
		err = Pa_AbortStream(stream);
		if(err != paNoError)
			return Pa_Destroy(err, &data, "abort stream");
	}

	/* close PortAudio stream */
	err = Pa_CloseStream(stream);
	if(err != paNoError)
		return Pa_Destroy(err, &data, "close stream");

	/* close X display and exit */
	XCloseDisplay(disp);

	return Pa_Destroy(err, &data, NULL);
}
/* EOF */
