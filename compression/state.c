#include "state.h"

#include <stdlib.h>

#include "lib/io.h"

struct state *init_state(void)
{
  struct state *state = malloc(sizeof(struct state));
  if (!state)
    return NULL;

  state->dict = init_dict();
  state->inbytes = init_bytes();
  state->learning = init_bytes();
  state->outbits = init_bits();
  if (!state->dict || !state->inbytes || !state->learning || !state->outbits)
    return NULL;

  return state;
}

void flush_inbytes(struct state *state, int outputfd)
{
  while (0 < state->inbytes->size)
  {
    /* Try to find the biggest prefix in the dictionary. */
    for (size_t size = state->inbytes->size; 0 < size; size--)
    {
      int code = dict_find(state->dict, state->inbytes->bytes, size);
      if (code != -1)
      {
        append_bits(state->outbits, code);
        shift_bytes(state->inbytes, size);
        write_bits(state->outbits, outputfd);
        break;
      }
    }
  }
}

void free_state(struct state * state, int outputfd)
{
  flush_inbytes(state, outputfd);
  flush_bits(state->outbits, outputfd);
  free(state->outbits);
  free_bytes(state->learning);
  free_bytes(state->inbytes);
  free_dict(state->dict);
  free(state);
}
