#pragma once

#include <cstdint>
#include <string>

#include <SDL.h>
#include <SDL_syswm.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include <core/Logger.h>

using std::string;

static const Logger LOGGER = Logger::create("BGFXWindow");

class BGFXWindow {
public:
    BGFXWindow(const string& title, int32_t width, int32_t height)
        : width(width), height(height) {
        if(SDL_Init( SDL_INIT_VIDEO ) < 0) {
            LOGGER.logf(LOG_ERROR, "Failed to init SDL Video, SDL_Error: %s", SDL_GetError());
        }

        this->window = SDL_CreateWindow(title.c_str(),
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  width, height, SDL_WINDOW_SHOWN);
        if( window == nullptr ) {
            LOGGER.logf(LOG_ERROR, "Window could not be created. SDL_Error: %s", SDL_GetError());
        }
    }

    ~BGFXWindow() {
        bgfx::shutdown();
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    bool init() {
        SDL_SysWMinfo wmi;
        SDL_VERSION(&wmi.version);
        if (!SDL_GetWindowWMInfo(window, &wmi)) {
            LOGGER.logf(LOG_ERROR, "Failed to get window info. SDL_Error: %s", SDL_GetError());
            return false;
        }

        bgfx::PlatformData pd;
        pd.ndt = nullptr;
        pd.nwh = (void*)(uintptr_t)wmi.info.cocoa.window;
        bgfx::setPlatformData(pd);

        bgfx::renderFrame();
        bgfx::init();

        bgfx::reset(width, height, BGFX_RESET_VSYNC);
        // bgfx::setDebug(BGFX_DEBUG_TEXT /*| BGFX_DEBUG_STATS*/);

        bgfx::setViewRect(0, 0, 0, width, height);
        bgfx::setViewClear(0,
                           BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
                           0x443355FF, 1.0f, 0);

        // Set render state
        bgfx::setState(BGFX_STATE_DEFAULT);

        bgfx::touch(0);
        return true;
    }

private:
    SDL_Window* window;
    int32_t width;
    int32_t height;
};