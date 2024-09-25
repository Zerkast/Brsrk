#include "Sound.hpp"
#include <cstddef>
#include <cstdio>

Sound::Sound(const char* filepath, int volume) {
    audioChunk = Mix_LoadWAV(filepath);
    if (audioChunk == NULL) {
        printf("Couldnt load audio sound: %s", filepath);
    }
    Mix_VolumeChunk(audioChunk, volume);
}

Sound::Sound(const char* filepath) {
    audioChunk = Mix_LoadWAV(filepath);
    if (audioChunk == NULL) {
        printf("Couldnt load audio sound: %s", filepath);
    }
    Mix_VolumeChunk(audioChunk, 100);
}
// -1 here means we let SDL_mixer pick the first channel that is free
// If no channel is free it'll return an err code.
void Sound::play() {
    Mix_PlayChannel(-1, audioChunk, 0);
}

void Sound::play(int times) {
    Mix_PlayChannel(-1, audioChunk, times - 1);
}

void Sound::setVolume(int volume) {
    Mix_VolumeChunk(audioChunk, volume);
}