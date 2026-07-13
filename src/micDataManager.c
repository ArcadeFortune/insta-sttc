#include "main.h"

void storeSamples(MicData *micData, const float *samples, size_t amount)
{
  size_t wrappedWriteIndex = (micData->writeIndex & (MIC_DATA_BUFFER_SIZE - 1));
  size_t samplesLeftInBuffer = MIC_DATA_BUFFER_SIZE - wrappedWriteIndex;
  micData->writeIndex += amount;
  // todo: increast read index if write index is catching up
  if (samplesLeftInBuffer < amount)
  {
    memcpy(micData->buf + wrappedWriteIndex, samples, samplesLeftInBuffer * sizeof(float));
    amount -= samplesLeftInBuffer;
    samples += samplesLeftInBuffer;
    wrappedWriteIndex = 0;
  }
  memcpy(micData->buf + wrappedWriteIndex, samples, amount * sizeof(float));
}

size_t readSamples(MicData *micData)
{
  size_t unreadAmount = micData->writeIndex - micData->readIndex;
  micData->readIndex += unreadAmount;
  return unreadAmount;
}

// buffer
// [x][x][x][x][x][x][0][0]
//  r                 w

// samples:
// [x][x][x]
