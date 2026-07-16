#include "main.h"

atomic_bool isRecording = false;
atomic_int websocketState = NOT_CONNECTED;

int main() {
  bool previousIsRecording = isRecording;
  PaStream *stream = NULL;
  struct lws_context *context = startWebsocketClient();
  printf("connecting to openai\n");
  connectWebsocketClient(context);

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

  while (true) {
    // if (websocketState == UNUSABLE) {
    //   printf("Websocket connection is unusable.\n");
    //   break;
    // }
    // lws_service(context, 0);
    if (isRecording && !previousIsRecording) {
      printf("starting to listen the mic\n");
      startListen(&micData, &stream);
      previousIsRecording = true;
    }
    if (!isRecording && previousIsRecording) {
      previousIsRecording = false;
      printf("stopping the microphone\n");
      stopListen(stream);
    }
    if (isRecording) {
      processSample(&micData);
      //todo: second thread to continusely read buffer and send it to websocket.
      if (websocketState == CONNECTED) {
        sendToWebsocket(micData.base64Buf);
      }
    }

    Pa_Sleep(20 * 10);
  }

  printf("stopping the websocket client\n");
  // stopWebsocketClient(context);
  free(buf);
  free(pcmBuf);
  free(base64Buf);
  printf("bye.\n");
  return 0;
}
