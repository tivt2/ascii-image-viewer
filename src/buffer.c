#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void buf_resize(Buffer *buf, size_t capacity) {
  buf->data = realloc(buf->data, capacity);
  if (buf->data == NULL) {
    perror("buf_resize");
    exit(EXIT_FAILURE);
  }
  buf->capacity = capacity;
}

void buf_write(Buffer *buf, const char *data) {
  size_t data_len = strlen(data);
  if (buf->length + data_len + 1 >= buf->capacity) {
    size_t new_cap = buf->capacity * 2;
    if (new_cap < (buf->length + data_len + 1)) {
      new_cap = buf->length + data_len + 1;
    }
    buf_resize(buf, new_cap);
  }

  memcpy(buf->data + buf->length, data, data_len);
  buf->length += data_len;
  buf->data[buf->length] = '\0';
}

void buf_write_int(Buffer *buf, int num) {
  char num_str[64];
  sprintf(num_str, "%d", num);
  size_t data_len = strlen(num_str);
  if (buf->length + data_len + 1 > buf->capacity) {
    size_t new_cap = buf->capacity * 2;
    if (new_cap < (buf->length + data_len + 1)) {
      new_cap = buf->length + data_len + 1;
    }
    buf_resize(buf, new_cap);
  }

  memcpy(buf->data + buf->length, num_str, data_len);
  buf->length += data_len;
  buf->data[buf->length] = '\0';
}

void buf_print(Buffer *buf, FILE *stream) {
  fprintf(stream, "%s", buf->data);
  fflush(stream);
}

void buf_clear(Buffer *buf) { buf->length = 0; }
