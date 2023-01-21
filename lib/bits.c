#include "bits.h"

#include <limits.h>
#include <stdlib.h>

struct bits *init_bits(void)
{
  struct bits *bits = malloc(sizeof(struct bits));
  if (!bits)
    return NULL;

  bits->bits = 0;
  bits->available = 0;
  bits->window = CHAR_BIT;

  return bits;
}

void append_bits(struct bits *bits, int value)
{
  while ((1 << bits->window) <= value)
  {
    /* Current window is not big enough, expand it. */
    bits->bits |= ((uint64_t)(uint8_t)ESCAPE) << bits->available;
    bits->available += bits->window;
    bits->bits |= ((uint64_t)(uint8_t)~ESCAPE) << bits->available;
    bits->available += bits->window;
    bits->window++;
  }
  if (value == ESCAPE)
  {
    /* Append 2 escapes. */
    bits->bits |= ((uint64_t)ESCAPE) << bits->available;
    bits->available += bits->window;
    bits->bits |= ((uint64_t)ESCAPE) << bits->available;
    bits->available += bits->window;
  }
  else
  {
    bits->bits |= ((uint64_t)value) << bits->available;
    bits->available += bits->window;
  }
}
