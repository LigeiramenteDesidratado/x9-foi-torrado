#ifndef INPUT_H
#define INPUT_H

#include "../common/common.h"
#include <SDL2/SDL.h>

struct input_t;
struct screen_t;

// memory allocator
struct input_t *input_new(void);

// Constructor
void input_ctor(struct input_t *);

// Destructor
void input_dtor(struct input_t *);

// Behavior
void input_do(struct input_t *input, game_component_args *args);
bool_t input_quit_signal(struct input_t *);
void input_set_quit_signal(struct input_t *input, bool_t sig);
bool_t input_scan_key(struct input_t *input, int key);
bool_t input_scan_key_lock(struct input_t *input, int key);

#endif
