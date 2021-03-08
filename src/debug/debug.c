#include "../common/common.h"
#include "../graphic/graphic.h"
#include "../screen/screen.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  float fps;
  bool_t show_tl_panel;
  bool_t show_b_panel;

  // Top Left panel
  SDL_Rect tl_panel;
  // Bottom panel
  SDL_Rect b_panel;

} debug_t;

debug_t *debug_new(void) {
  debug_t *debug = (debug_t *)malloc(sizeof(debug_t));
  debug->show_b_panel = 0;
  debug->show_tl_panel = 0;

  return debug;
}

void debug_ctor(debug_t *debug, struct screen_t *screen) {
  int h = screen_get_window_h(screen);
  debug->b_panel.x = 10;
  debug->b_panel.y = (h / 3) + (h / 3) + 10;
  debug->b_panel.h = (h / 3) - 20;
  debug->b_panel.w = screen_get_window_w(screen) - 10 - 10;
}

void debug_dtor(UNUSED debug_t *debug) {
  // Do nothing
}

void debug_toggle_tl_panel(debug_t *debug) {
  debug->show_tl_panel = !debug->show_tl_panel;
}

void debug_toggle_b_panel(debug_t *debug) {
  debug->show_b_panel = !debug->show_b_panel;
}

void debug_blit_b_panel(debug_t *debug, game_component_args *args) {

  int h = screen_get_window_h(args->screen);
  debug->b_panel.x = 10;
  debug->b_panel.y = (h / 3) + (h / 3) + 10;
  debug->b_panel.h = (h / 3) - 20;
  debug->b_panel.w = screen_get_window_w(args->screen) - 10 - 10;

  if (!debug->show_b_panel) {
    return;
  }
  SDL_Renderer *renderer = graphic_get_renderer(args->graphic);

  SDL_SetRenderDrawColor(renderer, 0x14, 0xf4, 0x14, 0x14);
  SDL_RenderDrawRect(renderer, &debug->b_panel);
}

SDL_Rect debug_get_b_rect(debug_t *debug) { return debug->b_panel; }
