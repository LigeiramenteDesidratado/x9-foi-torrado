#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "../menu/menu.h"
#include "../levels/lvl_one/lvl_one.h"
#include "../scene/scene.h"
#include "../input/input.h"
#include "../transition/transition.h"
#include "../camera/camera.h"

#include "../common/common.h"

typedef struct {

    scenes_id current_scene;

    struct transition_t* transition;
    struct scene_t* scene;
    struct camera_t* camera;

    /* struct menu_t* menu; */

} stage_t;

private void __stage_build_scene(stage_t* stage, game_component_args* args);
private void __stage_clean_scene(stage_t* stage);

stage_t* stage_new(void) {
    stage_t* stage = (stage_t*)malloc(sizeof(stage_t));
    stage->scene = NULL;
    stage->transition = NULL;
    stage->camera = NULL;

    return stage;
}

int stage_ctor(stage_t* stage, game_component_args* args) {

    stage->current_scene = MENU;

    stage->scene = (struct scene_t*)menu_new();
    if (menu_ctor((struct menu_t*)stage->scene, args, MENU) != 0) {
        return -1;
    }

    stage->transition = transition_new();
    if (transition_ctor(stage->transition) != 0) {
        return -1;
    }

    stage->camera = camera_new();
    if (camera_ctor(stage->camera) != 0) {
        return -1;
    }

    return 0;
}

void stage_dtor(stage_t* stage) {

    // Work around for freeing memory
    stage->current_scene = MAX_SCENES;
    __stage_clean_scene(stage);

    transition_dtor(stage->transition);
    free(stage->transition);
    stage->transition = NULL;

    camera_dtor(stage->camera);
    free(stage->camera);
    stage->camera = NULL;

}

void stage_do(stage_t* stage, game_component_args* args) {

    transition_do(stage->transition, args);

    if (transition_is_middle(stage->transition)) {
        __stage_clean_scene(stage);
        __stage_build_scene(stage, args);
        scene_do(stage->scene, args);
    }

    if (input_scan_key(args->input, SDL_SCANCODE_T)) {

        transition_start(stage->transition);
    }
    // A bit strange, but only update scene if is not transitioning
    // or if is fading out
    if (!transition_is_active(stage->transition)) {
        scene_do(stage->scene, args);
    }

    camera_do(stage->camera, scene_get_focus_cord(stage->scene), args);

}

void stage_draw(read_only stage_t* stage, game_component_args* args) {

    scene_draw(stage->scene, args);
    camera_draw(stage->camera, args);
    transition_draw(stage->transition, args);
}

void stage_set_scene(stage_t* stage, scenes_id id) {

    if (!transition_is_active(stage->transition)) {
        stage->current_scene = id;
        transition_start(stage->transition);
    }
}

private void __stage_clean_scene(stage_t* stage) {

    switch (scene_get_id(stage->scene)) {
        case MENU:
            if (stage->current_scene != MENU) {
                /* camera_dtor(stage->camera); */
                /* free(stage->camera); */

                menu_dtor((struct menu_t*)stage->scene);
                free((struct menu_t*)stage->scene);
                stage->scene = NULL;
            }
            break;

        case LVL_ONE:
            if (stage->current_scene != LVL_ONE) {
                /* camera_dtor(stage->camera); */
                /* free(stage->camera); */

                lvl_one_dtor((struct lvl_one_t*)stage->scene);
                free((struct lvl_one_t*)stage->scene);
                stage->scene = NULL;
            }
            break;
        case MAX_SCENES:
        default:
            break;
    }
}

private void __stage_build_scene(stage_t* stage, game_component_args* args) {

    if (stage->scene != NULL) { return; }

    switch (stage->current_scene) {
        case MENU:
            stage->scene = (struct scene_t*)menu_new();
            menu_ctor((struct menu_t*)stage->scene, args, MENU);

            camera_set_area(stage->camera, (area_t){0});

            break;

        case LVL_ONE:
            stage->scene = (struct scene_t*)lvl_one_new();
            lvl_one_ctor((struct lvl_one_t*)stage->scene, args, LVL_ONE);

            camera_set_area(stage->camera, lvl_one_get_area());

            break;

        case MAX_SCENES:
        default:
            stage->scene = (struct scene_t*)menu_new();
            menu_ctor((struct menu_t*)stage->scene, args, MENU);
            break;
    }

}

SDL_FRect stage_get_camera_rect(read_only stage_t* stage) {
    return camera_get_rect(stage->camera);
}
