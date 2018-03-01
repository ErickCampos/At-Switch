#ifndef _REC_PA_
#define _REC_PA_

#include <stdio.h>
#include <stdlib.h>
#include <portaudio.h>

#define SAMPLE_RATE       16000
#define FRAMES_PER_BUFFER 4096
#define NUM_SECONDS       4
#define NUM_CHANNELS      1

/* #define DITHER_FLAG    paDitherOff */
#define DITHER_FLAG       0

/* #define WRITE_TO_FILE     0 */

/* Select sample format. */
/*
 * typedef float SAMPLE;
 * #define PA_SAMPLE_TYPE  paFloat32
 * #define SAMPLE_SILENCE  0.0f
 * #define PRINTF_S_FORMAT "%.8f"
 */

typedef short SAMPLE;
#define PA_SAMPLE_TYPE  paInt16
#define SAMPLE_SILENCE  0
#define PRINTF_S_FORMAT "%d"

/*
 * typedef char SAMPLE;
 * #define PA_SAMPLE_TYPE  paInt8
 * #define SAMPLE_SILENCE  0
 * #define PRINTF_S_FORMAT "%d"
 * 
 * typedef unsigned char SAMPLE;
 * #define PA_SAMPLE_TYPE  paUInt8
 * #define SAMPLE_SILENCE  128
 * #define PRINTF_S_FORMAT "%d"
 */

typedef struct {
	int          frameIndex;  /* Index into sample array. */
	int          maxFrameIndex;
	SAMPLE      *recordedSamples;
} paTestData;

#endif /* _REC_PA_ */
