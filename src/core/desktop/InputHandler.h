#pragma once

#include <SDL.h>

class InputHandler {
public:
    InputHandler()
        : quit(false) {}

    void poll() {
        SDL_Event currentEvent;
        while(SDL_PollEvent(&currentEvent) != 0) {
            if (currentEvent.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    bool exitRequested() const {
        return quit;
    }

private:
    bool quit;
};