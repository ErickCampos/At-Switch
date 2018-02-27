/* 
   A Minimal Capture Program
   This program opens an audio interface for capture, configures it for
   stereo, 16 bit, 44.1kHz, interleaved conventional read/write
   access. Then its reads a chunk of random data from it, and exits. It
   isn't meant to be a real program.
   From on Paul David's tutorial : http://equalarea.com/paul/alsa-audio.html
   Fixes rate and buffer problems

   sudo apt-get install libasound2-dev
   gcc -o alsa-record-example -lasound alsa-record-example.c && ./alsa-record-example hw:0
 */

#include "rec_alsa.h"

void
rec_alsa_create(rec_alsa_struct* params)
{
	int err;

	#if DEGUB_ALSA
		fprintf(stdout, "opening audio interface\n");
	#endif
	err = snd_pcm_open(&params->capture_handle, params->dev, SND_PCM_STREAM_CAPTURE, 0);
	if(err < 0) {
		fprintf(stderr, "cannot open audio device %s(%s)\n", argv[1], snd_strerror(err));
		exit(1);
	}

	#if DEGUB_ALSA
		fprintf(stdout, "trying to alloc hw params\n");
	#endif
	err = snd_pcm_hw_params_malloc(&params->hw_params);
	if(err < 0) {
		fprintf(stderr, "cannot allocate hardware parameter structure(%s)\n", snd_strerror(err));
		exit(1);
	}

	#if DEGUB_ALSA
		fprintf(stdout, "initializing hw params\n");
	#endif
	err = snd_pcm_hw_params_any(params->capture_handle, params->hw_params);
	if(err < 0) {
		fprintf(stderr, "cannot initialize hardware parameter structure(%s)\n",
				snd_strerror(err));
		exit(1);
	}

	#if DEGUB_ALSA
		fprintf(stdout, "setting hw params access\n");
	#endif
	err = snd_pcm_hw_params_set_access(params->capture_handle, params->hw_params, SND_PCM_ACCESS_RW_INTERLEAVED);
	if(err < 0) {
		fprintf(stderr, "cannot set access type(%s)\n", snd_strerror(err));
		exit(1);
	}

	#if DEGUB_ALSA
		fprintf(stdout, "setting hw params format\n");
	#endif
	err = snd_pcm_hw_params_set_format(params->capture_handle, params->hw_params, params->format);
	if(err < 0) {
		fprintf(stderr, "cannot set sample format(%s)\n", snd_strerror(err));
		exit(1);
	}

	#if DEGUB_ALSA
		fprintf(stdout, "setting hw params rate\n");
	#endif
	err = snd_pcm_hw_params_set_rate_near(params->capture_handle, params->hw_params, &params->rate, 0);
	if(err < 0) {
		fprintf(stderr, "cannot set sample rate(%s)\n", snd_strerror(err));
		exit(1);
	}

	#if DEGUB_ALSA
		fprintf(stdout, "setting hw params channels\n");
	#endif
	err = snd_pcm_hw_params_set_channels(params->capture_handle, params->hw_params, params->channels);
	if(err < 0) {
		fprintf(stderr, "cannot set channel count(%s)\n", snd_strerror(err));
		exit(1);
	}

	#if DEGUB_ALSA
		fprintf(stdout, "setting hw params\n");
	#endif
	err = snd_pcm_hw_params(params->capture_handle, params->hw_params);
	if(err < 0) {
		fprintf(stderr, "cannot set parameters(%s)\n", snd_strerror(err));
		exit(1);
	}

	#if DEGUB_ALSA
		fprintf(stdout, "freeing hw params\n");
	#endif
	snd_pcm_hw_params_free(params->hw_params);

	#if DEGUB_ALSA
		fprintf(stdout, "preparing audio interface\n");
	#endif
	err = snd_pcm_prepare(params->capture_handle);
	if(err < 0) {
		fprintf(stderr, "cannot prepare audio interface for use(%s)\n", snd_strerror(err));
		exit(1);
	}

	#if DEGUB_ALSA
		fprintf(stdout, "allocating buffer\n");
	#endif
	int bytes_per_sample = snd_pcm_format_width(params->format) / 8;
	params->buf_size = params->buffer_frames * bytes_per_sample * params->channels;
	params->buffer = malloc(params->buf_size);

	for(i=0; i<100; ++i) {
		err = snd_pcm_readi(params->capture_handle, params->buffer, params->buffer_frames);
		if(err != params->buffer_frames) {
			fprintf(stderr, "read from audio interface failed(%s)\n", snd_strerror(err));
			exit(1);
		} else {
			for(j=0; j<params->buf_size; j+=2) {
				params->sample = (((int)params->buffer[j+1]) << 8) | (int)params->buffer[j];
				printf("%d\n", params->sample);
			}
		}
	}
}

void
rec_alsa_destroy(rec_alsa_struct *params)
{
	#if DEGUB_ALSA
		fprintf(stdout, "freeing buffer\n");
	#endif
	free(params->buffer);

	#if DEGUB_ALSA
		fprintf(stdout, "closing audio interface\n");
	#endif
	snd_pcm_close(params->capture_handle);
}
