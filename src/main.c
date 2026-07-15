#include "main.h"

atomic_bool isRecording = false;

int main() {
  PaStream *stream = NULL;

  float *buf = malloc(MIC_DATA_BUFFER_SIZE * sizeof(float));
  int16_t *pcmBuf = malloc(MIC_DATA_BUFFER_SIZE * sizeof(int16_t));
  char *base64Buf = malloc(MIC_DATA_BUFFER_SIZE * sizeof(char) * 2 * 4 / 3);
  MicData micData = {
      .buf = buf,
      .pcmBuf = pcmBuf,
      .base64Buf = base64Buf,
      .writeIndex = 0,
      .readIndex = 0,
  };

  CreateThread(NULL, 0, keyboardThread, NULL, 0, NULL);

  // startListen(&micData, &stream);
  // struct lws_context *context = startWebsocketClient();

  while (1) {
    // processSample(&micData);
    // lws_service(context, 0);
    printf("isRecording: %d\n", atomic_load(&isRecording));
    Pa_Sleep(20 * 10);
  }

  free(buf);
  free(pcmBuf);
  free(base64Buf);
  // stopListen(stream);
  // stopWebsocketClient(context);
  printf("bye.\n");
  return 0;
}
