#include "decompress.h"

#include <unistd.h>

#include "lib/bytes.h"
#include "lib/io.h"
#include "state.h"

int learn(struct state *state, int outputfd)
{
  for (size_t size = 1; size <= state->learning->size; ++size)
  {
    int code = dict_find(state->dict, state->learning->bytes, size);
    if (code == -1)
    {
      /* The pattern was not found. Learn this pattern, output one byte. */
      if (dict_add_entry(state->dict, state->learning->bytes, size) == -1)
        return -1;
      write(outputfd, state->learning->bytes, 1);
      shift_bytes(state->learning, 1);
      /* Try again */
      return learn(state, outputfd);
    }
  }
  return 0;
}

int decompress(int inputfd, int outputfd)
{
  struct state *state = init_state();
  if (!state)
    return -1;

  int value;
  while ((value = read_bits(state->inbits, inputfd)) >= 0)
  {
    struct dictionary_entry const *entry = dict_get(state->dict, value);
    if (append_bytes(state->learning, entry->bytes, entry->size) == -1)
      return -1;
    if (learn(state, outputfd) == -1)
      return -1;
  }
  if (value == -2)
    return -1;

  free_state(state, outputfd);
  return 0;
}
