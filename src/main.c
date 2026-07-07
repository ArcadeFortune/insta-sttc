#include "main.h"

int main()
{
  MicData data = {
      .writeIndex = 0,
      .readIndex = 0,
      .unreadAmount = 0,
  };
  PaStream *stream;
  startListen(&data);

  Pa_Sleep(10000);

  stopListen(stream);
  printf("bye.\n");
  return 0;
}
