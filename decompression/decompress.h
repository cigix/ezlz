#pragma once

/* Decompress the input stream into the output stream. Return -1 on error. */
int decompress(int inputfd, int outputfd);
