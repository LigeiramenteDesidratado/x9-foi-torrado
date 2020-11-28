#ifndef STAGE_H
#define STAGE_H

#include "../common/common.h"
#include "../scene/scene.h"

#include <SDL2/SDL.h>

struct stage_t;

// Allocate memory
struct stage_t* stage_new(void);

// Constructor
int stage_ctor(struct stage_t* stage, game_component_args* args);

// Destructor
void stage_dtor(struct stage_t*);

// Behavior
void stage_draw(read_only struct stage_t* stage, game_component_args* args);
void stage_do(struct stage_t*, game_component_args* args);
void stage_set_scene(struct stage_t* stage, scenes_id id);
SDL_FRect stage_get_camera_rect(read_only struct stage_t* stage);

#endif
