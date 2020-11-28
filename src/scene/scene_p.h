#ifndef SCENE_P_H
#define SCENE_P_H

#include "scene_defs.h"
#include "../common/common.h"
#include <SDL2/SDL.h>


// Polymorphic behavior functions
typedef void (*do_t) (void* ptr, game_component_args* args);
typedef void (*draw_t) (void* ptr, game_component_args* args);
typedef SDL_FPoint (*focus_cord_t) (void* ptr);

/*
   The scene_t "class" has two behavior functions. The draw_t and do_t functions are
   supposed to be polymorphic and can be overridden by the child classes.
*/
typedef struct {
    // id will works like a runtime type check
    scenes_id __id;

    draw_t scene_draw;
    do_t scene_do;
    focus_cord_t scene_get_focus_cord;

} scene_t;

#endif
