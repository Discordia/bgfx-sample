#include <core/desktop/BGFXWindow.h>
#include <core/ShaderProgram.h>
#include <core/StreamFactory.h>
#include <core/desktop/DesktopStreamFactory.h>
#include <core/desktop/InputHandler.h>
#include <core/Camera.h>

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

    bgfx::VertexLayout vertexLayout;
    vertexLayout
            .begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Color0,   4, bgfx::AttribType::Uint8, true)
            .end();

    bgfx::DynamicVertexBufferHandle vertexBuffer = bgfx::createDynamicVertexBuffer(8, vertexLayout);
    bgfx::DynamicIndexBufferHandle indexBuffer = bgfx::createDynamicIndexBuffer(12);

    ShaderProgram shaderProgram(shared_ptr<StreamFactory>(new DesktopStreamFactory("out/osx")));
    auto programHandle = shaderProgram.loadProgram("v_simple.bin", "f_simple.bin");

    Camera camera(width, height);

    const bx::Vec3 eye = { 0.0f, 0.0f, 10.0f };
    const bx::Vec3 at  = { 0.0f, 0.0f,  0.0f };
    camera.setLookAt(eye, at);
    camera.setProjection(60.0f, 0.1f, 100.0f);
    camera.update();

    // Poll for events and wait till user closes window
    bool running = true;
    InputHandler inputHandler;

    while(running) {
        inputHandler.poll();
        running = !inputHandler.exitRequested();

        bgfx::setVertexBuffer(0, vertexBuffer);
        bgfx::setIndexBuffer(indexBuffer);

        bgfx::update(vertexBuffer, 0, bgfx::makeRef(cubeVertices, sizeof(cubeVertices)));
        bgfx::update(indexBuffer, 0, bgfx::makeRef(cubeIndices, sizeof(cubeIndices)));

        bgfx::submit(0, programHandle);
        bgfx::frame();
    }

    return 0;
}