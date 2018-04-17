/*
 * 
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
#include <math.h>
#include "rec_pa.h"
#include "mouse_x11.h"

#define INIT_WINDOW_STEP 750
#define DEGUB 0

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
	PaError    err;
	paTestData data;

	long i;              /* a dumb iterator */
	int win_step;        /* step to walk over the window */
	int click_count = 0;
	long avg_power = 0;  /* average power of the signal */

	/* simulate a queue of size 3 */
	/*       0     1     2        */
	/*    .-----.-----.-----.     */
	/* ->       |     |       ->  */
	/*    '-----'-----'-----'     */
	/*      last       first      */
	/*       in         in        */
	unsigned long fifo[3]; 

	/* handling control c */
	signal(SIGINT, sigint_handler);

	/* create the portaudio "object" */
	if((err = Pa_Create(&stream, err, &data)) != paNoError) {
		return Pa_Destroy(err, &data, "create pa structures");
	}

	/* initialize queue with non valid frame index values */
	for(i=0; i<3; i++)
		fifo[i] = -1;

	/* update frame indexes on queue */
	i = 2; /* TODO sizeof(fifo)/sizeof(unsigned long)?  */
	while(keep_running && (err = Pa_IsStreamActive(stream)) == 1 && i > -1) {
		if(data.frameIndex != fifo[i])
			fifo[i--] = data.frameIndex;

		/* the stream needs to breath for some ms */
		Pa_Sleep(150);
	} /* close while */

	/* analyze a 500-samples window to estimate the average power of the signal */
	int lower_interval = 3*(fifo[2]+fifo[1])/4;
	for(i=lower_interval; i<lower_interval+500; i++)
		avg_power += pow(abs(data.recordedSamples[i]), 2);

	/* take the mean and add 20% of power to ensure reliability */
	avg_power /= 500*1.2; 

	/* apply main routine here */
	// TODO: https://github.com/EddieRingle/portaudio/blob/master/examples/paex_record_file.c
	// TODO: http://portaudio.com/docs/v19-doxydocs/paex__record__file_8c_source.html
	while(keep_running && (err = Pa_IsStreamActive(stream)) == 1) {

		/* wait for the proper time to en/dequeue */
		while(data.frameIndex == fifo[0])
			Pa_Sleep(500);

		/* update queue: enqueue D (at 0), dequeue A (from 2) */
		fifo[2] = fifo[1];
		fifo[1] = fifo[0];
		fifo[0] = data.frameIndex;

		if(click_count > 0) {
			click_count -= 2;
			continue;
		}

		/* looking at every 1k samples from the signal can save our precious time */
		win_step = INIT_WINDOW_STEP;
		click_count = 0;
		for(i=fifo[2]; i<fifo[1]; i+=win_step) {
			if(abs(data.recordedSamples[i]) > avg_power) {
				win_step /= 2;
				if(++click_count == 5) {
					fprintf(stdout, "CLICK!\n");
					fflush(stdout);
					break;
				}
			}
		}

		if(DEGUB) {
			for(i=fifo[2]; i<fifo[1]; i++) 
				fprintf(stdout, "%+04d\n", data.recordedSamples[i]);
			fflush(stdout);
		}

		/* gimme a break for some ms */
		Pa_Sleep(500);
	} /* close while */

	if(err < 0)
		return Pa_Destroy(err, &data, "check whether stream is active");

	if(!keep_running) {
		fprintf(stderr, "Aborted\n");
		fflush(stderr);
		err = Pa_AbortStream(stream);
		if(err != paNoError)
			return Pa_Destroy(err, &data, "abort stream");
	}

	err = Pa_CloseStream(stream);
	if(err != paNoError)
		return Pa_Destroy(err, &data, "close stream");

	return Pa_Destroy(err, &data, NULL);
}
