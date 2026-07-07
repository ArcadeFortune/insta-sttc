#include "main.h"

void storeSamples(MicData *micData, float *samples, unsigned long amount)
{
  size_t wrappedWriteIndex = (micData->writeIndex & (MIC_DATA_BUFFER_SIZE - 1));
  size_t samplesLeftInBuffer = MIC_DATA_BUFFER_SIZE - wrappedWriteIndex;
  micData->writeIndex += amount;
  micData->unreadAmount += amount;
  // if samples would overflow buf
  if (samplesLeftInBuffer < amount)
  {
    memcpy(micData->buf + wrappedWriteIndex, samples, samplesLeftInBuffer * sizeof(float));
    amount -= samplesLeftInBuffer;
    samples += samplesLeftInBuffer;
    wrappedWriteIndex = 0;
  }
  memcpy(micData->buf + wrappedWriteIndex, samples, amount * sizeof(float));
}

// buffer
// [][][][][][][][]
// ri          wi

// samples:
// [][][]
