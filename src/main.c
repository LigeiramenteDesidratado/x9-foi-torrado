#include <SDL2/SDL.h>

#include "common/common.h"
#include "game.h"

int main(UNUSED int argc, UNUSED char **argv) {
  struct game_t *game = game_new();

  game_ctor(game);
  /* game_component_args. */

  if (game_main_loop(game) != 0) {
    fprintf(stderr, "Failed to initialize main loop! SDL Error: %s\n",
            SDL_GetError());
  }

  game_dtor(game);

  free(game);
}
