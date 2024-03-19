#ifndef COMMON_H_
#define COMMON_H_

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define HIDE_CURSOR "\033[?25l"
#define SHOW_CURSOR "\033[?25h"
#define CLEAR_TERM "\033[2J"

#define BG_RGB_E "\033[0m"

typedef enum { ANSI, ASCII } DrawMode;

void image_draw(const char *file_path, DrawMode mode);

typedef struct Buffer Buffer;

struct Buffer {
  size_t length;
  size_t capacity;
  char *data;
};

void buf_write(Buffer *, const char *);
void buf_write_int(Buffer *, int);
void buf_print(Buffer *, FILE *);
void buf_clear(Buffer *);

void bg_color(char *, uint8_t, uint8_t, uint8_t);

#endif // !COMMON_H_
