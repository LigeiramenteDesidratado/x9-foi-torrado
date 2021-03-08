#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "../common/common.h"
#include <SDL2/SDL_image.h>

struct graphic_t;
struct screen_t;

void __graphic_blit_rect(struct graphic_t *graphic, SDL_Texture *texture,
                         SDL_Rect *src, SDL_Rect *dest,
                         game_component_args *args);
void __graphic_blit_rect_f(struct graphic_t *graphic, SDL_Texture *texture,
                           SDL_Rect *src, SDL_FRect *dest,
                           game_component_args *args);

#define graphic_blit_rect(G, T, SRC, DST, ARGS)                                \
  _Generic((DST), SDL_Rect                                                     \
           : __graphic_blit_rect, SDL_FRect                                    \
           : __graphic_blit_rect_f, default                                    \
           : __graphic_blit_rect)(G, T, SRC, DST, ARGS)

void __graphic_blit(struct graphic_t *graphic, SDL_Texture *texture, int x,
                    int y, game_component_args *args);
void __graphic_blit_f(struct graphic_t *graphic, SDL_Texture *texture, float x,
                      float y, game_component_args *args);

#define graphic_blit(G, T, X, Y, ARGS)                                         \
  _Generic((X), int                                                            \
           : __graphic_blit, float                                             \
           : __graphic_blit_f, default                                         \
           : __graphic_blit)(G, T, X, Y, ARGS)

void __graphic_draw_rect(struct graphic_t *graphic, SDL_Rect dest);
void __graphic_draw_rect_f(struct graphic_t *graphic, SDL_FRect dest);

#define graphic_draw_rect(G, T)                                                \
  _Generic((T), SDL_FRect                                                      \
           : __graphic_draw_rect_f, SDL_Rect                                   \
           : __graphic_draw_rect, default                                      \
           : __graphic_draw_rect)(G, T)

// memory allocator
struct graphic_t *graphic_new(void);

// Constructor
int graphic_ctor(struct graphic_t *, struct screen_t *);

// Destructor
void graphic_dtor(struct graphic_t *);

// Behavior
SDL_Texture *graphic_load_texture(struct graphic_t *, const char *);
SDL_Renderer *graphic_get_renderer(struct graphic_t *);

void graphic_present_scene(struct graphic_t *);
void graphic_clear_scene(struct graphic_t *graphic);
/* void graphic_draw_rect(struct graphic_t* graphic, SDL_Rect dest); */
/* void graphic_blit(struct graphic_t*, SDL_Texture*, int, int); */
/* void graphic_blit_rect(struct graphic_t* graphic, SDL_Texture *texture,
 * SDL_Rect* src, SDL_Rect* dest); */
void graphic_blit_fill_rect(struct graphic_t *graphic, SDL_Color c,
                            SDL_Rect *rect);

#endif
