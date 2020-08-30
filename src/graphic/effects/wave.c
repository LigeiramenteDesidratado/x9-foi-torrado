#include <stdlib.h>
#include <SDL2/SDL.h>

#include "../graphic.h"
#include "../../entity/entity.h"
#include "glow.h"
#include "helpers.h"

typedef struct {
    struct entity_t* particle;
    int phase;
    int amp;
    int freq;
    int spd;

    int start_x;
    int start_y;

    direction dir;

    int height;
    int width;
    int angle;

} wave_t;

wave_t* wave_new(void) {
    wave_t* wave = (wave_t*)malloc(sizeof(wave_t));
    wave->particle = NULL;

    return wave;
}

int wave_ctor(wave_t* wave,
        struct graphic_t* graphic,
        SDL_Color* color,
        int mid_x,
        int mid_y,
        int width,
        int height,
        int phase,
        int amp,
        int freq,
        int spd,
        direction dir) {

    SDL_Texture* texture = create_glow_ball(graphic, rand() % 20+10, *color, 3);
    if (texture == NULL) {
        return -1;
    }

    wave->particle = entity_new();
    if (entity_ctor(wave->particle, texture, mid_x, mid_y) != 0) {
        return -1;
    }

    wave->height  = height;
    wave->width   = width;
    wave->phase   = phase;
    wave->amp     = amp;
    wave->freq    = freq;
    wave->spd     = spd;
    wave->dir     = dir;
    wave->start_x = mid_x;
    wave->start_y = mid_y;
    wave->angle   = 0;

    return 0;
}

void wave_dtor(wave_t* wave) {

    entity_dtor(wave->particle);
    free(wave->particle);
}

SDL_Point wave_get_start(wave_t* wave) {

    return (SDL_Point){wave->start_x, wave->start_y};
}

void wave_move_start(wave_t* wave, int x, int y) {
    int diff_x = x - wave->start_x;
    int diff_y = y - wave->start_y;

    /* SDL_Point middle = particle_get_middle(wave->particle); */
    float ex = entity_get_x(wave->particle);
    float ey = entity_get_y(wave->particle);

    entity_set_dx(wave->particle, ex + diff_x);
    entity_set_dy(wave->particle, ey + diff_y);

    wave->start_x = x;
    wave->start_y = y;
}

void wave_do(wave_t* wave) {

    entity_set_dx(wave->particle, 0);
    entity_set_dy(wave->particle, 0);

    SDL_Point middle = entity_get_middle(wave->particle);

    switch (wave->dir) {
        case UP:
            if (middle.y <= 0) {
                wave->start_y = wave->height;
                wave->start_x = rand() % wave->width+1;
                wave->angle = 0;
                entity_set_x(wave->particle, wave->start_x);
                entity_set_y(wave->particle, wave->start_y);

            } else {
                int x = SDL_sin(helper_deg2rad(wave->angle + wave->phase)) * wave->amp;
                entity_set_dx(wave->particle, x);
                entity_set_dy(wave->particle, -wave->spd);
            }
            break;

        case DOWN:
            if (middle.y >= wave->height) {
                wave->start_y = 1;
                wave->start_x = rand() % wave->width+1;
                wave->angle = 0;
                entity_set_x(wave->particle, wave->start_x);
                entity_set_y(wave->particle, wave->start_y);

            } else {
                int x = SDL_sin(helper_deg2rad(wave->angle + wave->phase)) * wave->amp;
                entity_set_dx(wave->particle, x);
                entity_set_dy(wave->particle, wave->spd);

            }
            break;

        case LEFT:
            if (middle.x <= 0) {
                wave->start_y = rand() % wave->height+1;
                wave->start_x = wave->width;
                wave->angle = 0;
                entity_set_x(wave->particle, wave->start_x);
                entity_set_y(wave->particle, wave->start_y);

            } else {
                int y = SDL_sin(helper_deg2rad(wave->angle + wave->phase)) * wave->amp;
                entity_set_dx(wave->particle, -wave->spd);
                entity_set_dy(wave->particle, y);

            }
            break;

        case RIGHT:
            if (middle.x >= wave->width) {
                wave->start_y = rand() % wave->height+1;
                wave->start_x = 0;
                wave->angle = 0;
                entity_set_x(wave->particle, wave->start_x);
                entity_set_y(wave->particle, wave->start_y);

            } else {
                int y = SDL_sin(helper_deg2rad(wave->angle + wave->phase)) * wave->amp;
                entity_set_dx(wave->particle, wave->spd);
                entity_set_dy(wave->particle, y);

            }
            break;
    }

    wave->angle += wave->freq;
    entity_do(wave->particle);
}

void wave_move(wave_t* wave, int x, int y) {
    entity_set_dx(wave->particle, x);
    entity_set_dy(wave->particle, y);
}

void wave_set_height(wave_t* wave, int height) {
    wave->height = height;
}

void wave_set_width(wave_t* wave, int width) {
    wave->width = width;
}

void wave_set_amp(wave_t* wave, int amp) {
    wave->amp = amp;
}

void wave_set_freq(wave_t* wave, int freq) {
    wave->freq = freq;
}

void wave_set_spd(wave_t* wave, int spd) {
    wave->spd = spd;
}

void wave_set_phase(wave_t* wave, int phase) {
    wave->phase = phase;
}

void wave_draw(wave_t* wave, struct graphic_t* graphic) {
    entity_draw(wave->particle, graphic);
}
