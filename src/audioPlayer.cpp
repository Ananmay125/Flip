#include "audioPlayer.h"
#include <iostream>

AudioPlayer::AudioPlayer() {
    device = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    if (!device)
        std::cout << "SDL_OpenAudioDevice failed: " << SDL_GetError() << "\n";
}

AudioPlayer::~AudioPlayer() {
    for (auto& [name, clip] : sounds) {
        SDL_UnbindAudioStream(clip.stream);
        SDL_DestroyAudioStream(clip.stream);
        SDL_free(clip.buf);
    }
    SDL_CloseAudioDevice(device);
}

bool AudioPlayer::loadSound(const std::string& name, const char* path) {
    SoundClip clip;
    if (!SDL_LoadWAV(path, &clip.spec, &clip.buf, &clip.len)) {
        std::cout << "Failed to load " << path << ": " << SDL_GetError() << "\n";
        return false;
    }
    SDL_AudioSpec deviceSpec;
    SDL_GetAudioDeviceFormat(device, &deviceSpec, NULL);

    clip.stream = SDL_CreateAudioStream(&clip.spec, &deviceSpec);
    if (!clip.stream) { SDL_free(clip.buf); return false; }

    SDL_BindAudioStream(device, clip.stream);
    sounds[name] = clip;
    return true;
}

void AudioPlayer::play(const std::string& name) {
    auto it = sounds.find(name);
    if (it == sounds.end()) return;
    auto& clip = it->second;
    SDL_ClearAudioStream(clip.stream);
    SDL_PutAudioStreamData(clip.stream, clip.buf, (int)clip.len);
    SDL_FlushAudioStream(clip.stream);
}

void AudioPlayer::setVolume(float gain) {
    for (auto& [name, clip] : sounds)
        SDL_SetAudioStreamGain(clip.stream, gain);
}

bool AudioPlayer::isFinished(const std::string& name) {
    auto it = sounds.find(name);
    if (it == sounds.end()) return true;

    if (SDL_GetAudioStreamQueued(it->second.stream) == 0) {
        return true;
    }
    return false;
}