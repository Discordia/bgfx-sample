#pragma once

#include <memory>
#include <bgfx/bgfx.h>

using std::shared_ptr;
using std::make_shared;

struct GeometryData {
    uint8_t *data;
    uint32_t size;

    static GeometryData *make(const void *data, uint32_t size) {
        auto *renderData = new GeometryData();
        renderData->data = (uint8_t *) data;
        renderData->size = size;
        return renderData;
    }
};

class GeometryChunk {
public:
    GeometryChunk(
            const GeometryData *vertices,
            uint32_t vertexCount,
            const GeometryData *indices,
            uint32_t indexCount) {
        this->vertices = vertices;
        this->vertexCount = vertexCount;
        this->indices = indices;
        this->indexCount = indexCount;
    }

    ~GeometryChunk() {
        if (vertices != nullptr) {
            delete vertices;
            vertices = nullptr;
        }

        if (indices != nullptr) {
            delete indices;
            indices = nullptr;
        }
    }

    static shared_ptr<GeometryChunk>    create(
            const void *vertices, uint32_t verticesSize,
            uint32_t vertexCount,
            const void *indices, uint32_t indicesSize,
            uint32_t indexCount) {
        return std::make_shared<GeometryChunk>(
                GeometryData::make(vertices, verticesSize),
                vertexCount,
                GeometryData::make(indices, indicesSize),
                indexCount);
    }

    const bgfx::Memory *getVerticesAsRef() { return bgfx::makeRef(vertices->data, vertices->size); }
    uint32_t getVertexCount() { return vertexCount; }
    const bgfx::Memory *getIndicesAsRef() { return bgfx::makeRef(indices->data, indices->size); }
    uint32_t getIndexCount() { return indexCount; }

private:
    const GeometryData *vertices;
    uint32_t vertexCount;
    const GeometryData *indices;
    uint32_t indexCount;
};