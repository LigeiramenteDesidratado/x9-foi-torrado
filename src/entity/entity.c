#include <SDL2/SDL.h>
#include <stdlib.h>

#include "../common/common.h"

typedef struct {
  int w, h;

  float x, y;
  float dx, dy;

} entity_t;

entity_t *entity_new(void) {
  entity_t *entity = (entity_t *)malloc(sizeof(entity_t));
  entity->dx = 0;
  entity->dy = 0;
  entity->x = 0;
  entity->y = 0;
  entity->w = 0;
  entity->h = 0;

  return entity;
}

int entity_ctor(entity_t *entity, float x, float y, int w, int h) {

  entity->x = x;
  entity->y = y;
  entity->w = w;
  entity->h = h;

  return 0;
}

void entity_dtor(UNUSED entity_t *entity) {}

void entity_do(entity_t *entity) {

  entity->x += entity->dx;
  entity->y += entity->dy;
}

void entity_draw(UNUSED entity_t *entity, UNUSED game_component_args *args) {}

SDL_FPoint entity_get_middle(entity_t *entity) {

  return (SDL_FPoint){entity->x + entity->w / 2, entity->y + entity->h / 2};
}

float entity_get_x(entity_t *entity) { return entity->x; }

float entity_get_y(entity_t *entity) { return entity->y; }

void entity_set_x(entity_t *entity, float x) { entity->x = x; }

void entity_set_y(entity_t *entity, float y) { entity->y = y; }

float entity_get_dx(entity_t *entity) { return entity->dx; }

float entity_get_dy(entity_t *entity) { return entity->dy; }

void entity_set_dx(entity_t *entity, float dx) { entity->dx = dx; }

void entity_set_dy(entity_t *entity, float dy) { entity->dy = dy; }

float entity_get_h(entity_t *entity) { return entity->h; }

float entity_get_w(entity_t *entity) { return entity->w; }

SDL_FPoint entity_get_cord(entity_t *entity) {
  return (SDL_FPoint){entity->x, entity->y};
}
