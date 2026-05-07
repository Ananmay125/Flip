#include "renderer.h"
#include "input.h"
#include "Interface.h"
#include "audioPlayer.h"
#include <SDL3_mixer/SDL_mixer.h>
#include <time.h>

Window* gWindow = nullptr;

void ChangeAnim(const char* path) {
    gWindow->loadAnimation(path);
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
   
    Window window("Flip", 150, 150);
    gWindow = &window;

    InputHandler input;

    window.setPositionBottomRight();
    window.loadAnimation("resources/Blue-guy/gamblecore.gif");
    AudioPlayer audio;
    audio.loadSound("blue", "resources/audio/gamblecore.wav");
    audio.loadSound("teto", "resources/audio/teto.wav");
    audio.loadSound("hate", "resources/audio/teto1.wav");
    audio.loadSound("tetoing", "resources/audio/tetoing.wav");
    audio.loadSound("teto2", "resources/audio/teto2.wav");
    audio.loadSound("teto3", "resources/audio/teto2.wav");
    audio.loadSound("aigis", "resources/audio/aigis.wav");
    audio.loadSound("peak", "resources/audio/peak.wav");

    Interface ui;
    ui.init("resources/fonts/PixelPurl.ttf", 16);

    ui.addMenuItem("Play Gamble", [&input]() {
        input.isBlue();
        input.setAnimation("resources/Blue-guy/gamblecore.gif", ChangeAnim);
        });

    ui.addMenuItem("Play Teto", [&input]() {
        input.setAnimation("resources/Teto/teto.gif", ChangeAnim);
        input.isTeto();
        });

    ui.addMenuItem("Rei(Requested Item)", [&input]() {
        input.setAnimation("resources/Rei/rei.gif", ChangeAnim);
        input.isRei();
        });

    ui.addMenuItem("Explode", [&input]() {
        input.isRed();
        input.setAnimation("resources/Red-guy/explode.gif", ChangeAnim);
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
                    ChangeAnim, &audio);
            }

            
        }
        input.update(&audio);

        input.updateDragging(SDL_GetRenderWindow(window.getRenderer()));

        window.render(input.paused());

        ui.render(window.getRenderer());
        SDL_RenderPresent(window.getRenderer());

        SDL_Delay(10);
    }

    return 0;
}