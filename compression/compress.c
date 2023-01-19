#include "compress.h"

#include <unistd.h>

#include "state.h"
#include "lib/io.h"

void match_inbytes(struct state *state)
{
  int code =
    dict_find(state->dict, state->inbytes->bytes, state->inbytes->size);
  if (code == -1)
  {
    /* The inbytes were not found. 1 byte ago they would, so output that. */
    append_bits(state->outbits, dict_find(
          state->dict, state->inbytes->bytes, state->inbytes->size - 1));
    shift_bytes(state->inbytes, state->inbytes->size - 1);
  }
  /* If the inbytes were found, skip until we get one more byte. */
}

/* Return -1 in case of error, 0 otherwise. */
int learn(struct state *state)
{
  int code =
    dict_find(state->dict, state->learning->bytes, state->learning->size);
  if (code == -1)
  {
    /* The pattern was not found. Learn this pattern, shift by one byte. */
    if (dict_add_entry(state->dict, state->learning) < 0)
      return -1;
    shift_bytes(state->learning, 1);
  }
  /* If the pattern is found, skip until we get one more byte. */
  return 0;
}

int compress(int inputfd, int outputfd)
{
  struct state *state = init_state();
  if (!state)
    return -1;

  uint8_t byte;
  int ret;
  while ((ret = read(inputfd, &byte, 1)) != 0)
  {
    if (ret < 0)
      return ret;

    if (append_byte(state->inbytes, byte) < 0
        || append_byte(state->learning, byte) < 0)
      return -1;
    match_inbytes(state);
    if (learn(state) < 0)
      return -1;
    write_bits(state->outbits, outputfd);
  }

  free_state(state, outputfd);
  return 0;
}
