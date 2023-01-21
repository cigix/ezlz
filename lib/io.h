#pragma once

#include "bits.h"

/* Write as many bytes as possible. */
void write_bits(struct bits *, int outputfd);

/* Write all remaining bits, with padding 0s. */
void flush_bits(struct bits *, int outputfd);

/* Read next value from input stream. Return -1 if stream has ended, -2 in case
** of error, the value otherwise. */
int read_bits(struct bits *, int inputfd);
