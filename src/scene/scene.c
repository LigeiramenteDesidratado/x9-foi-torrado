#include <stdlib.h>
#include <stdio.h>

#include "scene_p.h"
#include "../common/common.h"


void __scene_do(UNUSED void* this_ptr, UNUSED game_component_args* args) {
    /* scene_t* scene = (scene_t*)this_ptr; */

    printf("Do nothing. You should overwrite this function\n");
}

void __scene_draw(UNUSED void* this_ptr, UNUSED game_component_args* args) {
    /* scene_t* scene = (scene_t*)this_ptr; */

    printf("Draw nothing. You should overwrite this function\n");
}

SDL_FPoint __scene_get_focus_cord(UNUSED void* this_ptr) {
    /* scene_t* scene = (scene_t*)this_ptr; */

    return (SDL_FPoint){0};
}

scene_t* scene_new(void) {
    return (scene_t*)malloc(sizeof(scene_t));
}

void scene_ctor(scene_t* scene, scenes_id id) {

    // Set the function pointer to point to the default definition
    scene->__id = id;
    scene->scene_do = __scene_do;
    scene->scene_draw = __scene_draw;
    scene->scene_get_focus_cord = __scene_get_focus_cord;

}

void scene_dtor(UNUSED scene_t* scene) {

}

void scene_do(scene_t* scene, game_component_args* args) {
    scene->scene_do(scene, args);
}

void scene_draw(scene_t* scene, game_component_args* args) {
    scene->scene_draw(scene, args);
}

SDL_FPoint scene_get_focus_cord(scene_t* scene) {
    return scene->scene_get_focus_cord(scene);
}

scenes_id scene_get_id(scene_t* scene) {
    return scene->__id;
}
