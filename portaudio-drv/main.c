#include "rec_pa.h"
#include "mouse_x11.h"

int
main(void)
{
	PaStream*  stream;
	PaError    err; // = paNoError;
	paTestData data;
	int i;
	int prev_idx, cur_idx;

	if((err = Pa_Create(&stream, err, &data)) != paNoError) {
		return Pa_Destroy(err, &data, "create pa structures");
	}

	/* TODO apply main routine here */
	prev_idx = 0;
	while((err = Pa_IsStreamActive(stream)) == 1) {
		//printf("%d\n", data.recordedSamples[data.frameIndex+i]);
		//fflush(stdout);
		if((cur_idx = data.frameIndex) != prev_idx) {
			prev_idx = cur_idx;
		}
		Pa_Sleep(250); /* ms */
	}

	if(err < 0)
		return Pa_Destroy(err, &data, "check whether stream is active");

	err = Pa_CloseStream(stream);
	if(err != paNoError)
		return Pa_Destroy(err, &data, "close stream");

	return Pa_Destroy(err, &data, NULL);
}
