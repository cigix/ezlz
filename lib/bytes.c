#include "bytes.h"

#include <stdlib.h>
#include <string.h>

#define BYTES_INITIAL_CAPACITY 4

struct bytes *init_bytes(void)
{
  struct bytes *bytes = malloc(sizeof(struct bytes));
  if (!bytes)
    return NULL;

  bytes->capacity = BYTES_INITIAL_CAPACITY;
  bytes->bytes = malloc(bytes->capacity);
  if (!bytes->bytes)
    return NULL;
  bytes->size = 0;

  return bytes;
}

void free_bytes(struct bytes *bytes)
{
  free(bytes->bytes);
  free(bytes);
}

int append_byte(struct bytes *bytes, uint8_t byte)
{
  if (bytes->size == bytes->capacity)
  {
    bytes->capacity *= 2;
    bytes->bytes = realloc(bytes->bytes, bytes->capacity);
    if (!bytes->bytes)
      return -1;
  }

  bytes->bytes[bytes->size++] = byte;
  return 0;
}

int append_bytes(struct bytes *bytes, uint8_t const *toadd, size_t size)
{
  if (bytes->capacity < bytes->size + size)
  {
    while (bytes->capacity < bytes->size + size)
      bytes->capacity *= 2;
    bytes->bytes = realloc(bytes->bytes, bytes->capacity);
    if (!bytes->bytes)
      return -1;
  }

  memcpy(bytes->bytes + bytes->size, toadd, size);
  bytes->size += size;
  return 0;
}

void shift_bytes(struct bytes *bytes, size_t n)
{
  bytes->size -= n;
  memmove(bytes->bytes, bytes->bytes + n, bytes->size);
}
