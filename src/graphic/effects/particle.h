#ifndef PARTICLE_H
#define PARTICLE_H

#include <SDL2/SDL.h>

struct particles_t;
struct graphic_t;

// Allocate memory
struct particle_t* particle_new(void);

// Constructor
int particle_ctor(struct particle_t*, SDL_Renderer*, SDL_Color*, int, int);

// Destructor
void particle_dtor(struct particle_t*);

// Behavior
void particle_move(struct particle_t*, int, int);
void particle_move_rect(struct particle_t*, int, int);
SDL_Rect particle_get_rect(struct particle_t*);
SDL_Point particle_get_middle(struct particle_t*);
void particle_draw(struct particle_t*, struct graphic_t*);
void particle_set_texture(struct particle_t*, SDL_Texture*);

#endif
