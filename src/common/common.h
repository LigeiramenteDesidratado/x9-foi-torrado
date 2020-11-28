#ifndef COMMON_H
#define COMMON_H

#include <SDL2/SDL.h>

#ifdef __GNUC__
#define UNUSED \
    __attribute__((unused))
#else
#define UNUSED
#endif

typedef enum {false_t, true_t} bool_t;
typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STATIC

} direction_t;

#define private static
#define read_only const

typedef struct {
    int w, h;

} area_t;

typedef struct {

    struct audio_t* audio;
    struct graphic_t* graphic;
    struct input_t* input;
    struct menu_t* menu;
    struct screen_t* screen;
    struct text_t* text;
    struct stage_t* stage;

} game_component_args;

#define MAX_COLORS 5

extern SDL_Color game_colors[MAX_COLORS];

#endif
