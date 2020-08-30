#include <SDL2/SDL.h>

float helper_get_distance(SDL_Point p1, SDL_Point p2)
{
    int dist_x = p2.x - p1.x;
    int dist_y = p2.y - p1.y;

    float distance = SDL_sqrt(dist_x*dist_x + dist_y*dist_y);

    return distance;
}

double helper_deg2rad(float deg) {
    return (deg/360)*2*3.14159265358979;
}
