#pragma once
#include <SDL3/SDL.h>

class InputHandler {
private:
    bool isDragging = false;
    bool isLocked = false;
    bool isPaused = false;
    bool isRunning = true;

    float grabX = 0, grabY = 0;

    const char* currentGif = "resources/Blue-guy/gamblecore.gif";
    bool isBeingHeld = false;

public:
    bool running() const;
    bool paused() const;
    bool locked() const;
    bool dragging() const;

    void handleEvent(SDL_Event& event, SDL_Window* window, void(*changeAnim)(const char*));
    void updateDragging(SDL_Window* window);
    void setAnimation(const char* path, void(*changeAnim)(const char*));
};