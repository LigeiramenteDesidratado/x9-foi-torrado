#include <stdlib.h>

#include <SDL2/SDL.h>
#include "../graphic/graphic.h"

typedef struct {
    SDL_Texture* p_text;

    area_t area;

} texture_t;

texture_t* texture_new(void) {
    texture_t* texture = (texture_t*)malloc(sizeof(texture_t));

    texture->p_text = NULL;
    texture->area = (area_t){0};

    return texture;
}

int texture_ctor(UNUSED texture_t* texture) {

    return 0;
}

void texture_dtor(texture_t* texture) {

    if (texture->p_text != NULL) {
        SDL_DestroyTexture(texture->p_text);
        texture->p_text = NULL;
    }

}

void texture_load(texture_t* texture, const char* filename, game_component_args* args) {
    if (texture->p_text != NULL) {
        SDL_SetError("Texture is not NULL");
    }

    texture->p_text = graphic_load_texture(args->graphic, filename);

    SDL_QueryTexture(texture->p_text, NULL, NULL, &texture->area.w, &texture->area.h);
}

void texture_create(texture_t* texture, int w, int h, game_component_args* args) {

    if (texture->p_text != NULL) {
        SDL_SetError("Texture is not NULL");
    }
    texture->p_text = SDL_CreateTexture(graphic_get_renderer(args->graphic), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);

    texture->area.w = w;
    texture->area.h = h;
}

void texture_set_blend_mode(texture_t* texture) {

    if (texture->p_text != NULL) {
        SDL_SetTextureBlendMode(texture->p_text, SDL_BLENDMODE_BLEND);
    }
}

// Do not forget to call texture_reset_render_target when you're done
void texture_set_render_target(texture_t* texture, game_component_args* args) {

    if (texture->p_text != NULL) {
        SDL_SetRenderTarget(graphic_get_renderer(args->graphic), texture->p_text);
    }
}

void texture_reset_render_target(UNUSED texture_t* texture, game_component_args* args) {

    SDL_SetRenderTarget(graphic_get_renderer(args->graphic), NULL);
}

void texture_set_color_mod(texture_t* texture, SDL_Color c) {

    if (SDL_SetTextureColorMod(texture->p_text, c.r, c.g, c.b) != 0) {
        SDL_SetError("Error While setting texture color mod\n");
    }
}

void texture_query(texture_t* texture) {

    if (texture->p_text != NULL) {
        SDL_QueryTexture(texture->p_text, NULL, NULL, &texture->area.w, &texture->area.h);
    }
}

void texture_do(UNUSED texture_t* texture) {

}

void texture_draw(texture_t* texture, float x, float y,  game_component_args* args) {

    if (texture->p_text != NULL) {
        graphic_blit(args->graphic, texture->p_text, x, y, args);
    }
}

int texture_get_w(texture_t* texture) {
    return texture->area.w;
}

int texture_get_h(texture_t* texture) {
    return texture->area.h;
}

void texture_set_w(texture_t* texture, int w) {
    texture->area.w = w;
}

void texture_set_h(texture_t* texture, int h) {
    texture->area.h = h;
}
