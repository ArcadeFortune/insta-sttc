#include <stdatomic.h>

typedef struct {
  void* buf;
  size_t trueMaxElements;
  size_t maxElements;
  size_t elementSize;
  atomic_size_t head;
  atomic_size_t tail;
} RingBuffer;
