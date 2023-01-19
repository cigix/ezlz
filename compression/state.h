#pragma once

#include "lib/bits.h"
#include "lib/bytes.h"
#include "lib/dict.h"

struct state
{
  struct dictionary *dict;

  struct bytes *inbytes;
  struct bytes *learning;
  struct bits *outbits;
};

/* Allocate a new struct state. Return NULL in case of error. */
struct state *init_state(void);

/* Flush the buffers to the output and free the struct bytes. */
void free_state(struct state *, int outputfd);
