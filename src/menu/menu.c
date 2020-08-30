#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>

#include "../entity/entity.h"
#include "../graphic/graphic.h"
#include "../input/input.h"
#include "../screen/screen.h"
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
    int lock;

    // Current selected item in the menu
    opts selected;

    // Rectangle that will contain all menu opts
    SDL_Rect menu_rect;

    // Menu opts
    text_line_t* menu_text[MAX_OPTS];

} menu_t;

// Allocate memory and set pointers to NULL
menu_t* menu_new(void) {
    menu_t* menu = (menu_t*)malloc(sizeof(menu_t));

    for (int i = 0; i < MAX_OPTS; ++i) {
        menu->menu_text[i] = NULL;
    }
    return menu;
}

// Initialize resources
int menu_ctor(menu_t* menu, struct graphic_t* graphic) {

    const char* m_text[MAX_OPTS] = {
        "PLAY",
        "CREDITS",
        "EXIT",
    };

    // When the menu is loaded the
    // option PLAY will be selected
    menu->selected = PLAY;

    for (int i = 0; i < MAX_OPTS; ++i) {
        menu->menu_text[i] = (text_line_t*)malloc(sizeof(text_line_t));

        menu->menu_text[i]->line = (char*)malloc((strlen(m_text[i])+1) * sizeof(char));
        strcpy(menu->menu_text[i]->line, m_text[i]);

        // The color of the unselected items in the menu
        menu->menu_text[i]->color = (SDL_Color){0xf4,0xf4,0xf4, 0xff};

    }

    menu->lock = 12;
    return 0;
}

// Free resources
void menu_dtor(menu_t* menu) {

    for (int i = 0; i < MAX_OPTS; ++i) {
        free(menu->menu_text[i]->line);
        menu->menu_text[i]->line = NULL;

        free(menu->menu_text[i]);
        menu->menu_text[i] = NULL;
    }
}

void menu_do(menu_t* menu, struct input_t* input, struct screen_t* screen) {

    if (menu->lock > 0) {
        menu->lock--;
    }

    // Move to the previous item in the menu
    if (menu->lock == 0 && (menu->selected) > PLAY && input_scan_key(input, SDL_SCANCODE_K)) {
        menu->selected--;
        menu->lock = 12;
    }

    // Move to the next item in the menu
    if (menu->lock == 0 && (menu->selected) < EXIT && input_scan_key(input, SDL_SCANCODE_J)) {
        menu->selected++;
        menu->lock = 12;
    }

    // Behaviors of the selected items in the menu
    if (menu->lock == 0 && input_scan_key(input, SDL_SCANCODE_RETURN)) {
        switch(menu->selected) {
            case EXIT:
                input_set_quit_signal(input, 0);
                break;

            case PLAY:
                break;

            case CREDITS:
                break;

            case MAX_OPTS:
            default:
                SDL_SetError("Invalid menu selection: %d\n", menu->selected);
                break;
        }
        menu->lock = 12;
    }

    // Get the actual window width and height
    int w = screen_get_window_w(screen);
    int h = screen_get_window_h(screen);

    // Draw a rectangle in the middle of the screen
    // as a guideline for the menu
    menu->menu_rect.h = h / 2;
    menu->menu_rect.w = w / 2;
    menu->menu_rect.x = (w / 4);
    menu->menu_rect.y = (h / 4);


    for (int i = 0; i < MAX_OPTS; ++i) {
        // Options' menu position inside of the rectangle
        menu->menu_text[i]->rect.x = menu->menu_rect.x;
        menu->menu_text[i]->rect.y = menu->menu_rect.y + 10 +(i*25);
        menu->menu_text[i]->rect.w = menu->menu_rect.w;
        if (menu->selected == i) {
            // The color of the items selected in the menu
            menu->menu_text[i]->color.g = 0x13;
            menu->menu_text[i]->color.b = 0x13;
        } else {
            // The color of the items not selected in the menu
            menu->menu_text[i]->color.g = 0xf4;
            menu->menu_text[i]->color.b = 0xf4;
        }
    }

}

void menu_draw(menu_t* menu, struct graphic_t* graphic, struct text_t* text) {


    /* SDL_SetRenderDrawColor(graphic_get_renderer(graphic), 0x14, 0xf4, 0x14, 0x14); */
    /* SDL_RenderDrawRect(graphic_get_renderer(graphic), &menu->menu_rect); */

    for (int i = 0; i < MAX_OPTS; ++i) {
        // Draw each menu option in its axis
        text_draw_line(text, graphic, menu->menu_text[i], 1);
    }
}
