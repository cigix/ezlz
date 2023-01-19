#pragma once

#include "bits.h"

/* Write as many bytes as possible. */
void write_bits(struct bits *, int outputfd);

/* Write all remaining bits, with padding 0s. */
void flush_bits(struct bits *, int outputfd);
