#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>

#include "../common/common.h"

struct entity_t;
struct graphic_t;

// Allocate memory
struct entity_t *entity_new(void);

// Constructor
int entity_ctor(struct entity_t *entity, float x, float y, int w, int h);

// Destructor
void entity_dtor(struct entity_t *);

void entity_do(struct entity_t *);

SDL_FPoint entity_get_middle(struct entity_t *entity);
SDL_FPoint entity_get_cord(struct entity_t *entity);

float entity_get_x(struct entity_t *);
float entity_get_y(struct entity_t *);
void entity_set_x(struct entity_t *, float);
void entity_set_y(struct entity_t *, float);

float entity_get_dx(struct entity_t *);
float entity_get_dy(struct entity_t *);
void entity_set_dx(struct entity_t *, float);
void entity_set_dy(struct entity_t *, float);

float entity_get_w(struct entity_t *);
float entity_get_h(struct entity_t *);

#endif
