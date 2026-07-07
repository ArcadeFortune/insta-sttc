#include <stdio.h>
#include <stdint.h>
#include "portaudio.h"

#define SAMPLE_RATE (24000)
#define BUFFER_SIZE (100)

typedef struct
{
  int16_t *inputBuf[BUFFER_SIZE];
  size_t samplesBuffered;
  size_t maxSamples;
  unsigned char isTalking;
} MicData;

audioCallback(const void *input,
              void *output,
              unsigned long frameCount,
              const PaStreamCallbackTimeInfo *timeInfo,
              PaStreamCallbackFlags statusFlags,
              MicData *userData)
{
  const float *samples = (const float *)input;

  if (samples)
  {
    printf("sample: %f\n", samples[0]);
    userData->inputBuf[userData->samplesBuffered++] = (int16_t)samples[0];

    if (userData->samplesBuffered >= BUFFER_SIZE - 1)
    {
      printf("Enough samples for buffer.\n");
      return paComplete;
    }
  }
  return paContinue;
};

int main()
{
  printf("Listening for microphone\n\n");
  int16_t inputBuf[BUFFER_SIZE] = {0};
  MicData data = {
      .inputBuf = &inputBuf,
      .samplesBuffered = 0,
      .isTalking = 0,
  };
  PaError err;
  PaStream *stream;
  err = Pa_Initialize();
  if (err)
    return printf("Error with the audio device: %s\n", Pa_GetErrorText(err));

  err = Pa_OpenDefaultStream(
      &stream,
      1, // input channels
      0, // output channels
      paFloat32,
      SAMPLE_RATE,
      256,
      audioCallback,
      &data);
  if (err)
    return printf("Unable to open audio stream: %s\n", Pa_GetErrorText(err));

  err = Pa_StartStream(stream);
  if (err)
    return printf("Unable to start audio stream: %s\n", Pa_GetErrorText(err));

  printf("Recording... Press Enter to stop.\n");
  Pa_Sleep(30000);
  err = Pa_StopStream(stream);
  if (err)
    return printf("Unable to stop audio stream: %s\n", Pa_GetErrorText(err));
  Pa_CloseStream(stream);

  err = Pa_Terminate();
  if (err)
    return printf("Error with terminating audio stream: %s\n", Pa_GetErrorText(err));
  printf("thank you for using this app.\n");
  return 0;
}
