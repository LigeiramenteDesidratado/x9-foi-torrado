#ifndef DEBUG_H
#define DEBUG_H
#include <SDL2/SDL.h>
typedef int bool_t;

struct debug_t;
struct screen_t;
struct graphic_t;

// memory allocator
struct debug_t* debug_new(void);

// Constructor
void debug_ctor(struct debug_t*, struct screen_t*);

// Destructor
void debug_dtor(struct debug_t*);

// Behavior
void debug_toggle_tl_panel(struct debug_t*);
void debug_toggle_b_panel(struct debug_t*);
void debug_set_fps(struct debug_t*, float);
void debug_blit_b_panel(struct debug_t*, struct graphic_t*, struct screen_t*);
SDL_Rect debug_get_b_rect(struct debug_t*);

#endif
