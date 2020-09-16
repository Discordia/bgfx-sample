#include <core/Renderer.h>
#include <core/StreamFactory.h>
#include <core/Camera.h>

Renderer::Renderer(shared_ptr<StreamFactory> streamFactory, vector<shared_ptr<RenderChunk>> &renderQueue)
        : streamFactory(std::move(streamFactory)), renderQueue(renderQueue) {}

void Renderer::init(int32_t width, int32_t height) {
    // Camera setup
    Camera camera(width, height);
    const bx::Vec3 eye = {0.0f, 0.0f, 10.0f};
    const bx::Vec3 at = {0.0f, 0.0f, 0.0f};
    camera.setLookAt(eye, at);
    camera.setProjection(60.0f, 0.1f, 100.0f);
    camera.update();

    // Shader program used to render setup
    this->shaderProgram = ShaderProgram::load(streamFactory, "v_simple.bin", "f_simple.bin");

    // VertexBuffer and IndexBuffer setup
    this->vertexBuffer = std::make_unique<VertexBuffer>(20, VertexType::POS3_COLOR4);
    this->indexBuffer = std::make_unique<IndexBuffer>(20);
}

void Renderer::beginFrame() {
}

void Renderer::drawFrame() {
    uint32_t vertexOffset = 0;
    uint32_t indexOffset = 0;

    for (const auto &chunk : renderQueue) {
        auto geometry = chunk->getGeometry();
        vertexBuffer->update(vertexOffset, geometry->getVerticesAsRef());
        indexBuffer->update(indexOffset, geometry->getIndicesAsRef());

        vertexBuffer->bind();
        indexBuffer->bind(indexOffset, geometry->getIndexCount());
        shaderProgram->submit();

        vertexOffset += geometry->getVertexCount();
        indexOffset += geometry->getIndexCount();
    }
}

void Renderer::endFrame() {
    renderQueue.clear();
    bgfx::frame();
}

