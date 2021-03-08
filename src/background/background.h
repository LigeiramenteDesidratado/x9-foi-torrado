#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../common/common.h"
#include <SDL2/SDL.h>

struct background_t;
struct screen_t;

// Allocate memory
struct background_t *background_new(void);

// Constructor
int background_ctor(struct background_t *background, const char *filename,
                    int w, int h, game_component_args *args);

// Destructor
void background_dtor(struct background_t *);

// Behavior
void background_do(struct background_t *background, game_component_args *args);
void background_draw(struct background_t *background,
                     game_component_args *args);
void background_set_texture_color(struct background_t *background, SDL_Color c);
SDL_Rect background_get_area(struct background_t *background);
void background_set_texture_wh(struct background_t *background, int w, int h);

#endif
