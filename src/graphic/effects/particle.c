#include <SDL2/SDL.h>
#include <stdlib.h>

#include "../../common/common.h"
#include "../../entity/entity.h"
#include "../../texture/texture.h"
#include "../graphic.h"
#include "helpers.h"

typedef struct {

  struct entity_t *particle;
  struct texture_t *texture;
  int phase;
  int amp;
  int freq;
  float spd;

  float start_x, start_y;

  direction_t dir;

  int height;
  int width;
  int angle;

} particle_t;

private
int __texture_count = 0;

typedef enum { SMALL, MEDIUM, LARGE, MAX_SIZE } __part_size_t;
private
struct {
  struct texture_t *textures[MAX_SIZE];

} __texture_particle_array[MAX_COLORS];

private
void __particle_init_textures(game_component_args *args) {

  SDL_Renderer *renderer = graphic_get_renderer(args->graphic);

  for (int c = 0; c < MAX_COLORS; ++c) {
    for (int t = 0; t < MAX_SIZE; ++t) {
      __texture_particle_array[c].textures[t] = texture_new();

      texture_ctor(__texture_particle_array[c].textures[t]);

      // SMALL = 10;
      // MEDIUM = 20;
      // LARGE = 30;
      int radius = (t + 1) * 10;

      texture_create(__texture_particle_array[c].textures[t], 2 * radius,
                     2 * radius, args);
      texture_set_blend_mode(__texture_particle_array[c].textures[t]);
      texture_set_render_target(__texture_particle_array[c].textures[t], args);

      float relative_dist = 0;
      float distance = 0;
      int alpha = 0;
      int dim = 3;

      SDL_Point p = {0, 0};
      SDL_Point p_mid = {radius, radius};

      for (int y = 0; y < 2 * radius; y++) {
        for (int x = 0; x < 2 * radius; x++) {
          p.x = x;
          p.y = y;

          distance = helper_get_distance(p, p_mid);

          if (distance <= radius) {
            relative_dist = (float)(distance / radius * dim + 0.5);
            alpha = (int)(255 / (relative_dist * relative_dist) / 4);
          } else {
            alpha = 0;
          }

          SDL_SetRenderDrawColor(renderer, game_colors[c].r, game_colors[c].g,
                                 game_colors[c].b, alpha);

          // TODO: Error catch
          SDL_RenderDrawPoint(renderer, x, y);
        }
      }

      texture_query(__texture_particle_array[c].textures[t]);
      texture_reset_render_target(__texture_particle_array[c].textures[t],
                                  args);
    }
  }
}

particle_t *particle_new(void) {
  particle_t *particle = (particle_t *)malloc(sizeof(particle_t));
  particle->particle = NULL;
  particle->texture = NULL;

  return particle;
}

int particle_ctor(particle_t *particle, float mid_x, float mid_y, int width,
                  int height, int phase, int amp, int freq, float spd,
                  direction_t dir, game_component_args *args) {

  /* particle->texture = texture_new(); */
  int color = rand() % MAX_COLORS;
  int size = rand() % MAX_SIZE;

  if (__texture_count == 0) {
    __particle_init_textures(args);
  }
  ++__texture_count;

  particle->texture = __texture_particle_array[color].textures[size];

  particle->particle = entity_new();
  if (entity_ctor(particle->particle, mid_x, mid_y,
                  texture_get_w(particle->texture),
                  texture_get_h(particle->texture)) != 0) {
    return -1;
  }

  particle->height = height;
  particle->width = width;
  particle->phase = phase;
  particle->amp = amp;
  particle->freq = freq;
  particle->spd = spd;
  particle->dir = dir;
  particle->start_x = mid_x;
  particle->start_y = mid_y;
  particle->angle = 0;

  return 0;
}

void particle_dtor(particle_t *particle) {

  entity_dtor(particle->particle);
  free(particle->particle);
  particle->particle = NULL;

  /* texture_dtor(particle->texture); */
  /* free(particle->texture); */
  particle->texture = NULL;

  if (--__texture_count <= 0) {

    for (int c = 0; c < MAX_COLORS; ++c) {
      for (int t = 0; t < MAX_SIZE; ++t) {
        texture_dtor(__texture_particle_array[c].textures[t]);
        free(__texture_particle_array[c].textures[t]);
        __texture_particle_array[c].textures[t] = NULL;
      }
    }
  }
}

SDL_FPoint particle_get_start(read_only particle_t *particle) {

  return (SDL_FPoint){particle->start_x, particle->start_y};
}

void particle_move_start(particle_t *particle, int x, int y) {
  float diff_x = x - particle->start_x;
  float diff_y = y - particle->start_y;

  float ex = entity_get_x(particle->particle);
  float ey = entity_get_y(particle->particle);

  entity_set_dx(particle->particle, ex + diff_x);
  entity_set_dy(particle->particle, ey + diff_y);

  particle->start_x = x;
  particle->start_y = y;
}

void particle_do(particle_t *particle) {

  entity_set_dx(particle->particle, 0);
  entity_set_dy(particle->particle, 0);

  SDL_FPoint middle = entity_get_middle(particle->particle);

  switch (particle->dir) {
  case UP:
    if (middle.y <= 0) {
      particle->start_y = particle->height;
      particle->start_x = rand() % particle->width + 1;
      particle->angle = 0;
      entity_set_x(particle->particle, particle->start_x);
      entity_set_y(particle->particle, particle->start_y);

    } else {
      float x =
          (float)SDL_sin(helper_deg2rad(particle->angle + particle->phase)) *
          particle->amp;
      entity_set_dx(particle->particle, x);
      entity_set_dy(particle->particle, -particle->spd);
    }
    break;

  case DOWN:
    if (middle.y >= particle->height) {
      particle->start_y = 1;
      particle->start_x = rand() % particle->width + 1;
      particle->angle = 0;
      entity_set_x(particle->particle, particle->start_x);
      entity_set_y(particle->particle, particle->start_y);

    } else {
      float x =
          (float)SDL_sin(helper_deg2rad(particle->angle + particle->phase)) *
          particle->amp;
      entity_set_dx(particle->particle, x);
      entity_set_dy(particle->particle, particle->spd);
    }
    break;

  case LEFT:
    if (middle.x <= 0) {
      particle->start_y = rand() % particle->height + 1;
      particle->start_x = particle->width;
      particle->angle = 0;
      entity_set_x(particle->particle, particle->start_x);
      entity_set_y(particle->particle, particle->start_y);

    } else {
      float y =
          (float)SDL_sin(helper_deg2rad(particle->angle + particle->phase)) *
          particle->amp;
      entity_set_dx(particle->particle, -particle->spd);
      entity_set_dy(particle->particle, y);
    }
    break;

  case RIGHT:
    if (middle.x >= particle->width) {
      particle->start_y = rand() % particle->height + 1;
      particle->start_x = 0;
      particle->angle = 0;
      entity_set_x(particle->particle, particle->start_x);
      entity_set_y(particle->particle, particle->start_y);

    } else {
      float y =
          (float)SDL_sin(helper_deg2rad(particle->angle + particle->phase)) *
          particle->amp;
      entity_set_dx(particle->particle, particle->spd);
      entity_set_dy(particle->particle, y);
    }
    break;

  case STATIC:
    return;
  }

  particle->angle += particle->freq;
  entity_do(particle->particle);
}

void particle_move(particle_t *particle, int x, int y) {
  entity_set_dx(particle->particle, x);
  entity_set_dy(particle->particle, y);
}

void particle_set_height(particle_t *particle, int height) {
  particle->height = height;
}
void particle_set_width(particle_t *particle, int width) {
  particle->width = width;
}
void particle_set_amp(particle_t *particle, int amp) { particle->amp = amp; }
void particle_set_freq(particle_t *particle, int freq) {
  particle->freq = freq;
}
void particle_set_spd(particle_t *particle, float spd) { particle->spd = spd; }
void particle_set_phase(particle_t *particle, int phase) {
  particle->phase = phase;
}
void particle_draw(read_only particle_t *particle, game_component_args *args) {
  texture_draw(particle->texture, entity_get_x(particle->particle),
               entity_get_y(particle->particle), args);
}
