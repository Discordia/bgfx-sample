#pragma once

#include <core/GeometryChunk.h>

class RenderChunk {
public:
    explicit RenderChunk(shared_ptr<GeometryChunk> geometryChunk)
        : geometryChunk(std::move(geometryChunk)) {}

    ~RenderChunk() = default;

    static shared_ptr<RenderChunk> forGeometry(shared_ptr<GeometryChunk> geometry) {
        return make_shared<RenderChunk>(geometry);
    }

    shared_ptr<GeometryChunk> getGeometry() {
        return geometryChunk;
    }

private:
    shared_ptr<GeometryChunk> geometryChunk;
};