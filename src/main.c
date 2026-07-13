#include "main.h"

int main()
{
  // float *buf = malloc(MIC_DATA_BUFFER_SIZE * sizeof(float));
  // int16_t *pcmBuf = malloc(MIC_DATA_BUFFER_SIZE * sizeof(int16_t) * 10);
  // char *base64Buf = malloc(MIC_DATA_BUFFER_SIZE * sizeof(char) * 10);
  float *buf = malloc(6);
  int16_t *pcmBuf = malloc(6);
  char *base64Buf = malloc(6 * 4 / 3);

  buf[0] = 1.0f;
  buf[1] = -1.0f;
  buf[2] = .5f;
  buf[3] = .15f;
  buf[4] = 0;
  buf[5] = 1.5f;

  MicData micData = {
      .buf = buf,
      .pcmBuf = pcmBuf,
      .base64Buf = base64Buf,
      .writeIndex = 6,
      .readIndex = 0,
  };
  processSample(&micData);
  return 0;
  // PaStream *stream = NULL;

  // startListen(&micData, &stream);

  // for (int i = 0; i < 100; i++)
  // {
  //   processSample(&micData);
  //   Pa_Sleep(10);
  // }
  // Pa_Sleep(20000);

  // free(buf);
  // free(base64Buf);
  // stopListen(stream);
  // printf("bye.\n");
  return 0;
}
