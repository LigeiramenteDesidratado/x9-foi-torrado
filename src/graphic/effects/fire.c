#include <stdio.h>

#include <SDL2/SDL.h>

#include "particle.h"
#include "../../entity/entity.h"
#include "../../common/common.h"
#include "glow.h"

#define FIRE_PARTICLES 2

typedef struct {
    struct particle_t* particles[FIRE_PARTICLES];
    struct entity_t* center;
    SDL_Rect rect;
    /* SDL_Texture* texture_cache[FIRE_PARTICLES]; */

    bool_t mid;
    direction_t dir;

    /* int w; */
    /* int h; */
    /* float x; */
    /* float y; */
    /* float dx; */
    /* float dy; */

} fire_t;

fire_t* fire_new(void) {
    fire_t* fire = (fire_t*)malloc(sizeof(fire_t));
    fire->center = NULL;

    for (int i = 0; i < FIRE_PARTICLES; i++) {
        /* fire->texture_cache[i] = NULL; */
        fire->particles[i] = NULL;
    }

    /* fire->dx = 0; */
    /* fire->dy = 0; */
    /* fire->h = 0; */
    /* fire->w = 0; */
    /* fire->x = 0; */
    /* fire->y = 0; */
    fire->mid = 0;
    fire->dir = UP;

    return fire;
}

int fire_ctor(fire_t* fire, struct graphic_t* graphic, float _x, float _y, int _w, int _h, direction_t dir, int base_freq, int base_speed) {

    /* fire->x = x; */
    /* fire->y = y; */
    /* fire->w = w; */
    /* fire->h = h; */

    fire->center = entity_new();
    if (entity_ctor(fire->center, create_glow_ball(graphic, 60, (SDL_Color){255,255,255,255}, 3), 0.f, 0.f) != 0) {
        return -1;
    }

    fire->rect.x = _x;
    fire->rect.y = _y;
    fire->rect.w = _w;
    fire->rect.h = _h;

    switch(dir) {

        case UP:
            entity_set_x(fire->center, _x);
            entity_set_y(fire->center, _y + _h - _h / 5);
            break;
        case DOWN:
            entity_set_x(fire->center, _x);
            entity_set_y(fire->center, _y + _h / 5);
            break;
        case LEFT:
            entity_set_x(fire->center, _x + _w - _w / 5);
            entity_set_y(fire->center, _y);
            break;
        case RIGHT:
            entity_set_x(fire->center, _x + _w / 5);
            entity_set_y(fire->center, _y);
            break;
        default:
            break;
    }

    SDL_Color fire_c;

    for (int i = 0; i < FIRE_PARTICLES; i++) {

        /* int radius = 40 + rand()%10; */
        fire_c.r = 200 + rand()%55;
        fire_c.g = 20 + rand()%60;
        fire_c.b = rand()%40;

        /* fire->texture_cache[i] = create_glow_ball(graphic, radius, fire_c, 3); */

        float x = 0, y = 0;
        int height = 0, amp = 0;

        // TODO: fix fire position
        if (fire->dir == UP || fire->dir == DOWN) {
            x = entity_get_x(fire->center) - fire->rect.w / 14 + rand()%(fire->rect.w / 7);
            y = fire->rect.y + (fire->dir == UP ? fire->rect.h : 0);
            height = fire->rect.h / 5 + rand()%(fire->rect.h * 4 / 5);
            amp = fire->rect.w * 5 / 28 + rand()%(fire->rect.w / 4);

        } else if (fire->dir == LEFT || fire->dir == RIGHT) {
            x = fire->rect.x + (fire->dir == LEFT ? fire->rect.w : 0);
            y = entity_get_y(fire->center) - fire->rect.h / 14 + rand()%(fire->rect.h / 7);
            height = fire->rect.w / 5 + rand()%(fire->rect.w * 4 / 5);
            amp = fire->rect.h * 5 / 28 + rand()%(fire->rect.h / 4);
        }

        int phase = rand()%360;
        int freq = base_freq + rand()%(base_freq*2);
        int speed = base_speed + rand()%base_speed;

        fire->particles[i] = wave_new();
        wave_ctor(fire->particles[i], graphic, &fire_c, x, y, height, height, phase, amp, freq, speed, UP);
    }

    // TODO: Set particle cache texture;
    /* for(int i = 0; i < FIRE_PARTICLES; i++) { */
    /*         particles[i].set_texture(fire_texture_cache[rand()%(FIRE_PARTICLES - 1)]); */
    /* } */

    SDL_Texture* texture = create_glow_ball(graphic, FIRE_PARTICLES*2 , (SDL_Color){230, 70, 20, 0}, 3);
    fire->center = entity_new();
    if (entity_ctor(fire->center, texture, 100.f, 100.f) != 0) {
        return -1;
    }

    return 0;
}

void fire_dtor(fire_t* fire) {

    for (int i = 0; i < FIRE_PARTICLES; i++) {
        wave_dtor(fire->particles[i]);
        free(fire->particles[i]);

        /* SDL_DestroyTexture(fire->texture_cache[i]); */
        /* fire->texture_cache[i] = NULL; */
    }

    entity_dtor(fire->center);
    free(fire->center);

}

void fire_do(fire_t* fire) {
    entity_do(fire->center);
    for (int i = 0; i < FIRE_PARTICLES; i++) {
        wave_do(fire->particles[i]);
    }
}

void fire_move(fire_t* fire, int x, int y) {
    fire->rect.x = x;
    fire->rect.y = y;

    entity_set_dx(fire->center, entity_get_dx(fire->center));
    entity_set_dy(fire->center, entity_get_dy(fire->center));

    /* entity_set_dx(fire->middle, fire->x); */
    /* entity_set_dy(fire->middle, fire->y); */
    /* particle_move(fire->middle, fire->center.x, fire->center.y); */

    /* for (int i = 0; i < FIRE_PARTICLES; i++) { */
    /*     SDL_Point start = wave_get_start(fire->particles[i]); */
    /*     wave_move_start(fire->particles[i], start.x, start.y ); */
    /* } */
}

void fire_draw(fire_t* fire, game_component_args* args) {

    entity_draw(fire->center, args);

    for (int i = 0; i < FIRE_PARTICLES; i++) {
        wave_draw(fire->particles[i], args);
    }
}
