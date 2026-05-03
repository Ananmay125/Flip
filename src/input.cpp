#include "input.h"
#include <iostream>

bool InputHandler::running() const { return isRunning; }
bool InputHandler::paused() const { return isPaused; }
bool InputHandler::locked() const { return isLocked; }
bool InputHandler::dragging() const { return isDragging; }

void InputHandler::handleEvent(SDL_Event& event, SDL_Window* window, void(*changeAnim)(const char*)) {

    if (event.type == SDL_EVENT_QUIT)
        isRunning = false;

    if (event.type == SDL_EVENT_KEY_DOWN) {
        switch (event.key.key) {
        case SDLK_ESCAPE:
            isRunning = false;
            break;

        case SDLK_1:
            currentGif = "resources/Blue-guy/gamblecore.gif";
            isBlue();
            changeAnim(currentGif);
            break;

        case SDLK_2:
            currentGif = "resources/Teto/teto.gif";
            isTeto();
            changeAnim(currentGif);
            break;

        case SDLK_3:
            currentGif = "resources/Blue-guy/hard.gif";
            isBlue();
            changeAnim(currentGif);
            break;

        case SDLK_4:
            currentGif = "resources/kevin/kevin.gif";
            isBlue();
            changeAnim(currentGif);
            break;

        case SDLK_5:
            currentGif = "resources/Red-guy/explode.gif";
            isRed();
            changeAnim(currentGif);
            break;

        case SDLK_6:
            currentGif = "resources/Blue-guy/meme.gif";
            isBlue();
            changeAnim(currentGif);
            break;

        case SDLK_P:
            isLocked = !isLocked;
            std::cout << (isLocked ? "Locked in\n" : "Not locked in\n");
            break;
        }
    }

    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {

        if (event.button.button == SDL_BUTTON_LEFT) {

            if (!isBeingHeld) {
                isBeingHeld = true;
                if (teto == true) {
                    SDL_Log("Teto Pet");
                    changeAnim("resources/Teto/pet.gif");
                }
                else if (redguy == true)
                {
                    SDL_Log("Red Baby");
                    changeAnim("resources/Red-guy/goober.gif");
                }
                else
                {
                    SDL_Log("Not Teto Pet");
                    changeAnim("resources/Blue-guy/goober.gif");
                }
           
            }

            if (!isLocked) {
                isDragging = true;

                float mx, my;
                SDL_GetGlobalMouseState(&mx, &my);

                int wx, wy;
                SDL_GetWindowPosition(window, &wx, &wy);

                grabX = mx - wx;
                grabY = my - wy;
            }
        }

        if (event.button.button == SDL_BUTTON_MIDDLE) {
            isPaused = !isPaused;
        }
    }

    if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        isDragging = false;

        if (isBeingHeld) {
            isBeingHeld = false;
            changeAnim(currentGif);
        }
    }
}

void InputHandler::updateDragging(SDL_Window* window) {
    if (isDragging && !isLocked) {
        float mx, my;
        SDL_GetGlobalMouseState(&mx, &my);

        SDL_SetWindowPosition(window,
            (int)(mx - grabX),
            (int)(my - grabY));
    }
}

void InputHandler::setAnimation(const char* path, void(*changeAnim)(const char*)) {
    currentGif = path;
    changeAnim(currentGif);
}