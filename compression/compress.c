#include "compress.h"

#include <unistd.h>

#include "lib/io.h"
#include "state.h"

/* Return -1 in case of error, 0 otherwise. */
int learn(struct state *state)
{
  for (size_t size = 2; size <= state->learning->size; ++size)
  {
    int code = dict_find(state->dict, state->learning->bytes, size);
    if (code == -1)
    {
      /* The pattern was not found. Learn this pattern, shift by one byte. */
      append_bits(state->outbits,
          dict_find(state->dict, state->learning->bytes, size - 1));
      if (dict_add_entry(state->dict, state->learning->bytes, size) == -1)
        return -1;

      shift_bytes(state->learning, size - 1);
      return 0;
    }
  }
  /* If all prefix patterns are found, skip until we get one more byte. */
  return 0;
}

int compress(int inputfd, int outputfd)
{
  struct state *state = init_state();
  if (!state)
    return -1;

  uint8_t byte;
  int ret;
  while ((ret = read(inputfd, &byte, 1)) > 0)
  {
    if (append_byte(state->learning, byte) < 0)
      return -1;
    if (learn(state) < 0)
      return -1;
    write_bits(state->outbits, outputfd);
  }
  if (ret < 0)
    return ret;

  free_state(state, outputfd);
  return 0;
}
