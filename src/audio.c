#include "main.h"

PaStreamCallbackResult audioCallback(const void *input, void *output,
                                     unsigned long frameCount,
                                     const PaStreamCallbackTimeInfo *timeInfo,
                                     PaStreamCallbackFlags statusFlags,
                                     void *userData) {
  const float *samples = (const float *)input;
  MicData *data = (MicData *)userData;

  if (samples) {
    storeSamples(data, samples, frameCount);

    // for (unsigned int i = 0; i < frameCount; i++)
    // {
    //   int16_t sample;
    //   if (samples[i] >= 1.0f)
    //     sample = 32767;
    //   else if (samples[i] <= -1.0f)
    //     sample = -32768;
    //   else
    //     sample = (int16_t)(samples[i] * 32767.0f);
    //   // data->inputBuf[data->writeIndex] = sample;
    //   // if have to wrap, wrap

    //   data->writeIndex = (data->writeIndex + 1) % MIC_DATA_BUFFER_SIZE;

    //   // todo: if data->cancel then return paAbort
    // }
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
                             paFloat32, SAMPLE_RATE, FRAMES_PER_BUFFER,
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
