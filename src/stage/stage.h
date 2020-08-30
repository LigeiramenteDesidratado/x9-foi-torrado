#ifndef STAGE_H
#define STAGE_H

#include <SDL2/SDL.h>

struct stage_t;
struct screen_t;
struct graphic_t;
struct input_t;
struct text_t;

// Allocate memory
struct stage_t* stage_new(void);

// Constructor
int stage_ctor(struct stage_t*, struct graphic_t*);

// Destructor
void stage_dtor(struct stage_t*);

// Behavior
void stage_draw(struct stage_t* stage, struct graphic_t* graphic, struct screen_t* screen, struct text_t* text);
void stage_do(struct stage_t*, struct graphic_t*, struct input_t*, struct screen_t*);

#endif
