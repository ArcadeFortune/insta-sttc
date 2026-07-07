#include "main.h"

int main()
{
  MicData data = {
      .writeIndex = 0,
      .readIndex = 0,
      .unreadAmount = 0,
  };

  PaStream *stream = NULL;
  startListen(&data, &stream);

  Pa_Sleep(2000);

  stopListen(stream);
  printf("bye.\n");
  return 0;
}
