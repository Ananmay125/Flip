#pragma once
#include <SDL3/SDL.h>
#include <unordered_map>
#include <string>

struct SoundClip {
    SDL_AudioSpec spec;
    Uint8* buf = nullptr;
    Uint32 len = 0;
    SDL_AudioStream* stream = nullptr;
};

class AudioPlayer {
private:
    SDL_AudioDeviceID device = 0;
    std::unordered_map<std::string, SoundClip> sounds;

public:
    AudioPlayer();
    ~AudioPlayer();
    bool loadSound(const std::string& name, const char* path);
    void play(const std::string& name);
    void setVolume(float gain); // 0.0 - 1.0
};