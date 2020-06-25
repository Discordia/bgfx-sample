#include <core/desktop/BGFXWindow.h>
#include <bx/math.h>

#include <core/ShaderProgram.h>
#include <core/StreamFactory.h>
#include <core/desktop/DesktopStreamFactory.h>
#include <core/desktop/InputHandler.h>
#include "ColorCube.h"

int main (int argc, char* args[]) {
    int32_t width = 640;
    int32_t height = 480;
    BGFXWindow window("BGFX sample", width, height);
    window.init();

    ColorCube colorCube;
    ShaderProgram shaderProgram(shared_ptr<StreamFactory>(new DesktopStreamFactory("out/osx")));
    auto programHandle = shaderProgram.loadProgram("v_simple.bin", "f_simple.bin");

    const bx::Vec3 at  = { 0.0f, 0.0f,  0.0f };
    const bx::Vec3 eye = { 0.0f, 0.0f, 10.0f };

    // Set view and projection matrix for view 0.
    float view[16];
    bx::mtxLookAt(view, eye, at);

    float proj[16];
    bx::mtxProj(proj,
                60.0f,
                float(width)/float(height),
                0.1f, 100.0f,
                bgfx::getCaps()->homogeneousDepth);

    bgfx::setViewTransform(0, view, proj);

    float mtx[16];
    bx::mtxRotateY(mtx, 0.0f);

    // position x,y,z
    mtx[12] = 0.0f;
    mtx[13] = 0.0f;
    mtx[14] = 0.0f;

    // Set model matrix for rendering.
    bgfx::setTransform(mtx);

    // Poll for events and wait till user closes window
    bool running = true;
    InputHandler inputHandler;
    while(running) {
        inputHandler.poll();
        running = !inputHandler.exitRequested();

        // Set vertex and index buffer.
        bgfx::setVertexBuffer(0, colorCube.getVertexBuffer());
        bgfx::setIndexBuffer(colorCube.getIndexBuffer());

        // Submit primitive for rendering to view 0.
        bgfx::submit(0, programHandle);

        bgfx::frame();
    }

    return 0;
}