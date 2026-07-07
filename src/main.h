#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
// #include <stdatomic.h>
#include "portaudio.h"

#define SAMPLE_RATE (24000)
#define FRAMES_PER_BUFFER (2400)
#define MIC_DATA_BUFFER_SIZE (16384) // has to be power of 2

typedef struct
{
  float *buf;
  size_t writeIndex;
  size_t readIndex;
  size_t unreadAmount;
} MicData;
