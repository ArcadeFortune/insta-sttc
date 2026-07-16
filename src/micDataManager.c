#include "main.h"
void storeSamples(MicData *micData, const int16_t *samples, size_t amount) {
  size_t wrappedWriteIndex = (micData->writeIndex & (MIC_DATA_BUFFER_SIZE - 1));
  size_t samplesLeftInBuffer = MIC_DATA_BUFFER_SIZE - wrappedWriteIndex;
  micData->writeIndex += amount;
  // todo: increast read index if write index is catching up
  if (samplesLeftInBuffer < amount) {
    memcpy(micData->buf + wrappedWriteIndex, samples,
           samplesLeftInBuffer * sizeof(int16_t));
    amount -= samplesLeftInBuffer;
    samples += samplesLeftInBuffer;
    wrappedWriteIndex = 0;
  }
  memcpy(micData->buf + wrappedWriteIndex, samples, amount * sizeof(int16_t));
}

size_t readSamples(MicData *micData) {
  size_t unreadAmount = micData->writeIndex - micData->readIndex;
  micData->readIndex += unreadAmount;
  return unreadAmount;
}
