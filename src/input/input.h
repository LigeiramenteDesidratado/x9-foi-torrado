#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

typedef int bool_t;

struct input_t;
struct screen_t;

// memory allocator
struct input_t* input_new(void);

// Constructor
void input_ctor(struct input_t*);

// Destructor
void input_dtor(struct input_t*);

// Behavior
void input_do(struct input_t*, struct screen_t* screen);
bool_t input_quit_signal(struct input_t*);
void input_set_quit_signal(struct input_t* input, bool_t sig);
bool_t input_scan_key(struct input_t*, int);

#endif
