#pragma once

struct RenderData {
    uint8_t *data;
    uint32_t size;

    static RenderData *make(const void *data, uint32_t size) {
        auto *renderData = new RenderData();
        renderData->data = (uint8_t *) data;
        renderData->size = size;
        return renderData;
    }
};

class RenderChunk {
public:
    static RenderChunk create(const void *vertices, uint32_t verticesSize, const void *indices, uint32_t indicesSize) {
        return RenderChunk(
                RenderData::make(vertices, verticesSize),
                RenderData::make(indices, indicesSize)
        );
    }

    ~RenderChunk() {
        if (vertices != nullptr) {
            delete vertices;
            vertices = nullptr;
        }

        if (indices != nullptr) {
            delete indices;
            indices = nullptr;
        }
    }

    const RenderData *getVertices() { return vertices; }
    const bgfx::Memory *getVerticesAsRef() { return bgfx::makeRef(vertices->data, vertices->size); }

    const RenderData *getIndices() { return indices; }
    const bgfx::Memory *getIndicesAsRef() { return bgfx::makeRef(indices->data, indices->size); }

private:
    RenderChunk(const RenderData *vertices, const RenderData *indices) {
        this->vertices = vertices;
        this->indices = indices;
    }

    const RenderData *vertices;
    const RenderData *indices;
};