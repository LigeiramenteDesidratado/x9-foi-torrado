#ifndef TRANSITION_H
#define TRANSITION_H

#include "../common/common.h"

struct transition_t;

// Allocate memory
struct transition_t *transition_new(void);

// Constructor
int transition_ctor(struct transition_t *transition);

// Destructor
void transition_dtor(struct transition_t *transition);

// Behaviors
void transition_do(struct transition_t *transition, game_component_args *args);
void transition_draw(struct transition_t *transition,
                     game_component_args *args);
bool_t transition_is_middle(struct transition_t *transition);
bool_t transition_is_active(struct transition_t *transition);
void transition_start(struct transition_t *transition);

#endif
