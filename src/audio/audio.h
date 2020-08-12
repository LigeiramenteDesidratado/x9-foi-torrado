#ifndef AUDIO
#define AUDIO

struct audio_t;

screen_t* audio_new();

// Constructor
int audio_ctor(audio_t*);

// Destructor
void audio_dtor(audio_t*);

// Behaviors
#endif
