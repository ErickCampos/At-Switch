/*
 * $Id$
 *
 * This program uses the PortAudio Portable Audio Library.
 * For more information see: http://www.portaudio.com
 * Copyright (c) 1999-2000 Ross Bencina and Phil Burk
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * The text above constitutes the entire PortAudio license; however, 
 * the PortAudio community also makes the following non-binding requests:
 *
 * Any person wishing to distribute modifications to the Software is
 * requested to send the modifications to the original developer so that
 * they can be incorporated into the canonical version. It is also 
 * requested that these non-binding requests be included along with the 
 * license above.
 */

#include "rec_pa.h"

paError*
Pa_Create(PaStream *stream, paError *err, paTestData *data)
{
	PaStreamParameters  inputParameters, outputParameters;
	int                 i;
	int                 totalFrames;
	int                 numSamples;
	int                 numBytes;

	/* Record for a few seconds. */
	data.maxFrameIndex = totalFrames = NUM_SECONDS * SAMPLE_RATE;
	data.frameIndex = 0;
	numSamples = totalFrames * NUM_CHANNELS;
	numBytes = numSamples * sizeof(SAMPLE);

	/* From now on, recordedSamples is initialised. */
	data.recordedSamples = (SAMPLE *) malloc(numBytes);
	if(data.recordedSamples == NULL) {
		printf("Could not allocate record array.\n");
		return Pa_Destroy(&err, &data);
	}
	for(i=0; i<numSamples; i++)
		data.recordedSamples[i] = 0;

	err = Pa_Initialize();
	if(err != paNoError)
		return Pa_Destroy(&err, &data);

	inputParameters.device = Pa_GetDefaultInputDevice(); /* default input dev */
	if (inputParameters.device == paNoDevice) {
		fprintf(stderr,"Error: No default input device.\n");
		return Pa_Destroy(&err, &data);
	}

	inputParameters.channelCount = 1;
	inputParameters.sampleFormat = PA_SAMPLE_TYPE;
	inputParameters.suggestedLatency = 
			Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
	inputParameters.hostApiSpecificStreamInfo = NULL;

	/* Record some audio. -------------------------------------------- */
	err = Pa_OpenStream(
			&stream,
			&inputParameters,
			NULL,                  /* &outputParameters, */
			SAMPLE_RATE,
			FRAMES_PER_BUFFER,
			paClipOff, /* we won't output OOR samples so don't bother clippin them */
			recordCallback,
			&data);

	if(err != paNoError)
		return Pa_Destroy(&err, &data);

	err = Pa_StartStream(stream);
	if(err != paNoError)
		return Pa_Destroy(&err, &data);
}

paError
Pa_Destroy(paError *err, paTestData *data)
{
	Pa_Terminate();
	if(data->recordedSamples)       /* Sure it is NULL or valid. */
		free(data->recordedSamples);
	if(err != paNoError) {
		fprintf(stderr, "An error occured while using the portaudio stream\n");
		fprintf(stderr, "Error number: %d\n", err);
		fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
		err = 1;          /* Always return 0 or 1, but no other return codes. */
	}
	return 0;
}

/* This routine will be called by the PortAudio engine when audio is needed.
 * It may be called at interrupt level on some machines so don't do anything
 * that could mess up the system like calling malloc() or free().
 */
static int
recordCallback(
		const void *inputBuffer, void *outputBuffer,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags,
		void *userData)
{
	paTestData *data = (paTestData*)userData;
	const SAMPLE *rptr = (const SAMPLE*)inputBuffer;
	SAMPLE *wptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
	long framesToCalc;
	long i;
	int finished;
	unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;

	if(framesLeft < framesPerBuffer) {
		framesToCalc = framesLeft;
		finished = paComplete;
	} else {
		framesToCalc = framesPerBuffer;
		finished = paContinue;
	}

	if(inputBuffer == NULL) {
		for(i=0; i<framesToCalc; i++) {
			*wptr++ = SAMPLE_SILENCE;     /* left */
			if(NUM_CHANNELS == 2)
				*wptr++ = SAMPLE_SILENCE; /* right */
		}
	} else {
		for(i=0; i<framesToCalc; i++) {
			*wptr++ = *rptr++;       /* left */
			printf("%d\n", data->recordedSamples[data->frameIndex+i]);
			fflush(stdout);
			if(NUM_CHANNELS == 2)
				*wptr++ = *rptr++;  /* right */
		}
	}
	data->frameIndex += framesToCalc;
	return finished;
}
/* EOF */
