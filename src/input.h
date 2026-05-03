#pragma once
#include <SDL3/SDL.h>

class InputHandler {
private:
    bool isDragging = false;
    bool isLocked = false;
    bool isPaused = false;
    bool isRunning = true;
    bool teto = false;
    bool redguy = false;
    bool blue = true;
    bool check1 = true;
    bool check2 = false;
    bool check3 = false;
    bool check4 = false;
    bool check5 = false;
    bool p3 = false;
    float grabX = 0, grabY = 0;

    const char* currentGif = "resources/Blue-guy/gamblecore.gif";
    bool isBeingHeld = false;

public:
    bool running() const;
    bool paused() const;
    bool locked() const;
    bool dragging() const;
    void isTeto() {
        teto = true;
        redguy = false;
        p3 = false;
    }

    void isRed() {
        redguy = true;
        teto = false;
        p3 = false;
    }

    void isBlue() {
        redguy = false;
        teto = false;
        p3 = false;
        blue = true;
    }
    
    void isSecret() {
        redguy = false;
        teto = false;
        p3 = true;
    }

    void gifchange(const char* Epic) {
        currentGif = Epic;
    }

    void secret(SDL_Keycode key, void(*changeAnim)(const char*));

    void handleEvent(SDL_Event& event, SDL_Window* window, void(*changeAnim)(const char*));
    void updateDragging(SDL_Window* window);
    void setAnimation(const char* path, void(*changeAnim)(const char*));
};