#include <stdlib.h>

#include "../entity/entity.h"
#include "../graphic/graphic.h"
#include "../input/input.h"
#include "../texture/texture.h"

#define PLAYER_SPEED 8

typedef struct {
    struct entity_t* pneu;
    struct texture_t* texture;

    // Area that bounds the player
    int area_w, area_h;
    SDL_FPoint start_pos;
} player_t;

player_t* player_new(void) {
    player_t* player = (player_t*)malloc(sizeof(player_t));
    player->pneu = NULL;
    player->texture = NULL;
    player->start_pos = (SDL_FPoint){0};

    return player;
}

int player_ctor(player_t* player, int area_w, int area_h, float start_x, float start_y, game_component_args* args) {

    player->pneu = entity_new();

    player->texture = texture_new();
    texture_load(player->texture,"gfx/pneu.png", args);

    if (entity_ctor(player->pneu, start_x, start_y, texture_get_w(player->texture), texture_get_h(player->texture)) != 0) {
        return -1;
    }

    player->start_pos.x = start_x;
    player->start_pos.y = start_y;

    player->area_w = area_w;
    player->area_h = area_h;

    return 0;
}

void player_dtor(player_t* player) {

    entity_dtor(player->pneu);
    free(player->pneu);
    player->pneu = NULL;

    texture_dtor(player->texture);
    free(player->texture);
    player->texture = NULL;
}

void player_draw(read_only player_t* player, game_component_args* args) {

    texture_draw(player->texture, entity_get_x(player->pneu), entity_get_y(player->pneu), args);
}

void player_do(player_t* player, game_component_args* args) {

    entity_set_dx(player->pneu, 0);
    entity_set_dy(player->pneu, 0);

    if (input_scan_key(args->input, SDL_SCANCODE_K)) {
        if (entity_get_y(player->pneu) > 0) {
            entity_set_dy(player->pneu, -PLAYER_SPEED);
        }
    }

    if (input_scan_key(args->input, SDL_SCANCODE_J)) {
        if (entity_get_y(player->pneu) < (player->area_h - entity_get_h(player->pneu))) {
            entity_set_dy(player->pneu, PLAYER_SPEED);
        }
    }

    if (input_scan_key(args->input, SDL_SCANCODE_H)) {
        if (entity_get_x(player->pneu) > 0) {
            entity_set_dx(player->pneu, -PLAYER_SPEED);
        }
    }

    if (input_scan_key(args->input, SDL_SCANCODE_L)) {
        if (entity_get_x(player->pneu) < (player->area_w - entity_get_w(player->pneu))) {
            entity_set_dx(player->pneu, PLAYER_SPEED);
        }
    }

    entity_do(player->pneu);
}

float player_get_x(read_only player_t* player) {
    return entity_get_x(player->pneu);
}

float player_get_y(read_only player_t* player) {
    return entity_get_y(player->pneu);
}

SDL_FPoint player_get_middle(read_only player_t* player) {
    return entity_get_middle(player->pneu);
}

SDL_Point player_get_middle_i(read_only player_t* player) {

    SDL_Point m_i;
    SDL_FPoint m_f = entity_get_middle(player->pneu);

    m_i.x = (int)m_f.x;
    m_i.y = (int)m_f.y;

    return m_i;
}

SDL_Point player_get_cord_i(read_only player_t* player) {
    SDL_Point point;
    SDL_FPoint fpoint = entity_get_cord(player->pneu);

    point.x = (int)fpoint.x;
    point.y = (int)fpoint.y;

    return point;
}

void player_reset_pos(player_t* player) {

    entity_set_x(player->pneu, player->start_pos.x);
    entity_set_y(player->pneu, player->start_pos.y);
}
