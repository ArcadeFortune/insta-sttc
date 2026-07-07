#include <stdio.h>
#include <stdint.h>
// #include <stdatomic.h>
#include "portaudio.h"

#define SAMPLE_RATE (24000)
#define FRAMES_PER_BUFFER (2400)
#define BUFFER_SIZE (12000)

typedef struct
{
  int16_t inputBuf[BUFFER_SIZE];
  size_t writeIndex;
  size_t readIndex;
  size_t unreadAmount;
} MicData;
