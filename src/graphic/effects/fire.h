#ifndef FIRE_H
#define FIRE_H

#include <SDL2/SDL.h>
#include "helpers.h"

struct fire_t;
struct graphic_t;

typedef int bool_t;

// Allocate memory
struct fire_t* fire_new(void);

// Contructor
int fire_ctor(struct fire_t* fire, struct graphic_t* graphic, int x, int y, int w, int h, direction dir, int base_freq, int base_speed, bool_t small);

// Destructor
void fire_dtor(struct fire_t*);

// Behavior
void fire_do(struct fire_t*);
void fire_draw(struct fire_t* fire, struct graphic_t*);
void fire_move(struct fire_t*, int, int);


#endif
