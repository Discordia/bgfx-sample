#include <core/desktop/BGFXWindow.h>
#include <core/ShaderProgram.h>
#include <core/StreamFactory.h>
#include <core/desktop/DesktopStreamFactory.h>
#include <core/desktop/InputHandler.h>
#include <core/Camera.h>
#include "ColorCube.h"

int main () {
    int32_t width = 640;
    int32_t height = 480;
    BGFXWindow window("BGFX sample", width, height);
    window.init();

    ColorCube colorCube;
    bgfx::DynamicVertexBufferHandle vertexBuffer = bgfx::createDynamicVertexBuffer(
            bgfx::makeRef(cubeVertices, sizeof(cubeVertices)),
            colorCube.getVertexLayout()
    );

    bgfx::DynamicIndexBufferHandle indexBuffer = bgfx::createDynamicIndexBuffer(
            bgfx::makeRef(cubeIndices, sizeof(cubeIndices))
    );


    ShaderProgram shaderProgram(shared_ptr<StreamFactory>(new DesktopStreamFactory("out/osx")));
    auto programHandle = shaderProgram.loadProgram("v_simple.bin", "f_simple.bin");

    Camera camera(width, height);

    const bx::Vec3 eye = { 0.0f, 0.0f, 10.0f };
    const bx::Vec3 at  = { 0.0f, 0.0f,  0.0f };
    camera.setLookAt(eye, at);
    camera.setProjection(60.0f, 0.1f, 100.0f);
    camera.update();

    // Poll for events and wait till user closes window
    bool running = true;
    InputHandler inputHandler;

    while(running) {
        inputHandler.poll();
        running = !inputHandler.exitRequested();

        bgfx::setVertexBuffer(0, vertexBuffer);
        bgfx::setIndexBuffer(indexBuffer);
        bgfx::submit(0, programHandle);
        bgfx::frame();
    }

    return 0;
}