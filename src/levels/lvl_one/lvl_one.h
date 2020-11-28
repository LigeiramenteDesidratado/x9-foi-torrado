#ifndef LVL_ONE_H
#define LVL_ONE_H

#include "../../common/common.h"
#include "../../scene/scene.h"

struct lvl_one_t;

// Allocate memory
struct lvl_one_t* lvl_one_new(void);

// Constructor
int lvl_one_ctor(struct lvl_one_t* lvl_one, game_component_args* args, scenes_id id);

// Destructor
void lvl_one_dtor(struct lvl_one_t* lvl_one);

// Behavior
size_t lvl_one_size_of();
area_t lvl_one_get_area();

#endif
