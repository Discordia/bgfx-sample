#include <core/Renderer.h>
#include <core/StreamFactory.h>
#include <core/Camera.h>

Renderer::Renderer(shared_ptr<StreamFactory> streamFactory)
    : streamFactory(std::move(streamFactory)) {}

void Renderer::init(int32_t width, int32_t height) {
    // Camera setup
    Camera camera(width, height);
    const bx::Vec3 eye = { 0.0f, 0.0f, 10.0f };
    const bx::Vec3 at  = { 0.0f, 0.0f,  0.0f };
    camera.setLookAt(eye, at);
    camera.setProjection(60.0f, 0.1f, 100.0f);
    camera.update();

    // Shader program used to render setuo
    this->shaderProgram = ShaderProgram::load(streamFactory, "v_simple.bin", "f_simple.bin");

    // VertexBuffer and IndexBuffer setup
    this->vertexBuffer = std::make_unique<VertexBuffer>(8, VertexType::POS3_COLOR4);
    this->indexBuffer = std::make_unique<IndexBuffer>(12);
}

void Renderer::beginFrame() {
    vertexBuffer->bind();
    indexBuffer->bind();
}

void Renderer::draw(RenderChunk& renderChunk) {
    vertexBuffer->update(0, renderChunk.getVerticesAsRef());
    indexBuffer->update(0, renderChunk.getIndicesAsRef());

    shaderProgram->submit();
}

void Renderer::endFrame() {
    bgfx::frame();
}


