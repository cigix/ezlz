#pragma once

#include "lib/dict.h"
#include "lib/bits.h"
#include "lib/bytes.h"

struct state 
{
  struct dictionary *dict;

  struct bits *inbits;
  struct bytes *learning;
};

/* Allocate a new struct state. Return NULL in case of error. */
struct state *init_state(void);

/* Free the struct state. */
void free_state(struct state *);
