#include "common.h"
#include <sys/ioctl.h>
#include <unistd.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const char *ascii_table[] = {"..", "--", "::", "==", "++", "**", "##", "@@"};
const int idx_period = (255 / 8) + 1;

int ascii_lum_idx(int lum) {
  int idx = lum / idx_period;
  return idx;
}

void ansi_bg_rgb_init(char *dst, unsigned char r, unsigned char g,
                      unsigned char b) {
  sprintf(dst, "\033[48;2;%d;%d;%dm", r, g, b);
}

void image_draw(const char *file_path, DrawMode mode) {
  int iw, ih, in;
  unsigned char *data = stbi_load(file_path, &iw, &ih, &in, 0);
  float aspect_ratio = (float)iw / ih;

  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  int win_w = w.ws_col;
  int win_h = w.ws_row - 2;
  float win_aspect = (float)win_w / win_h;

  if (aspect_ratio > win_aspect) {
    win_h = win_w * (float)ih / iw;
  } else {
    win_w = win_h * (float)iw / ih;
  }

  float w_aspect = (float)iw / win_w;
  float h_aspect = (float)ih / win_h;

  Buffer buf = {0};
  for (int y = 0; y < win_h; y++) {
    for (int x = 0; x < win_w; x++) {
      int idx = (int)(y * h_aspect) * iw + (int)(x * w_aspect);
      unsigned char *color = &data[idx * in];

      unsigned char r = color[0];
      unsigned char g = color[1];
      unsigned char b = color[2];

      if (mode == ANSI) {
        char color_str[32];
        ansi_bg_rgb_init(color_str, r, g, b);
        buf_write(&buf, color_str);
        buf_write(&buf, "  ");
        buf_write(&buf, BG_RGB_E);
      } else {
        int luminosity = (r + g + b) / 3;
        if (luminosity == 0) {
          buf_write(&buf, "  ");
        } else {
          int idx = ascii_lum_idx(luminosity);
          buf_write(&buf, ascii_table[idx]);
        }
      }
    }
    buf_write(&buf, "\n");
  }

  buf_print(&buf, stdout);

  buf_clear(&buf);

  stbi_image_free(data);
}
