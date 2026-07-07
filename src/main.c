#include "main.h"

int main()
{
  float *buf = malloc(MIC_DATA_BUFFER_SIZE * sizeof(float));

  MicData micData = {
      .buf = buf,
      .writeIndex = 0,
      .readIndex = 0,
      .unreadAmount = 0,
  };
  PaStream *stream = NULL;

  startListen(&micData, &stream);

  Pa_Sleep(20000);

  stopListen(stream);
  printf("bye.\n");
  return 0;
}
