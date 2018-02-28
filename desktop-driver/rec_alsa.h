/* 
 * Minimal "driver" to make all sort of AT switches work on a desktop computer
 * via audio jack's P2 3.5mm connector as a simple 'mouse click'. No USB or
 * additional mouse device is needed, just the switch :)
 *  
 * Authors: Feb, 2018. Federal University of Pará (UFPA). Belém, Brazil.
 * Cassio Batista - cassio.batista.13@gmail.com
 * Erick Campos - erick.c.modesto@gmail.com
 * 
 * Credits:
 * ALSA Capture Program: Paul David (http://equalarea.com/paul/alsa-audio.html)
 * Mouse with X11/Xlib: Enrico "Pioz" (https://gist.github.com/pioz/726474)
 *
 * Compile: $ make
 * gcc -o jack-at-deskdriver mouse_x11.c rec_alsa.c main.c -lX11 -lasound 
 *
 */

#ifndef _REC_ALSA_
#define _REC_ALSA_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <alsa/asoundlib.h>

#define REC_ALSA_TAG "[ALSA] "
#define REC_ALSA_DEGUB  1

#define REC_ALSA_SAMPLING_RATE   8000
#define REC_ALSA_BUFFER_FRAMES   128
#define REC_ALSA_CHANNELS        2
#define REC_ALSA_DEV             "hw:1"
#define REC_ALSA_FORMAT          SND_PCM_FORMAT_S16_LE
#define REC_ALSA_EVENT_THRESH    10000

typedef struct {
	char         *dev;          /* hw:1 */
	char         *buffer;       /* allocated on the fly */
	int          buf_size;      /* computed on the fly */
	int          buffer_frames; /* 128 */
	unsigned int rate;          /* 8000 */
	unsigned int channels;      /* 2 */

	snd_pcm_t           *capture_handle;
	snd_pcm_hw_params_t *hw_params;
	snd_pcm_format_t    format;          /* SND_PCM_FORMAT_S16_LE */
} rec_alsa_t;

void rec_alsa_create(rec_alsa_t* params);
void rec_alsa_destroy(rec_alsa_t* params);
float get_event_prob(rec_alsa_t* params);

#endif /* _REC_ALSA_ */
