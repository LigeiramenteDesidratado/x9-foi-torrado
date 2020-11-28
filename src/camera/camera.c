#include <stdlib.h>
#include <SDL2/SDL.h>

#include "../common/common.h"
#include "../graphic/effects/shake.h"
#include "../screen/screen.h"
#include "../input/input.h"
#include "../graphic/graphic.h"


typedef struct {
    // Point at which camera will keep the focus
    SDL_FPoint focus;

    SDL_FRect rect;
    // Area at which camera can act
    SDL_FRect area;

    struct shake_t* shake;

} camera_t;

// Allocate memory to the camera object
camera_t* camera_new(void) {
    camera_t* camera = (camera_t*)malloc(sizeof(camera_t));

    camera->focus = (SDL_FPoint){0};
    camera->rect = (SDL_FRect){0};
    camera->area = (SDL_FRect){0};
    camera->shake = NULL;

    return camera;
}

int camera_ctor(camera_t* camera) {

    camera->shake = shake_new();
    if (shake_ctor(camera->shake, 1000, 60) != 0) {
        return -1;
    }

    return 0;
}

void camera_dtor(camera_t* camera) {

    camera->rect = (SDL_FRect){0};
    camera->area = (SDL_FRect){0};
    camera->focus = (SDL_FPoint){0};

    shake_dtor(camera->shake);
    free(camera->shake);
    camera->shake = NULL;
}

void camera_do(camera_t* camera, SDL_FPoint cord, game_component_args* args) {

    int w = screen_get_window_w(args->screen);
    int h = screen_get_window_h(args->screen);

    camera->rect.w = w > camera->area.w ? camera->area.w : w;
    camera->rect.h = h > camera->area.h ? camera->area.h : h;

    camera->rect.x = (cord.x) - (camera->rect.w /2);
    camera->rect.y = (cord.y) - (camera->rect.h /2);

    // if it is outside the left
    if (camera->rect.x < camera->area.x)
        camera->rect.x = camera->area.x;
    // or right margin, pull back
    else if (camera->rect.x + camera->rect.w > camera->area.x + camera->area.w)
        camera->rect.x = (camera->area.x + camera->area.w) - camera->rect.w;

    // if came out on top
    if (camera->rect.y < camera->area.y)
        camera->rect.y = camera->area.y;
    // or bottom margin, pull back
    else if (camera->rect.y + camera->rect.h > camera->area.x + camera->area.h)
        camera->rect.y = (camera->area.y + camera->area.h) - camera->rect.h;

    if (input_scan_key(args->input, SDL_SCANCODE_N)) {
        shake_start(camera->shake);
    }

    shake_do(camera->shake, &camera->rect.x, &camera->rect.y);
}

void camera_draw(camera_t* camera, game_component_args* args) {

    SDL_FRect dest;
    dest.x = camera->focus.x;
    dest.y = camera->focus.y;
    dest.h = camera->rect.h;
    dest.w = camera->rect.w;

    graphic_draw_rect(args->graphic, dest);
}

SDL_FRect camera_get_rect(camera_t* camera) {

    return camera->rect;
}

void camera_set_focus(camera_t* camera, float x, float y) {

    camera->focus.x = x;
    camera->focus.y = y;
}

void camera_set_area(camera_t* camera, area_t area) {

    camera->area.w = area.w;
    camera->area.h = area.h;

}
