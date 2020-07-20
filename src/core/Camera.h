#pragma once

#include <bx/math.h>
#include <bgfx/bgfx.h>

class Camera {
public:
    Camera(int32_t width, int32_t height)
        : width(width), height(height) {
        bx::mtxRotateY(model, 0.0f);
        model[12] = 0.0f;
        model[13] = 0.0f;
        model[14] = 0.0f;
    }

    void setLookAt(const bx::Vec3& eye, const bx::Vec3& at) {
        bx::mtxLookAt(view, eye, at);
    }

    void setProjection(float fovy, float near, float far) {
        bx::mtxProj(projection,
                    fovy,
                    float(width)/float(height),
                    near, far,
                    bgfx::getCaps()->homogeneousDepth);
    }

    void update() {
        bgfx::setViewTransform(0, view, projection);
        bgfx::setTransform(model);
    }

private:
    int32_t width;
    int32_t height;
    float view[16]{};
    float projection[16]{};
    float model[16]{};
};