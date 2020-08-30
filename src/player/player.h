#ifndef PLAYER_H
#define PLAYER_H

struct player_t;
struct graphic_t;
struct screen_t;

// Allocate memory
struct player_t* player_new(void);

// Constructor
int player_ctor(struct player_t*, struct graphic_t*);

// Destructor
void player_dtor(struct player_t*);

// Behavior
void player_draw(struct player_t*, struct graphic_t*);
void player_do(struct player_t*, struct input_t*, struct screen_t*);
float player_get_x(struct player_t*);
float player_get_y(struct player_t*);

#endif
