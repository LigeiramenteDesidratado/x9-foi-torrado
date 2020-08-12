#include "SDL2/SDL.h"
#include <string.h>

#define GAME_W 800
#define GAME_H 600

typedef struct {
    unsigned int w;
    unsigned int h;
    char* title;
    SDL_Window* window;
    SDL_Renderer* renderer;

} screen_t;

screen_t* screen_new() {
    screen_t* screen = (screen_t*)malloc(sizeof(screen_t));
    screen->renderer = NULL;
    screen->renderer = NULL;
    screen->w = 0;
    screen->h = 0;

    return screen;
}

int screen_ctor(screen_t* screen, const char* title) {

    // init video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return -1;
    }

    screen->title = (char*)malloc((strlen(title)+1) * sizeof(char));
    strcpy(screen->title, title);

    if (screen->w == 0) { screen->w = GAME_W; }
    if (screen->h == 0) { screen->h = GAME_H; }

    screen->window = SDL_CreateWindow(title,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            screen->w,
            screen->h,
            0
    );

    if (!screen->window) {
        return -1;
    }

    screen->renderer = SDL_CreateRenderer(screen->window,
            -1,
            SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC
    );

    if (!screen->renderer) {
        return -1;
    }

    return 0;
}

void screen_dtor(screen_t* screen) {
    SDL_DestroyRenderer(screen->renderer);
    screen->renderer = NULL;

    SDL_DestroyWindow(screen->window);
    screen->window = NULL;

    free(screen->title);
}
