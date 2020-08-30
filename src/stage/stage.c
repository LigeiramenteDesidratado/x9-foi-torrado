#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "../entity/entity.h"
#include "../graphic/graphic.h"
#include "../background/background.h"
#include "../input/input.h"
#include "../screen/screen.h"
#include "../player/player.h"
#include "../graphic/effects/wave.h"
#include "../graphic/effects/fire.h"
#include "../graphic/effects/glow.h"
#include "../menu/menu.h"
#include "../text/text.h"

#define MAX_PARTICLES 8

SDL_Color colors[5] = {
    {254, 106, 213, 0},
    {199, 116, 232, 0},
    {173, 140, 254, 0},
    {135, 149, 232, 0},
    {148, 208, 254, 0}
};

typedef struct {
    struct background_t* bg;
    struct player_t* player;
    struct fire_t* fire;

    struct entity_t* particles[MAX_PARTICLES];
    struct wave_t* waves[MAX_PARTICLES];

    struct menu_t* menu;

} stage_t;


stage_t* stage_new(void) {
    stage_t* stage = (stage_t*)malloc(sizeof(stage_t));
    stage->bg = NULL;
    stage->player = NULL;
    stage->fire = NULL;
    stage->menu = NULL;

    return stage;
}

int stage_ctor(stage_t* stage, struct graphic_t* graphic, struct screen_t* screen) {

    stage->bg = background_new();
    if (background_ctor(stage->bg, graphic_load_texture(graphic, "gfx/sun.png")) != 0) {
        return -1;
    }

    stage->player = player_new();
    if (player_ctor(stage->player, graphic) != 0) {
        return -1;
    }


    stage->fire = fire_new();
    if (fire_ctor(stage->fire, graphic, 100, 200, 10, 200, UP, 5, 2, 0) != 0) {
        return -1;
    }

    stage->menu = menu_new();
    if (menu_ctor(stage->menu, graphic) != 0 ) {
        return -1;
    }

    int w = screen_get_window_default_w(screen);
    int h = screen_get_window_default_h(screen);
    for (int i = 0; i < MAX_PARTICLES; i++) {
        srand(time(NULL)+i);
        SDL_Texture* texture = create_glow_ball(graphic, rand() % 20+10, (colors[rand() % 5]), 3);
        stage->particles[i] = entity_new();
        if (entity_ctor(stage->particles[i], texture, (rand() % w + 1), (rand() % h + 1)) != 0) {
            return -1;
        }
    }

    int posw, posh;
    for (int i = 0; i < MAX_PARTICLES; i++) {
        srand(time(NULL)+i);
        int dir = (rand() % (RIGHT+1));
        stage->waves[i] = wave_new();

        switch(dir) {
            case UP:
                posw = w / 2;
                posh = h;
                break;
            case DOWN:
                posw = w / 2;
                posh = 0;
                break;
            case LEFT:
                posw = w;
                posh = h / 2;
                break;
            case RIGHT:
                posw = 0;
                posh = h / 2;
                break;
            default:
                SDL_SetError("Invalid wave particle direction: %d\n", dir);
                dir = UP;
                posw = w / 2;
                posh = h;
        }

        if (wave_ctor(
                stage->waves[i],
                graphic,
                &(colors[rand() % 5]),
                posw,
                posh,
                w,
                h,
                (rand() % 190 + 1),
                (rand() % 10 + 1),
                (rand() % 6 + 1),
                (rand() % 6 + 1),
                dir) != 0) { return -1; }
    }


    return 0;
}

void stage_dtor(stage_t* stage) {
    player_dtor(stage->player);
    free(stage->player);

    for (int i = 0; i < MAX_PARTICLES; i++) {
        wave_dtor(stage->waves[i]);
        free(stage->waves[i]);
    }

    for (int i = 0; i < MAX_PARTICLES; i++) {
        entity_dtor(stage->particles[i]);
        free(stage->particles[i]);
    }

    fire_dtor(stage->fire);
    free(stage->fire);

    menu_dtor(stage->menu);
    free(stage->menu);

    background_dtor(stage->bg);
    free(stage->bg);
}


void stage_draw(stage_t* stage, struct graphic_t* graphic, struct screen_t* screen, struct text_t* text) {

    SDL_Renderer* renderer = graphic_get_renderer(graphic);

    background_draw(stage->bg, renderer, screen);

    for (int i = 0; i < MAX_PARTICLES; i++ ) {
        entity_draw(stage->particles[i], graphic);
        wave_draw(stage->waves[i], graphic);
    }

    fire_draw(stage->fire, graphic);

    menu_draw(stage->menu, graphic, text);

    player_draw(stage->player, graphic);

}

void stage_do(stage_t* stage, struct graphic_t* graphic, struct input_t* input, struct screen_t* screen) {

    for (int i = 0; i < MAX_PARTICLES; i++) {
        wave_set_width(stage->waves[i], screen_get_window_w(screen));
        wave_set_height(stage->waves[i], screen_get_window_h(screen));
        wave_do(stage->waves[i]);
    }


    menu_do(stage->menu, input, screen);

    player_do(stage->player, input, screen);

    fire_move(stage->fire, player_get_x(stage->player), player_get_y(stage->player));
    fire_do(stage->fire);

}
