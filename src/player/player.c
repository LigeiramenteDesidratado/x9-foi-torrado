#include <stdlib.h>

#include "../entity/entity.h"
#include "../graphic/graphic.h"
#include "../input/input.h"
#include "../screen/screen.h"

#define PLAYER_SPEED 4

typedef struct {
    struct entity_t* pneu;

} player_t;

player_t* player_new(void) {
    player_t* player = (player_t*)malloc(sizeof(player_t));
    player->pneu = NULL;

    return player;
}

int player_ctor(player_t* player, struct graphic_t* graphic) {

    player->pneu = entity_new();
    if (entity_ctor(player->pneu, graphic_load_texture(graphic, "gfx/pneu.png"), 100, 100) != 0) {
        return -1;
    }

    return 0;
}

void player_dtor(player_t* player) {

    entity_dtor(player->pneu);
    free(player->pneu);
}

void player_draw(player_t* player, struct graphic_t* graphic) {

    entity_draw(player->pneu, graphic);
}

void player_do(player_t* player, struct input_t* input, struct screen_t* screen) {

    entity_set_dx(player->pneu, 0);
    entity_set_dy(player->pneu, 0);

    if (input_scan_key(input, SDL_SCANCODE_K)) {
        if (entity_get_y(player->pneu) > 0) {
            entity_set_dy(player->pneu, -PLAYER_SPEED);
        }
    }

    if (input_scan_key(input, SDL_SCANCODE_J)) {
        if (entity_get_y(player->pneu) < (screen_get_window_h(screen) - entity_get_h(player->pneu))) {
            entity_set_dy(player->pneu, PLAYER_SPEED);
        }
    }

    if (input_scan_key(input, SDL_SCANCODE_H)) {
        if (entity_get_x(player->pneu) > 0) {
            entity_set_dx(player->pneu, -PLAYER_SPEED);
        }
    }

    if (input_scan_key(input, SDL_SCANCODE_L)) {
        if (entity_get_x(player->pneu) < screen_get_window_w(screen) - entity_get_w(player->pneu)) {
            entity_set_dx(player->pneu, PLAYER_SPEED);
        }
    }

    entity_do(player->pneu);
}

float player_get_x(player_t* player) {
    return entity_get_x(player->pneu);
}

float player_get_y(player_t* player) {
    return entity_get_y(player->pneu);
}
