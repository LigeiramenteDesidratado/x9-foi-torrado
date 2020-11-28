#ifndef PARTICLE_H
#define PARTICLE_H

#include <SDL2/SDL.h>
#include "helpers.h"
#include "../../common/common.h"


struct particle_t;

// Allocate memory
struct particle_t* particle_new(void);

// Constructor
int particle_ctor(struct particle_t* particle,
        float mid_x,
        float mid_y,
        int width,
        int height,
        int phase,
        int amp,
        int freq,
        int spd,
        direction_t dir,
        game_component_args* args
        );

// Destructor
void particle_dtor(struct particle_t*);

// Behavior
void particle_move_start(struct particle_t*, int, int);
void particle_do(struct particle_t* particle);
void particle_draw(read_only struct particle_t* particle, game_component_args* args);
void particle_set_amp(struct particle_t*, int);
void particle_set_freq(struct particle_t*, int);
void particle_set_spd(struct particle_t*, int);
void particle_set_phase(struct particle_t*, int);
void particle_set_height(struct particle_t* particle, int);
void particle_set_width(struct particle_t* particle, int);
void particle_move(struct particle_t*, int, int);
SDL_FPoint particle_get_start(read_only struct particle_t* particle);

#endif
