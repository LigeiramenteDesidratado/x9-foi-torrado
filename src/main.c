#include <SDL2/SDL.h>

#include "game.h"

int main(int argc, char** argv) {
    struct game_t* game = game_new();

    game_ctor(game);
    SDL_Delay(3000);
    game_dtor(game);
}
