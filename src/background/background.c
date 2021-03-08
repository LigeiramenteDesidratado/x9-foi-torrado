#include <SDL2/SDL.h>

#include "../common/common.h"
#include "../graphic/graphic.h"
#include "../screen/screen.h"
#include "../texture/texture.h"

typedef struct {
  struct texture_t *bg;
  // background texture holder
  SDL_FPoint rect;

  SDL_Rect area;

} background_t;

background_t *background_new(void) {
  background_t *background = (background_t *)malloc(sizeof(background_t));
  background->bg = NULL;

  background->rect = (SDL_FPoint){0};
  background->area = (SDL_Rect){0};

  return background;
}

int background_ctor(background_t *background, const char *filename, int w,
                    int h, game_component_args *args) {

  background->bg = texture_new();
  texture_load(background->bg, filename, args);

  if (w >= 0 && h >= 0) {
    background->area.w = w;
    background->area.h = h;
  }

  return 0;
}

void background_dtor(background_t *background) {

  texture_dtor(background->bg);
  free(background->bg);
  background->bg = NULL;
}

void background_do(background_t *background, game_component_args *args) {

  background->rect.x = (screen_get_window_w(args->screen) / 2) -
                       (texture_get_w(background->bg) / 2);
  background->rect.y = (screen_get_window_h(args->screen) / 2) -
                       (texture_get_h(background->bg) / 2);
}

void background_set_texture_wh(background_t *background, int w, int h) {

  texture_set_w(background->bg, w);
  texture_set_h(background->bg, h);
}

SDL_Rect background_get_area(background_t *background) {

  return background->area;
}

void background_set_texture_color(background_t *background, SDL_Color c) {

  texture_set_color_mod(background->bg, c);
}

void background_draw(background_t *background, game_component_args *args) {

  texture_draw(background->bg, background->rect.x, background->rect.y, args);
}
