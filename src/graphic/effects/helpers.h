#ifndef HELPERS_H
#define HELPERS_H

#include <SDL2/SDL.h>

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT

} direction ;

float helper_get_distance(SDL_Point, SDL_Point);
double helper_deg2rad(float);
#endif
