#ifndef _REC_ALSA_
#define _REC_ALSA_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <alsa/asoundlib.h>

#define DEGUB_ALSA 0

typedef struct rec_params {
	char         *dev
	char         *buffer;
	short        sample;
	int          buf_size;
	int          buffer_frames; /* 128 */
	unsigned int rate;          /* 8000 */
	unsigned int channels;      /* 2 */

	snd_pcm_t           *capture_handle;
	snd_pcm_hw_params_t *hw_params;
	snd_pcm_format_t    format;          /* SND_PCM_FORMAT_S16_LE */
} rec_alsa_struct;

void rec_alsa_create(rec_alsa_struct* params);
void rec_alsa_destroy(rec_alsa_struct* params);

#endif /* _REC_ALSA_ */
