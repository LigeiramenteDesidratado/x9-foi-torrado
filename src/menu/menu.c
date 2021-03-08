#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>

#include "../audio/audio.h"
#include "../background/background.h"
#include "../common/common.h"
#include "../graphic/graphic.h"
#include "../input/input.h"
#include "../scene/scene.h"
#include "../scene/scene_p.h"
#include "../screen/screen.h"
#include "../stage/stage.h"
#include "../text/text.h"
#include "../text/text_p.h"

typedef enum {
  PLAY,
  CREDITS,
  EXIT,
  MAX_OPTS

} opts;

// Main menu of the game
typedef struct {
  // Is mandatory that scene_t type be the first item in the attribute
  // structure.
  scene_t scene;

  struct background_t *bg;

  // Current selected item in the menu
  opts selected;

  // Rectangle that will contain all menu opts
  SDL_Rect menu_rect;

  // Menu opts
  text_line_t *menu_text[MAX_OPTS];

} menu_t;

void __menu_do(void *ptr, game_component_args *args);
void __menu_draw(void *ptr, game_component_args *args);

// Allocate memory and set pointers to NULL
menu_t *menu_new(void) {
  menu_t *menu = (menu_t *)malloc(sizeof(menu_t));

  for (int i = 0; i < MAX_OPTS; ++i) {
    menu->menu_text[i] = NULL;
  }
  menu->bg = NULL;
  return menu;
}

// Initialize resources
int menu_ctor(menu_t *menu, game_component_args *args, scenes_id id) {

  scene_ctor((struct scene_t *)menu, id);
  menu->scene.scene_do = __menu_do;
  menu->scene.scene_draw = __menu_draw;

  menu->bg = background_new();
  if (background_ctor(menu->bg, "gfx/menu-backg.png", 800, 600, args) != 0) {
    return -1;
  }
  background_set_texture_color(menu->bg, game_colors[1]);

  const char *m_text[MAX_OPTS] = {
      "PLAY",
      "CREDITS",
      "EXIT",
  };

  // When the menu is loaded the
  // option PLAY will be selected
  menu->selected = PLAY;

  for (int i = 0; i < MAX_OPTS; ++i) {
    menu->menu_text[i] = (text_line_t *)malloc(sizeof(text_line_t));

    menu->menu_text[i]->line =
        (char *)malloc((strlen(m_text[i]) + 1) * sizeof(char));
    strcpy(menu->menu_text[i]->line, m_text[i]);

    // The color of the unselected items in the menu
    menu->menu_text[i]->color = game_colors[4];
  }

  return 0;
}

// Free resources
void menu_dtor(menu_t *menu) {

  for (int i = 0; i < MAX_OPTS; ++i) {
    free(menu->menu_text[i]->line);
    menu->menu_text[i]->line = NULL;

    free(menu->menu_text[i]);
    menu->menu_text[i] = NULL;
  }

  background_dtor(menu->bg);
  free(menu->bg);
  menu->bg = NULL;

  scene_dtor((struct scene_t *)menu);
}

void __menu_do(void *ptr, game_component_args *args) {

  menu_t *menu = (menu_t *)ptr;

  // Move to the previous item in the menu
  if ((menu->selected) > PLAY &&
      input_scan_key_lock(args->input, SDL_SCANCODE_K)) {
    menu->selected--;
    audio_play_sound(args->audio, CH_MENU, SND_MENU);
  }

  // Move to the next item in the menu
  if ((menu->selected) < EXIT &&
      input_scan_key_lock(args->input, SDL_SCANCODE_J)) {
    menu->selected++;
    audio_play_sound(args->audio, CH_MENU, SND_MENU);
  }

  // Behavior of the selected item in the menu
  if (input_scan_key_lock(args->input, SDL_SCANCODE_RETURN)) {
    switch (menu->selected) {

    case EXIT:
      input_set_quit_signal(args->input, false_t);
      break;

    case PLAY:
      stage_set_scene(args->stage, LVL_ONE);
      audio_play_sound(args->audio, CH_MENU, SND_LOADING);
      break;

    case CREDITS:
      break;

    case MAX_OPTS:
      // Fallthrough
    default:
      SDL_SetError("Invalid menu selection: %d\n", menu->selected);
      break;
    }
  }

  background_do(menu->bg, args);

  // Get the actual window width and height
  int w = screen_get_window_w(args->screen);
  int h = screen_get_window_h(args->screen);

  // Draw a rectangle in the middle of the screen
  // as a guideline for the menu
  menu->menu_rect.h = h / 2;
  menu->menu_rect.w = w / 2;
  menu->menu_rect.x = (w / 4);
  menu->menu_rect.y = (h / 4);

  for (int i = 0; i < MAX_OPTS; ++i) {
    // Options' menu position inside of the rectangle
    menu->menu_text[i]->rect.x = menu->menu_rect.x;
    menu->menu_text[i]->rect.y = menu->menu_rect.y + 10 + (i * 25);
    menu->menu_text[i]->rect.w = menu->menu_rect.w;
    if (menu->selected == (opts)i) {
      // The color of the selected item in the menu
      menu->menu_text[i]->color = game_colors[4];
    } else {
      // The color of the items not selected in the menu
      menu->menu_text[i]->color = game_colors[1];
    }
  }
}

void __menu_draw(void *ptr, game_component_args *args) {

  menu_t *menu = (menu_t *)ptr;

  background_draw(menu->bg, args);

  for (int i = 0; i < MAX_OPTS; ++i) {
    // Draw each menu option in its axis
    text_draw_line(args->text, args, menu->menu_text[i], true_t);
  }
}
