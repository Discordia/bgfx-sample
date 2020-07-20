#pragma once

#include <bgfx/bgfx.h>

struct PosColorVertex {
    float x;
    float y;
    float z;
    uint32_t abgr;
};


static PosColorVertex cubeVertices[] = {
        {  0.5f,  0.5f, 0.0f, 0xff0000ff },
        {  0.5f, -0.5f, 0.0f, 0xff0000ff },
        { -0.5f, -0.5f, 0.0f, 0xff00ff00 },
        { -0.5f,  0.5f, 0.0f, 0xff00ff00 }};

static const uint16_t cubeIndices[] = {
        0,1,3,
        1,2,3};



class ColorCube {
public:
    ColorCube() {
        bgfx::VertexLayout vertexLayout;
        vertexLayout
                .begin()
                .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
                .add(bgfx::Attrib::Color0,   4, bgfx::AttribType::Uint8, true)
                .end();

        vertexBuffer = bgfx::createVertexBuffer(
                bgfx::makeRef(cubeVertices, sizeof(cubeVertices)),
                vertexLayout
        );

        indexBuffer = bgfx::createIndexBuffer(
                bgfx::makeRef(cubeIndices, sizeof(cubeIndices))
        );
    }

    bgfx::VertexBufferHandle getVertexBuffer() {
        return vertexBuffer;
    }

    bgfx::IndexBufferHandle getIndexBuffer() {
        return indexBuffer;
    }

private:
    bgfx::VertexBufferHandle vertexBuffer{};
    bgfx::IndexBufferHandle indexBuffer{};
};