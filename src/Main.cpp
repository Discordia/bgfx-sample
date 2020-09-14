#include <core/desktop/BGFXWindow.h>
#include <core/desktop/InputHandler.h>
#include <core/Renderer.h>

struct PosColorVertex {
    float x;
    float y;
    float z;
    uint32_t abgr;
};

static PosColorVertex cubeVertices[] = {
        {  0.5f,  0.5f, 0.0f, 0xff0000ff },
        {  0.5f, -0.5f, 0.0f, 0xff0000ff },
        { -0.5f, -0.5f, 0.0f, 0xff0000ff },
        { -0.5f,  0.5f, 0.0f, 0xff0000ff }};

static const uint16_t cubeIndices[] = {
        0,1,3,
        1,2,3};

int main () {
    int32_t width = 640;
    int32_t height = 480;
    BGFXWindow window("BGFX sample", width, height);
    window.init();

    Renderer renderer{};
    renderer.init(width, height);

    // Poll for events and wait till user closes window
    bool running = true;
    InputHandler inputHandler;

    const RenderMemory *vertices = new RenderMemory(cubeVertices, sizeof(cubeVertices));
    const RenderMemory *indices = new RenderMemory(cubeIndices, sizeof(cubeIndices));

    while(running) {
        inputHandler.poll();
        running = !inputHandler.exitRequested();

        renderer.beginFrame();
        renderer.draw(vertices, indices);
        renderer.endFrame();
    }

    return 0;
}