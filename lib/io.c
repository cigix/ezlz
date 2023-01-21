#include "io.h"

#include <limits.h>
#include <unistd.h>

void write_bits(struct bits *bits, int outputfd)
{
  while (CHAR_BIT <= bits->available)
  {
    write(outputfd, &bits->bits, 1);
    bits->bits >>= CHAR_BIT;
    bits->available -= CHAR_BIT;
  }
}

void flush_bits(struct bits *bits, int outputfd)
{
  size_t towrite = 0;
  while ((towrite * CHAR_BIT) < bits->available)
    towrite++;
  if (towrite != 0)
    write(outputfd, &bits->bits, towrite);
}

/* Return -1 if stream has ended, -2 in case of error, 0 otherwise. */
int read_2_windows(struct bits *bits, int inputfd)
{
  while (bits->available < 2 * bits->window)
  {
    uint8_t byte;
    int ret = read(inputfd, &byte, 1);
    if (ret <= 0)
      return ret - 1;
    bits->bits |= ((uint64_t)byte) << bits->available;
    bits->available += CHAR_BIT;
  }
  return 0;
}

int read_bits(struct bits *bits, int inputfd)
{
  if (read_2_windows(bits, inputfd) == -2)
    return -2;
  if (bits->available < bits->window)
    return -1;
  uint64_t mask = (1U << bits->window) - 1;
  int value = bits->bits & mask;
  bits->bits >>= bits->window;
  bits->available -= bits->window;
  if (value == ((uint64_t)ESCAPE))
  {
    int nextvalue = bits->bits & mask;
    bits->bits >>= bits->window;
    bits->available -= bits->window;
    if (nextvalue != ((uint64_t)ESCAPE))
    {
      /* Single escape: increase window size */
      bits->window++;
      /* Try again */
      return read_bits(bits, inputfd);
    }
    /* Double escape: one ESCAPE value */
  }
  return value;
}
