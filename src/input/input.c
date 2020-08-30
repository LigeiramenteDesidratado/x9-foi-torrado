#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "../screen/screen.h"

#define MAX_KEYBOARD_KEYS 350

typedef int bool_t;

typedef struct {
    bool_t quit_signal;
    SDL_Event e;
    int keyboard[MAX_KEYBOARD_KEYS];

} input_t;


static void __input_key_up(input_t*, SDL_KeyboardEvent*);
static void __input_key_down(input_t*, SDL_KeyboardEvent*);

input_t* input_new(void) {
    input_t* input =  (input_t*)malloc(sizeof(input_t));
    memset(&input->keyboard, 0, sizeof(input->keyboard));

    return input;
}

void input_ctor(input_t* input) {
    input->quit_signal = 1;
}

void input_dtor(input_t* input) {
    // Do nothing
}

void input_do(input_t* input, struct screen_t* screen) {

    while (SDL_PollEvent(&input->e) != 0) {
        switch (input->e.type) {

            case SDL_QUIT:
                input->quit_signal = 0;
                break;

            case SDL_WINDOWEVENT:
                if (input->e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    screen_set_window_size(screen, input->e.window.data1, input->e.window.data2);
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
        input->keyboard[event->keysym.scancode] = 0;
    }
}

static void __input_key_down(input_t* input, SDL_KeyboardEvent* event) {
    // check if the keyboard event was a result of  Keyboard repeat event
    if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
        input->keyboard[event->keysym.scancode] = 1;
    }
}

bool_t input_quit_signal(input_t* input) {
    return input->quit_signal;
}

void input_set_quit_signal(input_t* input, bool_t sig) {
    input->quit_signal = sig;
}

bool_t input_scan_key(input_t* input, int key) {
    return input->keyboard[key];
}
