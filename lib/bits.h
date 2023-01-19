#pragma once

#include <stddef.h>
#include <stdint.h>

struct bits
{
  uint64_t bits;
  size_t available;
  size_t window;
};

/* Allocate a new struct bits. Return NULL in case of error. */
struct bits *init_bits(void);

/* Append a value to the bits. May also append escape values. */
void append_bits(struct bits *, int);
