#include "common.h"
#include <bits/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Usage: ascii-renderer <file_path> <ascii|ansi>\n");
    exit(EXIT_FAILURE);
  }

  DrawMode mode;
  if (strncasecmp(argv[2], "ascii", 5) == 0) {
    mode = ASCII;
  } else if (strncasecmp(argv[2], "ansi", 4) == 0) {
    mode = ANSI;
  } else {
    printf("Usage: ascii-renderer <file_path> <ascii|ansi>\n");
    exit(EXIT_FAILURE);
  }

  image_draw(argv[1], mode);

  return 0;
}
