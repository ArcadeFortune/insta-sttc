#include <stdlib.h>
#include <stdint.h>
#define ALIGNMENT (64)

typedef struct Array
{
  void *items;
  int head;
  int tail;
  size_t itemCount;
  size_t itemsSize;
  size_t arraySize;
} Array;

Array newArray(size_t size)
{
  size_t realSize = (size + ALIGNMENT - 1) & ~(ALIGNMENT - 1);
  void *items = malloc(realSize);
  Array array = {
      .items = items,
      .itemCount = 0,
      .itemsSize = 0,
      .arraySize = realSize,
      .head = 0,
      .tail = 0,
  };
  return array;
}

void deleteArray(Array *arr)
{
  free(arr->items);
}

// void append(Array *arr, int16_t buf)
// {
//   arr->items[arr->itemCount * arr->itemsSize] = buf;
//   arr
//   // Item *newItem = malloc(sizeof(Item));
//   // newItem->buffer = buf;
//   // newItem->next = NULL;

//   // if (arr.items == NULL)
//   // {
//   //   arr.items = newItem;
//   // }
//   // arr.last = newItem;
//   // arr.length++;
// }

// void bulkAppend(Array *arr, int16_t *buf)
// {
//   memcopy
// }

void *popQueue()
{
  // int nextTmp = q.next->
}
