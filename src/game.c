#include <stdlib.h>
#include <stdio.h>

#include "SDL2/SDL.h"

#include "screen/screen.h"

typedef struct {
    struct screen_t* screen;

} game_t;

game_t* game_new() {
    game_t* game = (game_t*)malloc(sizeof(game_t));
    game->screen = NULL;

    return game;
}

void game_ctor(game_t* game) {
    game->screen = screen_new();

    if (screen_ctor(game->screen, "caloteiro") != 0) {
        fprintf(stderr, "Failed to initialize screen. SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
}

void game_dtor(game_t* game) {

    screen_dtor(game->screen);
}
