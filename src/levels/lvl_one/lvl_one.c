#include <stdlib.h>
#include <time.h>

#include "../../background/background.h"
#include "../../common/common.h"
#include "../../entity/entity.h"
#include "../../graphic/effects/particle.h"
#include "../../graphic/graphic.h"
#include "../../player/player.h"
#include "../../scene/scene.h"
#include "../../scene/scene_p.h"
#include "../../screen/screen.h"

#define MAX_PARTICLES 2400

// Map area
#define LVL_W 3160
#define LVL_H 3160

typedef struct {
  // Is mandatory that scene_t type be the first item in the attribute
  // structure.
  scene_t scene;

  struct background_t *bg;
  struct player_t *player;

  struct particle_t *particles[MAX_PARTICLES];

} lvl_one_t;

private
void __lvl_one_do(void *ptr, game_component_args *args);
private
void __lvl_one_draw(void *ptr, game_component_args *args);
private
SDL_FPoint __lvl_one_get_player_cord(void *ptr);

lvl_one_t *lvl_one_new(void) {
  lvl_one_t *lvl_one = (lvl_one_t *)malloc(sizeof(lvl_one_t));

  lvl_one->bg = NULL;
  lvl_one->player = NULL;

  return lvl_one;
}

int lvl_one_ctor(lvl_one_t *lvl_one, game_component_args *args, scenes_id id) {

  scene_ctor((struct scene_t *)lvl_one, id);
  lvl_one->scene.scene_do = __lvl_one_do;
  lvl_one->scene.scene_draw = __lvl_one_draw;
  lvl_one->scene.scene_get_focus_cord = __lvl_one_get_player_cord;

  lvl_one->bg = background_new();
  if (background_ctor(lvl_one->bg, "gfx/sun.png", LVL_W, LVL_H, args) != 0) {
    return -1;
  }

  lvl_one->player = player_new();
  if (player_ctor(lvl_one->player, LVL_W, LVL_H, 100.f, 100.f, args) != 0) {
    return -1;
  }

  int posw, posh;
  for (int i = 0; i < MAX_PARTICLES; i++) {

    direction_t dir = (rand() % (STATIC + 1));
    lvl_one->particles[i] = particle_new();

    posw = rand() % LVL_W + 1;
    posh = rand() % LVL_H + 1;

    if (particle_ctor(lvl_one->particles[i], posw, posh, LVL_W, LVL_H,
                      (rand() % 190 + 1), (rand() % 10 + 1), (rand() % 6 + 1),
                      (rand() % 6 + 1), dir, args) != 0) {
      return -1;
    }
  }
  return 0;
}

void lvl_one_dtor(lvl_one_t *lvl_one) {

  player_dtor(lvl_one->player);
  free(lvl_one->player);
  lvl_one->player = NULL;

  for (int i = 0; i < MAX_PARTICLES; i++) {
    particle_dtor(lvl_one->particles[i]);
    free(lvl_one->particles[i]);
    lvl_one->particles[i] = NULL;
  }

  background_dtor(lvl_one->bg);
  free(lvl_one->bg);
  lvl_one->bg = NULL;

  scene_dtor((struct scene_t *)lvl_one);
}

private
void __lvl_one_do(void *ptr, game_component_args *args) {

  lvl_one_t *lvl_one = (lvl_one_t *)ptr;

  background_do(lvl_one->bg, args);

  for (int i = 0; i < MAX_PARTICLES; i++) {
    particle_do(lvl_one->particles[i]);
  }

  player_do(lvl_one->player, args);
}

private
void __lvl_one_draw(void *ptr, game_component_args *args) {

  lvl_one_t *lvl_one = (lvl_one_t *)ptr;

  background_draw(lvl_one->bg, args);

  for (int i = 0; i < MAX_PARTICLES; i++) {
    particle_draw(lvl_one->particles[i], args);
  }

  player_draw(lvl_one->player, args);
}

private
SDL_FPoint __lvl_one_get_player_cord(void *ptr) {
  lvl_one_t *lvl_one = (lvl_one_t *)ptr;

  return player_get_middle(lvl_one->player);
}

area_t lvl_one_get_area() { return (area_t){LVL_W, LVL_H}; }
