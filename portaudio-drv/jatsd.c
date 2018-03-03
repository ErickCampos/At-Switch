#include <signal.h>
#include "rec_pa.h"
#include "mouse_x11.h"

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
	PaError    err; // = paNoError;
	paTestData data;

	long i;
	unsigned long fifo[3];

	/* handling control c */
	signal(SIGINT, sigint_handler);

	if((err = Pa_Create(&stream, err, &data)) != paNoError) {
		return Pa_Destroy(err, &data, "create pa structures");
	}

	for(i=0; i<3; i++)
		fifo[i] = -1;

	i = 2; /* TODO sizeof(fifo)/sizeof(unsigned long)?  */
	while(keep_running && (err = Pa_IsStreamActive(stream)) == 1 && i > -1) {
		if(data.frameIndex != fifo[i])
			fifo[i--] = data.frameIndex;

		Pa_Sleep(150); /* ms */
	} /* close while */

	/* apply main routine here */
	while(keep_running && (err = Pa_IsStreamActive(stream)) == 1) {

		if(data.frameIndex != fifo[0]) {
			fifo[2] = fifo[1];
			fifo[1] = fifo[0];
			fifo[0] = data.frameIndex;
		}

		for(i=fifo[2]; i<fifo[1]; i++) {
			fprintf(stdout, "%+04d\n", data.recordedSamples[i]);
			fflush(stdout);
		}

		Pa_Sleep(500); /* ms */
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
