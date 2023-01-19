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
