#ifndef SOUND_HPP
#define SOUND_HPP
#include <SDL2/SDL_mixer.h>

class Sound {
public:
    Sound(const char* filepath, int volume);
    Sound(const char* filepath);
    void play();
    void play(int times);
    void setVolume(int volume);

private:
    Mix_Chunk *audioChunk;
};
#endif