#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL2/SDL.h>

struct background_t;
struct screen_t;

// Allocate memory
struct background_t* background_new(void);

// Constructor
int background_ctor(struct background_t*, SDL_Texture*);
// Destructor
void background_dtor(struct background_t*);

// Behavior
void background_draw(struct background_t*, SDL_Renderer*, struct screen_t*);

#endif
