#include <core/desktop/BGFXWindow.h>
#include <core/desktop/InputHandler.h>
#include <core/Renderer.h>
#include <core/desktop/DesktopStreamFactory.h>

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

    vector<RenderChunk> renderQueue;
    Renderer renderer(shared_ptr<StreamFactory>(new DesktopStreamFactory("out/osx")));
    renderer.init(width, height);

    // Poll for events and wait till user closes window
    bool running = true;
    InputHandler inputHandler;

    auto chunk = RenderChunk::create(
            cubeVertices, sizeof(cubeVertices),
            cubeIndices, sizeof(cubeIndices));

    while(running) {
        inputHandler.poll();
        running = !inputHandler.exitRequested();

        renderer.beginFrame();
        renderer.draw(chunk);
        renderer.endFrame();
    }

    return 0;
}