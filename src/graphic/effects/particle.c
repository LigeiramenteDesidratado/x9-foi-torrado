#include <SDL2/SDL.h>
#include <time.h>

#include "helpers.h"
#include "../graphic.h"
#include "glow.h"

typedef struct {
    SDL_Texture* texture;

    // Middle point
    SDL_Point middle_p;
    SDL_Rect rect;

} particle_t;

static SDL_Texture* __particle_create(particle_t*, SDL_Renderer*, int, int, int, int, int);

particle_t* particle_new(void) {

    particle_t* particle = (particle_t*)malloc(sizeof(particle_t));
    particle->texture = NULL;

    return particle;
}

int particle_ctor(particle_t* particle, SDL_Renderer* renderer, SDL_Color* color, int mid_x, int mid_y) {

    particle->middle_p.x = mid_x;
    particle->middle_p.y = mid_y;

    particle->rect.x = mid_x;
    particle->rect.y = mid_y;
    particle->rect.w = 0;
    particle->rect.h = 0;

    particle->texture = create_glow_ball(renderer, rand() % 20+10, *color, 3);
    if (particle->texture == NULL) {
        return -1;
    }

    int w, h;
    if (SDL_QueryTexture(particle->texture, 0, 0, &w, &h) != 0) {
        return -1;
    }


    particle->rect.x = particle->middle_p.x - w / 2;
    particle->rect.y = particle->middle_p.y - h / 2;
    particle->rect.w = w;
    particle->rect.h = h;

    return 0;
}

void particle_dtor(particle_t* particle) {

    SDL_DestroyTexture(particle->texture);
    particle->texture = NULL;
}

void particle_move(particle_t* particle, int mid_x, int mid_y) {

    particle->middle_p.x = mid_x;
    particle->middle_p.y = mid_y;

    particle->rect.x = mid_x - particle->rect.w / 2;
    particle->rect.y = mid_y - particle->rect.h / 2;
}

void particle_move_rect(particle_t* particle, int x, int y) {

    particle->rect.x = x;
    particle->rect.y = y;

    particle->middle_p.x = x + particle->rect.w / 2;
    particle->middle_p.y = y + particle->rect.h / 2;

}

SDL_Rect particle_get_rect(particle_t* particle) {

    return particle->rect;
}

SDL_Point particle_get_middle(particle_t* particle) {

    return particle->middle_p;
}

void particle_set_texture(particle_t* particle, SDL_Texture* new_texture) {

    if (particle->texture != NULL) {
        SDL_DestroyTexture(particle->texture);
        particle->texture = NULL;
    }

    particle->texture = new_texture;
}

void particle_draw(particle_t* particle, struct graphic_t* graphic) {

    graphic_blit(graphic, particle->texture, particle->rect.x, particle->rect.y);
}

static SDL_Texture* __particle_create(particle_t* particle, SDL_Renderer* renderer, int r, int g, int b, int a, int radius) {

    SDL_Texture* text = NULL;
    SDL_Point p = {0, 0};
    SDL_Point p_mid = {radius, radius};

    // TODO: Catch error
    text = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, radius*2, radius*2);

    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_SetRenderTarget(renderer, text);
    SDL_SetTextureBlendMode(text, SDL_BLENDMODE_BLEND);

    for ( int y = 0; y < 2*radius; y++ ) {
        for ( int x = 0; x < 2*radius; x++ ) {
            p.x = x;
            p.y = y;

            if (helper_get_distance(p, p_mid) <= radius) {
                // TODO: Catch error
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }

    SDL_SetRenderTarget(renderer, NULL);

    return text;
}
