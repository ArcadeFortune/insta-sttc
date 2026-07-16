#include "main.h"

PaStreamCallbackResult audioCallback(const void *input, void *output,
                                     unsigned long frameCount,
                                     const PaStreamCallbackTimeInfo *timeInfo,
                                     PaStreamCallbackFlags statusFlags,
                                     void *userData) {
  const int16_t *samples = (const int16_t *)input;
  MicData *data = (MicData *)userData;

  if (samples) {
    storeSamples(data, samples, frameCount);
  }
  return paContinue;
};

int startListen(MicData *micData, PaStream **stream) {
  printf("Listening for microphone\n\n");
  PaError err;
  err = Pa_Initialize();
  if (err)
    return printf("Error with the audio device: %s\n", Pa_GetErrorText(err));

  err = Pa_OpenDefaultStream(stream,
                             1, // input channels
                             0, // output channels
                             paInt16, SAMPLE_RATE, FRAMES_PER_BUFFER,
                             audioCallback, micData);
  if (err)
    return printf("Unable to open audio stream: %s\n", Pa_GetErrorText(err));

  err = Pa_StartStream(*stream);
  if (err)
    return printf("Unable to start audio stream: %s\n", Pa_GetErrorText(err));

  return printf("Recording..\n");
}

int stopListen(PaStream *stream) {
  PaError err;
  err = Pa_StopStream(stream);
  if (err)
    return printf("Unable to stop audio stream: %s\n", Pa_GetErrorText(err));
  Pa_CloseStream(stream);

  err = Pa_Terminate();
  if (err)
    return printf("Error with terminating audio stream: %s\n",
                  Pa_GetErrorText(err));

  return printf("Stream closed.\n");
}
