#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "../common/common.h"
#include "audio-defs.h"

#define MAX_SND_CHANNELS 8

private
char *musics[MSC_MAX] = {
    "music/cheiro-comunismo.opus", // MAIN
    "music/planet-ruined.ogg",     // MENU
    "music/cheiro-somebody.ogg",   // X9
};

private
char *sounds[SND_MAX] = {
    "sfx/menu.ogg",    // MENU
    "sfx/loading.ogg", // MENU
};

typedef struct {
  /* Mix_Chunk* sounds[SND_MAX]; */
  Mix_Music *music[MSC_MAX];
  Mix_Chunk *sounds[SND_MAX];

  background_music_t current_music_playing;

} audio_t;

private
int __audio_load_music(audio_t *, char **);
private
int __audio_load_sounds(audio_t *audio, char *filename[SND_MAX]);

audio_t *audio_new() {
  audio_t *audio = (audio_t *)malloc(sizeof(audio_t));
  for (int i = 0; i < MSC_MAX; i++) {
    audio->music[i] = NULL;
  }

  return audio;
}

int audio_ctor(audio_t *audio) {

  int flags = MIX_INIT_MP3 | MIX_INIT_OGG;
  int rflags = Mix_Init(flags);
  if (flags != rflags) {
    return -1;
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0) {
    return -1;
  }

  Mix_AllocateChannels(MAX_SND_CHANNELS);

  if (__audio_load_music(audio, musics) != 0) {
    return -1;
  }
  if (__audio_load_sounds(audio, sounds) != 0) {
    return -1;
  }

  audio->current_music_playing = -1;

  return 0;
}

void audio_dtor(audio_t *audio) {
  for (int i = 0; i < MSC_MAX; i++) {
    if (audio->music[i] != NULL) {

      Mix_FreeMusic(audio->music[i]);
      audio->music[i] = NULL;
    }
  }

  for (int i = 0; i < SND_MAX; i++) {
    if (audio->sounds[i] != NULL) {
      Mix_FreeChunk(audio->sounds[i]);
      audio->sounds[i] = NULL;
    }
  }

  Mix_Quit();
}

void audio_play_music_loop(audio_t *audio, background_music_t music) {

  if (music > MSC_MAX) {
    return;
  }

  if (audio->current_music_playing == music) {
    (!Mix_PausedMusic()) ? Mix_PauseMusic() : Mix_ResumeMusic();
    return;
  }

  audio->current_music_playing = music;
  Mix_FadeInMusic(audio->music[music], -1, 11000);
}

void audio_play_sound(audio_t *audio, channels_t channel, sound_effect_t id) {

  Mix_PlayChannel(channel, audio->sounds[id], 0);
}

private
int __audio_load_sounds(audio_t *audio, char *filename[SND_MAX]) {

  for (int i = 0; i < SND_MAX; i++) {
    audio->sounds[i] = Mix_LoadWAV(filename[i]);
    if (audio->sounds[i] == NULL) {
      return -1;
    }
  }

  return 0;
}

private
int __audio_load_music(audio_t *audio, char *filename[MSC_MAX]) {

  for (int i = 0; i < MSC_MAX; i++) {
    if (audio->music[i] != NULL) {
      Mix_HaltMusic();
      Mix_FreeMusic(audio->music[i]);
      audio->music[i] = NULL;
    }

    audio->music[i] = Mix_LoadMUS(filename[i]);
    if (audio->music[i] == NULL) {
      return -1;
    }
  }

  return 0;
}
