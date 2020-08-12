#ifndef SCREEN
#define SCREEN

struct screen_t;

struct screen_t* screen_new();

// Constructor
int screen_ctor(struct screen_t*, const char*);

// Destructor
void screen_dtor(struct screen_t*);

// Behaviors
#endif
