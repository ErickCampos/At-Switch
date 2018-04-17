#ifndef _REC_PA_
#define _REC_PA_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <portaudio.h>

#define PA_SAMPLE_RATE        16000
#define PA_FRAMES_PER_BUFFER  2048
#define NUM_SECONDS           10
#define PA_NUM_CHANNELS       1    /* mono=1, stereo=2 */

/* #define DITHER_FLAG    paDitherOff */
#define DITHER_FLAG       0

#if 0
	typedef float            PA_SAMPLE;
	#define PA_SAMPLE_TYPE   paFloat32
	#define SAMPLE_SILENCE   0.0f
	#define PRINTF_S_FORMAT  "%.8f"
#elif 1
	typedef short            PA_SAMPLE;
	#define PA_SAMPLE_TYPE   paInt16
	#define SAMPLE_SILENCE   0
	#define PRINTF_S_FORMAT  "%d"
#elif 0
	typedef char             PA_SAMPLE;
	#define PA_SAMPLE_TYPE   paInt8
	#define SAMPLE_SILENCE   0
	#define PRINTF_S_FORMAT  "%d"
#elif 0
	typedef unsigned char    PA_SAMPLE;
	#define PA_SAMPLE_TYPE   paUInt8
	#define SAMPLE_SILENCE   128
	#define PRINTF_S_FORMAT  "%d"
#endif
 
typedef struct {
	int        frameIndex;  /* Index into sample array. */
	int        maxFrameIndex;
	PA_SAMPLE *recordedSamples;
} paTestData;

int Pa_Create(PaStream **stream, PaError err, paTestData *data);
int Pa_Init(PaStream **stream, PaError err, paTestData *data);
int Pa_Destroy(PaError err, paTestData *data, const char *msg);
static int recordCallback(const void*, void*, unsigned long,
		const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags, void*);
#endif /* _REC_PA_ */
