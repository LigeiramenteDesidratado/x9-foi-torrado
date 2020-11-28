#ifndef SHAKE_H
#define SHAKE_H

struct shake_t;

// Allocate memory
struct shake_t* shake_new(void);

// Constructor
int shake_ctor(struct shake_t* shake, int duration, int freq);

// Destructor
void shake_dtor(struct shake_t* shake);

// Behavior
void shake_do(struct shake_t* shake, float* x, float* y);
void shake_start(struct shake_t* shake);

#endif
