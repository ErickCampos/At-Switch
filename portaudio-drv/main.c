int
main(void)
{
	PaStream*           stream;
	PaError             err = paNoError;
	paTestData          data;

	if(Pa_Create(&stream, &err, &data) != paNoError)
		return Pa_Destroy(&err, &data);

	/* TODO appply main routine here */
	while((err = Pa_IsStreamActive(stream)) == 1) {
		//printf("%d\n", data.recordedSamples[data.frameIndex+i]);
		//fflush(stdout);
		Pa_Sleep(1000); /* ms */
	}

	if(err < 0)
		return Pa_Destroy(&err, &data);

	err = Pa_CloseStream(stream);
	if(err != paNoError)
		return Pa_Destroy(&err, &data);

	return Pa_Destroy(&err, &data);
}
