#ifndef GLOW_H
#define GLOW_H

#include <SDL2/SDL.h>

struct graphic_t;

SDL_Texture *create_glow_ball(struct graphic_t *graphic, int radius,
                              SDL_Color color, int dim);

#endif
