#ifndef GAME_H
#define GAME_H

struct game_t;

// memory allocator
struct game_t *game_new(void);

// Constructor
void game_ctor(struct game_t *);

// Destructor
void game_dtor(struct game_t *);

// Behaviors
int game_main_loop(struct game_t *);
void game_quit(struct game_t *);

#endif
