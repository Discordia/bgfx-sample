#include <cstdio>
#include <SDL.h>
#include <SDL_syswm.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

SDL_Window* window = nullptr;
const int WIDTH = 640;
const int HEIGHT = 480;
int main (int argc, char* args[]) {

    // Initialize SDL systems
    if(SDL_Init( SDL_INIT_VIDEO ) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n",
               SDL_GetError());
    }
    else {
        //Create a window
        window = SDL_CreateWindow("BGFX Tutorial",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  WIDTH, HEIGHT,
                                  SDL_WINDOW_SHOWN);
        if(window == nullptr) {
            printf("Window could not be created! SDL_Error: %s\n",
                   SDL_GetError());
        }
    }

    SDL_SysWMinfo wmi;
    SDL_VERSION(&wmi.version);
    if (!SDL_GetWindowWMInfo(window, &wmi)) {
        return 1;
    }

    bgfx::PlatformData pd;
    pd.ndt = nullptr;
    pd.nwh = (void*)(uintptr_t)wmi.info.cocoa.window;
    bgfx::setPlatformData(pd);

    bgfx::renderFrame();
    bgfx::init();

    bgfx::reset(WIDTH, HEIGHT, BGFX_RESET_VSYNC);
    bgfx::setDebug(BGFX_DEBUG_TEXT /*| BGFX_DEBUG_STATS*/);

    bgfx::setViewRect(0, 0, 0, uint16_t(WIDTH), uint16_t(HEIGHT));
    bgfx::setViewClear(0,
                       BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
                       0x443355FF, 1.0f, 0);

    bgfx::touch(0);

    // Poll for events and wait till user closes window
    bool quit = false;
    SDL_Event currentEvent;
    while(!quit) {
        while(SDL_PollEvent(&currentEvent) != 0) {
            if(currentEvent.type == SDL_QUIT) {
                quit = true;
            }
        }

        bgfx::frame();
    }

    bgfx::shutdown();

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}