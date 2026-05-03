#include "renderer.h"
#include <iostream>

Window::Window(const char* title, int w, int h)
    : width(w), height(h), currentFrame(0)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    window = SDL_CreateWindow(title, width, height,
        SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP |
        SDL_WINDOW_TRANSPARENT | SDL_WINDOW_UTILITY);

    renderer = SDL_CreateRenderer(window, NULL);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    lastFrameTime = SDL_GetTicks();
}

Window::~Window() {
    clearFrames();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Renderer* Window::getRenderer() {
    return renderer;
}

void Window::clearFrames() {
    for (auto tex : frames) {
        SDL_DestroyTexture(tex);
    }
    frames.clear();
    delays.clear();
    currentFrame = 0;
}

void Window::loadAnimation(const char* path) {
    clearFrames();

    IMG_Animation* anim = IMG_LoadAnimation(path);
    if (!anim) return;

    for (int i = 0; i < anim->count; i++) {
        SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, anim->frames[i]);
        SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);

        frames.push_back(tex);
        delays.push_back(anim->delays[i]);
    }

    IMG_FreeAnimation(anim);
}

void Window::render(bool isPaused) {
    Uint64 now = SDL_GetTicks();

    if (!isPaused && !frames.empty()) {
        if ((int)(now - lastFrameTime) >= delays[currentFrame]) {
            currentFrame = (currentFrame + 1) % frames.size();
            lastFrameTime = now;
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    if (!frames.empty()) {
        SDL_FRect rect = { 0, 0, (float)width, (float)height };
        SDL_RenderTexture(renderer, frames[currentFrame], NULL, &rect);
    }

    SDL_RenderPresent(renderer);
}

void Window::setPositionBottomRight() {
    SDL_Rect usable;
    SDL_GetDisplayUsableBounds(SDL_GetPrimaryDisplay(), &usable);

    SDL_SetWindowPosition(window,
        usable.x + usable.w - width,
        usable.y + usable.h - height);
}