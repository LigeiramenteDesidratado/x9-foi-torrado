#include <stdio.h>
#include <time.h>

#include "../common/common.h"
#include "../graphic/graphic.h"
#include "../screen/screen.h"

#define MAX_RECT_TRANSITION 2048
#define MAX_PER_LOOP 24
#define MAX_SQUARE_SIZE 24

typedef enum {
  IN,
  OUT,
  DONE

} transition_state_t;

typedef struct {
  SDL_Rect rect;
  SDL_Color c;

} __rects_t;

typedef struct {
  transition_state_t state;
  int offset;

  __rects_t rects[MAX_RECT_TRANSITION];

} transition_t;

transition_t *transition_new(void) {
  transition_t *transition = (transition_t *)malloc(sizeof(transition_t));

  for (int i = 0; i < MAX_RECT_TRANSITION; ++i) {
    transition->rects[i].c = (SDL_Color){0};
    transition->rects[i].rect = (SDL_Rect){0};
  }

  return transition;
}

int transition_ctor(transition_t *transition) {

  transition->state = DONE;
  return 0;
}

void transition_dtor(UNUSED transition_t *transition) {}

void transition_do(transition_t *transition, game_component_args *args) {

  if (transition->state != DONE) {

    int w = screen_get_window_w(args->screen);
    int h = screen_get_window_h(args->screen);

    for (int i = 0; i < MAX_PER_LOOP; ++i) {

      if (transition->state == IN) {

        if (++transition->offset >= MAX_RECT_TRANSITION - 1) {
          transition->state = OUT;
        }

        int off = transition->offset;

        transition->rects[off].rect.w = 30 + (rand() % MAX_SQUARE_SIZE);
        transition->rects[off].rect.h = 30 + (rand() % MAX_SQUARE_SIZE);
        transition->rects[off].rect.x = rand() % w;
        transition->rects[off].rect.y = rand() % h;

        transition->rects[off].c = game_colors[rand() % MAX_COLORS];

      } else if (transition->state == OUT) {

        if (--transition->offset <= 0) {
          transition->state = DONE;
        }

      } else {
        break;
      }
    }
  }
}

void transition_draw(transition_t *transition, game_component_args *args) {

  if (transition->state != DONE) {
    for (int i = 0; i < transition->offset; ++i) {
      graphic_blit_fill_rect(args->graphic, transition->rects[i].c,
                             &transition->rects[i].rect);
    }
  }
}

void transition_start(transition_t *transition) {

  transition->offset = 0;
  transition->state = IN;
}

bool_t transition_is_middle(transition_t *transition) {

  return (bool_t)(transition->state == OUT);
}

bool_t transition_is_active(transition_t *transition) {

  return (bool_t)(transition->state != DONE);
}
