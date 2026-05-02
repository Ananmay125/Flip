#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    MIX_Init();

    int windowWidth = 150, windowHeight = 150;
    SDL_Window* window = SDL_CreateWindow("Flip", windowWidth, windowHeight,
        SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_TRANSPARENT | SDL_WINDOW_UTILITY);

    SDL_Rect usable;
    SDL_GetDisplayUsableBounds(SDL_GetPrimaryDisplay(), &usable);
    SDL_SetWindowPosition(window, usable.x + usable.w - windowWidth, usable.y + usable.h - windowHeight);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    MIX_Mixer* mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
    MIX_Audio* sound = MIX_LoadAudio(mixer, "resources/gamblecore.wav", true);

    IMG_Animation* anim = IMG_LoadAnimation("resources/gamblecore.gif");
    std::vector<SDL_Texture*> frames;
    std::vector<int> delays; 

    for (int i = 0; i < anim->count; i++) {
        SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, anim->frames[i]);
        SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
        frames.push_back(tex);
        delays.push_back(anim->delays[i]);
    }
    IMG_FreeAnimation(anim);

    int currentFrame = 0;
    Uint64 lastFrameTime = SDL_GetTicks();

    bool isRunning = true, isDragging = false, isLocked = false, isPlaying = false;
    float grabX = 0, grabY = 0;

    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) isRunning = false;
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) isRunning = false;

            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_P) {
                isLocked = !isLocked;
                std::cout << (isLocked ? "Pet Locked!" : "Pet Unlocked!") << std::endl;
            }

            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT) {
                if (!isPlaying) {
                    MIX_PlayAudio(mixer, sound);
                    isPlaying = true;
                }

                if (!isLocked) {
                    isDragging = true;
                    SDL_GetGlobalMouseState(&grabX, &grabY);
                    int wx, wy; SDL_GetWindowPosition(window, &wx, &wy);
                    grabX -= wx; grabY -= wy;
                }
            }

            if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) isDragging = false;
        }

        if (isDragging && !isLocked) {
            float mx, my;
            SDL_GetGlobalMouseState(&mx, &my);
            SDL_SetWindowPosition(window, (int)(mx - grabX), (int)(my - grabY));
        }

        Uint64 now = SDL_GetTicks();
        if ((int)(now - lastFrameTime) >= delays[currentFrame]) {
            currentFrame = (currentFrame + 1) % frames.size();
            lastFrameTime = now;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_FRect rect = { 0, 0, (float)windowWidth, (float)windowHeight };
        SDL_RenderTexture(renderer, frames[currentFrame], NULL, &rect);
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    for (SDL_Texture* tex : frames) SDL_DestroyTexture(tex);
    MIX_DestroyAudio(sound);
    MIX_DestroyMixer(mixer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}