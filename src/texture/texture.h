#ifndef TEXTURE_H
#define TEXTURE_H

#include "../common/common.h"

struct texture_t;

// Allocate memory
struct texture_t* texture_new(void);

// Constructor
int texture_ctor(struct texture_t* texture);

// Destructor
void texture_dtor(struct texture_t* texture);

// Behavior
void texture_draw(struct texture_t* texture, float x, float y,  game_component_args* args);
void texture_load(struct texture_t* texture, const char* filename, game_component_args* args);
void texture_create(struct texture_t* texture, int w, int h, game_component_args* args);
void texture_set_blend_mode(struct texture_t* texture);
void texture_set_color_mod(struct texture_t* texture, SDL_Color c);
void texture_set_render_target(struct texture_t* texture, game_component_args* args);
void texture_reset_render_target(struct texture_t* texture, game_component_args* args);
void texture_query(struct texture_t* texture);
int texture_get_w(struct texture_t* texture);
int texture_get_h(struct texture_t* texture);
void texture_set_w(struct texture_t* texture, int w);
void texture_set_h(struct texture_t* texture, int h);


#endif
