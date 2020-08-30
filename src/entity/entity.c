#include <stdlib.h>
#include <SDL2/SDL.h>
#include "../graphic/graphic.h"

typedef struct {
    float x;
    float y;
    int w;
    int h;
    float dx;
    float dy;
    SDL_Texture* texture;

} entity_t;

entity_t* entity_new(void) {
    entity_t* entity = (entity_t*)malloc(sizeof(entity_t));
    entity->texture = NULL;
    entity->dx = 0;
    entity->dy = 0;
    entity->x = 0;
    entity->y = 0;
    entity->w = 0;
    entity->h = 0;

    return entity;
}

int entity_ctor(entity_t* entity, SDL_Texture* texture, int x, int y) {

    if(texture == NULL) {
        SDL_SetError("invalid texture address");
        return -1;
    }
    entity->texture = texture;

    entity->x = x;
    entity->y = y;

    if (SDL_QueryTexture(entity->texture, NULL, NULL, &entity->w, &entity->h) != 0) {
        return -1;
    }

    return 0;
}

void entity_dtor(entity_t* entity) {

    SDL_DestroyTexture(entity->texture);
    entity->texture = NULL;
}

void entity_do(entity_t* entity) {

    entity->x += entity->dx;
    entity->y += entity->dy;
}

void entity_draw(entity_t* entity, struct graphic_t* graphic) {

    graphic_blit(graphic, entity->texture, entity->x, entity->y);
}

SDL_Texture* entity_get_texture(entity_t* entity) {

    return entity->texture;
}

SDL_Point entity_get_middle(entity_t* entity) {

    return (SDL_Point){entity->x + entity->w / 2, entity->y + entity->h / 2};
}

float entity_get_x(entity_t* entity) {
    return entity->x;
}

float entity_get_y(entity_t* entity) {
    return entity->y;
}

void entity_set_x(entity_t* entity, float x) {
    entity->x = x;
}

void entity_set_y(entity_t* entity, float y) {
    entity->y = y;
}

float entity_get_dx(entity_t* entity) {
    return entity->dx;
}

float entity_get_dy(entity_t* entity) {
    return entity->dy;
}

void entity_set_dx(entity_t* entity, float dx) {
    entity->dx = dx;
}

void entity_set_dy(entity_t* entity, float dy) {
    entity->dy = dy;
}

float entity_get_h(entity_t* entity) {
    return entity->h;
}

float entity_get_w(entity_t* entity) {
    return entity->w;
}
