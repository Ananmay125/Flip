#include "renderer.h"
#include "input.h"
#include <SDL3_mixer/SDL_mixer.h>

Window* gWindow = nullptr;

void ChangeAnim(const char* path) {
    gWindow->loadAnimation(path);
}

int main(int argc, char* argv[]) {

    Window window("Flip", 150, 150);
    gWindow = &window;

    window.setPositionBottomRight();
    window.loadAnimation("resources/gamblecore.gif");

    InputHandler input;

    while (input.running()) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            input.handleEvent(event,
                SDL_GetRenderWindow(window.getRenderer()),
                ChangeAnim);
        }

        input.updateDragging(SDL_GetRenderWindow(window.getRenderer()));

        window.render(input.paused());

        SDL_Delay(10);
    }

    return 0;
}