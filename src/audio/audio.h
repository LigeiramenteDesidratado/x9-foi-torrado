#ifndef AUDIO_H
#define AUDIO_H

#include "audio-defs.h"

struct audio_t;

// memory allocator
struct audio_t* audio_new(void);

// Constructor
int audio_ctor(struct audio_t*);

// Destructor
void audio_dtor(struct audio_t*);

// Behaviors
void audio_play_music_loop(struct audio_t*, background_music_t);
void audio_play_sound(struct audio_t* audio, channels_t channel, sound_effect_t id);
#endif
