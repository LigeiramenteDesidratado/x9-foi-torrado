#ifndef CAMERA_H
#define CAMERA_H

#include "../common/common.h"
#include <SDL2/SDL.h>

struct camera_t;

// Allocate memory
struct camera_t *camera_new(void);

// Constructor
int camera_ctor(struct camera_t *camera);

// Destructor
void camera_dtor(struct camera_t *camera);

// Behavior
void camera_do(struct camera_t *camera, SDL_FPoint cord,
               game_component_args *args);
void camera_draw(struct camera_t *camera, game_component_args *args);
SDL_FRect camera_get_rect(struct camera_t *camera);
void camera_set_focus(struct camera_t *camera, int x, int y);
void camera_set_area(struct camera_t *camera, area_t area);

#endif
