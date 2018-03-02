#include <signal.h>
#include "rec_pa.h"
#include "mouse_x11.h"

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
	unsigned long remainder;

	/* handling control c */
	signal(SIGINT, sigint_handler);

	if((err = Pa_Create(&stream, err, &data)) != paNoError) {
		return Pa_Destroy(err, &data, "create pa structures");
	}

	remainder = data.maxFrameIndex - data.frameIndex;
	if(remainder < framesPerBuffer) {
		finished = paComplete;
	} else {
		remainder = framesPerBuffer;
	}

	/* TODO apply main routine here */
	while(keep_running && (err = Pa_IsStreamActive(stream)) == 1) {
		if(data.frameIndex > 0) {
		for(i=0; i<10; i++)
			printf("%d, ", data.recordedSamples[10]);
		printf("\n");
		}
		Pa_Sleep(250); /* ms */
	}

	printf("%d\n", data.recordedSamples[10]);

	if(err < 0)
		return Pa_Destroy(err, &data, "check whether stream is active");

	if(!keep_running) {
		fprintf(stdout, "Aborted\n");
		fflush(stdout);
		err = Pa_AbortStream(stream);
		if(err != paNoError)
			return Pa_Destroy(err, &data, "abort stream");
	}

	err = Pa_CloseStream(stream);
	if(err != paNoError)
		return Pa_Destroy(err, &data, "close stream");

	return Pa_Destroy(err, &data, NULL);
}
