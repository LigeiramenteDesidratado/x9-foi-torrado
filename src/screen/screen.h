#ifndef SCREEN_H
#define SCREEN_H

#include "SDL2/SDL.h"

struct screen_t;

// Allocate
struct screen_t* screen_new(void);

// Constructor
int screen_ctor(struct screen_t*, const char*);

// Destructor
void screen_dtor(struct screen_t*);

// Behaviors
SDL_Window* screen_get_window(struct screen_t*);

void screen_set_window_size(struct screen_t*, int, int);

// returns the window width
unsigned int screen_get_window_w(struct screen_t*);
// returns the window height
unsigned int screen_get_window_h(struct screen_t*);

unsigned int screen_get_window_default_w(struct screen_t*);
unsigned int screen_get_window_default_h(struct screen_t*);
#endif
