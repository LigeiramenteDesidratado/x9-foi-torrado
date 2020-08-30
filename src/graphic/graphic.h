#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL2/SDL_image.h>

struct graphic_t;
struct screen_t;

// memory allocator
struct graphic_t* graphic_new(void);

// Constructor
int graphic_ctor(struct graphic_t*, struct screen_t*);

// Destructor
void graphic_dtor(struct graphic_t*);

// Behavior
SDL_Texture* graphic_load_texture(struct graphic_t*, const char*);
SDL_Renderer* graphic_get_renderer(struct graphic_t*);

void graphic_present_scene(struct graphic_t*);
void graphic_blit(struct graphic_t*, SDL_Texture*, int, int);
void graphic_blit_rect(struct graphic_t* graphic, SDL_Texture *texture, SDL_Rect* src, SDL_Rect* dest);

#endif
