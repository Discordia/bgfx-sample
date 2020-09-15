#include <core/desktop/BGFXWindow.h>
#include <core/desktop/InputHandler.h>
#include <core/Renderer.h>
#include <core/desktop/DesktopStreamFactory.h>

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

static const uint16_t cubeIndices[] = {
        0,1,3,
        1,2,3};

static const uint16_t cubeIndices2[] = {
        4,5,7,
        5,6,7};


static PosColorVertex cubeVertices3[] = {
        {  0.5f,  2.5f, 0.0f, 0xff0000ff },
        {  0.5f,  1.5f, 0.0f, 0xff0000ff },
        { -0.5f,  1.5f, 0.0f, 0xff0000ff },
        { -0.5f,  2.5f, 0.0f, 0xff0000ff },
        {  1.5f,  -1.5f, 0.0f, 0xff00ff00 },
        {  1.5f, -2.5f, 0.0f, 0xff00ff00 },
        { -1.5f, -2.5f, 0.0f, 0xff00ff00 },
        { -1.5f,  -1.5f, 0.0f, 0xff00ff00 }};

static const uint16_t cubeIndices3[] = {
        0,1,3,
        1,2,3,
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
            cubeVertices, sizeof(cubeVertices),
            cubeIndices, sizeof(cubeIndices));
    auto renderChunk1 = RenderChunk::forGeometry(chunk1);

    auto chunk2 = GeometryChunk::create(
            cubeVertices2, sizeof(cubeVertices2),
            cubeIndices2, sizeof(cubeIndices2));
    auto renderChunk2 = RenderChunk::forGeometry(chunk2);

    auto chunk3 = GeometryChunk::create(
            cubeVertices3, sizeof(cubeVertices3),
            cubeIndices3, sizeof(cubeIndices3));
    auto renderChunk3 = RenderChunk::forGeometry(chunk3);

    while(running) {
        inputHandler.poll();
        running = !inputHandler.exitRequested();

        renderer.beginFrame();
        renderQueue.push_back(renderChunk1);
        renderQueue.push_back(renderChunk2);

        // Render this instead of the two render chunks above to have a working exmaple
        // renderQueue.push_back(renderChunk3);
        renderer.drawFrame();
        renderer.endFrame();
    }

    return 0;
}