/* 
 * A Minimal Capture Program
 * This program opens an audio interface for capture, configures it for
 * stereo, 16 bit, 44.1kHz, interleaved conventional read/write
 * access. Then its reads a chunk of random data from it, and exits. It
 * isn't meant to be a real program.
 * From on Paul David's tutorial : http://equalarea.com/paul/alsa-audio.html
 * Fixes rate and buffer problems
 *
 * sudo apt-get install libasound2-dev
 * gcc -o alsa-record-example -lasound alsa-record-example.c && ./alsa-record-example hw:0
 */

#include "rec_alsa.h"

void
rec_alsa_create(rec_alsa_t* params)
{
	int err;

	#if REC_ALSA_DEGUB
		fprintf(stdout, REC_ALSA_TAG "creating rec cap alsa obj\n");
	#endif

	/* define sampling rate, buffer size and number of channels */
	params->rate          = REC_ALSA_SAMPLING_RATE;
	params->buffer_frames = REC_ALSA_BUFFER_FRAMES;
	params->channels      = REC_ALSA_CHANNELS;
	params->format        = REC_ALSA_FORMAT;

	/* define the device */
	params->dev = (char*)malloc(10*sizeof(char));
	params->dev = strcpy(params->dev, REC_ALSA_DEV);

	#if REC_ALSA_DEGUB
		fprintf(stdout, REC_ALSA_TAG "opening audio if (interface)\n");
	#endif
	err = snd_pcm_open(
				&params->capture_handle, params->dev, SND_PCM_STREAM_CAPTURE, 0);
	if(err < 0) {
		fprintf(stderr, REC_ALSA_TAG
				"can't open audio dev %s (%s)\n", params->dev, snd_strerror(err));
		exit(1);
	}

	#if REC_ALSA_DEGUB
		fprintf(stdout, REC_ALSA_TAG "trying to alloc hw params\n");
	#endif
	err = snd_pcm_hw_params_malloc(&params->hw_params);
	if(err < 0) {
		fprintf(stderr,
				"cannot allocate hw param struc (%s)\n", snd_strerror(err));
		exit(1);
	}

	#if REC_ALSA_DEGUB
		fprintf(stdout, REC_ALSA_TAG "initializing hw params\n");
	#endif
	err = snd_pcm_hw_params_any(params->capture_handle, params->hw_params);
	if(err < 0) {
		fprintf(stderr, REC_ALSA_TAG
				"cannot initialize hw param struct (%s)\n", snd_strerror(err));
		exit(1);
	}

	#if REC_ALSA_DEGUB
		fprintf(stdout, REC_ALSA_TAG "setting hw params access\n");
	#endif
	err = snd_pcm_hw_params_set_access(params->capture_handle,
					params->hw_params, SND_PCM_ACCESS_RW_INTERLEAVED);
	if(err < 0) {
		fprintf(stderr, REC_ALSA_TAG
				"cannot set access type(%s)\n", snd_strerror(err));
		exit(1);
	}

	#if REC_ALSA_DEGUB
		fprintf(stdout, REC_ALSA_TAG "setting hw params format\n");
	#endif
	err = snd_pcm_hw_params_set_format(
				params->capture_handle, params->hw_params, params->format);
	if(err < 0) {
		fprintf(stderr, REC_ALSA_TAG 
				"cannot set sample format(%s)\n", snd_strerror(err));
		exit(1);
	}

	#if REC_ALSA_DEGUB
		fprintf(stdout, REC_ALSA_TAG "setting hw params rate\n");
	#endif
	err = snd_pcm_hw_params_set_rate_near(
				params->capture_handle, params->hw_params, &params->rate, 0);
	if(err < 0) {
		fprintf(stderr, REC_ALSA_TAG
				"cannot set sample rate(%s)\n", snd_strerror(err));
		exit(1);
	}

	#if REC_ALSA_DEGUB
		fprintf(stdout, REC_ALSA_TAG "setting hw params channels\n");
	#endif
	err = snd_pcm_hw_params_set_channels(
				params->capture_handle, params->hw_params, params->channels);
	if(err < 0) {
		fprintf(stderr, REC_ALSA_TAG
				"cannot set channel count(%s)\n", snd_strerror(err));
		exit(1);
	}

	#if REC_ALSA_DEGUB
		fprintf(stdout, REC_ALSA_TAG "setting hw params\n");
	#endif
	err = snd_pcm_hw_params(params->capture_handle, params->hw_params);
	if(err < 0) {
		fprintf(stderr, REC_ALSA_TAG "cannot set parameters(%s)\n", snd_strerror(err));
		exit(1);
	}

	#if REC_ALSA_DEGUB
		fprintf(stdout, REC_ALSA_TAG "freeing hw params\n");
	#endif
	snd_pcm_hw_params_free(params->hw_params);

	#if REC_ALSA_DEGUB
		fprintf(stdout, REC_ALSA_TAG "preparing audio interface\n");
	#endif
	err = snd_pcm_prepare(params->capture_handle);
	if(err < 0) {
		fprintf(stderr, REC_ALSA_TAG 
				"cannot prepare audio if for use (%s)\n", snd_strerror(err));
		exit(1);
	}

	#if REC_ALSA_DEGUB
		fprintf(stdout, REC_ALSA_TAG "allocating buffer\n");
	#endif
	int bytes_per_sample = snd_pcm_format_width(params->format) / 8;
	params->buf_size = params->buffer_frames * bytes_per_sample * params->channels;
	params->buffer = malloc(params->buf_size);

} /* close create */

int
rec_alsa_get_event_prob(rec_alsa_t* params)
{
	int err, j;
	short sample;
	float p;

	err = snd_pcm_readi(
			params->capture_handle, params->buffer, params->buffer_frames);
	if(err != params->buffer_frames) {
		fprintf(stderr, 
				"read from audio if failed (%s)\n", snd_strerror(err));
		return -1;
	}

	p = 0.0;
	/* FIXME: check endianness */
	for(j=0; j<params->buf_size; j+=2) {
		sample = (((short)params->buffer[j+1])<<8) | (short)params->buffer[j];
		if(sample < -REC_ALSA_EVENT_THRESH || sample > REC_ALSA_EVENT_THRESH) {
			p += 1.0;
		}
	}

	return (int)(100*p/(params->buf_size/2));
} /* close get prob */

void
rec_alsa_destroy(rec_alsa_t *params)
{
	#if REC_ALSA_DEGUB
		fprintf(stdout, REC_ALSA_TAG "freeing buffer\n");
	#endif
	free(params->buffer);

	#if REC_ALSA_DEGUB
		fprintf(stdout, REC_ALSA_TAG "freeing dev\n");
	#endif
	free(params->dev);

	#if REC_ALSA_DEGUB
		fprintf(stdout, REC_ALSA_TAG "closing audio interface\n");
	#endif
	snd_pcm_close(params->capture_handle);
} /* close destroy */
/* EOF */
