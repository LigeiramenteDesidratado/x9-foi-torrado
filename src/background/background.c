#include <SDL2/SDL.h>

#include "../screen/screen.h"

typedef struct {
    SDL_Texture* background_sun;

} background_t;

background_t* background_new(void) {
    background_t* background = (background_t*)malloc(sizeof(background_t));
    background->background_sun = NULL;

    return background;
}

int background_ctor(background_t* background, SDL_Texture* texture) {

    if(texture == NULL) {
        SDL_SetError("invalid texture address");
        return -1;
    }
    background->background_sun = texture;

    return 0;
}

void background_dtor(background_t* background) {

    SDL_DestroyTexture(background->background_sun);
    background->background_sun = NULL;
}

void background_draw(background_t* background, SDL_Renderer* renderer, struct screen_t* screen) {
    SDL_SetRenderDrawColor(renderer, 0x12, 0x12, 0x12, 0xFF);
    SDL_RenderClear(renderer);

    SDL_Rect rect;

    rect.x = (screen_get_window_w(screen)/2) - 260 / 2;
    rect.y = (screen_get_window_h(screen)/2) - 260 / 2;
    rect.w = 260;
    rect.h = 260;
    SDL_RenderCopy(renderer, background->background_sun, NULL, &rect);

}
