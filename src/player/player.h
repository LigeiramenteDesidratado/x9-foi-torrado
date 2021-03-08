#ifndef PLAYER_H
#define PLAYER_H

#include "../common/common.h"

struct player_t;
struct graphic_t;

// Allocate memory
struct player_t *player_new(void);

// Constructor
int player_ctor(struct player_t *player, int area_w, int area_h, float start_x,
                float start_y, game_component_args *args);

// Destructor
void player_dtor(struct player_t *);

// Behavior
void player_draw(read_only struct player_t *, game_component_args *args);
void player_do(struct player_t *player, game_component_args *args);
float player_get_x(read_only struct player_t *);
float player_get_y(read_only struct player_t *);
SDL_FPoint player_get_middle(read_only struct player_t *player);
SDL_Point player_get_middle_i(read_only struct player_t *player);
SDL_Point player_get_cord_i(read_only struct player_t *player);
void player_reset_pos(struct player_t *player);

#endif
