#ifndef WAVE_H
#define WAVE_H

#include <SDL2/SDL.h>
#include "helpers.h"

struct wave_t;
struct graphic_t;

// Allocate memory
struct wave_t* wave_new(void);

// Constructor
int wave_ctor(struct wave_t* wave,
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
        direction dir);

// Destructor
void wave_dtor(struct wave_t*);

// Behavior
SDL_Point wave_get_start(struct wave_t*);
void wave_move_start(struct wave_t*, int, int);
void wave_do(struct wave_t* wave);
void wave_draw(struct wave_t*, struct graphic_t*);
void wave_set_amp(struct wave_t*, int);
void wave_set_freq(struct wave_t*, int);
void wave_set_spd(struct wave_t*, int);
void wave_set_phase(struct wave_t*, int);
void wave_set_height(struct wave_t* wave, int);
void wave_set_width(struct wave_t* wave, int);
void wave_move(struct wave_t*, int, int);

#endif
