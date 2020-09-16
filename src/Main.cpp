#include <core/desktop/BGFXWindow.h>
#include <core/desktop/InputHandler.h>
#include <core/Renderer.h>
#include <core/desktop/DesktopStreamFactory.h>
#include <iostream>

static PosColorVertex cubeVertices[] = {
        {  0.5f,  2.5f, 0.0f, 0xff0000ff },
        {  0.5f,  1.5f, 0.0f, 0xff0000ff },
        { -0.5f,  1.5f, 0.0f, 0xff0000ff },
        { -0.5f,  2.5f, 0.0f, 0xff0000ff }};

static PosColorVertex cubeVertices2[] = {
        {  1.5f,  -1.5f, 0.0f, 0xff00ff00 },
        {  1.5f, -2.5f, 0.0f, 0xff00ff00 },
        { -1.5f, -2.5f, 0.0f, 0xff00ff00 },
        { -1.5f,  -1.5f, 0.0f, 0xff00ff00 }};

static const uint32_t cubeIndices[] = {
        0,1,3,
        1,2,3};

static const uint32_t cubeIndices2[] = {
        4,5,7,
        5,6,7};

int main () {
    int32_t width = 640;
    int32_t height = 480;
    BGFXWindow window("BGFX sample", width, height);
    window.init();

    vector<shared_ptr<RenderChunk>> renderQueue;
    Renderer renderer(shared_ptr<StreamFactory>(new DesktopStreamFactory("out/osx")), renderQueue);
    renderer.init(width, height);

    // Poll for events and wait till user closes window
    bool running = true;
    InputHandler inputHandler;

    auto chunk1 = GeometryChunk::create(
            cubeVertices, sizeof(cubeVertices), 4,
            cubeIndices, sizeof(cubeIndices), 6);
    auto renderChunk1 = RenderChunk::forGeometry(chunk1);

    auto chunk2 = GeometryChunk::create(
            cubeVertices2, sizeof(cubeVertices2), 4,
            cubeIndices2, sizeof(cubeIndices2), 6);
    auto renderChunk2 = RenderChunk::forGeometry(chunk2);

    while(running) {
        inputHandler.poll();
        running = !inputHandler.exitRequested();

        renderer.beginFrame();
        renderQueue.push_back(renderChunk1);
        renderQueue.push_back(renderChunk2);

        renderer.drawFrame();
        renderer.endFrame();
    }

    return 0;
}