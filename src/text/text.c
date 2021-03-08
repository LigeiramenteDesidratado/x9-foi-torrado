#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <string.h>

#include "../common/common.h"
#include "../graphic/graphic.h"
#include "text_p.h"

#define MAX_LINE_LENGTH 1024

#define GLYPH_W 7
#define GLYPH_H 7

typedef struct {
  SDL_Texture *font_texture;
  char text_buffer[MAX_LINE_LENGTH];
  SDL_Rect src;
} text_t;

text_t *text_new(void) {
  text_t *text = (text_t *)malloc(sizeof(text_t));
  text->font_texture = NULL;
  return text;
}

int text_ctor(text_t *text, struct graphic_t *graphic) {

  text->font_texture = graphic_load_texture(graphic, "gfx/fonts.png");
  if (text->font_texture == NULL) {
    return -1;
  }

  return 0;
}

void text_dtor(text_t *text) {

  SDL_DestroyTexture(text->font_texture);
  text->font_texture = NULL;
}

void text_reset_buffer(text_t *text) {
  memset(&text->text_buffer, '\0', sizeof(text->text_buffer));
}

int text_get_max_line_length(void) { return MAX_LINE_LENGTH; }

void text_draw_line(text_t *text, game_component_args *args, text_line_t *line,
                    bool_t centered) {
  int i, len, c;
  SDL_Rect dest;

  len = strlen(line->line);

  if (centered) {
    line->rect.x += (line->rect.w) / 2 - ((len * (GLYPH_W + 10)) / 2);
  }

  text->src.w = GLYPH_W;
  text->src.h = GLYPH_H;
  text->src.y = 0;

  dest.w = text->src.w + 10;
  dest.h = text->src.h + 10;

  SDL_SetTextureColorMod(text->font_texture, line->color.r, line->color.g,
                         line->color.b);

  for (i = 0; i < len; i++) {
    c = line->line[i];

    if (c >= ' ' && c <= '~') {
      if (c == ' ') {
        line->rect.x += GLYPH_W + 10;
        continue;
      }

      text->src.x = (c - ' ') * GLYPH_W;
      dest.x = line->rect.x;
      dest.y = line->rect.y;
      graphic_blit_rect(args->graphic, text->font_texture, &text->src, &dest,
                        args);
      line->rect.x += GLYPH_W + 10;
    }
  }
}

void text_draw(text_t *text, game_component_args *args, int x, int w, int y,
               int r, int g, int b, char *format, ...) {
  int i, len, c, initx;
  SDL_Rect dest;
  va_list argsf;

  initx = x;

  memset(&text->text_buffer, '\0', sizeof(text->text_buffer));

  va_start(argsf, format);
  vsprintf(text->text_buffer, format, argsf);
  va_end(argsf);

  len = strlen(text->text_buffer);
  text->src.w = GLYPH_W;
  text->src.h = GLYPH_H;
  text->src.y = 0;
  dest.w = text->src.w + 10;
  dest.h = text->src.h + 10;
  SDL_SetTextureColorMod(text->font_texture, r, g, b);

  for (i = 0; i < len; i++) {
    c = text->text_buffer[i];
    if (c == '\n') {
      x = initx;
      y += GLYPH_H + 20;
      continue;
    }

    if (c >= ' ' && c <= '~') {
      if (c == ' ') {
        x += GLYPH_W + 10;
        continue;
      }

      text->src.x = (c - ' ') * GLYPH_W;
      dest.x = x;
      dest.y = y;
      graphic_blit_rect(args->graphic, text->font_texture, &text->src, &dest,
                        args);
      if (x + GLYPH_W + 10 >= w) {
        x = initx;
        y += GLYPH_H + 20;
      } else {
        x += GLYPH_W + 10;
      }
    }
  }
}
