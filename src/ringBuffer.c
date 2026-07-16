#include "../headers/ringBuffer.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

void writeToBuffer(RingBuffer *rBuf, const void *in, size_t amountElements) {
  size_t headI = rBuf->head % rBuf->maxElements;
  size_t tailI = rBuf->tail % rBuf->maxElements;
  size_t slotsBeforeEnd = rBuf->maxElements - headI;
  const size_t slotsAvailable = slotsBeforeEnd + tailI;
  const bool isPassingTail =
      slotsAvailable < amountElements && rBuf->head != rBuf->tail;
  const bool hasToSplit = slotsBeforeEnd < amountElements;
  if (isPassingTail) {
    amountElements = slotsAvailable;
  }
  if (hasToSplit) {
    memcpy(rBuf->buf + (headI * rBuf->elementSize), in,
           slotsBeforeEnd * rBuf->elementSize);
    rBuf->head += slotsBeforeEnd;
    headI = 0;
    amountElements -= slotsBeforeEnd;
  } else {
    slotsBeforeEnd = 0;
  }
  memcpy(rBuf->buf + (headI * rBuf->elementSize),
         in + slotsBeforeEnd * rBuf->elementSize,
         amountElements * rBuf->elementSize);
  rBuf->head += amountElements;
}

size_t readFromBuffer(RingBuffer *rBuf, void *out, size_t amountElements) {
  size_t tailI = rBuf->tail % rBuf->maxElements;
  const bool isPassingHead = rBuf->head - rBuf->tail < amountElements;
  size_t slotsBeforeEnd = rBuf->maxElements - tailI;
  const bool hasToSplit = slotsBeforeEnd < amountElements;
  if (isPassingHead) {
    amountElements = rBuf->head - rBuf->tail;
  }
  const size_t elementsRead = amountElements;
  if (hasToSplit) {
    memcpy(out, rBuf->buf + (tailI * rBuf->elementSize),
           slotsBeforeEnd * rBuf->elementSize);
    rBuf->tail += slotsBeforeEnd;
    tailI = 0;
    amountElements -= slotsBeforeEnd;
  } else {
    slotsBeforeEnd = 0;
  }

  memcpy(out + slotsBeforeEnd * rBuf->elementSize,
         rBuf->buf + (tailI * rBuf->elementSize),
         amountElements * rBuf->elementSize);
  rBuf->tail += amountElements;
  return elementsRead;
}

// buffer
// [0][0][0][0][0][0][0][0][0][0][0]
//  t
//  h

// writeToBuffer
// [x][x][x]

// buffer
// [x][x][x][0][0][0][0][0][0][0]
//  t        h

// writeToBuffer
// [x][x][x][x]

// buffer
// [x][x][x][x][x][x][x][0][0][0]
//  t                    h

// readFromBuffer
// 5

// buffer
// [r][r][r][r][r][x][x][0][0][0]
//                 t     h

// writeToBuffer
// [x][x][x][x]

// buffer
// [x][r][r][r][r][x][x][x][x][x]
//     h           t

// readFromBuffer
// 4

// buffer
// [x][r][r][r][r][r][r][r][r][x]
//     h                       t

// readFromBuffer
// 300

// buffer
// [r][r][r][r][r][r][r][r][r][r]
//     h
//     t

// writeToBuffer
// [x][x][x][x][x][x]

// buffer
// [r][x][x][x][x][x][x][r][r][r]
//     t                 h

// writeToBuffer
// [x][x][x][x][x][x]

// buffer
// [x][x][x][x][x][x][x][x][x][x]
//     t  h
