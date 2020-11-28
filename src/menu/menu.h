#ifndef MENU_H
#define MENU_H

#include "../common/common.h"
#include "../scene/scene.h"

struct menu_t;

// Allocate memory
struct menu_t* menu_new(void);

// Constructor
int menu_ctor(struct menu_t* menu, game_component_args* args, scenes_id id);

// Destructor
void menu_dtor(struct menu_t*);

// Behavior
/* void menu_do(struct menu_t*, struct input_t*, struct screen_t* screen); */
/* void menu_draw(struct menu_t* menu, struct graphic_t* graphic, struct text_t* text); */

#endif
