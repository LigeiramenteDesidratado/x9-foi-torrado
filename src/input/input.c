#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "../screen/screen.h"
#include "../common/common.h"

#define MAX_KEYBOARD_KEYS 350

typedef struct {
    bool_t quit_signal;
    int lock;
    SDL_Event e;
    bool_t keyboard[MAX_KEYBOARD_KEYS];

} input_t;


static void __input_key_up(input_t*, SDL_KeyboardEvent*);
static void __input_key_down(input_t*, SDL_KeyboardEvent*);

input_t* input_new(void) {
    input_t* input =  (input_t*)malloc(sizeof(input_t));
    memset(&input->keyboard, 0, sizeof(input->keyboard));

    return input;
}

void input_ctor(input_t* input) {
    input->lock = 12;
    input->quit_signal = 1;
}

void input_dtor(UNUSED input_t* input) {
    // Do nothing
}

void input_do(input_t* input, game_component_args* args) {

    if (input->lock > 0) input->lock--;

    while (SDL_PollEvent(&input->e) != 0) {
        switch (input->e.type) {

            case SDL_QUIT:
                input->quit_signal = false_t;
                break;

            case SDL_WINDOWEVENT:
                if (input->e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    screen_set_window_size(args->screen, input->e.window.data1, input->e.window.data2);
                }
                break;

            case SDL_KEYUP:
                __input_key_up(input, &input->e.key);
                break;

            case SDL_KEYDOWN:
                __input_key_down(input, &input->e.key);
                break;

            default:
                break;
        }
    }
}

static void __input_key_up(input_t* input, SDL_KeyboardEvent* event) {
    // check if the keyboard event was a result of  Keyboard repeat event
    if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
        input->keyboard[event->keysym.scancode] = false_t;
    }
}

static void __input_key_down(input_t* input, SDL_KeyboardEvent* event) {
    // check if the keyboard event was a result of  Keyboard repeat event
    if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
        input->keyboard[event->keysym.scancode] = true_t;
    }
}

bool_t input_quit_signal(input_t* input) {
    return input->quit_signal;
}

void input_set_quit_signal(input_t* input, bool_t sig) {
    input->quit_signal = sig;
}

bool_t input_scan_key(input_t* input, int key) {
    return key < MAX_KEYBOARD_KEYS && input->keyboard[key];
}

bool_t input_scan_key_lock(input_t* input, int key) {

    bool_t val = false_t;

    if (input->lock == 0 && key < MAX_KEYBOARD_KEYS) {
        val = input->keyboard[key];
        if (val) {
            input->lock = 12;
        }
    }

    return val;
}
