#include <core/desktop/BGFXWindow.h>
#include <core/desktop/InputHandler.h>
#include <core/Renderer.h>

int main () {
    int32_t width = 640;
    int32_t height = 480;
    BGFXWindow window("BGFX sample", width, height);
    window.init();

    Renderer renderer;
    renderer.init(width, height);

    // Poll for events and wait till user closes window
    bool running = true;
    InputHandler inputHandler;

    while(running) {
        inputHandler.poll();
        running = !inputHandler.exitRequested();

        renderer.beginFrame();
        renderer.draw();
        renderer.endFrame();
    }

    return 0;
}