#pragma once

#include <stddef.h>
#include <stdint.h>

struct bytes
{
  uint8_t *bytes;
  size_t size;
  size_t capacity;
};

/* Allocate a new struct bytes. Return NULL in case of error. */
struct bytes *init_bytes(void);

/* Free a struct bytes and its underlying buffers. */
void free_bytes(struct bytes *);

/* Append a single byte at the end of the bytes. May reallocate. Return -1 in
** case of error, 0 otherwise. */
int append_byte(struct bytes *, uint8_t);

/* Append multiple bytes at the end of the bytes. May reallocate. Return -1 in
** case of error, 0 otherwise. */
int append_bytes(struct bytes *, uint8_t const *, size_t);

/* Drop the first n bytes, reducing the size of the bytes. */
void shift_bytes(struct bytes *, size_t n);
