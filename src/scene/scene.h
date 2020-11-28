#ifndef SCENE_H
#define SCENE_H

#include "../common/common.h"
#include "scene_defs.h"

// Foward declaration
struct scene_t;

// Allocate memory
struct scene_t* scene_new();

// Constructor
void scene_ctor(struct scene_t* scene, scenes_id id);

// Destructor
void scene_dtor(struct scene_t* scene);

// Behavior
void scene_do(struct scene_t* scene, game_component_args* args);
void scene_draw(struct scene_t* scene, game_component_args* args);
scenes_id scene_get_id(struct scene_t* scene);
SDL_FPoint scene_get_focus_cord(struct scene_t* scene);

#endif
