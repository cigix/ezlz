#include "state.h"

#include <stdlib.h>
#include <unistd.h>

struct state *init_state(void)
{
  struct state *state = malloc(sizeof(struct state));
  if (!state)
    return NULL;

  state->dict = init_dict();
  state->inbits = init_bits();
  state->learning = init_bytes();
  if (!state->dict || !state->inbits || !state->learning)
    return NULL;

  return state;
}

void free_state(struct state *state, int outputfd)
{
  write(outputfd, state->learning->bytes, state->learning->size);
  free_bytes(state->learning);
  free(state->inbits);
  free_dict(state->dict);
  free(state);
}
