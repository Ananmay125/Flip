#pragma once
#include <SDL3/SDL.h>
#include "audioPlayer.h"

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

    bool dcheck1 = true;
    bool dcheck2 = false;
    bool dcheck3 = false;
    bool dcheck4 = false;
    bool dcheck5 = false;

    Uint32 nextHateTime = 0;
    bool p3 = false;

    float grabX = 0, grabY = 0;

    const char* currentGif = "resources/Blue-guy/gamblecore.gif";
    bool isBeingHeld = false;

public:
    void update(AudioPlayer* audio);
    bool running() const;
    bool paused() const;
    bool locked() const;
    bool dragging() const;
    int tetoac = 4; //Change this gng if adding teto audio clipss
    int z = rand() % tetoac;
    void isTeto() {
        nextHateTime = SDL_GetTicks() + (rand() % 75000 + 90000);
        teto = true;
        redguy = false;
        p3 = false;
    }

    void isRed() {
        nextHateTime = 0;
        redguy = true;
        teto = false;
        p3 = false;
    }

    void isBlue() {
        nextHateTime = 0;
        redguy = false;
        teto = false;
        p3 = false;
        blue = true;
    }
    
    void isSecret() {
        nextHateTime = 0;
        redguy = false;
        teto = false;
        p3 = true;
    }

    void gifchange(const char* Epic) {
        currentGif = Epic;
    }

    void secret(SDL_Keycode key, void(*changeAnim)(const char*));
    void handleEvent(SDL_Event& event, SDL_Window* window, void(*changeAnim)(const char*), AudioPlayer* audio);
    void updateDragging(SDL_Window* window);
    void setAnimation(const char* path, void(*changeAnim)(const char*));

};