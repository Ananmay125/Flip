#include "renderer.h"
#include "input.h"
#include "Interface.h"
#include <SDL3_mixer/SDL_mixer.h>

Window* gWindow = nullptr;

void ChangeAnim(const char* path) {
    gWindow->loadAnimation(path);
}

int main(int argc, char* argv[]) {
   
    Window window("Flip", 150, 150);
    gWindow = &window;

    InputHandler input;

    window.setPositionBottomRight();
    window.loadAnimation("resources/gamblecore.gif");

    Interface ui;
    ui.init("resources/fonts/PixelPurl.ttf", 16);

    ui.addMenuItem("Play Gamble", [&input]() {
        input.setAnimation("resources/Blue-guy/gamblecore.gif", ChangeAnim);
        });

    ui.addMenuItem("Play Teto", [&input]() {
        input.setAnimation("resources/Teto/teto.gif", ChangeAnim);
        });

    ui.addMenuItem("Play Kevin", [&input]() {
        input.setAnimation("resources/kevin/kevin.gif", ChangeAnim);
        });

    ui.addMenuItem("Exit Game", []() {
        exit(0);
    });

    while (input.running()) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (!ui.handleEvent(event)) {
                input.handleEvent(event,
                    SDL_GetRenderWindow(window.getRenderer()),
                    ChangeAnim);
            }

            input.handleEvent(event,
                SDL_GetRenderWindow(window.getRenderer()),
                ChangeAnim);
        }

        input.updateDragging(SDL_GetRenderWindow(window.getRenderer()));

        window.render(input.paused());

        ui.render(window.getRenderer());
        SDL_RenderPresent(window.getRenderer());

        SDL_Delay(10);
    }

    return 0;
}