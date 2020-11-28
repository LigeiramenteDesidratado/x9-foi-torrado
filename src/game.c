#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "SDL2/SDL.h"

#include "screen/screen.h"
#include "input/input.h"
#include "audio/audio.h"
#include "debug/debug.h"
#include "text/text.h"
#include "graphic/graphic.h"
#include "stage/stage.h"
#include "common/common.h"

typedef struct {

    game_component_args* args;

    struct screen_t* screen;
    struct graphic_t* graphic;
    struct input_t* input;
    struct text_t* text;
    struct audio_t* audio;
    struct stage_t* stage;

    struct debug_t* debug;

} game_t;

#define FPS 60

private void __game_cap_frame_rate(long *then, float *remainder);

game_t* game_new(void) {

    game_t* game  = (game_t*)malloc(sizeof(game_t));

    game->screen  = NULL;
    game->graphic = NULL;
    game->input   = NULL;
    game->text    = NULL;
    game->audio   = NULL;
    game->stage   = NULL;
    game->debug   = NULL;

    return game;
}

void game_ctor(game_t* game) {


    game->args = (game_component_args*)malloc(sizeof(game_component_args));
    game->screen = screen_new();
    if (screen_ctor(game->screen, "caloteiro") != 0) {
        fprintf(stderr, "Failed to initialize screen. SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
    game->args->screen = game->screen;

    game->graphic = graphic_new();
    if (graphic_ctor(game->graphic, game->screen) != 0) {
        fprintf(stderr, "Failed to initialize graphic. SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
    game->args->graphic = game->graphic;

    game->input = input_new();
    input_ctor(game->input);
    game->args->input = game->input;

    game->audio = audio_new();
    if (audio_ctor(game->audio) != 0) {
        fprintf(stderr, "Failed to initialize audio. SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
    game->args->audio = game->audio;

    game->text = text_new();
    if (text_ctor(game->text, game->graphic) != 0) {
        fprintf(stderr, "Failed to initialize text. SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
    game->args->text = game->text;

    game->stage = stage_new();
    if (stage_ctor(game->stage, game->args) != 0) {
        fprintf(stderr, "Failed to initialize stage. SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
    game->args->stage = game->stage;

    game->debug = debug_new();
    debug_ctor(game->debug, game->screen);
}

void game_dtor(game_t* game) {

    stage_dtor(game->stage);
    free(game->stage);

    input_dtor(game->input);
    free(game->input);

    audio_dtor(game->audio);
    free(game->audio);

    text_dtor(game->text);
    free(game->text);

    debug_dtor(game->debug);
    free(game->debug);

    graphic_dtor(game->graphic);
    free(game->graphic);

    screen_dtor(game->screen);
    free(game->screen);

    free(game->args);


    SDL_Quit();
}

int game_main_loop(game_t* game) {

    int f = 18;
    const char* error;

    audio_play_music_loop(game->audio, MSC_X9);

    long then = SDL_GetTicks();
    float remainder = 0;
    float elapsed = 0;

    while (input_quit_signal(game->input)) {

        Uint64 start = SDL_GetPerformanceCounter();

        graphic_clear_scene(game->graphic);

        input_do(game->input, game->args);

        stage_do(game->stage, game->args);

        if (input_scan_key_lock(game->input, SDL_SCANCODE_F)) {
            audio_play_music_loop(game->audio, MSC_MENU);
        }

        if (input_scan_key_lock(game->input, SDL_SCANCODE_E)) {
            audio_play_music_loop(game->audio, MSC_MAIN);
        }
        if (input_scan_key_lock(game->input, SDL_SCANCODE_X)) {
            audio_play_music_loop(game->audio, MSC_X9);
        }
        if (input_scan_key_lock(game->input, SDL_SCANCODE_F5)) {
            debug_toggle_b_panel(game->debug);
        }

        stage_draw(game->stage, game->args);

        debug_blit_b_panel(game->debug, game->args);

        SDL_Rect rect = debug_get_b_rect(game->debug);

        text_draw(
                game->text,
                game->args,
                10,
                screen_get_window_w(game->screen) - 10,
                10,
                0x00, 0xff, 0x00,
                "FPS: %.2f", elapsed
        );

        text_draw(game->text, game->args, rect.x + 10, rect.w - 10, rect.y + 10, 0xff, 0x00, 0x00, "A E S T H E T I C__");

        graphic_present_scene(game->graphic);

        __game_cap_frame_rate(&then, &remainder);
        Uint64 end = SDL_GetPerformanceCounter();

        if (--f == 0) {
            Uint64 freq = SDL_GetPerformanceFrequency();
            elapsed = (float)(1 / ((end - start) / (float)freq));
            f = 15;
        }

        error = SDL_GetError();
        if (*error) {
            fprintf(stderr, "SDL Error: %s\n", error);
            SDL_ClearError();
        }
    }

    return 0;
}

private void __game_cap_frame_rate(long *then, float *remainder) {
    long wait, frameTime;
    wait = (long int)(16 + *remainder);

    *remainder -= (int)*remainder;

    frameTime = SDL_GetTicks() - *then;

    wait -= frameTime;
    if (wait < 1) {
        wait = 1;
    }
    SDL_Delay(wait);

    *remainder += 0.667f;

    *then = SDL_GetTicks();
}
