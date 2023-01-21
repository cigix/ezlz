#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "decompress.h"

int main(int argc, char **argv)
{
  int inputfd = 0;
  int outputfd = 1;
  if (2 == argc)
    outputfd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
  if (3 == argc)
  {
    inputfd = open(argv[1], O_RDONLY);
    outputfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
  }

  if (inputfd < 0 || outputfd < 0 || decompress(inputfd, outputfd) < 0)
  {
    perror(argv[0]);
    return 1;
  }

  if (inputfd != 0)
    close(inputfd);
  if (outputfd != 1)
    close(outputfd);

  return 0;
}
