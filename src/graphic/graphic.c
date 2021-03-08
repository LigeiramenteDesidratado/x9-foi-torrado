#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL_image.h>

#include "../screen/screen.h"
#include "../stage/stage.h"

typedef struct {
  SDL_Renderer *renderer;

} graphic_t;

void __graphic_blit_rect_f(graphic_t *graphic, SDL_Texture *texture,
                           SDL_Rect *src, SDL_FRect *dest,
                           game_component_args *args);
void __graphic_blit_rect(graphic_t *graphic, SDL_Texture *texture,
                         SDL_Rect *src, SDL_Rect *dest,
                         game_component_args *args);

graphic_t *graphic_new(void) {

  graphic_t *graphic = (graphic_t *)malloc(sizeof(graphic_t));

  graphic->renderer = NULL;

  return graphic;
}

int graphic_ctor(graphic_t *graphic, struct screen_t *screen) {

  int flags = IMG_INIT_PNG;
  int rflags = IMG_Init(flags);
  if (flags != rflags) {
    return -1;
  }

  graphic->renderer =
      SDL_CreateRenderer(screen_get_window(screen), -1,
                         SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!graphic->renderer) {
    return -1;
  }

  return 0;
}

void graphic_dtor(graphic_t *graphic) {

  SDL_DestroyRenderer(graphic->renderer);
  graphic->renderer = NULL;

  IMG_Quit();
}

SDL_Renderer *graphic_get_renderer(graphic_t *graphic) {
  return graphic->renderer;
}

SDL_Texture *graphic_load_texture(graphic_t *graphic, const char *filename) {
  SDL_Texture *texture;
  SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                 "Loading %s", filename);

  texture = IMG_LoadTexture(graphic->renderer, filename);
  if (texture == NULL) {
    printf("Failed to load texture %s! SDL Error: %s\n", filename,
           SDL_GetError());
    exit(1);
  }

  return texture;
}

// The blit function simply draws the specified texture on screen
// at specified x and y coordinates
void __graphic_blit(graphic_t *graphic, SDL_Texture *texture, int x, int y,
                    game_component_args *args) {
  SDL_Rect dest;

  dest.x = x;
  dest.y = y;
  SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
  __graphic_blit_rect(graphic, texture, NULL, &dest, args);
}

void __graphic_blit_f(graphic_t *graphic, SDL_Texture *texture, float x,
                      float y, game_component_args *args) {
  SDL_FRect dest;
  int w, h;

  dest.x = x;
  dest.y = y;

  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  dest.w = w;
  dest.h = h;

  __graphic_blit_rect_f(graphic, texture, NULL, &dest, args);
}

void __graphic_blit_rect_f(graphic_t *graphic, SDL_Texture *texture,
                           SDL_Rect *src, SDL_FRect *dest,
                           game_component_args *args) {

  SDL_FRect camera = stage_get_camera_rect(args->stage);
  dest->x = dest->x - camera.x;
  dest->y = dest->y - camera.y;

  /* SDL_SetRenderDrawColor(graphic->renderer, 0x14, 0xf4, 0x14, 0x14); */
  /* SDL_RenderDrawRectF(graphic->renderer, dest); */

  SDL_RenderCopyF(graphic->renderer, texture, src, dest);
}

void __graphic_blit_rect(graphic_t *graphic, SDL_Texture *texture,
                         SDL_Rect *src, SDL_Rect *dest,
                         game_component_args *args) {

  SDL_FRect camera = stage_get_camera_rect(args->stage);
  SDL_FRect destf;

  destf.x = dest->x - camera.x;
  destf.y = dest->y - camera.y;
  destf.w = dest->w;
  destf.h = dest->h;

  /* SDL_SetRenderDrawColor(graphic->renderer, 0x14, 0xf4, 0x14, 0x14); */
  /* SDL_RenderDrawRect(graphic->renderer, dest); */

  SDL_RenderCopyF(graphic->renderer, texture, src, &destf);
}

void __graphic_draw_rect(graphic_t *graphic, SDL_Rect dest) {

  SDL_SetRenderDrawColor(graphic->renderer, 0x14, 0xf4, 0x14, 0x14);
  SDL_RenderDrawRect(graphic->renderer, &dest);
}

void __graphic_draw_rect_f(graphic_t *graphic, SDL_FRect dest) {

  SDL_SetRenderDrawColor(graphic->renderer, 0x14, 0xf4, 0x14, 0x14);
  SDL_RenderDrawRectF(graphic->renderer, &dest);
}

void graphic_blit_fill_rect(graphic_t *graphic, SDL_Color c, SDL_Rect *rect) {

  SDL_SetRenderDrawColor(graphic->renderer, c.r, c.g, c.b, c.a);
  SDL_RenderFillRect(graphic->renderer, rect);
}

void graphic_clear_scene(graphic_t *graphic) {

  SDL_SetRenderDrawColor(graphic->renderer, 0x12, 0x12, 0x12, 0xFF);
  SDL_RenderClear(graphic->renderer);
}

void graphic_present_scene(graphic_t *graphic) {
  SDL_RenderPresent(graphic->renderer);
}
