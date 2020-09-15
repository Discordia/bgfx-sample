#pragma once

#include <memory>
#include <bgfx/bgfx.h>

using std::shared_ptr;
using std::make_shared;

struct GeoemtryData {
    uint8_t *data;
    uint32_t size;

    static GeoemtryData *make(const void *data, uint32_t size) {
        auto *renderData = new GeoemtryData();
        renderData->data = (uint8_t *) data;
        renderData->size = size;
        return renderData;
    }
};

class GeometryChunk {
public:
    GeometryChunk(const GeoemtryData *vertices, const GeoemtryData *indices) {
        this->vertices = vertices;
        this->indices = indices;
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

    static shared_ptr<GeometryChunk> create(
            const void *vertices, uint32_t verticesSize,
            const void *indices, uint32_t indicesSize) {
        return std::make_shared<GeometryChunk>(
                GeoemtryData::make(vertices, verticesSize),
                GeoemtryData::make(indices, indicesSize));
    }

    const GeoemtryData *getVertices() { return vertices; }
    const bgfx::Memory *getVerticesAsRef() { return bgfx::makeRef(vertices->data, vertices->size); }

    const GeoemtryData *getIndices() { return indices; }
    const bgfx::Memory *getIndicesAsRef() { return bgfx::makeRef(indices->data, indices->size); }

private:
    const GeoemtryData *vertices;
    const GeoemtryData *indices;
};