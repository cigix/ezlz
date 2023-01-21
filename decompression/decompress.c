#include "decompress.h"

#include <unistd.h>

#include "lib/bytes.h"
#include "lib/io.h"
#include "state.h"

int learn_found(struct state *state, int value, int outputfd)
{
  struct dictionary_entry const *entry = dict_get(state->dict, value);
  if (0 < state->learning->size) {
    if (append_byte(state->learning, entry->bytes[0]) == -1)
      return -1;
    if (dict_add_entry(
          state->dict, state->learning->bytes, state->learning->size) == -1)
      return -1;
    /* Entry may have been reallocated. */
    entry = dict_get(state->dict, value);
  }
  write(outputfd, entry->bytes, entry->size);
  shift_bytes(state->learning, state->learning->size);
  return append_bytes(state->learning, entry->bytes, entry->size);
}

int learn_not_found(struct state *state, int outputfd)
{
  if (append_byte(state->learning, state->learning->bytes[0]) == -1)
    return -1;
  if (dict_add_entry(
        state->dict, state->learning->bytes, state->learning->size) == -1)
    return -1;
  write(outputfd, state->learning->bytes, state->learning->size);
  return 0;
}

int learn(struct state *state, int value, int outputfd)
{
  struct dictionary_entry const *entry = dict_get(state->dict, value);
  if (entry != NULL)
    return learn_found(state, value, outputfd);
  return learn_not_found(state, outputfd);
}

int decompress(int inputfd, int outputfd)
{
  struct state *state = init_state();
  if (!state)
    return -1;

  int value;
  while ((value = read_bits(state->inbits, inputfd)) >= 0)
  {
    if (learn(state, value, outputfd) == -1)
        return -1;
  }
  if (value == -2)
    return -1;

  free_state(state);
  return 0;
}
