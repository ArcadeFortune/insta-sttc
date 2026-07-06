#include <stdio.h>
#include "portaudio.h"

// int audioCallback(const void *input,
//                   void *output,
//                   unsigned long frameCount,
//                   const PaStreamCallbackTimeInfo *timeInfo,
//                   PaStreamCallbackFlags statusFlags,
//                   void *userData)
// {

//   const float *samples = (const float *)input;

//   if (samples)
//   {
//     printf("First sample: %f\n", samples[0]);
//   }

//   return paContinue;
// };

int main()
{
  printf("Listening for microphone");
  // PaStream *stream;

  // Pa_Initialize();

  // Pa_OpenDefaultStream(
  //     &stream,
  //     1, // input channels
  //     0, // output channels
  //     paFloat32,
  //     44100,
  //     256,
  //     audioCallback,
  //     NULL);

  // Pa_StartStream(stream);

  // printf("Recording... Press Enter to stop.\n");
  // getchar();

  // Pa_StopStream(stream);
  // Pa_CloseStream(stream);
  // Pa_Terminate();
  return 0;
}
