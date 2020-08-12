#ifndef GAME
#define GAME

struct game_t;

// malloc a new new game object
struct game_t* game_new();

// Constructor
void game_ctor(struct game_t*);

// Destructor
void game_dtor(struct game_t*);

// Behaviors

#endif
