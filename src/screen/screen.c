#include "SDL2/SDL.h"
#include <string.h>

#include "../common/common.h"

#define GAME_W 800
#define GAME_H 600

typedef struct {
  unsigned int w;
  unsigned int h;
  char *title;
  SDL_Window *window;

} screen_t;

screen_t *screen_new(void) {
  screen_t *screen = (screen_t *)malloc(sizeof(screen_t));

  // TODO: Does it belong here?
  screen->window = NULL;
  screen->title = NULL;
  screen->w = 0;
  screen->h = 0;

  return screen;
}

int screen_ctor(screen_t *screen, const char *title) {

  // init video subsystem
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    return -1;
  }

  screen->title = (char *)malloc((strlen(title) + 1) * sizeof(char));
  strcpy(screen->title, title);

  if (screen->w == 0) {
    screen->w = GAME_W;
  }
  if (screen->h == 0) {
    screen->h = GAME_H;
  }

  screen->window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       screen->w, screen->h, SDL_WINDOW_SHOWN);

  if (!screen->window) {
    return -1;
  }

  return 0;
}

void screen_dtor(screen_t *screen) {

  SDL_DestroyWindow(screen->window);
  screen->window = NULL;

  free(screen->title);
}

unsigned int screen_get_window_w(screen_t *screen) { return screen->w; }

unsigned int screen_get_window_h(screen_t *screen) { return screen->h; }

unsigned int screen_get_window_default_w(UNUSED screen_t *screen) {
  return GAME_W;
}

unsigned int screen_get_window_default_h(UNUSED screen_t *screen) {
  return GAME_H;
}

SDL_Window *screen_get_window(screen_t *screen) { return screen->window; }
void screen_set_window_size(screen_t *screen, int w, int h) {
  screen->w = w;
  screen->h = h;
}
