#ifndef TEXT_P_H
#define TEXT_P_H

#include <SDL2/SDL.h>

typedef struct {
    SDL_Rect rect;
    SDL_Color color;
    char* line;

} text_line_t;

#endif
