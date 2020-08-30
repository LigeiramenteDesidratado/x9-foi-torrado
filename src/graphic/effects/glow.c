#include <SDL2/SDL.h>

#include "helpers.h"
#include "../graphic.h"

SDL_Texture* create_glow_ball(struct graphic_t* graphic, int radius, SDL_Color color, int dim) {

    SDL_Renderer* renderer = graphic_get_renderer(graphic);

    float relative_dist = 0;
    float distance = 0;
    int alpha = 0;

    SDL_Point p = {0, 0};
    SDL_Point p_mid = {radius, radius};
    SDL_Texture* texture = NULL;

    if(dim < 0) {
        dim = 4.0;
    }

    // TODO: Error catch
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, radius*2, radius*2);

    SDL_SetRenderTarget(renderer, texture);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    for(int y = 0; y < 2*radius; y++) {
        for(int x = 0; x < 2*radius; x++) {
            p.x = x;
            p.y = y;

            distance = helper_get_distance(p, p_mid);

            if (distance <= radius) {
                relative_dist = distance/radius*dim + 0.5;
                alpha = 255/(relative_dist*relative_dist)/4;
            } else {
                alpha = 0;
            }

            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, alpha);

            // TODO: Error catch
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }

    SDL_SetRenderTarget(renderer, NULL);

    return texture;
}
