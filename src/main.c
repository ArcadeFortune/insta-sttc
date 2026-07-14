#include "main.h"

int main()
{
  float *buf = malloc(MIC_DATA_BUFFER_SIZE * sizeof(float));
  int16_t *pcmBuf = malloc(MIC_DATA_BUFFER_SIZE * sizeof(int16_t));
  char *base64Buf = malloc(MIC_DATA_BUFFER_SIZE * sizeof(char) * 2 * 4 / 3);

  PaStream *stream = NULL;
  MicData micData = {
      .buf = buf,
      .pcmBuf = pcmBuf,
      .base64Buf = base64Buf,
      .writeIndex = 0,
      .readIndex = 0,
  };

  startListen(&micData, &stream);

  while (1)
  {
    processSample(&micData);
    Pa_Sleep(20);
  }

  free(buf);
  free(pcmBuf);
  free(base64Buf);
  stopListen(stream);
  printf("bye.\n");
  return 0;
}
