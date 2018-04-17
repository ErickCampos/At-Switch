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
	const PA_SAMPLE *rptr = (const PA_SAMPLE*)inputBuffer;
	PA_SAMPLE *wptr = &data->recordedSamples[data->frameIndex * PA_NUM_CHANNELS];
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
			#if PA_NUM_CHANNELS == 2
				*wptr++ = SAMPLE_SILENCE; /* right */
			#endif
		}
	} else {
		for(i=0; i<framesToCalc; i++) {
			*wptr++ = *rptr++;       /* left */
			#if PA_NUM_CHANNELS == 2 
				*wptr++ = *rptr++;  /* right */
			#endif
		}
	}
	data->frameIndex += framesToCalc;
	return finished;
}

int
Pa_Create(PaStream **stream, PaError err, paTestData *data)
{
	int i;
	int totalFrames;
	int numSamples;
	int numBytes;
	PaStreamParameters inParams, outParams;

	/* Record for a few seconds */
	data->maxFrameIndex = totalFrames = NUM_SECONDS * PA_SAMPLE_RATE;
	data->frameIndex = 0;
	numSamples = totalFrames * PA_NUM_CHANNELS;
	numBytes = numSamples * sizeof(PA_SAMPLE);

	/* From now on, recordedSamples is initialised */
	data->recordedSamples = (PA_SAMPLE *) malloc(numBytes);
	if(data->recordedSamples == NULL) 
		return Pa_Destroy(err, data, "allocate record array");

	return Pa_Init(stream, err, data);
}

int
Pa_Init(PaStream **stream, PaError err,  paTestData *data)
{
	int i;
	int totalFrames;
	int numSamples;
	PaStreamParameters inParams, outParams;

	/* Record for a few seconds */
	data->maxFrameIndex = totalFrames = NUM_SECONDS * PA_SAMPLE_RATE;
	data->frameIndex = 0;
	numSamples = totalFrames * PA_NUM_CHANNELS;

	for(i=0; i<numSamples; i++)
		data->recordedSamples[i] = 0;

	err = Pa_Initialize();
	if(err != paNoError)
		return Pa_Destroy(err, data, "initialize internal data structs");

	inParams.device = Pa_GetDefaultInputDevice(); /* default input dev */
	if (inParams.device == paNoDevice)
		return Pa_Destroy(err, data, "get default input device");

	inParams.channelCount = PA_NUM_CHANNELS;
	inParams.sampleFormat = PA_SAMPLE_TYPE;
	inParams.suggestedLatency = 
			Pa_GetDeviceInfo(inParams.device)->defaultLowInputLatency;
	inParams.hostApiSpecificStreamInfo = NULL;

	/* Record some audio -------------------------------------------- */
	err = Pa_OpenStream(
			stream,
			&inParams,
			NULL,                  /* &outParams, */
			PA_SAMPLE_RATE,
			PA_FRAMES_PER_BUFFER,
			paClipOff, /* we won't output OOR samples so don't bother clippin them */
			recordCallback,
			data);

	if(err != paNoError)
		return Pa_Destroy(err, data, "open stream");

	err = Pa_StartStream(*stream);
	if(err != paNoError)
		return Pa_Destroy(err, data, "start stream");

	return paNoError;
}

int
Pa_Destroy(PaError err, paTestData *data, const char *msg)
{
	Pa_Terminate();
	if(data->recordedSamples)       /* Sure it is NULL or valid */
		free(data->recordedSamples);
	if(err != paNoError) {
		fprintf(stderr, "An error occured while attempting to %s\n", msg);
		fprintf(stderr, "Error number: %d\n", err);
		fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
		fflush(stderr);
		return 1;          /* Always return 0 or 1, but no other return codes */
	}
	return 0;
}

/* EOF */
