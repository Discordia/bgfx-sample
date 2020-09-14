#include <core/Renderer.h>
#include <core/ShaderProgram.h>
#include <core/StreamFactory.h>
#include <core/desktop/DesktopStreamFactory.h>
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

void Renderer::init(int32_t width, int32_t height) {
    bgfx::VertexLayout vertexLayout;
    vertexLayout
            .begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Color0,   4, bgfx::AttribType::Uint8, true)
            .end();

    this->vertexBuffer0 = bgfx::createDynamicVertexBuffer(8, vertexLayout);
    this->indexBuffer0 = bgfx::createDynamicIndexBuffer(12);

    ShaderProgram shaderProgram(shared_ptr<StreamFactory>(new DesktopStreamFactory("out/osx")));
    this->programHandle = shaderProgram.loadProgram("v_simple.bin", "f_simple.bin");

    Camera camera(width, height);

    const bx::Vec3 eye = { 0.0f, 0.0f, 10.0f };
    const bx::Vec3 at  = { 0.0f, 0.0f,  0.0f };
    camera.setLookAt(eye, at);
    camera.setProjection(60.0f, 0.1f, 100.0f);
    camera.update();
}

void Renderer::beginFrame() {
    bgfx::setVertexBuffer(0, vertexBuffer0);
    bgfx::setIndexBuffer(indexBuffer0);
}

void Renderer::draw() {
    bgfx::update(vertexBuffer0, 0, bgfx::makeRef(cubeVertices, sizeof(cubeVertices)));
    bgfx::update(indexBuffer0, 0, bgfx::makeRef(cubeIndices, sizeof(cubeIndices)));

    bgfx::submit(0, programHandle);
}

void Renderer::endFrame() {
    bgfx::frame();
}


