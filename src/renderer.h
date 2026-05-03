#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>

class Window {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    int width, height;

    std::vector<SDL_Texture*> frames;
    std::vector<int> delays;

    int currentFrame;
    Uint64 lastFrameTime;

public:
    Window(const char* title, int w, int h);
    ~Window();

    SDL_Renderer* getRenderer();

    void loadAnimation(const char* path);
    void render(bool isPaused);
    void clearFrames();

    void setPositionBottomRight();
};