#pragma once

/* Compress the input stream into the output stream. Return -1 on error. */
int compress(int inputfd, int outputfd);
